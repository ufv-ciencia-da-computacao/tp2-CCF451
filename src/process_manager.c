#include "./includes/process_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static int get_min_time_process(ready_t *ready, process_table_t *table){
    queuePriority *q = NULL;
    int min_time = 0x3f3f3f, pid=-1;

    for(q = ready->hPriority; q ; q = q->next){
        int t = process_table_get_program(table, q->index).tam - process_table_get_program_counter(table, q->index)+1;
        if(min_time > t) min_time = t, pid = q->index;
    }

    return pid;
}

char process_manager_read_next_instruction(FILE* file) {
    FILE *f;
    char c;
    fscanf(file, "%c", &c);
    return c;
}

void process_manager_init(process_manager_t *pm, char *filename, int print_config) {
    blocked_init(&(pm->blocked_queue), QUEUE_SIZE);
    ready_init(&(pm->ready_queue));
    process_table_init(&(pm->table), TABLE_SIZE);
    executing_init(&(pm->exe));
    time_unit_init(&pm->time);
    pm->print_config = print_config;
    
    program_t program;
    program_init(&program, filename);
    data_t data;
    data_init(&data, 0);

    int pid = process_table_add(&pm->table, -1, 0, program, data, 0, 0);
    executing_set(&pm->exe, pid);

    cpu_init(&(pm->cpu), program, data, 0, 1);
}

int weird_round_robin(cpu_t *cpu, executing_t *exe, ready_t *ready, process_table_t *table, process_state state) {
    //printf("%d\n", cpu->program_ptr.tam);
    int pid = executing_get(exe);
    int pid_ready, priority;
    // printf("ready size: %d ready front: %d\n", ready_size(ready), ready_top(ready));
    if(state == state_terminated) {
        pid_ready = ready_top(ready);
        if(pid_ready != -1) ready_pop(ready);
        return pid_ready;
    } else if(state == state_blocked) {
        priority = process_table_get_priority(table, pid);
        process_table_set_priority(table, pid, (priority ? priority-1 : priority));
        pid_ready = ready_top(ready);
        if(pid_ready != -1) ready_pop(ready);
        return pid_ready;

    } else if (cpu->time_used >= cpu->quantum) {
        priority = process_table_get_priority(table, pid);
        priority = (priority < 3 ? priority+1 : priority);
        process_table_set_priority(table, pid, priority);
        ready_push(ready, pid, priority);
        
        pid_ready = ready_top(ready);
        if(pid_ready != -1) ready_pop(ready);
        return pid_ready;
    }
    return pid;
}

int sjf_sched(cpu_t *cpu, executing_t *exe, ready_t *ready, process_table_t *table, process_state state){
    int pid = executing_get(exe);

    if(cpu->program_counter >= cpu->program_ptr.tam || state == state_terminated || state == state_blocked) {
        int pid_ready = get_min_time_process(ready, table);
        if(pid_ready != -1) ready_pop(ready);
        return pid_ready;
    }
    return pid;
}

void print_system_state(process_manager_t *pm) {
    int pid = executing_get(&pm->exe);
    int priority = process_table_get_priority(&pm->table, pid);
    int quantum = pm->cpu.quantum;
    int used_quantum = pm->cpu.time_used;
    int pc = pm->cpu.program_counter;
    
    pid_t p = fork();
    if(p < 0) {
        fprintf(stderr, "Fork failed");
        exit(255);
    } else if(p > 0) {
        // parent continue execution after child exits
        wait(NULL);
    } else {
        int print_config = pm->print_config;
        int time = time_unit_get(&pm->time);
        printf("Curr time: %d\n", time);

        if(print_config & PRINT_EXECUTING_PID) {
            printf("Executing PID: %d\n", pid);
        } 

        if(print_config & PRINT_PRIORITY) {
            printf("Priority: %d\n", priority);
        }

        if(print_config & PRINT_QUANTUM) {
            printf("Quantum: %d\n", quantum);
        }

        if(print_config & PRINT_USED_QUANTUM) {
            printf("Used in Quantum: %d\n", used_quantum);
        }

        if(print_config & PRINT_PROGRAM_COUNTER) {
            printf("Program Counter: %d\n", pc);
        }

        printf("\n ------- \n\n");

        // after print, exit process
        exit(0);
    }
}

void process_manager_execute_command(process_manager_t *pm, char c, scheduler sched_function) {

    if (c == 'U') {
            // fim da unidade de tempo
        cpu_execute_next_instruction(&(pm->cpu), &(pm->exe), &(pm->ready_queue), &(pm->blocked_queue), &(pm->table), &pm->time, sched_function);

        time_unit_tick(&pm->time);
    } else if (c == 'L') {
        // desbloqueia o primeiro processo simulado na fila bloqueada
        if (!blocked_empty(&(pm->blocked_queue))) {
            int pid = blocked_front(&(pm->blocked_queue));
            int priority = process_table_get_priority(&(pm->table), pid);
            // printf("pid: %d priority: %d moved from blocked\n", pid, priority);
            blocked_pop(&(pm->blocked_queue));
            ready_push(&(pm->ready_queue), pid, priority);

            
            pid = executing_get(&pm->exe);
            if(pid == -1) {
                pid = ready_top(&pm->ready_queue);
                ready_pop(&pm->ready_queue);    
                program_t program = process_table_get_program(&pm->table, pid);
                data_t data = process_table_get_data(&pm->table, pid);
                int pc = process_table_get_program_counter(&pm->table, pid);
                int quantum = 1 << process_table_get_priority(&pm->table, pid);
                
                executing_set(&pm->exe, pid);
                cpu_init(&pm->cpu, program, data, pc, quantum);
            }
        }
    } else if (c == 'I') {
        print_system_state(pm);
    } else if (c == 'M') {
        print_system_state(pm);
        exit(0);
    }
}

void process_manager_main(process_manager_t *pm, FILE *file, scheduler sched_function) {
    char c;

    while (1) {
        c = process_manager_read_next_instruction(file);

        process_manager_execute_command(pm, c, sched_function);
    }
}
