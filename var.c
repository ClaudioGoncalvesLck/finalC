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
void adicionarCol(){

};
void editarCol(){

};
void removerCol(){

};
void menuCol()
{
    int opcao;
    do
    {
        system("cls");
        printf("**********************************\n");

        printf("MENU COLABORADORES\n\n");

        printf("1- Adicionar\n");

        printf("2- Editar\n");

        printf("3- Remover\n\n");

        printf("**********************************\n");

        scanf("%d", opcao);
        switch (opcao)
        {
        case 0:
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

        printf("**********************************\n");

        scanf("%d", opcao);
        if (opcao = 0)
        {
            mainmenu();
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

        printf("**********************************\n");

        scanf("%d", opcao);
        if (opcao = 0)
        {
            mainmenu();
        }
    } while (opcao != 0);
};
