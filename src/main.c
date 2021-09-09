#include <stdio.h>
#include "./includes/time.h"

int main() {

    int time;
    time_init(&time);
    printf("%d\n", time_now(&time));
    intick(&time);
    printf("%d\n", time_now(&time));

    return 0;
}
