#include "main.h"

int main(int argc, int* argv){
    int i;
    pthread_t threadBtn,threadMain = pthread_self(),threadBuzz;

    partition_t exemple1, exemple2;
    partition_t partitionExemple;

    /* CHECK_T(pthread_create (&threadBtn, NULL, (pf_t)threadBoutons, NULL),"pthread_create() boutons");
	CHECK_T(pthread_create (&threadBuzz, NULL, (pf_t)threadBuzzer, NULL),"pthread_create() buzzer"); */
    /*creerMelodieExemple1(&exemple1);
    strcpy(exemple1.titre,"testEcriture");
    ecrireMelodie("testEcriture",&exemple1);

    printf("Mélodie générée aléatoirement\n");
    for(i=0;i<MAX_NOTES;i++){
        printf("%d : %d\n",exemple1.mel[i].note,exemple1.mel[i].ms);
    }*/

    //creerMelodieExemple1(exemple1);


    //Programme principal
	/* while(1){

    




    } */
    /*printf("HEYYYYY");
    lireMelodie("testEcriture2",&partitionExemple);
    i=0;

    printf("Le titre de la partition est : '%s'\n",partitionExemple.titre);
    do {
        printf("Note : %d Hz | Temps : %d ms\n",partitionExemple.mel[i].note,partitionExemple.mel[i].ms);
        i++;
    } while (partitionExemple.mel[i].note != -1);*/
    //char **tableau = getNamesOfAllPartitions();
    

}

void creerMelodieExemple1(partition_t* part){
    int i=0;
    unsigned int ms = 0;
    note_t note;
    une_note_t laNote;

    for(i=0;i<MAX_NOTES;i++){
        ms = 50 + (rand() % 451);
        note = tabNotes[rand() % 8];

        laNote.ms = ms;
        laNote.note = note;
        part->mel[i] = laNote;
    }

    
}


