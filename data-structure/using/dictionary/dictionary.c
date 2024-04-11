/**
 * dictionary.c
 * 
 * 해시 테이블을 사용해서 검색을 하는 프로그램입니다.
**/

#define _POSIX_C_SOURCE  200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/hash-table.h"
#include "../../include/pair.h"
#include "md5.h"

#define BUFFER_SIZE  1024

char *make_string(const char *str);

uint8_t *md5_string(const char *word);
int hash_function(const char *word);

hash_table *init_dictionary(const char *file)
{
    hash_table *dictionary = init_hash_table(
        0,
        (int (*)(const void *))hash_function,
        (int (*)(const void *, const void *))strcmp,
        free, 
        free
    );

    FILE *fp = NULL;
    if ((fp = fopen(file, "rt")) == NULL)
    {
        fprintf(stderr, "can not open file!\n");
        exit(EXIT_FAILURE);
    }

    char *buffer = NULL;
    size_t buffer_size;
    ssize_t n_read;

    while (feof(fp) == 0)
    {
        n_read = getline(&buffer, &buffer_size, fp);
        buffer[n_read - 1] = '\0';
        char *key = make_string(buffer);
        
        n_read = getline(&buffer, &buffer_size, fp);
        buffer[n_read - 1] = '\0';
        char *value = make_string(buffer);

        if (hash_table_insert(dictionary, key, value) < 0)
        {
            hash_table_update(dictionary, key, value);
            free(key);
        }
    }

    free(buffer);
    fclose(fp);

    return dictionary;
}


int main(void)
{
    hash_table *dictionary = init_dictionary("eng_dic.txt");

    char *input = NULL;
    size_t size = BUFFER_SIZE;
    ssize_t n_len;
    while (1)
    {
        printf("Input a word : ");
        n_len = getline(&input, &size, stdin);
        input[n_len - 1] = '\0';

        if (!strcmp(input, "exit"))
            break;
        
        char *result = (char *)hash_table_get_value(dictionary, input);
        if (result == NULL)
            printf("%s is not found!\n", input);
        else
            printf("%s\n", result);
    }

    free(input);
    destroy_hash_table(dictionary);

    return 0;
}


char *make_string(const char *str)
{
    return strcpy((char *)malloc(strlen(str) + 1), str);
}


uint8_t *md5_string(const char *word)
{
    uint8_t *hash_value = (uint8_t *)malloc(sizeof(uint8_t) * 16);

    MD5_CTX ctx;
    MD5Init(&ctx);
    MD5Update(&ctx, (uint8_t *)word, (int)strlen(word));
    MD5Final(hash_value, &ctx);

    return hash_value;
}

int hash_function(const char *word)
{
    uint8_t *md5_hash = md5_string(word);
    
    unsigned int ret_value = 0;
    for (int i = 0; i < 16; i += 4)
    {
        unsigned int temp = ((unsigned int)(md5_hash[i + 0] << 24) |
                            (unsigned int)(md5_hash[i + 1] << 16) |
                            (unsigned int)(md5_hash[i + 2] << 8) |
                            (unsigned int)(md5_hash[i + 3] << 0));
        ret_value += temp;
    }
    free(md5_hash);

    return (int)(ret_value & 0x7FFFFFFF);
}

