#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include "Encabezados/variables_globales.h"
#include "Encabezados/estructuras_funciones.h"
#include "Encabezados/archivos.h"
#include "Encabezados/dibujado.h"
#include "Encabezados/funciones_menu.h"
void mov_futbol(enemy_& en, char mapa[SIZE][SIZE]);
int golpe(player_ jg[FASES], enemy_ futbol[CANT], int points);
bool coll_w(char fwall[SIZE][SIZE], int x, int y, bool dir, bool wall_true);
float damage(player_& jg, enemy_& en);
int main()
{
    /*_______________________________________________________________________________________________
    ///////////////////////////////////////DECLARAR VARIABLES////////////////////////////////////////
    _________________________________________________________________________________________________*/
    int x = 0, y = 0, P = 0, i = 0, j = 0, k = 0, tipo = 1, cont_futbol = 0, puntuacion = 0, exp = 0;
    float tempo_enemy = -12.0, tempo_enemy_reset = 0.0, tiempo = 0.0;
    int mouseX = 10, mouseY = 10, MouseSpeed = 5;
    char mapa[SIZE][SIZE], fwall[SIZE][SIZE];
    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));
    bool flag_key_up_true = false, pausa = false, flag_key_p_true = false, flag_key_x_true = false,
        coll_left = false, coll_right = false, coll_up = false, coll_down = false;
    //struct enemy_ futbol[CANT];
    /*_______________________________________________________________________________________________
    ///////////////////////////////////////INICIAR ARCHIVO///////////////////////////////////////////
    _________________________________________________________________________________________________*/
    tipo = ABRIR_MAPA(mapa, tipo);       //TIPO: decide si es mapa 1 o 2, se usará más adelante...
    ABRIR_MAPA(fwall, 3);
    /*_______________________________________________________________________________________________
    ///////////////////////////////////////INICIAR ALLEGRO///////////////////////////////////////////
    _________________________________________________________________________________________________*/
    al_init();
    al_init_image_addon();
    al_install_keyboard();
    al_install_mouse();

    text_hp = al_create_builtin_font();
    text_points = al_create_builtin_font();
    text_exp = al_create_builtin_font();
    timer = al_create_timer(1.0 / 30.0);
    timer_enemy = al_create_timer(1.0);
    queue = al_create_event_queue();
    disp = al_create_display(WIDTH, HEIGHT);

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer_enemy));
    /*_______________________________________________________________________________________________
    ///////////////////////////////////////REGISTRAR IMGS////////////////////////////////////////////
    _________________________________________________________________________________________________*/
    sky = al_load_bitmap("Sprites/Escenario/sky.bmp");
    dirt = al_load_bitmap("Sprites/Escenario/dirt.bmp");
    platform = al_load_bitmap("Sprites/Escenario/platform.bmp");
    perfil = al_load_bitmap("Sprites/Escenario/profile.bmp");
    pwup = al_load_bitmap("Sprites/Escenario/power_up.bmp");
    bar = al_load_bitmap("Sprites/Escenario/bar.bmp");
    sky_scroll = al_load_bitmap("Sprites/Escenario/sky_scroll.png");
    interfaz = al_load_bitmap("Sprites/Escenario/Interfaz.png");

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
        "posx=%d, posy=%d, salto=%d, gravity=%d, exp=%d, vida=%f, lvlup=%f",
        jg[0].posx, jg[0].posy, jg[0].salto, jg[0].gravity, jg[0].exp, jg[0].vida, jg[0].lvlup
    );

    /*_______________________________________________________________________________________________
    ////////////////////////////////////INICIALIZAR ENEMIGOS/////////////////////////////////////////
    _________________________________________________________________________________________________*/
    srand(time(0));
    /*modificado profe....*/

        VARIABLES_ENEMIGOS_INICIAL(mapa, futbol, i);
        /*printf("\n%d - %d\t[HP:%.3f]", futbol[i].posx, futbol[i].posy, futbol[i].hp);*/
  
    /*________________________________________________________________________________________________
    /////////////////////////////////////////INICIA EL JUEGO//////////////////////////////////////////
    _________________________________________________________________________________________________*/
    //done = func_menu();
    //func_instructions();
    al_start_timer(timer);
    while (!done)
    {
        al_wait_for_event(queue, &event);
        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            /*_______________________________________________________________________________________________
            /////////////////////////////////////////////COLISIÓN////////////////////////////////////////////
            _________________________________________________________________________________________________*/
            coll_left = coll_izq(mapa, jg[0].posx, jg[0].posy, coll_left);
            coll_right = coll_der(mapa, jg[0].posx, jg[0].posy, coll_right);
            coll_up = coll_arriba(mapa, jg[0].posx, jg[0].posy, coll_up);
            coll_down = coll_abajo(mapa, jg[0].posx, jg[0].posy, coll_down);
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
                if (key[ALLEGRO_KEY_Z] && !flag_key_up_true)
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
                    if ((mapa[((jg[0].posy) / PXL_H)+1][jg[0].posx / PXL_W] == 'p') ||
                        (mapa[((jg[0].posy) / PXL_H)+1][jg[0].posx / PXL_W] == 'D'))
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
                    jg[0].dir = false;
                    jg[0].posx = jg[0].posx - jg[0].velx;
                    if (jg[0].posx <= 0)
                        jg[0].posx = WIDTH - PXL_W;
                }
            }
            if (!coll_right)
            {
                if (key[ALLEGRO_KEY_RIGHT])
                {
                    jg[0].dir = true;
                    jg[0].posx = jg[0].posx + jg[0].velx;
                    if (jg[0].posx >= WIDTH)
                        jg[0].posx = 0;
                }
            }
            /*_______________________________________________________________________________________________
            /////////////////////////////////////////////ACCIONES////////////////////////////////////////////
            _________________________________________________________________________________________________*/
            if (key[ALLEGRO_KEY_P] && !flag_key_p_true)
            {
                flag_key_p_true = true;
                printf("entra?\t");
            }
            if (flag_key_p_true && !key[ALLEGRO_KEY_P])     //PAUSA
            {
                done = func_pause(pausa);
                flag_key_p_true = false;
                printf("OUT?\t");
            }
            if (key[ALLEGRO_KEY_X])                         //GOLPE
            {
                    puntuacion = golpe(jg, futbol, puntuacion);
            }

            if (jg[0].vida <= 0)                //MUERTE
                done = true;

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
            break;
        case ALLEGRO_EVENT_KEY_UP:
            key[event.keyboard.keycode] &= KEY_RELEASED;
            break;
        }
        /*_______________________________________________________________________________________________
        /////////////////////////////////////////////ENEMIGOS////////////////////////////////////////////
        _________________________________________________________________________________________________*/
        tempo_enemy += 0.0333333333334;
        tempo_enemy_reset += 0.0333333333334;
        tiempo += 0.03333333334;
        if (tiempo >= 2.0)
        {
            puntuacion++;
            tiempo = 0.0;
        }
        if (tempo_enemy >= -10.0 && tempo_enemy <= -5.0)         //GENERAR POR PRIMERA VEZ E INICIALIZAR ENEMIGOS
        {
            for (cont_futbol = 0; cont_futbol < 6; cont_futbol++)
            {
                if (futbol[cont_futbol].hp <= 0.0 && futbol[cont_futbol].draw)
                {
                    futbol[cont_futbol].hp += futbol[cont_futbol].velx;
                    futbol[cont_futbol].velx += 0.3333334;
                    futbol[cont_futbol].flag_death = 0;
                    printf("VELOCIDAD:[%.3f]\t VIDA:[%.3f] --- POSX:[%d]; POSY:[%d]\n", futbol[cont_futbol].velx, futbol[cont_futbol].hp, futbol[cont_futbol].posx, futbol[cont_futbol].posy);
                }
            }
        }
        if (tempo_enemy_reset >= 15.0 && tempo_enemy_reset <= 18.0)    //EN CASO DE MORIR - ACÁ REAPARECEN
        {
            for (cont_futbol = 0; cont_futbol < CANT; cont_futbol++)
            {
                if (futbol[cont_futbol].posx == 0.0 && futbol[cont_futbol].posy == 0.0 && futbol[cont_futbol].flag_death)
                {
                    printf("RESET\t");
                    VARIABLES_ENEMIGOS_RESET(mapa, futbol, cont_futbol);
                    printf("VEL:[%.3f]\t HP:[%.3f] --- X:[%d]; Y:[%d]\n", futbol[cont_futbol].velx, futbol[cont_futbol].hp, futbol[cont_futbol].posx, futbol[cont_futbol].posy);
                }
            }
        }
        if (tempo_enemy_reset >= 20.0 && tempo_enemy >= 0.0)                           //TIEMPO PARA EL REINICIO DEL TEMPORIZADOR
        {
            printf("\nCERO\t");
            tempo_enemy = -15.0;
            tempo_enemy_reset = 0.0;
        }
        for (cont_futbol = 0; cont_futbol < CANT; cont_futbol++)
        {
            mov_futbol(futbol[cont_futbol], mapa);
        }
        for (cont_futbol = 0; cont_futbol < CANT; cont_futbol++)
        {
            jg[0].vida = damage(jg[0], futbol[cont_futbol]);
        }
        for (cont_futbol = 0; cont_futbol < CANT; cont_futbol++)
        {
            if (futbol[cont_futbol].hp <= 0.0 && futbol[cont_futbol].flag_death)
            {
                futbol[cont_futbol].draw = false;
            }
        }
        /*_______________________________________________________________________________________________
        /////////////////////////////////////////////DIBUJO//////////////////////////////////////////////
        _________________________________________________________________________________________________*/
        if (al_is_event_queue_empty(queue) && (!done))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            DRAW_MAP_SINCE_MAPA(mapa, sky, platform, dirt);

            if (jg[0].posy >= (HEIGHT - PXL_H))
                jg[0].posy = HEIGHT - PXL_H;

            al_draw_bitmap_region(jg0_Idle, 0, 0, PXL_W, PXL_H, jg[0].posx, jg[0].posy, 0);
            al_draw_scaled_bitmap(interfaz, 0, 0, 485, 248, 0, 0, 275, 115, 0);
            al_draw_textf(text_hp, al_map_rgb(0, 0, 0), 150, 54, 0, "HP: %.0f", jg[0].vida);
            al_draw_textf(text_points, al_map_rgb(0, 0, 0), 130, 20, 0, "POINTS: %d", puntuacion);
            al_draw_textf(text_exp, al_map_rgb(0, 0, 0), 130, 92, 0, "XP: %d", exp);
            al_convert_mask_to_alpha(jg0_Idle, al_map_rgba(255, 0, 0, 255));
            for (cont_futbol = 0; cont_futbol < 6; cont_futbol++)
            {
                if (!futbol[cont_futbol].draw && (futbol[cont_futbol].hp <= 0.0))
                {
                    futbol[cont_futbol].posx = 0;
                    futbol[cont_futbol].posy = 0;
                }
                else if (futbol[cont_futbol].draw && futbol[cont_futbol].hp)
                {
                    al_draw_bitmap_region(futbol_img, 0, 0, PXL_W, PXL_H, futbol[cont_futbol].posx, futbol[cont_futbol].posy, 0);
                    al_convert_mask_to_alpha(futbol_img, al_map_rgba(255, 0, 0, 255));
                }
            }
            al_flip_display();
        }
    }

    exit_game();
    return 0;
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
        if ((fwall[y / PXL_H][(x / PXL_W)+2] == 'W')
            ||
            (fwall[y / PXL_H][(x / PXL_W) + 2] == 'p')
            ||
            (fwall[(y + PXL_H) / PXL_H][(x / PXL_W)+2] == 'W'))
            wall_true = true;
        else
            wall_true = false;
    }
    else
    {
        if ((fwall[y / PXL_H][(x - 1) / PXL_W] == 'W')
            ||
            (fwall[y / PXL_H][((x - 1) / PXL_W)] == 'p')
            ||
            (fwall[(y + PXL_H) / PXL_H][(x - 1) / PXL_W] == 'W'))
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
    for(contaE=0; contaE<CANT; contaE++)
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