#include "./includes/cpu.h"
#include "./includes/data.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void   cpu_init(cpu_t *cpu, program_t program, data_t data, int program_counter, int quantum) {
    cpu->time_used=0;
    cpu->data_memory_ptr = data;
    cpu->program_ptr = program;
    cpu->program_counter = program_counter;
    cpu->quantum = quantum;
}

void create_process(cpu_t *cpu, ready_t *ready, process_table_t *table, executing_t *exe, time_unit_t *time) {
    int pid = executing_get(exe);
    int priority = process_table_get_priority(table, pid);
    data_t d_copy = data_copy(&cpu->data_memory_ptr);
    program_t p_copy = program_copy(&cpu->program_ptr);
    int t = time_unit_get(time);
    int new_pid = process_table_add(table, pid, cpu->program_counter+1, p_copy, d_copy, priority, t);
    ready_push(ready, new_pid, priority);
}

void context_switch(cpu_t *cpu, executing_t *exe, process_table_t *table, process_state new_state, int pid_sched) {

    if(new_state != state_terminated) {
        int pid = executing_get(exe);
        int priority = process_table_get_priority(table, pid);
        int curr_time = process_table_get_used_time(table, pid);
        process_table_update(table, pid, cpu->program_counter, cpu->program_ptr, cpu->data_memory_ptr, priority, new_state, curr_time + cpu->time_used);
    }

    if (pid_sched==-1) {
        executing_destroy(exe);
        cpu->program_counter=-1;
    } else {
        executing_set(exe, pid_sched);
        data_t data = process_table_get_data(table, pid_sched);
        program_t program = process_table_get_program(table, pid_sched);
        int program_counter = process_table_get_program_counter(table, pid_sched);
        int priority = process_table_get_priority(table, pid_sched);

        cpu_init(cpu, program, data, program_counter, 1 << priority);
        process_table_set_state(table, pid_sched, state_executing);
    }
}

void  cpu_execute_next_instruction(cpu_t *cpu, executing_t *exe, ready_t *ready, blocked_t *blocked, process_table_t *table, time_unit_t *time, scheduler sched_function) {
    int index, value, pid;
    process_state curr_state = state_executing;
    if (cpu->program_counter != -1) {
        // printf("program counter: %d\n", cpu->program_counter);
        pid = executing_get(exe);
        int priority = process_table_get_priority(table, pid);
        instruction_t inst = program_get(&(cpu->program_ptr), cpu->program_counter);

        if (inst.name == 'D') {
            index = atoi(inst.parameter1);
            cpu->data_memory_ptr.data[index] = 0;
            cpu->program_counter++;

        } else if (inst.name == 'V') {
            index = atoi(inst.parameter1);
            value = atoi(inst.parameter2);
            cpu->data_memory_ptr.data[index] = value;
            cpu->program_counter++;
            
        } else if (inst.name == 'A') {
            index = atoi(inst.parameter1);
            value = atoi(inst.parameter2);
            cpu->data_memory_ptr.data[index] += value;
            cpu->program_counter++;

        } else if (inst.name == 'S') {
            index = atoi(inst.parameter1);
            value = atoi(inst.parameter2);
            cpu->data_memory_ptr.data[index] -= value;
            cpu->program_counter++;

        } else if (inst.name == 'N') {
            value = atoi(inst.parameter1);
            data_destroy(&cpu->data_memory_ptr);
            data_init(&cpu->data_memory_ptr, value);
            cpu->program_counter++;

        } else if (inst.name == 'B') {
            blocked_push(blocked, pid);
            curr_state = state_blocked;
            cpu->program_counter++;
            // int pid_sched = sched_function(cpu, exe, ready, table, state_blocked);
            // context_switch(cpu, exe, table, state_blocked, pid_sched);

        } else if (inst.name == 'T') {
            data_destroy(&cpu->data_memory_ptr);
            program_destroy(&cpu->program_ptr);
            process_table_remove(table, pid);
            curr_state = state_terminated;
            // int pid_sched = sched_function(cpu, exe, ready, table, state_terminated);
            // context_switch(cpu, exe, table, state_terminated, pid_sched);

        } else if (inst.name=='F') {
            create_process(cpu, ready, table, exe, time);
            value = atoi(inst.parameter1);
            // printf("this fork shoud have parameter 1. got %d\n", value);
            cpu->program_counter += value + 1;

        } else if (inst.name == 'R') {
            program_destroy(&cpu->program_ptr);
            program_init(&(cpu->program_ptr), inst.parameter1);
            cpu->program_counter = 0;
        } else {
            fprintf(stderr, "this is a invalid instruction: %d, %s, %s.\n", inst.name, inst.parameter1, inst.parameter2);
            assert(0);
        }
        cpu->time_used++;
        
        int pid_sched = sched_function(cpu, exe, ready, table, curr_state);
        // printf("executing: %d\n", pid);
        // printf("scheduled: %d\n", pid_sched);
        // printf("priority: %d\n", priority);
        // printf("instruction: %c\n", inst.name);
        // printf("program size: %d\n", cpu->program_ptr.tam);

        // printf("---------\n");

        if (pid_sched != pid) {
            context_switch(cpu, exe, table, curr_state, pid_sched);
        }
    }
}

void   cpu_destroy(cpu_t *cpu);
void   cpu_update(cpu_t *cpu, data_t data_memory, int quantum, int program_counter) {
    cpu->data_memory_ptr = data_memory;
    cpu->quantum = quantum;
    cpu->program_counter = program_counter;
}
int    cpu_get_program_counter(cpu_t *cpu) {
    return cpu->program_counter;
}
int cpu_get_time_used(cpu_t *cpu) {
    return cpu->time_used;
}

void cpu_add_quantum_time(cpu_t *cpu) {
    cpu->time_used += cpu->quantum;
}

void cpu_print_to_file(cpu_t *cpu,FILE *file){
  char str[100000];
  data_print_to_string(&cpu->data_memory_ptr,str);
  fprintf(file, "PROGRAM COUNTER \t DATA MEMORY \t TIME USED \t QUANTUM\n");
  fprintf(file, "%d \t %s \t %d \t %d",
  cpu->program_counter,
  str,
  cpu->time_used,
  cpu->quantum);
}
