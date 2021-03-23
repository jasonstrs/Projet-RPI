#include <form.h>
#include <assert.h>
#include <ctype.h>
#include <curses.h>	/* Necessary for all Curses programs */
#include <menu.h>	/* Gives you menuing capabilities */
#include <string.h>	/* Needed for strlen() and friends */

#include <stdio.h>
#include <stdlib.h>	/* Needed for calloc() */


#define WHITEONRED 1
#define WHITEONBLUE 2
#define WHITEONBLACK 3
#define BLACKONWHITE 4
#define REDONWHITE 5

extern char *choices[];
char name_Partition[50];


char* trim_whitespaces(char *str);
int driver(int ch,FORM *form,FIELD *fields[3],WINDOW *wUI);
int initFormPartition();
int runMenu(
        WINDOW *wParent,
		int height,
		int width,
		int y,
		int x,
		char *choices[],
		char titre[20]
		);
bool initColors(void);
void wclrscr(WINDOW * pwin);
void wCenterTitle(WINDOW *pwin, const char * title);
int handleChoice(int choix);
void initFenetre();
void runNcurses(void);

