#pragma once
/*_______________________________________________________________________________________________
///////////////////////////////////////////ESTRUCTURAS///////////////////////////////////////////
_________________________________________________________________________________________________*/
struct player_
{
    int posx;
    int posy;
    int velx;
    int salto;                  //permite saltar
    int gravity;                //gravedad
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
    int E;
}futbol[CANT];

struct ranking
{
    char name[LARGE];
    int points;
};
/*_______________________________________________________________________________________________
/////////////////////////////////////////////PROTOTIPOS//////////////////////////////////////////
_________________________________________________________________________________________________*/
//FUNCIONES PARA ENEMIGOS:
void VARIABLES_ENEMIGOS_INICIAL(char mapa[SIZE][SIZE], enemy_ futbol[CANT], int i);
void VARIABLES_ENEMIGOS_RESET(char mapa[SIZE][SIZE], enemy_ futbol[CANT], int i, int tipo);
void mov_futbol(enemy_& en, char mapa[SIZE][SIZE]);
int golpe(player_ jg[FASES], enemy_ futbol[CANT], int points);
bool coll_w(char fwall[SIZE][SIZE], int x, int y, bool dir, bool wall_true);
float damage(player_& jg, enemy_& en);

//FUNCIONES LECTURA ARCHIVO:
int ABRIR_MAPA(char mapa[SIZE][SIZE], int tipo);

//FUNCIONES PARA JUGADOR:
void VARIABLES_JUGADOR(player_& jg, int fase);
bool coll_izq(char mapa[SIZE][SIZE], int x, int y, bool coll_left);
bool coll_der(char mapa[SIZE][SIZE], int x, int y, bool coll_right);
bool coll_arriba(char mapa[SIZE][SIZE], int x, int y, bool coll_up);
bool coll_abajo(char mapa[SIZE][SIZE], int x, int y, bool coll_down);

//FUNCIONES DEL MENÚ y PAUSA:
bool func_menu(ranking rank[MAX_RANK]);
void func_instructions();
bool func_pause(bool pausa);

//FUNCIONES PARA RANKING:
bool func_rank(ranking rank[MAX_RANK]);
void reed_rank(ranking rank[MAX_RANK], int* Nreal);
void show_rank(ranking rank[MAX_RANK], int Nreal);
void save_rank(ranking rank[MAX_RANK], int Nreal);
void comparacion_rank(ranking rank[MAX_RANK], int tus_puntos);

//FUNCIÓN PARA DIBUJAR Y PARA DESTRUIR ELEMENTOS:
void DRAW_MAP_SINCE_MAPA(char dibujado[SIZE][SIZE], ALLEGRO_BITMAP* sky, ALLEGRO_BITMAP* platform, ALLEGRO_BITMAP* dirt);
void exit_game();
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