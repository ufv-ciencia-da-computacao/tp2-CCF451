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
    data_init(&data, 7);
    index = process_table_add(&pt, -1, 0, program, data, 0, 0);

    prev_data = process_table_get_data(&pt, index);

    process_table_remove(&pt, index);

    printf("%d %d\n", pt.data[index].process.data.size, prev_data.size);

    data_destroy(&prev_data);

    return 0;
}