#ifndef __EXECUTING_H__
#define __EXECUTING_H__

typedef struct executing * executing_t;

void executing_init(executing_t *executing);
void executing_destroy(executing_t *executing);
void executing_set(executing_t *executing /*, parameters */);

#endif