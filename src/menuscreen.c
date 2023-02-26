#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include "../lib/screens.h"
#include "../lib/morpion.h"

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

//Affiche la grille.
int SDL_AfficherGrilleVide(SDL_Renderer * renderer, SDL_Rect contour){

    SDL_Rect background = SDL_CreerRect(0, 0, SCREEN_W, SCREEN_H);
    SDL_Rect contour1 = SDL_CreerRect(contour.x - 1, contour.y - 1, contour.w, contour.h);
    SDL_Rect contour2 = SDL_CreerRect(contour.x + 1, contour.y + 1, contour.w, contour.h);

    //Fond
    if (SDL_SetRenderDrawColor(renderer, 187, 238, 238, SDL_ALPHA_OPAQUE) != 0){
        return 1;
    }
    
    if (SDL_RenderFillRect(renderer, &background) != 0){
        return 1;
    }

    //Couleur
    if (SDL_SetRenderDrawColor(renderer, 80, 200, 190, SDL_ALPHA_OPAQUE) != 0){
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

//Prends en paramètre la case, le rendu et le symbole à afficher.
int SDL_ajouter_symbole_dans_case (SDL_Rect casegrille, SDL_Renderer * renderer, SDL_Texture * croix){
    SDL_Rect temp = casegrille ;
    SDL_QueryTexture(croix, NULL, NULL, &(casegrille.w), &(casegrille.h));
    casegrille = temp ;
    SDL_RenderCopy(renderer, croix, NULL, &casegrille);
    SDL_RenderPresent(renderer);
    return 0;
}

int SDL_AfficherTexte (SDL_Renderer * renderer, TTF_Font * police, SDL_Color couleur, char * chaine/*, SDL_Rect boite_de_texte*/){

    SDL_Rect boite_de_texte = SDL_CreerRect(0, SCREEN_H, SCREEN_W, ESPACE_TEXTE);

    //Fond
    printf("Création du fond | ");
    if (SDL_SetRenderDrawColor(renderer, 187, 238, 238, SDL_ALPHA_OPAQUE) != 0){
        return 1;
    }
    
    if (SDL_RenderFillRect(renderer, &boite_de_texte) != 0){
        return 1;
    }

    //Texte

    printf("Création texte | ");
    SDL_Surface * texte = TTF_RenderUTF8_Blended (police, chaine, couleur);
    if(!texte) return 1;

    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_Texture * texte_tex = SDL_CreateTextureFromSurface(renderer,texte);

    if(!texte_tex) return 2;
    SDL_FreeSurface(texte);

    if (SDL_QueryTexture(texte_tex, NULL, NULL, &(boite_de_texte.w), &(boite_de_texte.h))){
        return 3;
    }
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderCopy(renderer, texte_tex, NULL, &boite_de_texte);

    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texte_tex);
    return 0 ;
}

/*Prends en paramètre le joueur dont c'est le tour, la grille 9*9, le morpion 3*3, les coordonnées de la dernière case jouée, et les coordonnées de la case jouée
Retourne -1 si le coup n'est pas valide, 0 sinon.*/
int valideCase (int * joueur, int grille[N][N], int morpion[M][M], int * xdc, int * ydc, int x, int y){

    int carre = -1 ;

    if (*xdc == -1){ //C'est le premier tour.
        carre =  4 ;
    }
    //Si le joueur est renvoyé sur une case déjà gagnée par un joueur.
    else if ( morpion[(*xdc)%M][(*ydc)%M] != 0 ){
        carre = 9;
    }
    else {
        carre = (*xdc)%M * 3 + (*ydc)%M ;
    }

    //printf("Contenu de la case visée : %i en x=%i et y=%i",grille[x][y],x,y);
    if((coog_to_carr(x,y) != carre) && (carre != 9)){
        printf("Carré non valide.\n");
    }
    else if (grille[x][y] != 0){
        printf("La case est déjà occupée.\n") ;
    }
    else if (carre == 9 && morpion[x/M][y/M] != 0){
        printf("Le carré est déjà complété.\n");
    }
    else {
        *xdc = x ;
        *ydc = y ;//Les coordonnées sont valides et deviennent le nouveau dernier coup joué.
        grille[x][y] = *joueur ; //On ajoute la valeur du joueur à la grille à l'endroit joué.
        //Si le joueur du coup est X, alors on passe au tour de O, sinon c'est le tour de X.
        if (*joueur == X) *joueur = O ;
        else *joueur = X ;
        return 0 ; 
    }

    return -1 ;
}