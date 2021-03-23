TARGET_PC=/home/jason/Bureau/PROJET/RPI_NCURSES/target_ncurses_PC
TARGET_PI=/home/jason/Bureau/PROJET/RPI_NCURSES/target_ncurses_PI

PATH_NCURSES_PROGRAMS=/home/jason/Bureau/PROJET/RPI_NCURSES

LD_LIBRARY_PATH=/home/jason/Bureau/PROJET/RPI_NCURSES/target_ncurses_PC/lib
LD_LIBRARY_PATH_PI=/home/jason/Bureau/PROJET/RPI_NCURSES/target_ncurses_PI/lib

CC=/home/jason/Bureau/COURS_LINUX/LE3/RPI/tools-master/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc


#L'option -I<PATH> permet d'indiquer le chemin des fichiers d'en-têtes
#L'option -L<PATH> permet d'indiquer le chemin des librairies


all: menu 


#################### PC ########################

libNcurses.o : libNcurses.c
	gcc -c -I$(TARGET_PC)/include/ncurses -I$(TARGET_PC)/include libNcurses.c

menu.o: menu.c
	gcc -c menu.c -o menu.o


menu: menu.o libNcurses.o
	gcc -L$(LD_LIBRARY_PATH) libNcurses.o menu.o  -o menu -lncurses -lpanel -lmenu -lform


#################### FIN PC ######################



menu_PI.o: menu.c
	$(CC) -c -I$(TARGET_PI)/include/ncurses -I$(TARGET_PI)/include menu.c -o menu_PI.o


menu_PI: menu_PI.o
	$(CC) -L$(LD_LIBRARY_PATH_PI) menu_PI.o -o menu_PI -lncurses -lpanel -lmenu -lform



clean :
	rm *.o
	rm -rf menu
	rm -rf menu_PI
	rm -rf form_*