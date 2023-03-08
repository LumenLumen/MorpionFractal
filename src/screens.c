#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include "../lib/screens.h"
#include "../lib/morpion.h"
/**
\file screens.c
\brief programme ...
\author Groupe morpion fractal
\version 1
\date 9 février 2023
*/

/**
\fn void SDL_ExitWithError(const char * message)
\brief En cas d'erreur, la fonction affiche l'erreur avec le message passé en paramètre.
\return EXIT_FAILURE
*/

//En cas d'erreur, la fonction affiche l'erreur avec le message passé en paramètre
void SDL_ExitWithError(const char * message){
    SDL_Log("Erreur : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

/**
\fn SDL_Rect SDL_CreerRect(int x, int y, int w, int h){
\brief Initialise un rectangle avec les valeurs passées en paramètre
\return rectangle

*/

//Initialise un rectangle avec les valeurs passées en paramètre
SDL_Rect SDL_CreerRect(int x, int y, int w, int h){
    SDL_Rect rectangle;
    rectangle.x = x ;//Coordonnées x de l'angle haut gauche
    rectangle.y = y ;//Corddonnées y de l'angle haut gauche 
    rectangle.w = w ;//Longueur du rectangle
    rectangle.h = h ;//Hauteur
    return rectangle ;
}
/**
\fn int SDL_ClickInButton(int mousex, int mousey, SDL_Rect button)
\brief Prend en paramètre les coordonnés d'un clic et un rectangle.
\brief Renvoie vrai si le click est dans le rect, non sinon.
\return ((mousex >= button.x && mousex <= button.x + button.w) && (mousey >= button.y && mousey <= button.y + button.h))
*/
int SDL_ClickInButton(int mousex, int mousey, SDL_Rect button){
    return ((mousex >= button.x && mousex <= button.x + button.w) && (mousey >= button.y && mousey <= button.y + button.h));
}
/**
\fn SDL_AfficherGrilleVide(SDL_Renderer * renderer, SDL_Rect contour)
\brief fonction qui affiche la grille et definie sa couleur.
\return on retourne 0 si on réussi sinon 1.
*/
//Affiche la grille.
int SDL_AfficherGrilleVide(SDL_Renderer * renderer, SDL_Rect contour){

    SDL_Rect contour1 = SDL_CreerRect(contour.x - 1, contour.y - 1, contour.w, contour.h);
    SDL_Rect contour2 = SDL_CreerRect(contour.x + 1, contour.y + 1, contour.w, contour.h);

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
/**
\fn SDL_ajouter_symbole_dans_case (SDL_Rect casegrille, SDL_Renderer * renderer, SDL_Texture * croix)
\brief fonction qui prends en paramètre la case, le rendu et le symbole à afficher pour ajouter un symbole dans la grille.
\return 0
*/
//Prends en paramètre la case, le rendu et le symbole à afficher.
int SDL_ajouter_symbole_dans_case (SDL_Rect casegrille, SDL_Renderer * renderer, SDL_Texture * croix){
    SDL_Rect temp = casegrille ;
    SDL_QueryTexture(croix, NULL, NULL, &(casegrille.w), &(casegrille.h));
    casegrille = temp ;
    SDL_RenderCopy(renderer, croix, NULL, &casegrille);
    return 0;
}
/**
\fn SDL_AfficherTexte (SDL_Renderer * renderer, TTF_Font * police, SDL_Color couleur, char * chaine)
\brief affiche du texte en dessous de la grille lors de la partie.
\return un entier
*/
int SDL_AfficherTexte (SDL_Renderer * renderer, TTF_Font * police, char * chaine){

    SDL_Rect boite_de_texte = SDL_CreerRect(0, SCREEN_H, SCREEN_W, ESPACE_TEXTE);
    SDL_Color couleur = {37, 47, 61};

    //Fond
    if (SDL_SetRenderDrawColor(renderer, 187, 238, 238, SDL_ALPHA_OPAQUE) != 0){
        return 1;
    }
    
    if (SDL_RenderFillRect(renderer, &boite_de_texte) != 0){
        return 1;
    }

    //Texte
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


/**
\fn int SDL_MiseAJourRenderer (SDL_Renderer * renderer, int grille_int[N][N], int morpion_int[M][M], SDL_Rect grille[N][N], SDL_Texture * croix, SDL_Texture * rond, int xdc, int ydc, int var)
\brief On initialise la grille et met en surbrillance la case dans laquelle on va jouer.
*/
int SDL_MiseAJourRenderer (SDL_Renderer * renderer, int grille_int[N][N], int morpion_int[M][M], SDL_Rect grille[N][N], SDL_Texture * croix, SDL_Texture * rond, int xdc, int ydc, int var){

    //Ces valeurs existent dans le programme principal mais je ne sais pas s'il vaut mieux ou pas les passer en paramètre au risque d'alourdir l'appel.
    SDL_Rect contour = SDL_CreerRect(MARGIN, MARGIN, SCREEN_H - MARGIN*2, SCREEN_W - MARGIN*2);
    SDL_Rect sauv_rec = SDL_CreerRect(SCREEN_W*8/9, MARGIN+contour.h, MARGIN, MARGIN);
    SDL_Rect background = SDL_CreerRect(0, 0, SCREEN_W, SCREEN_H + ESPACE_TEXTE);

    SDL_Rect morpion[3][3];

    SDL_Texture * sauv ;
    SDL_Surface * image ;

    int i, j, x, y ;

    ///Initialisation de la grilles de rectangle.
    for (i = 0 ; i < 3 ; i++){
        for (j = 0 ; j < 3 ; j++){
            morpion[i][j]=SDL_CreerRect(MARGIN + i * contour.w/3, MARGIN + j * contour.h/3,contour.w/3,contour.h/3);
        }
    }

    SDL_RenderClear(renderer);

    //Affichage du fond.
    if (SDL_SetRenderDrawColor(renderer, 187, 238, 238, SDL_ALPHA_OPAQUE) != 0){
        return 1;
    }
    
    if (SDL_RenderFillRect(renderer, &background) != 0){
        return 1;
    }

    ///Affichage du prochain rectangle où jouer.
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    if (SDL_SetRenderDrawColor(renderer, 252, 237, 194, 100) != 0){
        return 1;
    }
        
    predict_rect(xdc, ydc, &x, &y);

    if (var == 0){ //Sans la variante 
        if (morpion_int[x][y] == 0 && carre_plein(grille_int, x*M, y*M) == 0){
            if (SDL_RenderFillRect(renderer, &morpion[y][x]) != 0){
                return 1;
            }
        }
        else{ //La case est déjà remplie et on ne peut plus y jouer.
            for (i = 0 ; i < M ; i++){
                for (j = 0 ; j < M ; j++){
                        if (morpion_int[i][j] == 0 && carre_plein(grille_int, i*M, j*M) == 0){
                            if (SDL_RenderFillRect(renderer, &morpion[j][i]) != 0){
                                return 1;
                            }
                        }
                }
            }
        }
    }
    else{ ///Variante : La case est déjà remplie et on ne peut plus y jouer.
        if (carre_plein(grille_int, x*M, y*M) == 0){
            if (SDL_RenderFillRect(renderer, &morpion[y][x]) != 0){
                return 1;
            }
        }
        else{ //La case est déjà remplie et on ne peut plus y jouer.
            for (i = 0 ; i < M ; i++){
                for (j = 0 ; j < M ; j++){
                        if (carre_plein(grille_int, i*M, j*M) == 0){
                            if (SDL_RenderFillRect(renderer, &morpion[j][i]) != 0){
                                return 1;
                            }
                        }
                }
            }
        }
    }

    if (var){ ///Variante : On affiche les carrés pris sous la grille.
        for (i = 0 ; i < M ; i++){
            for (j = 0 ; j < M ; j++){
                    if (morpion_int[i][j] == X) SDL_ajouter_symbole_dans_case(morpion[j][i], renderer, croix);
                    else if (morpion_int[i][j] == O) SDL_ajouter_symbole_dans_case(morpion[j][i], renderer, rond);
            }
        }
    }

    ///Affichage de la grille
    SDL_AfficherGrilleVide(renderer, contour);

    for (i=0 ; i<N ; i++){
        for (j=0 ; j<N ; j++){
            if(grille_int[j][i]==X) SDL_ajouter_symbole_dans_case(grille[i][j],renderer,croix);
            else if(grille_int[j][i]==O) SDL_ajouter_symbole_dans_case(grille[i][j],renderer,rond);
        }
    }
    
    if (var == 0){ //Pas de variante.
        for (i = 0 ; i < M ; i++){
            for (j = 0 ; j < M ; j++){
                    if (morpion_int[i][j] == X) SDL_ajouter_symbole_dans_case(morpion[j][i], renderer, croix);
                    else if (morpion_int[i][j] == O) SDL_ajouter_symbole_dans_case(morpion[j][i], renderer, rond);
            }
        }
    }

    ///Chargement de la disquette de sauvegarde.
    image = IMG_Load("./src/img/sauv.png");
    if(!image){
        return 1;
    }
    sauv = SDL_CreateTextureFromSurface(renderer, image);
    if (rond == NULL){
        return 1;
    }
    SDL_FreeSurface(image);
    SDL_ajouter_symbole_dans_case(sauv_rec,renderer,sauv);

    SDL_RenderPresent(renderer);
    return 0;

    /**
    \return 0
    */
}