#ifndef BUZZ_BTN_HEADER
#define BUZZ_BTN_HEADER


#include "projet_rpi.h"
#include "boutons.h"
#include "buzzer.h" 
#include "read_write.h"


void* threadBoutons();
void* threadBuzzer ();


void creerMelodieExemple1(melodie_t mel);


#endif