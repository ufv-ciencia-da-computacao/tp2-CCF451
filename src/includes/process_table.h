#ifndef __PROCESS_TABLE_H__
#define __PROCESS_TABLE_H__

#include "time.h"
#include "program.h"
#include "data.h"
#include "time.h"

typedef enum {
    state_ready,
    state_executing,
    state_blocked,
    state_terminated,
} process_state;

typedef struct {
    struct {
        struct {
            int pid;
            int parent_pid;
            int program_counter;
            program_t program;
            data_t data;
            int priority;
            process_state state;
            time_t begin_time;
            time_t used_time;
        } process;
        int available;
    } *data;
    int size;
    int next_index;
} process_table_t;

void process_table_init(process_table_t *pt, int size);
void process_table_destroy(process_table_t *pt);
int process_table_add(process_table_t *pt, int parent_pid, int program_counter, program_t program, data_t data, int priority, time_t begin_time);
void process_table_update(process_table_t *pt, int index, int program_counter, program_t program, data_t data, int priority, process_state state, time_t used_time);
void process_table_update_2(process_table_t *pt, int index, int priority, process_state state);
void process_table_remove(process_table_t *pt, int index);

void process_table_set_program_counter(process_table_t *pt, int index, int program_counter);
void process_table_set_program(process_table_t *pt, int index, program_t program);
void process_table_set_data(process_table_t *pt, int index, data_t data);
void process_table_set_priority(process_table_t *pt, int index, int priority);
void process_table_set_begin_time(process_table_t *pt, int index, time_t begin_time);
void process_table_set_used_time(process_table_t *pt, int index, time_t used_time);
void process_table_set_state(process_table_t *pt, int index, process_state state);
void process_table_set_parent_pid(process_table_t *pt, int index, int parent_pid);

int process_table_get_parent_pid(process_table_t *pt, int index);
int process_table_get_program_counter(process_table_t *pt, int index);
program_t process_table_get_program(process_table_t *pt, int index);
data_t process_table_get_data(process_table_t *pt, int index);
int process_table_get_priority(process_table_t *pt, int index);
process_state process_table_get_state(process_table_t *pt, int index);
time_t process_table_get_begin_time(process_table_t *pt, int index);
time_t process_table_get_used_time(process_table_t *pt, int index);

void process_table_print_to_file(process_table_t *pt, FILE *file);

#endif