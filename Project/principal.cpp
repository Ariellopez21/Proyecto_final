#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_memfile.h>
#include <allegro5/file.h>
#define WIDTH 240
#define HEIGHT  320
#define SIZE 20
#define PXL_H 16
#define PXL_W 12
#define KEY_SEEN     1
#define KEY_RELEASED 2
#define VALOR_INIT_SALTO 10
#define VALOR_GRAVITY 10

struct colision                 //Aún averiguando si usar esto o no...
{
    int xy1;
    int xy2;
    int xy3;
    int xy4;
};
typedef struct colision coll;

struct fisicas
{
    int gravedad;               //viene siendo el aumento de pos_y hacia abajo
    coll coll_enemy;            //abarca los 4 tipos de enemigos
    coll colL_block;            //abarca cañon - plataforma - suelo
    coll coll_jg;               //segun yo abarcará solo jg0 - jg1
};
typedef struct fisicas fis;
struct player
{
    fis phy;
    int posx;
    int posy;
    int fase;                   //identifica al jg0, jg1, jg2
    int salto;                  //viene siendo el aumento de pos_y hacia arriba
};
typedef struct player jugador;
int main()
{
    /*_______________________________________________________________________________________________
    ///////////////////////////////////////DECLARAR VARIABLES////////////////////////////////////////
    _________________________________________________________________________________________________*/
    FILE* fmapa0;
    int L_i = 0, L_j = 0, x = 0, y = 0, i = 0, j = 0;
    char mapa0[SIZE][SIZE], basura;
    bool done = false;
    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));
    bool flag_key_up_true = false;
    /*_______________________________________________________________________________________________
    ///////////////////////////////////////INICIAR ARCHIVO///////////////////////////////////////////
    _________________________________________________________________________________________________*/
    fmapa0 = fopen("C:/Users/ariel/OneDrive/Escritorio/IMG/MAPAS/mapa0.txt", "r");
    if (fmapa0 == NULL)
    {
        printf("ERROR");
        return 0;
    }
    for (L_i = 0; L_i < SIZE; L_i++)
    {
        for (L_j = 0; L_j < SIZE; L_j++)
        {
            fscanf(fmapa0, "%c", &mapa0[L_i][L_j]);
        }
        fscanf(fmapa0, "%c", &basura);
    }
    for (L_i = 0; L_i < SIZE; L_i++)
    {
        for (L_j = 0; L_j < SIZE; L_j++)
        {
            printf("%c", mapa0[L_i][L_j]);
        }
        printf("\n");
    }
    fclose(fmapa0);
    /*_______________________________________________________________________________________________
    ///////////////////////////////////////INICIAR ALLEGRO///////////////////////////////////////////
    _________________________________________________________________________________________________*/
    al_init();
    al_init_image_addon();
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
    ALLEGRO_BITMAP* sky = al_load_bitmap("C:/Users/ariel/OneDrive/Escritorio/IMG/BG/sky.png");
    ALLEGRO_BITMAP* dirt = al_load_bitmap("C:/Users/ariel/OneDrive/Escritorio/IMG/BG/dirt.png");
    ALLEGRO_BITMAP* platform = al_load_bitmap("C:/Users/ariel/OneDrive/Escritorio/IMG/BG/platform.png");
    /*
       * jg2, * jg3,                                           //Fases del jugador
       * fut, * bask, * tennis, * american, * cannon, * boss,  //Enemigos
       * llave_inglesa, * engranaje, * bateria;                //Puntos
    */
    /*_______________________________________________________________________________________________
    ///////////////////////////////////////INICIALIZAR JUGADOR///////////////////////////////////////
    _________________________________________________________________________________________________*/
    jugador jg0;
    jg0.fase = 0;
    jg0.posx = WIDTH / 2;
    jg0.posy = HEIGHT - (PXL_H*2);
    jg0.phy.gravedad = VALOR_GRAVITY;
    jg0.salto = VALOR_INIT_SALTO;
    jg0.phy.coll_jg.xy1 = 1;
    jg0.phy.coll_jg.xy2 = 1;
    jg0.phy.coll_jg.xy3 = 1;
    jg0.phy.coll_jg.xy4 = 1;
    ALLEGRO_BITMAP* jg0_bitmap = al_load_bitmap("C:/Users/ariel/OneDrive/Escritorio/IMG/PLAYER/player1_an0.png");
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
                jg0.posy = jg0.posy - jg0.salto;
                if (jg0.salto > 0)
                    jg0.salto--;
                else
                    flag_key_up_true = true;
            }
            else
            {
                jg0.salto = VALOR_INIT_SALTO;
                jg0.posy = jg0.posy + jg0.phy.gravedad;
                //if(colision entre plataforma y personaje). Actualmente la condición no existe, pero es porque necesito colisión!
                flag_key_up_true = false;
            }
            //if (key[ALLEGRO_KEY_DOWN])      //RESERVADO PARA jg2 -> aumenta su tamaño y tendrá posibilidad de agacharse. Aún solo idea.
                //jg2.posy;
            if (key[ALLEGRO_KEY_LEFT])
            {
                jg0.posx = jg0.posx - 3;
                if (jg0.posx <= (0 - PXL_W/2))
                    jg0.posx = WIDTH;
            }
            if (key[ALLEGRO_KEY_RIGHT])
            {
                jg0.posx = jg0.posx + 3;
                if (jg0.posx >= (WIDTH + PXL_W))
                    jg0.posx = 0;
            }
            if (key[ALLEGRO_KEY_ESCAPE])
                done = true;

            for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
                key[i] &= KEY_SEEN;
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
            key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
            break;
        case ALLEGRO_EVENT_KEY_UP:
            key[event.keyboard.keycode] &= KEY_RELEASED;
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }

        if (!sky || !jg0_bitmap || !platform || !dirt)
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
                    if (mapa0[i][j] == 'x')
                    {
                        al_draw_bitmap(sky, j * PXL_W, i * PXL_H, 0);
                    }
                    if (mapa0[i][j] == 's')
                    {
                        al_draw_bitmap(dirt, j * PXL_W, i * PXL_H, 0);
                    }
                    if (mapa0[i][j] == 'p')
                    {
                        al_draw_bitmap(platform, j * PXL_W, i * PXL_H, 0);
                    }
                }
            }
            if (jg0.posy >= (HEIGHT - (PXL_H * 2)))                 //LIMITE INFERIOR, por ahora es sobre el pixel de suelo pues aun no hay colisiones implementadas.
                jg0.posy = HEIGHT - (PXL_H * 2);
            al_draw_bitmap(jg0_bitmap, jg0.posx, jg0.posy, 0);
            al_convert_mask_to_alpha(jg0_bitmap, al_map_rgb(122, 9, 250));
            al_flip_display();
        }
    }
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_bitmap(sky);
    al_destroy_bitmap(dirt);
    al_destroy_bitmap(platform);
    al_destroy_bitmap(jg0_bitmap);
}