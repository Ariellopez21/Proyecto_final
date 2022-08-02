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
#define MAXENEMY 4
#define FASES 3
#define SCENE 3
#define POINTS 3

enum colision_detectada_por_movimiento
{
    case_hostil_mov, case_jg, case_points
};
enum deteccion_movimiento
{
    arbitrario, establecido
};

struct desplazamientos1
{
    int posx;
    int posy;
    int velx;
    int vely;
};
typedef struct desplazamientos1 movimiento;

struct fisicas1
{
    movimiento mov;
    int col_det;
    int gravity;
};
typedef struct fisicas1 fis;

struct dinamico
{
    fis enemy[MAXENEMY];
    fis player[FASES];
};
typedef struct dinamico din;

enum colision_detectada_quieto
{
    case_friendly, case_hostil_qt
};

struct solido
{
    int col_quiet[2];
};
typedef struct solido sol;
struct estatico
{
    sol escenario[SCENE];
    sol consumible[POINTS];
};
typedef struct estatico est;

int main()
{
    /*_______________________________________________________________________________________________
    ///////////////////////////////////////DECLARAR VARIABLES////////////////////////////////////////
    _________________________________________________________________________________________________*/
    FILE* fmapa0;
    int L_i = 0, L_j = 0, x = 0, y = 0, i = 0, j = 0;
    char mapa0[SIZE][SIZE], basura, aux;
    bool done = false;
    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));
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
    ALLEGRO_BITMAP* jg1 = al_load_bitmap("C:/Users/ariel/OneDrive/Escritorio/IMG/PLAYER/player1_an0.png");
    al_draw_bitmap(jg1, j * PXL_W, i * PXL_H, 0);
    al_convert_mask_to_alpha(jg1, al_map_rgb(122, 9, 250));
    /*
       * jg2, * jg3,                                           //Fases del jugador
       * fut, * bask, * tennis, * american, * cannon, * boss,  //Enemigos
       * llave_inglesa, * engranaje, * bateria;                //Puntos
    */
    /////////////////////////////////////////////////////////////////////////////////////////////////

    al_start_timer(timer);
    while (!done)                   //Comienza el juego :D
    {
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            if (key[ALLEGRO_KEY_UP])
                y = y - 4;
            if (key[ALLEGRO_KEY_DOWN])
                y = y + 4;
            if (key[ALLEGRO_KEY_LEFT])
            {
                x = x - 3;
                if (x <= (0 - PXL_W))
                    x = WIDTH;
            }
            if (key[ALLEGRO_KEY_RIGHT])
            {
                x = x + 3;
                if (x >= (WIDTH + PXL_W))
                    x = 0;
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

        if (!sky || !jg1 || !platform || !dirt)
        {
            printf("NO SE CARGÓ");
            return 0;
        }

        if (al_is_event_queue_empty(queue) && (!done))
        {
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
            al_flip_display();
        }
    }
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_bitmap(sky);
    al_destroy_bitmap(dirt);
    al_destroy_bitmap(platform);
    al_destroy_bitmap(jg1);
    printf("hola");
    printf("hola mundo");
}