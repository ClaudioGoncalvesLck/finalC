#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct colaborador
{
    int id;
    char nome;
} Colaborador;

struct listaColaboradores
{
    Colaborador col[10];
};

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
void registarCol(Colaborador *lista, int tam);
void listarCol(Colaborador *lista);