#include "./includes/time_unit.h"
#include <stdlib.h>

void time_unit_init(time_unit_t *time) {
    *time = 0;
}

void time_unit_tick(time_unit_t *time) {
    *time += 1;
}