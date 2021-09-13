#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "./src/includes/process_manager.h"
#include <string.h>

int main() {

    FILE *config_file = fopen("config_file", "r");
    int print_config = 0;
    scheduler sched_function = NULL;
    int use_input_file;
    int sleep_between_commands;

    char cmd[100];
    char opt;
    while(!feof(config_file)) {
        fscanf(config_file, "%s = %c\n", cmd, &opt);

        if(strcmp(cmd, "PRINT_EXECUTING_PID") == 0 && opt == 'Y') print_config |= PRINT_EXECUTING_PID;
        if(strcmp(cmd, "PRINT_PRIORITY") == 0 && opt == 'Y') print_config |= PRINT_PRIORITY;
        if(strcmp(cmd, "PRINT_QUANTUM") == 0 && opt == 'Y') print_config |= PRINT_QUANTUM;
        if(strcmp(cmd, "PRINT_VARIABLES") == 0 && opt == 'Y') print_config |= PRINT_VARIABLES;
        if(strcmp(cmd, "PRINT_PROGRAM_COUNTER") == 0 && opt == 'Y') print_config |= PRINT_PROGRAM_COUNTER;
        if(strcmp(cmd, "PRINT_USED_CPU_TIME") == 0 && opt == 'Y') print_config |= PRINT_USED_CPU_TIME;
        if(strcmp(cmd, "PRINT_PARENT_PID") == 0 && opt == 'Y') print_config |= PRINT_PARENT_PID;
        if(strcmp(cmd, "PRINT_BLOCKED") == 0 && opt == 'Y') print_config |= PRINT_BLOCKED;
        if(strcmp(cmd, "PRINT_READY") == 0 && opt == 'Y') print_config |= PRINT_READY;
        if(strcmp(cmd, "PRINT_USED_QUANTUM") == 0 && opt == 'Y') print_config |= PRINT_USED_QUANTUM;
        if(strcmp(cmd, "USE_ROUND_ROBIN") == 0) sched_function = (opt == 'Y') ? weird_round_robin : sjf_sched;
        if(strcmp(cmd, "USE_CONTROL_FILE") == 0) use_input_file = (opt == 'Y');
        if(strcmp(cmd, "SLEEP_BETWEEN_COMMANDS") == 0) sleep_between_commands = (opt == 'Y');
    }

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

            if(sleep_between_commands) sleep(1);

            if(c == 'M') break;
        }

    } else {
        process_manager_t pm;
        process_manager_init(&pm, "init", print_config);
        
        while(1) {

            char c;
            read(fd[0], &c, 1);
            
            process_manager_execute_command(&pm, c, sched_function);
        }
    }

    return 0;
}
