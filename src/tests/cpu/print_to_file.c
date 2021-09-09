#include <stdio.h>
#include "../../includes/cpu.h"
#include "../../includes/data.h"
#include "../../includes/program.h"

int main() {

    cpu_t cpu;
    data_t data;
    program_t program;

    program_init(&program, "init.txt");
    data_init(&data, 10);

    cpu_init(&cpu, program, data,0,3);

    cpu_print_to_file(&cpu,fopen("teste.csv","w"));

    return 0;
}
