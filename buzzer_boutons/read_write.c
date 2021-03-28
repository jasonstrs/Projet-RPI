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


int lireMelodie(char *titre, partition_t* melodie) {
    FILE * fp=NULL;
    char path[100];
    char error[100];

    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    int cpt=0,frequence,duree;

    strcpy(path,"./partitions/");
    strcat(path,titre);

    strcpy(error,"ERREUR LORS DE L'OUVERTURE DU FICHIER : ");
    strcat(error,path);

    CHECK_P(fp = fopen(path, "r"),error);

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
        melodie->mel[cpt].note = -1;


    fclose(fp);
    if (line)
        free(line);
}