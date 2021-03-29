#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <signal.h>


#include "projet_rpi.h"

extern int tabNotes[8];

/**
 * @brief Analyse la partition pour calculer combien de rectangles seront nécessaires pour représenter toutes les notes
 * 
 * @param p La partition
 * @return int Le nombre de rectangles
 */
int GetTailleTabNotes(partition_t p);

/**
 * @brief Alloue de la mémoire pour le tableau de notes, et le remplit en calculant les coordonnées de chaque notes sur la partition
 * 
 * @param p La partition
 * @param tab Le tableau de SDL_Rect représentant les notes
 * @param size Le nombre de SDL_Rect du tableau (calculé grâce à GetTailleTabNotes())
 * @return SDL_Rect** Le tableau de SDL_REct représentant les notes
 */
SDL_Rect** GetTabRectNotes(partition_t p, SDL_Rect** tab, int size);

extern void ecrireMelodie(partition_t* part);
extern void lireMelodie(char *titre,partition_t* melodie);