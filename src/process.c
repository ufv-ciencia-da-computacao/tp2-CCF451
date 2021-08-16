#include "./includes/process.h"

typedef struct process_manager {
/*
    registros,
    contador de programa,
    palavra do estado do programa,
    ponteiro de pilha,
    estado do processo,
    Prioridade,
    parametros de escalonamento,
    ID do processo,
    processo pai,
    grupo de processo,
    sinais,
    momento que o processo foi iniciado,
    tempo de CPU usado,
    tempo de CPU do process filho,
    tempo de alarme seguinte    
*/
} process_manager_t;

typedef struct memory_manager {
/*
    ponteiro para informações sobre o segmento de texto
    ponteiro para informações sobre o segmento de dados
    ponteiro para informações sobre o segmento de pilha
*/
} memory_manager_t;

typedef struct file_manager {
/*
    diretorio raiz,
    diretorio de trabalho,
    descritores de arquivos,
    id do usiario,
    id do grupo
*/
} file_manager_t;



struct process {
    process_manager_t proc;
    memory_manager_t mem;
    file_manager_t file;
};
