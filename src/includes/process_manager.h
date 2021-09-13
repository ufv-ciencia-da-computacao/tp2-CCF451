#ifndef __PROCESS_MANAGER_H__
#define __PROCESS_MANAGER_H__

#include "cpu.h"
#include "data.h"
#include "program.h"

#define QUEUE_SIZE 256
#define TABLE_SIZE 512

#define PRINT_EXECUTING_PID         (1 << 0)
#define PRINT_PRIORITY              (1 << 1)
#define PRINT_QUANTUM               (1 << 2)
#define PRINT_VARIABLES             (1 << 3)
#define PRINT_PROGRAM_COUNTER       (1 << 4)
// #define PRINT_STATE                 (1 << 5)
#define PRINT_USED_CPU_TIME         (1 << 6)
#define PRINT_PARENT_PID            (1 << 7)
#define PRINT_BLOCKED               (1 << 8)
#define PRINT_READY                 (1 << 9)
#define PRINT_USED_QUANTUM          (1 << 10)

typedef struct process_manager {
    process_table_t table;
    ready_t ready_queue;
    blocked_t blocked_queue;
    executing_t exe;
    cpu_t cpu;
    time_unit_t time;

    int print_config;
} process_manager_t;

void process_manager_init(process_manager_t *pm, char *filename, int print_config);
void process_manager_main(process_manager_t *pm, FILE *file, scheduler sched_function);
int weird_round_robin(cpu_t *cpu, executing_t *exe, ready_t *ready, process_table_t *table, process_state state);
int sjf_sched(cpu_t *cpu, executing_t *exe, ready_t *ready, process_table_t *table, process_state state);
void process_manager_execute_command(process_manager_t *pm, char c, scheduler sched_function);

#endif
