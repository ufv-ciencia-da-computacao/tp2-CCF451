#ifndef __PROCESS_TABLE_H__
#define __PROCESS_TABLE_H__

#include "time.h"
#include "program.h"
#include "data.h"

typedef enum {
    state_ready,
    state_executing,
    state_blocked
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
void process_table_remove(process_table_t *pt, int index);

#endif