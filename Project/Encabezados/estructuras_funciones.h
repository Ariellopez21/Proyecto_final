#pragma once
enum animacion
{
    ann_quiet = 0, ann_up = 1, ann_right = 2, ann_left = 3, ann_punch = 4
};
enum pos_enemy
{
    F1x = 288,
    F1y = 200,
    F2x=264,
    F2y=482,

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
    int powerup;
    int col_x;
    int col_y;
}jg[FASES];

struct enemy_
{
    int posx;
    int posy;
    int velx;
    int vely;
    bool wall;
    bool live;
    int dmg;
    bool dir;
    int gen;
}futbol[1], basket[1], tennis[1], american[1], cannon[1];

void VARIABLES_JUGADOR(player_& jg, int fase);
void VARIABLES_ENEMIGOS(enemy_& en);
void exit_game();

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

void VARIABLES_ENEMIGOS(enemy_ &en)
{
    en.posx = 450;
    en.posy = 620;
    en.velx = 10;
    en.vely = 0;
    en.wall = false;
    en.live = true;
    en.dmg = 1;     //-1 por contacto
    en.dir = true;  //derecha
    en.gen = 0;     //cannon->basket...
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