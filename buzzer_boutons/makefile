PATH_WPI=/home/simon/Documents/pi/target_wpi

CC=gcc_croise


all: buzzer.o boutons.o main.o
	$(CC) -L$(PATH_WPI)/lib buzzer.o boutons.o main.o -o main -lwiringPi -lpthread

main.o: main.c
	$(CC) -c -I$(PATH_WPI)/include main.c -o main.o 


buzzer.o:buzzer.c
	$(CC) -c -I$(PATH_WPI)/include buzzer.c -o buzzer.o 
	
boutons.o:boutons.c
	$(CC) -c -I$(PATH_WPI)/include boutons.c -o boutons.o 
	
	
	
buzzer : buzzer.c
	$(CC) -I$(PATH_WPI)/include -L$(PATH_WPI)/lib buzzer.c -o buzzer -lwiringPi -lpthread




clean: 
	rm -rf *.o buzzer


 
