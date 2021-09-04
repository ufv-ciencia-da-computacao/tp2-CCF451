/*
    UPDATE

    As you can see, retured data from get is still valid even after an update, that is because get return a copy of the data inside the process table.
    Be carefull, after using get, YOU HAVE to take care of allocated memory.
*/

#include <stdio.h>
#include <stdlib.h>
#include "../../includes/process_table.h"

int main() {

    int N = 10;

    process_table_t pt;
    process_table_init(&pt, N);

    program_t program;
    data_t data, prev_data;
    int index;

    program_init(&program, "init.txt");
    data_init(&data, 5);
    index = process_table_add(&pt, -1, 0, program, data, 0, 0);
    data_destroy(&data);
    program_destroy(&program);

    printf("%d %d %d\n", index, pt.data[index].process.data.size, data.size);

    program_init(&program, "program.txt");
    data_init(&data, 10);
    prev_data = process_table_get_data(&pt, index);
    process_table_update(&pt, index, 10, program, data, 0, state_ready, 11);
    data_destroy(&data);
    program_destroy(&program);


    printf("%d %d %d\n", index, prev_data.size, pt.data[index].process.data.size);

    data_destroy(&prev_data);

    return 0;
}