#ifndef __EXECUTING_H__
#define __EXECUTING_H__

typedef struct executing executing_t;

struct executing {
    // ids da tabela de processos
    int id;
    int working;
};

void executing_init(executing_t *executing);
void executing_destroy(executing_t *executing);
void executing_set(executing_t *executing, int id);
int executing_get(executing_t *executing);

#endif
