
#include "MKL25Z4.h"


#define M_SW1  (1<<4)
#define M_SW2  (1<<5)
#define M_SW3  (1<<16)
#define M_SW4  (1<<17)

#define NUM_ROWS 3     //ROZMERY POLE PRO POZICE POSTAV
#define NUM_COLS 5
#define MAX_WIDTH 95	//SIRKA HERNI PLOCHY


#define RYCHLOST 6
#define postavaDx 11			//SIRKA NEPRATEL
#define postavaDy 7				//VYSKA NEPRATEL
#define INVADERS_DROP 4			//SKOK DOLU
//#define SPACE_BETWEEN_ALIENS 4
//#define SPACE_BETWEEN_ROWS 1


#define ACTIVE 0				//OBJEKT SE BUDE ZOBRAZOVAT
#define ZNICEN 2				//OBJEKT SE NEBUDE ZOBRAZOVAT

#define TANK_WIDTH 13
#define TANK_HEIGH 8
#define TANK_STEPX 2
#define TANK_STARTXPOS 63
#define TANK_STARTYPOS 60

#define RAKETA_HEIGH 4
#define RAKETA_WIDTH 1
#define RAKETA_RYCHLOST 4



typedef struct gameObject{
	int x;
	int y;
	uint8_t status;
}GameObject;


typedef struct alienObject{
	GameObject ord;
}AlienObject;


typedef struct tankObject{
	GameObject ord;
}TankObject;



////////////////////////////////
void Enemy_Init();
void Tank_Init();
void Screen_Update();
void Screen_Clear();
void Screen_Delete();


////////////////////////////////vykreslovani
void Tank_Update();
void Tank_Clear();
void Rocket_Update();
void Rocket_Clear();

void Chobot_vykreslit();
void Chobot1_vykreslit();
void Meduza_vykreslit();
void Meduza1_vykreslit();
void Krakatice_vykreslit();
void Krakatice1_vykreslit();

////////////////////////////pozice
int RightMosPos();
int LeftMosPos();

//////////////////////////////ridici logika
void Enemy_Control();
void Tank_Control();
void Rocket_Control();
void Collision_Control();
void Kolize_postava_raketa();
_Bool Kolize(uint8_t alienX, uint8_t alienY);

/////////////////////////////////////////obrazovky
void Game_Over();



void Game_Stats();
void Game_StatsRefresh();

void Game_Start();    ///hlavni smycka


