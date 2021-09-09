#ifndef __CPU_H__
#define __CPU_H__

#include "data.h"
#include "time.h"
#include "program.h"
#include "ready.h"
#include "blocked.h"
#include "process_table.h"
#include "executing.h"

typedef struct cpu {
    // program_ptr,
    int program_counter;
    int pid;
    data_t data_memory_ptr;
    program_t program_ptr;
    time quantum;
    time time_used;
} cpu_t;

typedef void(*scheduler)(cpu_t *cpu, ready_t *ready, executing_t *exe, process_table_t *table);

void   cpu_init(cpu_t *cpu, program_t program, data_t data, int program_counter, int priority);
void   cpu_execute_next_instruction(cpu_t *cpu, executing_t *exe, ready_t *ready, blocked_t *blocked, process_table_t *table, scheduler sched_function);
void   cpu_destroy(cpu_t *cpu);
void   cpu_update(cpu_t *cpu, data_t data_memory, int quantum, int program_counter);
int    cpu_get_program_counter(cpu_t *cpu);
time_t cpu_get_time_used(cpu_t *cpu);
void   cpu_add_quantum_time(cpu_t *cpu);
void   weird_round_robin(cpu_t *cpu, ready_t *ready, executing_t *exe, process_table_t *table);
void cpu_print_to_file(cpu_t *cpu,FILE *file);
#endif
