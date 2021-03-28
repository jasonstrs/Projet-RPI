#include "afficheur.h"


/**
 * @brief Table de nombre, chaque nombre est associé à un code héxa
 */
const uint8_t numbertable[] = { 
	0x3F, /* 0 */ 
	0x06, /* 1 */ 
	0x5B, /* 2 */ 
	0x4F, /* 3 */ 
	0x66, /* 4 */ 
	0x6D, /* 5 */ 
	0x7D, /* 6 */ 
	0x07, /* 7 */ 
	0x7F, /* 8 */ 
	0x6F, /* 9 */ 
	0x77, /* a */ 
	0x7C, /* b */ 
	0x39, /* C */ 
	0x5E, /* d */ 
	0x79, /* E */ 
	0x71, /* F */ 
}; 


/**
 * @brief Fonction qui permet de régler l'intensité lumineuse
 * @param fd int représentant l'afficheur 7 segments
 * @param b intensité voulue
 */
void setBrightness(int fd, uint8_t b) { 
  if (b > 15) b = 15; 
  wiringPiI2CWrite(fd, HT16K33_CMD_BRIGHTNESS | b); 
} 


/**
 * @brief Fonction qui permet de régler le taux de clignotement
 * @param fd int représentant l'afficheur 7 segments
 * @param b taux voulu
 */
void blinkRate(int fd, uint8_t b) { 
  if (b > 3) b = 0; // turn off if not sure 
  wiringPiI2CWrite(fd, HT16K33_BLINK_CMD | HT16K33_BLINK_DISPLAYON | (b << 1)); 
} 

/**
 * @brief Fonction qui permet de démarrer l'afficheur 7 segments
 * 
 * @param fd int représentant l'afficheur 7 segments à démarrer
 */
void begin(int fd) { 
  wiringPiI2CWrite(fd, 0x21); 
  blinkRate(fd, HT16K33_BLINK_OFF); 
  setBrightness(fd, 15); // max brightness 
} 


/**
 * @brief Cette fonction permet d'écrire un numéro sur l'afficheur 7 segment
 * 
 * @param fd int représentant l'afficheur 7 segments 
 * @param offset position du premier digit (dans notre cas 0)
 */
void writeDisplay(int fd, int offset) { 
  uint8_t addr = (uint8_t) 0x00;	 
  uint8_t i=0; 
  for(i=0 ; i<4 ; i++) { 
	if(i==2) // 2 points 
	    addr+=2;   
        wiringPiI2CWriteReg8(fd, addr++, displaybuffer[i+offset] & 0xFF); 
        wiringPiI2CWriteReg8(fd, addr++, displaybuffer[i+offset] >> 8);  
  }  
} 


/**
 * @brief Fonction qui permet de vider le buffer, autrement dit d'éteindre tout le 7 segments
 * 
 */
void clear7Seg(void) { 
  uint8_t i=0; 
  for (i=0; i<12; i++) { 
    displaybuffer[i] = 0; 
  } 
} 


/**
 * @brief Fonction qui permet d'allumer la colonne d'un digit suivant le nombre que l'on souhaite afficher
 * @param d correspond au numéro du digit sur lequel on travaille
 * @param bitmask correspond à l'adresse hexa du digit choisi
 */
void writeDigitRaw(uint8_t d, uint8_t bitmask) { 
  if (d > 11) return; 
  displaybuffer[d] = bitmask; 
} 


/**
 * @brief Permet d'écrire un numéro dans le buffer du digit
 * @param d numéro du digit sur lequel on écrit
 * @param num numéro que l'on veut écrire
 * @param dot boolean qui permet de savoir si on met un '.' ou pas sur l'affichage
 */
void writeDigitNum(uint8_t d, uint8_t num, bool dot) { 
  if (d > 11) return; 
  writeDigitRaw(d, numbertable[num] | (dot << 7)); 
} 


/**
 * @brief Fonction qui permet de décomposer un nombre en nombre de centaine, nombre de dizaine et d'unité
 *          pour les afficher sur chaque digit du 7 segments
 * @param frequence fréquence de la note à décomposer
 * @param centaine nombre de centaine
 * @param dizaine nombre de dizaine
 * @param unite nombre de unité
 */
void decomposerFrequence(int frequence,int *centaine, int *dizaine, int *unite){
    (*centaine)=0;
    (*dizaine)=0;
    (*unite)=0;
    while (frequence>99){
        (*centaine)++;
        frequence-=100;
    }

    while (frequence>9){
        (*dizaine)++;
        frequence-=10;
    }

    (*unite)=frequence;
}