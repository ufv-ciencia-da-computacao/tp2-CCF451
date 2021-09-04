#ifndef __READY_H__
#define __READY_H__

typedef struct queuePriority* ptrQueueP;
typedef struct queuePriority{
  int index;
  ptrQueueP next;
}queuePriority;

typedef struct ready{
    queuePriority *hPriority;
    queuePriority *mPriority;
    queuePriority *lPriority;
    queuePriority *vLPriority;
}ready_t;


void ready_init(ready_t *ready);//OK
void ready_destroy(ready_t *ready);//OK
void ready_push(ready_t *ready, int index,int priority);//OK
void ready_pop(ready_t *ready);//OK
int  ready_top(ready_t *ready);//OK
int  ready_empty(ready_t *ready);//OK
int  ready_size(ready_t *ready);//OK

void queue_init(queuePriority *queue,int index);//OK
void queue_destroy(queuePriority *queue);//OK
queuePriority* queue_pop(queuePriority *queue);//OK
int queue_size(queuePriority *queue);//OK

void add_index(queuePriority *queue,int index);//OK
void toString(ready_t *ready);//OK


#endif
