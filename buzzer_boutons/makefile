#PATH_WPI=/home/simon/Documents/pi/target_wpi

#CC=gcc_croise
PATH_WPI=/home/jason/Bureau/COURS_LINUX/LE3/RPI/SEANCE_4/target_wpi

CC=/home/jason/Bureau/COURS_LINUX/LE3/RPI/tools-master/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc


all: buzzer.o boutons.o main.o read_write.o afficheur.o
	$(CC) -L$(PATH_WPI)/lib buzzer.o boutons.o main.o read_write.o afficheur.o -o main -lwiringPi -lpthread

main.o: main.c
	$(CC) -c -I$(PATH_WPI)/include main.c -o main.o 


buzzer.o:buzzer.c
	$(CC) -c -I$(PATH_WPI)/include buzzer.c -o buzzer.o 
	
boutons.o:boutons.c
	$(CC) -c -I$(PATH_WPI)/include boutons.c -o boutons.o 
	

read_write.o:read_write.c
	$(CC) -c -I$(PATH_WPI)/include read_write.c -o read_write.o 


afficheur.o:afficheur.c
	$(CC) -c -I$(PATH_WPI)/include afficheur.c -o afficheur.o 
	
	
	
buzzer : buzzer.c
	$(CC) -I$(PATH_WPI)/include -L$(PATH_WPI)/lib buzzer.c -o buzzer -lwiringPi -lpthread




clean: 
	rm -rf *.o buzzer


 
