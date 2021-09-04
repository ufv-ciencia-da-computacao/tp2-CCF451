#ifndef __DATA_H__
#define __DATA_H__

typedef struct {
    int *data;
    int size;
} data_t;

void data_init(data_t *data, int size);
void data_destroy(data_t *data);
void data_set(data_t *data, int index, int value);
int  data_get(data_t *data, int index);
data_t data_copy(data_t *orig);

#endif