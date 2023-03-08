#include "../lib/morpion.h"
#include "../lib/sauvegarde.h"
#include "../lib/screens.h"
/**
\file morpion.c
\brief programme ...
\author Groupe morpion fractal
\version 1
\date 9 février 2023
*/
/**
\fn int main (int argc, char * argv[]){

\brief On appelle les fonctions.
*/
int main (int argc, char * argv[]){
    option_t * options = malloc(sizeof(option_t)) ;
    SDL_Window * window = NULL ;
    SDL_Renderer * renderer = NULL ;

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
    window = SDL_CreateWindow("Morpion fractal", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_H, SCREEN_W + ESPACE_TEXTE, 0);
    if (window == NULL){
        SDL_ExitWithError("Création fenêtre échouée"); 
    }

    //Création du rendu.
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Création rendu échouée");
    }

    init_option(options);

    menuscreen(window, renderer, options);

    //Libération de la mémoire
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    free(options);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
