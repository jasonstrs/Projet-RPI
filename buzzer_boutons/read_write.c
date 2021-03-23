#include "read_write.h"

int ecrireMelodie(char* titre, partition_t* part){
    FILE* f;
    int i=0;
    char path[100], error[150];

    system("mkdir -p partitions");
    strcpy(path,"./partitions/");
    strcat(path,titre);

    strcpy(error,"ERREUR LORS DE L'OUVERTURE DU FICHIER ");
    strcat(error,path);
    f = fopen(path,"w");


    fprintf(f,"%s\n",part->titre);

    while(part->mel[i].note != -1 && i<MAX_NOTES){
        fprintf(f,"%d:%d\n",part->mel[i].note,part->mel[i].ms);
        i++;
    }



    strcpy(error,"ERREUR LORS DE LA FERMETURE DU FICHIER ");
    strcat(error,path);
    CHECK(fclose(f),error);
}