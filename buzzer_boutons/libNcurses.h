#include "projet_rpi.h"

#include <form.h>
#include <assert.h>
#include <ctype.h>
#include <curses.h>	/* Necessary for all Curses programs */
#include <menu.h>	/* Gives you menuing capabilities */

#define WHITEONRED 1
#define WHITEONBLUE 2
#define WHITEONBLACK 3
#define BLACKONWHITE 4
#define REDONWHITE 5


// ------------------------------------------------------------------------------------ //
// ------------------------------------------------------------------------------------ //
// -------------------------------- VARIABLES GLOBALES -------------------------------- //
// ------------------------------------------------------------------------------------ //
// ------------------------------------------------------------------------------------ //

/**
 * @brief Liste des choix possibles proposés à l'utilisateur dans le menu principal
 */
extern char *choices[];

/**
 * @brief Variable globale qui permet de stocker le nom d'une nouvelle partition ou de la partition à charger dans SDL
 */
char name_Partition[50];


// ------------------------------------------------------------------------------------ //
// ------------------------------------------------------------------------------------ //
// -------------------------------------- PROTOTYPES ---------------------------------- //
// ------------------------------------------------------------------------------------ //
// ------------------------------------------------------------------------------------ //


/**
 * @brief Fonction qui permet de supprimer les espaces ajoutés à la fin du champs de formulaire ncurses
 * /!\ On utilise cette fonction car ncurses ajoute des espaces à la fin du champs
 * 
 * @param str champs de formulaire récupéré dans ncurses
 * @return char* chaine de caractères sans les espaces à la fin
 */
char* trim_whitespaces(char *str);


/**
 * @brief Fonction qui permet de gérer les touches appuyées par l'utilisateur dans le sous menu "Nouvelle Partition".
 * F1 => Revenir au menu supérieur
 * Le reste permet de se déplacer/écrire/supprimer/espace...
 * @param ch correspond à la touche qui a été appuyée
 * @param form correspond au formulaire 
 * @param wUI correspond à la fenêtre dans laquelle se trouve le formulaire (fenêtre rouge)
 * @return int 
 */
int driver(int ch,FORM *form,WINDOW *wUI);


/**
 * @brief Cette fonction permet d'initialiser et d'afficher le formulaire "Nouvelle Partition"
 * @return int return -1 si on souhaite revenir au menu principal, 0 sinon
 */
int initFormPartition(void);


/**
 * @brief Fonction qui permet de démarrer le menu principal sur la fenêtre principal, en y insérant le titre et les coordonnées
 * @param wParent fenêtre principale
 * @param height hauteur de la fenêtre fille
 * @param width largeur de la fenêtre fille
 * @param y coordonnée y de la fenêtre fille
 * @param x coordonnée x de la fenêtre fille
 * @param choices choix disponibles dans le menu
 * @param titre titre de la fenêtre/bordule
 * @return int return -3 si on souhaite quitter l'application, sinon retourne l'index de l'option choisie dans le menu
 */
int runMenu(WINDOW *wParent, int height, int width, int y, int x, char *choices[], char titre[20]);


/**
 * @brief Fonction qui permet d'initialiser les couleurs pour notre librairie ncurses
 * @return true : si le terminal est capable d'afficher des couleurs
 * @return false : si le terminal n'est pas capable d'afficher des couleurs
 */
bool initColors(void);

/**
 * @brief Fonction qui permet de dessiner le fond de la fenêtre
 * @param pwin fenêtre sur laquelle on met un fond
 */
void wclrscr(WINDOW * pwin);

/**
 * @brief Fonction qui permet de centrer le titre en haut de la fenêtre
 * @param pwin fênetre sur laquelle on veut placer le titre
 * @param title titre que l'on veut donner
 */
void wCenterTitle(WINDOW *pwin, const char * title);

/**
 * @brief Fonction qui permet de gérer le choix de l'utilisateur dans le menu principal
 * @param choix index de l'option choisie par l'utilisateur
 * @return int return -1 si on doit relancer le menu principal, sinon 1
 */
int handleChoice(int choix);

/**
 * @brief Fonction qui permet d'initialiser la fenêtre, c'est-à-dire mettre un fond bleu, activer la détection des touches,
 * activer les couleurs et afficher la fenêtre
 */
void initFenetre(void);


/**
 * @brief Cette fonction permet de démarrer la librairie ncurses, elle appelle une fonction d'initialisation de la fenêtre
 * pour obtenir un fond bleu et elle lance le menu principal de notre librairie
 */
void runNcurses(void);

/**
 * @brief Cette fonction permet d'initialiser et d'afficher le formulaire "Aide"
 */
void initFormHelp();

/**
 * @brief Fonction qui permet de récupérer une fenêtre qui va servir de bordure
 * @param title titre que l'on veut donner à la fenêtre
 * @return WINDOW* fenêtre wBorder qui est retournée
 */
WINDOW * getWindowBorder(char *title);

/**
 * @brief Fonction qui permet de récupérer l'interface utilisateur sur laquelle sera mise des écritures ou 
 * un formulaire, dans notre projet, c'est la fenêtre rouge
 * @param wBorder bordure qui va encadrée notre fenêtre
 * @return WINDOW* fenêtre interface utilisateur qui est retournée
 */
WINDOW * getUserInterface(WINDOW * wBorder);

int menu();

extern void* threadBoutons();
extern void* threadBuzzer ();
extern void* threadSDL ();

extern pthread_t threadBtn,threadMain,threadBuzz,threadSDL2;

extern partition_t part;

void lireMelodie(char *titre,partition_t *melodie);
