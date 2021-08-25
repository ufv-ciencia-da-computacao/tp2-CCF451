#ifndef __BLOCKED_H__
#define __BLOCKED_H__

typedef struct{
    int *pid;
    int front, back;
} blocked_t;

void blocked_init(blocked_t *blocked, int size);
void blocked_destroy(blocked_t *blocked);
void blocked_push(blocked_t *blocked, int value);
void blocked_pop(blocked_t *blocked);
int  blocked_front(blocked_t *blocked);
int  blocked_empty(blocked_t *blocked);
int  blocked_size(blocked_t *blocked);

#endif
