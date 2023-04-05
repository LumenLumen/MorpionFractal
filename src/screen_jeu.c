#include "../lib/screens.h"
#include "../lib/morpion.h"
#include "../lib/sauvegarde.h"
/**
    \file screen_jeu.c
    \brief Programme qui gère toutes les fonctions relatives aux parties de tout type.
    \author Groupe morpion fractal
    \version 1
    \date 9 février 2023
*/

/**
    \fn int tour_de_jeu (SDL_Renderer * renderer, int grille_int[9][9], int morpion_int[3][3], SDL_Rect grille[9][9], SDL_Texture * croix, SDL_Texture * rond, int i, int j, int * xdc, int * ydc, int * joueur, option_t * options, int (*fonction) (int *, int(*)[9], int(*)[3], int *, int *, int, int))
    \brief Déroule le tour de jeu en appelant les fonctions nécessaires
    \param renderer le rendu pour afficher la grille
    \param grille_int la grille 9*9 qui représente la grille.
    \param morpion_int le morpion 3*3
    \param grille la grille 9*9 pour l'affichage des cases dans la grille
    \param croix la texture pour le symbole croix
    \param rond la texture pour le symbole rond
    \param i abscisse du coup joué
    \param j ordonné du coup joué
    \param xdc pointeur vers l'abscisse du précédent coup joué
    \param ydc pointeur vers l'ordonnée du précédent coup joué
    \param joueur pointeur vers le joueur à c'est le tour
    \param options les options de jeu
    \param fonction la fonction qui va vérifier si le coup (i, j) est valide.
    \return La fonction retourne -1 si le match est nul, 0 s'il n'y a aucun vainqueur, 1 si X gagne, 2 si O gagne, 3, 4 ou 5 si le coup joué n'est pas valide.
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
            if (vainqueur <= 0){

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
            return 3 ; 
            break ;
        case 4 :
            SDL_RenderFillRect(renderer, &boite_de_texte);
            SDL_TextInRect(renderer, boite_de_texte, "La case est déjà occupée.");
            return 4 ;
            break ;
        case 5 :
            SDL_RenderFillRect(renderer, &boite_de_texte);
            SDL_TextInRect(renderer, boite_de_texte, "Le carré est déjà complété.");
            return 5 ;
            break ;
        default : return 6 ;
        }

    return vainqueur;
}

/**
    \fn int gamescreen (SDL_Window * window, SDL_Renderer * renderer, int reload, option_t * options)
    \brief Cette fonction gère l'ecran de jeu en local et joueur contre machine, les événements et la fin de la partie. Elle lance si nécessaire une sauvegarde, et fait une sauvegarde si nécessaire.
    \param window La fenêtre d'affichage
    \param renderer le rendu d'affichage
    \param reload vaut 1 si on charge la sauvegarde automatique, 2 si on charge la sauvegarde manuelle, charge une nouvelle partie pour les autres valeurs.
    \param options options de jeu
    \return 0 si elle se termine correctement, autre valeur si recontre une erreur : 1 - erreur de chargement de sauvegarde ; 2 - erreur dans le chargement d'image ; 3 - erreur d'affichage de la grille ; 4 - options->vsia contient une valeur non reconnue (!=0,1,2,3,4). 
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
    int i, j, x, y;
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
        return 3;
    }

    SDL_TextInRect(renderer, boite_de_texte, "Début de la partie !");
    SDL_RenderPresent(renderer);

    /*=================================== GESTION DES EVENEMENTS =============================================*/

    while(program_launched){
        
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

                                    if (vainqueur == X || vainqueur == O || vainqueur == -1) program_launched = SDL_FALSE ;

                                    if (options->vsia && ! options->variante && program_launched == SDL_TRUE){
                                        SDL_Delay(200);
                                        do {
                                            switch (options->vsia){
                                                case 1 : ia_random(joueur, *xdc, *ydc, &x, &y, morpion_int, grille_int); break ;
                                                case 2 : ia_random_2(joueur, *xdc, *ydc, &x, &y, morpion_int, grille_int); break ;
                                                case 3 : ia_random_completionniste(joueur, *xdc, *ydc, &x, &y, morpion_int, grille_int); break ;
                                                case 4 : ia_eval_simple(joueur, *xdc, *ydc, &x, &y, morpion_int, grille_int); break ;
                                                default : return 4 ;
                                            }
                                            vainqueur = tour_de_jeu (renderer, grille_int, morpion_int, grille, croix, rond, x, y, xdc, ydc, &joueur, options, valideCase);
                                        } while (vainqueur >= 3);
                                        SDL_RenderPresent(renderer);
                                        if (vainqueur == X || vainqueur == O || vainqueur == -1) program_launched = SDL_FALSE ;
                                    }
                                    
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
                    return 0;
                    break ;

                default : break ;
            }
        }
    }

    //Annonce du vainqueur
    if (vainqueur == O) SDL_TextInRect(renderer, boite_de_texte, "Le vainqueur est O.");
    else if (vainqueur == -1){
        SDL_TextInRect(renderer, boite_de_texte, "Match nul !");
        SDL_RenderPresent(renderer);
        wait_a_click();
        SDL_RenderFillRect(renderer, &boite_de_texte);
        SDL_TextInRect(renderer, boite_de_texte, "Vous n'avez pas lu les règles ?");
        SDL_RenderPresent(renderer);
        wait_a_click();
        SDL_RenderFillRect(renderer, &boite_de_texte);
        SDL_TextInRect(renderer, boite_de_texte, "C'est interdit les égalités !!");
        SDL_RenderPresent(renderer);
        wait_a_click();
        SDL_RenderFillRect(renderer, &boite_de_texte);
        SDL_TextInRect(renderer, boite_de_texte, "Vous êtes nuls !");
        SDL_RenderPresent(renderer);
        wait_a_click();
        SDL_RenderFillRect(renderer, &boite_de_texte);
        SDL_TextInRect(renderer, boite_de_texte, "Puisque c'est comme ça, j'me tire !");
        SDL_RenderPresent(renderer);
        wait_a_click();
        free(xdc);
        free(ydc);
        return 0 ;
    }
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
                    return 0;
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

/**
    \fn int iavsia (SDL_Window * window, SDL_Renderer * renderer, option_t * options)
    \brief S'occupe de gérer les parties machine contre machine et de les afficher.
    \param window fenêtre d'affichage
    \param renderer rendu d'affichage
    \param options options de jeu
    \return renvoie 0 si elle se termine correctement, renvoie : 2 - erreur chargement image ; 3 - erreur affichage grille
*/
int iavsia (SDL_Window * window, SDL_Renderer * renderer, option_t * options){
    //On efface le rendu.
    SDL_RenderClear(renderer);

    SDL_Rect grille[9][9];
    SDL_Rect contour = SDL_CreerRect(MARGIN, MARGIN, SCREEN_H - MARGIN*2, SCREEN_W - MARGIN*2);
    SDL_Rect boite_de_texte = SDL_CreerRect(10, SCREEN_H, SCREEN_W, ESPACE_TEXTE);

    //Définition des textures.
    SDL_Texture * croix ;
    SDL_Texture * rond ;
    SDL_Surface * image ;

    //Définition des entiers.    
    int grille_int[N][N];
    int morpion_int[M][M];
    int x, y;
    int vainqueur = 0;

    int joueur = 1 ; //Tour du joueur ;
    int * xdc = malloc(sizeof(int)); //Ligne du dernier coup ;
    int * ydc = malloc(sizeof(int)); //Colonne du dernier coup ;

    (* xdc) = 1 ;
    (* ydc) = 1 ;
    init_grille(grille_int);
    init_morpion(morpion_int);

    options->variante = 0 ;

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

    for (x = 0 ; x < 9 ; x++){
        for (y = 0 ; y < 9 ; y++){
            grille[x][y]=SDL_CreerRect(MARGIN + x * contour.w/9, MARGIN + y * contour.h/9,contour.w/9,contour.h/9);
        }
    }

    if(SDL_MiseAJourRenderer(renderer, grille_int, morpion_int, grille, croix, rond, *xdc, *ydc, options) != 0){
        free(xdc); free(ydc);
        return 3;
    }

    SDL_TextInRect(renderer, boite_de_texte, "Cliquez pour avancer la partie.");
    SDL_RenderPresent(renderer);

    /*=================================== PARTIE =============================================*/

    while (morpiongagne(morpion_int) == 0){ //Tq la partie n'est pas finie.
        if (wait_a_click()){free(xdc); free(ydc); return 0 ;}
        do {
            ia_eval_simple(joueur, *xdc, *ydc, &x, &y, morpion_int, grille_int);
            vainqueur = tour_de_jeu (renderer, grille_int, morpion_int, grille, croix, rond, x, y, xdc, ydc, &joueur, options, valideCase);
        } while (vainqueur >= 3);
        SDL_RenderPresent(renderer);
    }

    //Annonce du vainqueur
    if (vainqueur == O) SDL_TextInRect(renderer, boite_de_texte, "Le vainqueur est O.");
    else if (vainqueur == -1){
        SDL_TextInRect(renderer, boite_de_texte, "Match nul !");
        SDL_RenderPresent(renderer);
        if (wait_a_click()){free(xdc); free(ydc); return 0 ;}
        SDL_RenderFillRect(renderer, &boite_de_texte);
        SDL_TextInRect(renderer, boite_de_texte, "Vous n'avez pas lu les règles ?");
        SDL_RenderPresent(renderer);
        if (wait_a_click()){free(xdc); free(ydc); return 0 ;}
        SDL_RenderFillRect(renderer, &boite_de_texte);
        SDL_TextInRect(renderer, boite_de_texte, "C'est interdit les égalités !!");
        SDL_RenderPresent(renderer);
        if (wait_a_click()){free(xdc); free(ydc); return 0 ;}
        SDL_RenderFillRect(renderer, &boite_de_texte);
        SDL_TextInRect(renderer, boite_de_texte, "Vous êtes nuls !");
        SDL_RenderPresent(renderer);
        if (wait_a_click()){free(xdc); free(ydc); return 0 ;}
        SDL_RenderFillRect(renderer, &boite_de_texte);
        SDL_TextInRect(renderer, boite_de_texte, "Puisque c'est comme ça, j'me tire !");
        SDL_RenderPresent(renderer);
        if (wait_a_click()){free(xdc); free(ydc); return 0 ;}
        free(xdc);
        free(ydc);
        return 0 ;
    }
    else SDL_TextInRect(renderer, boite_de_texte, "Le vainqueur est X.");
    SDL_RenderPresent(renderer);

    if (wait_a_click()){free(xdc); free(ydc); return 0 ;}

    //Libération de la mémoire
    free(xdc);
    free(ydc);
    options->vsia = 0 ;
    menuscreen(window, renderer, options);
    return 0 ;
    
}