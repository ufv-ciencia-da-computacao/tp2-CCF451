#include "./includes/cpu.h"

#include <stdio.h>
#include <stdlib.h>

void   cpu_init(cpu_t *cpu, program_t program, data_t data) {
    cpu->time_used=0;
    cpu->data_memory_ptr = data_copy(&data);
    cpu->program_ptr = program_copy(&program);
    cpu->program_counter = 0;
}

void create_process(cpu_t *cpu, ready_t *ready, process_table_t *table, executing_t *exe) {
    int pid = executing_get(exe);
    time_t time = 9999; // tempo atual
    process_table_add(table, pid, cpu->program_counter+1, process_table_get_program(table, pid), cpu->data_memory_ptr, process_table_get_priority(table, pid), time);

    cpu->time_used = 0;
}

void  cpu_execute_next_instruction(cpu_t *cpu, executing_t *exe, ready_t *ready, blocked_t *blocked, process_table_t *table) {
    int index, value;
    char* string;

    if (cpu->program_counter != -1) {
        instruction_t inst = cpu->program_ptr.instructions[cpu->program_counter];
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

            data_init(&cpu->data_memory_ptr, value);
            cpu->program_counter++;

        } else if (inst.name == 'B') {
            cpu->program_counter++;
            cpu_context_switch(cpu, exe, ready, blocked, table, state_blocked, state_executing);

        } else if (inst.name == 'T') {
            data_destroy(&cpu->data_memory_ptr);
            cpu->program_counter++;
            cpu_context_switch(cpu, exe, ready, blocked, table, state_terminated, state_executing);

        } else if (inst.name=='F') {
            create_process(cpu, ready, table, exe);

            value = atoi(inst.parameter1);
            cpu->program_counter += value;
        } else if (inst.name == 'R') {
            cpu->program_counter = 0;
            string = inst.parameter1;

            program_init(&(cpu->program_ptr), string);
        }
    }
}

void cpu_context_switch(cpu_t *cpu, executing_t *exe, ready_t *ready, blocked_t *blocked, process_table_t *table, process_state new_state, process_state old_state) {
    int pid = executing_get(exe);

    if (old_state == state_executing && new_state == state_blocked) {
        printf("blocked\n");
        blocked_push(blocked, pid);
    }

    if (old_state == state_executing && new_state == state_terminated) {
        // do nothing
    }
    
    process_table_update(table, pid, cpu->program_counter, process_table_get_program(table, pid), cpu->data_memory_ptr, process_table_get_priority(table, pid), new_state, cpu->time_used);
    
    int pid_ready = ready_top(ready);
    
    if (pid_ready==-1) {
        executing_destroy(exe);  
        cpu->program_counter = -1;
    } else {
        executing_set(exe, pid_ready);
    
        cpu->data_memory_ptr = process_table_get_data(table, pid_ready);
        cpu->program_counter = process_table_get_program_counter(table, pid_ready);
        cpu->time_used = process_table_get_used_time(table, pid_ready);

        process_table_update(table, pid_ready, process_table_get_program_counter(table, pid_ready), process_table_get_program(table, pid_ready), process_table_get_data(table, pid_ready), process_table_get_priority(table, pid_ready), state_executing, process_table_get_used_time(table, pid_ready));

        ready_pop(ready);
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
time_t cpu_get_time_used(cpu_t *cpu) {
    return cpu->time_used;
}

void cpu_add_quantum_time(cpu_t *cpu) {
    cpu->time_used += cpu->quantum;
}