PATH_WPI=#/home/simon/Documents/pi/target_wpi
PATH_I = #-I$(PATH_WPI)/include
PATH_L = #-L$(PATH_WPI)/lib

CC=gcc


all: buzzer.o boutons.o main.o read_write.o partition_sdl.o
	$(CC) $(PATH_L) buzzer.o boutons.o main.o read_write.o partition_sdl.o  -o main -lwiringPi -lpthread `sdl2-config --cflags --libs` -lSDL2_ttf -lSDL2_image -lm

main.o: main.c
	$(CC) -c $(PATH_I) main.c -o main.o 


buzzer.o:buzzer.c
	$(CC) -c $(PATH_I) buzzer.c -o buzzer.o 
	
boutons.o:boutons.c
	$(CC) -c $(PATH_I) boutons.c -o boutons.o 
	

read_write.o:read_write.c
	$(CC) -c $(PATH_I) read_write.c -o read_write.o 

partition_sdl.o : partition_sdl.c
	$(CC) -c partition_sdl.c -o partition_sdl.o `sdl2-config --cflags --libs`


clean: 
	rm -rf *.o main


 
