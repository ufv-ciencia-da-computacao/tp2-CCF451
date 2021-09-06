#include "./includes/executing.h"

void executing_init(executing_t *ex) {
    ex->id = -1;
}
void executing_destroy(executing_t *ex) {
    ex->id = -1;
}
void executing_set(executing_t *ex, int id) {
    ex->id = id;
}
int executing_get(executing_t *ex) {
    return ex->id;
}

