#include <stdio.h>
#include "./includes/time.h"

int main() {

    time_t time;
    time_init(&time);
    printf("%d\n", time_now(&time));
    time_tick(&time);
    printf("%d\n", time_now(&time));

    return 0;
}