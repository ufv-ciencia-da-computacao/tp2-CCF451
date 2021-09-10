#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "./src/includes/process_manager.h"

int main() {

    int use_round_robin = 1;
    int use_input_file = 1;
    int use_simple_output = 1;

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
        while(!feof(file)) {
            fscanf(file, "%c ", &c);
            write(fd[1], &c, 1);

            printf("sent: %c\n", c);
        }

    } else {
        process_manager_t pm;
        process_manager_init(&pm, "init");
        
        while(1) {

            char c;
            read(fd[0], &c, 1);

            printf("received: %c\n", c);
            
            process_manager_execute_command(&pm, c, use_round_robin);

            if(c == 'M') break;
        }
    }

    return 0;
}
