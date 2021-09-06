#ifndef __PROCESS_TABLE_H__
#define __PROCESS_TABLE_H__

#include "time.h"
#include "program.h"
#include "data.h"

typedef enum {
    state_ready,
    state_executing,
    state_blocked,
    state_terminated,
} process_state;

typedef struct {
    int pid;
    int parent_pid;
    int program_counter;
    program_t program;
    data_t data;
    int priority;
    process_state state;
    time begin_time;
    time used_time;
} process_t;

typedef struct {
    struct {
        process_t process;
        int available;
    } *data;
    int size;
    int next_index;
} process_table_t;

void process_table_init(process_table_t *pt, int size);
void process_table_destroy(process_table_t *pt);
int process_table_add(process_table_t *pt, int parent_pid, int program_counter, program_t program, data_t data, int priority, time begin_time);
void process_table_update(process_table_t *pt, int index, int program_counter, program_t program, data_t data, int priority, process_state state, time used_time);
void process_table_remove(process_table_t *pt, int index);

int process_table_get_parent_pid(process_table_t *pt, int index);
int process_table_get_program_counter(process_table_t *pt, int index);
program_t process_table_get_program(process_table_t *pt, int index);
data_t process_table_get_data(process_table_t *pt, int index);
int process_table_get_priority(process_table_t *pt, int index);
process_state process_table_get_state(process_table_t *pt, int index);
time process_table_get_begin_time(process_table_t *pt, int index);
time process_table_get_used_time(process_table_t *pt, int index);

#endif