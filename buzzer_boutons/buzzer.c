#include <softTone.h>
#include "buzzer.h"

#define	BUZZER	1 //Buzzer connecté à la pin 37 du RPI -> pin 25 wPi

extern int lireMelodie(char *titre,partition_t* melodie);

extern int commandeBuzzer;
extern int commandeSDL;
int playpause = 0;
int reset = 0;
int enregistrement = 0, indexEnregistrement = 0;
struct timeval  tv;


partition_t part;


int tabNotes[8] = {DO,RE,MI,FA,SOL,LA,SI,DO2};

void resetPart(){
    int i;
    for(i=0;i<MAX_NOTES;i++){
        part.mel[i].note = 0;
        part.mel[i].ms = 0;
    }
}

int threadBuzzer (){
    printf("Thread buzzer lancé! \n");
    /* lireMelodie("testEcriture4",&part); */
	int i ;
    
	wiringPiSetup () ;
    

    softToneWrite (BUZZER, 0) ;

	CHECK(softToneCreate (BUZZER),"Problème lors de la création du softTone() sur le buzzer");
    atexit(eteindre_buzzer);

    while(1)
    {        
        enregistrerAvecBoutons();
        /* jouerMelodie(part.mel); */
    }

    

    /* for(i=0;i<MAX_NOTES;i++){
        printf("%d : %d\n",part.mel[i].note,part.mel[i].ms);
    } 

    printf("\tFIN LECTURE\n"); */
    /* jouerMelodie(part.mel); */

	softToneWrite (BUZZER, 0) ;

    pthread_exit(0);
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
}


void jouerNoteTemps(note_t note, unsigned int ms){
    int i=0;
    softToneWrite(BUZZER,note);
    while(i<ms){
        majCommandes();
        if(playpause){
            softToneWrite(BUZZER,note);
            delay(1);
            i++;
        }
        else
            softToneWrite(BUZZER,0);
        
    }
    softToneWrite(BUZZER,0);
}

void enregistrerAvecBoutons(){
    double currentTime,initialTime, tpsCumule = 0;
    indexEnregistrement = 0;
    majCommandes();
    /* if(playpause)return; */
    while(enregistrement && indexEnregistrement < MAX_NOTES && tpsCumule < 18000){
        gettimeofday(&tv, NULL);
        initialTime = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ;
        if(isPressed){
            if(lastBtn<8){
                jouerNote(tabNotes[lastBtn]);
                part.mel[indexEnregistrement].note = tabNotes[lastBtn];
                while(isPressed);
                gettimeofday(&tv, NULL);
                currentTime = ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000) - initialTime;
                tpsCumule+=currentTime;
                part.mel[indexEnregistrement].ms = currentTime;
                printf("Note %d : %d | %d\n",indexEnregistrement,part.mel[indexEnregistrement].note,part.mel[indexEnregistrement].ms);
                indexEnregistrement++;
            }      
        }
        else{
            softToneWrite (BUZZER, 0) ;
            part.mel[indexEnregistrement].note = BLANC;
            while((!isPressed || (isPressed && lastBtn>7)) && enregistrement)majCommandes();
            gettimeofday(&tv, NULL);
            currentTime = ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000) - initialTime;
            tpsCumule+=currentTime;
            part.mel[indexEnregistrement].ms = currentTime;
            printf("Note %d : %d | %d\n",indexEnregistrement,part.mel[indexEnregistrement].note,part.mel[indexEnregistrement].ms);
            indexEnregistrement++;
        }
            

        majCommandes();
    }
    /* if(indexEnregistrement < MAX_NOTES)part.mel[indexEnregistrement].note = -1; */
        
}



void eteindre_buzzer(){
    int i;

    printf("Fin du programme, on s'assure que le buzzer s'éteint bien\n");
    softToneWrite (BUZZER, 0) ;
    delay(500);
    softToneWrite (BUZZER, 0) ;
    digitalWrite(BUZZER,LOW);
}

void jouerMelodie(melodie_t mel){
    int i=0;
    reset = 0;
    //La mélodie se termine quand la prochaine note vaut -1, ou qu'on a joué MAXNOTES
    while(mel[i].note != -1 && i<MAX_NOTES){
        //printf("note %d = %d : %d\n",i, mel[i].note,mel[i].ms);
        majCommandes();
        /* if(enregistrement)return; */
        if(reset){
            i = 0;
            reset = 0;
            continue;
        }
        jouerNoteTemps(mel[i].note,mel[i].ms);
        i++;
    }

    softToneWrite(BUZZER,0);
    delay(50);
    softToneWrite(BUZZER,0);
    commandeBuzzer = RETOUR_DEBUT;
    commandeSDL = RETOUR_DEBUT;
}

void majCommandes(){
    switch(commandeBuzzer){
        case PLAY_PAUSE:
            playpause = !playpause;
        break;
        case RETOUR_DEBUT:
            playpause = 0;
            indexEnregistrement = 0;
            reset = 1;
            resetPart();
        break;
        case DEBUT_FIN_ENR:   
            indexEnregistrement = 0;   
            enregistrement = !enregistrement;
            resetPart();
            /* if(!enregistrement){
                if(indexEnregistrement<MAX_NOTES){
                    part.mel[indexEnregistrement].note = -1;
                }
            }
            else{
                indexEnregistrement = 0;
            } */
        break;
        case RESET:
            indexEnregistrement = 0;
            resetPart();
        break;
        default:
            /* printf("commande : %d\n",commandeBuzzer); */
        break;
    }
    commandeBuzzer = 0;
    
}