#include "./includes/cpu.h"
#include "./includes/time.h"

struct cpu {
    // program_ptr,
    int program_counter;
    int *data_memory_ptr;
    time_t quantum;
    time_t time_used;
};
