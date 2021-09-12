#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "./src/includes/process_manager.h"

int main() {

    int use_round_robin = 1;
    int use_input_file = 0;
    int use_simple_output = 1;

    printf("The system is initializing");
    fflush(stdout);
    for(int i=0; i<3; ++i) {
        printf(".");
        fflush(stdout);
        sleep(1);
    }

    printf("\nready to go!!\n");
    sleep(1);


    int print_config = PRINT_EXECUTING_PID | PRINT_USED_QUANTUM | PRINT_PROGRAM_COUNTER;

    int fd[2];

    if(pipe(fd) == -1) {
        fprintf(stderr, "Pipe failed");
        return 0;
    }

    pid_t p = fork();

    if(p < 0) {
        fprintf(stderr, "Fork failed");
        return 0;
    } else if(p > 0) {
        FILE *file;
        if(use_input_file) file = fopen("control", "r");
        else file = stdin;

        char c;
        while(1) {
            fscanf(file, " %c", &c);
            write(fd[1], &c, 1);

            if(c == 'M') break;
        }

    } else {
        process_manager_t pm;
        process_manager_init(&pm, "init", print_config);
        
        while(1) {

            char c;
            read(fd[0], &c, 1);
            
            process_manager_execute_command(&pm, c, weird_round_robin);
        }
    }

    return 0;
}
