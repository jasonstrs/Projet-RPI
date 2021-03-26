PATH_WPI=/home/simon/Documents/pi/target_wpi

CC=gcc


all: buzzer.o boutons.o main.o read_write.o
	$(CC) -L$(PATH_WPI)/lib buzzer.o boutons.o main.o read_write.o  -o main -lwiringPi -lpthread -lSDL -lSDL_ttf `sdl-config --cflags --libs`

main.o: main.c
	$(CC) -c -I$(PATH_WPI)/include main.c -o main.o 


buzzer.o:buzzer.c
	$(CC) -c -I$(PATH_WPI)/include buzzer.c -o buzzer.o 
	
boutons.o:boutons.c
	$(CC) -c -I$(PATH_WPI)/include boutons.c -o boutons.o 
	

read_write.o:read_write.c
	$(CC) -c -I$(PATH_WPI)/include read_write.c -o read_write.o 
	
	
	
buzzer : buzzer.c
	$(CC) -I$(PATH_WPI)/include -L$(PATH_WPI)/lib buzzer.c -o buzzer -lwiringPi -lpthread




clean: 
	rm -rf *.o buzzer


 
