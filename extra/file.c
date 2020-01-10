#include <stdio.h>
#include <stdlib.h>

typedef struct sListInt
{
    int val;
    int id;
} ListInt;

void save(ListInt *lst, int tam)
{
    FILE *file = fopen("file.bin", "wb+");
    int cnt = 0;

    if (file == NULL || lst == NULL)
    {
        return;
    }

    for (int i = 0; i < tam; i++)
    {
        cnt++;
        fwrite(&lst[i], sizeof(ListInt), 1, file);
    }
    fclose(file);
    printf("write %d items", cnt);
}

void read(ListInt *lst, int tam)
{
    FILE *file = fopen("file.bin", "rb");
    ListInt val;
    int cnt = 0;
    while (fread(&val, sizeof(ListInt), 1, file) > 0)
    {
        lst[cnt] = val;
        cnt++;
    }
    fclose(file);
    printf("read %d items ok\n", cnt);
}

int main(int argc, char *argv[])
{
    ListInt head[5];
    for (int i = 0; i < 5; i++)
    {
        head[i].val = i * 10;
        head[i].id = i;
    }
    //printf("--save list\n");
    //save(head, 5);

    ListInt head[5];
    read(head, 0);
    for (int i = 0; i < 5; i++)
    {
        printf("%d\n", head[i].val);
    }
    return 0;
}