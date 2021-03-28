#include "read_write.h"



/**
 * @brief Fonction qui permet d'écrire une mélodie dans un fichier
 * 
 * @param titre titre d'une partition (et aussi nom du fichier qui va être créé)
 * @param part partition que l'on souhaite écrire dans notre fichier
 */

void ecrireMelodie(char* titre, partition_t* part){
    FILE* f;
    int i=0;
    char path[100], error[150];

    system("mkdir -p partitions");
    strcpy(path,"./partitions/");
    strcat(path,titre);

    strcpy(error,"ERREUR LORS DE L'OUVERTURE DU FICHIER ");
    strcat(error,path);
    CHECK_P(f = fopen(path,"w"),error);


    fprintf(f,"%s\n",part->titre);

    while(part->mel[i].note != -1 && i<MAX_NOTES){
        fprintf(f,"%d:%d\n",part->mel[i].note,part->mel[i].ms);
        i++;
    }



    strcpy(error,"ERREUR LORS DE LA FERMETURE DU FICHIER ");
    strcat(error,path);
    CHECK(fclose(f),error);
}

}
/**
 * @brief Fonction qui permet de lire une mélodie dans un fichier
 * 
 * @param titre titre de la partition que l'on souhaite ouvrir
 * @param partition objet partition que l'on va remplir en lisant le fichier
 */
int lireMelodie(char *titre, partition_t* melodie) {
    FILE * fp=NULL;
    char path[100];
    char error[100];

    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    int cpt=0;
    
    strcpy(path,"./partitions/");
    strcat(path,titre);

    strcpy(error,"ERREUR LORS DE L'OUVERTURE DU FICHIER : ");
    strcat(error,path);

    CHECK_P(fp = fopen(path, "r"),error);

    strcpy(melodie->titre,titre); // on donne un nom à notre partition

    while ((read = getline(&line, &len, fp)) != -1) {
        //printf("%s", line);
        if(!cpt){
            //printf("Le nom de la partition est : '%s'",line);
        } else {
            sscanf(line,"%d:%d",&frequence,&duree);
            melodie->mel[cpt - 1].note = frequence;
            melodie->mel[cpt - 1].ms = duree;
        }

        cpt++;
    }


    if (cpt ==0){// on vérifie si cpt est 0 ou pas
        perror("ERREUR : LA PARTITION EST VIDE"); exit(-1);
    }

    melodie->mel[cpt-1].note=-1; // dernière note !!

    strcpy(error,"ERREUR LORS DE LA FERMETURE DU FICHIER ");
    strcat(error,path);
    CHECK(fclose(fp),error);

    if (line)
        free(line);
}

/**
 * @brief Fonction qui permet de compter le nombre de ligne du résultat d'une commande
 * Cette fonction est utile pour allouer la mémoire dans les tableaux
 * @param commande commmande que l'on veut exécuter (chemin absolu). Ex: /bin/cat
 * @param chemin chemin sur lequel on veut exécuter la commande
 * @return int nombre de lignes du résultat
 */
int countNumberOfLineOutput(char *commande,char *chemin){
    FILE *fp;
    char path[10];
    char error[100];
    char path_commande_complete[100];
    int nb;

    strcpy(error,"ERREUR LORS DE LA COMMANDE : ");
    strcat(error,path);

    strcpy(path_commande_complete,commande);
    strcat(path_commande_complete," ");
    strcat(path_commande_complete,chemin);
    strcat(path_commande_complete," | wc -l");


        /* Open the command for reading. */
    CHECK_P(fp = popen(path_commande_complete, "r"),error);


    /* Read the output a line at a time - output it. */
    nb=atoi(fgets(path, sizeof(path), fp));

    strcpy(error,"ERREUR LORS DE LA FERMETURE DE LA COMMANDE ");
    strcat(error,path);
    /* close */
    CHECK(pclose(fp),error);
    return nb;
}


/**
 * @brief Fonction qui permet de récupérer un tableau qui contient l'ensemble des noms des partitions et donc des fichiers
 * @param nbPartitions correspond au nombre de partitions présentes dans le répertoire ./partitions
 * @return char* tableau contenant les noms des partitions
 */
char **getNamesOfAllPartitions(int nbPartitions){
    // on alloue de la mémoire pour l'ensemble des cases du tableau
    char **tabNamePartition=(char **)malloc(sizeof(char*)*(nbPartitions+2));  // +2 pour mettre le '\0' et "Quitter"
    DIR *d;
    struct dirent *dir;
    int cpt=0;

    d = opendir("./partitions");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (strcmp(dir->d_name,".") !=0 && strcmp(dir->d_name,"..") !=0){ // on ne prend pas le répertoire "." et ".."
                tabNamePartition[cpt] = (char *)malloc(sizeof(char) * 30); // on alloue de la mémoire pour la case
                strcpy(tabNamePartition[cpt],dir->d_name);
                cpt++;
            }
        }
        closedir(d);
    }
    strcpy(tabNamePartition[cpt],"Quitter");
    tabNamePartition[cpt+1]='\0';
    return tabNamePartition;
}


