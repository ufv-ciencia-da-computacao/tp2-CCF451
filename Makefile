.PHONY: all

all: main clean

main: main.c cpu process_table program data blocked ready executing process_manager time_unit
	gcc main.c cpu.o process_table.o program.o data.o blocked.o ready.o executing.o process_manager.o time_unit.o -o MAIN 

cpu: ./src/cpu.c
	gcc -c ./src/cpu.c -o cpu.o

process_table: ./src/process_table.c
	gcc -c ./src/process_table.c -o process_table.o

program: ./src/program.c
	gcc -c ./src/program.c -o program.o

data: ./src/data.c
	gcc -c ./src/data.c -o data.o

blocked: ./src/blocked.c
	gcc -c ./src/blocked.c -o blocked.o

ready: ./src/ready.c
	gcc -c ./src/ready.c -o ready.o

executing: ./src/executing.c
	gcc -c ./src/executing.c -o executing.o

process_manager: ./src/process_manager.c
	gcc -c ./src/process_manager.c -o process_manager.o

time_unit: ./src/time_unit.c
	gcc -c ./src/time_unit.c -o time_unit.o

clean:
ifeq ($(OS),Windows_NT)
#	del main
	del *.o
else
	rm -rf *.o
endif
