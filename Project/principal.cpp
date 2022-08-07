#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_memfile.h>
#include <allegro5/file.h>
#include "variables_globales.h"
#include "estructuras_funciones.h"
#include "archivos.h"
#include "dibujado.h"
void func_menu();
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
    bool flag_key_up_true = false;
    /*_______________________________________________________________________________________________
    ///////////////////////////////////////INICIAR ARCHIVO///////////////////////////////////////////
    _________________________________________________________________________________________________*/
    tipo = ABRIR_MAPA(mapa, tipo);       //TIPO: decide si es mapa 1 o 2, se usará más adelante...
    /*_______________________________________________________________________________________________
    ///////////////////////////////////////INICIAR ALLEGRO///////////////////////////////////////////
    _________________________________________________________________________________________________*/
    al_init();
    al_init_image_addon();
    al_init_primitives_addon();
    al_init_font_addon();
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
    sky = al_load_bitmap("sky.bmp");
    dirt = al_load_bitmap("dirt.bmp");
    platform = al_load_bitmap("platform.bmp");
    perfil = al_load_bitmap("profile.bmp");
    pwup = al_load_bitmap("power_up.bmp");
    bar = al_load_bitmap("bar.bmp");

    jg0_Idle = al_load_bitmap("jg0_Idle_Walk.bmp");
    jg0_Walk = al_load_bitmap("jg0_Idle_Walk.bmp");
    jg0_Jump = al_load_bitmap("jg0_Jump.bmp");
    jg0_Punch = al_load_bitmap("jg0_Punch.bmp");
    jg0_Damage = al_load_bitmap("jg0_Damage.bmp");

    jg1_Idle = al_load_bitmap("jg1_Idle_Walk.bmp");
    jg1_Walk = al_load_bitmap("jg1_Idle_Walk.bmp");
    jg1_Jump = al_load_bitmap("jg1_Jump.bmp");
    jg1_Punch = al_load_bitmap("jg1_Punch.bmp");
    jg1_Damage = al_load_bitmap("jg1_Damage.bmp");
    /*
       * fut, * bask, * tennis, * american, * cannon, * boss,  //Enemigos
       * llave_inglesa, * engranaje, * bateria;                //Puntos
    */
    menu_principal = al_load_bitmap("menu_0.bmp");
    menu_principal1 = al_load_bitmap("menu_1.bmp");        //CURSOR START
    menu_principal2 = al_load_bitmap("menu_2.bmp");        //CURSOR RANKING
    menu_principal3 = al_load_bitmap("menu_3.bmp");        //CURSOR EXIT
    menu_ranking = al_load_bitmap("ranking.bmp");
    menu_history = al_load_bitmap("history.bmp");         
    menu_instructions = al_load_bitmap("instructions0.bmp");
    menu_instructions1 = al_load_bitmap("instructions1.bmp");  //CURSOR OK!
    pause = al_load_bitmap("pause.bmp");                    //MANTENER RELACIÓN DE ASPECTO
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
    ////////////////////////////////////INICIALIZAR POSICIÓN BLOCKS//////////////////////////////////
    _________________________________________________________________________________________________*/
    /*________________________________________________________________________________________________
    /////////////////////////////////////////INICIA EL JUEGO//////////////////////////////////////////
    _________________________________________________________________________________________________*/
    al_start_timer(timer);
    while (!done)
    {
        func_menu();
        //->func_rank();
        //->func_innstrucciones()
        //etc...
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:                                       //MOV. JUGADOR
            if (key[ALLEGRO_KEY_UP] && !flag_key_up_true)
            {
                jg[0].posy = jg[0].posy - jg[0].salto;
                if (jg[0].salto > 0)
                    jg[0].salto--;
                else
                    flag_key_up_true = true;
            }
            else
            {
                jg[0].salto = VALOR_INIT_SALTO;
                jg[0].posy = jg[0].posy + jg[0].gravity;
                //if(colision entre plataforma y personaje). Actualmente la condición no existe, pero es porque necesito colisión!
                flag_key_up_true = false;
            }
            if (key[ALLEGRO_KEY_LEFT])
            {
                jg[0].posx = jg[0].posx - 13;
                if (jg[0].posx <= (0 - PXL_W))
                    jg[0].posx = WIDTH;
            }
            if (key[ALLEGRO_KEY_RIGHT])
            {
                jg[0].posx = jg[0].posx + 13;
                if (jg[0].posx >= WIDTH)
                    jg[0].posx = 0 - PXL_W;
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
            break;
        case ALLEGRO_EVENT_KEY_UP:
            key[event.keyboard.keycode] &= KEY_RELEASED;
            break;
        }
        if (!sky || !platform || !dirt || !pwup || !perfil || !bar)
        {
            printf("NO SE CARGÓ");
            return 0;
        }
        if (al_is_event_queue_empty(queue) && (!done))
        {
            //Aquí debería partir la colisión creo...
            al_clear_to_color(al_map_rgb(0, 0, 0));
            DRAW_MAP_SINCE_MAPA(mapa, sky, platform, dirt, pwup, perfil, bar);

            if (jg[0].posy >= (HEIGHT - (PXL_H * 2)))                 //LIMITE INFERIOR, por ahora es sobre el pixel de suelo pues aun no hay colisiones implementadas.
                jg[0].posy = HEIGHT - (PXL_H * 2);

            al_draw_bitmap_region(jg0_Idle, 0, 0, PXL_W, PXL_H, jg[0].posx, jg[0].posy, 0);
            al_convert_mask_to_alpha(jg0_Idle, al_map_rgb(107, 41, 115));
            al_flip_display();
        }
    }
    /*_______________________________________________________________________________________________
    /////////////////////////////////////////////FINALIZAR////////////////////////////////////////////
    _________________________________________________________________________________________________*/
    exit_game();
    return 0;
}

void func_menu()
{
    while (!done)
    {
        switch (event.type)
        {

        }
        if (al_is_event_queue_empty(queue) && (!done))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_flip_display();
        }
    }
}