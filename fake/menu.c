#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "header.h"

//Limpar Ecra
void limparEcra(void)
{
    //se for Windows o computador e utilizado o comando system("cls"), se for outro OS, é o comando system("clear"))
    #ifdef _WIN32
        system("cls");
    #elif defined(unix) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)) 
        system("clear");
    #endif
}

//Mostra a Dashboard
void menuDashboard(Auditoria auditorias[], Vulnerabilidade vulnerabilidades[], int nAud, int nVul)
{
    int i;
    float media;
        puts("+------------------------------Dashboard-------------------------------+");
    printf("|%70s|\n", "");
    //Se nao tem numero de registos de auditorias, mostra que nao existe auditorias
    if (nAud == 0)
    {
        printf("|%sQuantidade Auditorias: %-10s%36s|\n", " ", "Nao existe", " ");
        printf("|%sMedia de Auditorias: %-10s%38s|\n", " ", "Nao existe", " ");
        printf("|%s%-69s|\n", " ", "Auditoria c/ mais vulnerabilidades: ");
        printf("|   %-10s%57s|\n", "Nao existe", " ");
        printf("|%s%-69s|\n", " ", "Auditoria c/ menos vulnerabilidades: ");
        printf("|   %-10s%57s|\n", "Nao existe", " ");
        printf("|%70s|\n", "");
    }
    else
    {
        //mostra a quantidade de auditorias
        printf("|%sQuantidade Auditorias: %-5d%41s|\n", " ", nAud, " ");
        //variavel para guardar o valor da funcao mediaVulAuditoria
        media = mediaVulAuditoria(auditorias, nAud); 
        //mostra a media de vulnerabilidades nas auditorias
        printf("|%sMedia de Vulnerabilidades no conjunto de todas as Auditorias: %-5.2f%2s|\n", " ", media, " ");
        //variavel para guardar o indice da auditoria com mais vulnerabilidades ativas
        i = auditoriaComMaisVulnerabilidades(auditorias, nAud);
        //mostra a auditoria com mais vulnerabilidades
        printf("|%s%-69s|\n", " ", "Auditoria c/ mais vulnerabilidades: ");
        //mostra o codigo, data e quantidade vulnerabilidades ativas dessa auditoria
        printf("|   Codigo: %-5dData: %-2d-%-2d-%-4d  N. Vulnerabilidades: %-5d%10s|\n", auditorias[i].codigo, auditorias[i].data.dia, auditorias[i].data.mes, auditorias[i].data.ano, auditorias[i].quantidadeVulnerabilidades, "");
        //variavel para guardar o indice da auditoria com menos vulnerabilidades ativas
        i = auditoriaComMenosVulnerabilidades(auditorias, nAud);
        //mostra a auditoria com menos vulnerabilidades
        printf("|%s%-69s|\n", " ", "Auditoria c/ menos vulnerabilidades: ");
        //mostra o codigo, data e quantidade vulnerabilidades ativas dessa auditoria
        printf("|   Codigo: %-5dData: %-2d-%-2d-%-4d  N. Vulnerabilidades: %-5d%10s|\n", auditorias[i].codigo, auditorias[i].data.dia, auditorias[i].data.mes, auditorias[i].data.ano, auditorias[i].quantidadeVulnerabilidades, "");
        printf("|%70s|\n", "");
    }
    
}

//Mostra o Menu Principal
void menuPrincipal()
{
    //Declaracao das variaveis para o numero de registos das auditorias/colaboradores/vulnerabilidades
    int numColaboradores;
    int numVulnerabilidades;
    int numAuditorias;
    //Declaracao dos arrays para o numero de registos das auditorias/colaboradores/vulnerabilidades
    Colaborador aColaboradores[TAM_COLABORADORES];
    Vulnerabilidade aVulnerabilidades[TAM_VULNERABILIDADES];
    Auditoria aAuditorias[TAM_AUDITORIAS];
    int input; //variavel que guarda a escolha que o utilizador fez no menu 
    int arrNums[3]; //array para ler/guardar as variaveis numColaboradores/numVulnerabilidades/numAuditorias

    //Funcao para ler os numeros guardados no ficheiro nvariaveis e que guarda no array
    lerNumAudColVul(arrNums);
    //guardar a informacao do array em variaveis
    numAuditorias = arrNums[0];
    numColaboradores = arrNums[1];
    numVulnerabilidades = arrNums[2];

    //ler os arrays guardados dos ficheiros
    lerArrayColaboradores(aColaboradores);
    lerArrayAuditorias(aAuditorias);
    lerArrayVulnerabilidades(aVulnerabilidades);

    //vai repetindo enquanto o utilizador nao escrever 0
    do
    {
        limparEcra();
        //mostra o menu Dashboard
        menuDashboard(aAuditorias, aVulnerabilidades, numAuditorias, numVulnerabilidades);
        puts("+----------------------------------Menu--------------------------------+");
        printf("|%70s|\n", "");
        printf("|%s%-69s|\n", " ", "1-Auditorias");
        printf("|%s%-69s|\n", " ", "2-Colaboradores");
        printf("|%s%-69s|\n", " ", "3-Vulnerabilidades");
        printf("|%70s|\n", "");
        printf("|%s%-69s|\n", " ", "O-Sair");
        printf("|%70s|\n", "");
        puts("+----------------------------------------------------------------------+");
        scanf("%d", &input); 
        //Limpar o que escrevemos
        getchar();
        switch (input)
        {
        case 0:
            break;
        case 1: //se escrever 1, limpa o ecra e abre o menuAuditorias
            limparEcra();
            numAuditorias = menuAuditorias(aAuditorias, aColaboradores, aVulnerabilidades, numAuditorias, numVulnerabilidades, numColaboradores);
            break;

        case 2: //se escrever 2, limpa o ecra e abre o menuColaboradores
            limparEcra();
            numColaboradores = menuColaboradores(aColaboradores, numColaboradores);
            break;

        case 3: //se escrever 3, limpa o ecra e abre o menuVulnerabilidades
            limparEcra();
            numVulnerabilidades = menuVulnerabilidades(aVulnerabilidades, aAuditorias, numVulnerabilidades, numAuditorias);
            break;

        default: 
            break;
        }
    } while (input > 0);

    limparEcra();
    //guarda os numeros de registos no ficheiro
    guardarNumAudColVul(numAuditorias, numColaboradores, numVulnerabilidades);
    //guarda o array auditorias no ficheiro
    guardarArrayAuditorias(aAuditorias);
    //guarda o array colaboradores no ficheiro
    guardarArrayColaboradores(aColaboradores);
    //guarda o array vulnerabilidades no ficheiro
    guardarArrayVulnerabilidades(aVulnerabilidades);
}

//Menu Auditorias
int menuAuditorias(Auditoria auditorias[], Colaborador colaboradores[], Vulnerabilidade vulnerabilidades[], int n, int nVul, int nCol)
{
    int input; //variavel que guarda a escolha que o utilizador fez no menu

    //vai repetindo enquanto o utilizador nao escrever 0
    do
    {
        limparEcra();
        puts("+----------------------------------Menu--------------------------------+");
        printf("|%70s|\n", "");
        printf("|%70s|\n", "");
        printf("|%s%-69s|\n", " ", "1-Criar Auditoria");
        printf("|%s%-69s|\n", " ", "2-Listar Auditorias efetuadas por colaborador");
        printf("|%s%-69s|\n", " ", "3-Listar todas as Auditorias");
        printf("|%s%-69s|\n", " ", "4-Listar todas as Auditorias ordenadas por numero de vulnerabilidades");
        printf("|%70s|\n", "");
        printf("|%s%-69s|\n", " ", "O-Menu Principal");
        printf("|%70s|\n", "");
        puts("+----------------------------------------------------------------------+");
        scanf("%d", &input);
        //Limpar o que escrevemos
        getchar();
        switch (input)
        {
        case 0:
            break;

        case 1: //se escrever 1, limpa o ecra e abre a funcao criarAuditoria e o resultado e guardado na variavel n
            limparEcra();
            n = criarAuditoria(auditorias, colaboradores, vulnerabilidades, n, nVul, nCol);
            break;

        case 2: //se escrever 2, limpa o ecra e abre a funcao listarAuditoriasColaborador
            limparEcra();
            listarAuditoriasColaborador(auditorias, colaboradores, n, nCol);
            break;

        case 3: //se escrever 3, limpa o ecra e abre a funcao listarAuditorias
            limparEcra();
            listarAuditorias(auditorias, colaboradores, n);
            break;

        case 4: //se escrever 4, limpa o ecra e abre a funcao listarAuditoriasOrdenadas
            limparEcra();
            listarAuditoriasOrdenadas(auditorias, colaboradores, n);
            break;

        default: 
            break;
        }
    } while (input > 0);

    limparEcra();
    //retorna o numero de registos das auditorias
    return n;
}

//Menu Colaboradores
int menuColaboradores(Colaborador colaboradores[], int n)
{
    int input; //variavel que guarda a escolha que o utilizador fez no menu

    //vai repetindo enquanto o utilizador nao escrever 0
    do
    {

        limparEcra();
        puts("+---------------------------Menu Colaborador---------------------------+");
        printf("|%70s|\n", "");
        printf("|%70s|\n", "");
        printf("|%s%-69s|\n", " ", "1-Inserir Colaborador");
        printf("|%s%-69s|\n", " ", "2-Editar Colaborador");
        printf("|%s%-69s|\n", " ", "3-Remover Colaborador");
        printf("|%s%-69s|\n", " ", "4-Listar Colaboradores");
        printf("|%70s|\n", "");
        printf("|%s%-69s|\n", " ", "O-Menu Principal");
        printf("|%70s|\n", "");
        puts("+----------------------------------------------------------------------+");
        scanf("%d", &input);
        //Limpar o que escrevemos
        getchar();
        switch (input)
        {
        case 0:
            break;
        case 1: //se escrever 1, limpa o ecra e abre a funcao inserirColaborador e o resultado e guardado na variavel n
            limparEcra();
            n = inserirColaborador(colaboradores, n);
            
            break;
        case 2: //se escrever 2, limpa o ecra e abre a funcao editarColaborador
            limparEcra();
            editarColaborador(colaboradores, n);
            break;
        case 3: //se escrever 3, limpa o ecra e abre a funcao removerColaborador
            limparEcra();
            removerColaborador(colaboradores, n);
            break;
        case 4: //se escrever 4, limpa o ecra e abre a funcao listarColaboradores
            limparEcra();
            listarColaboradores(colaboradores, n);
            break;

        default: 
            break;
        }
    } while (input > 0);

    limparEcra();
    //retorna o numero de registos dos colaboradores
    return n;
}

//Menu Vulnerabilidades
int menuVulnerabilidades(Vulnerabilidade vulnerabilidades[], Auditoria auditorias[], int n, int nAud)
{
    int input; //variavel que guarda a escolha que o utilizador fez no menu

    //vai repetindo enquanto o utilizador nao escrever 0
    do
    {
        limparEcra();
        puts("+----------------------------------Menu--------------------------------+");
        printf("|%70s|\n", "");
        printf("|%70s|\n", "");
        printf("|%s%-69s|\n", " ", "1-Inserir Vulnerabilidade");
        printf("|%s%-69s|\n", " ", "2-Editar Vulnerabilidade");
        printf("|%s%-69s|\n", " ", "3-Adicionar Vulnerabilidade a uma auditoria");
        printf("|%s%-69s|\n", " ", "4-Remover Vulnerabilidade a uma auditoria");
        printf("|%s%-69s|\n", " ", "5-Listar Vulnerabilidades de uma auditoria");
        printf("|%s%-69s|\n", " ", "6-Listar todas as Vulnerabilidades");
        printf("|%70s|\n", "");
        printf("|%s%-69s|\n", " ", "O-Menu Principal");
        printf("|%70s|\n", "");
        puts("+----------------------------------------------------------------------+");
        scanf("%d", &input);
        //Limpar o que escrevemos
        getchar();

        switch (input)
        {
        case 0:
            break;

        case 1: //se escrever 1, limpa o ecra e abre a funcao inserirVulnerabilidade e o resultado e guardado na variavel n
            limparEcra();
            n = inserirVulnerabilidade(vulnerabilidades, n);
            break;

        case 2: //se escrever 2, limpa o ecra e abre a funcao editarColaborador
            limparEcra();
            editarVulnerabilidade(vulnerabilidades, n);
            break;

        case 3: //se escrever 3, limpa o ecra e abre a funcao adicionarVulAuditoria
            limparEcra();
            adicionarVulAuditoria(vulnerabilidades, auditorias, n, nAud);
            break;

        case 4: //se escrever 4, limpa o ecra e abre a funcao removerVulAuditoria
            limparEcra();
            removerVulAuditoria(vulnerabilidades, auditorias, n, nAud);
            break;

        case 5: //se escrever 5, limpa o ecra e abre a funcao listarVulAuditoria
            limparEcra();
            listarVulAuditoria(vulnerabilidades, auditorias, n, nAud);
            break;

        case 6: //se escrever 6, limpa o ecra e abre a funcao listarVulnerabilidades
            limparEcra();
            listarVulnerabilidades(vulnerabilidades, n);
            break;

        default: 
            break;
        }
    } while (input > 0);

    limparEcra();
    //retorna o numero de registos dos vulnerabilidades
    return n;
}
