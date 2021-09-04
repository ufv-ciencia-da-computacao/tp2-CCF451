#include "./includes/process_table.h"
#include <stdlib.h>

void process_table_init(process_table_t *pt, int size) {
    pt->data = malloc(size * sizeof(*pt->data));
    pt->size = size;
    pt->next_index = 0;
    int i;
    for(i=0; i<pt->size; ++i) {
        pt->data[i].available = 1;
    }
}

void process_table_destroy(process_table_t *pt) {
    int i;
    for(i=0; i<pt->size; ++i) {
        program_destroy(&pt->data[i].process.program);
        data_destroy(&pt->data[i].process.data);
    }
    free(pt->data);
    pt->data = NULL;
    pt->size = 0;
}

int process_table_add(process_table_t *pt, int parent_pid, int program_counter, program_t program, data_t data, int priority, time_t begin_time) {
    /*find first available position and add this process */
    int i;
    int index = -1;
    for(i=0; i < pt->size && index == -1; ++i, pt->next_index = (pt->next_index == pt->size-1) ? 0 : pt->next_index+1) {
        if(pt->data[pt->next_index].available) {
            index = pt->next_index;
            pt->data[index].available = 0;
            pt->data[index].process.pid = index;
            pt->data[index].process.parent_pid = parent_pid;
            pt->data[index].process.program_counter = program_counter;
            pt->data[index].process.program = program;
            pt->data[index].process.data = data;
            pt->data[index].process.priority = priority;
            pt->data[index].process.state = state_ready;
            pt->data[index].process.begin_time = begin_time;
            pt->data[index].process.used_time = 0;
        }
    }

    return index;
}

void process_table_update(process_table_t *pt, int index, int program_counter, program_t program, data_t data, int priority, process_state state, time_t used_time) {
    pt->data[index].process.program_counter = program_counter;
    program_destroy(&pt->data[index].process.program);
    pt->data[index].process.program = program_copy(&program);
    data_copy(&pt->data[index].process.data, data);
    pt->data[index].process.priority = priority;
    pt->data[index].process.state = state;
    pt->data[index].process.used_time = used_time;
}

void process_table_remove(process_table_t *pt, int index) {
    pt->data[index].available = 1;
    data_destroy(&pt->data[index].process.data);
    program_destroy(&pt->data[index].process.program);
}


int process_table_get_parent_pid(process_table_t *pt, int index) {
    return pt->data[index].process.pid;
}

int process_table_get_program_counter(process_table_t *pt, int index) {
    return pt->data[index].process.program_counter;
}

program_t process_table_get_program(process_table_t *pt, int index) {
    return pt->data[index].process.program;
}

data_t process_table_get_data(process_table_t *pt, int index) {
    return pt->data[index].process.data;
}

int process_table_get_priority(process_table_t *pt, int index) {
    return pt->data[index].process.priority;
}

process_state process_table_get_state(process_table_t *pt, int index) {
    return pt->data[index].process.state;
}

time_t process_table_get_begin_time(process_table_t *pt, int index) {
    return pt->data[index].process.begin_time;
}

time_t process_table_get_used_time(process_table_t *pt, int index) {
    return pt->data[index].process.used_time;
}