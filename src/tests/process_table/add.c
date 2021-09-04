/*
    ADD

    Added data is completely copied inside the table. 
    Be carrefull with allocated memory, YOU have to make sure of allocated memory, process table WON'T take care of it.
*/

#include <stdio.h>
#include <stdlib.h>
#include "../../includes/process_table.h"

int main() {

    int N = 10;

    process_table_t pt;
    process_table_init(&pt, N);

    program_t program;
    data_t data;
    int index;

    program_init(&program, "init.txt");
    data_init(&data, 10);
    index = process_table_add(&pt, -1, 0, program, data, 0, 0);
    data_destroy(&data);
    program_destroy(&program);

    printf("%d %d %d\n", index, pt.data[index].process.data.size, data.size);


    return 0;
}