#ifndef BUZZ_BTN_HEADER
#define BUZZ_BTN_HEADER


#include "projet_rpi.h"
#include "boutons.h"
#include "buzzer.h" 
#include "read_write.h"


void* threadBoutons();
void* threadBuzzer ();

/**
 * @brief Crée une mélodie aléatoire
 * 
 * @param mel 
 */
void creerMelodieExemple1(partition_t* part);


#endif