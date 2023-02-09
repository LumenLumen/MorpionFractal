/*Pour compiler : gcc gamescreen.c -o gamescreen $(sdl2-config --cflags --libs)*/
#include "../lib/screens.h"

int SDL_AfficherGrilleVide(SDL_Renderer * renderer, SDL_Rect contour){

    SDL_Rect background = SDL_CreerRect(0, 0, SCREEN_W, SCREEN_H);
    SDL_Rect contour1 = SDL_CreerRect(contour.x - 1, contour.y - 1, contour.w, contour.h);
    SDL_Rect contour2 = SDL_CreerRect(contour.x + 1, contour.y + 1, contour.w, contour.h);

    //Fond
    if (SDL_SetRenderDrawColor(renderer, 200, 200, 200, SDL_ALPHA_OPAQUE) != 0){
        return 1;
    }
    
    if (SDL_RenderFillRect(renderer, &background) != 0){
        return 1;
    }

    //Couleur
    if (SDL_SetRenderDrawColor(renderer, 200, 100, 100, SDL_ALPHA_OPAQUE) != 0){
        return 1;
    }


    //Contour de la grille.
    if (SDL_RenderDrawRect(renderer, &contour) != 0){
        return 1;
    }
    if (SDL_RenderDrawRect(renderer, &contour2) != 0){
        return 1;
    }
    if (SDL_RenderDrawRect(renderer, &contour1) != 0){
        return 1;
    }

    //Dessin des lignes majeures.
    if (SDL_RenderDrawLine(renderer, MARGIN + contour.w/3, contour.y, MARGIN + contour.w/3, contour.y + contour.h) != 0){
        return 1;
    }
    if (SDL_RenderDrawLine(renderer, MARGIN + contour.w/3 + 1, contour.y, MARGIN + contour.w/3 + 1, contour.y + contour.h) != 0){
        return 1;
    }
    if (SDL_RenderDrawLine(renderer, MARGIN + 2*contour.w/3, contour.y, MARGIN + 2*contour.w/3, contour.y + contour.h) != 0){
        return 1;
    }
    if (SDL_RenderDrawLine(renderer, MARGIN + 2*contour.w/3 + 1, contour.y, MARGIN + 2*contour.w/3 + 1, contour.y + contour.h) != 0){
        return 1;
    }
    if (SDL_RenderDrawLine(renderer, contour.x , MARGIN + contour.h/3, contour.x + contour.w , MARGIN + contour.h/3) != 0){
        return 1;
    }
    if (SDL_RenderDrawLine(renderer, contour.x , MARGIN + contour.h/3 + 1, contour.x + contour.w , MARGIN + contour.h/3 + 1) != 0){
        return 1;
    }
    if (SDL_RenderDrawLine(renderer, contour.x , MARGIN + 2*contour.h/3, contour.x + contour.w, MARGIN + 2*contour.h/3) != 0){
        return 1;
    }
    if (SDL_RenderDrawLine(renderer, contour.x , MARGIN + 2*contour.h/3 + 1, contour.x + contour.w, MARGIN + 2*contour.h/3 + 1) != 0){
        return 1;
    }

    //Dessin des lignes mineures verticales.

    if (SDL_RenderDrawLine(renderer, MARGIN + contour.w/9, contour.y, MARGIN + contour.w/9, contour.y + contour.h) != 0){
        return 1;
    }
    if (SDL_RenderDrawLine(renderer, MARGIN + 2*contour.w/9, contour.y, MARGIN + 2*contour.w/9, contour.y + contour.h) != 0){
        return 1;
    }

    if (SDL_RenderDrawLine(renderer, MARGIN + 4*contour.w/9, contour.y, MARGIN + 4*contour.w/9, contour.y + contour.h) != 0){
        return 1;
    }
    if (SDL_RenderDrawLine(renderer, MARGIN + 5*contour.w/9, contour.y, MARGIN + 5*contour.w/9, contour.y + contour.h) != 0){
        return 1;
    }

    if (SDL_RenderDrawLine(renderer, MARGIN + 7*contour.w/9, contour.y, MARGIN + 7*contour.w/9, contour.y + contour.h) != 0){
        return 1;
    }
    if (SDL_RenderDrawLine(renderer, MARGIN + 8*contour.w/9, contour.y, MARGIN + 8*contour.w/9, contour.y + contour.h) != 0){
        return 1;
    }

    //Dessins des lignes mineures horizontales
    if (SDL_RenderDrawLine(renderer, contour.x , MARGIN + 1*contour.h/9, contour.x + contour.w, MARGIN + 1*contour.h/9) != 0){
        return 1;
    }
    if (SDL_RenderDrawLine(renderer, contour.x , MARGIN + 2*contour.h/9, contour.x + contour.w, MARGIN + 2*contour.h/9) != 0){
        return 1;
    }
    if (SDL_RenderDrawLine(renderer, contour.x , MARGIN + 4*contour.h/9, contour.x + contour.w, MARGIN + 4*contour.h/9) != 0){
        return 1;
    }
    if (SDL_RenderDrawLine(renderer, contour.x , MARGIN + 5*contour.h/9, contour.x + contour.w, MARGIN + 5*contour.h/9) != 0){
        return 1;
    }
    if (SDL_RenderDrawLine(renderer, contour.x , MARGIN + 7*contour.h/9, contour.x + contour.w, MARGIN + 7*contour.h/9) != 0){
        return 1;
    }
    if (SDL_RenderDrawLine(renderer, contour.x , MARGIN + 8*contour.h/9, contour.x + contour.w, MARGIN + 8*contour.h/9) != 0){
        return 1;
    }

    return 0 ;
}

int gamescreen (SDL_Window * window, SDL_Renderer * renderer){

    //SDL_Window * window = NULL ; //on garde la fenêtre de menu, pas besoin d'en créer une nouvelle
    //SDL_Renderer * renderer = NULL ;
    SDL_bool program_launched = SDL_TRUE ;
    SDL_Event event ;

    SDL_Rect contour = SDL_CreerRect(MARGIN, MARGIN, SCREEN_H - MARGIN*2, SCREEN_W - MARGIN*2);

    SDL_Rect grille[9][9];
    int i, j;

    SDL_RenderClear(renderer);

    //Initialise SDL pour l'aspect visuel.
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        SDL_ExitWithError("Initialisation SDL");
    }

    /* //Création de la fenêtre.
    window = SDL_CreateWindow("Morpion fractal", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_H, SCREEN_W, 0);
    if (window == NULL){
        SDL_ExitWithError("Création fenêtre échouée"); 
    } 

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Création rendu échouée"); 
    } */

    /*======================================= AFFICHAGE ===================================================*/
    if(SDL_AfficherGrilleVide(renderer, contour) != 0){
        SDL_ExitWithError("Affichage de la grille échouée");
    }

    SDL_RenderPresent(renderer);


    /*=================================== CREATION DES CARRES ================================================*/

    for (i = 0 ; i < 9 ; i++){
        for (j = 0 ; j < 9 ; j++){
            grille[i][j]=SDL_CreerRect(MARGIN + i * contour.w/9, MARGIN + j * contour.h/9,contour.w/9,contour.h/9);
        }
    }

    /*=================================== GESTION DES EVENEMENTS =============================================*/


    while(program_launched){ 
        
        //On attends un événement.
        while(SDL_PollEvent(&event)){ 

            switch(event.type){

                case SDL_MOUSEBUTTONDOWN :
                    if (SDL_ClickInButton(event.button.x, event.button.y, contour)){ //Si le joueur clique dans la grille.
                        for (i = 0 ; i < 9 ; i++){
                            for (j = 0 ; j < 9 ; j++){
                                if (SDL_ClickInButton(event.button.x, event.button.y,grille[i][j])){ //On checke dans quelle case il a joué.
                                    printf("Carré %d, %d\n", i, j);
                                    
                                }
                            }
                        }
                    }
                    continue;
                
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