#include <softTone.h>
#include "buzzer.h"

#define	BUZZER	1 //Buzzer connecté à la pin 37 du RPI -> pin 25 wPi

int tabNotes[8] = {DO,RE,MI,FA,SOL,LA,SI,DO2};

int threadBuzzer (){
	int i ;

	wiringPiSetup () ;

    /* jouerNote(DO);
    delay(200); */
    softToneWrite (BUZZER, 0) ;

	CHECK(softToneCreate (BUZZER),"Problème lors de la création du softTone() sur le buzzer");
    atexit(eteindre_buzzer);

    while(1)
        jouerNoteSelonBoutons();

	softToneWrite (BUZZER, 0) ;
}

void jouerExemple(){
    printf("début\n");
    jouerNoteTemps(DO,300);
    delay(100);

    jouerNoteTemps(RE,300);
    delay(100);

    jouerNoteTemps(MI,300);
    delay(100);

    jouerNoteTemps(DO,300);
    delay(200);

    jouerNoteTemps(DO,300);
    delay(100);

    jouerNoteTemps(RE,300);
    delay(100);

    jouerNoteTemps(MI,300);
    delay(100);

    jouerNoteTemps(DO,300);
    delay(100);



    jouerNoteTemps(MI,300);
    delay(100);

    jouerNoteTemps(FA,300);
    delay(100);

    jouerNoteTemps(SOL,300);
    delay(100);

    delay(500);

    jouerNoteTemps(MI,300);
    delay(100);

    jouerNoteTemps(FA,300);
    delay(100);

    jouerNoteTemps(SOL,300);
    delay(100);
    printf("fin");
}

void jouerNote(note_t note){
    softToneWrite(BUZZER,note);
    delay(10);
}


void jouerNoteTemps(note_t note, unsigned int ms){
    softToneWrite(BUZZER,note);
    delay(ms);
    softToneWrite(BUZZER,0);
}

void jouerNoteSelonBoutons(){
    
    if(isPressed){
        if(lastBtn<8)
            jouerNote(tabNotes[lastBtn]);
    }
    else
        softToneWrite (BUZZER, 0) ;
}



void eteindre_buzzer(){
    int i;

    printf("Fin du programme, on s'assure que le buzzer s'éteint bien\n");
    softToneWrite (BUZZER, 0) ;
    delay(500);
    softToneWrite (BUZZER, 0) ;
    digitalWrite(BUZZER,LOW);
}