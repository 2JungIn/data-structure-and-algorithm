#ifndef _PAIR_H_
#define _PAIR_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct pair
{
    void *first;
    void *second;
    
    int (*compare)(const void *, const void *);
    void (*free_first)(void *);     /* 첫번째 원소 free 함수 */
    void (*free_second)(void *);    /* 두번째 원소 free 함수 */
} pair;

pair *init_pair(void *first, void *second, int (*compare)(const void *, const void *), void (*free_first)(void *), void (*free_second)(void *));
void destroy_pair(pair *p);

void *get_first(const pair *p);
void *get_second(const pair *p);

int set_first(pair *p, void *elem);
int set_second(pair *p, void *elem);

void swap_elem(pair *p, int (*compare)(const void *, const void *));

#ifdef __cplusplus
}
#endif

#endif  /* _PAIR_H_ */