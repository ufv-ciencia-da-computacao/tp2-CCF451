#include "./includes/process_manager.h"

static int get_min_time_process(ready_t *ready, process_table_t *table){
    queuePriority *q = NULL;
    int min_time = 0x3f3f3f, pid;

    for(q = ready->hPriority; q ; q = q->next){
        int t = process_table_get_program(table, q->index).tam - process_table_get_program_counter(table, q->index);
        if(min_time > t) min_time = t, pid = q->index;
    }

    for(q = ready->mPriority; q ; q = q->next){
        int t = process_table_get_program(table, q->index).tam - process_table_get_program_counter(table, q->index);
        if(min_time > t) min_time = t, pid = q->index;
    }

    for(q = ready->lPriority; q ; q = q->next){
        int t = process_table_get_program(table, q->index).tam - process_table_get_program_counter(table, q->index);
        if(min_time > t) min_time = t, pid = q->index;
    }

    for(q = ready->vLPriority; q ; q = q->next){
        int t = process_table_get_program(table, q->index).tam - process_table_get_program_counter(table, q->index);
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

char process_manager_read_next_instruction(FILE* file) {
    FILE *f;
    char c;
    fscanf(file, "%c", &c);
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

int weird_round_robin(cpu_t *cpu, executing_t *exe, ready_t *ready, process_table_t *table, process_state state) {
    //printf("%d\n", cpu->program_ptr.tam);
    int priority = process_table_get_priority(table, executing_get(exe));
    if (cpu->time_used >= cpu->quantum) {
        process_table_set_priority(table, executing_get(exe), (priority < 3 ? priority+1 : priority));
        int pid_ready = ready_top(ready);
        if(pid_ready != -1) ready_pop(ready);
        return pid_ready;
    }
    if(state == state_blocked) process_table_set_priority(table, executing_get(exe), (priority? priority-1 : priority));
    return executing_get(exe);
}

int sjf_sched(cpu_t *cpu, executing_t *exe, ready_t *ready, process_table_t *table, process_state state){
    // printf("%d\n", cpu->program_ptr.tam);
    if(cpu->program_counter >= cpu->program_ptr.tam) {
        int pid_ready = get_min_time_process(ready, table);
        if(pid_ready != -1) ready_pop_min_time(ready, pid_ready);

        return pid_ready;
        return -1;
    }
    return executing_get(exe);
}

void process_manager_main(process_manager_t *pm, FILE *file, int op_policy) {
    char c;

    scheduler sched_function = op_policy ? weird_round_robin : sjf_sched;

    while (1) {
        c = process_manager_read_next_instruction(file);

        if (c == 'U') {
            // fim da unidade de tempo
            cpu_execute_next_instruction(&(pm->cpu), &(pm->exe), &(pm->ready_queue), &(pm->blocked_queue), &(pm->table), sched_function);
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
