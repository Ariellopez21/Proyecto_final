#pragma once
//TAMAÑOS:
#define WIDTH 600				//WINDOW
#define HEIGHT  800				//WINDOW
#define SIZE 20					//ARCHIVO
#define PXL_W 30				//PIXEL
#define PXL_H 40				//PIXEL
#define PXL_CENTROW (PXL_W/2)	//CENTRO PIXEL
#define PXL_CENTROH (PXL_H/2)	//CENTRO PIXEL

#define KEY_SEEN     1			//MEMORIA KEY
#define KEY_RELEASED 2			//MEMORIA KEY

#define VALOR_INIT_SALTO 17
#define VALOR_GRAVITY 22
#define VEL_X0 12
#define FASES 3
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
