#pragma once
int ABRIR_MAPA(char mapa[SIZE][SIZE], int tipo)
{
    FILE* fmapa;
    int i = 0, j = 0;
    char trash;
    if (tipo == 1)
    {
        fmapa = fopen("Archivos/Mapa_inicial.txt", "r");
        if (fmapa == NULL)
        {
            printf("ERROR");
            return 0;
        }
    }
    else
    {
        fmapa = fopen("Archivos/Mapa_jefe.txt", "r");
        if (fmapa == NULL)
        {
            printf("ERROR");
            return 0;
        }
    }

    if (tipo == 3)
    {
        fmapa = fopen("Archivos/wall_enemy.txt", "r");
        if (fmapa == NULL)
        {
            printf("ERROR");
            return 0;
        }
    }

    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
            fscanf(fmapa, "%c", &mapa[i][j]);
        fscanf(fmapa, "%c", &trash);
    }
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
            printf("%c", mapa[i][j]);
        printf("\n");
    }
    printf("\n");
    fclose(fmapa);
    return tipo;
}

void reed_rank(ranking rank[MAX_RANK], int* Nreal)
{
    FILE* frank;
    *Nreal = 0;
    if ((frank = fopen("Archivos/rankingR.txt", "r")) == NULL)
    {
        printf("Error al abrir archivo1!!");
        return;
    }
    while (!feof(frank))
    {
        fscanf(frank, "%s", rank[*Nreal].name);
        fscanf(frank, "%d", &rank[*Nreal].points);
        (*Nreal)++;
    }
    fclose(frank);
}
void show_rank(ranking rank[MAX_RANK], int Nreal)
{
    int i;
    for (i = 0; i < Nreal; i++)
    {
        printf("%s %d\t", rank[i].name, rank[i].points);
        printf("\n");
    }
}
void save_rank(ranking rank[MAX_RANK], int Nreal)
{
    FILE* frank;
    int i;
    if ((frank = fopen("Archivos/rankingR.txt", "w")) == NULL)
    {
        printf("Error al abrir archivo2!!");
        return;
    }
    for (i = 0; i < Nreal; i++)
    {
        if (i < Nreal - 1)
            fprintf(frank, "%s %d\n", rank[i].name, rank[i].points);
        else
            fprintf(frank, "%s %d", rank[i].name, rank[i].points);
    }
    fclose(frank);
}