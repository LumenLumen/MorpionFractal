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

    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        SDL_ExitWithError("Initialisation SDL");
    }

    if (SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer) != 0)
        SDL_ExitWithError("Création fenêtre + rendu");

/*-------------------------------------------------------*/
    SDL_bool program_launched = SDL_TRUE ;

    while(program_launched){ //Boucle infinie :)
        SDL_Event event ;
        
        //On attends un événement.
        while(SDL_PollEvent(&event)){ //SDL_WaitEvent(&event) == 1 pour bloquer l'exécution du prog

            switch(event.type){
                //Si la touche b est pressée.
                case SDL_KEYDOWN :
                    switch (event.key.keysym.sym){
                        case SDLK_b :
                            printf("Vous avez appuyé sur B.\n");
                            continue; //On met des continue plutôt que des break pour que le programme continue de s'exécuter.
                        default : continue ;
                    }

                //Si la touche b est relâchée.
                case SDL_KEYUP :
                    switch (event.key.keysym.sym){
                        case SDLK_b :
                            printf("Vous avez relaché B.\n");
                            continue;
                        default : continue ;
                    }
                
                //Affiche à chaque mouvement de la souris les coordonnées du curseur.
                /*case SDL_MOUSEMOTION :
                    printf("%d / %d\n", event.motion.x, event.motion.y);
                    break;*/

                /*case SDL_MOUSEBUTTONDOWN :
                    printf("Clic en %d, %d\n", event.button.x, event.button.y);
                    break;*/

                //Affiche les clics effectués sur la fenêtre.
                case SDL_MOUSEBUTTONDOWN :
                    if (event.button.clicks >= 2) 
                        printf("Double-clic !\n"); 
                    if (event.button.button == SDL_BUTTON_LEFT) 
                        printf("Clic gauche !\n");
                    if (event.button.button == SDL_BUTTON_RIGHT) 
                        printf("Clic droit !\n");
                    break;

                //La croix en huat à droite est pressée.
                case SDL_QUIT : 
                    program_launched = SDL_FALSE ; 
                    break ;

                default : break ;
            }
        }
    }
/*-------------------------------------------------------*/

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}