#include "./includes/process_table.h"
#include "./time.h"
#include <stdlib.h>

struct process_table {
    struct {
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
    (*pt)->list = malloc(size * sizeof(*(*pt)->list));
    for(i=0; i<size; ++i) {
        (*pt)->list[i].program_counter = 0;
        (*pt)->list[i].pid = -1;
        /* initialize all values */
    }
}

void process_table_destroy(process_table_t *pt) {
    free((*pt)->list);
    free(*pt);
    *pt = NULL;
}



// void process_table_ SOMETHING