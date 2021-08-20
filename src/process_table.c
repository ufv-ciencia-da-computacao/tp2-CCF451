#include "./includes/process_table.h"
#include <stdlib.h>

static int next_id = 0;

struct process_table {
    struct {
        int available;
        int pid;
        int parent_pid;
        int program_counter;
        int *data_memory_ptr;
        int priority;
        process_state state;
        time_t begin_time;
        time_t used_time;
    } *list;
    int size;
};

void process_table_init(process_table_t *pt, int size) {
    int i;
    (*pt) = malloc(sizeof **pt);
    (*pt)->size = size;
    (*pt)->list = malloc(size * sizeof *(*pt)->list);
    for(i=0; i<size; ++i) {
        (*pt)->list[i].program_counter = 0;
        (*pt)->list[i].pid = -1;
        (*pt)->list[i].available = 1;
        /* initialize all values */
    }
}

void process_table_destroy(process_table_t *pt) {
    free((*pt)->list);
    free(*pt);
    *pt = NULL;
}

int process_table_add(process_table_t *pt, int parent_pid, int program_counter, int *data_memory_ptr, int priority, time_t now) {
    /*find first available position and add this process */
    int pos;
    for(pos=0; pos < (*pt)->size; ++pos) if((*pt)->list[pos].available) break;
    if(pos == (*pt)->size) {/* handle this error */}

    (*pt)->list[pos].available = 0;
    (*pt)->list[pos].pid = next_id++;
    (*pt)->list[pos].parent_pid = parent_pid;
    (*pt)->list[pos].program_counter = program_counter;
    (*pt)->list[pos].data_memory_ptr = data_memory_ptr;
    (*pt)->list[pos].priority = priority;
    (*pt)->list[pos].state = state_ready;
    (*pt)->list[pos].begin_time = now;
    (*pt)->list[pos].used_time = 0;

    return pos;
}

void process_table_update(process_table_t *pt /*, parameters */);
void process_table_get_priority(process_table_t *pt, int index);

void process_table_remove(process_table_t *pt, int index) {
    (*pt)->list[index].available = 1;
}