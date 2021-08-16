#ifndef __PROCESS_H__
#define __PROCESS_H__

typedef enum states states_t;

typedef struct process {
    int pid;
    int parent_pid;
    int program_counter;

    
} process_t;


#endif