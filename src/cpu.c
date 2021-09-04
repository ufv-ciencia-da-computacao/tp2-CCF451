#include "./includes/cpu.h"
#include "./includes/data.h"
#include "./includes/time.h"
#include "./includes/program.h"
#include "./includes/ready.h"
#include "./includes/blocked.h"
#include "./includes/process_table.h"
#include "./includes/executing.h"
#include <stdio.h>

void   cpu_init(cpu_t *cpu, program_t program, data_t data) {
    (*cpu)->time_used=0;
    (*cpu)->data_memory_ptr=data;
    (*cpu)->program_ptr = program;
    (*cpu)->program_counter = 0;
}

void create_process(cpu_t *cpu, ready_t *ready, process_table_t *table, executing_t *exe) {
    int pid = executing_get(exe);
    process_t process = process_table_get(table, pid);

    time_t time = 9999; // tempo atual
    process_table_add(table, pid, (*cpu)->program_counter, process.program, (*cpu)->data_memory_ptr, process.priority, time);

    (*cpu)->time_used = 0;
}

void  cpu_execute_next_instruction(cpu_t *cpu, executing_t *exe, ready_t *ready, blocked_t *blocked, process_table_t *table) {
    int index, value;

    instruction_t inst = (*cpu)->program_ptr.instructions[(*cpu)->program_counter];
    
    if (inst.name == 'D') {
        index = atoi(inst.parameter1);
        (*cpu)->data_memory_ptr.data[index] = 0;
        (*cpu)->program_counter++;

    } else if (inst.name == 'V') {
        index = atoi(inst.parameter1);
        value = atoi(inst.parameter2);

        (*cpu)->data_memory_ptr.data[index] = value;
        (*cpu)->program_counter++;

    } else if (inst.name == 'A') {
        index = atoi(inst.parameter1);
        value = atoi(inst.parameter2);

        (*cpu)->data_memory_ptr.data[index] += value;
        (*cpu)->program_counter++;

    } else if (inst.name == 'S') {
        index = atoi(inst.parameter1);
        value = atoi(inst.parameter2);

        (*cpu)->data_memory_ptr.data[index] -= value;
        (*cpu)->program_counter++;

    } else if (inst.name == 'N') {
        value = atoi(inst.parameter1);

        data_init(&(*cpu)->data_memory_ptr, value);
        (*cpu)->program_counter++;

    } else if (inst.name == 'B') {
        (*cpu)->program_counter++;
        cpu_context_switch(cpu, exe, ready, blocked, table, state_executing, state_blocked);

    } else if (inst.name == 'T') {
        data_destroy(&(*cpu)->data_memory_ptr);
        (*cpu)->program_counter++;
        cpu_context_switch(cpu, exe, ready, blocked, table, state_terminated, state_executing);

    } else if (inst.name=='F') {
        (*cpu)->program_counter++;
        create_process(cpu, ready, table, exe);
        
        value = atoi(inst.parameter1);
        (*cpu)->program_counter += value;
    } else if (inst.name == 'R') {
        (*cpu)->program_counter = 0;
        value = inst.parameter1;

        program_init(&((*cpu)->program_ptr), value);
        data_destroy(&(*cpu)->data_memory_ptr);
    }
}

void cpu_context_switch(cpu_t *cpu, executing_t *exe, ready_t *ready, blocked_t *blocked, process_table_t *table, process_state new_state, process_state old_state) {
    int pid = executing_get(exe);

    if (old_state == state_executing && new_state == state_blocked) {
        blocked_push(blocked, pid);
    }

    if (old_state == state_executing && new_state == state_terminated) {
        // do nothing
    }
    
    process_t process = process_table_get(table, pid);
    process_table_update(table, pid, (*cpu)->program_counter, process.program, (*cpu)->data_memory_ptr, process.priority, new_state, (*cpu)->time_used);
    
    int pid_ready = ready_top(ready);
    executing_set(exe, pid_ready);
    
    process_t process_ready = process_table_get(table, pid_ready);

    (*cpu)->data_memory_ptr = data_copy(&(process_ready.data));
    (*cpu)->program_counter = process_ready.program_counter;
    (*cpu)->time_used = process_ready.used_time;

    process_table_update(table, pid_ready, process_ready.program_counter, process_ready.program, process_ready.data, process_ready.priority, state_executing, process_ready.used_time);
    
    ready_pop(ready);
}

void   cpu_destroy(cpu_t *cpu);
void   cpu_update(cpu_t *cpu, data_t data_memory, int quantum, int program_counter) {
    (*cpu)->data_memory_ptr = data_memory;
    (*cpu)->quantum = quantum;
    (*cpu)->program_counter = program_counter;
}
int    cpu_get_program_counter(cpu_t *cpu) {
    return (*cpu)->program_counter;
}
time_t cpu_get_time_used(cpu_t *cpu) {
    return (*cpu)->time_used;
}

void cpu_add_quantum_time(cpu_t *cpu) {
    (*cpu)->time_used += (*cpu)->quantum;
}