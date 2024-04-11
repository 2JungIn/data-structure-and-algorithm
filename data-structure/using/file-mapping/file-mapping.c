#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>

#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

#include "../../include/map.h"

#define MAX_PATH    1024
#define BUFFER_SIZE 1024

struct file
{
    size_t file_size;
    char *mapped_addr;
};

void unix_error(const char *msg);
int compare(const char *str1, const char *str2);
struct file *make_file(const char *file_name);
void release_file(struct file *f);

map *init_file_map(const char *path)
{
    char current_dir[MAX_PATH];
    if (getcwd(current_dir, sizeof(current_dir)) == NULL)
        unix_error("getcwd");

    if (chdir(path) < 0)
        unix_error("chdir");
    
    map *file_map = init_map(
        (int (*)(const void *, const void *))compare,
        free,
        (void (*)(void *))release_file);

    DIR *d = NULL;

    if ((d = opendir("./")) == NULL)
        unix_error("opendir");

    for (struct dirent *e = readdir(d); e; e = readdir(d))
    {
        if (e->d_type != DT_REG)
            continue;
        
        char *file_name = strdup(e->d_name);
        struct file *f = make_file(file_name);
        if (f == NULL)  /* error: make_file() */
        {
            printf("\"%s\" mapping failed!\n", file_name);
            free(file_name);
            continue;
        }

        map_insert(file_map, file_name, f);
        printf("\"%s\" mapping success!\n", file_name);
    }
    
    if (closedir(d) < 0)
        unix_error("closedir");

    if (chdir(current_dir) < 0)
        unix_error("chdir");

    return file_map;
}

int main(void)
{
    map *file_map = init_file_map("../../src");
    
    char *input = NULL;
    size_t size = BUFFER_SIZE;
    ssize_t n_len;
    while (1)
    {
        printf("\nInput print file name: ");
        n_len = getline(&input, &size, stdin);
        input[n_len - 1] = '\0';

        if (!strcmp(input, "exit"))
            break;
        
        struct file *f = (struct file *)map_get_value(file_map, input);
        if (f == NULL)
            printf("\"%s\" is not found!\n", input);
        else
        {
            const size_t file_size = f->file_size;
            const char *mapped_addr = f->mapped_addr;

            printf("\n[file name: \"%s\"\tfile size: %ld Byte]\n\n", input, file_size);

            for (size_t i = 0; i < f->file_size; i++)
                printf("%c", mapped_addr[i]);
            
            printf("\n\n");
        }
    }

    free(input);

    destroy_map(file_map);

    return 0;
}


void unix_error(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int compare(const char *str1, const char *str2)
{
    return strcmp(str1, str2);
}

struct file *make_file(const char *file_name)
{
    if (file_name == NULL)
        return NULL;
    
    int fd;
    if ((fd = open(file_name, O_RDONLY, 0644)) < 0)
        unix_error("open");
    
    struct stat s;
    if (fstat(fd, &s) < 0)
        unix_error("fstat");
    
    char *mapped_addr = NULL;
    if ((mapped_addr = (char *)mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
        unix_error("mmap");
    
    if (close(fd) < 0)
        unix_error("close");

    struct file *f = NULL;
    if ((f = (struct file *)malloc(sizeof(struct file))) == NULL)
    {
        fprintf(stderr, "malloc( %ld ): failed!\n", sizeof(struct file));

        if (munmap(mapped_addr, s.st_size) < 0)
            unix_error("munmap");

        return NULL;
    }

    f->file_size = s.st_size;
    f->mapped_addr = mapped_addr;

    return f;
}

void release_file(struct file *f)
{
    if (f == NULL)
        return ;
    
    if (munmap(f->mapped_addr, f->file_size) < 0)
        unix_error("munmap");
    
    free(f);
}