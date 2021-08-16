.PHONY: all

all: main

main: ./src/main.c
	gcc ./src/main.c -o main

clean:
ifeq ($(OS),Windows_NT)
	del main
else
	rm main
endif