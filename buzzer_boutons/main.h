#ifndef MAIN_HEADER
#define MAIN_HEADER

#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <string.h> 
#include <pthread.h>
#include <wiringPi.h>

// ------------------------------------------------------------------------------------ //
// ------------------------------------------------------------------------------------ //
// ------------------------------------ AFFICHAGE ------------------------------------- //
// ------------------------------------------------------------------------------------ //
// ------------------------------------------------------------------------------------ //
/**
 * @brief Couleur d'affichage dans la console
 * 
 */
typedef enum
{
    BLACK = 30,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,
    BLINK = 5,
    HIGH_FONT  = 1,
    INV   = 7,
}couleur_aff_t;

/**
 * @brief Efface le contenu de la console
 * 
 */
#define clearScreen()  	{ printf("\033[H\033[2J");fflush(stdout); }

/**
 * @brief Définit la couleur qui sera utilisée dans la console
 * 
 */
#define setTerm(param)  { printf("\033[1m\033[%dm", param); fflush(stdout); }

/**
 * @brief Réinitialise la couleur d'affichage dans la console
 * 
 */
#define resetTerm()		setTerm(0);

char* CharTestGETSTRING;


// ------------------------------------------------------------------------------------ //
// ------------------------------------------------------------------------------------ //
// --------------------------------- MACRO-FONCTIONS ---------------------------------- //
// ------------------------------------------------------------------------------------ //
// ------------------------------------------------------------------------------------ //
/**
 * @brief Gère l'execution d'un appel système
 * 
 */
#define CHECK(sts, msg) if ((sts)==-1) {perror(msg); exit(-1);}

/**
 * @brief Gère l'execution des fonctions de gestion de threads
 * 
 */
#define CHECK_T(status, msg)                        \
  if (0 != (status))   {                            \
    fprintf(stderr, "pthread erreur : %s\n", msg);  \
    exit (EXIT_FAILURE);                            \
  }

/**
 * @brief Gère l'execution de fonctions retournant des poiinteurs
 * 
 */
#define CHECK_P(sts, msg) if ((sts)==NULL) {perror(msg); exit(-1);}

/**
 * @brief Suspend l'execution jusqu'à l'appui sur Entrer
 * 
 */
#define PAUSE 		setTerm(GREEN);printf("\n\t\t\tAppuyer sur Entrée pour continuer...\n");getchar();resetTerm();

// ------------------------------------------------------------------------------------ //
// ------------------------------------------------------------------------------------ //
// ------------------------------------- TYPES ---------------------------------------- //
// ------------------------------------------------------------------------------------ //
// ------------------------------------------------------------------------------------ //

typedef void* (*pf_t)(void *);

// ------------------------------------------------------------------------------------ //
// ------------------------------------------------------------------------------------ //
// -------------------------------- VARIABLES GLOBALES -------------------------------- //
// ------------------------------------------------------------------------------------ //
// ------------------------------------------------------------------------------------ //




#endif
