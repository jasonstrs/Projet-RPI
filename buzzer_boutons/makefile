PATH_WPI=#/home/simon/Documents/pi/target_wpi
PATH_I = #-I$(PATH_WPI)/include
PATH_L = #-L$(PATH_WPI)/lib

CC=gcc
#CC=gcc_croise
#PATH_WPI=/home/jason/Bureau/COURS_LINUX/LE3/RPI/SEANCE_4/target_wpi

LINK_FLAGS= -lSDL2_ttf -lSDL2_image -lm -lwiringPi -lpthread -lncurses -lpanel -lmenu -lform

ALL_O = buzzer.o boutons.o main.o read_write.o afficheur.o partition_sdl.o libNcurses.o menu.o

CC_FLAGS = #-Wall -Wextra

#CC=/home/jason/Bureau/COURS_LINUX/LE3/RPI/tools-master/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc

all: $(ALL_O)
	$(CC) $(CC_FLAGS) $(PATH_L) $(ALL_O) -o main `sdl2-config --cflags --libs` $(LINK_FLAGS)

main.o: main.c
	$(CC) $(CC_FLAGS) -c $(PATH_I) main.c -o main.o 


buzzer.o:buzzer.c
	$(CC) $(CC_FLAGS) -c $(PATH_I) buzzer.c -o buzzer.o 
	
boutons.o:boutons.c
	$(CC) $(CC_FLAGS) -c $(PATH_I) boutons.c -o boutons.o 
	

read_write.o:read_write.c
	$(CC) $(CC_FLAGS) -c  read_write.c -o read_write.o 


afficheur.o:afficheur.c
	$(CC) $(CC_FLAGS) -c  afficheur.c -o afficheur.o 
	


partition_sdl.o : partition_sdl.c
	$(CC) $(CC_FLAGS) -c partition_sdl.c -o partition_sdl.o `sdl2-config --cflags --libs`

libNcurses.o : libNcurses.c
	gcc $(CC_FLAGS) -c libNcurses.c

menu.o: menu.c
	gcc $(CC_FLAGS) -c menu.c -o menu.o



clean: 
	rm -rf *.o main


 
