#include "./includes/data.h"
#include <stdlib.h>

void data_init(data_t *data, int size) {
    data->data = malloc(size * sizeof(*data->data));
    data->size = size;
}

void data_destroy(data_t *data) {
    free(data->data);
    data->data = NULL;
    data->size = 0;
}

void data_set(data_t *data, int index, int value) {
    data->data[index] = value;
}

int  data_get(data_t *data, int index) {
    return data->data[index];
}

data_t data_copy(data_t *orig) {
    int i;
    data_t dest;
    data_init(&dest, orig->size);
    for(i=0; i<orig->size; ++i) {
        dest.data[i] = orig->data[i];
    }
    return dest;
}

void data_print_to_file(data_t *data, FILE *file) {

}

void data_print_to_string(data_t *data, char *str) {
    int i;
    for(int i=0; i<data->size; ++i) {
        if(i) printf(",");
        sprintf(str, "%d", data->data[i]);
    }
}