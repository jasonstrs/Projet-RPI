#include "main.h"

int main(int argc, int* argv){
    int i;
    pthread_t threadBtn,threadMain = pthread_self(),threadBuzz;

    melodie_t exemple1, exemple2;

    /* CHECK_T(pthread_create (&threadBtn, NULL, (pf_t)threadBoutons, NULL),"pthread_create() boutons");
	CHECK_T(pthread_create (&threadBuzz, NULL, (pf_t)threadBuzzer, NULL),"pthread_create() buzzer"); */

    creerMelodieExemple1(exemple1);

    

    //Programme principal
	/* while(1){






    } */

}

void creerMelodieExemple1(melodie_t mel){
    int i=0;
    unsigned int ms = 0;
    note_t note;
    une_note_t laNote;

    for(i=0;i<30;i++){
        ms = 50 + (rand() % 451);
        note = tabNotes[rand() % 8];

        laNote.ms = ms;
        laNote.note = note;
        mel[i] = laNote;
    }

    printf("Mélodie générée aléatoirement");
    for(i=0;i<30;i++){
        printf("%d : %d\n",mel[i].note,mel[i].ms);
    }
}


