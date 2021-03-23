#include "projet_rpi.h"


// pour lister les fichiers du répertoire
// https://www.studytonight.com/c/programs/files-and-streams/program-to-list-files-in-directory

/**
 * @brief Fonction qui permet d'écrire une mélodie dans un fichier
 * 
 * @param titre titre d'une partition (et aussi nom du fichier qui va être créé)
 * @param part partition que l'on souhaite écrire dans notre fichier
 */
void ecrireMelodie(char* titre, partition_t* part);


/**
 * @brief Fonction qui permet de lire une mélodie dans un fichier
 * 
 * @param titre titre de la partition que l'on souhaite ouvrir
 * @param partition objet partition que l'on va remplir en lisant le fichier
 */
void lireMelodie(char *titre,partition_t *partition);

/**
 * @brief Fonction qui permet de compter le nombre de ligne du résultat d'une commande
 * Cette fonction est utile pour allouer la mémoire dans les tableaux
 * @param commande commmande que l'on veut exécuter (chemin absolu). Ex: /bin/cat
 * @param chemin chemin sur lequel on veut exécuter la commande
 * @return int nombre de lignes du résultat
 */
int countNumberOfLineOutput(char *commande,char *chemin);


/**
 * @brief Fonction qui permet de récupérer un tableau qui contient l'ensemble des noms des partitions et donc des fichiers
 * @return char* tableau contenant les noms des partitions
 */
char **getNamesOfAllPartitions(void);