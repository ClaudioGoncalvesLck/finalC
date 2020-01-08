#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "header.h"

Colaborador novoColaborador(int id) //id é o numero de registos do array Colaboradores
{

    Colaborador colaborador;

    puts("Inserir Colaborador");
    puts("");

    colaborador.codigo = id + 1; //insere no codigo colaborador, o ultimo numero de registos mais 1
    printf("Nome: ");
    fgets(colaborador.nome, 70, stdin);  //le o que o utilizador escreve no maximo 70 chars e guarda na variavel colaborador.nome
    colaborador.nome[strlen(colaborador.nome) - 1] = '\0'; // retira o \n, porque o fgets le o ENTER, e por isso e preciso remove-lo
    colaborador.ativo = true; //coloca-se o colaborador Ativo

    return colaborador; //retorna a variavel colaborador
}

//Inserir colaboradores, o n é o numero de registos ja feitos e colaboradores[] e o array
int inserirColaborador(Colaborador colaboradores[], int n)
{
    if (n >= TAM_COLABORADORES) // Se o numero de registos for maior ou igual que TAM_COLABORADORES vai retornar
    {                           // o mesmo valor e nao executa o resto para nao exceder o tamanho do array colaboradores
        return n;
    }
    colaboradores[n] = novoColaborador(n); //chama a funcao novoColaborador e a funcao
                                           //retorna um colaborador para adicionar ao array
    n++; //adiciona + 1                                                            

    return n; //Retorna o numero de registos
}

//pesquisar o indice do colaborador atraves do id que utilizador inseriu
int pesquisarColaboradorID(Colaborador colaboradores[], int n, int id)
{
    int i = 0;

    if (id > n || 0 >= id) //se o id que o utilizador escreveu, for maior que o numero de registos
    {                      //ou que o id que escreveu e menor ou igual que 0, vai ser retornado -1 (erro, precisa de perguntar outra vez)
        return -1;
    }

    while (colaboradores[i].codigo != id) //enquanto colaboradores[i].codigo for diferente ao id
    {                                     //que o utilizador escreveu vai sendo incrementado o i
        i++;
    }

    return i; //retorna a posicao do colaborador, que é precisa para ser utilizada no array
}

//Editar Colaborador, o n é o numero de registos dos colaboradores e colaboradores[] e o array
void editarColaborador(Colaborador colaboradores[], int n) 
{
    int posicao = 0, id;

    puts("Editar Colaborador");
    puts("");

    if (n > 0) //se tiver registos colaboradores, continua a funcao senao mostra que nao existe colaboradores
    {
        do
        {
            if (posicao == -1) //se repetir, vai limpar o ecra e depois
            {                  //vai mostrar ao utilizador que o ID foi invalido
                limparEcra();
                puts("Editar Colaborador");
                puts("");
                puts("ID invalido");
            }
            printf("Insira o ID do colaborador a procurar: ");
            scanf("%d", &id);
            getchar(); //Limpar o que escrevemos
            posicao = pesquisarColaboradorID(colaboradores, n, id); //chama a funcao pesquisarColaboradorID e retorna a posicao do colaborador no array
        
        } while (posicao == -1);  //vai repetir se o ID que o utilizador escrever ser invalido

        printf("Novo nome do colaborador: ");
        fgets(colaboradores[posicao].nome, 70, stdin); //le o que o utilizador escreve no maximo 70 chars e guarda na variavel colaborador[posicao].nome
        colaboradores[posicao].nome[strlen(colaboradores[posicao].nome) - 1] = '\0'; // retira o \n, porque o fgets le o ENTER, e por isso e preciso remove-lo
    } else
    {
        puts("Nao existe colaboradores no momento");

        getchar(); //Parar o programa para o utilizador conseguir ver a mensagem em que nao existe
                   //e para proseguir o utilizador apenas precisa de clicar no ENTER
    }
    
    

    
}

//Remover Colaborador(desativar atraves do campo ATIVO), o n é o numero de registos dos colaboradores e colaboradores[] e o array
void removerColaborador(Colaborador colaboradores[], int n)
{
    int posicao = 0, id;

    puts("Remover Colaborador");
    puts("");

    if (n > 0) //se tiver registos colaboradores, continua a funcao senao mostra que nao existe colaboradores
    {
        do
        {
            if (posicao == -1) //se repetir, vai limpar o ecra e depois
            {                  //vai mostrar ao utilizador que o ID foi invalido
                limparEcra();
                puts("Remover Colaborador");
                puts("");
                puts("ID invalido");
            }
            printf("Insira o ID do colaborador a remover: ");
            scanf("%d", &id);
            getchar(); //Limpa o que escrevemos
            posicao = pesquisarColaboradorID(colaboradores, n, id); //chama a funcao pesquisarColaboradorID e retorna a posicao do colaborador no array
        
        } while (posicao == -1); //vai repetir se o ID que o utilizador escrever ser invalido.

        if (posicao != -1 && colaboradores[posicao].ativo) //se a posicao for diferente e o colaborador da posicao procurada
        {                                                  //estiver ativo, o colaborador vai ser alterado para ativo=falso
            colaboradores[posicao].ativo = false;
        }

    } else
    {
        puts("Nao existe colaboradores no momento");

        getchar(); //Parar o programa para o utilizador conseguir ver a mensagem em que nao existe
                   //e para proseguir o utilizador apenas precisa de clicar no ENTER
    }
    
    

    
}

//Listar/Mostrar os Colaboradores existentes (ativos/desativado), o n é o numero de registos feitos aos colaboradores e colaboradores[] e o array
void listarColaboradores(Colaborador colaboradores[], int n)
{
    int i; //variavel para o ciclo FOR
    
    puts("Lista de Colaboradores");
    puts("");

    if (n > 0) //se o numero de registos for maior que 0, vai ser mostrada a lista de colaboradores
    {          //senao é mostrada a mensagem em que nao existe colaboradores
        printf("+--Codigo--+--------------------Nome---------------------------+--Estado---+\n");
        for (i = 0; i < n; i++) //enquanto i for menor que o numero de registos, vai ser mostrado os colaboradores
        {                       //e é incrementado o i
            printf("|  %-6d  |", colaboradores[i].codigo); //mostrar o codigo do colaborador
            printf(" %-50s", colaboradores[i].nome); //mostrar o nome do colaborador, com espaco reservado de 70 chars, em que comeca a mostrar da esquerda
            if (colaboradores[i].ativo) //se no campo ativo tiver True, quer dizer que o colaborador está ativo
            {                           //senao o colaborador esta desativado
                printf("| %-10s|\n", "Ativo");
            }
            else
            {
                printf("| %-10s|\n", "Desativado");
            }
        }

        printf("+----------+---------------------------------------------------+-----------+\n");
    }
    else
    {
        puts("Nao existe colaboradores no momento");
    }
    getchar(); //Parar o programa, para o utilizador conseguir ver a lista/mensagem, e para proseguir
               //o utilizador apenas precisa de clicar no ENTER
}              
