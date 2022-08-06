#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int ABRIR_MAPA(char mapa[SIZE][SIZE], int tipo)
{
    FILE* fmapa;
    int i = 0, j = 0;
    char trash;
    if (tipo == 1)
    {
        fmapa = fopen("Mapa_inicial.txt", "r");
        if (fmapa == NULL)
        {
            printf("ERROR");
            return 0;
        }
    }
    else
    {
        fmapa = fopen("Mapa_jefe.txt", "r");
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
    printf("%c", mapa[i][j]);
    fclose(fmapa);
    return tipo;
}