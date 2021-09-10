#ifndef __PROCESS_MANAGER_H__
#define __PROCESS_MANAGER_H__

#include "cpu.h"
#include "data.h"
#include "program.h"

#define QUEUE_SIZE 256
#define TABLE_SIZE 512

typedef struct process_manager {
    process_table_t table;
    ready_t ready_queue;
    blocked_t blocked_queue;
    executing_t exe;
    cpu_t cpu;
} process_manager_t;

void process_manager_init(process_manager_t *pm, char *filename);
void process_manager_main(process_manager_t *pm, FILE *file, int op_policy);
int weird_round_robin(cpu_t *cpu, executing_t *exe, ready_t *ready, process_table_t *table, process_state state);
int sjf_sched(cpu_t *cpu, executing_t *exe, ready_t *ready, process_table_t *table, process_state state);
void process_manager_execute_command(process_manager_t *pm, char c, int op_policy);

#endif
