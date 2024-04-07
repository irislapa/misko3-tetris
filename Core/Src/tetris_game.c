
#include "tetris_game.h"

void UserPixelSetFunction(UG_S16 x, UG_S16 y, UG_COLOR c)
{
	ILI9341_SetDisplayWindow(x, y, 1, 1);
	ILI9341_SendData((LCD_IO_Data_t *)&c, 1);
}

UG_RESULT _HW_FillFrame_(UG_S16 x, UG_S16 y, UG_S16 w, UG_S16 h, UG_COLOR c)
{
	LCD_FillRect(x, y, w, h, c);

	return UG_RESULT_OK;
}


// global variables
UG_GUI gui;

uint16_t p_y = 240/2 - 100;
uint16_t p_x = 320/2 - 100;

int score = 0;
int rotations;
int fullRow[24] = {0};
int seed = 12345;
uint16_t fieldArray[34*25]={0};
coord_t joystick_raw, joystick_out;
joystick_t joystick;

typedef struct {
	buttons_enum_t name;
    int previousState;
    uint32_t lastPressTime;
} ButtonState;

ButtonState up = {BTN_UP, 0, 0};
ButtonState right = {BTN_RIGHT, 0, 0};
ButtonState down = {BTN_DOWN, 0, 0};
ButtonState left = {BTN_LEFT, 0, 0};
ButtonState ok = {BTN_OK, 0, 0};
ButtonState esc = {BTN_ESC, 0, 0};

typedef enum {
    JOY_LEFT,
	JOY_RIGHT
} direction;

typedef struct {
	direction dir;
    int previousState;
    uint32_t lastPressTime;
} joystickState;

typedef enum {
    START_SCREEN,
    GAMING_SCREEN,
    GAME_OVER_SCREEN
} GameState;

// field array has a "wall" of 1 cells around for easier collision detection
void initFA() {
	for (int y = 0; y < 25; y++) {
		for (int x = 0; x < 34; x++) {
			if (x==0 || x==33 || y==24) {
				fieldArray[y*34+x] = 1;
			}
			else fieldArray[y*34+x] = 0;
		}
	}
}

void initFR() {
	for (int i = 0; i < 24; i++) {
		fullRow[i] = 0;
	}
}


void writeToFA(Tetromino t) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            int i = (t.y+y) * 34 + t.x+x;
            uint16_t tetrominoValue = t.grid[rotateTetromino(x, y, t.rotation)];
            if (tetrominoValue != 0) {
            	fieldArray[i] = tetrominoValue;
            	fullRow[t.y+y] += 1;
            	if (fullRow[t.y+y] == 32) score++;
            }
        }
    }
}


int collisions(Tetromino t, int tx, int ty, int rotation) {
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			uint16_t tValue = t.grid[rotateTetromino(x, y, rotation)];
			int fieldIndex = (ty + y) * 34 + (tx + x);
			if (tx+x >= 0 && tx+x < 34) {
				if (ty + y >= 0 && ty + y < 25) {

					if (tValue != 0 && fieldArray[fieldIndex] != 0) {
					// we get collision
						return 1;
					}

				}
			}
		}
	}
	return 0;
}


// RNG function
int pseudoRandom(int diviser) {
    // Constants for a commonly-used LCG from Numerical Recipes
    const unsigned int m = 0x7fffffff;  // 2^31-1
    const unsigned int a = 1664525;
    const unsigned int c = 1013904223;
    seed = (a * seed + c) % m;
    return seed % diviser;
}


int isButtonPressed(ButtonState* button) {
    int currentState = !KBD_get_button_state(button->name);
    uint32_t debounceInterval = 15;
    uint32_t currentTick = HAL_GetTick();
    int isPressed = 0; // false by default

    if (currentState && !button->previousState && (currentTick - button->lastPressTime > debounceInterval)) {
            button->lastPressTime = currentTick; // Update the last press time
            isPressed = 1;
        }


    button->previousState = currentState;
    return isPressed;
}

int handleButtons() {
  if (isButtonPressed(&right)) return 1;
  if (isButtonPressed(&left)) return 3;
  if (isButtonPressed(&up)) return 0;
  if (isButtonPressed(&down)) return 2;
  if (isButtonPressed(&ok)) return 5;
  if (isButtonPressed(&esc)) return 6;
  else return 4;
}


int handleJoystick() {
	HAL_ADC_Start(&hadc4);
	HAL_ADC_PollForConversion(&hadc4,10);// Waiting for ADC conversion
	joystick_raw.x=HAL_ADC_GetValue(&hadc4);

	HAL_ADC_Start(&hadc4);
	HAL_ADC_PollForConversion(&hadc4,10);// Waiting for ADC conversion
	joystick_raw.y=HAL_ADC_GetValue(&hadc4);
	HAL_ADC_Stop(&hadc4);

	joystick_get(&joystick_raw, &joystick_out, &joystick);
	if (joystick_out.x > 0) return 1;
	else if (joystick_out.x <-18) return -1;
	return 0;
}


void DrawStartScreen() {
	UG_FontSelect(&FONT_32X53);
	UG_SetForecolor(C_GREEN);
	UG_PutString(p_x-2,p_y,"TETRIS");
	UG_FontSelect(&FONT_12X16);
	UG_SetForecolor(C_WHITE);
	UG_PutString(p_x-8, p_y + 100,"PRESS OK TO PLAY");
	if (rotations == 1) UG_PutString(p_x-20, p_y + 150,"ROTATIONS ENABLED");
	if (rotations == 0) UG_PutString(p_x-20, p_y + 150,"ROTATIONS DISABLED");
	HAL_Delay(100);
}


void DrawGameOverScreen() {
	UG_FontSelect(&FONT_32X53);

	char scoreString[10];
	sprintf(scoreString, "%d", score);

	UG_SetForecolor(C_RED);
	UG_PutString(10,p_y,"GAME OVER");
	UG_FontSelect(&FONT_12X16);
	UG_SetForecolor(C_WHITE);
	UG_PutString(100,p_y + 100,"SCORE:");
	UG_PutString(190,p_y + 100, scoreString);
	UG_PutString(21,p_y + 180,"PRESS OK TO TRY AGAIN");
	HAL_Delay(100);
}

int toggle(int rotations) {
	if (rotations == 1) return 0;
	if (rotations == 0) return 1;
}

int init_tetris_game() {
    LED_init();
    KBD_init();
    SCI_init();
    joystick_init(&joystick);
    LCD_Init();
    UG_Init(&gui, UserPixelSetFunction, ILI9341_GetParam(LCD_WIDTH), ILI9341_GetParam(LCD_HEIGHT));
    UG_FontSelect(&FONT_8X12);
    UG_SetForecolor(C_WHITE);
    UG_SetBackcolor(C_BLACK);
    UG_DriverRegister(DRIVER_FILL_FRAME, (void *)_HW_FillFrame_);
    UG_DriverEnable(DRIVER_FILL_FRAME);
}

int tetris_game() {
    int rotationInput;
	Tetromino t;
	GameState currentState = START_SCREEN;
    while (1) {
    	switch (currentState) {

    	// ---------- START-STATE----------
            case START_SCREEN:
            	score = 0;
            	initFA();
            	initFR();
    			DrawStartScreen();
    			int buttonPressed = handleButtons();
    			if (buttonPressed < 4) {
    				rotations = toggle(rotations);
    				seed++;
    				UG_FillScreen(C_BLACK);
    			}

    			if (!KBD_get_button_state(BTN_OK)) {
    				UG_FillScreen(C_BLACK);
    				t = generateTetromino(pseudoRandom(7), pseudoRandom(4), 16);
    				//t = generateTetromino(0, 0, 16);
    				currentState = GAMING_SCREEN;
    				break;
    			}
    		break;

        // ---------- GAME-STATE----------
   	        case GAMING_SCREEN:
   			    LCD_TetrisFrame(t, fieldArray, fullRow);
   			    HAL_Delay(10);
   			    int input = handleButtons();
   			    int inputJ = handleJoystick();
   			    if (input == 6) {
   				    LCD_ClearScreen();
   				    rotations = 0;
   				    UG_FillScreen(C_BLACK);
   				    currentState = START_SCREEN;
   			    }
   			    HAL_Delay(200);
   			    int tetrominoLanded = 0;
   			    rotationInput = t.rotation;
   			    if (rotations == 1 && t.shape != 'O') {
   				    rotationInput += (input < 4) ? 1 : 0;
   			    }
   			    // checks collisions
   			    t.x += (inputJ != 0 && collisions(t, t.x+inputJ, t.y, rotationInput) == 1) ? 0 : inputJ;
   			    if (collisions(t, t.x, t.y+1, rotationInput) == 1) {
   				    t.rotation = rotationInput;
   				    writeToFA(t);
   				    tetrominoLanded = 1;
   			    }
   			    else {
   				    t.rotation = rotationInput;
   				    t.y++;
   			    }
      			    LCD_ClearScreen();
   			    if (tetrominoLanded == 1) {
   				    LCD_PlayingField(fieldArray, fullRow);
   				if (t.y == 0) {
   					LCD_ClearScreen();
   					currentState = GAME_OVER_SCREEN;
   					break;
   				}
   				int s = pseudoRandom(7);
   				int r = pseudoRandom(4);
   				int p = pseudoRandom(28);
   				// generates new tetromino
   				t = generateTetromino(s, r, p+1);
   				//t = generateTetromino(0, 0, 16);
   			    }
   	        break;
       
        // ---------- GAME-OVER ----------
   	        case GAME_OVER_SCREEN:
   	    	   	DrawGameOverScreen();
   				if (!KBD_get_button_state(BTN_OK)) {
   					UG_FillScreen(C_BLACK);
   					currentState = START_SCREEN;
   					break;
   			    }
   	        break;
   	    }
      }
}