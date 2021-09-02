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

void data_copy(data_t *dest, data_t orig) {
    int i;
    if(dest->size > 0) data_destroy(dest);
    data_init(dest, orig.size);
    for(i=0; i<orig.size; ++i) {
        dest->data[i] = orig.data[i];
    }
}