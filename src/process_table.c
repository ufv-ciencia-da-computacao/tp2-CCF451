#include "./includes/process_table.h"
#include "./includes/process.h"

struct process_table {
    process_t *list;
    int size;
};
