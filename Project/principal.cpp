#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>
#include "Encabezados/variables_globales.h"
#include "Encabezados/archivos.h"
#include "Encabezados/estructuras_funciones.h"
#include "Encabezados/dibujado.h"
#include "Encabezados/funciones_menu.h"
bool coll_izq(char mapa[SIZE][SIZE], player_& jg, bool coll_left);
bool coll_der(char mapa[SIZE][SIZE], player_& jg, bool coll_right);
bool coll_up(char mapa[SIZE][SIZE], player_& jg, bool coll_up);
bool coll_down(char mapa[SIZE][SIZE], player_& jg, bool coll_down);

void mov_futbol(int x, int vel, bool dir);
int main()
{
    /*_______________________________________________________________________________________________
    ///////////////////////////////////////DECLARAR VARIABLES////////////////////////////////////////
    _________________________________________________________________________________________________*/
    int x = 0, y = 0, i = 0, j = 0, k = 0, tipo = 1;
    int mouseX = 10, mouseY = 10, MouseSpeed = 5;
    char mapa[SIZE][SIZE];
    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));
    bool flag_key_up_true = false, pausa = false, flag_key_p_true = false,
        coll_left = false, coll_right = false, coll_up = false, coll_down = false;
    /*_______________________________________________________________________________________________
    ///////////////////////////////////////INICIAR ARCHIVO///////////////////////////////////////////
    _________________________________________________________________________________________________*/
    tipo = ABRIR_MAPA(mapa, tipo);       //TIPO: decide si es mapa 1 o 2, se usará más adelante...
    /*_______________________________________________________________________________________________
    ///////////////////////////////////////INICIAR ALLEGRO///////////////////////////////////////////
    _________________________________________________________________________________________________*/
    al_init();
    al_init_image_addon();
    al_install_keyboard();
    al_install_mouse();

    al_set_window_position(disp, 800, 100);
    al_set_window_title(disp, "Planeta Gol!");

    timer = al_create_timer(1.0 / 30.0);
    queue = al_create_event_queue();
    disp = al_create_display(WIDTH, HEIGHT);

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());
    /*_______________________________________________________________________________________________
    ///////////////////////////////////////REGISTRAR IMGS////////////////////////////////////////////
    _________________________________________________________________________________________________*/
    sky = al_load_bitmap("Sprites/Escenario/sky.bmp");
    dirt = al_load_bitmap("Sprites/Escenario/dirt.bmp");
    platform = al_load_bitmap("Sprites/Escenario/platform.bmp");
    perfil = al_load_bitmap("Sprites/Escenario/profile.bmp");
    pwup = al_load_bitmap("Sprites/Escenario/power_up.bmp");
    bar = al_load_bitmap("Sprites/Escenario/bar.bmp");

    jg0_Idle = al_load_bitmap("Sprites/Jugador/jg0_Idle_Walk.bmp");
    jg0_Walk = al_load_bitmap("Sprites/Jugador/jg0_Idle_Walk.bmp");
    jg0_Jump = al_load_bitmap("Sprites/Jugador/jg0_Jump.bmp");
    jg0_Punch = al_load_bitmap("Sprites/Jugador/jg0_Punch.bmp");
    jg0_Damage = al_load_bitmap("Sprites/Jugador/jg0_Damage.bmp");

    jg1_Idle = al_load_bitmap("Sprites/Jugador/jg1_Idle_Walk.bmp");
    jg1_Walk = al_load_bitmap("Sprites/Jugador/jg1_Idle_Walk.bmp");
    jg1_Jump = al_load_bitmap("Sprites/Jugador/jg1_Jump.bmp");
    jg1_Punch = al_load_bitmap("Sprites/Jugador/jg1_Punch.bmp");
    jg1_Damage = al_load_bitmap("Sprites/Jugador/jg1_Damage.bmp");

    futbol_img = al_load_bitmap("Sprites/Enemigos/futbol.png");
    basket_img = al_load_bitmap("Sprites/Enemigos/basketpng.png");
    tennis_img = al_load_bitmap("Sprites/Enemigos/tennis.png");
    /*
       * american, * cannon, * boss,                           //Enemigos
       * llave_inglesa, * engranaje, * bateria;                //Puntos
    */
    menu_principal = al_load_bitmap("Screen/menu_0.bmp");
    menu_principal1 = al_load_bitmap("Screen/menu_1.bmp");        //CURSOR START
    menu_principal2 = al_load_bitmap("Screen/menu_2.bmp");        //CURSOR RANKING
    menu_principal3 = al_load_bitmap("Screen/menu_3.bmp");        //CURSOR EXIT
    menu_ranking = al_load_bitmap("Screen/ranking.bmp");
    menu_history = al_load_bitmap("Screen/history.bmp");         
    menu_instructions = al_load_bitmap("Screen/instructions0.bmp");
    menu_instructions1 = al_load_bitmap("Screen/instructions1.bmp");  //CURSOR OK!
    pause = al_load_bitmap("Screen/pause_0.bmp");                    //MANTENER RELACIÓN DE ASPECTO
    pause1 = al_load_bitmap("Screen/pause_1.png");
    pause2 = al_load_bitmap("Screen/pause_2.png");
    /*_______________________________________________________________________________________________
    ///////////////////////////////////////INICIALIZAR JUGADOR///////////////////////////////////////
    _________________________________________________________________________________________________*/
    for (i = 0; i < FASES; i++)
        VARIABLES_JUGADOR(jg[i], i);
    printf
    (
        "posx=%d, posy=%d, salto=%d, gravity=%d, powerup=%d, colx=%d, coly=%d, vida=%f, lvlup=%f",
        jg[0].posx, jg[0].posy, jg[0].salto, jg[0].gravity, jg[0].powerup, jg[0].col_x, jg[0].col_y,
        jg[0].vida, jg[0].lvlup
    );

    /*_______________________________________________________________________________________________
    ////////////////////////////////////INICIALIZAR ENEMIGOS/////////////////////////////////////////
    _________________________________________________________________________________________________*/
    srand(time(0));
    VARIABLES_ENEMIGOS(futbol[0]);
    /*________________________________________________________________________________________________
    /////////////////////////////////////////INICIA EL JUEGO//////////////////////////////////////////
    _________________________________________________________________________________________________*/
    //done = func_menu();
    //func_instructions();
    al_start_timer(timer);
    while (!done)
    {
        al_wait_for_event(queue, &event);
        mov_futbol(futbol[0].posx, futbol[0].velx, futbol[0].dir);
        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            //coll_left = colision(mapa, jg[0]);
            //coll_right
            //coll_up
            //coll_down

            //CORTAR
            //COLISION IZQ
            if (
                (mapa[jg[0].posy / PXL_H][(jg[0].posx - 1) / PXL_W] == 'p' ||
                    mapa[jg[0].posy / PXL_H][(jg[0].posx - 1) / PXL_W] == 'D')
                &&
                (mapa[(jg[0].posy + (PXL_H / 2)) / PXL_H][(jg[0].posx - 1) / PXL_W] == 'p' ||
                    mapa[(jg[0].posy + (PXL_H / 2)) / PXL_H][(jg[0].posx - 1) / PXL_W] == 'D')
                &&
                (mapa[(jg[0].posy + PXL_H) / PXL_H][(jg[0].posx - 1) / PXL_W] == 'p' ||
                    mapa[(jg[0].posy + PXL_H) / PXL_H][(jg[0].posx - 1) / PXL_W] == 'D')
                )
                coll_left = true;
            else
                coll_left = false;

            //COLISION DER
            if (
                (mapa[jg[0].posy / PXL_H][(jg[0].posx + SIZE + 5) / PXL_W] == 'p' ||
                    mapa[jg[0].posy / PXL_H][(jg[0].posx + SIZE + 5) / PXL_W] == 'D')
                &&
                (mapa[(jg[0].posy + (PXL_H / 2)) / PXL_H][(jg[0].posx + SIZE + 5) / PXL_W] == 'p' ||
                    mapa[(jg[0].posy + (PXL_H / 2)) / PXL_H][(jg[0].posx + SIZE + 5) / PXL_W] == 'D')
                &&
                (mapa[(jg[0].posy + PXL_H) / PXL_H][(jg[0].posx + SIZE + 5) / PXL_W] == 'p' ||
                    mapa[(jg[0].posy + PXL_H) / PXL_H][(jg[0].posx + SIZE + 5) / PXL_W] == 'D')
                )
                coll_right = true;
            else
                coll_right = false;

            //COLISION ARRIBA
            if (
                (mapa[jg[0].posy / PXL_H][jg[0].posx / PXL_W] == 'p')
                ||
                (mapa[jg[0].posy / PXL_H][(jg[0].posx + (SIZE / 2)) / PXL_W] == 'p')
                ||
                (mapa[jg[0].posy / PXL_H][(jg[0].posx + SIZE) / PXL_W] == 'p')
                )
                coll_up = true;
            else
                coll_up = false;

            //COLISION ABAJO
            if (
                ((mapa[(jg[0].posy + PXL_H) / PXL_H][jg[0].posx / PXL_W] == 'p') ||
                    (mapa[(jg[0].posy + PXL_H) / PXL_H][jg[0].posx / PXL_W] == 'D'))
                ||
                ((mapa[(jg[0].posy + PXL_H) / PXL_H][(jg[0].posx + (SIZE / 2)) / PXL_W] == 'p') ||
                    (mapa[(jg[0].posy + PXL_H) / PXL_H][jg[0].posx / PXL_W] == 'D'))
                ||
                ((mapa[(jg[0].posy + PXL_H) / PXL_H][(jg[0].posx + SIZE) / PXL_W] == 'p') ||
                    (mapa[(jg[0].posy + PXL_H) / PXL_H][jg[0].posx / PXL_W] == 'D'))
                )
                coll_down = true;
            else
                coll_down = false;
            //HASTA AQUI

            if (coll_down)
            {
                jg[0].gravity = 0;
            }
            else
            {
                jg[0].gravity = VALOR_GRAVITY;
            }

            if (!coll_up)
            {
                if (key[ALLEGRO_KEY_UP] && !flag_key_up_true)
                {
                    jg[0].posy = jg[0].posy - jg[0].salto;
                    if (jg[0].salto > 0)
                        jg[0].salto--;
                    else
                    {
                        flag_key_up_true = true;
                        jg[0].salto = 0;
                    }
                }
                else
                {
                    jg[0].posy = jg[0].posy + jg[0].gravity;
                    if ((mapa[(jg[0].posy + PXL_H) / PXL_H][jg[0].posx / PXL_W] == 'p') ||
                        (mapa[(jg[0].posy + PXL_H) / PXL_H][jg[0].posx / PXL_W] == 'D'))
                    {
                        jg[0].salto = VALOR_INIT_SALTO;
                        flag_key_up_true = false;
                    }
                }
            }
            else
            {
                jg[0].salto = 0;
                jg[0].posy = jg[0].posy + jg[0].gravity;
            }

            if (!coll_left)
            {
                if (key[ALLEGRO_KEY_LEFT])
                {
                    jg[0].posx = jg[0].posx - jg[0].velx;
                    if (jg[0].posx <= 0)
                        jg[0].posx = WIDTH - PXL_W;
                }
            }

            if (!coll_right)
            {
                if (key[ALLEGRO_KEY_RIGHT])
                {
                    jg[0].posx = jg[0].posx + jg[0].velx;
                    if (jg[0].posx >= WIDTH)
                        jg[0].posx = 0;
                }
            }
                        
            if (key[ALLEGRO_KEY_ESCAPE])
                done = true;
            for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
                key[i] &= KEY_SEEN;
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
            key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
         
            if (key[ALLEGRO_KEY_P] && !flag_key_p_true)
            {
                flag_key_p_true = true;
                printf("entra?\t");
            }
            break;
        case ALLEGRO_EVENT_KEY_UP:
            key[event.keyboard.keycode] &= KEY_RELEASED;
            break;
        }
        if (flag_key_p_true && !key[ALLEGRO_KEY_P])//PAUSA
        {
            done = func_pause(pausa);
            flag_key_p_true = false;
        } 
        if (al_is_event_queue_empty(queue) && (!done))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            DRAW_MAP_SINCE_MAPA(mapa, sky, platform, dirt, pwup, perfil, bar);

            if (jg[0].posy >= (HEIGHT - PXL_H))
                jg[0].posy = HEIGHT - PXL_H;

            al_draw_bitmap_region(jg0_Idle, 0, 0, PXL_W, PXL_H, jg[0].posx, jg[0].posy, 0);
            al_convert_mask_to_alpha(jg0_Idle, al_map_rgba(255, 0, 0, 255));
            al_draw_bitmap_region(futbol_img, 0, 0, PXL_W, PXL_H, futbol[0].posx, futbol[0].posy, 0);
            al_convert_mask_to_alpha(futbol_img, al_map_rgba(255, 0, 0, 255));
            al_flip_display();
        }
    }
    exit_game();
    return 0;
}
bool coll_izq(char mapa[SIZE][SIZE], player_& jg, bool coll_left)
{
    if (
        (mapa[jg.posy / PXL_H][(jg.posx - 1) / PXL_W] == 'p' ||
            mapa[jg.posy / PXL_H][(jg.posx - 1) / PXL_W] == 'D')
        &&
        (mapa[(jg.posy + (PXL_H / 2)) / PXL_H][(jg.posx - 1) / PXL_W] == 'p' ||
            mapa[(jg.posy + (PXL_H / 2)) / PXL_H][(jg.posx - 1) / PXL_W] == 'D')
        &&
        (mapa[(jg.posy + PXL_H) / PXL_H][(jg.posx - 1) / PXL_W] == 'p' ||
            mapa[(jg.posy + PXL_H) / PXL_H][(jg.posx - 1) / PXL_W] == 'D')
        )
        return (coll_left=true);
    else
        return (coll_left = false);
}
bool coll_der(char mapa[SIZE][SIZE], player_& jg, bool coll_right)
{
    if (
        (mapa[jg.posy / PXL_H][(jg.posx + SIZE + 5) / PXL_W] == 'p' ||
            mapa[jg.posy / PXL_H][(jg.posx + SIZE + 5) / PXL_W] == 'D')
        &&
        (mapa[(jg.posy + (PXL_H / 2)) / PXL_H][(jg.posx + SIZE + 5) / PXL_W] == 'p' ||
            mapa[(jg.posy + (PXL_H / 2)) / PXL_H][(jg.posx + SIZE + 5) / PXL_W] == 'D')
        &&
        (mapa[(jg.posy + PXL_H) / PXL_H][(jg.posx + SIZE + 5) / PXL_W] == 'p' ||
            mapa[(jg.posy + PXL_H) / PXL_H][(jg.posx + SIZE + 5) / PXL_W] == 'D')
        )
        return (coll_right = true);
    else
        return (coll_right = false);
}
bool coll_up(char mapa[SIZE][SIZE], player_& jg, bool coll_up)
{
    if (
        (mapa[jg.posy / PXL_H][jg.posx / PXL_W] == 'p')
        ||
        (mapa[jg.posy / PXL_H][(jg.posx + (SIZE / 2)) / PXL_W] == 'p')
        ||
        (mapa[jg.posy / PXL_H][(jg.posx + SIZE) / PXL_W] == 'p')
        )
        return (coll_up = true);
    else
        return (coll_up = false);
}
bool coll_down(char mapa[SIZE][SIZE], player_& jg, bool coll_down)
{
    if (
        ((mapa[(jg.posy + PXL_H + 1) / PXL_H][jg.posx / PXL_W] == 'p') ||
            (mapa[(jg.posy + PXL_H + 1) / PXL_H][jg.posx / PXL_W] == 'D'))
        ||
        ((mapa[(jg.posy + PXL_H + 1) / PXL_H][(jg.posx + (SIZE / 2)) / PXL_W] == 'p') ||
            (mapa[(jg.posy + PXL_H + 1) / PXL_H][jg.posx / PXL_W] == 'D'))
        ||
        ((mapa[(jg.posy + PXL_H + 1) / PXL_H][(jg.posx + SIZE) / PXL_W] == 'p') ||
            (mapa[(jg.posy + PXL_H + 1) / PXL_H][jg.posx / PXL_W] == 'D'))
        )
        return (coll_down = true);
    else
        return (coll_down = false);
}

void mov_futbol(int x, int vel, bool dir)
{
    x += vel;
    
}