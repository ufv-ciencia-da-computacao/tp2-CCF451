#ifndef __CPU_H__
#define __CPU_H__

typedef struct cpu * cpu_t;

struct cpu {
    // program_ptr,
    int program_counter;
    int pid;
    data_t data_memory_ptr;
    program_t program_ptr;
    time_t quantum;
    time_t time_used;
};

#include "./includes/cpu.h"
#include "./includes/data.h"
#include "./includes/time.h"
#include "./includes/program.h"
#include "./includes/ready.h"
#include "./includes/blocked.h"
#include "./includes/process_table.h"
#include "./includes/executing.h"
#include <stdio.h>

void   cpu_init(cpu_t *cpu, program_t program, data_t data);
void   cpu_execute_next_instruction(cpu_t *cpu, executing_t *exe, ready_t *ready, blocked_t *blocked, process_table_t *table);
void   cpu_context_switch(cpu_t *cpu, executing_t *exe, ready_t *ready, blocked_t *blocked, process_table_t *table, process_state new_state, process_state old_state);
void   cpu_destroy(cpu_t *cpu);
void   cpu_update(cpu_t *cpu, data_t data_memory, int quantum, int program_counter);
int    cpu_get_program_counter(cpu_t *cpu);
time_t cpu_get_time_used(cpu_t *cpu);
void   cpu_add_quantum_time(cpu_t *cpu);
#endif