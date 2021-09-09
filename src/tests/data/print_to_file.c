#include <stdio.h>
#include "../../includes/data.h"

int main() {

    data_t data, data1;
    data_init(&data, 10);

    data_set(&data, 2, 0);
    data_set(&data, 1, 1);

    data_print_to_file(&data, stdout);

    return 0;
}