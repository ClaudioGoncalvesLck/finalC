#include "structs.h"
#include "stdlib.h"

void mainmenu()
{
    system("cls");
    printf("**********************************\n");

    printf("MAIN MENU\n\n");

    printf("1- Colaboradores\n");

    printf("2- Auditorias\n");

    printf("3- Vulnerabilidades\n\n");

    printf("**********************************\n");
};
void adicionarCol()
{
    Colaborador lista;
    dadosColaborador(&lista);
    registarCol(&lista, 2);
}
void dadosColaborador(Colaborador *lista)
{
    system("cls");
    printf("ID: ");
    scanf("%d", &lista->id);
    printf("Nome: ");
    scanf("%s", &lista->nome);
};
void registarCol(Colaborador *lista, int tam)
{
    FILE *file = fopen("colaboradores.bin", "wb+");
    int contador = 0;

    for (int i = 0; i < tam; i++)
    {
        contador++;
        fwrite(&lista[i], sizeof(Colaborador), 1, file);
    }

    fclose(file);
    printf("write %d items", contador);
};

void listarCol(Colaborador *lista)
{
    FILE *file = fopen("colaboradores.bin", "rb");
    Colaborador val;
    int contador = 0;
    while (fread(&val, sizeof(Colaborador), 1, file) > 0)
    {
        lista[contador] = val;
        printf("ID: %d", &lista[contador].id);
        printf("Nome: %s", &lista[contador].nome);
        contador++;
    }
    fclose(file);
    printf("read %d items ok\n", contador);
    getchar();
};

void editarCol(){

};
void removerCol(){

};
void adicionarVuln(){

};
void editarVuln(){

};
void removerVuln(){

};
void adicionarAud(){

};
void editarAud(){

};
void removerAud(){

};
void menuCol(Colaborador *lista)
{
    int opcao;
    do
    {
        system("cls");
        printf("**********************************\n");

        printf("MENU COLABORADORES\n\n");

        printf("1- Adicionar\n");

        printf("2- Editar\n");

        printf("3- Remover\n");

        printf("4 - Listar\n\n");

        printf("0 - Voltar ao Menu\n\n");

        printf("**********************************\n");

        scanf("%d", &opcao);
        switch (opcao)
        {
        case 0:
            return;
            break;
        case 1:
            adicionarCol();
            break;
        case 2:
            editarCol();
            break;
        case 3:
            removerCol();
            break;
        case 4:
            listarCol(lista);
            break;
        }
    } while (opcao != 0);
};

void menuVuln()
{
    int opcao;
    do
    {
        system("cls");
        printf("**********************************\n");

        printf("MENU VULNERABILIDADES\n\n");

        printf("1- Adicionar\n");

        printf("2- Editar\n");

        printf("3- Remover\n\n");

        printf("0 - Voltar ao Menu\n\n");

        printf("**********************************\n");

        scanf("%d", &opcao);
        switch (opcao)
        {
        case 0:
            return;
            break;
        case 1:
            adicionarVuln();
            break;
        case 2:
            editarVuln();
            break;
        case 3:
            removerVuln();
            break;
        }
    } while (opcao != 0);
};

void menuAuditorias()
{
    int opcao;
    do
    {
        system("cls");
        printf("**********************************\n");

        printf("MENU AUDITORIAS\n\n");

        printf("1- Adicionar\n");

        printf("2- Editar\n");

        printf("3- Remover\n\n");

        printf("0 - Voltar ao Menu\n\n");

        printf("**********************************\n");

        scanf("%d", &opcao);
        switch (opcao)
        {
        case 0:
            return;
            break;
        case 1:
            adicionarAud();
            break;
        case 2:
            editarAud();
            break;
        case 3:
            removerAud();
            break;
        }
    } while (opcao != 0);
};
