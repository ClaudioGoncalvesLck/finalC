#ifndef HEADER_H_
#define HEADER_H_

#define TAM_COLABORADORES 20
#define TAM_VULNERABILIDADES 20
#define TAM_AUDITORIAS 20

//Estruturas
//nivel
typedef enum
{
    baixo = 1,
    moderado,
    elevado
} nivel;

//Ativo
typedef enum
{
    false,
    true
} bool;

//Estrutura Data
typedef struct
{
    int dia;
    int mes;
    int ano;
} Data;

//Estrutura Vulnerabilidades
typedef struct
{
    int codigo;
    char descricao[100];
    nivel nivel;
    bool ativo;
} Vulnerabilidade;

//Estrutura Colaborador
typedef struct
{
    int codigo;
    char nome[70];
    bool ativo;
} Colaborador;

//Estrutura Auditorias
typedef struct
{
    int codigo;
    Data data;
    int duracao;
    int quantidadeVulnerabilidades;
    int quantidadeVulRemovidas;
    Colaborador colaborador;
    Vulnerabilidade vulnerabilidades[TAM_VULNERABILIDADES];

} Auditoria;

//ECRA
//Funcao Limpar o ecra
void limparEcra(void);

//MENU
void menuDashboard();
int menuAuditorias(Auditoria auditorias[], Colaborador colaboradores[], Vulnerabilidade vulnerabilidades[], int n, int nVul, int nCol);
int menuVulnerabilidades(Vulnerabilidade vulnerabilidades[], Auditoria auditorias[], int n, int nAud);
int menuColaboradores(Colaborador colaboradores[], int n);
void menuPrincipal();

//Funcoes Ler Ficheiros
void lerArrayColaboradores(Colaborador colaboradores[]);
void lerArrayVulnerabilidades(Vulnerabilidade vulnerabilidades[]);
void lerArrayAuditorias(Auditoria auditorias[]);
void lerNumAudColVul(int arrNum[]);
void guardarArrayColaboradores(Colaborador colaboradores[]);
void guardarArrayVulnerabilidades(Vulnerabilidade vulnerabilidades[]);
void guardarArrayAuditorias(Auditoria auditorias[]);
void guardarNumAudColVul(int nAud, int nCol, int nVul);

//Funcoes Colaborador
Colaborador novoColaborador(int id);
int inserirColaborador(Colaborador colaboradores[], int n);
void editarColaborador(Colaborador colaboradores[], int n);
void removerColaborador(Colaborador colaboradores[], int n);
int pesquisarColaboradorID(Colaborador colaboradores[], int n, int id);
void listarColaboradores(Colaborador colaboradores[], int n);

//Funcoes Vulnerabilidades
Vulnerabilidade novoVulnerabilidade(int id);
int inserirVulnerabilidade(Vulnerabilidade vulnerabilidades[], int n);
void editarVulnerabilidade(Vulnerabilidade vulnerabilidades[], int n);
int pesquisarVulnerabilidadeID(Vulnerabilidade vulnerabilidades[], int n, int id);
void adicionarVulAuditoria(Vulnerabilidade vulnerabilidades[], Auditoria auditorias[], int n, int nAud);
void removerVulAuditoria(Vulnerabilidade vulnerabilidades[], Auditoria auditorias[], int n, int nAud);
void listarVulnerabilidades(Vulnerabilidade vulnerabiliades[], int n);
void listarVulAuditoria(Vulnerabilidade vulnerabilidades[], Auditoria auditorias[], int n, int nAud);

//Funcoes Auditorias
Auditoria novaAuditoria(Colaborador colaboradores[], Vulnerabilidade vulnerabilidades[], int id, int nVul, int nCol);
int criarAuditoria(Auditoria auditorias[], Colaborador colaboradores[], Vulnerabilidade vulnerabilidades[], int n, int nVul, int nCol);
int pesquisarAuditoriaID(Auditoria auditorias[], int n, int id);
int pesquisarAuditoriaVulID(Auditoria auditorias[], int nVul, int id, int idVul);
void listarAuditorias(Auditoria auditorias[], Colaborador colaboradores[], int n);
void listarAuditoriasColaborador(Auditoria auditorias[], Colaborador colaboradores[], int n, int nCol);
void listarAuditoriasOrdenadas(Auditoria auditorias[], Colaborador colaboradores[], int n);
int auditoriaComMaisVulnerabilidades(Auditoria auditorias[], int n);
int auditoriaComMenosVulnerabilidades(Auditoria auditorias[], int n);
double mediaVulAuditoria(Auditoria auditorias[], int n);
#endif