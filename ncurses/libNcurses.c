#include "libNcurses.h"

char *choices[] =			/* The menu choices */
{
    "Nouvelle partition",
    "Charger une partition",
    "Aide",
    "Quitter l'application",
    NULL
};

void runNcurses(void){
    int choiceno;

    initFenetre();

    /* ACQUIRE THE USER'S CHOICE */
    do {
        choiceno = runMenu(stdscr, 50, 100, 2, 50, choices,"Choisir une option");

    } while (handleChoice(choiceno) == -1);


    printf("\n\nYou chose item %d, %s\n", choiceno, choiceno>=0 ? choices[choiceno] : choices[-choiceno]);
    printf("'%s'\n",name_Partition);
}


void initFenetre(){
	initscr();		/* start ncurses */
    cbreak();		/* immediately acquire each keystroke */
    noecho();		/* do not echo user keystrokes */
    keypad(stdscr, TRUE);	/* enable detection of function keys */
    initColors();		/* enable colors and initialize pairs */

    /* SET UP AND PAINT STANDARD SCREEN */
    wattrset(stdscr, COLOR_PAIR(WHITEONBLUE) | WA_BOLD);
    wclrscr(stdscr);
    mvwaddstr(stdscr, 10, 10, "");
    touchwin(stdscr);
    wrefresh(stdscr);
    
}


//////////////////////// FORM NOUVELLE ////////////////////////
/*
 * This is useful because ncurses fill fields blanks with spaces.
 */
char* trim_whitespaces(char *str)
{
	char *end;

	// trim leading space
	while(isspace(*str))
		str++;

	if(*str == 0) // all spaces?
		return str;

	// trim trailing space
	end = str + strnlen(str, 128) - 1;

	while(end > str && isspace(*end))
		end--;

	// write new null terminator
	*(end+1) = '\0';

	return str;
}

int driver(int ch,FORM *form,FIELD *fields[3],WINDOW *wUI)
{
	int i;

	switch (ch) {

        case KEY_F(1):
            return -1;
        break;

        case 10:
            return 0;
        break;

		case KEY_F(2):
			// Or the current field buffer won't be sync with what is displayed
			form_driver(form, REQ_NEXT_FIELD);
			form_driver(form, REQ_PREV_FIELD);
			move(LINES-3, 2);

			for (i = 0; fields[i]; i++) {
				printw("%s", trim_whitespaces(field_buffer(fields[i], 0)));

				if (field_opts(fields[i]) & O_ACTIVE)
					printw("\"\t");
				else
					printw(": \"");
			}

			refresh();
			pos_form_cursor(form);
			break;

		case KEY_DOWN:
			form_driver(form, REQ_NEXT_FIELD);
			form_driver(form, REQ_END_LINE);
			break;

		case KEY_UP:
			form_driver(form, REQ_PREV_FIELD);
			form_driver(form, REQ_END_LINE);
			break;

		case KEY_LEFT:
			form_driver(form, REQ_PREV_CHAR);
			break;

		case KEY_RIGHT:
			form_driver(form, REQ_NEXT_CHAR);
			break;

		// Delete the char before cursor
		case KEY_BACKSPACE:
		case 127:
			form_driver(form, REQ_DEL_PREV);
			break;

		// Delete the char under the cursor
		case KEY_DC:
			form_driver(form, REQ_DEL_CHAR);
			break;

		default:
			form_driver(form, ch);
			break;
	}
	touchwin(wUI);	/* refresh prior to getch() */
	wrefresh(wUI); 	/* refresh prior to getch() */
    return 1;
}


int initFormPartition(){
    int ch,res;
    FORM *form;
    FIELD *fields[3];
	WINDOW * wBorder=NULL;
	WINDOW *wUI=NULL;


	wBorder = getWindowBorder("Nouvelle Partition");
	wUI = getUserInterface(wBorder);
	
    /*
        new_field(1, 50, 20, 15, 0, 0);
        1=>
        50=>
        20=>coordonnée y
        15=>coordonnée x
	*/

    fields[0] = new_field(1, 50, 10, 0, 0, 0); // création champs 1
	fields[1] = new_field(1, 50, 10, 25, 0, 0); // création champs 1
	fields[2] = NULL;
	assert(fields[0] != NULL && fields[1] != NULL);

	// color field + ajout attribut
	set_field_back(fields[0],COLOR_PAIR(WHITEONRED) | WA_BOLD);
	set_field_back(fields[1],COLOR_PAIR(WHITEONRED) | WA_BOLD);

	set_field_buffer(fields[0], 0, "Nom de la partition :");
	set_field_buffer(fields[1], 0, "");

	set_field_opts(fields[0], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
	set_field_opts(fields[1], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);

    form = new_form(fields); // on crée le formulaire
	assert(form != NULL);

	set_form_win(form, wBorder); // on synchronise le form avec les deux interfaces
	set_form_sub(form,wUI);
	
	post_form(form); // on l'ajoute

	/* REFRESH THE BORDER WINDOW PRIOR TO ACCEPTING USER INTERACTION */
	touchwin(wBorder);
	wrefresh(wBorder);
	touchwin(wUI);
	wrefresh(wUI); 

    do {
        ch=getch();
        res=driver(ch,form,fields,wUI);
    } while (res != -1 && res !=0);

    // Or the current field buffer won't be sync with what is displayed
    form_driver(form, REQ_NEXT_FIELD);
    form_driver(form, REQ_PREV_FIELD);
    move(LINES-3, 2);
    //printf("Mot: '%s'", trim_whitespaces(field_buffer(fields[1], 0)));

	if (res == 0)
		strcpy(name_Partition,trim_whitespaces(field_buffer(fields[1], 0)));

	unpost_form(form);
	free_form(form);
	free_field(fields[0]);
	free_field(fields[1]);
	delwin(wUI);
	delwin(wBorder);
	return res;
}

///////////////////////////////////////////////////////////////////

WINDOW * getWindowBorder(char *title){
	WINDOW * wBorder=NULL;
	/* SET UP WINDOW FOR MENU'S BORDER */
	wBorder = newwin(50, 100, 2, 50);
	wattrset(wBorder, COLOR_PAIR(WHITEONRED) | WA_BOLD);
	wclrscr(wBorder); 
	box(wBorder, 0, 0);
	wCenterTitle(wBorder, title);
	return wBorder;
}

WINDOW * getUserInterface(WINDOW * wBorder){
	WINDOW *wUI;
	/* Set up WINDOW FOR USER  */
	wUI = derwin(wBorder, 20,80, 2, 2);
	wbkgd(wUI,COLOR_PAIR(WHITEONRED) | WA_BOLD);
	return wUI;
}


int initFormHelp(){
	int ch,res;
    FORM *form;
    FIELD *fields[2];
	WINDOW * wBorder=NULL;
	WINDOW *wUI=NULL;

	wBorder = getWindowBorder("Aide");
	wUI = getUserInterface(wBorder);

    fields[0] = new_field(2, 60, 10, 0, 0, 0); // création champs 1
	fields[1] = NULL;

	assert(fields[0] != NULL);

	// color field + ajout attribut
	set_field_back(fields[0],COLOR_PAIR(WHITEONRED) | WA_BOLD);
	set_field_buffer(fields[0], 0, "Veuillez consulter la page SDL qui vient de s'ouvrir !              F1 pour quitter");

    form = new_form(fields); // on crée le formulaire
	assert(form != NULL);
	curs_set(0); // on cache le curseur

	set_form_win(form, wBorder); // on synchronise le form avec les deux interfaces
	set_form_sub(form,wUI);
	post_form(form); // on l'ajoute

	/* REFRESH THE BORDER WINDOW PRIOR TO ACCEPTING USER INTERACTION */
	touchwin(wBorder);
	wrefresh(wBorder);
	touchwin(wUI);
	wrefresh(wUI); 

    do { // tant que la touche appuyé est différente de F1
        ch=getch();
    } while (ch != KEY_F(1));

	unpost_form(form);
	free_form(form);
	free_field(fields[0]);
	delwin(wUI);
	delwin(wBorder);
	return res;
}


//////////////////////////////////////////////////////////////////////

void wCenterTitle(WINDOW *pwin, const char * title)
	{
	int x, maxy, maxx, stringsize;
	getmaxyx(pwin, maxy, maxx);
	stringsize = 4 + strlen(title);
	x = (maxx - stringsize)/2;
	mvwaddch(pwin, 0, x, ACS_RTEE);
	waddch(pwin, ' ');

	waddstr(pwin, title);
	waddch(pwin, ' ');
	waddch(pwin, ACS_LTEE);
	}

void wclrscr(WINDOW * pwin)
	{
	int y, x, maxy, maxx;
	getmaxyx(pwin, maxy, maxx);
	for(y=0; y < maxy; y++)
		for(x=0; x < maxx; x++)
			mvwaddch(pwin, y, x, 32);
	}

bool initColors()
{
    if(has_colors())
        {
        start_color();
        init_pair(WHITEONRED, COLOR_WHITE, COLOR_RED);
        init_pair(WHITEONBLUE, COLOR_WHITE, COLOR_BLUE);
        init_pair(REDONWHITE, COLOR_RED, COLOR_WHITE);
        return(true);
        }
    else
        return(false);
}


int runMenu(
		WINDOW *wParent,
		int height,
		int width,
		int y,
		int x,
		char *choices[],
		char titre[20]
		)
	{
	int c;			/* key pressed */	
	ITEM **my_items;	/* list of items on this menu */
	MENU *my_menu;		/* the menu structure */

	WINDOW *wUI;		/* window on which the user
					interacts with the menu */
	WINDOW *wBorder;	/* window containing the wUI window
					and the border and title */

        int n_choices;		/* number of items on menu */
        int ssChoice;		/* subscript to run around the choices array */
	int my_choice = -1;	/* the zero based numeric user choice */

	/* CALCULATE NUMBER OF MENU CHOICES */
	for(n_choices=0; choices[n_choices]; n_choices++);

	/* ALLOCATE ITEM ARRAY AND INDIVIDUAL ITEMS */
        my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
        for(ssChoice = 0; ssChoice < n_choices; ++ssChoice)
                my_items[ssChoice] = new_item(choices[ssChoice], NULL);
	my_items[n_choices] = (ITEM *)NULL;

	/* CREATE THE MENU STRUCTURE */
	my_menu = new_menu((ITEM **)my_items);

	/* PUT > TO THE LEFT OF HIGHLIGHTED ITEM */
	set_menu_mark(my_menu, "> ");

	/* SET UP WINDOW FOR MENU'S BORDER */
	wBorder = newwin(height, width, y, x);
	wattrset(wBorder, COLOR_PAIR(WHITEONRED) | WA_BOLD);
	wclrscr(wBorder); 
	box(wBorder, 0, 0);
	wCenterTitle(wBorder, titre);

	/* SET UP WINDOW FOR THE MENU'S USER INTERFACE */
	wUI = derwin(wBorder, height-2, width-2, 2, 2);

	/* ASSOCIATE THESE WINDOWS WITH THE MENU */
	set_menu_win(my_menu, wBorder);
	set_menu_sub(my_menu, wUI);

	/* MATCH MENU'S COLORS TO THAT OF ITS WINDOWS */
	set_menu_fore(my_menu, COLOR_PAIR(REDONWHITE));
	set_menu_back(my_menu, COLOR_PAIR(WHITEONRED) | WA_BOLD);

	/* SET UP AN ENVIRONMENT CONDUCIVE TO MENUING */
	keypad(wUI, TRUE);	/* enable detection of function keys */
	noecho();		/* user keystrokes don't echo */
	curs_set(0);		/* make cursor invisible */

    mvprintw(LINES - 3, 2, "Appuyer sur <ENTER> pour choisir une option");
	mvprintw(LINES - 2, 2, "Up and Down pour naviguer (F1 pour quitter)");

	/* DISPLAY THE MENU */
	post_menu(my_menu);

	/* REFRESH THE BORDER WINDOW PRIOR TO ACCEPTING USER INTERACTION */
	touchwin(wBorder);
	wrefresh(wBorder);  

    

	/* HANDLE USER KEYSTROKES */
	while(my_choice == -1)
		{
		touchwin(wUI);	/* refresh prior to getch() */
		wrefresh(wUI); 	/* refresh prior to getch() */
		c = getch();
		switch(c)
			{
			case KEY_F(1): return -3; break;
			case KEY_DOWN:
				menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;/* SET UP WINDOW FOR MENU'S BORDER */
			case 10:	/* Enter */
				my_choice = item_index(current_item(my_menu));

				/* RESET CURSOR IN CASE MORE SELECTION IS NECESSARY */
				pos_menu_cursor(my_menu);
				break;
			}
		}	

	/* FREE ALL ALLOCATED MENU AND ITEM RESOURCES */
	unpost_menu(my_menu);
        for(ssChoice = 0; ssChoice < n_choices; ++ssChoice)
                free_item(my_items[ssChoice]);
	free_menu(my_menu);

	/* DESTROY MENU WINDOW AND BORDER WINDOWS */
	delwin(wUI);
	delwin(wBorder);

	/* UNDO MENU SPECIFIC ENVIRONMENT */
	curs_set(1);			/* make cursor visible again */
	
	/* REPAINT THE CALLING SCREEN IN PREPARATION FOR RETURN */
	touchwin(wParent);
	wrefresh(wParent);

	/* RETURN THE ZERO BASED NUMERIC USER CHOICE */
	return(my_choice);
}

int handleChoice(int choix){
    int choiceno;
    char **menu_options=NULL;
	int nbPartition=20;

    switch (choix)
    {

        case 0:
            //printf("Nouvelle partition \n");
            choiceno = initFormPartition();
			if (-1 == choiceno) { // QUITTER
                return -1; // on revient au menu supérieur
            } else {
                printf(("On lance la partition crée dans SDL\n"));
				endwin(); /// POUR LE MOMENT !
            }
        break;


        case 1:
            menu_options = calloc (nbPartition,sizeof(char*));
            menu_options[0]="Partition 1";
            menu_options[1]="Partition 2";
            menu_options[2]="Partition 3";
            menu_options[3]="Partition 4";
            menu_options[4]="Partition 5";
            menu_options[5]="Partition 1";
            menu_options[6]="Partition 2";
            menu_options[7]="Partition 3";
            menu_options[8]="Partition 4";
            menu_options[9]="Partition 5";
            menu_options[10]="Partition 1";
            menu_options[11]="Partition 2";
            menu_options[12]="Partition 3";
            menu_options[13]="Partition 4";
            menu_options[14]="Partition 5";
            menu_options[15]="Partition 1";
            menu_options[16]="Partition 2";
            menu_options[17]="Partition 3";
            menu_options[18]="Quitter";
               
            choiceno = runMenu(stdscr, 50, 100, 2, 50, menu_options,"Charger Partition");

            if (nbPartition-2 == choiceno || choiceno == -3) { // QUITTER
                free(menu_options);
                return -1; // on revient au menu supérieur
            } else {
                printf(("On lance une partition dans SDL\n"));
				endwin(); /// POUR LE MOMENT !
            }
        break;

        case 2:
			printf(("On lance une partition dans SDL\n"));
			initFormHelp();
			endwin();
        break;

		case -3:
        case 3:
            printf("Quitter\n");
            endwin();	/* end ncurses */
        break;
        
        default:
            break;
        }
}





