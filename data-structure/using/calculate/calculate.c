/**
 * calculate.c
 * 
 * 스텍과 큐를 사용해서 수식을 계산하는 프로그램입니다.
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/stack.h"
#include "../../include/queue.h"

void print_char(const void *c);
void print_int(const void *n);
void stack_print(const stack *s, void (*print_item)(const void *));
void queue_print(const queue *q, void (*print_item)(const void *));

int *new_int(const int i);

int compare(const char a, const char b);
int to_int(char ch);

int operator(const char ch)
{
    if(ch == '+' || ch == '-' || ch == '*' || ch == '/')
        return 1;

    return 0;
}

int prec(char ope)
{
    if(ope == '*' || ope == '/')
        return 2;
    if(ope == '+' || ope == '-')
        return 1;
    return 0;
}

queue *get_postfix(const char *infix, const int n)
{
    queue *postfix = init_queue(NULL);
    stack *s = init_stack(NULL);

    for (int i = 0; i < n; i++)
    {
        char *ch = (char *)&infix[i];

        if (*ch >= '0' && *ch <= '9')
        {
            queue_enqueue(postfix, ch);
        }
        else if (*ch == '(')
        {
            stack_push(s, ch);
        }
        else if (*ch == ')')
        {
            while (!stack_empty(s) && *(char *)stack_top(s) != '(')
                queue_enqueue(postfix, stack_pop(s));

            stack_pop(s);
        }
        else
        {
            while (!stack_empty(s) && prec(*ch) <= prec(*(char *)stack_top(s)))
                queue_enqueue(postfix, stack_pop(s));

            stack_push(s, ch);
        }

        printf("stack: ");
        stack_print(s, print_char);
        printf("queue: ");
        queue_print(postfix, print_char);
        printf("\n");
    }

    while (!stack_empty(s))
        queue_enqueue(postfix, stack_pop(s));

    printf("stack: ");
    stack_print(s, print_char);
    printf("queue: ");
    queue_print(postfix, print_char);
    printf("\n");

    destroy_stack(s);

    return postfix;
}

int calculate(const char *infix, const int n)
{
    queue *postfix = get_postfix(infix, n);
    stack *s = init_stack(NULL);

    while (!queue_empty(postfix))
    {
        char *front = (char *)queue_dequeue(postfix);

        if (!operator(*front))
        {
            stack_push(s, new_int(to_int(*front)));
        }
        else
        {
            int *b = (int *)stack_pop(s);
            int *a = (int *)stack_pop(s); 

            switch (*front)
            {
                case '+': stack_push(s, new_int( (*a) + (*b) )); break;
                case '-': stack_push(s, new_int( (*a) - (*b) )); break;
                case '*': stack_push(s, new_int( (*a) * (*b) )); break;
                case '/': stack_push(s, new_int( (*a) / (*b) )); break;
                default : 
                    printf("Unkown operator!\n"); 
                    exit(EXIT_FAILURE);
            }

            free(a);
            free(b);
        }

        printf("stack: ");
        stack_print(s, print_int);
    }

    int *top = (int *)stack_pop(s);
    int result = *top;
    free(top);

    destroy_stack(s);
    destroy_queue(postfix);

    return result;
}


int main(void)
{
    char infix[] = "((1+2)*3-4)/5";
    int n = sizeof(infix) / sizeof(infix[0]) - 1;
    
    printf("\ncalculate: %d\n", calculate(infix, n)); /* 1 */
    
    return 0;
}


void print_char(const void *c)
{
    printf("%c ", *(char *)c);
}

void print_int(const void *n)
{
    printf("%d ", *(int *)n);
}

void stack_print(const stack *s, void (*print_item)(const void *))
{
    iterator begin = single_linked_list_begin(s);
    iterator end = single_linked_list_end(s);

    for (iterator itr = begin; itr != end; itr = single_linked_list_next(itr))
    {
        print_item(single_linked_list_iter_get(itr));
    }

    printf ("\n");
}

void queue_print(const queue *q, void (*print_item)(const void *))
{
    iterator begin = single_linked_list_begin(q);
    iterator end = single_linked_list_end(q);

    for (iterator itr = begin; itr != end; itr = single_linked_list_next(itr))
        print_item(single_linked_list_iter_get(itr));

    printf ("\n");
}


int *new_int(const int i)
{
    return memcpy(malloc(sizeof(int)), &i, sizeof(int));
}


int compare(const char a, const char b)
{
    return a - b;
}

int to_int(char ch)
{
    return ch - '0';
}
