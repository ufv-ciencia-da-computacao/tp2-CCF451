#include <stdio.h>
#include "../../includes/data.h"

int main() {

    data_t data, data1;
    data_init(&data, 10);

    data_set(&data, 2, 0);
    data_set(&data, 1, 1);

    data_copy(&data1, data);

    printf("%d\n", data_get(&data1, 1));

    return 0;
}