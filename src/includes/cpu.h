#ifndef __CPU_H__
#define __CPU_H__

typedef struct cpu * cpu_t;

void   cpu_init(cpu_t *cpu);
void   cpu_destroy(cpu_t *cpu);
void   cpu_update(cpu_t *cpu /*, parametros*/);
int    cpu_get_program_counter(cpu_t *cpu);
time_t cpu_get_time_used(cpu_t *cpu);

#endif