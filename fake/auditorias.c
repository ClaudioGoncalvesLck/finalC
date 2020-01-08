#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "header.h"

//id é o numero de registos do array Auditorias, nVul é num. registos Vulnerabilidades,
//nCol é num. registos Colaboradores
Auditoria novaAuditoria(Colaborador colaboradores[], Vulnerabilidade vulnerabilidades[], int id, int nVul, int nCol)
{
    Auditoria auditoria;
    Colaborador colaborador;
    int lastVul = 0, i = 0, auxID;
    int posicaoCol = 0, posicaoVul = 0, idCol, idVul;

    puts("Criar Auditoria");
    puts("");

    auditoria.codigo = id + 1; //insere no codigo auditoria, o ultimo numero de registos mais 1
    
    do
    {
        if (posicaoCol == -1) //se repetir, vai limpar o ecra e depois
        {                     //vai mostrar ao utilizador que o ID foi invalido
            limparEcra();
            puts("Criar Auditoria");
            puts("");
            puts("ID invalido");
        }
        printf("Insira o ID do colaborador: ");
        scanf("%d", &idCol);
        getchar(); //Limpar o que escrevemos

        //chama a funcao pesquisarColaboradorID e retorna a posicao do colaborador no array
        posicaoCol = pesquisarColaboradorID(colaboradores, nCol, idCol); 
    } while (posicaoCol == -1);  //vai repetir se o ID que o utilizador escrever ser invalido

    auditoria.colaborador.codigo = idCol;

    printf("Data (Dia-Mes-Ano): ");
    scanf("%d-%d-%d", &auditoria.data.dia, &auditoria.data.mes, &auditoria.data.ano);

    printf("Duracao (minutos): ");
    scanf("%d", &auditoria.duracao);

    do
    {
        if (posicaoVul == -1) //se repetir, vai limpar o ecra, depois vai mostrar ao utilizador
        {                     //que o ID foi invalido e acaba a mostrar o que inseriu anteriormente
            limparEcra();
            puts("Criar Auditoria");
            puts("");
            puts("ID invalido");
            printf("Insira o ID do colaborador: %d\n", idCol);
        }
        printf("ID Vulnerabilidade que pretende adicionar: ");
        scanf("%d", &idVul);
        getchar(); //Limpar o que escrevemos

        //chama a funcao pesquisarVulnerabilidadeID e retorna a posicao da vulnerabilidade no array
        posicaoVul = pesquisarVulnerabilidadeID(vulnerabilidades, nVul, idVul);

    } while (posicaoVul == -1); //vai repetir se o ID que o utilizador escrever ser invalido

    //adicionar vulnerabilidade na auditoria, 0 é a primeiro indice
    auditoria.vulnerabilidades[0].codigo = idVul;

    //coloca 1 na quantidadeVulnerabilidades
    auditoria.quantidadeVulnerabilidades = 1;

    //iniciar a quantidade com um 0
    auditoria.quantidadeVulRemovidas = 0;

    return auditoria; //retorna a variavel auditoria
}

//Criar Auditorias, o n é o numero de registos ja feitos, nVul = num. vulnerabilidades,
//nCol = num. colaboradores e auditorias[] e o array
int criarAuditoria(Auditoria auditorias[], Colaborador colaboradores[], Vulnerabilidade vulnerabilidades[], int n, int nVul, int nCol)
{
    // Se o numero de registos for maior ou igual que TAM_AUDITORIAS ou nCol/nVul for igual a 0 vai retornar
    //o mesmo valor (num. Auditorias) e nao executa o resto para nao exceder o tamanho do array auditorias
    if (n >= TAM_AUDITORIAS || nCol == 0 || nVul == 0) 
    {                           
        return n;
    }

    //chama a funcao novaAuditoria e a funcao e retorna uma auditoria para adicionar ao array
    auditorias[n] = novaAuditoria(colaboradores, vulnerabilidades, n, nVul, nCol);
    
    n++; //Adiciona + 1

    return n; //Retorna o numero de registos
}

//Pesquisar Auditoria atraves do ID fornecido pelo utilizador
int pesquisarAuditoriaID(Auditoria auditorias[], int n, int id)
{
    int i = 0;

    if (id > n || 0 >= id) //se o id que o utilizador escreveu, for maior que o numero de registos
    {                      //ou que o id que escreveu e menor ou igual que 0, vai ser retornado -1 (erro, precisa de perguntar outra vez)
        return -1;
    }

    while (auditorias[i].codigo != id) //enquanto colaboradores[i].codigo for diferente ao id
    {                                  //que o utilizador escreveu vai sendo incrementado o i
        i++;
    }

    return i; //retorna a posicao da auditoria, que é precisa para ser utilizada no array
}

//Pesquisar na Auditoria fornecida pelo utilizador, encontrar a vulnerabilidade fornecida atraves do idVul
//id é a posicao da auditoria
int pesquisarAuditoriaVulID(Auditoria auditorias[], int nVul, int id, int idVul)
{
    int i = 0;


    if (idVul > nVul || 0 >= idVul) //se o id que o utilizador escreveu, for maior que o numero de registos
    {                               //ou que o id que escreveu e menor ou igual que 0, vai ser retornado -1 (erro, precisa de perguntar outra vez)
        return -1;
    }

    //enquanto auditorias[id].vulnerabilidades[i].codigo for diferente ao id que o utilizador 
    //escreveu vai sendo incrementado o i
    while (auditorias[id].vulnerabilidades[i].codigo != idVul)
    {
        i++;
    }

    //confirmar se o idVul e igual a auditorias[id].vulnerabilidades[i].codigo
    if (auditorias[id].vulnerabilidades[i].codigo == idVul)
    {
        return i; //retorna a posicao da vulnerabilidade
    }

    return -1; //erro

}

//Listar/Mostrar todas as Auditorias
void listarAuditorias(Auditoria auditorias[], Colaborador colaboradores[], int n)
{

    int i; //variavel para o ciclo FOR
    int auxCol; //variavel auxiliar para guardar o codigo do colaborador guardado nas auditorias

    puts("Lista de Auditorias");
    puts("");

    if (n > 0) //se o numero de registos for maior que 0, vai ser mostrada a lista de auditorias
    {          //senao é mostrada a mensagem em que nao existe auditorias

        printf("+--Codigo--+ID Col.+------------------------Nome-----------------------+---Data---+--Duracao-+-N.Vulner.-+\n");
        for (i = 0; i < n; i++) //enquanto i for menor que o numero de registos, vai ser mostrado as auditorias
        {                       //e é incrementado o i
            printf("| %-8d |", auditorias[i].codigo);
            printf(" %-6d|", auditorias[i].colaborador.codigo);
            auxCol = auditorias[i].colaborador.codigo;
            //mostra o nome do colaborador atraves do array Colaboradores
            //precisa de reduzir porque o indice e sempre menos -1 que o codigo do colaborador
            printf(" %-50s|", colaboradores[auxCol-1].nome); 
            //mostra o dia, mes e ano
            printf("%2d-%2d-%4d|", auditorias[i].data.dia, auditorias[i].data.mes, auditorias[i].data.ano);
            //mostra a duracao
            printf("%6dmin.|", auditorias[i].duracao);
            //mostra a quantidade de vulnerabilidades ativas
            printf(" %-10d|\n", auditorias[i].quantidadeVulnerabilidades);
        }
        printf("+----------+-------+---------------------------------------------------+----------+----------+-----------+\n");
    }
    else
    {
        puts("Nao existe Auditorias no momento");
    }
    getchar(); //Parar o programa, para o utilizador conseguir ver a lista/mensagem, e para proseguir
               //o utilizador apenas precisa de clicar no ENTER
}

//Listar/Mostrar as Auditorias de um colaborador atraves do id fornecido pelo utilizador
void listarAuditoriasColaborador(Auditoria auditorias[], Colaborador colaboradores[], int n, int nCol)
{
    int i, posicaoCol = 0, idCol;
    bool existe = false; //variavel para saber se o colaborador tem alguma auditoria com o codigo dele

    puts("Listar Auditorias efetuadas por colaborador");
    puts("");

    if (nCol > 0) //se tiver registos colaboradores, continua a funcao senao mostra que nao existe colaboradores
    {
        
        do
        {
            if (posicaoCol == -1) //se repetir, vai limpar o ecra e depois
            {                     //vai mostrar ao utilizador que o ID foi invalido
                limparEcra();
                puts("Listar Auditorias efetuadas por colaborador");
                puts("");
                puts("ID invalido");
            }
            printf("Insira o ID do colaborador: ");
            scanf("%d", &idCol);
            getchar(); //Limpa o que escrevemos
            //chama a funcao pesquisarColaboradorID e retorna a posicao do colaborador no array
            posicaoCol = pesquisarColaboradorID(colaboradores, nCol, idCol);
        } while (posicaoCol == -1); //vai repetir se o ID que o utilizador escrever ser invalido

        if (n > 0) //se o numero de registos for maior que 0, vai ser mostrada a lista de auditorias
        {          //senao é mostrada a mensagem em que nao existe auditorias
            limparEcra();
            printf("Lista de Auditorias do Colaborador %d\n", idCol);
            puts("");
            printf("+--Codigo--+---Data---+--Duracao-+------N.Vulner.-----+\n");
            for (i = 0; i < n; i++) //enquanto i for menor que o numero de registos, vai ser mostrado as auditorias
            {                       //e é incrementado o i

                //se o codigo do colaborador for igual ao id fornecido pelo utilizador vais ser mostrado os dados
                if (idCol == auditorias[i].colaborador.codigo)
                {
                    printf("| %-8d |", auditorias[i].codigo); //codigo da auditoria
                    //mostra o dia, mes e ano
                    printf("%2d-%2d-%4d|", auditorias[i].data.dia, auditorias[i].data.mes, auditorias[i].data.ano);
                    //mostra a duracao
                    printf("%6dmin.|", auditorias[i].duracao);
                    //mostra a quantidade de vulnerabilidades ativas
                    printf(" %-19d|\n", auditorias[i].quantidadeVulnerabilidades);
                    //muda para true porque quer dizer o colaborador tem pelo menos 1 auditoria encontrada
                    existe = true; 
                }
            }
            //se ainda estiver FALSE quer dizer que nao tem nenhuma auditoria registada por ele
            if (!existe) 
            {
                printf("|%18s%18s%17s|\n", " ", "Nao tem no momento", " ");
            }
            printf("+----------+----------+----------+--------------------+\n"); //fecha a tabela
        }

        //Parar o programa, para o utilizador conseguir ver a lista/mensagem, e para proseguir
        //o utilizador apenas precisa de clicar no ENTER
        getchar(); 

    } else
    {
        puts("Nao existe colaboradores no momento");

        getchar(); //Parar o programa para o utilizador conseguir ver a mensagem em que nao existe
                   //e para proseguir o utilizador apenas precisa de clicar no ENTER
    }
    
    

    
}

//Listar/Mostrar todas as Auditorias ordenadas(decrescente) atraves da quantidade de vulnerabilidades ativas
void listarAuditoriasOrdenadas(Auditoria auditorias[], Colaborador colaboradores[], int n)
{

    int i, j, auxCol;
    Auditoria aux /*Variavel auxiliar*/, auxAuditorias[n] /*Array auxiliar para ordenar*/;

    puts("Listar todas as Auditorias ordenadas por numero de vulnerabilidades");
    puts("");

    //Copiar para o array auxiliar
    for (i = 0; i < n; i++)
    {
        auxAuditorias[i].codigo = auditorias[i].codigo; //copia o codigo
        auxAuditorias[i].data = auditorias[i].data; //copia a data
        auxAuditorias[i].duracao = auditorias[i].duracao; //copia a duracao
        //copia a quantidade de vulnerabilidades ativas
        auxAuditorias[i].quantidadeVulnerabilidades = auditorias[i].quantidadeVulnerabilidades;
        //copia o codigo do utilizador
        auxAuditorias[i].colaborador.codigo = auditorias[i].colaborador.codigo;
    }

    for (i = 0; i < n - 1; i++) //enquanto i for menor que n(n-1 para nao tar a comparar 2 indices iguais)
    {
        for (j = i + 1; j < n; j++) //enquanto j for menor que n(i+1 para nao tar a comparar 2 indices iguais)
        {
            //se auxAuditorias[i] fosse menor que auxAuditorias[j]
            if (auxAuditorias[i].quantidadeVulnerabilidades < auxAuditorias[j].quantidadeVulnerabilidades)
            {
                aux = auxAuditorias[j]; //auxAuditorias[j] era guardada na variavel auxiliar
                auxAuditorias[j] = auxAuditorias[i]; //auxAuditorias[i] era guardada em auxAuditorias[i]
                auxAuditorias[i] = aux; //no fim era guardada em auxAuditorias[i] o aux
            }
        }
    }

    if (n > 0) //se o numero de registos for maior que 0, vai ser mostrada a lista de auditorias
    {          //senao é mostrada a mensagem em que nao existe auditorias
        printf("+--Codigo--+ID Col.+------------------------Nome-----------------------+---Data---+--Duracao-+-N.Vulner.-+\n");
        for (i = 0; i < n; i++)//enquanto i for menor que o numero de registos, vai ser mostrado as auditorias
        {                       //e é incrementado o i
            printf("| %-8d |", auxAuditorias[i].codigo);
            printf(" %-6d|", auxAuditorias[i].colaborador.codigo);
            auxCol = auxAuditorias[i].colaborador.codigo;
            //precisa de reduzir porque o indice e sempre menos -1 que o codigo do colaborador
            printf(" %-50s|", colaboradores[auxCol - 1].nome);
            printf("%2d-%2d-%4d|", auxAuditorias[i].data.dia, auxAuditorias[i].data.mes, auxAuditorias[i].data.ano);
            printf("%6dmin.|", auxAuditorias[i].duracao);
            printf(" %-10d|\n", auxAuditorias[i].quantidadeVulnerabilidades);
        }
        printf("+----------+-------+---------------------------------------------------+----------+----------+-----------+\n");
    }
    else
    {
        puts("Nao existe auditorias no momento");
    }
    getchar(); //Parar o programa, para o utilizador conseguir ver a lista/mensagem, e para proseguir
               //o utilizador apenas precisa de clicar no ENTER
}

//Ver a auditoria com mais vulnerabilidades
int auditoriaComMaisVulnerabilidades(Auditoria auditorias[], int n)
{

    int indiceAuxQt, i, auxQt = 0;

    if (n == 0) //se numero de auditorias for igual a 0, vai retornar 0(quer dizer que nao existe auditorias)
    {
        return 0;
    }

    for (i = 0; i < n; i++) //enquanto i é menor que n, o i e incrementado
    {
        //se a auxQt e menor que auditorias[i].quantidadeVulnerabilidades é adicionado na variavel
        //auxQt o valor de auditorias[i].quantidadeVulnerabilidades e depois e guardado o indice atraves
        //da variavel indiceAuxQt
        if (auxQt < auditorias[i].quantidadeVulnerabilidades)
        {
            auxQt = auditorias[i].quantidadeVulnerabilidades;
            indiceAuxQt = i;
        }
    }

    return indiceAuxQt; //retorna o indice da auditoria com mais vulnerabilidades
}

//Ver a auditoria com menos vulnerabilidades
int auditoriaComMenosVulnerabilidades(Auditoria auditorias[], int n)
{

    int indiceAuxQt, i, auxQt = 999;

    if (n == 0) //se numero de auditorias for igual a 0, vai retornar 0(quer dizer que nao existe auditorias)
    {
        return 0;
    }

    for (i = 0; i < n; i++) //enquanto i é menor que n, o i e incrementado
    {
        //se a auxQt é maior que auditorias[i].quantidadeVulnerabilidades é adicionado na variavel
        //auxQt o valor de auditorias[i].quantidadeVulnerabilidades e depois e guardado o indice atraves
        //da variavel indiceAuxQt
        if (auxQt > auditorias[i].quantidadeVulnerabilidades)
        {
            auxQt = auditorias[i].quantidadeVulnerabilidades;
            indiceAuxQt = i;
        }
    }

    return indiceAuxQt; //retorna o indice da auditoria com menos vulnerabilidades
}

//fazer a media de vulnerabilidades das auditorias
double mediaVulAuditoria(Auditoria auditorias[], int n){
    int soma=0;
    double media;

    //enquanto i menor que n, incrementa o i
    for (int i = 0; i < n; i++) 
    {
        //somar a quantidade de vulnerabilidades (total de vulnerabilidades)
        soma=soma+auditorias[i].quantidadeVulnerabilidades;
    }
    
    //calcula a media. Double serve para converter a variavel soma em Double
    media = (double)soma / n;

    return media; //retorna a media
}