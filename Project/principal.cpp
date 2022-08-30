#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "Encabezados/variables_globales.h"
#include "Encabezados/struct-prototypes.h"
#include "Encabezados/archivos.h"
#include "Encabezados/dibujado.h"
#include "Encabezados/funciones_menu.h"
#include "Encabezados/player.h"
#include "Encabezados/enemy.h"
int main()
{
    /*_______________________________________________________________________________________________
    ///////////////////////////////////////DECLARAR VARIABLES////////////////////////////////////////
    _________________________________________________________________________________________________*/
    int x = 0, y = 0, i = 0, j = 0, tipo = 1, cont_futbol = 0, puntuacion = 0, exp = 0, recorrido = 0;
    float tempo_enemy = -12.0, tempo_enemy_reset = 0.0, tiempo = 0.0;
    int mouseX = 10, mouseY = 10, MouseSpeed = 5;
    char mapa[SIZE][SIZE];
    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));
    int mantener_z = VALOR_INIT_SALTO;
    bool pausa = false, flag_key_p_true = false, flag_key_x_true = false,
        coll_left = false, coll_right = false, coll_up = false, coll_down = false;
    struct ranking rank[MAX_RANK];
    /*_______________________________________________________________________________________________
    ///////////////////////////////////////INICIAR ARCHIVO///////////////////////////////////////////
    _________________________________________________________________________________________________*/
    tipo = ABRIR_MAPA(mapa, tipo);       //TIPO: decide que mapa leerá...
    /*_______________________________________________________________________________________________
    ///////////////////////////////////////INICIAR ALLEGRO///////////////////////////////////////////
    _________________________________________________________________________________________________*/
    al_init();
    al_init_image_addon();
    al_install_keyboard();
    al_install_mouse();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_acodec_addon();
    al_install_audio();

    text_hp = al_create_builtin_font();
    text_points = al_create_builtin_font();
    text_exp = al_create_builtin_font();
    dead_text = al_load_font("Font/final_font.TTF", 25, 0);
    timer = al_create_timer(1.0 / 30.0);
    timer_enemy = al_create_timer(1.0);
    queue = al_create_event_queue();
    disp = al_create_display(WIDTH, HEIGHT);

    al_reserve_samples(10);
    SOUND = al_load_sample("OST/punch_sound.ogg");

    OST_MENUSAMPLE = al_load_sample("OST/menuost.ogg");
    OST_MENUINTANCE = al_create_sample_instance(OST_MENUSAMPLE);
    al_set_sample_instance_playmode(OST_MENUINTANCE, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(OST_MENUINTANCE, al_get_default_mixer());

    OST_GAMESAMPLE = al_load_sample("OST/playgame.ogg");
    OST_GAMEINSTANCE = al_create_sample_instance(OST_GAMESAMPLE);
    al_set_sample_instance_playmode(OST_GAMEINSTANCE, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(OST_GAMEINSTANCE, al_get_default_mixer());

    OST_OVERSAMPLE = al_load_sample("OST/gameover.ogg");
    OST_OVERINSTANCE = al_create_sample_instance(OST_OVERSAMPLE);
    al_set_sample_instance_playmode(OST_OVERINSTANCE, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(OST_OVERINSTANCE, al_get_default_mixer());

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
    sky_scroll = al_load_bitmap("Sprites/Escenario/sky_scroll.png");
    interfaz = al_load_bitmap("Sprites/Escenario/Interfaz.png");

    jg0_Idle = al_load_bitmap("Sprites/Jugador/jg0_Idle_Walk.bmp");

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
    go_screen = al_load_bitmap("Screen/gameover_screen.png");
    /*_______________________________________________________________________________________________
    ///////////////////////////////////////INICIALIZAR JUGADOR///////////////////////////////////////
    _________________________________________________________________________________________________*/
    for (i = 0; i < FASES; i++)
        VARIABLES_JUGADOR(jg[i], i);
    /*_______________________________________________________________________________________________
    ////////////////////////////////////INICIALIZAR ENEMIGOS/////////////////////////////////////////
    _________________________________________________________________________________________________*/
    srand(time(0));
    /*modificado profe....*/
    VARIABLES_ENEMIGOS_INICIAL(mapa, futbol, i);        //INICIALIZAR ENEMIGOS
    /*________________________________________________________________________________________________
    /////////////////////////////////////////INICIA EL JUEGO//////////////////////////////////////////
    _________________________________________________________________________________________________*/
    reed_rank(rank, &recorrido);        //Lee el ranking
    show_rank(rank, recorrido);         //Corroborar que el ranking esté bien.
    done = func_menu(rank);
    func_instructions();
    al_destroy_sample_instance(OST_MENUINTANCE);
    al_destroy_sample(OST_MENUSAMPLE);
    al_start_timer(timer);
    al_play_sample_instance(OST_GAMEINSTANCE);
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
                mantener_z = VALOR_INIT_SALTO;
                jg[0].posy -= jg[0].gravity;

            }
            if (!coll_up)
            {
                if (key[ALLEGRO_KEY_Z] && (mantener_z != 0))
                {
                    jg[0].posy -= jg[0].gravity;
                    mantener_z--;
                }
                else
                {
                    jg[0].posy += jg[0].gravity;
                }
            }
            /*if (key[ALLEGRO_KEY_Z] && !flag_key_up_true)
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
                }*/
            else
            {
                mantener_z = 0;
                jg[0].posy += jg[0].gravity;
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
            //PAUSA-----------------------------------------------------
            if (key[ALLEGRO_KEY_P] && !flag_key_p_true)
            {
                flag_key_p_true = true;
                printf("entra?\t");
            }
            if (flag_key_p_true && !key[ALLEGRO_KEY_P])
            {
                done = func_pause(pausa);
                flag_key_p_true = false;
                printf("OUT?\t");
            }
            //GOLPE-----------------------------------------------------
            if (key[ALLEGRO_KEY_X])
            {
                puntuacion = golpe(jg, futbol, puntuacion);
            }
            //MUERTE-----------------------------------------------------
            if (jg[0].vida <= 0)
            {
                done = true;
            }
            //ESCAPE-----------------------------------------------------
            if (key[ALLEGRO_KEY_ESCAPE])
            {
                done = true;
            }

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
        tempo_enemy += TIME;
        tempo_enemy_reset += TIME;
        tiempo += TIME;
        //PUNTUACIÓN POR TIEMPO-----------------------------------------------------
        if (tiempo >= 2.0)
        {
            puntuacion++;
            tiempo = 0.0;
        }
        //GENERAR POR PRIMERA VEZ-----------------------------------------------------
        if (tempo_enemy >= -10.0 && tempo_enemy <= -5.0)         //GENERAR POR PRIMERA VEZ
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
        //REGENERACIÓN ENEMIGOS-----------------------------------------------------
        if (tempo_enemy_reset >= 15.0 && tempo_enemy_reset <= 18.0)
        {
            for (cont_futbol = 0; cont_futbol < CANT; cont_futbol++)
            {
                if (futbol[cont_futbol].posx == 0.0 && futbol[cont_futbol].posy == 0.0 && futbol[cont_futbol].flag_death)
                {
                    printf("RESET\t");
                    VARIABLES_ENEMIGOS_RESET(mapa, futbol, cont_futbol, tipo);
                    printf("VEL:[%.3f]\t HP:[%.3f] --- X:[%d]; Y:[%d]\n", futbol[cont_futbol].velx, futbol[cont_futbol].hp, futbol[cont_futbol].posx, futbol[cont_futbol].posy);
                }
            }
        }
        //RESET TIME-----------------------------------------------------
        if (tempo_enemy_reset >= 20.0 && tempo_enemy >= 0.0)
        {
            printf("\nCERO\t");
            tempo_enemy = -15.0;
            tempo_enemy_reset = 0.0;
        }

        //MOVIMIENTO-----------------------------------------------------
        for (cont_futbol = 0; cont_futbol < CANT; cont_futbol++)
        {
            mov_futbol(futbol[cont_futbol], mapa);
        }
        //DAMAGE-----------------------------------------------------
        for (cont_futbol = 0; cont_futbol < CANT; cont_futbol++)
        {
            jg[0].vida = damage(jg[0], futbol[cont_futbol]);
        }
        //MUELTO-----------------------------------------------------
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

            if (jg[0].posy >= (HEIGHT - PXL_H))     //Condición: que no se escape de los límites del mapa.
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
    al_destroy_sample_instance(OST_GAMEINSTANCE);
    al_destroy_sample(OST_GAMESAMPLE);
    al_play_sample_instance(OST_OVERINSTANCE);
    if(puntuacion>0)
    {
        while (done)
        {
            al_wait_for_event(queue, &event);
            switch (event.type)
            {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = false;
                break;
            case ALLEGRO_KEY_ENTER:
                done = false;
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                break;
            }
            if (al_is_event_queue_empty(queue) && (done))
            {
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_scaled_bitmap(go_screen, 0, 0, 300, 400, 0, 0, WIDTH, HEIGHT, 0);
                //al_draw_text(dead_text, al_map_rgb(255, 255, 255), 200, 200, 0, "Ariellopez");
                //al_draw_text(dead_text, al_map_rgb(255, 255, 255), 200, 200, 0, "Ariellopez");
                al_flip_display();
            }
        }
        comparacion_rank(rank, puntuacion);
    }
    al_destroy_sample_instance(OST_OVERINSTANCE);
    al_destroy_sample(OST_OVERSAMPLE);

    exit_game();
    return 0;
}