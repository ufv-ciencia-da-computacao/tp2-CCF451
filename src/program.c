#include "./includes/program.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void program_init(program_t* program,char* file){
  FILE *f;
  int contador=0;
  f=fopen(file,"r");
  while (!feof(f)) {
    char str[200];
    fgets(str,200,f);
    contador++;
  }
  program->tam=contador;
  program->instructions=(instruction_t*) malloc(contador*sizeof(instruction_t));
  contador=0;
  fseek(f, 0, SEEK_SET);
  while(1) {
    char c;
    char parameter1[200];
    char parameter2[200];
    if(fscanf(f,"%c",&c)==EOF) break;
    //fscanf(f,"%c",&c);
    program->instructions[contador].name=c;
    if(c=='T'){
       strcpy(program->instructions[contador].parameter1,"");
       strcpy(program->instructions[contador].parameter2,"");
     }
     if(c=='N' || c=='F' || c=='D' || c=='R'){
       fscanf(f,"%s\n",parameter1);
       strcpy(program->instructions[contador].parameter1,parameter1);
       strcpy(program->instructions[contador].parameter2,"");
     }

     if(c=='V' || c=='A' || c=='S'){
       fscanf(f,"%s %s\n",parameter1,parameter2);
       strcpy(program->instructions[contador].parameter1,parameter1);
       strcpy(program->instructions[contador].parameter2,parameter2);
     }

    contador++;
 }
 fclose(f);

}
void program_destroy(program_t* program){
  free(program->instructions);
  program->tam=0;
}
instruction_t program_get(program_t* program,int index){
  return program->instructions[index];
}
void program_to_string(program_t* program){
  printf("Tamanho: %d\n",program->tam );
  for(int i=0;i<program->tam;i++){
    printf("%c %s %s \n",program->instructions[i].name,program->instructions[i].parameter1,
    program->instructions[i].parameter2 );
  }
}
