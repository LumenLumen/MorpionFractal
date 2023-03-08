#include <SDL.h>
#include <stdio.h>


void SDL_ExitWithError(const char * message){
    SDL_Log("Erreur : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}


int main (int argc, char ** argv){
    SDL_version nb;
    SDL_Window * window = NULL ;
    SDL_Renderer * renderer = NULL ;

    SDL_VERSION(&nb);
    printf("Bienvenue sur la SDL %d.%d.%d !\n", nb.major, nb.minor, nb.patch);

    //Initialise SDL pour l'aspect visuel
    //Visuel + son : SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        SDL_ExitWithError("Initialisation SDL");
    }

    //Créer une fenêtre et un rendu. Je vous conseille de tester le code en commentaire ci-dessous pour voir la différence.
    if (SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer) != 0)
        SDL_ExitWithError("Création fenêtre + rendu");

/* ------------- EQUIVAUT A ---------------
    window = SDL_CreateWindow("Première fenêtre SDL 2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);

    if (window == NULL){
        SDL_ExitWithError("Création fenêtre échouée"); 
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    if (renderer == NULL)
        SDL_ExitWithError("Création rendu échouée");
----------------------------------------*/

    //Change la couleur RGB du renderer. Le dernier paramètre est la transparence.
    if (SDL_SetRenderDrawColor(renderer, 112, 168, 237, SDL_ALPHA_OPAQUE) != 0)
        SDL_ExitWithError("Impossible de la couleur du rendu");

    //Dessine un point sur le renderer au coordonnées (100,450)
    if (SDL_RenderDrawPoint(renderer, 100, 450) != 0)
        SDL_ExitWithError("Impossible de dessiner un point");
    
    //Dessine une ligne sur le renderer de (50,50) à (500,500)
    if (SDL_RenderDrawLine(renderer, 50, 50, 500, 500) != 0)
        SDL_ExitWithError("Impossible de dessiner une ligne");

    //Il y a un type rectangle dans SDL.
    SDL_Rect rectangle ;
    rectangle.x = 300 ;//Coordonnées x de l'angle haut gauche
    rectangle.y = 300 ;//Corddonnées y de l'angle haut gauche
    rectangle.w = 200 ;//Longueur du rectangle
    rectangle.h = 120 ;//Hauteur

    //Changement de couleur parce que c'est fun.
    if (SDL_SetRenderDrawColor(renderer, 30, 200, 100, SDL_ALPHA_OPAQUE) != 0)
        SDL_ExitWithError("Impossible de la couleur du rendu");

    //Tracer d'un rectangle plein sur le renderer.
    //Pour rectangle creux : SDL_RenderDrawRect.
    if (SDL_RenderFillRect(renderer, &rectangle) != 0)
        SDL_ExitWithError("Impossible de dessiner un rectangle");

    //Application du renderer sur la fenêtre
    SDL_RenderPresent(renderer);

    SDL_Delay(5000); // Temps d'attente avant fermeture de la fenêtre.

    //Libération de la mémoire (obligatoire)
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}