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
ALLEGRO_FONT* text_hp, *text_points, *text_exp;
ALLEGRO_EVENT_QUEUE* queue;
ALLEGRO_TIMER* timer;
ALLEGRO_DISPLAY* disp;
ALLEGRO_EVENT event;
bool done = false;
ALLEGRO_BITMAP
* sky, *sky_scroll, *dirt, * platform, * perfil, * pwup, * bar, *interfaz,						//SCENE
* jg0_Idle, * jg0_Walk, * jg0_Jump, * jg0_Punch, * jg0_Damage,			//JUGADOR FASE 1
* jg1_Idle, * jg1_Walk, * jg1_Jump, * jg1_Punch, * jg1_Damage,			//JUGADOR FASE 2
* menu_principal, * menu_principal1, * menu_principal2, * menu_principal3,	//MENU PRINCIPAL
* menu_history, * menu_instructions, * menu_instructions1,					//MENU -> JUGAR
* menu_ranking,																//MENU -> RANKING
* pause, * pause1, * pause2,												//JUEGO -> PAUSA 
* futbol_img, * basket_img, * tennis_img;									//ENEMIGOS