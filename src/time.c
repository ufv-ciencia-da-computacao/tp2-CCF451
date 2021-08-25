#include "./includes/time.h"
#include <stdlib.h>

struct time {
    int t;
};

void time_init(time_t *time) {
    *time = malloc(sizeof **time);
    (*time)->t = 0;
}

void time_tick(time_t *time) {
    (*time)->t++;
}

int  time_now(time_t *time) {
    return (*time)->t;
}