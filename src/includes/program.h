#ifndef __PROGRAM_H__
#define __PROGRAM_H__

typedef struct{
  char name;
  char parameter1[100];
  char parameter2[100];
}instruction_t;

typedef struct{
  instruction_t* instructions;
  int tam;
}program_t;

void program_init(program_t* program,char* file);
void program_destroy(program_t* program);
instruction_t program_get(program_t* program,int index);
void program_to_string(program_t* program);
program_t program_copy(program_t* program);

#endif
