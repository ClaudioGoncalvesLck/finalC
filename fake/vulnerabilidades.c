#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "header.h"

Vulnerabilidade novaVulnerabilidade(int id) //id é o numero de registos do array vulnerabilidades
{

    Vulnerabilidade vulnerabilidade;
    int auxNivel; //variavel auxiliar para o ciclo DO...WHILE

    puts("Inserir Vulnerabilidade");
    puts("");

    vulnerabilidade.codigo = id + 1; //insere no codigo, o ultimo numero de registos mais 1
    printf("Descricao: ");
    fgets(vulnerabilidade.descricao, 100, stdin); //le o que o utilizador escreve no maximo 100 chars e guarda na variavel vulnerabilidade.descricao
    vulnerabilidade.descricao[strlen(vulnerabilidade.descricao) - 1] = '\0'; // retira o \n, porque o fgets le o ENTER, e por isso e preciso remove-lo
    puts("----------NIVEL----------");
    puts("Nivel 1 = Baixo");
    puts("Nivel 2 = Moderado");
    puts("Nivel 3 = Elevado");
    puts("-------------------------");
    do
    {
        printf("Nivel: ");
        scanf("%d", &auxNivel);
        getchar(); //Limpar o que escrevemos
    } while (1 > auxNivel || auxNivel > 3); //vai repetir se o utilizador colocar menos de 1 ou mais que 3
    
    vulnerabilidade.nivel = auxNivel; //insere no nivel, o que esta na variavel auxNivel, que vem DO...WHILE
    

    vulnerabilidade.ativo = true; //coloca a vulnerabilidade ativa

    return vulnerabilidade; //retorna a variavel vulnerabilidade com os dados que o utilizador inseriu


}

//Inserir vulnerabilidades, o n é o numero de registos ja feitos e vulnerabilidades[] e o array
int inserirVulnerabilidade(Vulnerabilidade vulnerabilidades[], int n)
{
    if (n >= TAM_VULNERABILIDADES) //Se o numero de registos for maior ou igual que TAM_VULNERABILIDADES vai retornar
    {                              //o mesmo valor e nao executa o resto para nao exceder o tamanho do array vulnerabilidades
        return n;
    }
    vulnerabilidades[n] = novaVulnerabilidade(n); //chama a funcao novavulnerabilidade e a funcao
                                                  //retorna uma vulnerabilidade para adicionar ao array

    n++; //adiciona +1

    return n; //retorna o numero de registos
}

//pesquisar o indice da vulnerabilidade atraves do id que utilizador inseriu
int pesquisarVulnerabilidadeID(Vulnerabilidade vulnerabilidades[], int n, int id)
{
    int i = 0;

    if (id > n || 0 >= id) //se o id que o utilizador escreveu, for maior que o numero de registos
    {                      //ou que o id que escreveu e menor ou igual que 0, vai ser retornado -1 (erro, precisa de perguntar outra vez)
        return -1;
    }

    while (vulnerabilidades[i].codigo != id) //enquanto vulnerabilidades[i].codigo for diferente ao id
    {                                        //que o utilizador escreveu vai sendo incrementado o i
        i++;
    }

    return i; //retorna a posicao da vulnerabilidade, que é precisa para ser utilizada no array
}

//Editar Vulnerabilidade, o n é o numero de registos das vulnerabilidades e vulnerabilidades[] e o array
void editarVulnerabilidade(Vulnerabilidade vulnerabilidades[], int n)
{
    int i = 0, posicao = 0, id, auxNivel;

    puts("Editar Vulnerabilidade");
    puts("");

    if (n > 0) //se tiver registos vulnerabilidades, continua a funcao senao mostra que nao existe vulnerabilidades
    {
        do
        {
            if (posicao == -1) //se repetir, vai limpar o ecra e depois
            {                  //vai mostrar ao utilizador que o ID foi invalido
                limparEcra();
                puts("Editar Vulnerabilidade");
                puts("");
                puts("ID invalido");
            }
            printf("Insira o ID da vulnerabilidade a procurar: ");
            scanf("%d", &id);
            getchar(); //Limpar o que escrevemos
            posicao = pesquisarVulnerabilidadeID(vulnerabilidades, n, id); //chama a funcao pesquisarVulnerabilidadeID e retorna a posicao da vulnerabilidade no array
        
        } while (posicao == -1); //vai repetir se o ID que o utilizador escrever ser invalido.

        printf("Nova descricao da vulnerabilidade: ");
        fgets(vulnerabilidades[posicao].descricao, 100, stdin); //le o que o utilizador escreve no maximo 100 chars e guarda na variavel vulnerabilidades[posicao].descricao
        vulnerabilidades[posicao].descricao[strlen(vulnerabilidades[posicao].descricao) - 1] = '\0'; // retira o \n, porque o fgets le o ENTER, e por isso e preciso remove-lo

        puts("----------NIVEL----------");
        puts("Nivel 1 = Baixo");
        puts("Nivel 2 = Moderado");
        puts("Nivel 3 = Elevado");
        puts("-------------------------");
        do
        {
            printf("Nivel: ");
            scanf("%d", &auxNivel);
            getchar(); //Limpar o que escrevemos

        } while (1 > auxNivel || auxNivel > 3); //vai repetir se o utilizador colocar menos de 1 ou mais que 3

        vulnerabilidades[posicao].nivel = auxNivel; //insere no nivel, o que esta na variavel auxNivel, que vem DO...WHILE
    } else
    {
        puts("Nao existe vulnerabilidades no momento");

        getchar(); //Parar o programa para o utilizador conseguir ver a mensagem em que nao existe
                   //e para proseguir o utilizador apenas precisa de clicar no ENTER
    }
    
}

//Adicionar uma Vulnerabilidade numa Auditoria, o n é o numero de registos das vulnerabilidades e nAud é o número de registos das auditorias
void adicionarVulAuditoria(Vulnerabilidade vulnerabilidades[], Auditoria auditorias[], int n, int nAud)
{
    int i = 0, posicaoAud = 0, idAud, idVul, auxQtVul, posicaoVul = 0, quantVuleQuantVulRem=0;
    bool podeAdicionar = true;

    puts("Adicionar Vulnerabilidade a uma auditoria");
    puts("");

    if (nAud > 0) //se tiver registos auditoria, continua a funcao senao mostra que nao existe auditorias
    {
        do
        {
            if (posicaoAud == -1) //se repetir, vai limpar o ecra e depois
            {                  //vai mostrar ao utilizador que o ID foi invalido
                limparEcra();
                puts("Adicionar Vulnerabilidade a uma auditoria");
                puts("");
                puts("ID invalido");
            }
            printf("Insira o ID da Autoria: ");
            scanf("%d", &idAud);
            getchar(); //Limpar o que escrevemos
            posicaoAud = pesquisarAuditoriaID(auditorias, nAud, idAud); //chama a funcao pesquisarAuditoriaID
                                                                        //e retorna a posicao da auditoria no array

        } while (posicaoAud == -1); //vai repetir se o ID que o utilizador escrever ser invalido

        do
        {
            if (posicaoVul == -1) //se repetir, vai limpar o ecra, depois vai mostrar ao utilizador
            {                     //que o ID foi invalido e acaba a mostrar o que inseriu anteriormente
                limparEcra();
                puts("Adicionar Vulnerabilidade a uma auditoria");
                puts("");
                printf("Insira o ID da Autoria: %d\n", idAud);
                puts("ID invalido");
            }
            printf("ID Vulnerabilidade que pretende adicionar: ");
            scanf("%d", &idVul);
            getchar(); //Limpar o que escrevemos

            //chama a funcao pesquisarVulnerabilidadeID e retorna a posicao da vulnerabilidade no array
            posicaoVul = pesquisarVulnerabilidadeID(vulnerabilidades, n, idVul); 
            
        } while (posicaoVul == -1); //vai repetir se o ID que o utilizador escrever ser invalido

        //total de vulnerabilidades na auditoria
        quantVuleQuantVulRem = auditorias[posicaoAud].quantidadeVulnerabilidades + auditorias[posicaoAud].quantidadeVulRemovidas;

        //verificar se o ID que o utilizador escreveu nao existe na auditoria
        //enquanto i e menor que quantVuleQuantVulRem e podeAdicionar = true
        while (i < quantVuleQuantVulRem && podeAdicionar)
        {
            if (auditorias[posicaoAud].vulnerabilidades[i].codigo == idVul)
            {
                podeAdicionar = false;
            }

            i++;
        }

        if (podeAdicionar)
        {
            //guarda a quantidade de vulnerabilidades ativas
            auxQtVul = auditorias[posicaoAud].quantidadeVulnerabilidades;

            //insere o id vulnerabilidade na auditoria que disse atraves do id
            auditorias[posicaoAud].vulnerabilidades[quantVuleQuantVulRem].codigo = idVul;

            //colocar a vulnerabilidade ativa
            auditorias[posicaoAud].vulnerabilidades[quantVuleQuantVulRem].ativo = true;

            //incrementa a quantidade vulnerabilidades na auditoria
            auditorias[posicaoAud].quantidadeVulnerabilidades = auxQtVul + 1;
        } else {
            printf("A vulnerabilidade que tentou adicionar ja existe.");

            getchar(); //Parar o programa para o utilizador conseguir ver a mensagem em que nao conseguir
            //adicionar pois já existe, e para proseguir o utilizador apenas precisa de clicar no ENTER
        }
    } else
    {
        puts("Nao existe auditorias no momento");

        getchar(); //Parar o programa para o utilizador conseguir ver a mensagem em que nao existe
                   //e para proseguir o utilizador apenas precisa de clicar no ENTER
    }
    
}

//Remover uma Vulnerabilidade numa Auditoria, o n é o numero de registos das vulnerabilidades e nAud é o número de registos das auditorias
void removerVulAuditoria(Vulnerabilidade vulnerabilidades[], Auditoria auditorias[], int n, int nAud)
{
    int i = 0, posicaoAud = 0, posicaoVul=0, idAud, idVul, auxQtVul = 0;

    puts("Remover Vulnerabilidade a uma auditoria");
    puts("");

    if (nAud > 0) //se tiver registos auditoria, continua a funcao senao mostra que nao existe auditorias
    {
        do
        {
            if (posicaoAud == -1) //se repetir, vai limpar o ecra e depois
            {                     //vai mostrar ao utilizador que o ID foi invalido
                limparEcra();
                puts("Remover Vulnerabilidade a uma auditoria");
                puts("");
                puts("ID invalido");
            }
            printf("Insira o ID da Autoria: ");
            scanf("%d", &idAud);
            getchar(); //Limpar o que escrevemos
            posicaoAud = pesquisarAuditoriaID(auditorias, nAud, idAud); //chama a funcao pesquisarAuditoriaID
                                                                        //e retorna a posicao da auditoria no array

        } while (posicaoAud == -1); //vai repetir se o ID que o utilizador escrever ser invalido

        do
        {
            if (posicaoVul == -1) //se repetir, vai limpar o ecra, depois vai mostrar ao utilizador
            {                     //que o ID foi invalido e acaba a mostrar o que inseriu anteriormente
                limparEcra();
                puts("Remover Vulnerabilidade a uma auditoria");
                puts("");
                printf("Insira o ID da Autoria: %d\n", idAud);
                puts("ID invalido");
            }
            printf("ID Vulnerabilidade que pretende remover: ");
            scanf("%d", &idVul);
            getchar(); //Limpar o que escrevemos

            //chama a funcao pesquisarAuditoriaVulID e retorna a posicao da vulnerabilidade
            //no array de vulnerabilidades na Auditorias
            posicaoVul = pesquisarAuditoriaVulID(auditorias, n, posicaoAud, idVul);
        } while (posicaoVul == -1); //vai repetir se o ID que o utilizador escrever ser invalido

        //guarda a quantidade de vulnerabilidades
        auxQtVul = auditorias[posicaoAud].quantidadeVulnerabilidades;

        //se for true muda para false. Este ciclo previne para nao incrementar quantidade
        //vulnerabilidades removidas a mais,pois ja esta removida(false)
        if (auditorias[posicaoAud].vulnerabilidades[posicaoVul].ativo) 
        {
            //coloca no campo ativo = false a vulnerabilidade, isto quer dizer que esta desativada
            auditorias[posicaoAud].vulnerabilidades[posicaoVul].ativo = false; 
            
            //reduz o numero de vulnerabilidades
            auxQtVul = auxQtVul - 1;

            //guarda o numero de vulnerabilidades
            auditorias[posicaoAud].quantidadeVulnerabilidades = auxQtVul;

            //incrementa a qt de vulnerabilidades removidas
            auditorias[posicaoAud].quantidadeVulRemovidas = auditorias[posicaoAud].quantidadeVulRemovidas + 1;
        } else
        {
            printf("A vulnerabilidade que tentou remover ja esta removida.");

            getchar(); //Parar o programa para o utilizador conseguir ver a mensagem em que nao conseguir
                       //remover pois já esta removida, e para proseguir o utilizador apenas precisa de clicar no ENTER
        }
    } else
    {
        puts("Nao existe auditorias no momento");

        getchar(); //Parar o programa para o utilizador conseguir ver a mensagem em que nao existe
                   //e para proseguir o utilizador apenas precisa de clicar no ENTER
    }   
}

//Listar/Mostrar as Vulnerabilidades, o n é o numero de registos feitos as vulnerabilidades e vulnerabilidades[] e o array
void listarVulnerabilidades(Vulnerabilidade vulnerabilidades[], int n)
{

    int i; //variavel para o ciclo FOR

    puts("Lista de Vulnerabilidades");
    puts("");

    if (n > 0) //se o numero de registos for maior que 0, vai ser mostrada a lista de vulnerabilidades
    {          //senao é mostrada a mensagem em que nao existe vulnerabilidades
        printf("+--Codigo--+-------------------------------Descricao------------------------------+--Nivel---+\n");
        for (i = 0; i < n; i++) //enquanto i for menor que o numero de registos, vai ser mostrado as vulnerabilidades
        {                       //e é incrementado o i
            printf("|  %-6d  |", vulnerabilidades[i].codigo); //mostra o codigo da vulnerabilidade
            printf(" %-68s ", vulnerabilidades[i].descricao);   //mostra a descricao, com espaco reservado de 100 chars, em que comeca a mostrar da esquerda
            switch (vulnerabilidades[i].nivel) //mostra o nivel da vul. se for 1 escreve baixo, 2 = moderado e 3 = elevado
            {
            case 1:
                printf("| %-9s|\n", "Baixo");
                break;
            case 2:
                printf("| %-9s|\n", "Moderado");
                break;
            case 3:
                printf("| %-9s|\n", "Elevado");
                break;

            default:
                break;
            }
            
        }

        printf("+----------+----------------------------------------------------------------------+----------+\n");
    }
    else
    {
        puts("Nao existe vulnerabilidades no momento");
    }
    getchar(); //Parar o programa, para o utilizador conseguir ver a lista/mensagem, e para proseguir
               //o utilizador apenas precisa de clicar no ENTER
}              

void listarVulAuditoria(Vulnerabilidade vulnerabilidades[], Auditoria auditorias[], int n, int nAud)
{

    int posicaoAud = 0, idAud, i, quantVuleQuantVulRem, codigoVul;

    puts("Lista de Vulnerabilidades de uma auditoria");
    puts("");

    //se o numero de registos de auditorias for maior que 0 vai perguntar qual e a auditoria e depois mostra-la
    //senao e mostrada que nao existe auditorias
    if (nAud > 0)
    {
        do
        {
            if (posicaoAud == -1) //se repetir, vai limpar o ecra e depois
            {                     //vai mostrar ao utilizador que o ID foi invalido
                limparEcra();
                puts("Lista de Vulnerabilidades de uma auditoria");
                puts("");
                puts("ID invalido");
            }
            printf("Insira o ID da Autoria: ");
            scanf("%d", &idAud);
            getchar(); //Limpar o que escrevemos

            posicaoAud = pesquisarAuditoriaID(auditorias, nAud, idAud); //chama a funcao pesquisarAuditoriaID
                                                                        //e retorna a posicao da auditoria no array

        } while (posicaoAud == -1); //vai repetir se o ID que o utilizador escrever ser invalido

        //total de vulnerabilidades na auditoria
        quantVuleQuantVulRem = auditorias[posicaoAud].quantidadeVulnerabilidades + auditorias[posicaoAud].quantidadeVulRemovidas;

        limparEcra();

        printf("Lista de Vulnerabilidades da Auditoria %d\n", idAud);
        puts("");
        printf("+--Codigo--+-----------------------------Vulnerabilidade---------------------------+--Nivel---+---Estado--+\n");
        for (i = 0; i < quantVuleQuantVulRem; i++)
        {
            //indice da vulnerabilidade
            codigoVul = auditorias[posicaoAud].vulnerabilidades[i].codigo; 
            printf("|  %6d  |", codigoVul); //mostra o codigo da vulnerabilidade(tem que adicionar +1 pois codigoVul e um indice)
            //mostra a descricao(codigoVul é o id e por isso tem que reduzir 1 por causa do indice)
            printf(" %-70s", vulnerabilidades[codigoVul-1].descricao);
            //mostra o nivel da vulnerabilidade. se for 1 escreve baixo, 2 = moderado e 3 = elevado
            //(codigoVul é o id e por isso tem que reduzir 1 por causa do indice)
            switch (vulnerabilidades[codigoVul-1].nivel)
            {
            case 1:
                printf("| %-9s|", "Baixo");
                break;
            case 2:
                printf("| %-9s|", "Moderado");
                break;
            case 3:
                printf("| %-9s|", "Elevado");
                break;

            default:
                break;
            }
            //se no campo ativo tiver True, quer dizer que a vulnerabilidade está ativo senao a vulnerabilidade esta desativado
            if (auditorias[posicaoAud].vulnerabilidades[i].ativo) 
            {                           
                printf(" %-10s|\n", "Ativo");
            }
            else
            {
                printf(" %-10s|\n", "Desativado");
            }
        }
        printf("+----------+-----------------------------------------------------------------------+----------+-----------+\n");
    } else
    {
        puts("Nao existe auditorias no momento");
    }

    getchar(); //Parar o programa, para o utilizador conseguir ver a lista/mensagem, e para proseguir
               //o utilizador apenas precisa de clicar no ENTER

}