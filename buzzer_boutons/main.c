#include "main.h"

extern void* threadSDL();
pthread_t threadBtn,threadMain,threadBuzz,threadSDL2;

int main(int argc, int* argv){
    int i;
    
    threadMain = pthread_self();


    /* begin(); */



/*     printf("Lancment thread Boutons...\n");
    CHECK_T(pthread_create (&threadBtn, NULL, (pf_t)threadBoutons, NULL),"pthread_create() boutons");

    printf("Lancment thread Buzzer...\n");
	CHECK_T(pthread_create (&threadBuzz, NULL, (pf_t)threadBuzzer, NULL),"pthread_create() buzzer"); 

    printf("Lancment thread SDL...\n");
	CHECK_T(pthread_create (&threadSDL2, NULL, (pf_t)threadSDL, NULL),"pthread_create() sdl");  */




    //Programme principal
	while(1){

        menu();




    }
    

}

void creerMelodieExemple1(partition_t* part){
    int i=0;
    unsigned int ms = 0;
    note_t note;
    une_note_t laNote, laNote2;

    for(i=0;i<MAX_NOTES;i+=2){
        ms = 50 + (rand() % 451);
        note = tabNotes[rand() % 8];

        laNote.ms = ms;
        laNote.note = note;
        part->mel[i] = laNote;

        ms = 50 + (rand() % 451);

        laNote2.ms = ms;
        laNote2.note = BLANC;
        part->mel[i+1] = laNote2;
    }

    
}


