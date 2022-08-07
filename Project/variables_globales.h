#pragma once
#define FASES 3
#define WIDTH 600
#define HEIGHT  800
#define SIZE 20
#define PXL_W 30
#define PXL_H 40
#define KEY_SEEN     1
#define KEY_RELEASED 2
#define VALOR_INIT_SALTO 17
#define VALOR_GRAVITY 22
#define VALOR_VEL_JG 6
#define TAM_PLATFORM 42
#define TAM_DIRT 20
ALLEGRO_EVENT_QUEUE* queue;
ALLEGRO_TIMER* timer;
ALLEGRO_DISPLAY* disp;
ALLEGRO_EVENT event;
bool done = false;
ALLEGRO_BITMAP
* sky, * dirt, * platform, * perfil, * pwup, * bar,
* jg0_Idle, * jg0_Walk, * jg0_Jump, * jg0_Punch, * jg0_Damage,
* jg1_Idle, * jg1_Walk, * jg1_Jump, * jg1_Punch, * jg1_Damage,
* menu_principal, * menu_principal1, * menu_principal2, * menu_principal3,
* menu_history, * menu_instructions, * menu_instructions1,
* menu_ranking,
* pause;
