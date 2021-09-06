#include <stdio.h>
#include <stdlib.h>
#include "../../includes/cpu.h"
#include "../../includes/data.h"
#include "../../includes/program.h"

int main() {

    process_table_t table;
    program_t program;
    data_t data;
    ready_t ready_queue;
    blocked_t blocked_queue;
    executing_t exe;

    int index;

    program_init(&program, "blocked.txt");
    process_table_init(&table, 10);
    ready_init(&ready_queue);
    executing_init(&exe);
    blocked_init(&blocked_queue, 10);

    data_init(&data, 10);

    cpu_t c;
    cpu_init(&c, program, data);
    // for (int i = 0; i < program.tam; i++) {
    //     printf("%d\n", i);
    //     cpu_execute_next_instruction(&c, &exe, &ready_queue, &blocked_queue, &table);
    // }

    cpu_execute_next_instruction(&c, &exe, &ready_queue, &blocked_queue, &table);
    cpu_execute_next_instruction(&c, &exe, &ready_queue, &blocked_queue, &table);
    cpu_execute_next_instruction(&c, &exe, &ready_queue, &blocked_queue, &table);
    cpu_execute_next_instruction(&c, &exe, &ready_queue, &blocked_queue, &table);
    cpu_execute_next_instruction(&c, &exe, &ready_queue, &blocked_queue, &table);
    cpu_execute_next_instruction(&c, &exe, &ready_queue, &blocked_queue, &table);
    cpu_execute_next_instruction(&c, &exe, &ready_queue, &blocked_queue, &table);


    printf("%d\n", c.program_counter);

    // printf("%d %d %d\n", 0, table.data[0].process.data.size, data.size);

    // for (int i =0; i<2; i++) printf("%d ", c.data_memory_ptr.data[i]);
    // printf("\n");

    // printf("%d\n", c.data_memory_ptr.size);

    return 0;
}