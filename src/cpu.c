#include "./includes/cpu.h"
#include "./includes/time.h"

struct cpu {
    // program_ptr,
    int program_counter;
    int *data_memory_ptr;
    time_t quantum;
    time_t time_used;
};


void cpu_init();
void cpu_destroy();
void cpu_set(); // set values
void cpu_get(); // get values