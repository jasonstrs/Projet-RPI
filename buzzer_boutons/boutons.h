#ifndef BTN_HEADER
#define BTN_HEADER

#include "projet_rpi.h"

#define BUTTON 6

//set IDs of the buttons
extern int buttonIDs[4][4];
//declarate GPIO pins for the lines
extern int rowPins[4];
//declarate GPIO pins for the columns
extern int columnPins[4];

/**
 * @brief Initialise correctement la matrice de boutons
 */
void InitBoutons();

/**
 * @brief Récupère le numéro du bouton sur lequel on a appuyé, en fonction des broches de ligne/colonne
 * 
 * @param row Broche correspondant à la ligne du bouton
 * @param col Broche correspondant à la colonne du bouton
 * @return int Numéro du bouton tel que défini sur la malette ([1;16])
 */
int GetIndex(int row, int col);

/**
 * @brief Analyse tour à tour toute les lignes/colonnes de la matrice, pour voir sur quel bouton on a appuyé
 * 
 * /!\ Ne détecte l'appui que sur 1 bouton à la fois !
 * 
 * Met à jour les variables globales lastBtn, lastTime et isPressed, pour que les autres threads puissent suivre l'état de la matrice.
 */
void AnalyserMatrice(void);

/**
 * @brief Numéro du dernier bouton pressé
 */
extern int lastBtn;

/**
 * @brief Temps pendant lequel le dernier bouton a été pressé
 */
extern int lastTime;

/**
 * @brief Un bouton est-il pressé sur la matrice ?
 */
extern int isPressed;

#endif