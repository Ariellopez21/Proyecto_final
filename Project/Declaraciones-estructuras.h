#pragma once
#define FASES 3
#define WIDTH 600
#define HEIGHT  800
#define SIZE 20
#define PXL_W 30
#define PXL_H 40
#define KEY_SEEN     1
#define KEY_RELEASED 2
#define VALOR_INIT_SALTO 17
#define VALOR_GRAVITY 22
#define VALOR_VEL_JG 6
#define TAM_PLATFORM 42
#define TAM_DIRT 20
struct blocks_
{
    int x;
    int y;
    int w;
    int h;
    int col_true;
};
typedef struct blocks_ block;

struct player_
{
    int posx;
    int posy;
    int salto;                  //viene siendo el aumento de pos_y hacia arriba
    int gravity;
    float vida;
    float lvlup;
    int powerup;
    int col_x;
    int col_y;
}jg[FASES];

void VARIABLES_JUGADOR(player_ &jg, int fase)
{
    if (fase == 0)
    {
        jg.posx = WIDTH / 2;
        jg.posy = HEIGHT - (PXL_H * 2);
        jg.salto = VALOR_INIT_SALTO;
        jg.gravity = VALOR_GRAVITY;
        jg.vida = 100;
        jg.lvlup = 0;
        jg.powerup = 0;
        jg.col_x = 0;
        jg.col_y = 0;
    }
    else if (fase == 1)
    {

    }
    else
    {

    }
}