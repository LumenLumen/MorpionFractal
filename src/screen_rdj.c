#include "../lib/screens.h"
#include "../lib/morpion.h"
#include "../lib/sauvegarde.h"

int wait_a_click (){
        SDL_bool program_launched = SDL_TRUE ;
        SDL_Event event ;
        while(program_launched){ 
            while(SDL_PollEvent(&event)){ 
                switch(event.type){
                    case SDL_MOUSEBUTTONDOWN :
                        program_launched = SDL_FALSE ;
                        break;
                    case SDL_QUIT : 
                        return 1;
                }
            }
        }
        return 0;
}

int regles_du_jeu (SDL_Window * window, SDL_Renderer * renderer, option_t * options){
    //Déclaration des variables pour la gestion des événements.
    SDL_bool program_launched = SDL_TRUE ;
    SDL_Event event ;

    SDL_Rect grille[9][9];
    SDL_Rect contour = SDL_CreerRect(MARGIN, MARGIN, SCREEN_H - MARGIN*2, SCREEN_W - MARGIN*2);
    SDL_Rect sauv_rec = SDL_CreerRect(SCREEN_W*8/9, MARGIN+contour.h, MARGIN, MARGIN);
    SDL_Rect boite_de_texte_l1 = SDL_CreerRect(10, SCREEN_H, SCREEN_W, ESPACE_TEXTE);
    SDL_Rect boite_de_texte_l2 = SDL_CreerRect(10, SCREEN_H + 50, SCREEN_W, ESPACE_TEXTE);
    SDL_Rect boite_de_texte_l3 = SDL_CreerRect(10, SCREEN_H + 100, SCREEN_W, ESPACE_TEXTE);
    SDL_Rect boite_de_texte_oui = SDL_CreerRect(600, SCREEN_H + 100, 50, 50);
    SDL_Rect boite_de_texte_non = SDL_CreerRect(700, SCREEN_H + 100, 50, 50);

    //Définition des textures.
    SDL_Texture * croix ;
    SDL_Texture * rond ;
    SDL_Surface * image ;

    //Définition des entiers.   
    int repeat = 0 ; 
    int grille_int[N][N];
    int morpion_int[M][M];
    int i, j;
    int vainqueur = 0;

    int joueur = 1 ; //Tour du joueur ;
    int * xdc = malloc(sizeof(int)) ; //Ligne du dernier coup ;
    int * ydc = malloc(sizeof(int)); //Colonne du dernier coup ;

    //On efface le rendu.
    SDL_RenderClear(renderer);

    (* xdc) = -1 ;
    (* ydc) = -1 ;
    init_grille(grille_int);
    init_morpion(morpion_int);

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

    /* ============================= DEBUT DU TUTO ============================== */

    SDL_SetRenderDrawColor(renderer, options->r, options->g, options->b, SDL_ALPHA_OPAQUE);

    SDL_TextInRect(renderer, boite_de_texte_l1, "Bienvenue dans les règles du jeu !");
    SDL_RenderPresent(renderer);

    if (wait_a_click()){free(xdc); free(ydc); return 0 ;}

    SDL_RenderFillRect(renderer, &boite_de_texte_l1);
    SDL_TextInRect(renderer, boite_de_texte_l1, "Je vais vous apprendre à jouer au");
    SDL_TextInRect(renderer, boite_de_texte_l2, "formidable jeu qu'est le morpion fractal !");
    
    SDL_RenderPresent(renderer);

    if (wait_a_click()){free(xdc); free(ydc); return 0 ;}

    do {
        if (repeat){
            SDL_RenderFillRect(renderer, &boite_de_texte_l1);
            SDL_TextInRect(renderer, boite_de_texte_l1, "Je répète alors !");
            SDL_TextInRect(renderer, boite_de_texte_l2, "Ecoute bien, mémoire de lombric !");
            SDL_RenderPresent(renderer);
            if (wait_a_click()){free(xdc); free(ydc); return 0 ;}
        }

        SDL_RenderFillRect(renderer, &boite_de_texte_l1);
        SDL_TextInRect(renderer, boite_de_texte_l1, "Tout d'abord, le jeu se joue à deux");
        SDL_TextInRect(renderer, boite_de_texte_l2, "joueurs. Vous pouvez inviter un ami");
        SDL_TextInRect(renderer, boite_de_texte_l3, "ou affronter votre ordinateur.");
        SDL_RenderPresent(renderer);

        if (wait_a_click()){free(xdc); free(ydc); return 0 ;}

        SDL_RenderFillRect(renderer, &boite_de_texte_l1);
        SDL_TextInRect(renderer, boite_de_texte_l1, "Comme au morpion, il y a donc X et O.");
        SDL_TextInRect(renderer, boite_de_texte_l2, "Des apparences différentes sont");
        SDL_TextInRect(renderer, boite_de_texte_l3, "disponibles dans les options.");
        SDL_RenderPresent(renderer);

        if (wait_a_click()){free(xdc); free(ydc); return 0 ;}

        SDL_RenderFillRect(renderer, &boite_de_texte_l1);
        SDL_TextInRect(renderer, boite_de_texte_l1, "Le but du jeu est de gagner !");
        SDL_TextInRect(renderer, boite_de_texte_l2, "C'est interdit de faire une égalité");
        SDL_TextInRect(renderer, boite_de_texte_l3, "car ce n'est pas prévu dans le code.");
        SDL_RenderPresent(renderer);

        if (wait_a_click()){free(xdc); free(ydc); return 0 ;}

        SDL_RenderFillRect(renderer, &boite_de_texte_l1);
        SDL_TextInRect(renderer, boite_de_texte_l1, "Ça va jusque là ?");
        SDL_TextInRect(renderer, boite_de_texte_l2, "Si non, je repète, face de mollusque.");
        SDL_TextInRect(renderer, boite_de_texte_oui, "Oui");
        SDL_TextInRect(renderer, boite_de_texte_non, "Non");
        SDL_RenderPresent(renderer);

        program_launched = SDL_TRUE ;
        while(program_launched){ 
            
            //On attends un événement.
            while(SDL_PollEvent(&event)){ 

                switch(event.type){

                    case SDL_MOUSEBUTTONDOWN :
                        if (SDL_ClickInButton(event.button.x, event.button.y, boite_de_texte_oui)){ 
                            repeat = 0 ;
                            program_launched = SDL_FALSE ;
                        }
                        else if (SDL_ClickInButton(event.button.x, event.button.y, boite_de_texte_non)){
                            repeat = 1 ;
                            program_launched = SDL_FALSE ;
                        }
                        break;
                    case SDL_QUIT : 
                        free(xdc);
                        free(ydc);
                        return 1;
                        break ;
                }
            }
        }
    }while (repeat);

    SDL_RenderFillRect(renderer, &boite_de_texte_l1);
    SDL_TextInRect(renderer, boite_de_texte_l1, "Très bien ! Passons à la pratique !");  
    SDL_RenderPresent(renderer);

    if (wait_a_click()){free(xdc); free(ydc); return 0 ;}

    do {
        if (repeat){
            init_grille(grille_int);
            init_morpion(morpion_int);
            SDL_MiseAJourRenderer(renderer, grille_int, morpion_int, grille, croix, rond, 4, 4, options);
            SDL_TextInRect(renderer, boite_de_texte_l1, "On est reparti alors !");
            SDL_TextInRect(renderer, boite_de_texte_l2, "C'est pourtant simple...");
            SDL_RenderPresent(renderer);
            if (wait_a_click()){free(xdc); free(ydc); return 0 ;}
        }
        SDL_RenderFillRect(renderer, &boite_de_texte_l1);
        SDL_TextInRect(renderer, boite_de_texte_l1, "Le premier joueur est X.");
        SDL_TextInRect(renderer, boite_de_texte_l2, "Le premier coup se joue dans");
        SDL_TextInRect(renderer, boite_de_texte_l3, "le carré central.");
        SDL_RenderPresent(renderer);

        if (wait_a_click()){free(xdc); free(ydc); return 0 ;}

        SDL_RenderFillRect(renderer, &boite_de_texte_l1);
        grille_int[3][5] = X ;
        SDL_MiseAJourRenderer(renderer, grille_int, morpion_int, grille, croix, rond, 3, 5, options);
        SDL_TextInRect(renderer, boite_de_texte_l1, "Imaginons que X joue dans la case en haut");
        SDL_TextInRect(renderer, boite_de_texte_l2, "à droite. Alors O devra jouer dans le");
        SDL_TextInRect(renderer, boite_de_texte_l3, "carré en haut à droite.");
        SDL_RenderPresent(renderer);

        if (wait_a_click()){free(xdc); free(ydc); return 0 ;}

        SDL_RenderFillRect(renderer, &boite_de_texte_l1);
        SDL_TextInRect(renderer, boite_de_texte_l1, "C'est alors au tour de O.");
        SDL_TextInRect(renderer, boite_de_texte_l2, "O joue dans n'importe quelle case");
        SDL_TextInRect(renderer, boite_de_texte_l3, "affichée en surbrillance.");
        SDL_RenderPresent(renderer);

        if (wait_a_click()){free(xdc); free(ydc); return 0 ;}

        grille_int[1][7] = O ;
        SDL_MiseAJourRenderer(renderer, grille_int, morpion_int, grille, croix, rond, 1, 7, options);
        SDL_TextInRect(renderer, boite_de_texte_l1, "O joue dans la case centrale.");
        SDL_TextInRect(renderer, boite_de_texte_l2, "X sera alors contraint de rejouer");
        SDL_TextInRect(renderer, boite_de_texte_l3, "dans le morpion central.");
        SDL_RenderPresent(renderer);

        if (wait_a_click()){free(xdc); free(ydc); return 0 ;}

        grille_int[4][4] = X ;
        SDL_MiseAJourRenderer(renderer, grille_int, morpion_int, grille, croix, rond, 4, 4, options);
        SDL_TextInRect(renderer, boite_de_texte_l1, "X joue dans la case centrale.");
        SDL_TextInRect(renderer, boite_de_texte_l2, "O sera alors contraint de rejouer lui");
        SDL_TextInRect(renderer, boite_de_texte_l3, "aussi dans le morpion central.");
        SDL_RenderPresent(renderer);

        if (wait_a_click()){free(xdc); free(ydc); return 0 ;}

        grille_int[5][4] = O ;
        SDL_MiseAJourRenderer(renderer, grille_int, morpion_int, grille, croix, rond, 5, 4, options);
        SDL_TextInRect(renderer, boite_de_texte_l1, "La partie continue...");
        SDL_RenderPresent(renderer);

        if (wait_a_click()){free(xdc); free(ydc); return 0 ;}

        grille_int[8][4] = X ;
        SDL_MiseAJourRenderer(renderer, grille_int, morpion_int, grille, croix, rond, 8, 4, options);

        if (wait_a_click()){free(xdc); free(ydc); return 0 ;}

        grille_int[7][4] = O ;
        SDL_MiseAJourRenderer(renderer, grille_int, morpion_int, grille, croix, rond, 7, 4, options);

        if (wait_a_click()){free(xdc); free(ydc); return 0 ;}

        grille_int[5][3] = X ;
        SDL_MiseAJourRenderer(renderer, grille_int, morpion_int, grille, croix, rond, 5, 3, options);
        SDL_TextInRect(renderer, boite_de_texte_l1, "On voit alors que X à aligner trois");
        SDL_TextInRect(renderer, boite_de_texte_l2, "symboles dans l'un des morpions.");
        SDL_TextInRect(renderer, boite_de_texte_l3, "Il remporte donc ce morpion.");
        SDL_RenderPresent(renderer);

        if (wait_a_click()){free(xdc); free(ydc); return 0 ;}

        check_carre(grille_int, morpion_int, 5, 3);
        SDL_MiseAJourRenderer(renderer, grille_int, morpion_int, grille, croix, rond, 5, 3, options);
        SDL_TextInRect(renderer, boite_de_texte_l1, "Il faut aligner trois morpions");
        SDL_TextInRect(renderer, boite_de_texte_l2, "pour gagner la partie !");
        SDL_TextInRect(renderer, boite_de_texte_l3, "Le jeu continue donc...");
        SDL_RenderPresent(renderer);

        if (wait_a_click()){free(xdc); free(ydc); return 0 ;}

        SDL_RenderFillRect(renderer, &boite_de_texte_l1);
        SDL_TextInRect(renderer, boite_de_texte_l1, "A moins qu'il faille que je répète ?");
        SDL_TextInRect(renderer, boite_de_texte_oui, "Non");
        SDL_TextInRect(renderer, boite_de_texte_non, "Oui");
        SDL_RenderPresent(renderer);

        program_launched = SDL_TRUE ;
        while(program_launched){ 
            
            //On attends un événement.
            while(SDL_PollEvent(&event)){ 

                switch(event.type){

                    case SDL_MOUSEBUTTONDOWN :
                        if (SDL_ClickInButton(event.button.x, event.button.y, boite_de_texte_oui)){ 
                            repeat = 0 ;
                            program_launched = SDL_FALSE ;
                        }
                        else if (SDL_ClickInButton(event.button.x, event.button.y, boite_de_texte_non)){
                            repeat = 1 ;
                            program_launched = SDL_FALSE ;
                        }
                        break;
                    case SDL_QUIT : 
                        free(xdc);
                        free(ydc);
                        return 1;
                        break ;
                }
            }
        }
    }while (repeat);

    do{
        if (repeat){
            grille_int[7][1] = 0 ;
            grille_int[8][3] = 0 ;
            grille_int[8][1] = 0 ;
            grille_int[8][5] = 0 ;
            grille_int[8][8] = 0 ;
            grille_int[8][6] = 0 ;
            grille_int[6][1] = 0 ;
            grille_int[0][4] = 0 ;
            grille_int[1][4] = 0 ;
            grille_int[0][5] = 0 ;
            grille_int[0][7] = 0 ;
            grille_int[0][3] = 0 ;
            init_morpion(morpion_int) ; morpion_int[1][1] = X ;
            SDL_MiseAJourRenderer(renderer, grille_int, morpion_int, grille, croix, rond, 5, 3, options);
            SDL_TextInRect(renderer, boite_de_texte_l1, "C'est pourtant super facile !");
            SDL_TextInRect(renderer, boite_de_texte_l2, "On est reparti pour un tour !");
            SDL_RenderPresent(renderer);
            if (wait_a_click()){free(xdc); free(ydc); return 0 ;}
        }
        grille_int[7][1] = O ;
        SDL_MiseAJourRenderer(renderer, grille_int, morpion_int, grille, croix, rond, 7, 1, options);
        SDL_TextInRect(renderer, boite_de_texte_l1, "O joue dans la case centrale.");
        SDL_TextInRect(renderer, boite_de_texte_l2, "mais le morpion central est déjà complété.");
        SDL_TextInRect(renderer, boite_de_texte_l3, "X joue donc dans le morpion qu'il veut.");
        SDL_RenderPresent(renderer);

        if (wait_a_click()){free(xdc); free(ydc); return 0 ;}

        SDL_RenderFillRect(renderer, &boite_de_texte_l1);
        SDL_TextInRect(renderer, boite_de_texte_l1, "Il est à noter que dans la variante qui");
        SDL_TextInRect(renderer, boite_de_texte_l2, "se lance à partir des options, il est");
        SDL_TextInRect(renderer, boite_de_texte_l3, "possible de jouer dans les cases gagnées.");
        SDL_RenderPresent(renderer);

        if (wait_a_click()){free(xdc); free(ydc); return 0 ;}

        grille_int[8][3] = X ;
        SDL_MiseAJourRenderer(renderer, grille_int, morpion_int, grille, croix, rond, 8, 3, options);
        SDL_TextInRect(renderer, boite_de_texte_l1, "La partie continue...");
        SDL_RenderPresent(renderer);

        if (wait_a_click()){free(xdc); free(ydc); return 0 ;}

        grille_int[8][1] = O ;
        SDL_MiseAJourRenderer(renderer, grille_int, morpion_int, grille, croix, rond, 8, 1, options);

        if (wait_a_click()){free(xdc); free(ydc); return 0 ;}

        grille_int[8][5] = X ;
        check_carre(grille_int, morpion_int, 8, 5);
        SDL_MiseAJourRenderer(renderer, grille_int, morpion_int, grille, croix, rond, 8, 5, options);
        SDL_TextInRect(renderer, boite_de_texte_l1, "X gagne un nouveau morpion !");
        SDL_TextInRect(renderer, boite_de_texte_l2, "Trop fort !");
        SDL_RenderPresent(renderer);

        if (wait_a_click()){free(xdc); free(ydc); return 0 ;}

        grille_int[8][8] = O ;
        SDL_MiseAJourRenderer(renderer, grille_int, morpion_int, grille, croix, rond, 8, 8, options);

        if (wait_a_click()){free(xdc); free(ydc); return 0 ;}

        grille_int[8][6] = X ;
        SDL_MiseAJourRenderer(renderer, grille_int, morpion_int, grille, croix, rond, 8, 6, options);

        if (wait_a_click()){free(xdc); free(ydc); return 0 ;}

        grille_int[6][1] = O ;
        check_carre(grille_int, morpion_int, 6, 1);
        SDL_MiseAJourRenderer(renderer, grille_int, morpion_int, grille, croix, rond, 6, 1, options);
        SDL_TextInRect(renderer, boite_de_texte_l1, "O gagne un morpion !");
        SDL_TextInRect(renderer, boite_de_texte_l2, "Va-t-il remonter ?");
        SDL_RenderPresent(renderer);

        if (wait_a_click()){free(xdc); free(ydc); return 0 ;}

        grille_int[0][4] = X ;
        SDL_MiseAJourRenderer(renderer, grille_int, morpion_int, grille, croix, rond, 0, 4, options);

        if (wait_a_click()){free(xdc); free(ydc); return 0 ;}

        grille_int[1][4] = O ;
        SDL_MiseAJourRenderer(renderer, grille_int, morpion_int, grille, croix, rond, 1, 4, options);

        if (wait_a_click()){free(xdc); free(ydc); return 0 ;}

        grille_int[0][5] = X ;
        SDL_MiseAJourRenderer(renderer, grille_int, morpion_int, grille, croix, rond, 0, 5, options);

        if (wait_a_click()){free(xdc); free(ydc); return 0 ;}

        grille_int[0][7] = O ;
        SDL_MiseAJourRenderer(renderer, grille_int, morpion_int, grille, croix, rond, 0, 7, options);

        if (wait_a_click()){free(xdc); free(ydc); return 0 ;}

        grille_int[0][3] = X ;
        check_carre(grille_int, morpion_int, 0, 3);
        SDL_MiseAJourRenderer(renderer, grille_int, morpion_int, grille, croix, rond, 0, 3, options);
        SDL_TextInRect(renderer, boite_de_texte_l1, "X a aligné trois morpions !");
        SDL_TextInRect(renderer, boite_de_texte_l2, "X a gagné !");
        SDL_TextInRect(renderer, boite_de_texte_l3, "O est vraiment trop nul...");
        SDL_RenderPresent(renderer);

        if (wait_a_click()){free(xdc); free(ydc); return 0 ;}

        SDL_RenderFillRect(renderer, &boite_de_texte_l1);
        SDL_TextInRect(renderer, boite_de_texte_l1, "Mais avez-vous compris les règles ?");
        SDL_TextInRect(renderer, boite_de_texte_oui, "Oui");
        SDL_TextInRect(renderer, boite_de_texte_non, "Non");
        SDL_RenderPresent(renderer);

        program_launched = SDL_TRUE ;
        while(program_launched){ 
            
            //On attends un événement.
            while(SDL_PollEvent(&event)){ 

                switch(event.type){

                    case SDL_MOUSEBUTTONDOWN :
                        if (SDL_ClickInButton(event.button.x, event.button.y, boite_de_texte_oui)){ 
                            repeat = 0 ;
                            program_launched = SDL_FALSE ;
                        }
                        else if (SDL_ClickInButton(event.button.x, event.button.y, boite_de_texte_non)){
                            repeat = 1 ;
                            program_launched = SDL_FALSE ;
                        }
                        break;
                    case SDL_QUIT : 
                        free(xdc);
                        free(ydc);
                        return 1;
                        break ;
                }
            }
        }
    }while (repeat);

    SDL_RenderFillRect(renderer, &boite_de_texte_l1);
    SDL_TextInRect(renderer, boite_de_texte_l1, "Le tutoriel est donc fini ! Merci");
    SDL_TextInRect(renderer, boite_de_texte_l2, "de m'avoir écouté ! Je vous");
    SDL_TextInRect(renderer, boite_de_texte_l3, "souhaite plein de partie endiablée !");
    SDL_RenderPresent(renderer);

    if (wait_a_click()){free(xdc); free(ydc); return 0 ;}

    free(xdc); free(ydc);
    menuscreen(window, renderer, options);
    return 0;
}