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
void comparacion_rank(int puntuacion, char nuevo_ingreso);

void comparacion_rank(int puntuacion, char nuevo_ingreso)
{
    int maximo = MAX_RANK-1, auxP;
    char auxN[MAX_LINE];
    bool mayor = true;
    while (mayor)
    {
        if (puntuacion > rank[maximo].points)
        {
            printf("posicion %d: TU:%d > EL:%d\n", maximo - 1, puntuacion, rank[maximo].points);
            auxP = rank[maximo].points;
            rank[maximo].points = puntuacion;
            rank[maximo + 1].points = auxP;
            strcpy(auxN, rank[maximo].name);
            strcpy(rank[maximo].name, &nuevo_ingreso);
            strcpy(rank[maximo + 1].name, auxN);
        }
        else if (puntuacion < rank[maximo].points)
            mayor = false;
        maximo--;
        if (maximo < 0)
            mayor = false;
    }
}