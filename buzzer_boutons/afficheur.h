#include "projet_rpi.h"
#include <stdint.h> 
#include <wiringPiI2C.h> 
#include <sys/time.h> 
#include <stdbool.h> 


// ------------------------------------------------------------------------------------ //
// ------------------------------------------------------------------------------------ //
// ------------------------ CONSTANTES SYMBOLIQUES ------------------------------------ //
// ------------------------------------------------------------------------------------ //
// ------------------------------------------------------------------------------------ //

#define HT16K33_BLINK_CMD 0x80 
#define HT16K33_BLINK_DISPLAYON 0x01 
#define HT16K33_BLINK_OFF 0 
#define HT16K33_BLINK_2HZ  1 
#define HT16K33_BLINK_1HZ  2 
#define HT16K33_BLINK_HALFHZ  3 
#define HT16K33_CMD_BRIGHTNESS 0xE0 

#define SEVENSEG_DIGITS 5 

// ------------------------------------------------------------------------------------ //
// ------------------------------------------------------------------------------------ //
// ---------------------------- VARIABLES GLOBALES ------------------------------------ //
// ------------------------------------------------------------------------------------ //
// ------------------------------------------------------------------------------------ //

/**
 * @brief Fonction qui permet d'afficher le buffer
 */
uint16_t displaybuffer[12]; 

/**
 * @brief Table de nombre, chaque nombre est associé à un code héxa
 */
extern const uint8_t numbertable[];




// ------------------------------------------------------------------------------------ //
// ------------------------------------------------------------------------------------ //
// ---------------------------------------- PROTOTYPES -------------------------------- //
// ------------------------------------------------------------------------------------ //
// ------------------------------------------------------------------------------------ //

/**
 * @brief Fonction qui permet de régler l'intensité lumineuse
 * @param fd int représentant l'afficheur 7 segments
 * @param b intensité voulue
 */
void setBrightness(int fd, uint8_t b);



/**
 * @brief Fonction qui permet de régler le taux de clignotement
 * @param fd int représentant l'afficheur 7 segments
 * @param b taux voulu
 */
void blinkRate(int fd, uint8_t b);


/**
 * @brief Fonction qui permet de démarrer l'afficheur 7 segments
 * 
 * @param fd int représentant l'afficheur 7 segments à démarrer
 */
void begin(int fd);


/**
 * @brief Cette fonction permet d'écrire un numéro sur l'afficheur 7 segment
 * 
 * @param fd int représentant l'afficheur 7 segments 
 * @param offset position du premier digit (dans notre cas 0)
 */
void writeDisplay(int fd, int offset); 


/**
 * @brief Fonction qui permet de vider le buffer, autrement dit d'éteindre tout le 7 segments
 * 
 */
void clear7Seg(void);


/**
 * @brief Fonction qui permet d'allumer la colonne d'un digit suivant le nombre que l'on souhaite afficher
 * @param d correspond au numéro du digit sur lequel on travaille
 * @param bitmask correspond à l'adresse hexa du digit choisi
 */
void writeDigitRaw(uint8_t d, uint8_t bitmask);


/**
 * @brief Permet d'écrire un numéro dans le buffer du digit
 * @param d numéro du digit sur lequel on écrit
 * @param num numéro que l'on veut écrire
 * @param dot boolean qui permet de savoir si on met un '.' ou pas sur l'affichage
 */
void writeDigitNum(uint8_t d, uint8_t num, bool dot);



/**
 * @brief Fonction qui permet de décomposer un nombre en nombre de centaine, nombre de dizaine et d'unité
 *          pour les afficher sur chaque digit du 7 segments
 * @param frequence fréquence de la note à décomposer
 * @param centaine nombre de centaine
 * @param dizaine nombre de dizaine
 * @param unite nombre de unité
 */
void decomposerFrequence(int frequence,int *centaine, int *dizaine, int *unite);




