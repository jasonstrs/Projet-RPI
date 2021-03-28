#ifndef BUZZ_BTN_HEADER
#define BUZZ_BTN_HEADER


#include "projet_rpi.h"
#include "boutons.h"
#include "buzzer.h" 
#include "partition_sdl.h" 
#include "read_write.h"
#include "afficheur.h"
#include "libNcurses.h"


void* threadBoutons();
void* threadBuzzer ();
void* threadSDL ();

/**
 * @brief Crée une mélodie aléatoire
 * 
 * @param mel 
 */
void creerMelodieExemple1(partition_t* part);


/**
 * @brief Fonction qui permet de tester l'afficheur 7 segments en écrivant 440 (fréquence du 'LA')
 */
void exemple7Segments(void);


#endif