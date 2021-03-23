#ifndef BUZZ_HEADER
#define BUZZ_HEADER


#include "projet_rpi.h"
#include <softTone.h>

#define	BUZZER	1 //pin wiringPi

extern int tabNotes[8];


//Variables globales permettant de connaître l'état des boutons
extern int lastBtn;
extern int lastTime;
extern int isPressed;


void jouerNote(note_t note);

/**
 * @brief Joue une note pendant un temps défini
 * 
 * @param note La note à jouer (DO -> DO ou BLANC)
 * @param ms Le temps (en ms) pendant lequel jouer la note
 */
void jouerNoteTemps(note_t note, unsigned int ms);

void eteindre_buzzer(void);

void jouerNoteSelonBoutons();

void jouerExemple(void);



#endif