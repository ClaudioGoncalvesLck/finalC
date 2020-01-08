#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define F_Auditorias "Auditorias.Dat"
#define F_AuditoriasOrdenadas "AuditoriasOrdenadas.Dat"
#define F_Colaboradores "Colaboradores.Dat"
#define F_Vulnerabilidades "Vunlerabilidades.Dat"
#define F_MaisVulnerabilidades "MaisVunlerabilidades.Dat"
#define F_MenosVulnerabilidades "MenosVunlerabilidades.Dat"
#define F_VulnImpacto "VulnImpacto.Dat"
#define F_Equipamentos "Equipamentos.Dat"
#define F_Tmp "tmp.Dat"



#define MAX_VULNERABILIDADES 10
#define MAX_NOME 50
#define MAX_EQUIPAMENTOS 10
#define MAX_EQUIP 20
#define MAX_DESC 50

FILE* fp;
FILE* fp_tmp;

int maior, menor;

enum mes 
{
	Jan = 1, Feb = 2, Mar = 3, Abr = 4, Mai = 5, Jun = 6, 
	Jul = 7, Ago = 8, Set = 9, Out = 10, Nov = 11, Dez = 12
};

enum resolvido
{
	nao, sim
};

enum impacto
{
	baixo, moderado, elevado
};

typedef struct data
{
	int dia, ano;
	enum mes mes;
}Data;

typedef struct colaborador
{
	int codigo;
	char nome[MAX_NOME];
	char apagado;
}Colaborador;

typedef struct equipamento
{
	int codigo;
	char tipo[MAX_EQUIP], marca[MAX_EQUIP], modelo[MAX_EQUIP];
	Data dataAquisicao;
	char apagado;
}Equipamento;

typedef struct vulnerabilidade
{
	int codigo, codAuditoria, qddVulnI;
	char descricao[MAX_DESC];
	enum impacto impacto;
	enum resolvido resolvido;
	Equipamento equipamentos[MAX_EQUIPAMENTOS];
	char apagado;
}Vulnerabilidade;

typedef struct auditoria 
{
	int codigo, duracao, qddVulnR, qddVulnI, qddEquiR, qddEquiI;
	Colaborador colaborador;
	Data data;
	Vulnerabilidade Vulnerabilidades[MAX_VULNERABILIDADES];
}Auditoria;

typedef struct vulnImpacto
{
	int codAud;
	int codVul[100];
}VulnImpacto;

typedef struct vulnEquipamento
{
	enum resolvido resolvido;
	Data data;
}VulnEquipamento;

void abrirFicheiro(char* nome);

void abrirFicheiroTmp(char* nome);

void inserirColaborador();

void lerColaborador(Colaborador* c);

void registarColaborador(Colaborador c);

void apresentarColaborador(Colaborador c);

void alterarColaborador();

void listarColaboradores();

void apagarColaborador();



void inserirVulnerabilidade();

void lerVulnerabilidade(Vulnerabilidade* v);

void registarVulnerabilidade(Vulnerabilidade v);

void listarVulnerabilidades();

void alterarVulnerabilidade();

void listarVulnerabilidadeSimples();

void apresentarVulnerabilidade(Vulnerabilidade v);

void apresentarCodAuditoria(Auditoria a);

void listarVulnPorEquipamento();


void inserirAuditoria();

void lerAuditoria(Auditoria* a);

void registarAuditoria(Auditoria a);

void listarAuditoria();

void listarAuditoriaColaborador(int n);

void listarAuditoriaOrdenadas();

void apresentarAuditoria(Auditoria a);

void apresentarVulnAuditoria(Auditoria a);

void selecionarColaborador();

void apresentarAuditoriaColaborador(Auditoria a);

void alterarAuditoria();

void adicionarVuln(Auditoria * a);

void removerVuln(Auditoria* a);

int contaAuditorias();

void maiorMenorVulnerabilidades();

float mediaVulnerabilidades();

void ordenaAuditorias();

void dashboard();

void menu();

void inserirDados();

void editarDados();

void listar();