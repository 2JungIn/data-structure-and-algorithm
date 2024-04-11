#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/stack.h"

char *new_data(char ch)
{
    return memcpy(malloc(sizeof(char)), &ch, sizeof(char));
}

int main(void)
{
    char str[] = "Now i won.";
    
    printf("origin: %s\n", str);
    
    printf("reverse: ");
    stack *s = init_stack(NULL);

    stack_pop(s);
    stack_top(s);

    for (int i = 0; str[i]; i++)
        stack_push(s, &str[i]);

    while (!stack_empty(s))
    {
        char *top = stack_pop(s);
        printf("%c", *top);
    }
    printf("\n");

    destroy_stack(s);

    return 0;
}