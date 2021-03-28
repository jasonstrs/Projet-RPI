#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


#include "projet_rpi.h"

extern int tabNotes[8];

int GetTailleTabNotes(partition_t p);
SDL_Rect** GetTabRectNotes(partition_t p, SDL_Rect** tab, int size);

extern void ecrireMelodie(partition_t* part);
extern void lireMelodie(char *titre,partition_t* melodie);