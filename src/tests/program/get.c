#include "../../includes/program.h"
#include <stdio.h>

void main(){
  printf("A instrução deve ser: A 1 55\n ");
  program_t program;
  program_init(&program,"../inputs/file1.txt");
  instruction_t instruction;
  instruction=program_get(&program,8);
  printf("%c %s %s \n",instruction.name,instruction.parameter1,
  instruction.parameter2 );

}
