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

/**
\fn int gamescreen (SDL_Window * window, SDL_Renderer * renderer, int reload, option_t * options)
\brief Cette fonction gère l'ecran de jeu avec les options.

*/
int gamescreen (SDL_Window * window, SDL_Renderer * renderer, int reload, option_t * options){

    //On efface le rendu.
    SDL_RenderClear(renderer);

    ///Déclaration des variables pour la gestion des événements.
    SDL_bool program_launched = SDL_TRUE ;
    SDL_Event event ;

    SDL_Rect grille[9][9];
    SDL_Rect contour = SDL_CreerRect(MARGIN, MARGIN, SCREEN_H - MARGIN*2, SCREEN_W - MARGIN*2);
    SDL_Rect sauv_rec = SDL_CreerRect(SCREEN_W*8/9, MARGIN+contour.h, MARGIN, MARGIN);

    ///Définition des textures.
    SDL_Texture * croix ;
    SDL_Texture * rond ;
    SDL_Surface * image ;
    TTF_Font *police = NULL;

    ///Définition des entiers.    
    int grille_int[N][N];
    int morpion_int[M][M];
    int i, j;
    int vainqueur ;

    int joueur = 1 ; //Tour du joueur ;
    int * xdc = malloc(sizeof(int)); //Ligne du dernier coup ;
    int * ydc = malloc(sizeof(int)); //Colonne du dernier coup ;


    if (reload){ ///si reload=1, on charge le fichier de sauvegarde
        load("toto.txt", grille_int, morpion_int, &joueur, xdc, ydc);
    }
    else{ ///sinon, on initialise une nouvelle grille
        (* xdc) = -1 ;
        (* ydc) = -1 ;
        init_grille(grille_int);
        init_morpion(morpion_int);
    }

    /*========================== CHARGEMENT DES IMAGES ===============================*/

    ///On charge l'image pour le joueur de la croix.
    image = IMG_Load(options->croiximg);
    if(!image){
        return 2;
    }

    croix = SDL_CreateTextureFromSurface(renderer, image);
    if (croix == NULL){
        return 2;
    }

    /// On charge l'image pour le joueur du rond.
    image = IMG_Load(options->rondimg);
    if(!image){
        return 2;
    }

    rond = SDL_CreateTextureFromSurface(renderer, image);
    if (rond == NULL){
        return 2;
    }

    //On libère l'image.
    SDL_FreeSurface(image);

    /* ================================ CHARGEMENT DU TEXTE (POLICE + COULEUR) ==============================*/

    if( (police = TTF_OpenFont("src/font/Coder'sCrux.ttf", 50)) == NULL){
        return 2;
    }

    /*==================================== AFFICHAGE GRILLE VIDE =================================================*/

    for (i = 0 ; i < 9 ; i++){
        for (j = 0 ; j < 9 ; j++){
            grille[i][j]=SDL_CreerRect(MARGIN + i * contour.w/9, MARGIN + j * contour.h/9,contour.w/9,contour.h/9);
        }
    }

    if(SDL_MiseAJourRenderer(renderer, grille_int, morpion_int, grille, croix, rond, *xdc, *ydc, options->variante) != 0){
        return 2;
    }

    SDL_AfficherTexte(renderer, police, "Début de la partie !");

    /*=================================== GESTION DES EVENEMENTS =============================================*/

    while(program_launched){ 
        
        //On attends un événement.
        while(SDL_PollEvent(&event)){ 

            switch(event.type){

                case SDL_MOUSEBUTTONDOWN :
                    if (SDL_ClickInButton(event.button.y, event.button.x, contour)){ ///Si le joueur clique dans la grille.

                        for (i = 0 ; i < 9 ; i++){
                            for (j = 0 ; j < 9 ; j++){
                                if (SDL_ClickInButton(event.button.y, event.button.x,grille[i][j])){ ///On checke dans quelle case il a joué.


                                    if (options->variante){
                                        switch (valideCase_var(&joueur, grille_int, morpion_int, xdc, ydc, i, j)){
                                            case 0 :
                                                check_carre(grille_int, morpion_int, i, j);
                                                SDL_MiseAJourRenderer(renderer, grille_int, morpion_int, grille, croix, rond, i, j, options->variante);

                                                ///TEST SI FIN DE LA PARTIE
                                                vainqueur = morpiongagne(morpion_int);
                                                if (vainqueur != 0) program_launched = SDL_FALSE ;

                                                ///AFFICHAGE DU TEXTE
                                                if (joueur == X) SDL_AfficherTexte(renderer, police, "C'est au tour de X.");
                                                else SDL_AfficherTexte(renderer, police, "C'est au tour de O.");

                                                if(options->autosave && vainqueur == 0){
                                                    save("auto.txt",grille_int,morpion_int,joueur,*xdc,*ydc);
                                                }

                                                break;
                                            case 3 :
                                                SDL_AfficherTexte(renderer, police, "Carré non valide.");
                                                break ;
                                            case 4 :
                                                SDL_AfficherTexte(renderer, police, "La case est déjà occupée.");
                                                break ;
                                            default : program_launched = SDL_FALSE ;
                                        }
                                    }

                                    else {
                                        switch (valideCase(&joueur, grille_int, morpion_int, xdc, ydc, i, j)){
                                            case 0 :
                                                check_carre(grille_int, morpion_int, i, j);
                                                SDL_MiseAJourRenderer(renderer, grille_int, morpion_int, grille, croix, rond, i, j, options->variante);

                                                //TEST SI FIN DE LA PARTIE
                                                vainqueur = morpiongagne(morpion_int);
                                                if (vainqueur != 0) program_launched = SDL_FALSE ;

                                                //AFFICHAGE DU TEXTE
                                                if (joueur == X) SDL_AfficherTexte(renderer, police, "C'est au tour de X.");
                                                else SDL_AfficherTexte(renderer, police, "C'est au tour de O.");

                                                if(options->autosave && vainqueur == 0){
                                                    save("auto.txt",grille_int,morpion_int,joueur,*xdc,*ydc);
                                                }

                                                break;
                                            case 3 :
                                                SDL_AfficherTexte(renderer, police, "Carré non valide.");
                                                break ;
                                            case 4 :
                                                SDL_AfficherTexte(renderer, police, "La case est déjà occupée.");
                                                break ;
                                            case 5 :
                                                SDL_AfficherTexte(renderer, police, "Le carré est déjà complété.");
                                                break ;
                                            default : program_launched = SDL_FALSE ;
                                        }
                                    }

                                    
                                }
                            }
                        }

                    }
                    if (SDL_ClickInButton(event.button.x, event.button.y, sauv_rec)){ ///SI le joueur clique sur le bouton de sauvegarde
                        SDL_AfficherTexte(renderer, police, "Partie sauvegardée !");
                        save("toto.txt",grille_int,morpion_int,joueur,*xdc,*ydc); /// On sauvegarde la partie.
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

    /// On annonce le vainqueur.
    if (vainqueur == O) SDL_AfficherTexte(renderer, police, "Le vainqueur est O.");
    else SDL_AfficherTexte(renderer, police, "Le vainqueur est X.");

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

    /// On libère la mémoire à la fin de la fonction.
    free(xdc);
    free(ydc);
    /**
    \return 0
    */
    return 0 ;
    
}