#ifndef __CPU_H__
#define __CPU_H__

typedef struct cpu * cpu_t;

struct cpu {
    // program_ptr,
    int program_counter;
    int *data_memory_ptr;
    time_t quantum;
    time_t time_used;
};

void   cpu_init(cpu_t *cpu);
void   cpu_destroy(cpu_t *cpu);
void   cpu_update(cpu_t *cpu, int* data_memory, int quantum, int program_counter);
int    cpu_get_program_counter(cpu_t *cpu);
time_t cpu_get_time_used(cpu_t *cpu);
void cpu_add_quantum_time(cpu_t *cpu);

#endif