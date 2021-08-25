#include "./includes/cpu.h"
#include "./includes/time.h"
#include <stdio.h>

void   cpu_init(cpu_t *cpu) {
    (*cpu)->time_used=0;
    (*cpu)->data_memory_ptr=NULL;
    (*cpu)->program_counter = 0;

}
void   cpu_destroy(cpu_t *cpu);
void   cpu_update(cpu_t *cpu, int* data_memory, int quantum, int program_counter) {
    (*cpu)->data_memory_ptr = data_memory;
    (*cpu)->quantum = quantum;
    (*cpu)->program_counter = program_counter;
}
int    cpu_get_program_counter(cpu_t *cpu) {
    return (*cpu)->program_counter;
}
time_t cpu_get_time_used(cpu_t *cpu) {
    return (*cpu)->time_used;
}

void cpu_add_quantum_time(cpu_t *cpu) {
    (*cpu)->time_used += (*cpu)->quantum;
}