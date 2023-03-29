#include "../lib/screens.h"
#include "../lib/morpion.h"
#include "../lib/sauvegarde.h"
/**
\file sreen_jeu.c
\brief programme ...
\author Groupe morpion fractal
\version 1
\date 9 février 2023
*/

int tour_de_jeu (SDL_Renderer * renderer, int grille_int[9][9], int morpion_int[3][3], SDL_Rect grille[9][9], SDL_Texture * croix, SDL_Texture * rond, int i, int j, int * xdc, int * ydc, int * joueur, option_t * options, int (*fonction) (int *, int(*)[9], int(*)[3], int *, int *, int, int)){
    
    int vainqueur = -1 ;
    SDL_Rect boite_de_texte = SDL_CreerRect(10, SCREEN_H, SCREEN_W, ESPACE_TEXTE);

    SDL_SetRenderDrawColor(renderer, options->r, options->g, options->b, SDL_ALPHA_OPAQUE);
    
    switch (fonction(joueur, grille_int, morpion_int, xdc, ydc, i, j)){
        case 0 :
            check_carre(grille_int, morpion_int, i, j);
            SDL_MiseAJourRenderer(renderer, grille_int, morpion_int, grille, croix, rond, i, j, options);

            //TEST SI FIN DE LA PARTIE
            vainqueur = morpiongagne(morpion_int);
            if (vainqueur == 0){

                //AFFICHAGE DU TEXTE
                if (*joueur == X) SDL_TextInRect(renderer, boite_de_texte, "C'est au tour de X.");
                else SDL_TextInRect(renderer, boite_de_texte, "C'est au tour de 0.");

                if(options->autosave && vainqueur == 0){
                    save("auto.txt",grille_int,morpion_int,*joueur,*xdc,*ydc, options->variante);
                }
            }
            return vainqueur ; //0 si partie non finie, sinon le num du vainqueur

            break;
        case 3 :
            SDL_RenderFillRect(renderer, &boite_de_texte);
            SDL_TextInRect(renderer, boite_de_texte, "Carré non valide.");
            break ;
        case 4 :
            SDL_RenderFillRect(renderer, &boite_de_texte);
            SDL_TextInRect(renderer, boite_de_texte, "La case est déjà occupée.");
            break ;
        case 5 :
            SDL_RenderFillRect(renderer, &boite_de_texte);
            SDL_TextInRect(renderer, boite_de_texte, "Le carré est déjà complété.");
            break ;
        default : return -1 ;
        }

    return vainqueur;
}

/**
\fn int gamescreen (SDL_Window * window, SDL_Renderer * renderer, int reload, option_t * options)
\brief Cette fonction gère l'ecran de jeu avec les options.

*/
int gamescreen (SDL_Window * window, SDL_Renderer * renderer, int reload, option_t * options){

    //On efface le rendu.
    SDL_RenderClear(renderer);

    //Déclaration des variables pour la gestion des événements.
    SDL_bool program_launched = SDL_TRUE ;
    SDL_Event event ;

    SDL_Rect grille[9][9];
    SDL_Rect contour = SDL_CreerRect(MARGIN, MARGIN, SCREEN_H - MARGIN*2, SCREEN_W - MARGIN*2);
    SDL_Rect sauv_rec = SDL_CreerRect(SCREEN_W*8/9, MARGIN+contour.h, MARGIN, MARGIN);
    SDL_Rect boite_de_texte = SDL_CreerRect(10, SCREEN_H, SCREEN_W, ESPACE_TEXTE);

    //Définition des textures.
    SDL_Texture * croix ;
    SDL_Texture * rond ;
    SDL_Surface * image ;

    //Définition des entiers.    
    int grille_int[N][N];
    int morpion_int[M][M];
    int i, j;
    int vainqueur = 0;

    int joueur = 1 ; //Tour du joueur ;
    int * xdc = malloc(sizeof(int)); //Ligne du dernier coup ;
    int * ydc = malloc(sizeof(int)); //Colonne du dernier coup ;


    if (reload == 1){ //si reload=1, on charge le fichier de sauvegarde
        if (load("auto.txt", grille_int, morpion_int, &joueur, xdc, ydc, &(options->variante)) == 0){
            free(xdc); free(ydc);
            return 1;
        }
    }
    else if (reload == 2){
        if (load("save.txt", grille_int, morpion_int, &joueur, xdc, ydc, &(options->variante)) == 0){
            free(xdc); free(ydc);
            return 1 ;
        }
    }
    else{ //sinon, on initialise une nouvelle grille
        (* xdc) = -1 ;
        (* ydc) = -1 ;
        init_grille(grille_int);
        init_morpion(morpion_int);
    }

    /*========================== CHARGEMENT DES IMAGES ===============================*/

    //Chargement de croix.
    image = IMG_Load(options->croiximg);
    if(!image){
        free(xdc); free(ydc);
        return 2;
    }

    croix = SDL_CreateTextureFromSurface(renderer, image);
    if (croix == NULL){
        free(xdc); free(ydc);
        return 2;
    }

    //Chargement de rond.
    image = IMG_Load(options->rondimg);
    if(!image){
        free(xdc); free(ydc);
        return 2;
    }

    rond = SDL_CreateTextureFromSurface(renderer, image);
    if (rond == NULL){
        free(xdc); free(ydc);
        return 2;
    }

    //On libère l'image.
    SDL_FreeSurface(image);

    /*==================================== AFFICHAGE GRILLE VIDE =================================================*/

    for (i = 0 ; i < 9 ; i++){
        for (j = 0 ; j < 9 ; j++){
            grille[i][j]=SDL_CreerRect(MARGIN + i * contour.w/9, MARGIN + j * contour.h/9,contour.w/9,contour.h/9);
        }
    }

    if(SDL_MiseAJourRenderer(renderer, grille_int, morpion_int, grille, croix, rond, *xdc, *ydc, options) != 0){
        free(xdc); free(ydc);
        return 2;
    }

    SDL_TextInRect(renderer, boite_de_texte, "Début de la partie !");
    SDL_RenderPresent(renderer);

    /*=================================== GESTION DES EVENEMENTS =============================================*/

    int cpt=0;

    while(program_launched){ 
        
        cpt=0;

        while(options->vsia==1 && joueur==2 && cpt<100){ //Si l'IA est activée
            ia_random_2(*xdc,*ydc,&i,&j,morpion_int,grille_int);
            if(options->variante) vainqueur = tour_de_jeu (renderer, grille_int, morpion_int, grille, croix, rond, i, j, xdc, ydc, &joueur, options, valideCase_var);
            else vainqueur = tour_de_jeu (renderer, grille_int, morpion_int, grille, croix, rond, i, j, xdc, ydc, &joueur, options, valideCase);
            if (vainqueur > 0) program_launched = SDL_FALSE ;
            SDL_RenderPresent(renderer);
            cpt++;
        }
        SDL_Delay(1000);
        
        //On attends un événement.
        while(SDL_PollEvent(&event)){ 

            switch(event.type){

                case SDL_MOUSEBUTTONDOWN :
                    if (SDL_ClickInButton(event.button.y, event.button.x, contour)){ //Si le joueur clique dans la grille.

                        for (i = 0 ; i < 9 ; i++){
                            for (j = 0 ; j < 9 ; j++){
                                if (SDL_ClickInButton(event.button.y, event.button.x,grille[i][j])){ //On checke dans quelle case il a joué.


                                    if (options->variante){ // Si variante
                                        vainqueur = tour_de_jeu (renderer, grille_int, morpion_int, grille, croix, rond, i, j, xdc, ydc, &joueur, options, valideCase_var);
                                    }
                                    else { //Sinon
                                        vainqueur = tour_de_jeu (renderer, grille_int, morpion_int, grille, croix, rond, i, j, xdc, ydc, &joueur, options, valideCase);
                                    }
                                    if (vainqueur > 0) program_launched = SDL_FALSE ;
                                    
                                }
                            }
                        }

                        SDL_RenderPresent(renderer);
                    }
                    if (SDL_ClickInButton(event.button.x, event.button.y, sauv_rec)){ //SI le joueur clique sur le bouton de sauvegarde
                        SDL_TextInRect(renderer, boite_de_texte, "Partie sauvegardée !");
                        save("save.txt", grille_int, morpion_int, joueur, *xdc, *ydc, options->variante); //sauvegarde
                    }
                    continue;
                
                //La croix en haut à droite est pressée.
                case SDL_QUIT : 
                    free(xdc);
                    free(ydc);
                    return 1;
                    break ;

                default : break ;
            }
        }
    }

    //Annonce du vainqueur
    if (vainqueur == O) SDL_TextInRect(renderer, boite_de_texte, "Le vainqueur est O.");
    else SDL_TextInRect(renderer, boite_de_texte, "Le vainqueur est X.");
    SDL_RenderPresent(renderer);

    /*============ FIN DE LA PARTIE ================*/
    program_launched = SDL_TRUE;
    while(program_launched){ 
        
        //On attends un événement.
        while(SDL_PollEvent(&event)){ 

            switch(event.type){
                case SDL_MOUSEBUTTONDOWN :
                    menuscreen(window, renderer, options);
                    program_launched = SDL_FALSE ;
                    break ;                
                //La croix en haut à droite est pressée.
                case SDL_QUIT : 
                    free(xdc);
                    free(ydc);
                    return 1;
                    break ;

                default : break ;
            }
        }
    }

    //Libération de la mémoire
    free(xdc);
    free(ydc);
    return 0 ;
    
}