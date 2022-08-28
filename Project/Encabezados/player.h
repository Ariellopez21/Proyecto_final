#pragma once
void VARIABLES_JUGADOR(player_& jg, int fase)
{
    if (fase == 0)
    {
        jg.posx = WIDTH / 2;
        jg.posy = HEIGHT - (PXL_H * 3);
        jg.velx = VEL_X0;
        jg.salto = 0;
        jg.gravity = VALOR_GRAVITY;
        jg.vida = 100;
        jg.lvlup = 0;
        jg.exp = 0;
        jg.dir = true;  //derecha
    }
    else if (fase == 1)
    {

    }
    else
    {

    }
}
bool coll_izq(char mapa[SIZE][SIZE], int x, int y, bool coll_left)
{
    if (
        (mapa[y / PXL_H][(x - 1) / PXL_W] == 'p' ||
            mapa[y / PXL_H][(x - 1) / PXL_W] == 'D')
        &&
        (mapa[(y + (PXL_H / 2)) / PXL_H][(x - 1) / PXL_W] == 'p' ||
            mapa[(y + (PXL_H / 2)) / PXL_H][(x - 1) / PXL_W] == 'D')
        &&
        (mapa[(y + PXL_H) / PXL_H][(x - 1) / PXL_W] == 'p' ||
            mapa[(y + PXL_H) / PXL_H][(x - 1) / PXL_W] == 'D')
        )
        return (coll_left = true);
    else
        return (coll_left = false);
}
bool coll_der(char mapa[SIZE][SIZE], int x, int y, bool coll_right)
{
    if (
        (mapa[y / PXL_H][(x + SIZE + 5) / PXL_W] == 'p' ||
            mapa[y / PXL_H][(x + SIZE + 5) / PXL_W] == 'D')
        &&
        (mapa[(y + (PXL_H / 2)) / PXL_H][(x + SIZE + 5) / PXL_W] == 'p' ||
            mapa[(y + (PXL_H / 2)) / PXL_H][(x + SIZE + 5) / PXL_W] == 'D')
        &&
        (mapa[(y + PXL_H) / PXL_H][(x + SIZE + 5) / PXL_W] == 'p' ||
            mapa[(y + PXL_H) / PXL_H][(x + SIZE + 5) / PXL_W] == 'D')
        )
        return (coll_right = true);
    else
        return (coll_right = false);
}
bool coll_arriba(char mapa[SIZE][SIZE], int x, int y, bool coll_up)
{
    if (
        (mapa[y / PXL_H][x / PXL_W] == 'p')
        ||
        (mapa[y / PXL_H][(x + (SIZE / 2)) / PXL_W] == 'p')
        ||
        (mapa[y / PXL_H][(x + SIZE) / PXL_W] == 'p')
        )
        return (coll_up = true);
    else
        return (coll_up = false);
}
bool coll_abajo(char mapa[SIZE][SIZE], int x, int y, bool coll_down)
{
    if ((mapa[(y / PXL_H) + 1][x / PXL_W] == 'p') ||
        (mapa[(y / PXL_H) + 1][x / PXL_W] == 'D'))
        coll_down = true;
    else
        coll_down = false;
    return coll_down;
}