#include "buzzerEtBoutons.h"

int main(int argc, int* argv){
    pthread_t threadBtn,threadMain = pthread_self(),threadBuzz;




    CHECK_T(pthread_create (&threadBtn, NULL, (pf_t)threadBoutons, NULL),"pthread_create()");
	CHECK_T(pthread_create (&threadBuzz, NULL, (pf_t)threadBuzzer, NULL),"pthread_create()");

	while(1);

}


void* threadBoutons(){

    wiringPiSetup () ;
	int buttonPin = -1; 
	int i = 0,j;
	
	InitBoutons();

	while(1) {
		buttonPin = AnalyserMatrice();
	}

	pthread_exit(0) ;

}