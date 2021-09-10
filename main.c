#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include "./src/includes/process_manager.h"

int main() {

    int use_round_robin = 1;
    int use_input_file = 0;

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
        if(use_input_file) file = fopen("control.txt", "r");
        else file = stdin;

        char c;
        while(1) {
            fscanf(file, " %c", &c);
            write(fd[1], &c, 1);

            // printf("read: %c\n", c);

            if(c == 'M') break;
        }

    } else {
        process_manager_t pm;
        process_manager_init(&pm, "init");
        
        while(1) {
            // wait(NULL);

            char c;
            read(fd[0], &c, 1);

            printf("received: %c\n", c);
            
            process_manager_execute_command(&pm, c, use_round_robin);

            if(c == 'M') break;
        }
    }

    return 0;
}
