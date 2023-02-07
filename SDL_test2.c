#include <SDL.h>
#include <stdio.h>


//Fonction qui sort les erreurs par message et exit le programme.
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

    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        SDL_ExitWithError("Initialisation SDL");
    }

    window = SDL_CreateWindow("Première fenêtre SDL 2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, 0);

    if (window == NULL){
        SDL_ExitWithError("Création fenêtre échouée"); 
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    if (renderer == NULL)
        SDL_ExitWithError("Création rendu échouée");

/*------------------------------------ -----------------------------*/

    SDL_Surface * image = NULL ; //On créé une image 
    SDL_Texture * texture = NULL ; //Et une texture
    image = SDL_LoadBMP("candyland.bmp");//On charge une image .bmp

    if (image == NULL){ //Verification du résultat de la fonction précédente.
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de charger l'image");
    }

    //On charge l'image dans la texture.
    texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image); //On libère l'image, on n'en aura plus besoin.

    if (texture == NULL){ //On vérifie que la fonction a fonctionné (toujours).
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de créer la texture");
    }

    SDL_Rect rectangle ;
    
    //On charge la texture dans la mémoire avec les hauteurs et largeurs auxquelles on veut afficher l'image.
    if(SDL_QueryTexture(texture, NULL, NULL, &rectangle.w, &rectangle.h) != 0){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de charger la texture");
    }
    
    //On centre l'image. 
    rectangle.x = (1024 - rectangle.w) / 2 ;
    rectangle.y = (768 - rectangle.h) / 2 ;

    //On copie dans le renderer la texture qu'on a chargé en mémoire.
    if(SDL_RenderCopy(renderer, texture, NULL, &rectangle) != 0){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible d'afficher la texture");
    }

    SDL_RenderPresent(renderer); //On affiche le rendu.


/*-------------------------------------------------------------------*/

    SDL_Delay(5000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
} 