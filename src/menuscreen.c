/*Pour compiler : gcc menuscreen.c -o menuscreen $(sdl2-config --cflags --libs)*/

#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include "../lib/screens.h"



#define SCREEN_H 800
#define SCREEN_W 800

//En cas d'erreur, la fonction affiche l'erreur avec le message passé en paramètre
void SDL_ExitWithError(const char * message){
    SDL_Log("Erreur : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

//Initialise un rectangle avec les valeurs passées en paramètre
SDL_Rect SDL_CreerRect(int x, int y, int w, int h){
    SDL_Rect rectangle;
    rectangle.x = x ;//Coordonnées x de l'angle haut gauche
    rectangle.y = y ;//Corddonnées y de l'angle haut gauche 
    rectangle.w = w ;//Longueur du rectangle
    rectangle.h = h ;//Hauteur
    return rectangle ;
}

//Prend en paramètre les coordonnés d'un clic et un rectangle.
//Renvoie vrai si le click est dans le rect, non sinon.
int SDL_ClickInButton(int mousex, int mousey, SDL_Rect button){
    return ((mousex >= button.x && mousex <= button.x + button.w) && (mousey >= button.y && mousey <= button.y + button.h));
}

int main (int argc, char ** argv){

    SDL_Window * window = NULL ;
    SDL_Renderer * renderer = NULL ;
    SDL_bool program_launched = SDL_TRUE ;
    SDL_Event event ;

    SDL_Surface * image = NULL ; 
    SDL_Texture * texture = NULL ;
    
    SDL_Rect background = SDL_CreerRect(0, 0, SCREEN_W, SCREEN_H);
    SDL_Rect newgame = SDL_CreerRect(SCREEN_W/3, 50, SCREEN_W/3, SCREEN_H/6);
    SDL_Rect loadgame = SDL_CreerRect(SCREEN_W/3, 100 + SCREEN_H/6, SCREEN_W/3, SCREEN_H/6);
    SDL_Rect optiongame = SDL_CreerRect(SCREEN_W/3, 150 + 2*SCREEN_H/6, SCREEN_W/3, SCREEN_H/6);
    SDL_Rect quitgame = SDL_CreerRect(SCREEN_W/3, 200 + 3*SCREEN_H/6, SCREEN_W/3, SCREEN_H/6);
    // A revoir si on resize la fenêtre

    //Initialise SDL pour l'aspect visuel.
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        SDL_ExitWithError("Initialisation SDL");
    }

    //Initialise TTF
	if(TTF_Init() == -1) {
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}

    //Création de la fenêtre.
    window = SDL_CreateWindow("Morpion fractal", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_H, SCREEN_W, 0);
    if (window == NULL){
        SDL_ExitWithError("Création fenêtre échouée"); 
    }

    //Création du rendu.
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Création rendu échouée");
    }

    //Fond
    if (SDL_SetRenderDrawColor(renderer, 160, 95, 165, SDL_ALPHA_OPAQUE) != 0)
        SDL_ExitWithError("Impossible de la couleur du rendu");
    
    if (SDL_RenderFillRect(renderer, &background) != 0){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de créer le rectangle background.");
    }

    //Carrés menu
    TTF_Font *police=NULL;
    //TTF_Font *TTF_OpenFont(const char * file, int ptsize);
    if( (police = TTF_OpenFont("src/font/ChowFun.ttf", 20)) == NULL){
        printf("erreur chargement font\n");
        exit(EXIT_FAILURE);
    }
        SDL_Color noir={0,0,0};
        //test création du texte
        SDL_Surface *texte=TTF_RenderUTF8_Blended(police,"coucou",noir);
        if(!texte){
            printf("Erreur à la création du texte : %s\n",SDL_GetError());
            exit(EXIT_FAILURE);
        }
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_Texture *texte_tex = SDL_CreateTextureFromSurface(renderer,texte);
        if(!texte_tex){
            printf("Erreur à la création du rendu de texte : %s\n",SDL_GetError());
            exit(EXIT_FAILURE);
        }
        SDL_FreeSurface(texte);
        //position du texte
        /* newgame.x=50;
        newgame.y=30; */
        SDL_QueryTexture(texte_tex,NULL,NULL,&(newgame.w),&(newgame.h));
        TTF_CloseFont(police);
    
   
   SDL_SetRenderDrawColor(renderer,0,0,0,255);
   SDL_RenderCopy(renderer,texte_tex,NULL,&newgame);
   

    if (SDL_SetRenderDrawColor(renderer, 80, 200, 190, SDL_ALPHA_OPAQUE) != 0)
        SDL_ExitWithError("Impossible de la couleur du rendu");
    
    image = SDL_LoadBMP("src/img/newgame.bmp");
    if (image == NULL){ 
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de charger l'image");
    }
    texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    if (texture == NULL){ 
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de créer la texture");
    }
    if(SDL_QueryTexture(texture, NULL, NULL, &newgame.w, &newgame.h) != 0){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de charger la texture");
    }
    newgame = SDL_CreerRect(SCREEN_W/3, 50, SCREEN_W/3, SCREEN_H/6);
    if(SDL_RenderCopy(renderer, texture, NULL, &newgame) != 0){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible d'afficher la texture");
    }
    

    if (SDL_RenderFillRect(renderer, &loadgame) != 0){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de créer le rectangle loadgame.");
    }

    if (SDL_RenderFillRect(renderer, &optiongame) != 0){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de créer le rectangle optiongame.");
    }

    if (SDL_RenderFillRect(renderer, &quitgame) != 0){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de créer le rectangle quitgame.");
    }

    SDL_RenderPresent(renderer);

    //DEBUT DES EVENTS
    while(program_launched){ 
        
        //On attends un événement.
        while(SDL_PollEvent(&event)){ 

            switch(event.type){
                
                case SDL_MOUSEBUTTONDOWN :
                    if (SDL_ClickInButton(event.button.x, event.button.y, newgame))
                        printf("Nouvelle partie !\n");
                        
                    else if (SDL_ClickInButton(event.button.x, event.button.y, loadgame)){

                    }
                        
                    else if (SDL_ClickInButton(event.button.x, event.button.y, optiongame))
                        printf("Affichage des options !\n");
                    else if (SDL_ClickInButton(event.button.x, event.button.y, quitgame))
                        program_launched = SDL_FALSE ;
                    continue;
                    

                //La croix en huat à droite est pressée.
                case SDL_QUIT : 
                    program_launched = SDL_FALSE ; 
                    break ;

                default : break ;
            }
        }
    }


    //Libération de la mémoire
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}