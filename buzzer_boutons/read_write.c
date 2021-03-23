#include "read_write.h"



int lireMelodie(char *titre, melodie_t melodie) {
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
        printf("%s", line);
        if(!cpt){
            printf("Le nom de la partition est : '%s'",line);
        } else {
            sscanf(line,"%d:%d",&frequence,&duree);
        }

        cpt++;
    }

    fclose(fp);
    if (line)
        free(line);
}