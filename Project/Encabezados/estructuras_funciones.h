#pragma once
/*_______________________________________________________________________________________________
/////////////////////////////////////ESTRUCTURAS-ENUMERACIONES///////////////////////////////////
_________________________________________________________________________________________________*/
enum animacion
{
    ann_quiet = 0, ann_up = 1, ann_right = 2, ann_left = 3, ann_punch = 4
};          //IDEA...
enum pos_enemy
{
    F1x = 288,
    F1y = 200,
    F2x=264,
    F2y=482,

};  //IDEA...

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
    int velx;
    int vely;
    bool wall;
    bool live;
    bool dmg;
    bool dir;
    int hp;
    bool draw;
}futbol[1], basket[1], tennis[1], american[1], cannon[1]; //EN PROCESO...
/*_______________________________________________________________________________________________
///////////////////////////////////////DECLARAR FUNCIONES////////////////////////////////////////
_________________________________________________________________________________________________*/
void VARIABLES_JUGADOR(player_& jg, int fase);
void VARIABLES_ENEMIGOS(enemy_& en);            //EN PROCESO...
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

void VARIABLES_ENEMIGOS(enemy_ &en)
{
    en.posx = 450;
    en.posy = 620;
    en.velx = 1;
    en.vely = 0;
    en.wall = false;
    en.live = true;
    en.dmg = false;     //-1 por contacto
    en.dir = true;  //derecha
    en.hp = 10;     
    en.draw = true;
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