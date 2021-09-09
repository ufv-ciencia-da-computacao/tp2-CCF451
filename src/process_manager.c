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

static int get_min_time_process(ready_t *ready, process_table_t *table){
    queuePriority *q = NULL;
    int min_time = 0x3f3f3f, pid;

    for(q = ready->hPriority; q ; q = q->next){
        int t = process_table_get_used_time(table, q->index);
        if(min_time > t) min_time = t, pid = q->index;
    }

    for(q = ready->mPriority; q ; q = q->next){
        int t = process_table_get_used_time(table, q->index);
        if(min_time > t) min_time = t, pid = q->index;
    }

    for(q = ready->lPriority; q ; q = q->next){
        int t = process_table_get_used_time(table, q->index);
        if(min_time > t) min_time = t, pid = q->index;
    }

    for(q = ready->vLPriority; q ; q = q->next){
        int t = process_table_get_used_time(table, q->index);
        if(min_time > t) min_time = t, pid = q->index;
    }

    return pid;
}

static void ready_pop_min_time(ready_t *ready, int pid){
    queuePriority *q = NULL;
    queuePriority *aux = NULL;
    int flag = 0;

    for(q = ready->hPriority; q && !flag; q = q->next){
        if(q->next->index == pid){
            flag = 1;
            break;
        }
    }

    for(q = ready->mPriority; q && !flag; q = q->next){
        if(q->next->index == pid){
            flag = 1;
            break;
        }
    }

    for(q = ready->lPriority; q && !flag; q = q->next){
        if(q->next->index == pid){
            flag = 1;
            break;
        }
    }

    for(q = ready->vLPriority; q && !flag; q = q->next){
        if(q->next->index == pid){
            flag = 1;
            break;
        }
    }

    aux = q->next;
    q->next = aux->next;
    free(aux);
}

void sjf_sched(cpu_t *cpu, ready_t *ready, executing_t *exe, process_table_t *table){
    int pid_ready = get_min_time_process(ready, table);

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

        ready_pop_min_time(ready, pid_ready);
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
