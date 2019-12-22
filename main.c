#include <stdio.h>
#include <string.h>
#include "structs.h"

int main(int argc, char const *argv[])
{
    int menu;
    printf("Que dados pretende alterar?\n");
    printf("1 - Colaboradores\n");
    printf("2 - Vulnerabilidades\n");
    printf("3 - Auditorias\n");

    switch (menu)
    {
    case 1:
        menuCol();
        break;
    case 2:
        menuVuln();
        break;
    case 3:
        menuAuditorias();
        break;
    default:
        break;
    }
}