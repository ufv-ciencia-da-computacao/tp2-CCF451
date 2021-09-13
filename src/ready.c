#include "./includes/ready.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

void ready_init(ready_t *ready){
  ready->hPriority=NULL;
  ready->mPriority=NULL;
  ready->lPriority=NULL;
  ready->vLPriority=NULL;
}

void ready_destroy(ready_t *ready){
  queue_destroy(ready->hPriority);
  queue_destroy(ready->mPriority);
  queue_destroy(ready->lPriority);
  queue_destroy(ready->vLPriority);
  //free(ready->hPriority);
  //free(ready->mPriority);
  //free(ready->lPriority);
  //free(ready->vLPriority);
  ready_init(ready);
}

void ready_push(ready_t *ready, int index,int priority){
  queuePriority *aux;

  if(priority==0){
    aux=ready->hPriority;
    if(aux==NULL){
      ready->hPriority=(queuePriority*) malloc(sizeof(queuePriority));
      queue_init(ready->hPriority,index);
    }else{
      add_index(ready->hPriority,index);
    }
  }
  if(priority==1){
    aux=ready->mPriority;
    if(aux==NULL){
      ready->mPriority=(queuePriority*) malloc(sizeof(queuePriority));
      queue_init(ready->mPriority,index);
    }else{
      add_index(ready->mPriority,index);
    }

  }
  if(priority==2){
    aux=ready->lPriority;
    if(aux==NULL){
      ready->lPriority=(queuePriority*) malloc(sizeof(queuePriority));
      queue_init(ready->lPriority,index);
    }else{
      add_index(ready->lPriority,index);
    }

  }
  if(priority==3){
    aux=ready->vLPriority;
    if(aux==NULL){
      ready->vLPriority=(queuePriority*) malloc(sizeof(queuePriority));
      queue_init(ready->vLPriority,index);
    }else{
      add_index(ready->vLPriority,index);
    }
  }
}

void ready_pop(ready_t *ready){
  if(ready->hPriority!=NULL){
    ready->hPriority=queue_pop(ready->hPriority);
  }
  else if(ready->mPriority!=NULL){
      ready->mPriority=queue_pop(ready->mPriority);
  }
  else if(ready->lPriority!=NULL){
      ready->lPriority=queue_pop(ready->lPriority);
  }
  else{
      ready->vLPriority=queue_pop(ready->vLPriority);
  }
}

int  ready_top(ready_t *ready){
  if(ready->hPriority!=NULL){
    return ready->hPriority->index;
  }
  else if(ready->mPriority!=NULL){
    return ready->mPriority->index;  }
    else if(ready->lPriority!=NULL){
      return ready->lPriority->index;
    }
    else if(ready->vLPriority!=NULL){
      return ready->vLPriority->index;
    }else{
      return -1;
    }
  }

int  ready_size(ready_t *ready){
    int contador=0;
    if(ready->hPriority!=NULL){
      contador+= queue_size(ready->hPriority);
    }
    if(ready->mPriority!=NULL){
      contador+= queue_size(ready->mPriority);
    }
    if(ready->lPriority!=NULL){
      contador+= queue_size(ready->lPriority);;
    }
    if(ready->vLPriority!=NULL){
      contador+= queue_size(ready->vLPriority);
    }

    return contador;
  }

int ready_empty(ready_t *ready){
  return ready_size(ready)==0;
}


void queue_init(queuePriority *queue,int index){
  queue->index=index;
  queue->next=NULL;
}

void queue_destroy(queuePriority *queue){
  queuePriority *aux;
  queuePriority *prev;
  if(queue==NULL) return;
  aux=queue;
  while(aux!=NULL){
    prev= aux;
    aux=aux->next;
    free(prev);
  }
}

queuePriority* queue_pop(queuePriority *queue){
    queuePriority *next;
    queuePriority *first;
    first=queue;
    next=queue->next;
    free(first);
    return next;
  }

int queue_size(queuePriority *queue){
  int contador=0;
  queuePriority *aux;
  aux=queue;
  while (aux->next!=NULL) {
    contador++;
    aux=aux->next;
  }
  return 1+contador;
}

void add_index(queuePriority *queue,int index){
  queuePriority *aux;
  aux=queue;
  while (aux->next!=NULL) {
      aux=aux->next;
  }
  aux->next=(queuePriority*) malloc(sizeof(queuePriority));
  aux=aux->next;
  queue_init(aux,index);
}

void print_queue_to_string(ptrQueueP queue, int priority, char *str) {
  char temp[100];
  while(queue != NULL) {
    sprintf(temp, "(%d,%d)", priority, queue->index);
    strcat(str, temp);
    if(queue->next != NULL) strcat(str, ",");
    queue = queue->next;
  }
}

void ready_print_to_string(ready_t *ready, char *str) {
  strcpy(str, "[");
  int prev = 0;
  if(ready->hPriority != NULL) {
    print_queue_to_string(ready->hPriority, 0, str);
    prev = 1;
  }
  if(ready->mPriority != NULL) {
    if(prev) strcat(str, ",");
    print_queue_to_string(ready->mPriority, 1, str);
    prev = 1;
  }
  if(ready->lPriority != NULL) {
    if(prev) strcat(str, ",");
    print_queue_to_string(ready->lPriority, 2, str);
    prev = 1;
  }
  if(ready->vLPriority != NULL) {
    if(prev) strcat(str, ",");
    print_queue_to_string(ready->vLPriority, 3, str);
  }
  strcat(str, "]");
}

void toString(ready_t *ready){
  char s1[10000];
  char s2[10000];
  char s3[10000];
  char s4[10000];
  if(ready->hPriority!=NULL){
    ptrQueueP aux;
    int contador=0;
    aux=ready->hPriority;
    s1[contador]=aux->index+'0';
    s1[contador+1]=',';
    contador+=2;
    printf("%d\n",contador );
    while (aux->next!=NULL) {
      aux=aux->next;
      s1[contador]=(aux->index)+'0';
      s1[contador+1]=',';
      printf("%d\n",contador );
      contador+=2;
    }
  }

  printf("High priority:%s\n" ,s1 );

  if(ready->mPriority!=NULL){
    ptrQueueP aux;
    int contador=0;
    aux=ready->mPriority;
    s2[contador]=aux->index+'0';
    s2[contador+1]=',';
    contador+=2;
    while (aux->next!=NULL) {
      aux=aux->next;
      s2[contador]=(aux->index)+'0';
      s2[contador+1]=',';
      contador+=2;
    }
  }
  printf("Medium priority:%s\n",s2 );

  if(ready->lPriority!=NULL){
    ptrQueueP aux;
    int contador=0;
    aux=ready->lPriority;
    s3[contador]=aux->index+'0';
    s3[contador+1]=',';
    contador+=2;
    while (aux->next!=NULL) {
      aux=aux->next;
      s3[contador]=(aux->index)+'0';
      s3[contador+1]=',';
      contador+=2;
    }
  }
  printf("Low priority:%s\n",s3 );

  if(ready->vLPriority!=NULL){
    ptrQueueP aux;
    int contador=0;
    aux=ready->vLPriority;
    s4[contador]=aux->index+'0';
    s4[contador+1]=',';
    contador+=2;
    while (aux->next!=NULL) {
      aux=aux->next;
      s4[contador]=(aux->index)+'0';
      s4[contador+1]=',';
      contador+=2;
    }
  }
  printf("Very low priority:%s\n",s4 );
}
