#include <stdio.h>
#include <stdlib.h>
#include "../../includes/cpu.h"
#include "../../includes/data.h"
#include "../../includes/program.h"
#include "../../includes/process_manager.h"

int main() {

    process_table_t table;
    program_t program;
    data_t data;
    ready_t ready_queue;
    blocked_t blocked_queue;
    executing_t exe;

    int index;

    program_init(&program, "file1.txt");
    process_table_init(&table, 10);
    int pid = process_table_add(&table, -1, 0, program, data, 0, 0);
    ready_init(&ready_queue);
    executing_init(&exe);
    blocked_init(&blocked_queue, 10);

    data_init(&data, 10);

    cpu_t c;
    cpu_init(&c, program, data, 0, 0);
    executing_set(&exe, pid);
    for (int i = 0; i < 100; i++) {
       //  printf("%d %d %d\n", i, process_table_get_priority(&table, pid), executing_get(&exe));
        cpu_execute_next_instruction(&c, &exe, &ready_queue, &blocked_queue, &table, weird_round_robin);
    }
    //printf("%d\n", executing_get(&exe));
    // cpu_execute_next_instruction(&c, &exe, &ready_queue, &blocked_queue, &table, sjf_sched);
    // cpu_execute_next_instruction(&c, &exe, &ready_queue, &blocked_queue, &table, sjf_sched);
    // cpu_execute_next_instruction(&c, &exe, &ready_queue, &blocked_queue, &table, sjf_sched);
    // cpu_execute_next_instruction(&c, &exe, &ready_queue, &blocked_queue, &table, sjf_sched);
    // cpu_execute_next_instruction(&c, &exe, &ready_queue, &blocked_queue, &table, sjf_sched);
    // cpu_execute_next_instruction(&c, &exe, &ready_queue, &blocked_queue, &table, sjf_sched);
    // cpu_execute_next_instruction(&c, &exe, &ready_queue, &blocked_queue, &table, );


    // printf("%d\n", c.program_counter);
    // //
    // printf("%d %d %d\n", 0, table.data[0].process.data.size, data.size);
    // //
    // for (int i =0; i<2; i++) printf("%d ", c.data_memory_ptr.data[i]);
    // printf("\n");
    // //
    // printf("%d\n", c.data_memory_ptr.size);

    process_table_destroy(&table);
    blocked_destroy(&blocked_queue);
    ready_destroy(&ready_queue);
    executing_destroy(&exe);


    return 0;
}
