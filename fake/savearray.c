#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "header.h"

//Guardar o Array Colaboradores no ficheiro colaboradores.dat
void guardarArrayColaboradores(Colaborador colaboradores[])
{
    FILE *fp; //variavel para o ficheiro

    //abrir o ficheiro
    fp = fopen("colaboradores.dat", "wb");
    //se o valor da variavel for nulo, fecha o programa
    if (fp == NULL)
    {
        exit(1);
    }
    //escreve o array colaboradores no ficheiro
    fwrite(colaboradores, sizeof(Colaborador), TAM_COLABORADORES, fp);

    //fechar o ficheiro
    fclose(fp);
}

//Ler o Array Colaboradores do ficheiro colaboradores.dat
void lerArrayColaboradores(Colaborador colaboradores[])
{
    FILE *fp; //variavel para o ficheiro
    Colaborador auxArray[TAM_COLABORADORES]; //Array auxiliar para guardar a leitura dos dados para depois copiar

    //abrir o ficheiro
    fp = fopen("colaboradores.dat", "rb");

    //se o valor da variavel for nulo, fecha o programa
    if (fp == NULL)
    {
        exit(1);
    }

    //ler do ficheiro para guardar no auxArray
    fread(auxArray, sizeof(auxArray), 1, fp);

    //copiar o array auxArray para o array colaboradores
    for (int i = 0; i < TAM_COLABORADORES; i++)
    {
        colaboradores[i].codigo = auxArray[i].codigo;
        colaboradores[i].ativo = auxArray[i].ativo;
        strncpy(colaboradores[i].nome, auxArray[i].nome, 70); //copiar a string
    }

    //fechar o ficheiro
    fclose(fp);
}

//Guardar o Array Vulnerabilidades no ficheiro vulnerabilidades.dat
void guardarArrayVulnerabilidades(Vulnerabilidade vulnerabilidades[])
{
    FILE *fp; //variavel para o ficheiro

    //abrir o ficheiro
    fp = fopen("vulnerabilidades.dat", "wb");
    //se o valor da variavel for nulo, fecha o programa
    if (fp == NULL)
    {
        exit(1);
    }

    //escreve o array vulnerabilidades no ficheiro
    fwrite(vulnerabilidades, sizeof(Vulnerabilidade), TAM_VULNERABILIDADES, fp);

    //fechar o ficheiro
    fclose(fp);
}

//Ler o Array Vulnerabilidades do ficheiro vulnerabilidades.dat
void lerArrayVulnerabilidades(Vulnerabilidade vulnerabilidades[])
{
    FILE *fp; //variavel para o ficheiro
    Vulnerabilidade auxArray[TAM_VULNERABILIDADES]; //Array auxiliar para guardar a leitura dos dados para depois copiar
    
    //abrir o ficheiro
    fp = fopen("vulnerabilidades.dat", "rb");

    //se o valor da variavel for nulo, fecha o programa
    if (fp == NULL)
    {
        exit(1);
    }

    //ler do ficheiro para guardar no auxArray
    fread(auxArray, sizeof(auxArray), 1, fp);

    //copiar o array auxArray para o array vulnerabilidades
    for (int i = 0; i < TAM_VULNERABILIDADES; i++)
    {
        vulnerabilidades[i].codigo = auxArray[i].codigo;
        vulnerabilidades[i].ativo = auxArray[i].ativo;
        vulnerabilidades[i].nivel = auxArray[i].nivel;
        strncpy(vulnerabilidades[i].descricao, auxArray[i].descricao, 100); //copiar string
    }

    //fechar o ficheiro
    fclose(fp);
}

//Guardar o Array Auditorias no ficheiro auditorias.dat
void guardarArrayAuditorias(Auditoria auditorias[])
{
    FILE *fp; //variavel para o ficheiro

    //abrir o ficheiro
    fp = fopen("auditorias.dat", "wb");
    //se o valor da variavel for nulo, fecha o programa
    if (fp == NULL)
    {
        exit(1);
    }

    //escreve o array auditorias no ficheiro
    fwrite(auditorias, sizeof(Auditoria), TAM_AUDITORIAS, fp);

    //fechar o ficheiro
    fclose(fp);
}

//Ler o Array Auditorias do ficheiro auditorias.dat
void lerArrayAuditorias(Auditoria auditorias[])
{
    FILE *fp; //variavel para o ficheiro
    Auditoria auxArray[TAM_AUDITORIAS]; //Array auxiliar para guardar a leitura dos dados para depois copiar

    //abrir o ficheiro
    fp = fopen("auditorias.dat", "rb");

    //se o valor da variavel for nulo, fecha o programa
    if (fp == NULL)
    {
        exit(1);
    }

    //ler do ficheiro para guardar no auxArray
    fread(auxArray, sizeof(auxArray), 1, fp);

    //copiar o array auxArray para o array auditorias
    for (int i = 0; i < TAM_AUDITORIAS; i++)
    {
        auditorias[i].codigo = auxArray[i].codigo;
        auditorias[i].data = auxArray[i].data;
        auditorias[i].duracao = auxArray[i].duracao;
        auditorias[i].quantidadeVulnerabilidades = auxArray[i].quantidadeVulnerabilidades;
        auditorias[i].quantidadeVulRemovidas = auxArray[i].quantidadeVulRemovidas;
        auditorias[i].colaborador.codigo = auxArray[i].colaborador.codigo;
        for (int j = 0; j < TAM_VULNERABILIDADES; j++) //copiar as vulnerabilidades de uma auditoria
        {
            auditorias[i].vulnerabilidades[j].codigo = auxArray[i].vulnerabilidades[j].codigo;
            auditorias[i].vulnerabilidades[j].ativo = auxArray[i].vulnerabilidades[j].ativo;
        }
    }

    //fechar o ficheiro
    fclose(fp);
}

//Guardar as variaveis nAud, nCol e nVul no ficheiro nvariaveis.dat
void guardarNumAudColVul(int nAud, int nCol, int nVul)
{
    FILE *fp; //variavel para o ficheiro
    int arrN[3] = {nAud, nCol, nVul}; //array para guardar as variaveis

    //abrir o ficheiro
    fp = fopen("nvariaveis.dat", "wb");
    //se o valor da variavel for nulo, fecha o programa
    if (fp == NULL)
    {
        exit(1);
    }

    //escreve o array arrN no ficheiro
    fwrite(arrN, sizeof(arrN), 1, fp);

    //fechar o ficheiro
    fclose(fp);
}

//Ler as variaveis nAud, nCol e nVul no ficheiro nvariaveis.dat
void lerNumAudColVul(int arrNum[])
{
    FILE *fp; //variavel para o ficheiro
    int arrN[3]; //array para guardar as variaveis a serem lidas

    //abrir o ficheiro
    fp = fopen("nvariaveis.dat", "rb");
    //se o valor da variavel for nulo, fecha o programa
    if (fp == NULL)
    {
        exit(1);
    }

    //ler do ficheiro para guardar o array arrN
    fread(arrN, sizeof(arrN), 1, fp);

    //fechar o ficheiro
    fclose(fp);

    //Numero de Auditorias
    if (arrN[0] <= TAM_AUDITORIAS) //se o arrN[0] for maior que o TAM_AUDITORIAS, pode ter havido uma falha
    {                              //e se caso isso aconteca, coloca-se o numero 0
        arrNum[0] = arrN[0];
    } else
    {
        arrNum[0] = 0;
    }

    //Numero de Colaboradores
    if (arrN[1] <= TAM_COLABORADORES) //se o arrN[1] for maior que o TAM_COLABORADORES, pode ter havido uma falha
    {                                 //e se caso isso aconteca, coloca-se o numero 0
        arrNum[1] = arrN[1];
    }
    else
    {
        arrNum[1] = 0;
    }

    //Numero de Vulnerabilidades
    if (arrN[2] <= TAM_VULNERABILIDADES) //se o arrN[2] for maior que o TAM_VULNERABILIDADES, pode ter havido uma falha
    {                                    //e se caso isso aconteca, coloca-se o numero 0
        arrNum[2] = arrN[2];
    }
    else
    {
        arrNum[2] = 0;
    }

}
