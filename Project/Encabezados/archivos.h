#pragma once
int ABRIR_MAPA(char mapa[SIZE][SIZE], int tipo)
{
    FILE* fmapa;
    int i = 0, j = 0;
    char trash;
    if (tipo == 1)
    {
        fmapa = fopen("Archivos/Map1.txt", "r");
        if (fmapa == NULL)
        {
            printf("ERROR");
            return 0;
        }
    }
    else if(tipo == 2)
    {
        fmapa = fopen("Archivos/Map2.txt", "r");
        if (fmapa == NULL)
        {
            printf("ERROR");
            return 0;
        }
    }
    else if (tipo == 3)
    {
        fmapa = fopen("Archivos/Map3.txt", "r");
        if (fmapa == NULL)
        {
            printf("ERROR");
            return 0;
        }
    }
    else if (tipo == 4)
    {
        fmapa = fopen("Archivos/Map4.txt", "r");
        if (fmapa == NULL)
        {
            printf("ERROR");
            return 0;
        }
    }
    else if (tipo == 5)
    {
        fmapa = fopen("Archivos/Map5.txt", "r");
        if (fmapa == NULL)
        {
            printf("ERROR");
            return 0;
        }
    }
    else
    {
        fmapa = NULL;
        printf("ERROR");
        return 0;
    }

    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
            fscanf(fmapa, "%c", &mapa[i][j]);
        fscanf(fmapa, "%c", &trash);
    }
    fclose(fmapa);
    return tipo;
}

void reed_rank(ranking rank[MAX_RANK], int* Nreal)              //Lee el archivo para ponerlo en .menú-ranking.
{
    FILE* frank;
    *Nreal= 0;
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
void show_rank(ranking rank[MAX_RANK], int Nreal)           //Muestra el ranking en menú-ranking.
{
    int i;
    for (i = 0; i < Nreal; i++)
    {
        printf("%s %d\t", rank[i].name, rank[i].points);
        printf("\n");
    }
}
void save_rank(ranking rank[MAX_RANK], int Nreal)           //Introduzca su nombre; Aparece puntuación.
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
void comparacion_rank(ranking rank[MAX_RANK], int tus_puntos)
{
    int maximo = MAX_RANK - 1, Nreal=MAX_RANK;
    char auxchar[MAX_LINE];
    int auxint, i, j;
    printf("Ingrese su nombre: ");
    scanf("%s", &rank[10].name);
    rank[10].points = tus_puntos;
    for (i = 0; i < MAX_RANK; i++)
    {
        printf("Posicion %d -> nombre: %s, puntos: %d\n", i+1, rank[i].name, rank[i].points);
    }

    for(i=0; i<MAX_RANK-1; i++)
    {
        for(j=0; j<MAX_RANK-1-i; j++)
        {
        if (rank[j].points > rank[j+1].points)
            {
                printf("CAMBIO %d -> nombre: %s, puntos: %d\n", maximo, rank[j].name, rank[j].points);
                printf("CAMBIO %d -> nombre: %s, puntos: %d\n", maximo, rank[j+1].name, rank[j+1].points);
                auxint = rank[j].points;
                rank[j].points = rank[j+1].points;
                rank[j+1].points = auxint;
                strcpy(auxchar, rank[j].name);
                strcpy(rank[j].name, rank[j+1].name);
                strcpy(rank[j+1].name, auxchar);

                printf("CAMBIO %d -> nombre: %s, puntos: %d\n", maximo, rank[j].name, rank[j].points);
                printf("CAMBIO %d -> nombre: %s, puntos: %d\n", maximo, rank[j+1].name, rank[j+1].points);
                printf("Si!\t\t\t\t\t");
            }
        }
    }
    for (int i = 0; i < MAX_RANK; i++)
    {
        printf("Posicion %d -> nombre: %s, puntos: %d\n", i + 1, rank[i].name, rank[i].points);
    }
    save_rank(rank, Nreal);
}