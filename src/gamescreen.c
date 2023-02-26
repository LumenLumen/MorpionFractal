#include "../lib/screens.h"
#include "../lib/morpion.h"


int gamescreen (SDL_Window * window, SDL_Renderer * renderer){

    SDL_RenderClear(renderer);

    SDL_bool program_launched = SDL_TRUE ;
    SDL_Event event ;

    SDL_Rect contour = SDL_CreerRect(MARGIN, MARGIN, SCREEN_H - MARGIN*2, SCREEN_W - MARGIN*2);

    SDL_Rect grille[9][9];
    //SDL_Rect morpion[3][3];

    SDL_Texture * croix ;
    SDL_Texture * rond ;
    SDL_Surface * image ;
    TTF_Font *police = NULL;
    
    int grille_int[N][N];
    int morpion_int[M][M];
    int i, j;
    int vainqueur ;

    int joueur = 1 ; //Tour du joueur ;
    int * xdc = malloc(sizeof(int)); //Ligne du dernier coup ;
    int * ydc = malloc(sizeof(int)); //Colonne du dernier coup ;

    (* xdc) = -1 ;
    (* ydc) = -1 ;
    init_grille(grille_int);
    init_morpion(morpion_int);

    /*========================== CHARGEMENT DES IMAGES ===============================*/
    

    image = IMG_Load("./src/img/bob.png");
    if(!image){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Echec du chargement de l'image.");
    }

    croix = SDL_CreateTextureFromSurface(renderer, image);
    if (croix == NULL){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Echec du chargement de l'image sur la texture.");
    }

    image = IMG_Load("./src/img/chochodile.png");
    if(!image){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Echec du chargement de l'image.");
    }

    rond = SDL_CreateTextureFromSurface(renderer, image);
    if (rond == NULL){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Echec du chargement de l'image sur la texture.");
    }

    SDL_FreeSurface(image);

    /* ====================================== CHARGEMENT DU TEXTE =========================================*/

    if( (police = TTF_OpenFont("src/font/MB-ThinkTwice_Regular.ttf", 50)) == NULL){
        SDL_ExitWithError("Echec chargement police");
    }

    /*SDL_Rect boite_de_texte = SDL_CreerRect(0, SCREEN_H, SCREEN_W, ESPACE_TEXTE);*/
    SDL_Color noir={0,0,0};
    
    SDL_AfficherTexte(renderer, police, noir, "Début de la partie !");

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

    /*
    for (i = 0 ; i < 3 ; i++){
        for (j = 0 ; j < 3 ; j++){
            morpion[i][j]=SDL_CreerRect(MARGIN + i * contour.w/3, MARGIN + j * contour.h/3,contour.w/3,contour.h/3);
        }
    }*/

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
                                    if (! valideCase(&joueur, grille_int, morpion_int, xdc, ydc, i, j)){

                                        if (joueur == X) SDL_ajouter_symbole_dans_case(grille[j][i], renderer, croix);
                                        else SDL_ajouter_symbole_dans_case(grille[j][i], renderer, rond);

                                        check_carre(grille_int, morpion_int, i, j);

                                        vainqueur = morpiongagne(morpion_int);
                                        if (vainqueur != 0) program_launched = SDL_FALSE ;
                                        printf("\n");
                                        printf("\n");
                                    }
                                    
                                }
                            }
                        }

                    }
                    continue;
                
                //La croix en haut à droite est pressée.
                case SDL_QUIT : 
                    program_launched = SDL_FALSE ;
                    SDL_DestroyRenderer(renderer);
                    SDL_DestroyWindow(window);
                    SDL_Quit();
                    exit(0);
                    break ;

                default : break ;
            }
        }
    }

    //Annonce du vainqueur
    //printf("Appel fonction | ");
    if (i == X) SDL_AfficherTexte(renderer, police, noir, "Le vainqueur est Bob.");
    else SDL_AfficherTexte(renderer, police, noir, "Le vainqueur est Chochodile.");
    SDL_Delay(1000);
    //printf("Fin fonction.");

    //Libération de la mémoire
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}


int menuscreen (void){

    SDL_Window * window = NULL ;
    SDL_Renderer * renderer = NULL ;
    SDL_bool program_launched = SDL_TRUE ;
    SDL_Event event ;

    SDL_Surface * image = NULL ; 
    SDL_Texture * texture = NULL ;
    

    SDL_Rect background = SDL_CreerRect(0, 0, SCREEN_W, SCREEN_H+ESPACE_TEXTE);
    SDL_Rect newgame = SDL_CreerRect(SCREEN_W/3, 150, SCREEN_W/3, SCREEN_H/6);
    SDL_Rect loadgame = SDL_CreerRect(SCREEN_W/3, 200 + SCREEN_H/6, SCREEN_W/3, SCREEN_H/6);
    SDL_Rect optiongame = SDL_CreerRect(SCREEN_W/3, 250 + 2*SCREEN_H/6, SCREEN_W/3, SCREEN_H/6);
    SDL_Rect quitgame = SDL_CreerRect(SCREEN_W/3, 300 + 3*SCREEN_H/6, SCREEN_W/3, SCREEN_H/6);
    // A revoir si on resize la fenêtre

    //Initialise SDL pour l'aspect visuel.
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        SDL_ExitWithError("Initialisation SDL");
    }

    //Initialise TTF
	if(TTF_Init() == -1) {
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}

    //Création de la fenêtre.
    window = SDL_CreateWindow("Morpion fractal", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_H, SCREEN_W + ESPACE_TEXTE, 0);
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
    if (SDL_SetRenderDrawColor(renderer, 187, 238, 238, SDL_ALPHA_OPAQUE) != 0)
        SDL_ExitWithError("Impossible de la couleur du rendu");
    
    if (SDL_RenderFillRect(renderer, &background) != 0){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de créer le rectangle background.");
    }

    //Carrés menu
    TTF_Font *police=NULL;
    //TTF_Font *TTF_OpenFont(const char * file, int ptsize);
    if( (police = TTF_OpenFont("src/font/ChowFun.ttf", 20)) == NULL){
        printf("erreur chargement font\n");
        exit(EXIT_FAILURE);
    }
    SDL_Color noir={0,0,0};

   

    if (SDL_SetRenderDrawColor(renderer, 80, 200, 190, SDL_ALPHA_OPAQUE) != 0)
        SDL_ExitWithError("Impossible de la couleur du rendu");
    
    /*image = SDL_LoadBMP("src/img/newgame.bmp");
    if (image == NULL){ 
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de charger l'image");
    }
    texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    if (texture == NULL){ 
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de créer la texture");
    }
    if(SDL_QueryTexture(texture, NULL, NULL, &newgame.w, &newgame.h) != 0){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de charger la texture");
    }
    newgame = SDL_CreerRect(SCREEN_W/3, 50, SCREEN_W/3, SCREEN_H/6);
    if(SDL_RenderCopy(renderer, texture, NULL, &newgame) != 0){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible d'afficher la texture");
    }
    */
    
    if (SDL_RenderFillRect(renderer, &newgame) != 0){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de créer le rectangle newgame.");
    }

    if (SDL_RenderFillRect(renderer, &loadgame) != 0){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de créer le rectangle loadgame.");
    }

    if (SDL_RenderFillRect(renderer, &optiongame) != 0){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de créer le rectangle optiongame.");
    }

    if (SDL_RenderFillRect(renderer, &quitgame) != 0){
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de créer le rectangle quitgame.");
    }


    //texte nouvelle partie
     SDL_Surface *texte=TTF_RenderUTF8_Blended(police,"NOUVELLE PARTIE",noir);
    if(!texte){
        printf("Erreur à la création du texte newgame : %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_Texture *texte_tex = SDL_CreateTextureFromSurface(renderer,texte);
    if(!texte_tex){
        printf("Erreur à la création du rendu de texte newgame : %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(texte);
    //position du texte
    newgame.y=200; 
    SDL_QueryTexture(texte_tex,NULL,NULL,&(newgame.w),&(newgame.h));
    TTF_CloseFont(police);
    
   
   SDL_SetRenderDrawColor(renderer,0,0,0,255);
   SDL_RenderCopy(renderer,texte_tex,NULL,&newgame);


    SDL_RenderPresent(renderer);

    newgame = SDL_CreerRect(SCREEN_W/3, 150, SCREEN_W/3, SCREEN_H/6);
    loadgame = SDL_CreerRect(SCREEN_W/3, 200 + SCREEN_H/6, SCREEN_W/3, SCREEN_H/6);
    optiongame = SDL_CreerRect(SCREEN_W/3, 250 + 2*SCREEN_H/6, SCREEN_W/3, SCREEN_H/6);
    quitgame = SDL_CreerRect(SCREEN_W/3, 300 + 3*SCREEN_H/6, SCREEN_W/3, SCREEN_H/6);

    //DEBUT DES EVENTS
    while(program_launched){ 
        
        //On attends un événement.
        while(SDL_PollEvent(&event)){ 

            switch(event.type){
                
                case SDL_MOUSEBUTTONDOWN :
                    //clic sur le bouton nouvelle partie
                    if (SDL_ClickInButton(event.button.x, event.button.y, newgame)){
                        printf("Nouvelle partie !\n");
                        gamescreen(window,renderer);
                        }
                    
                    //clic sur chargement d'une partie
                    else if (SDL_ClickInButton(event.button.x, event.button.y, loadgame)){

                    }
                    //clic sur options
                    else if (SDL_ClickInButton(event.button.x, event.button.y, optiongame))
                        printf("Affichage des options !\n");

                    //clic sur quitter
                    else if (SDL_ClickInButton(event.button.x, event.button.y, quitgame))
                        program_launched = SDL_FALSE ;
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
    TTF_Quit();
    SDL_Quit();
    return 0;
}