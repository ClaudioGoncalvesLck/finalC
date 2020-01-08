#include <stdio.h>
#include <string.h>
#include "structs.h"

int main(int argc, char const *argv[])
{
    int opcao;

    do
    {
        mainmenu();
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            menuCol();
            break;
        case 2:
            menuAuditorias();
            break;
        case 3:
            menuVuln();
            break;
        default:
            break;
        }
    } while (opcao != 0);
}