#ifndef BUZZ_HEADER
#define BUZZ_HEADER


#include "projet_rpi.h"
#include <softTone.h>
#include "afficheur.h"

#define	BUZZER	1 //pin wiringPi


//Variables globales permettant de connaître l'état des boutons
extern int lastBtn;
extern int lastTime;
extern int isPressed;

/**
 * @brief Joue une note jusqu'à ce qu'on l'arrête
 * 
 * @param note La fréquence à jouer
 */
void jouerNote(note_t note);

/**
 * @brief   Joue une note pendant un temps défini, puis arrête le buzzer. S'arre en fonction de la variable playpause
 * 
 * @param note La note à jouer (DO -> DO ou BLANC)
 * @param ms Le temps (en ms) pendant lequel jouer la note
 */
void jouerNoteTemps(note_t note, unsigned int ms);

/**
 * @brief Eteint le buzzer
 * 
 */
void eteindre_buzzer(void);

/**
 * @brief Joue les notes en fonction de l'appui sur les boutons, et les enregistre dans la partition courante.
 * 
 */
void enregistrerAvecBoutons();

/**
 * @brief Joue une mélodie d'exemple
 * 
 */
void jouerExemple(void);

/**
 * @brief Joue une mélodie
 * 
 * @param mel La mélodie à jouer
 */
void jouerMelodie(melodie_t mel);

/**
 * @brief Vérifie si un bouton de commande n'a pas été pressé.
 * 
 */
void majCommandes(void);



#endif