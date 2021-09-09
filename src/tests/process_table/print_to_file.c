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

    FILE *file = fopen("teste.csv", "w");

    process_table_print_to_file(&pt, file);

    fclose(file);

    return 0;
}