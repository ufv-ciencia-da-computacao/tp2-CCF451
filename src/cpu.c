#include "./includes/cpu.h"
#include "./includes/data.h"

#include <stdio.h>
#include <stdlib.h>

void   cpu_init(cpu_t *cpu, program_t program, data_t data, int program_counter, int priority) {
    cpu->time_used=0;
    cpu->data_memory_ptr = data_copy(&data);
    cpu->program_ptr = program_copy(&program);
    cpu->program_counter = 0;
    cpu->quantum = 1 << priority;
}

void create_process(cpu_t *cpu, ready_t *ready, process_table_t *table, executing_t *exe) {
    int pid = executing_get(exe);
    int time = cpu->time_used; // tempo atual
    process_table_add(table, pid, cpu->program_counter+1, process_table_get_program(table, pid), cpu->data_memory_ptr, process_table_get_priority(table, pid), time);

    cpu->time_used = 0;
}

void context_switch(cpu_t *cpu, executing_t *exe, process_table_t *table, process_state new_state, int pid_sched) {
    int pid = executing_get(exe);
    int priority = process_table_get_priority(table, pid);

    process_table_update(table, pid, cpu->program_counter, process_table_get_program(table, pid), cpu->data_memory_ptr, priority, new_state, cpu->time_used);

    if (pid_sched==-1) {
        executing_destroy(exe);
        cpu->program_counter=-1;
    } else {
        executing_set(exe, pid_sched);
        data_t data = process_table_get_data(table, pid_sched);
        program_t program = process_table_get_program(table, pid_sched);
        int time_used = process_table_get_used_time(table, pid_sched);
        int program_counter = process_table_get_program_counter(table, pid_sched);
        int priority = process_table_get_priority(table, pid_sched);

        cpu_init(cpu, program, data, program_counter, priority);
        process_table_update(table, pid_sched, program_counter, program, data, priority, state_executing, time_used);
    }
}

void  cpu_execute_next_instruction(cpu_t *cpu, executing_t *exe, ready_t *ready, blocked_t *blocked, process_table_t *table, scheduler sched_function) {
    int index, value;
    char* string;
    //printf("%d\n", executing_get(exe));
    if (cpu->program_counter != -1) {
        int pid = executing_get(exe);
        instruction_t inst = program_get(&(cpu->program_ptr), cpu->program_counter);
        cpu->program_counter++;
        cpu->time_used++;

        if (inst.name == 'D') {
            index = atoi(inst.parameter1);
            cpu->data_memory_ptr.data[index] = 0;

        } else if (inst.name == 'V') {
            index = atoi(inst.parameter1);
            value = atoi(inst.parameter2);
            cpu->data_memory_ptr.data[index] = value;

        } else if (inst.name == 'A') {
            index = atoi(inst.parameter1);
            value = atoi(inst.parameter2);
            cpu->data_memory_ptr.data[index] += value;

        } else if (inst.name == 'S') {
            index = atoi(inst.parameter1);
            value = atoi(inst.parameter2);
            cpu->data_memory_ptr.data[index] -= value;

        } else if (inst.name == 'N') {
            value = atoi(inst.parameter1);
            data_init(&cpu->data_memory_ptr, value);

        } else if (inst.name == 'B') {
            int pid = executing_get(exe);
            blocked_push(blocked, pid);
            int pid_sched = sched_function(cpu, exe, ready, table, state_blocked);
            context_switch(cpu, exe, table, state_blocked, pid_sched);
        } else if (inst.name == 'T') {
            data_destroy(&cpu->data_memory_ptr);
            int pid_sched = sched_function(cpu, exe, ready, table, state_terminated);
            context_switch(cpu, exe, table, state_terminated, pid_sched);
            process_table_remove(table, pid);
        } else if (inst.name=='F') {
            create_process(cpu, ready, table, exe);
            value = atoi(inst.parameter1);
            cpu->program_counter += value-1;
        } else if (inst.name == 'R') {
            cpu->program_counter = 0;
            string = inst.parameter1;
            program_init(&(cpu->program_ptr), string);
        }

        int pid_sched = sched_function(cpu, exe, ready, table, state_executing);

        if (pid_sched != pid && pid_sched != -1) {
            context_switch(cpu, exe, table, state_ready, pid_sched);
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
