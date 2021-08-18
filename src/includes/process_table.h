#ifndef __PROCESS_TABLE_H__
#define __PROCESS_TABLE_H__

typedef struct process_table * process_table_t;

typedef enum {
    state_ready,
    state_executing,
    state_blocked
} process_state;

void process_table_init(process_table_t *pt, int size);
void process_table_destroy(process_table_t *pt);

#endif