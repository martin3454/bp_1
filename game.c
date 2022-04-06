
#include "MKL25Z4.h"
#include "game.h"


uint8_t chobot_bitMap[]={

		0b01110000,
		0b00011000,
		0b01111100,
		0b10110110,
		0b00111100,
		0b00111100,
		0b00111100,
		0b10110110,
		0b01111100,
		0b00011000,
		0b01110000
	};

uint8_t chobot1_bitMap[]={

		0b00001110,
		0b10010000,
		0b01111100,
		0b00110110,
		0b00111100,
		0b00111100,
		0b00111100,
		0b00110110,
		0b01111100,
		0b10010000,
		0b00001110

	};

uint8_t meduza_bitMap[]={

		0b10000000,
		0b10110000,
		0b01001000,
		0b11111110,
		0b01111110,
		0b11011110,
		0b01111110,
		0b11111110,
		0b01001000,
		0b10110000,
		0b10000000
};

uint8_t meduza1_bitMap[]={

		0b01000000,
		0b10000000,
		0b01111000,
		0b11111110,
		0b01111110,
		0b11011110,
		0b01111110,
		0b11111110,
		0b01111000,
		0b10000000,
		0b01000000
};


uint8_t krakatice_bitMap[]={

		0b10000000,
		0b10000000,
		0b11011100,
		0b00110100,
		0b11111110,
		0b00111010,
		0b11111110,
		0b00110100,
		0b11011100,
		0b10000000,
		0b10000000
};


uint8_t krakatice1_bitMap[]={

		0b10000000,
		0b10000000,
		0b11011100,
		0b00110100,
		0b11101110,
		0b00101010,
		0b11101110,
		0b00110100,
		0b11011100,
		0b10000000,
		0b10000000
};


uint8_t tank_bitMap[]={

		0b11100000,
		0b11100000,
		0b11100000,
		0b11100000,
		0b11110000,
		0b11111000,
		0b11111111,
		0b11111000,
		0b11110000,
		0b11100000,
		0b11100000,
		0b11100000,
		0b11100000
};

uint8_t raketa_bitMap[]={

		0b11110000
};



uint8_t pozice_chobotnicX[NUM_COLS]={4, 19, 34, 49, 64};
uint8_t pozice_chobotnicY[NUM_ROWS]={4, 12, 20}; 							//0,9,17
AlienObject aliens[NUM_ROWS][NUM_COLS];
TankObject hrac;
GameObject raketa;
uint8_t score0, score1, score2;



int pockaj = -1;
int pockaj_hrac = -1;
int pockaj_raketa = -1;
int pohybX = 2;
int EnemaciCounter = RYCHLOST;
_Bool animace = 0;
_Bool GAME_ON = 1;
int y_f[3] = {4, 12, 20};
int drop = 0;



void Game_Start(){

	Enemy_Init();
	Tank_Init();
	Game_Stats();

	while(GAME_ON){

		Screen_Update();

		Enemy_Control();

		Rocket_Clear();

		Rocket_Control();

		Collision_Control();

		Tank_Clear();

		Tank_Control();

		Screen_Clear();
	}

	if(score0 + score1 + score2 == 15){
		FillScreen();
		SetPosition(25,33);
		WriteString("VYHRAL JSI");
	}
}



void Screen_Clear(){

	uint8_t i, j, sirka;

	if(drop){

		SetPosition(0, y_f[0] - 4);

		for(j = 0; j < 96; j++){
			Glcd_WriteData(0x00);
		}
	}

	for(i = 0 ; i < 3; i++){

		if(y_f[i] >= 0) SetPosition(0, y_f[i]);
		else {

			while(--pockaj >= 0);

			continue;
		}

		for(j = 0; j < 96; j++){
			Glcd_WriteData(0x00);
		}
	}

}

void Screen_Delete(){

	for(uint8_t i = 0; i < 64; i += 8){

		SetPosition(0,i);

		for(uint8_t j = 0; j < 96; j++)
			Glcd_WriteData(0x00);
	}

}



void Tank_Control(){

	if((PTA->PDIR & M_SW2) == 0 && hrac.ord.x + TANK_WIDTH < MAX_WIDTH )
		hrac.ord.x += TANK_STEPX;
	if((PTA->PDIR & M_SW1) == 0 && hrac.ord.x > 0)
		hrac.ord.x -= TANK_STEPX;

	//raketa
	if((PTA->PDIR & M_SW3) == 0 & raketa.status != ACTIVE){
		raketa.x = hrac.ord.x + (TANK_WIDTH / 2);
		raketa.y = TANK_STARTYPOS;
		raketa.status = ACTIVE;
	}
}

void Rocket_Control(){

	if(raketa.status == ACTIVE){
		if(raketa.y + RAKETA_HEIGH <= 0)
			raketa.status = ZNICEN;
		else raketa.y -= RAKETA_RYCHLOST;
	}
}

void Collision_Control(){

	Kolize_postava_raketa();
}

void Kolize_postava_raketa(){

	uint8_t j, i;

	if(raketa.status == ACTIVE){

		for(i = 0; i < NUM_ROWS; i++){

			if(raketa.status == ZNICEN) break;

			for(j = 0; j < NUM_COLS; j++){

				if(aliens[i][j].ord.status == ACTIVE){

					if(Kolize(aliens[i][j].ord.x, aliens[i][j].ord.y)){				//zasah

						aliens[i][j].ord.status=ZNICEN;

						switch(i){

							case 0: score0++;
							break;

							case 1: score1++;
							break;

							case 2: score2++;
							break;
						}

						Game_StatsRefresh();

						if(score0 + score1 + score2 == 15) GAME_ON = 0;

						raketa.status = ZNICEN;
						break;
					}
				}
			}
		}
	}


}


void Enemy_Control(){

	if((EnemaciCounter--) < 0){

		drop = 0;

		if(RightMosPos() + pohybX >= MAX_WIDTH || LeftMosPos() + pohybX <= 0){

			pohybX = -pohybX;

			drop = 1;

			if(score0 == 5) y_f[0] = -1;
			else y_f[0] += 4;

			if(score1 == 5) y_f[1] = -1;
			else y_f[1] += 4;

			if(score2 == 5) y_f[2] = -1;
			else y_f[2] += 4;
		}

		uint8_t j, i;

		for(i = 0; i < NUM_ROWS; i++){

			for(j = 0; j < NUM_COLS; j++){

				if(aliens[i][j].ord.status == ACTIVE){

					if(drop == 0){

						aliens[i][j].ord.x += pohybX;
					}else {

						aliens[i][j].ord.y += 4;
						uint8_t al_y = aliens[i][j].ord.y;
						uint8_t poloha = hrac.ord.y - 5;


						if(al_y >= poloha) Game_Over();
					}
				}
			}
		}
		EnemaciCounter = RYCHLOST;		//15 ide
		animace = !animace;

		if(score0 + score1 + score2 >= 6) {
			pockaj = 1550;
			pockaj_hrac = 100;
			pockaj_raketa = 10;
		}
		if(score0 + score1 + score2 >= 9){
			pockaj = 2500;
			pockaj_hrac = 600;
			pockaj_raketa = 10;
		}
		if(score0 + score1 + score2 >= 12){
			pockaj = 3600;
			pockaj_hrac = 1200;
			pockaj_raketa = 10;
		}

	}
}


void Screen_Update(){

	Tank_Update();
	if(raketa.status == ACTIVE) Rocket_Update();

	uint8_t j, i;

	for(j = 0; j < NUM_ROWS; j++){

		for(i = 0; i < NUM_COLS ; i++){

			if(aliens[j][i].ord.status == ACTIVE){

				SetPosition(aliens[j][i].ord.x, aliens[j][i].ord.y );

				switch(j){

						case 0:

								if(animace) Chobot_vykreslit();
								else Chobot1_vykreslit();

						break;

						case 1:

								if(animace) Meduza_vykreslit();
								else Meduza1_vykreslit();

						break;

						case 2:

								if(animace) Krakatice_vykreslit();
								else Krakatice1_vykreslit();
						break;
			  }
		  }else cekej(200);

		}
	}
}


void Game_Over(int poloha){

	GAME_ON = 0;
	Screen_Delete();
	SetPosition(40, 35);
	WriteString("Konec hry");

}

void Enemy_Init(){

	uint8_t j, i;

	for(i = 0; i < NUM_ROWS; i++){

		for(j = 0; j < NUM_COLS; j++){

			aliens[i][j].ord.x = pozice_chobotnicX[j];
			aliens[i][j].ord.y = pozice_chobotnicY[i];
			aliens[i][j].ord.status = ACTIVE;

		}
	}
}

void Chobot_vykreslit(){

	for(uint8_t x = 0; x < postavaDx; x++)
		Glcd_WriteData(chobot_bitMap[x]);
}

void Chobot1_vykreslit(){

	for(uint8_t x = 0; x < postavaDx; x++)
		Glcd_WriteData(chobot1_bitMap[x]);
}

void Tank_Update(){

	SetPosition(hrac.ord.x, hrac.ord.y );
	for(uint8_t x = 0; x < TANK_WIDTH; x++)
		Glcd_WriteData(tank_bitMap[x]);
}

void Tank_Clear(){

	while(--pockaj_hrac >= 0);

	SetPosition(hrac.ord.x, hrac.ord.y );
	for(uint8_t x = 0; x < TANK_WIDTH; x++)
		Glcd_WriteData(0x00);
}

void Rocket_Update(){

	SetPosition(raketa.x, raketa.y );
	Glcd_WriteData(raketa_bitMap[0]);
}

void Rocket_Clear(){

	while(--pockaj_raketa >= 0);
	SetPosition(raketa.x, raketa.y );
	Glcd_WriteData(0x00);
}

void Meduza_vykreslit(){

	for(uint8_t x = 0; x < postavaDx; x++)
		Glcd_WriteData(meduza_bitMap[x]);
}

void Meduza1_vykreslit(){

	for(uint8_t x = 0; x < postavaDx; x++)
		Glcd_WriteData(meduza1_bitMap[x]);
}

void Krakatice_vykreslit(){

	for(uint8_t x = 0; x < postavaDx; x++)
		Glcd_WriteData(krakatice_bitMap[x]);
}

void Krakatice1_vykreslit(){

	for(uint8_t x = 0; x < postavaDx; x++)
		Glcd_WriteData(krakatice1_bitMap[x]);
}


int LeftMosPos(){

	int i,down, nejmensi, leva_pos;
	nejmensi = 200;

	for(i = 0; i < NUM_COLS; i++){

		down = 0;

		while(down < NUM_ROWS){

			if(aliens[down][i].ord.status == ACTIVE){

				leva_pos = aliens[down][i].ord.x;
				if(leva_pos < nejmensi)

					nejmensi = leva_pos;
			}
			down++;
		}
		if(nejmensi < 200) return nejmensi;
	}
	return 0;
}

int RightMosPos(){

	int i,down, nejvetsi, prava_pos;
	nejvetsi = 0;

	for(i = NUM_COLS - 1; i >= 0; i--){

		down = 0;

		while(down < NUM_ROWS){

			if(aliens[down][i].ord.status == ACTIVE){

				prava_pos = aliens[down][i].ord.x + postavaDx;

				if(prava_pos > nejvetsi)
					nejvetsi = prava_pos;
			}
			down++;
		}
		if(nejvetsi > 0) return nejvetsi;
	}
	return 0;
}

_Bool Kolize(uint8_t alienX, uint8_t alienY ){
	return ((raketa.x  > alienX) & (raketa.x < alienX + postavaDx) & (raketa.y + RAKETA_HEIGH > alienY) & (raketa.y < alienY + postavaDy ));
}


void Game_StatsRefresh(){

	uint8_t i, j;

	for(i = 15; i < 64;i += 8){

		SetPosition(120, i);

		for(j = 0; j < 5; j++){
			Glcd_WriteData(0x00);
		}
	}
	SetPosition(120,15);
	WriteChar((char)score0+'0');

	SetPosition(120,25);
	WriteChar((char)score1+'0');

	SetPosition(120,40);
	WriteChar((char)score2+'0');

}


void Tank_Init(){

	PORTA->PCR[4] = 0x100;
	PORTA->PCR[5] = 0x100;
	PORTA->PCR[16] = 0x100;
	PORTA->PCR[17] = 0x100;

	PTA->PDDR &= ~(1<<4);  		//tlacitko 1-4 jako vstup
	PTA->PDDR &= ~(1<<5);
	PTA->PDDR &= ~(1<<16);
	PTA->PDDR &= ~(1<<17);

	hrac.ord.x=TANK_STARTXPOS;
	hrac.ord.y=TANK_STARTYPOS;

	raketa.status = ZNICEN;

	score0 = score1 = score2 = 0;

}

void Game_Stats(){

	Vline(96,0,63);

	SetPosition(102,15);
	Chobot_vykreslit();
	SetPosition(114,15);
	WriteString("=");
	SetPosition(120,15);
	WriteChar((char)score0+'0');

	SetPosition(102,25);
	Meduza_vykreslit();
	SetPosition(114,25);
	WriteString("=");
	SetPosition(120,25);
	WriteChar((char)score1+'0');

	SetPosition(102,40);
	Krakatice_vykreslit();
	SetPosition(114,40);
	WriteString("=", 1);
	SetPosition(120,40);
	WriteChar((char)score2+'0');

}
