.PHONY: all

all: init next_instruction clean

init: executing.o ready.o blocked.o time.o data.o program.o process_table.o cpu.o init.o
	gcc executing.o ready.o blocked.o time.o data.o program.o process_table.o cpu.o init.o -o init

next_instruction: executing.o ready.o blocked.o time.o data.o program.o process_table.o cpu.o next_instruction.o
	gcc executing.o ready.o blocked.o time.o data.o program.o process_table.o cpu.o next_instruction.o -o next_instruction

next_instruction.o: ./next_instruction.c
	gcc -c ./next_instruction.c -o next_instruction.o

init.o: ./init.c
	gcc -c ./init.c -o init.o

cpu.o: ../../cpu.c
	gcc -c ../../cpu.c -o cpu.o

process_table.o: ../../process_table.c
	gcc -c ../../process_table.c -o process_table.o

program.o: ../../program.c
	gcc -c ../../program.c -o program.o

data.o: ../../data.c
	gcc -c ../../data.c -o data.o

time.o: ../../time.c
	gcc -c ../../time.c -o time.o

blocked.o: ../../blocked.c
	gcc -c ../../blocked.c -o blocked.o

ready.o: ../../ready.c
	gcc -c ../../ready.c -o ready.o

executing.o: ../../executing.c
	gcc -c ../../executing.c -o executing.o

clean:
ifeq ($(OS),Windows_NT)
	del main
	del *.o
else
	rm *.o
endif