#include <stdio.h>
#include "../../includes/process_table.h"

int main() {

    int N = 10;

    process_table_t pt;
    process_table_init(&pt, N);

    printf("%d\n", sizeof(*pt.data));

    return 0;
}