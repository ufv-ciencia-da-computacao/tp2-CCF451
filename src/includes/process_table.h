#ifndef __PROCESS_TABLE_H__
#define __PROCESS_TABLE_H__

#include "time.h"

#define PID_MAX 32768

typedef enum {
    state_ready,
    state_executing,
    state_blocked
} process_state;

typedef struct {
    struct {
        int pid;
        int parent_pid;
        int program_counter;
        // *program_ptr
        int *data_memory_ptr;
        int priority;
        process_state state;
        time_t begin_time;
        time_t used_time;
    } data[PID_MAX+1];
    int available[PID_MAX+1];
} process_table_t;

void process_table_init(process_table_t *pt);
void process_table_destroy(process_table_t *pt);
int  process_table_add(process_table_t *pt, int parent_pid, int program_counter, int *data_memory_ptr, int priority, time_t now);
void process_table_update_process(process_table_t *pt /*, parameters */);
void process_table_get_priority(process_table_t *pt, int index);
void process_table_remove(process_table_t *pt, int index);

#endif