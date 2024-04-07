/*
 * Grafični gonilnik za platformo MiŠKo3.
 * Vsebuje:
 *   - lcd.{c,h}                Inicializacija in osnovno upravljanje zaslona
 *   - lcd_ili9341.{c,h}        Strojni vmesniki za inicializacijo in nastavljanje
 *                              krmilnika Ili9341 prek STMovega pomnilniškega vmesnika FMC
 *   - lcd_ili9341_registers.h  Seznam ukazov iz podatkovnega lista krmilnika Ili9341
 *   - lcd_demo.{c,h}           Grafični rutini za opcijski `Intro' funkciji
 *   - lcd_grafika.{c,h}        Bitni tabeli s slikama za `Intro' funkciji
 *
 * (C) 2022 Nejc Bertoncelj <nbertoncelj afna student.uni-lj.si>
 *
 * Deli povzeti po vmesniku platforme MiŠKo2
 * (C) 2015 Pirc, Jankovec, Matič et al, Fakulteta za elektrotehniko
 */

#include "lcd.h"

/*!
 * @brief Nizkonivojska inicializacija zaslona
 * @internal
 */
static void LCD_IO_Init()
{
	LCD_RST_LOW();
	HAL_Delay(120);
	LCD_RST_HIGH();
	HAL_Delay(120);
}

/*!
 * @brief Strojno pospešen izris polnega pravokotnega polja
 * @param x x koordinata izhodišča
 * @param y y koordinata izhodišča
 * @param h višina polja
 * @param w širina polja
 * @param c podatek o barvi
 * @internal
 *
 * Funkcija izbere želeno območje, potem pa tolikokrat pošlje izbrano barvo,
 * kolikor slikovnih točk je potrebnih.
 */
void LCD_FillRect(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint16_t c)
{
	uint32_t max_count   = ILI9341_GetParam(LCD_AREA);     /* Št. vseh pikslov     */
	uint32_t pixel_count = ((w + 1) - x) * ((h + 1) - y);  /* Dejansko št. pikslov */

	if(pixel_count > max_count)
		pixel_count = max_count;

	// Izbor koordinat piksla
	ILI9341_SetDisplayWindow(x, y, w, h);

	ILI9341_SendRepeatedData(c, pixel_count);
	//while (pixel_count) {
	//	LCD_IO_SendData((uint16_t *)&c, LCD_IO_DATA_WRITE_CYCLES);
	//	pixel_count--;
	//}
}


void LCD_Tetromino(Tetromino t) {
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			int gridIndex = rotateTetromino(x, y, t.rotation);
			uint16_t tetrominoValue = t.grid[gridIndex];
			if (tetrominoValue != 0) {  // If the current block of the tetromino is true
				int pixelX = (t.x + x-1)*10;
				int pixelY = (t.y + y)*10;
				ILI9341_SetDisplayWindow(pixelX, pixelY, 10, 10);
				ILI9341_SendRepeatedData(tetrominoValue, 10*10);
			}
		}
	}
}

void LCD_PlayingField(uint16_t fieldArray[], int fullRow[]) {
	for (int y = 0; y < 25; y++) {
		for (int x = 0; x < 33; x++) {
			uint16_t faValue = fieldArray[y * 34 + x+1];
			if (fullRow[y] == 32) {
				ILI9341_SetDisplayWindow(x*10, y*10, 10, 10);
				ILI9341_SendRepeatedData(C_GOLDEN_ROD, (10)*(10));
			}
			else if (faValue != 0) {
				ILI9341_SetDisplayWindow(x*10, y*10, 10, 10);
				ILI9341_SendRepeatedData(faValue, (10)*(10));
			}
		}
	}
}

void LCD_TetrisFrame(Tetromino t, uint16_t field[], int fullRow[]) {
	LCD_Tetromino(t);
	LCD_PlayingField(field, fullRow);
}

/*!
 * @brief Glavna inicializacija zaslona
 *
 * Inicializacija nastavi privzet barvni prostor (RGB565), orientacijo zaslona, vklopi osvetlitev,
 * zapolni zaslon s črno barvo in nastavi bel tekst na črni podlagi.
 * @note Za inicializacijo posameznih strojnih enot mora poskrbeti uporabnik (npr. FMC)
 */
void LCD_Init()
{
	// Resetiraj V/I linijo zaslona
	LCD_IO_Init();

	// Inicializiraj krmilnik Ili9341 v barvnem prostoru RBG565 in brez zasuka slike
	ILI9341_Init(ILI9341_COLORSPACE_RBG565, ILI9341_MISKO_ROTATE_0);
	ILI9341_DisplayOn();

	LCD_ClearScreen();
	// Gornja funkcija se bo zaključila pred izbrisom celega zaslona, ker si FMC zapomni vse
	// ukaze in sporoči, da se je zaključil prenos, ne pa pošiljanje.
	// Brez zamika bo zaslon za trenutek utripnil belo. Prej:  HAL_Delay(25);
	ILI9341_WaitTransfer();
	LCD_SetBacklight(1);
}

/*!
 * @brief Vklopi/izklopi osvetlitev zaslona
 * @param state logična vrednost
 */

void LCD_SetBacklight(uint8_t state)
{
	if (state == 1)
		LCD_BCKL_ON();
	else
		LCD_BCKL_OFF();
}

/*!
 * @brief Počisti zaslon (prebarvaj s črno barvo)
 */
void LCD_ClearScreen()
{
	ILI9341_SetDisplayWindow(0, 0, 320, 240);
	ILI9341_SendRepeatedData(C_BLACK, 321*241);
}
