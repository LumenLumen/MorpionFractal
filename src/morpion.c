#include "../lib/morpion.h"
#include "../lib/sauvegarde.h"
#include "../lib/screens.h"
#include <time.h>
/**
    \file morpion.c
    \brief Programme principal (main), initialise les bibliothèques et les éléments nécessaires.
    \author Groupe morpion fractal
    \version 1
    \date 9 février 2023
*/

/**
    \fn int main (int argc, char * argv[]){
    \brief Initialisation des variables nécessaires tout au long du programme et appelle du menu.
    \return 0
*/
int main (int argc, char * argv[]){

    srand(time(NULL));

    option_t * options = malloc(sizeof(option_t)) ;
    SDL_Window * window = NULL ;
    SDL_Renderer * renderer = NULL ;

    //Initialise SDL pour l'aspect visuel.
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0){
        free(options);
        return 0;
    }

    //Initialise TTF
	if(TTF_Init() == -1) {
        free(options);
        SDL_Quit();
        return 0;
	}

    //Création de la fenêtre.
    window = SDL_CreateWindow("Morpion fractal", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_H, SCREEN_W + ESPACE_TEXTE, 0);
    if (window == NULL){
        free(options);
        TTF_Quit();
        SDL_Quit();
        return 0;
    }
   

    //Création du rendu.
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL){
        SDL_DestroyWindow(window);
        free(options);
        TTF_Quit();
        SDL_Quit();
        return 0;
    }

    
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 1024) == -1) //Initialisation de l'API Mixer
    {
      Mix_GetError();
    }
    Mix_VolumeMusic(MIX_MAX_VOLUME / 2); //Mettre le volume à la moitié
    Mix_Music *musique; //Création d'un pointeur de type Mix_Music
    musique = Mix_LoadMUS("./src/musique/test.mp3"); //Chargement de la musique
    Mix_PlayMusic(musique, -1); //Jouer infiniment la musique

    init_option(options);

    menuscreen(window, renderer, options);

    //Libération de la mémoire
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    free(options);
    TTF_Quit();
    Mix_FreeMusic(musique); //Libération de la musique
    Mix_CloseAudio(); //Fermeture de l'API
    SDL_Quit(); 
   
    return 0;
}

