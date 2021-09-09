#include <stdio.h>
#include "../../includes/data.h"

int main() {

    data_t data, data1;
    data_init(&data, 10);

    data_set(&data, 2, 0);
    data_set(&data, 1, 1);

    char str[10000];

    data_print_to_string(&data, str);

    printf("%s\n", str);

    return 0;
}