#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <sys/time.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include <unistd.h>
#include "../buzzer_boutons/read_write.h"

#define     TPS1PART    5

int tabNotes[8] = {DO,RE,MI,FA,SOL,LA,SI,DO2};


int hauteurs[4] = {75,245,415,575};
int diffHauteur[8] = {110,99,88,77,66,56,46,35};
SDL_Rect barreDef = {100,75,5,130};

/**
 * @brief Analyse la partition pour calculer combien de rectangles seront nécessaires pour représenter toutes les notes
 * 
 * @param p La partition
 * @return int Le nomnbre de rectangles
 */
int GetTailleTabNotes(partition_t p){
    //on veut savoir combien de rectangles seront nécessaires pour dessiner toutes les notes.
    // 1px = 5ms
    // 1 ligne = 900px
    int cpt=0;
    int nbRec = 0;
    //Temps écoulé depuis le début de la mélodie
    int partTime = 0;

    int indexHauteur1;
    int indexHauteur2;
    une_note_t note;



    while(p.mel[cpt].note != -1 && cpt < MAX_NOTES){
        //On calcule le nombre de rectangles nécessaires : 1 par note, 2 si la note chevauche 2 lignes.
        note = p.mel[cpt];
        if(note.note == BLANC){
            cpt++;
            partTime += note.ms;
            continue;
        }
        indexHauteur1 = floor((int)((partTime)/4500)%4);
        indexHauteur2 = floor((int)((note.ms + partTime)/4500)%4);
        nbRec += indexHauteur2 - indexHauteur1 + 1;

        printf("temps note : %d | temps total : %d | somme : %d | nbRec : %d | On a ajouté : %d\n",note.ms,partTime,note.ms+partTime,nbRec, indexHauteur2 - indexHauteur1 + 1);
        partTime += note.ms;
        cpt++;
    }

    

    printf("\nIl nous faut %d rectangles, on alloue %ld octets\n",nbRec,nbRec * sizeof(SDL_Rect));
    printf("\n\n\n");
    cpt=0;


    //On a le nombre de rectangles, on peut allouer de la mémoire au tableau

    
    return nbRec;

}

/**
 * @brief Alloue de la mémoire pour le tableau de notes, et le remplit en calculant les coordonnées de chaque notes sur la partition
 * 
 * @param p La partition
 * @param tab Le tableau de SDL_Rect représentant les notes
 * @param size Le nombre de SDL_Rect du tableau (calculé grâce à GetTailleTabNotes())
 * @return SDL_Rect** Le tableau de SDL_REct représentant les notes
 */
SDL_Rect** GetTabRectNotes(partition_t p, SDL_Rect** tab, int size){
    //on veut maintenant calculer les positions de chaque note.
    // 1px = 5ms
    // 1 ligne = 900px
    int cpt=0,cpt2=0;
    //Temps écoulé depuis le début de la mélodie
    int partTime = 0;
    int index=0;
    int indexHauteur1;
    int indexHauteur2;
    une_note_t note;
    SDL_Rect currRect={0,0,200,100};
    int indexNote;
    int i;

    tab = (SDL_Rect**)malloc(size*sizeof(SDL_Rect*));
    for(cpt2=0;cpt2<size;cpt2++){
        tab[cpt2] = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    }

    while(p.mel[cpt].note != -1 && cpt < MAX_NOTES){
        //On calcule le nombre de rectangles nécessaires : 1 par note, 2 si la note chevauche 2 lignes.
        note = p.mel[cpt];
        if(note.note == BLANC){
            //Pas besoin de dessiner si y'a pas de note
            partTime += note.ms;
            cpt++;
            continue;
        }




        indexHauteur1 = floor((int)((partTime)/4500)%4);
        indexHauteur2 = floor((int)((note.ms + partTime)/4500)%4);
        if(0){//2 rectangles (ou +)

        }
        else{ //La note est sur 1 seule ligne
            //Calcul de l'abscisse,
            
            currRect.x = (partTime - 4500 * indexHauteur1)/TPS1PART + 100;


            //Calcul de l'ordonnée
            //Un petit switch dégeu
            switch(note.note){
                case DO:
                    indexNote = 0;
                break;
                case RE:
                    indexNote = 1;
                break;
                case MI:
                    indexNote = 2;
                break;
                case FA:
                    indexNote = 3;
                break;
                case SOL:
                    indexNote = 4;
                break;
                case LA:
                    indexNote = 5;
                break;
                case SI:
                    indexNote = 6;
                break;
                case DO2:
                    indexNote = 7;
                break;
            }
            currRect.y = (hauteurs[indexHauteur1] + diffHauteur[indexNote]);

            //Calcul largeur
            currRect.w = note.ms / 5;

            
        }

        currRect.h = 10;
        *tab[index++] = currRect;

        printf("On ajoute à l'indice %d un rectangle : x=%d | y=%d | w=%d\n",index - 1,tab[index - 1]->x,tab[index - 1]->y,tab[index - 1]->w);

        partTime += note.ms;
        cpt++;
        
    }

    return tab;

    
}


int main()
{
    SDL_Surface *ecran = NULL, *texte = NULL, *fond = NULL;
    SDL_Rect position;
    SDL_Event events;
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0, 255};
    SDL_Window *sdlWindow; 
    SDL_Renderer *sdlRenderer; 
    int isOpen = 1;
    int i;

    struct timeval  tv;
    struct timespec tms;
    double initialTime = 0, currentTime = 0, lastTime = 0, time_in_mill;
    int firstTime=1,lancerDefilement = 1;
    int indexHauteur = 0;
    int tempX;

    //Partie permettant le réglage de la hauteur de chaque note dans la partition

/*     partition_t part;
    une_note_t note;
    int index = 0;
    for(i=0;i<64;i+=2){
        
        note.note = tabNotes[index++];
        if(index>=8)index = 0;
        note.ms = 400;

        part.mel[i] = note;

        note.note = BLANC;
        note.ms = 50;

        part.mel[i + 1] = note;
    } */

    partition_t p;
    lireMelodie("testEcriture4",&p);

    SDL_Rect** notes;

    int nbRec = GetTailleTabNotes(p);
    notes = GetTabRectNotes(p,notes,nbRec);

    /* for(i=0;i<nbRec;i++){
            printf("On dessinera : x=%d|y=%d|w=%d\n",notes[i]->x,notes[i]->y,notes[i]->w);
    } */

    CHECK_T(SDL_Init(SDL_INIT_VIDEO),"ERREUR INIT");

    printf("Init Fait\n");
    TTF_Init();

    
    CHECK_P(sdlWindow = SDL_CreateWindow("Titre", 460, 50, 640, 480, 0),SDL_GetError());

    SDL_SetWindowPosition(sdlWindow,460,50);
    SDL_SetWindowTitle(sdlWindow,"Test SDL2");

    printf("Fenetre Fait\n");

    CHECK_P(sdlRenderer = SDL_CreateRenderer(sdlWindow,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),SDL_GetError())

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  // permet d'obtenir les redimensionnements plus doux. 
    SDL_RenderSetLogicalSize(sdlRenderer, 1000, 1000);


    ecran = SDL_GetWindowSurface(sdlWindow);

    printf("Ecran Fait\n");

// ------------------------------------------------------------------------------------ //
// ------------------------------------------------------------------------------------ //
// --------------------------------- CREATION DES 4 PARTITIONS ---------------------------------- //
// ------------------------------------------------------------------------------------ //
// ------------------------------------------------------------------------------------ //

    SDL_Surface* image;
    CHECK_P(image = IMG_Load("Partition_resized.png"),"Erreur creation image");
    SDL_Texture* pTexturePartition1 = SDL_CreateTextureFromSurface(sdlRenderer, image);
    SDL_Texture* pTexturePartition2 = SDL_CreateTextureFromSurface(sdlRenderer, image);
    SDL_Texture* pTexturePartition3 = SDL_CreateTextureFromSurface(sdlRenderer, image);
    SDL_Texture* pTexturePartition4 = SDL_CreateTextureFromSurface(sdlRenderer, image);
    SDL_FreeSurface(image);
    SDL_Rect src_part1 = {0, 0, 0, 0}, src_part2 = {0, 0, 0, 0}, src_part3 = {0, 0, 0, 0}, src_part4 = {0, 0, 0, 0};
    SDL_Rect dst_part1 = { 0, 50, 1000, 170 }, dst_part2 = { 0, 220, 1000, 170 }, dst_part3 = { 0, 390, 1000, 170 }, dst_part4 = { 0, 550, 1000, 170 };

    SDL_QueryTexture(pTexturePartition1, NULL, SDL_TEXTUREACCESS_STATIC, &src_part1.w, &src_part1.h);
    SDL_QueryTexture(pTexturePartition2, NULL, SDL_TEXTUREACCESS_STATIC, &src_part2.w, &src_part2.h);
    SDL_QueryTexture(pTexturePartition3, NULL, SDL_TEXTUREACCESS_STATIC, &src_part3.w, &src_part3.h);
    SDL_QueryTexture(pTexturePartition4, NULL, SDL_TEXTUREACCESS_STATIC, &src_part4.w, &src_part4.h);





    // ------------------------------------------------------------------------------------ //
    // ------------------------------------------------------------------------------------ //
    // --------------------------------- AFFICHAGE DU TITRE ---------------------------------- //
    // --------------à terme, on passera un argument à la fonction qui génèrera la sdl-------- //
    // ------------------------------------------------------------------------------------ //

    char* titre = "Test titre";


    //Chargement de la police 
    //police = TTF_OpenFont("/usr/share/fonts/truetype/msttcorefonts/Arial.ttf", 40);
    //Pour le rpi
    police = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 40);
    //Écriture du texte dans la SDL_Surface texte en mode Blended (optimal)
    texte = TTF_RenderText_Blended(police, titre, couleurNoire);
    SDL_Texture* pTextureTitre = SDL_CreateTextureFromSurface(sdlRenderer, texte);
    SDL_Rect srcTexte={0,0,0,0} , dst_Texte={425,5,150,40};
    SDL_QueryTexture(pTextureTitre, NULL, SDL_TEXTUREACCESS_STATIC, &srcTexte.w, &srcTexte.h);
    
    printf("Titre fait\n");

    while (isOpen)
    {

        //Gestion des évènements
         while (SDL_PollEvent(&events))
        {
            switch (events.type)
            {
            case SDL_QUIT:
                isOpen = 0;
                break;
            }
        }

        //Réinitialisation de la fenêtre
        SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 255, 255); 
        SDL_RenderClear(sdlRenderer); 


        //Affichage des partitions
        SDL_RenderCopy(sdlRenderer, pTexturePartition1, &src_part1, &dst_part1); // Affiche la texture entièrement
        SDL_RenderCopy(sdlRenderer, pTexturePartition2, &src_part2, &dst_part2); // Affiche la texture entièrement
        SDL_RenderCopy(sdlRenderer, pTexturePartition3, &src_part3, &dst_part3); // Affiche la texture entièrement
        SDL_RenderCopy(sdlRenderer, pTexturePartition4, &src_part4, &dst_part4); // Affiche la texture entièrement

        //Affichage du titre
        SDL_RenderCopy(sdlRenderer, pTextureTitre, &srcTexte, &dst_Texte); // Affiche la texture entièrement
        SDL_SetRenderDrawColor(sdlRenderer,0,0,0,255);
        
        //printf("%f\n",time_in_mill);


        //Mise à jour de la position de la barre
        if(lancerDefilement){
            gettimeofday(&tv, NULL);
            time_in_mill = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ;

            if(firstTime){
                firstTime=0;
                initialTime = time_in_mill;
            }
            else{
                currentTime = time_in_mill - initialTime; //Temps écoulé en ms
                //printf("cT = %f, lT = %f\n",currentTime,lastTime);
                if(currentTime - lastTime > 10){
                    //printf("currentTime = %f, initialTime = %f, time=  %f\n",currentTime,initialTime,time_in_mill);
                    if(currentTime < 0 || currentTime > 18000){
                        //Si on est en dehors du temps prévu, on réinitialise tout
                        firstTime = 1;
                        currentTime = 0;
                        lancerDefilement = 0;
                        barreDef.x = 100;
                        barreDef.y = 75;
                        barreDef.w = 5;
                        barreDef.h = 130;
                    }
                    else{
                        //On fait avancer la barre
                        indexHauteur = floor((int)(currentTime / 4500)%4);
                        tempX = (currentTime - 4500 * indexHauteur)/TPS1PART + 100;
                        //printf("indexHauteur = %d ,  (int)(currentTime / 7000) = %d| On place la barre en %d,%d\n",indexHauteur, (int)(currentTime / 7000),tempX,hauteurs[indexHauteur]);
                        barreDef.x = tempX;
                        barreDef.y = hauteurs[indexHauteur];

                    }   
                    lastTime = currentTime;
                }
                
                
            }

        }

        for(i=0;i<nbRec;i++){
            /* printf("On dessine : x=%d|y=%d|w=%d\n",notes[i]->x,notes[i]->y,notes[i]->w); */
            SDL_RenderFillRect(sdlRenderer,notes[i]);
        }

        //Application de la mise à jour 
        SDL_RenderFillRect(sdlRenderer,&barreDef);

        SDL_RenderPresent(sdlRenderer); 
        
        //printf("%s\n",SDL_GetError());
    }

    SDL_DestroyTexture(pTexturePartition1);
    SDL_DestroyTexture(pTexturePartition2);
    SDL_DestroyTexture(pTexturePartition3);
    SDL_DestroyTexture(pTexturePartition4);

    TTF_CloseFont(police);
    TTF_Quit();

    SDL_FreeSurface(texte);
    SDL_Quit();

    return EXIT_SUCCESS;
} 
 
