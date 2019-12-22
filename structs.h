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
