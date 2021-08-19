#ifndef __READY_H__
#define __READY_H__

typedef struct ready * ready_t;

void ready_init(ready_t *ready, int size);
void ready_destroy(ready_t *ready);
void ready_push(ready_t *ready, int value);
void ready_pop(ready_t *ready);
int  ready_top(ready_t *ready);
int  ready_empty(ready_t *ready);
int  ready_size(ready_t *ready);


#endif