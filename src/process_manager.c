#include "./includes/process_manager.h"

char process_manager_read_next_instruction(FILE* file) {
    FILE *f;
    char c;
    fscanf(file, "%c", c);
    return c; 
}

void process_manager_init(process_manager_t *pm, char *filename) {
    blocked_init(&(pm->blocked_queue), QUEUE_SIZE);
    ready_init(&(pm->ready_queue));
    process_table_init(&(pm->table), TABLE_SIZE);
    executing_init(&(pm->exe));

    program_t program;
    program_init(&program, filename);
    data_t data;
    data_init(&data, 10);

    cpu_init(&(pm->cpu), program, data, 0, 0);
}

void weird_round_robin(cpu_t *cpu, ready_t *ready, executing_t *exe, process_table_t *table) {
    int pid_ready = ready_top(ready);
    
    if (pid_ready==-1) {
        executing_destroy(exe);  
        cpu->program_counter = -1;
    } else {
        executing_set(exe, pid_ready);
        data_t data = process_table_get_data(table, pid_ready);
        program_t program = process_table_get_program(table, pid_ready);
        int time_used = process_table_get_used_time(table, pid_ready);
        int program_counter = process_table_get_program_counter(table, pid_ready);
        int priority = process_table_get_priority(table, pid_ready);

        cpu_init(cpu, program, data, program_counter, priority);

        process_table_update(table, pid_ready, program_counter, program, data, priority, state_executing, time_used);

        ready_pop(ready);
    }
}

void process_manager_main(process_manager_t *pm, FILE *file) {
    char c;
    
    while (1) {
        c = process_manager_read_next_instruction(file);

        if (c == 'U') {
            // fim da unidade de tempo
            cpu_execute_next_instruction(&(pm->cpu), &(pm->exe), &(pm->ready_queue), &(pm->blocked_queue), &(pm->table), weird_round_robin);
        } else if (c == 'L') {
            // desbloqueia o primeiro processo simulado na fila bloqueada
            if (!blocked_empty(&(pm->blocked_queue))) {
                int pid = blocked_front(&(pm->blocked_queue));
                blocked_pop(&(pm->blocked_queue));
                ready_push(&(pm->ready_queue), pid, process_table_get_priority(&(pm->table), pid));  
            }
        } else if (c == 'I') {
            // imprime estado atual do sistema
        } else if (c == 'M') {
            // acaba
        } 
    } 
}