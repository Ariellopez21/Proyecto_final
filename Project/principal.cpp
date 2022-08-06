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
#include "Declaraciones-estructuras.h"

int main()
{
    /*_______________________________________________________________________________________________
    ///////////////////////////////////////DECLARAR VARIABLES////////////////////////////////////////
    _________________________________________________________________________________________________*/
    FILE* fmapa0;
    int L_i = 0, L_j = 0, x = 0, y = 0, i = 0, j = 0, k = 0;
    char mapa0[SIZE][SIZE], basura;
    bool done = false;
    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));
    bool flag_key_up_true = false;
    /*_______________________________________________________________________________________________
    ///////////////////////////////////////INICIAR ARCHIVO///////////////////////////////////////////
    _________________________________________________________________________________________________*/
    fmapa0 = fopen("Mapa_inicial.txt", "r");
    if (fmapa0 == NULL)
    {
        printf("ERROR");
        return 0;
    }
    for (L_i = 0; L_i < SIZE; L_i++)
    {
        for (L_j = 0; L_j < SIZE; L_j++)
            fscanf(fmapa0, "%c", &mapa0[L_i][L_j]); 
        fscanf(fmapa0, "%c", &basura);
    }
    for (L_i = 0; L_i < SIZE; L_i++)
    {
        for (L_j = 0; L_j < SIZE; L_j++)
            printf("%c", mapa0[L_i][L_j]);
        printf("\n");
    }
    printf("%c", mapa0[L_i][L_j]);
    fclose(fmapa0);
    /*_______________________________________________________________________________________________
    ///////////////////////////////////////INICIAR ALLEGRO///////////////////////////////////////////
    _________________________________________________________________________________________________*/
    al_init();
    al_init_image_addon();
    al_init_primitives_addon();
    al_init_font_addon();
    al_install_keyboard();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_DISPLAY* disp = al_create_display(WIDTH, HEIGHT);
    ALLEGRO_EVENT event;
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    /*_______________________________________________________________________________________________
    ///////////////////////////////////////REGISTRAR IMGS////////////////////////////////////////////
    _________________________________________________________________________________________________*/
    ALLEGRO_BITMAP* sky = al_load_bitmap("sky.bmp");
    ALLEGRO_BITMAP* dirt = al_load_bitmap("dirt.bmp");
    ALLEGRO_BITMAP* platform = al_load_bitmap("platform.bmp");
    ALLEGRO_BITMAP* perfil = al_load_bitmap("profile.bmp");
    ALLEGRO_BITMAP* pwup = al_load_bitmap("power_up.bmp");
    ALLEGRO_BITMAP* bar = al_load_bitmap("bar.bmp");
    ALLEGRO_BITMAP* jg0_bitmap = al_load_bitmap("jg0_momentaneo.bmp");

    //al_draw_bitmap_region(jg0_bitmap, tamaño1234, destino12);                     IMPORTANTE

    /*
       * jg2, * jg3,                                           //Fases del jugador
       * fut, * bask, * tennis, * american, * cannon, * boss,  //Enemigos
       * llave_inglesa, * engranaje, * bateria;                //Puntos
    */
    /*_______________________________________________________________________________________________
    ///////////////////////////////////////INICIALIZAR JUGADOR///////////////////////////////////////
    _________________________________________________________________________________________________*/
    for(i=0; i<FASES; i++)
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
        if (!sky || !jg0_bitmap || !platform || !dirt || !pwup || !perfil || !bar)
        {
            printf("NO SE CARGÓ");
            return 0;
        }
        if (al_is_event_queue_empty(queue) && (!done))
        {
            //Aquí debería partir la colisión creo...
            al_clear_to_color(al_map_rgb(0, 0, 0));
            for (i = 0; i < SIZE; i++)
            {
                for (j = 0; j < SIZE; j++)
                {
                    if (mapa0[i][j] == '0')
                    {
                        al_draw_bitmap(sky, j * PXL_W, i * PXL_H, 0);
                    }
                    if (mapa0[i][j] == 'D')
                    {
                        al_draw_bitmap(dirt, j * PXL_W, i * PXL_H, 0);
                    }
                    if (mapa0[i][j] == 'p')
                    {
                        al_draw_bitmap(platform, j * PXL_W, i * PXL_H, 0);
                    }
                    if (mapa0[i][j] == 'O')
                    {
                        al_draw_bitmap(perfil, j * PXL_W, i * PXL_H, 0);
                    }
                    if (mapa0[i][j] == 'U')
                    {
                        al_draw_bitmap(pwup, j * PXL_W, i * PXL_H, 0);
                        al_convert_mask_to_alpha(jg0_bitmap, al_map_rgb(120, 8, 249));
                    }
                    if (mapa0[i][j] == 'B')
                    {
                        al_draw_bitmap(bar, j * PXL_W, i * PXL_H, 0);
                    }
                }
            }
            if (jg[0].posy >= (HEIGHT - (PXL_H * 2)))                 //LIMITE INFERIOR, por ahora es sobre el pixel de suelo pues aun no hay colisiones implementadas.
                jg[0].posy = HEIGHT - (PXL_H * 2);
            al_draw_bitmap(jg0_bitmap, jg[0].posx, jg[0].posy, 0);
            al_convert_mask_to_alpha(jg0_bitmap, al_map_rgb(121, 9, 250));
            al_flip_display();
        }
    }
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_bitmap(sky);
    al_destroy_bitmap(dirt);
    al_destroy_bitmap(platform);
    al_destroy_bitmap(bar);
    al_destroy_bitmap(pwup);
    al_destroy_bitmap(perfil);
    al_destroy_bitmap(jg0_bitmap);
    return 0;
}