#pragma once
/*_______________________________________________________________________________________________
/////////////////////////////////////ESTRUCTURAS-ENUMERACIONES///////////////////////////////////
_________________________________________________________________________________________________*/
enum pos_enemy_futbol
{
    F1 = 0, F2 = 1, F3 = 2, F4 = 3, F5 = 4, F6 = 5,
    F1x = 288, F1y = 220,
    F2x = 264, F2y = 500,
    F3x = 108, F3y = 580,
    F4x = 450, F4y = 620,
    F5x = 100, F5y = 740,
    F6x = 400, F6y = 740
};

struct player_
{
    int posx;
    int posy;
    int velx;
    int salto;                  //viene siendo el aumento de pos_y hacia arriba
    int gravity;
    float vida;
    float lvlup;
    int exp;
    bool dir;
}jg[FASES];

struct enemy_
{
    int posx;
    int posy;
    float velx;
    float vely;
    bool wall;
    bool live;
    bool dmg;
    bool dir;
    float hp;
    bool draw;
    int flag_death;
}futbol[CANT]; //EN PROCESO...
struct rank_
{
    int puntos;
    char nombre[50];
};
/*_______________________________________________________________________________________________
///////////////////////////////////////DECLARAR FUNCIONES////////////////////////////////////////
_________________________________________________________________________________________________*/
void VARIABLES_JUGADOR(player_& jg, int fase);
void VARIABLES_ENEMIGOS_INICIAL(char mapa[SIZE][SIZE], enemy_ futbol[CANT], int i);            //EN PROCESO...
void VARIABLES_ENEMIGOS_RESET(char mapa[SIZE][SIZE], enemy_ futbol[CANT], int i);
void DRAW_MAP_SINCE_MAPA(char dibujado[SIZE][SIZE], ALLEGRO_BITMAP* sky, ALLEGRO_BITMAP* platform, ALLEGRO_BITMAP* dirt);
int ABRIR_MAPA(char mapa[SIZE][SIZE], int tipo);
int RANK(int puntos);
bool coll_izq(char mapa[SIZE][SIZE], int x, int y, bool coll_left);
bool coll_der(char mapa[SIZE][SIZE], int x, int y, bool coll_right);
bool coll_arriba(char mapa[SIZE][SIZE], int x, int y, bool coll_up);
bool coll_abajo(char mapa[SIZE][SIZE], int x, int y, bool coll_down);
void exit_game();
/*_______________________________________________________________________________________________
/////////////////////////////////////////////FUNCIONES///////////////////////////////////////////
_________________________________________________________________________________________________*/
void VARIABLES_JUGADOR(player_ &jg, int fase)
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
void VARIABLES_ENEMIGOS_INICIAL(char mapa[SIZE][SIZE], enemy_ futbol[CANT], int i)
{
    int contaE=0, j, k;

        for (j = 0; j < SIZE; j++)
            for (k = 0; k < SIZE; k++)
                if (mapa[j][k] == 'E')
                {
                    if(contaE<CANT)     //que pasa si contaE es menor que CANT y quedan arreglos basura?
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
                        contaE++;
                    }
                    else
                    {
                        mapa[j][k] = '0';
                    }
                }
}
void VARIABLES_ENEMIGOS_RESET(char mapa[SIZE][SIZE], enemy_ futbol[CANT], int contaE)
{
    ABRIR_MAPA(mapa, 1);
    int j, k;
    for (j = 0; j < SIZE; j++)
        for (k = 0; k < SIZE; k++)
            if (mapa[j][k] == 'E')
            {
                if(futbol[contaE].flag_death)       //Bandera: está muerto! o sea, vale 1
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
                    }
                }
                mapa[j][k] = '0';
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

void exit_game()
{
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_bitmap(sky);
    al_destroy_bitmap(dirt);
    al_destroy_bitmap(platform);
    al_destroy_bitmap(bar);
    al_destroy_bitmap(pwup);
    al_destroy_bitmap(perfil);
    al_destroy_bitmap(jg0_Idle);
    al_destroy_bitmap(jg0_Walk);
    al_destroy_bitmap(jg0_Jump);
    al_destroy_bitmap(jg0_Damage);
    al_destroy_bitmap(jg0_Punch);
    al_destroy_bitmap(jg1_Idle);
    al_destroy_bitmap(jg1_Walk);
    al_destroy_bitmap(jg1_Jump);
    al_destroy_bitmap(jg1_Damage);
    al_destroy_bitmap(jg1_Punch);
}