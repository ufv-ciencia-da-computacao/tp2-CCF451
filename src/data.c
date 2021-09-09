#include "./includes/data.h"
#include <stdlib.h>
#include <string.h>

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
    int i;
    char temp[20];
    fprintf(file, "[");
    for(int i=0; i<data->size; ++i) {
        if(i) fprintf(file, ",");
        fprintf(file, "%d", data->data[i]);
    }
    fprintf(file, "]");
}

void data_print_to_string(data_t *data, char *str) {
    int i;
    char temp[20];
    strcpy(str, "");
    strcat(str, "[");
    for(int i=0; i<data->size; ++i) {
        if(i) strcat(str, ",");
        sprintf(temp, "%d", data->data[i]);
        strcat(str, temp);
    }
    strcat(str, "]");
}