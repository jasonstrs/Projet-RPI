#ifndef BTN_HEADER
#define BTN_HEADER

#include "main.h"

#define BUTTON 6

//set IDs of the buttons
extern int buttonIDs[4][4];
//declarate GPIO pins for the lines
extern int rowPins[4];
//declarate GPIO pins for the columns
extern int columnPins[4];

void InitBoutons();
int GetIndex(int row, int col);
int AnalyserMatrice(void);


extern int lastBtn;
extern int lastTime;
extern int isPressed;

#endif