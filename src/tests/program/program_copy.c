#include "../../includes/program.h"
#include <stdio.h>

void main(){
  printf("O programa deve ser:\n N 2\n D 0\n D 1\n V 0 1000\n V 1 500\n A 0 19\n A 0 20\n S 1 53 \n A 1 55\n F 1\n R file_a\n T\n ");
  program_t program;
  program_t copy;
  program_init(&program,"../inputs/file1.txt");
  copy=program_copy(&program);
  program.instructions[0].name='x';
  //vetor copiadp
  printf("Vetor copiado:\n" );
  program_to_string(&copy);
  //vetor antigo alterado
  printf("Vetor antigo alterado:\n" );
  program_to_string(&program);

}
