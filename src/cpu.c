#include "./includes/cpu.h"

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
    time_t time = cpu->time_used; // tempo atual
    process_table_add(table, pid, cpu->program_counter+1, process_table_get_program(table, pid), cpu->data_memory_ptr, process_table_get_priority(table, pid), time);

    cpu->time_used = 0;
}

void context_switch(cpu_t *cpu, executing_t *exe, ready_t *ready, blocked_t *blocked, process_table_t *table, process_state new_state, process_state old_state, scheduler sched_function) {
    int pid = executing_get(exe);
    int priority = process_table_get_priority(table, pid);

    if (old_state == state_executing && new_state == state_blocked) {
        printf("blocked\n");
        blocked_push(blocked, pid);
        priority += priority ? -1 : 0;
    } else if (old_state == state_executing && new_state == state_terminated) {
        process_table_remove(table, pid);
    } else {
        process_table_update(table, pid, cpu->program_counter, process_table_get_program(table, pid), cpu->data_memory_ptr, priority, new_state, cpu->time_used);
    }

    sched_function(cpu, ready, exe, table);
}

void  cpu_execute_next_instruction(cpu_t *cpu, executing_t *exe, ready_t *ready, blocked_t *blocked, process_table_t *table, scheduler sched_function) {
    int index, value;
    char* string;

    if (cpu->program_counter != -1) {
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

            data_init(&cpu->data_memory_ptr, value);
            cpu->program_counter++;

        } else if (inst.name == 'B') {
            cpu->program_counter++;
            context_switch(cpu, exe, ready, blocked, table, state_blocked, state_executing, sched_function);

        } else if (inst.name == 'T') {
            data_destroy(&cpu->data_memory_ptr);
            cpu->program_counter++;
            context_switch(cpu, exe, ready, blocked, table, state_terminated, state_executing, sched_function);

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

    if (cpu->time_used >= cpu->quantum) {
        context_switch(cpu, exe, ready, blocked, table, state_ready, state_executing, sched_function);
    } else {
        cpu->time_used++;  
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