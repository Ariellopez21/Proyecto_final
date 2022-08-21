#pragma once
/*_______________________________________________________________________________________________
/////////////////////////////////////ESTRUCTURAS-ENUMERACIONES///////////////////////////////////
_________________________________________________________________________________________________*/
enum animacion
{
    ann_quiet = 0, ann_up = 1, ann_right = 2, ann_left = 3, ann_punch = 4
};          //IDEA...
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
    bool flag_death;
}futbol[6], basket[1], tennis[1], american[1], cannon[1]; //EN PROCESO...
struct rank_
{
    int puntos;
    char nombre[50];
};
/*_______________________________________________________________________________________________
///////////////////////////////////////DECLARAR FUNCIONES////////////////////////////////////////
_________________________________________________________________________________________________*/
void VARIABLES_JUGADOR(player_& jg, int fase);
void VARIABLES_ENEMIGOS_INICIAL(enemy_& en, int i);            //EN PROCESO...
void VARIABLES_ENEMIGOS_RESET(enemy_& en, int i);
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
        jg.posy = HEIGHT - (PXL_H * 2);
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

void VARIABLES_ENEMIGOS_INICIAL(enemy_ &en, int i)
{
    if (i == F1)
    {
        en.posx = F1x;
        en.posy = F1y;
    }
    else if (i == F2)
    {
        en.posx = F2x;
        en.posy = F2y;
    }
    else if (i == F3)
    {
        en.posx = F3x;
        en.posy = F3y;
    }
    else if (i == F4)
    {
        en.posx = F4x;
        en.posy = F4y;
    }
    else if (i == F5)
    {
        en.posx = F5x;
        en.posy = F5y;
    }
    else if (i == F6)
    {
        en.posx = F6x;
        en.posy = F6y;
    }
        en.velx = 1.0;
        en.vely = 0.0;
        en.wall = false;
        en.live = true;
        en.dmg = false;     //-1 por contacto
        en.dir = true;  //derecha
        en.hp = 0.0;
        en.draw = true;
}
void VARIABLES_ENEMIGOS_RESET(enemy_& en, int i)
{
    if (i == F1)
    {
        en.posx = F1x;
        en.posy = F1y;
    }
    else if (i == F2)
    {
        en.posx = F2x;
        en.posy = F2y;
    }
    else if (i == F3)
    {
        en.posx = F3x;
        en.posy = F3y;
    }
    else if (i == F4)
    {
        en.posx = F4x;
        en.posy = F4y;
    }
    else if (i == F5)
    {
        en.posx = F5x;
        en.posy = F5y;
    }
    else if (i == F6)
    {
        en.posx = F6x;
        en.posy = F6y;
    }
    if(en.velx <20.0)
        en.velx += 0.333334;
    en.vely = 0.0;
    en.wall = false;
    en.live = true;
    en.dmg = false;     //-1 por contacto
    en.dir = true;  //derecha
    if(en.hp < 10.0)
        en.hp += futbol[0].velx;
    en.draw = true;
    en.flag_death = false;
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
    if (
        ((mapa[(y + PXL_H) / PXL_H][x / PXL_W] == 'p') ||
            (mapa[(y + PXL_H) / PXL_H][x / PXL_W] == 'D'))
        ||
        ((mapa[(y + PXL_H) / PXL_H][(x + (SIZE / 2)) / PXL_W] == 'p') ||
            (mapa[(y + PXL_H) / PXL_H][x / PXL_W] == 'D'))
        ||
        ((mapa[(y + PXL_H) / PXL_H][(x + SIZE) / PXL_W] == 'p') ||
            (mapa[(y + PXL_H) / PXL_H][x / PXL_W] == 'D'))
        )
        return (coll_down = true);
    else
        return (coll_down = false);
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