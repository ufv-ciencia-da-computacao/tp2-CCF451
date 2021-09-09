#include "./includes/process_table.h"
#include <stdlib.h>
#include <stdio.h>

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
        if(!pt->data[i].available) {
            program_destroy(&pt->data[i].process.program);
            data_destroy(&pt->data[i].process.data);
        }
    }
    free(pt->data);
    pt->data = NULL;
    pt->size = 0;
}

int process_table_add(process_table_t *pt, int parent_pid, int program_counter, program_t program, data_t data, int priority, int begin_time) {
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

void process_table_update(process_table_t *pt, int index, int program_counter, program_t program, data_t data, int priority, process_state state, int used_time) {
    pt->data[index].process.program_counter = program_counter;
    pt->data[index].process.program = program;
    pt->data[index].process.data = data;
    pt->data[index].process.priority = priority;
    pt->data[index].process.state = state;
    pt->data[index].process.used_time = used_time;
}

void process_table_remove(process_table_t *pt, int index) {
    pt->data[index].available = 1;
    data_destroy(&pt->data[index].process.data);
    program_destroy(&pt->data[index].process.program);
}

void process_table_set_program_counter(process_table_t *pt, int index, int program_counter) {
    pt->data[index].process.program_counter = program_counter;
}

void process_table_set_program(process_table_t *pt, int index, program_t program) {
    pt->data[index].process.program = program;
}

void process_table_set_data(process_table_t *pt, int index, data_t data) {
    pt->data[index].process.data = data;
}

void process_table_set_priority(process_table_t *pt, int index, int priority) {
    pt->data[index].process.priority = priority;
}

void process_table_set_begin_time(process_table_t *pt, int index, int begin_time) {
    pt->data[index].process.begin_time = begin_time;
}

void process_table_set_used_time(process_table_t *pt, int index, int used_time) {
    pt->data[index].process.used_time = used_time;
}

void process_table_set_state(process_table_t *pt, int index, process_state state) {
    pt->data[index].process.state = state;
}

void process_table_set_parent_pid(process_table_t *pt, int index, int parent_pid) {
    pt->data[index].process.parent_pid = parent_pid;
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

int process_table_get_begin_time(process_table_t *pt, int index) {
    return pt->data[index].process.begin_time;
}

int process_table_get_used_time(process_table_t *pt, int index) {
    return pt->data[index].process.used_time;
}

void process_table_print_to_file(process_table_t *pt, FILE *file) {
    int i;
    fprintf(file, "PID\tPARENT PID\tPROGRAM COUNTER\tDATA ARRAY\tPRIORITY\tSTATE\tBEGIN TIME\tUSED TIME\n");
    char str_state[20];
    int pid, par_pid, pc, priority, begin, used;
    for(i=0; i<pt->size; ++i) {
        if(!pt->data[i].available) {
            pid = pt->data[i].process.pid;
            par_pid = pt->data[i].process.parent_pid;
            pc = pt->data[i].process.program_counter;
            priority = pt->data[i].process.priority;
            begin = pt->data[i].process.begin_time;
            used = pt->data[i].process.used_time;
            if(pt->data[i].process.state == state_blocked) sprintf(str_state, "blocked");
            else if(pt->data[i].process.state == state_executing) sprintf(str_state, "executing");
            else if(pt->data[i].process.state == state_ready) sprintf(str_state, "ready");
            else if(pt->data[i].process.state == state_terminated) sprintf(str_state, "terminated");
            fprintf(file, "%d\t%d\t%d\t", pid, par_pid, pc);
            data_print_to_file(&pt->data[i].process.data, file);
            fprintf(file, "\t%d\t%s\t%d\t%d\n", priority, str_state, begin, used);
        }
    }
}
