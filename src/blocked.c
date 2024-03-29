#include "includes/blocked.h"
#include <string.h>

static int blocked_max(blocked_t * blocked){
    return blocked->size - 1;
}

void blocked_init(blocked_t *blocked, int size){
    blocked->pid = (int *) malloc((size + 1) * sizeof(int));
    blocked->size = size;
    blocked->front = 0;
    blocked->back = 0;
}

void blocked_destroy(blocked_t *blocked){
    free(blocked->pid);
    blocked->size = -1;
    blocked->front = 0;
    blocked->back = 0;
}

void blocked_push(blocked_t *blocked, int pid){
    blocked->pid[blocked->back++] = pid;
    if(blocked->back > blocked_max(blocked)) blocked->back = 0;
    ++blocked->size;

}
void blocked_pop(blocked_t *blocked){
    blocked->pid[blocked->front] = -1;
    if(++blocked->front > blocked_max(blocked)) blocked->front = 0;
    --blocked->size;
}

int  blocked_front(blocked_t *blocked){
    return blocked->pid[blocked->front];
}

int  blocked_empty(blocked_t *blocked){
    return blocked->front == blocked->back;
}

int  blocked_size(blocked_t *blocked){
    return blocked->size;
}

void blocked_print_to_string(blocked_t *blocked, char *str) {
    strcpy(str, "[");
    char temp[100];
    int curr, i;
    for(curr = blocked->front, i=0; curr != blocked->back; ++i) {
        if(i) strcat(str, ",");
        sprintf(temp, "%d", blocked->pid[curr]);
        strcat(str, temp);
        curr = (curr == blocked_max(blocked)) ? 0 : (curr + 1);
    }
    strcat(str, "]");
}