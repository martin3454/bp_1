
#include "MKL25Z4.h"



void cekej (uint32_t delay_ms);

void PinInit();

//4094 FUNKCE SR
void SR_STR();
void SR_CLK();
void SR_L();
void SR_H();
void SR_WriteData(uint8_t data);

//GDM LOW LEVEL
void Glcd_Enable_H();
void Glcd_Enable_L();
void Glcd_RS_L();
void Glcd_RS_H();
void Glcd_EnableControler(uint8_t control);
void Glcd_DisableControler(uint8_t control);
void GlcdInit();
void Glcd_WriteCommand(uint8_t cmd, uint8_t control);
void Glcd_WriteData(uint8_t dat);



void SetPosition(uint8_t col, uint8_t row);
void SetPixel(uint8_t x, uint8_t y);

//nove
void SetColor(uint8_t col);

void FillScreen();
void ClearScreen();


//void GLCD_FillScreen_Ddram();    // smazat
//void GLCD_ClearScreen_Ddram();	// smazat


void Line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void Rectangle(uint8_t x, uint8_t y, uint8_t a, uint8_t b);
void FullRectangle(uint8_t x, uint8_t y, uint8_t a, uint8_t b);
void Vline(uint8_t x1, uint8_t y1, uint8_t y2);
void Hline(uint8_t x1, uint8_t x2, uint8_t y1);
void Circle(uint8_t x, uint8_t y, uint8_t r);
void FullCircle(uint8_t x, uint8_t y, uint8_t r);
void BitMapPrint(int *bitmap, int delka);
void StartScreen();


//ddram
void Ddram_Clear();
void Ddram_Set();
uint8_t Ddram_Read();
void Ddram_Write(uint8_t y, uint8_t x);


//ZNAKOVA SADA
void WriteChar(char charToWrite);
void WriteString(char* str);
unsigned char ReadByteFromRom(char * ptr);

void font_test();



