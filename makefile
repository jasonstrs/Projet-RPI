PATH_WPI=/home/simon/Documents/pi/target_wpi

CC=gcc_croise

all: buzzer.o boutons.o buzzerEtBoutons.o
	$(CC) -L$(PATH_WPI)/lib buzzer.o boutons.o buzzerEtBoutons.o -o buzzerEtBoutons -lwiringPi -lpthread

buzzerEtBoutons.o: buzzerEtBoutons.c
	$(CC) -c -I$(PATH_WPI)/include buzzerEtBoutons.c -o buzzerEtBoutons.o 


buzzer.o:buzzer.c
	$(CC) -c -I$(PATH_WPI)/include buzzer.c -o buzzer.o 
	
boutons.o:boutons.c
	$(CC) -c -I$(PATH_WPI)/include boutons.c -o boutons.o 
	
	
	
buzzer : buzzer.c
	$(CC) -I$(PATH_WPI)/include -L$(PATH_WPI)/lib buzzer.c -o buzzer -lwiringPi -lpthread




clean: 
	rm -rf *.o buzzer


 
