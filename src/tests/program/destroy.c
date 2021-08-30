#include "../../includes/program.h"
#include <stdio.h>
#include <stddef.h>
void main(){
  printf("O tamanho deve ser 0.\n");
  printf("Instruções devem ser nulas\n" );
  program_t program;
  program_init(&program,"../inputs/file1.txt");
  program_destroy(&program);
  if(program.instructions==NULL){
    printf("Instruções são nulas\n" );
  }else{
    printf("Instruções não são nulas\n" );
  }
  printf("Tamanho:%d",program.tam );

}
