#include <stdio.h>
#include <wiringPi.h>

#include "boutons.h"

//set IDs of the buttons
int buttonIDs[4][4] = {{4,3,2,1},{8,7,6,5},{12,11,10,9},{16,15,14,13}};
//declarate GPIO pins for the lines
int rowPins[4] = {2,3,21,22};
//declarate GPIO pins for the columns
int columnPins[4] = {23,24,25,6};

int lastBtn = 0;
int lastTime = 0;
int isPressed = 0;
int commandeSDL;
int commandeBuzzer;

void InitBoutons(){
	int i;
	//define 4 inputs with pull up resistors
	for(i=0;i<4;i++){
		pinMode (rowPins[i], INPUT) ;
		pullUpDnControl (rowPins[i],PUD_UP); // activation de la résistance de pull-up interne 
		pinMode(columnPins[i],OUTPUT);
		digitalWrite (columnPins[i], 1) ;
	}

}

int GetIndex(int row, int col){
	int indice, btnIndex;
	btnIndex = buttonIDs[row][col] -1;
	return btnIndex;
}

int HeldDown(int pin){
	return (rowPins[pin] == 0);
}

void AnalyserMatrice(void){
	int i,j;
	int pin;
	double ticks;
	for(i=0;i<4;i++){
		//Analyse des colonnes
		//printf("On met à 0 la colonne %d (pin %d)\n\n", 4 - i,columnPins[i]);
		digitalWrite (columnPins[i], 0) ; //On active la colonne
		
		for(j=0;j<4;j++){
			
			//Analyse des lignes
			//printf("Colonne %d ; Ligne : %d (pin %d) ; Etat : %d : %d\n",i+1,j+1,rowPins[j],digitalRead(columnPins[i]),digitalRead(rowPins[j]));

			if(digitalRead(rowPins[j]) == 0){
				pin = GetIndex(j,i);
				//printf("Bouton %d appuyé",pin + 1);
				isPressed = 1;
				lastBtn = pin;
				ticks = 0;   

				if(pin>7){
					commandeSDL = pin;
					commandeBuzzer = pin;
				}
					
					
				while(digitalRead(rowPins[j]) == 0){
					ticks++;
					delay(1);
				}
				//printf(" relaché! (maintenu %.1f secondes) \n",0.1*ticks);
				lastTime=0.001*ticks;
				isPressed = 0;
			}
			
		} 
		digitalWrite (columnPins[i], 1) ; //On désactive la colonne
		
	}
}


void* threadBoutons(){
	printf("Thread boutons lancé! \n");

    wiringPiSetup () ;
	int buttonPin = -1; 
	int i = 0,j;
	
	InitBoutons();

	while(1) {
		AnalyserMatrice();
	}

	pthread_exit(0) ;

}