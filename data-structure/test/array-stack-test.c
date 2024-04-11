#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/array-stack.h"

char *new_data(char ch)
{
    return memcpy(malloc(sizeof(char)), &ch, sizeof(char));
}

int main(void)
{
    char str[] = "Now i won.123456789";
    
    printf("origin: %s\n", str);
    
    printf("reverse: ");
    array_stack *s = init_array_stack(NULL);

    array_stack_pop(s);
    array_stack_top(s);

    for (int i = 0; str[i]; i++)
        array_stack_push(s, &str[i]);

    array_stack_resize(s, 10);

    while (!array_stack_empty(s))
    {
        char *top = array_stack_pop(s);
        printf("%c", *top);
    }
    printf("\n");

    destroy_array_stack(s);

    return 0;
}