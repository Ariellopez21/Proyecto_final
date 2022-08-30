#pragma once

void VARIABLES_ENEMIGOS_INICIAL(char mapa[SIZE][SIZE], enemy_ futbol[CANT], int i)
{
    int contaE = 0, j, k;

    for (j = 0; j < SIZE; j++)
        for (k = 0; k < SIZE; k++)
            if (mapa[j][k] == 'E')
            {
                if (contaE < CANT)
                {
                    futbol[contaE].posx = k * PXL_W;
                    futbol[contaE].posy = j * PXL_H;
                    futbol[contaE].velx = 1.0;
                    futbol[contaE].vely = 0.0;
                    futbol[contaE].wall = false;
                    futbol[contaE].live = true;     //PREGUNTAR: ESTO activado o no para que exista.
                    futbol[contaE].dmg = false;     //-1 por contacto
                    futbol[contaE].dir = true;  //derecha
                    futbol[contaE].hp = 0.0;
                    futbol[contaE].draw = true;
                    mapa[j][k] = '0';
                    futbol[contaE].E = contaE;
                    contaE++;
                }
                else
                {
                    mapa[j][k] = '0';
                }
            }
}
void VARIABLES_ENEMIGOS_RESET(char mapa[SIZE][SIZE], enemy_ futbol[CANT], int contaE, int tipo)
{
    ABRIR_MAPA(mapa, tipo);
    int j, k, pos = 0;
    for (j = 0; j < SIZE; j++)
        for (k = 0; k < SIZE; k++)
            if (mapa[j][k] == 'E')
            {
                if ((futbol[contaE].E == pos))
                {
                    if (futbol[contaE].flag_death)       //Bandera: está muerto! o sea, vale 1
                    {
                        if (contaE < CANT)     //que pasa si contaE es menor que CANT y quedan arreglos basura?
                        {
                            futbol[contaE].posx = k * PXL_W;
                            futbol[contaE].posy = j * PXL_H;
                            if (futbol[contaE].velx < 20.0)
                                futbol[contaE].velx += 0.333334;
                            futbol[contaE].vely = 0.0;
                            futbol[contaE].wall = false;
                            futbol[contaE].live = true;
                            futbol[contaE].dmg = false;     //-1 por contacto
                            futbol[contaE].dir = true;  //derecha
                            if (futbol[contaE].hp < 10.0)
                                futbol[contaE].hp += futbol[contaE].velx;
                            futbol[contaE].draw = true;
                            futbol[contaE].flag_death = 0;
                            mapa[j][k] = '0';
                        }
                    }
                }
                else
                {
                    mapa[j][k] = '0';
                }
                pos++;
            }
}

void mov_futbol(enemy_& en, char fwall[SIZE][SIZE])
{
    if (en.dir)
    {
        en.posx += en.velx;
        en.wall = coll_w(fwall, en.posx, en.posy, en.wall, en.dir);
        if (en.wall)
            en.dir = false;
    }
    else
    {
        en.posx -= en.velx;
        en.wall = coll_w(fwall, en.posx, en.posy, en.wall, en.dir);
        if (en.wall)
            en.dir = true;
    }
}
bool coll_w(char fwall[SIZE][SIZE], int x, int y, bool dir, bool wall_true)
{
    if (dir)
    {
        if ((fwall[(y / PXL_H)][(x / PXL_W) + 2] == 'W') || (fwall[(y / PXL_H)][(x / PXL_W) + 2] == 'p'))
            wall_true = true;
        else
            wall_true = false;
    }
    else
    {
        if ((fwall[(y / PXL_H)][(x - 1) / PXL_W] == 'W') || (fwall[(y / PXL_H)][(x - 1) / PXL_W] == 'p'))
            wall_true = true;
        else
            wall_true = false;
    }
    return wall_true;
}
float damage(player_& jg, enemy_& en)
{
    if (((jg.posx + PXL_CENTROW) >= en.posx) &&
        ((jg.posx + PXL_CENTROW) <= en.posx + PXL_W) &&
        ((jg.posy + PXL_CENTROH) >= en.posy) &&
        ((jg.posy + PXL_CENTROH) <= en.posy + PXL_H))
    {
        en.dmg = true;
    }
    else
    {
        en.dmg = false;
    }
    if (en.dmg)
    {
        jg.vida--;
    }
    return jg.vida;
}
int golpe(player_ jg[FASES], enemy_ futbol[CANT], int points)
{
    int contaE;
    for (contaE = 0; contaE < CANT; contaE++)
    {
        if (jg[0].dir)
        {
            if ((futbol[contaE].posx >= jg[0].posx + PXL_W && futbol[contaE].posx <= jg[0].posx + PXL_W * 2)
                &&
                (futbol[contaE].posy >= jg[0].posy && futbol[contaE].posy <= jg[0].posy + PXL_H))
            {
                futbol[contaE].live = false;
            }
            else
            {
                futbol[contaE].live = true;
            }
        }
        else
        {
            if ((futbol[contaE].posx >= jg[0].posx - PXL_W && futbol[contaE].posx <= jg[0].posx)
                &&
                (futbol[contaE].posy >= jg[0].posy && futbol[contaE].posy <= jg[0].posy + PXL_H))
            {
                futbol[contaE].live = false;
            }
            else
            {
                futbol[contaE].live = true;
            }
        }
        if (!futbol[contaE].live)
        {
            futbol[contaE].hp--;
            printf("->%.3f\t", futbol[contaE].hp);
            if (futbol[contaE].hp <= 0.0)
            {
                points += 10;
                futbol[contaE].flag_death = 1;
            }
        }
    }
    return points;
}