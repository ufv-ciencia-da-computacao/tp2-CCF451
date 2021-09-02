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
    data_init(&data, 0);
    index = process_table_add(&pt, -1, 0, program, data, 0, 0);

    printf("index = pid = %d\n", index);


    return 0;
}