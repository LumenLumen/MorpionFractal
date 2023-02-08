/*Pour compiler : gcc gamescreen.c -o gamescreen $(sdl2-config --cflags --libs)*/

#include <SDL.h>
#include <stdio.h>

#define SCREEN_H 800
#define SCREEN_W 800
#define MARGIN 50

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

    SDL_Rect background = SDL_CreerRect(0, 0, SCREEN_W, SCREEN_H);
    SDL_Rect contour1 = SDL_CreerRect(MARGIN - 1, MARGIN - 1, SCREEN_H - MARGIN*2, SCREEN_W - MARGIN*2);
    SDL_Rect contour = SDL_CreerRect(MARGIN, MARGIN, SCREEN_H - MARGIN*2, SCREEN_W - MARGIN*2);
    SDL_Rect contour2 = SDL_CreerRect(MARGIN + 1, MARGIN + 1, SCREEN_H - MARGIN*2, SCREEN_W - MARGIN*2);

    //Initialise SDL pour l'aspect visuel.
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        SDL_ExitWithError("Initialisation SDL");
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
    if (SDL_SetRenderDrawColor(renderer, 200, 200, 200, SDL_ALPHA_OPAQUE) != 0){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de la couleur du rendu");
    }
    
    if (SDL_RenderFillRect(renderer, &background) != 0){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de créer le rectangle background.");
    }

    //Couleur
    if (SDL_SetRenderDrawColor(renderer, 200, 100, 100, SDL_ALPHA_OPAQUE) != 0){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de la couleur du rendu");
    }


    //Contour de la grille.
    if (SDL_RenderDrawRect(renderer, &contour) != 0){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de créer le rectangle contour.");
    }
    if (SDL_RenderDrawRect(renderer, &contour2) != 0){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de créer le rectangle contour.");
    }
    if (SDL_RenderDrawRect(renderer, &contour1) != 0){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de créer le rectangle contour.");
    }

    //Dessin des lignes majeures.
    if (SDL_RenderDrawLine(renderer, MARGIN + contour.w/3, contour.y, MARGIN + contour.w/3, contour.y + contour.h) != 0){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de dessiner une ligne");
    }
    if (SDL_RenderDrawLine(renderer, MARGIN + contour.w/3 + 1, contour.y, MARGIN + contour.w/3 + 1, contour.y + contour.h) != 0){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de dessiner une ligne");
    }
    if (SDL_RenderDrawLine(renderer, MARGIN + 2*contour.w/3, contour.y, MARGIN + 2*contour.w/3, contour.y + contour.h) != 0){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de dessiner une ligne");
    }
    if (SDL_RenderDrawLine(renderer, MARGIN + 2*contour.w/3 + 1, contour.y, MARGIN + 2*contour.w/3 + 1, contour.y + contour.h) != 0){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de dessiner une ligne");
    }
    if (SDL_RenderDrawLine(renderer, contour.x , MARGIN + contour.h/3, contour.x + contour.w , MARGIN + contour.h/3) != 0){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de dessiner une ligne");
    }
    if (SDL_RenderDrawLine(renderer, contour.x , MARGIN + contour.h/3 + 1, contour.x + contour.w , MARGIN + contour.h/3 + 1) != 0){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de dessiner une ligne");
    }
    if (SDL_RenderDrawLine(renderer, contour.x , MARGIN + 2*contour.h/3, contour.x + contour.w, MARGIN + 2*contour.h/3) != 0){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de dessiner une ligne");
    }
    if (SDL_RenderDrawLine(renderer, contour.x , MARGIN + 2*contour.h/3 + 1, contour.x + contour.w, MARGIN + 2*contour.h/3 + 1) != 0){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de dessiner une ligne");
    }

    //Dessin des lignes mineures verticales.

    if (SDL_RenderDrawLine(renderer, MARGIN + contour.w/9, contour.y, MARGIN + contour.w/9, contour.y + contour.h) != 0){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de dessiner une ligne");
    }
    if (SDL_RenderDrawLine(renderer, MARGIN + 2*contour.w/9, contour.y, MARGIN + 2*contour.w/9, contour.y + contour.h) != 0){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de dessiner une ligne");
    }

    if (SDL_RenderDrawLine(renderer, MARGIN + 4*contour.w/9, contour.y, MARGIN + 4*contour.w/9, contour.y + contour.h) != 0){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de dessiner une ligne");
    }
    if (SDL_RenderDrawLine(renderer, MARGIN + 5*contour.w/9, contour.y, MARGIN + 5*contour.w/9, contour.y + contour.h) != 0){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de dessiner une ligne");
    }

    if (SDL_RenderDrawLine(renderer, MARGIN + 7*contour.w/9, contour.y, MARGIN + 7*contour.w/9, contour.y + contour.h) != 0){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de dessiner une ligne");
    }
    if (SDL_RenderDrawLine(renderer, MARGIN + 8*contour.w/9, contour.y, MARGIN + 8*contour.w/9, contour.y + contour.h) != 0){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de dessiner une ligne");
    }

    //Dessins des lignes mineures horizontales
    if (SDL_RenderDrawLine(renderer, contour.x , MARGIN + 1*contour.h/9, contour.x + contour.w, MARGIN + 1*contour.h/9) != 0){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de dessiner une ligne");
    }
    if (SDL_RenderDrawLine(renderer, contour.x , MARGIN + 2*contour.h/9, contour.x + contour.w, MARGIN + 2*contour.h/9) != 0){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de dessiner une ligne");
    }
    if (SDL_RenderDrawLine(renderer, contour.x , MARGIN + 4*contour.h/9, contour.x + contour.w, MARGIN + 4*contour.h/9) != 0){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de dessiner une ligne");
    }
    if (SDL_RenderDrawLine(renderer, contour.x , MARGIN + 5*contour.h/9, contour.x + contour.w, MARGIN + 5*contour.h/9) != 0){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de dessiner une ligne");
    }
    if (SDL_RenderDrawLine(renderer, contour.x , MARGIN + 7*contour.h/9, contour.x + contour.w, MARGIN + 7*contour.h/9) != 0){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de dessiner une ligne");
    }
    if (SDL_RenderDrawLine(renderer, contour.x , MARGIN + 8*contour.h/9, contour.x + contour.w, MARGIN + 8*contour.h/9) != 0){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de dessiner une ligne");
    }

    SDL_RenderPresent(renderer);

    while(program_launched){ 
        
        //On attends un événement.
        while(SDL_PollEvent(&event)){ 

            switch(event.type){
                
                //La croix en haut à droite est pressée.
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
    SDL_Quit();
    return 0;
}