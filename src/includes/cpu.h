#ifndef __CPU_H__
#define __CPU_H__

#include "data.h"
#include "program.h"
#include "ready.h"
#include "blocked.h"
#include "process_table.h"
#include "executing.h"
#include "time_unit.h"

typedef struct cpu {
    int program_counter;
    data_t data_memory_ptr;
    program_t program_ptr;
    int quantum;
    int time_used;
} cpu_t;

typedef int (*scheduler)(cpu_t *cpu, executing_t *exe, ready_t *ready, process_table_t *table, process_state state);

void   cpu_init(cpu_t *cpu, program_t program, data_t data, int program_counter, int quantum);
void   cpu_execute_next_instruction(cpu_t *cpu, executing_t *exe, ready_t *ready, blocked_t *blocked, process_table_t *table, time_unit_t *time, scheduler sched_function);
void   cpu_destroy(cpu_t *cpu);
void   cpu_update(cpu_t *cpu, data_t data_memory, int quantum, int program_counter);
int    cpu_get_program_counter(cpu_t *cpu);
int    cpu_get_time_used(cpu_t *cpu);
void   cpu_add_quantum_time(cpu_t *cpu);
void   cpu_print_to_file(cpu_t *cpu, FILE *file);
#endif
