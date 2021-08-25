#include "./includes/process_table.h"
#include <stdlib.h>

static int next_pid = 0;

void process_table_init(process_table_t *pt) {
    int i;
    for(i=0; i<=PID_MAX; ++i) {
        pt->available[i] = 1;
    }
}

void process_table_destroy(process_table_t *pt) {
    
}

int process_table_add(process_table_t *pt, int parent_pid, int program_counter, int *data_memory_ptr, int priority, time_t now) {
    /*find first available position and add this process */
    int i;
    int pid = -1;
    for(i=0; i <= PID_MAX && pid == -1; ++i, next_pid = (next_pid == PID_MAX) ? 0 : next_pid+1) {
        if(pt->available[next_pid]) {
            pt->available[next_pid] = 0;
            pt->data[next_pid].pid = next_pid;
            pt->data[next_pid].parent_pid = parent_pid;
            pt->data[next_pid].program_counter = program_counter;
            // init program memory
            pt->data[next_pid].data_memory_ptr = data_memory_ptr;
            pt->data[next_pid].priority = priority;
            pt->data[next_pid].used_time = 0;
            pt->data[next_pid].begin_time = now;
            
            pid = next_pid;
        }
    }

    return pid;
}

void process_table_update(process_table_t *pt /*, parameters */);
void process_table_get_priority(process_table_t *pt, int index);

void process_table_remove(process_table_t *pt, int index) {
    pt->available[index] = 1;
    // free(pt->data[index].data_memory_ptr);
    // free program memory ptr
}