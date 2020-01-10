#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct colaborador
{
    int id;
    char nome;
} Colaborador;

typedef struct auditoria
{
    int id;
    int colaboradorId;
    char data;
    int duracao;
    int quantidadeVuln;
} Auditoria;

typedef struct vulnerabilidade
{
    int id;
    char desc;
    char nivel;
} Vulnerabilidade;

void dadosColaborador(Colaborador *lista);
void listarCol(Colaborador *lista, int tam);
void read(Colaborador *lista, int tam);
void save(Colaborador *lista, int tam);