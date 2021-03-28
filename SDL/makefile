all: read_write.o
	gcc -o partition partition_sdl.c read_write.o `sdl2-config --cflags --libs` -lSDL2_ttf -lSDL2_image -lm

read_write.o:../buzzer_boutons/read_write.c
	$(CC) -c -I$(PATH_WPI)/include ../buzzer_boutons/read_write.c -o read_write.o 

clean : 
	rm -rf partition *.o
