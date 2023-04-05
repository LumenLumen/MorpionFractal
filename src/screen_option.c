#include "../lib/screens.h"
#include "../lib/morpion.h"
#include "../lib/sauvegarde.h"

/**
\file screen_option.c
\brief programme ...
\author Groupe morpion fractal
\version 1
\date 9 février 2023
*/
#define NB_IMG 18
#define NB_musique 10
#define NB_THEME 7
/**
\fn void init_option(option_t * options)
\brief Initialise les options à false et logo de base

*/
/*Initialise les options à false et logo de base*/
void init_option(option_t * options){
    options->autosave = 0 ;
    options->variante = 0 ;
    options->rondimg = "./src/img/rond.png" ;
    options->croiximg = "./src/img/croix.png" ;
    options->r = 187 ; options->rs = 80 ;
    options->g = 238 ; options->gs = 200 ;
    options->b = 238 ; options->bs = 190 ;
    options->musique = "./src/musique/test.mp3";
    options->vsia = 0 ;
}

/**
\fn int SDL_TextInRect (SDL_Renderer * renderer, SDL_Rect boite, char * message)
\brief Ajoute du texte dans le rectangle passé en paramètre.
\return retourne 0 si on réussi sinon 1. 
*/
/*Ajoute du texte dans le rectangle passé en paramètre*/
int SDL_TextInRect (SDL_Renderer * renderer, SDL_Rect boite, char * message){

    SDL_Color noir = {37, 47, 61};
    SDL_Surface * texte ;
    SDL_Texture * texte_tex ;
    TTF_Font * police = NULL;

    if ((police = TTF_OpenFont("src/font/Coder'sCrux.ttf", 50)) == NULL){
        return 1 ;
    }

    texte = TTF_RenderUTF8_Blended(police, message, noir);
    if (!texte){
        return 1 ;
    }

    texte_tex = SDL_CreateTextureFromSurface(renderer,texte);

    if (!texte_tex){
        return 1 ;
    }
 
    SDL_QueryTexture(texte_tex, NULL, NULL, &(boite.w), &(boite.h));
    SDL_RenderCopy(renderer, texte_tex, NULL, &boite);

    SDL_DestroyTexture(texte_tex);
    SDL_FreeSurface(texte);
    TTF_CloseFont(police);
    return 0;
}


/**
\fn int SDL_ChargerImage(SDL_Renderer * renderer, char * fichier, SDL_Texture ** texture)
\brief Charge une image dans la surface passée en paramètre.
\return 0 si on réussi sinon 1.
*/
int SDL_ChargerImage(SDL_Renderer * renderer, char * fichier, SDL_Texture ** texture){
    SDL_Surface * image ;

    image = IMG_Load(fichier);
    if(!image){
        return 1;
    }

    *texture = SDL_CreateTextureFromSurface(renderer, image);
    if (texture == NULL){
        return 1;
    }

    SDL_FreeSurface(image);
    return 0;
}

int MAJ_option(SDL_Window * window, SDL_Renderer * renderer, option_t * options, int rcurr, int ccurr, int music){

    // ==== Déclaration des rectangles
    SDL_Rect background = SDL_CreerRect(0, 0, SCREEN_W, SCREEN_H+ESPACE_TEXTE);

    //Texte
    SDL_Rect bouton_auto = SDL_CreerRect(100, 100, 100, 200);
    SDL_Rect bouton_var = SDL_CreerRect(100, 225, 100, 100);
    SDL_Rect choix_rond = SDL_CreerRect(100, 325, 100, 100);
    SDL_Rect choix_croix = SDL_CreerRect(100, 550, 100, 100);
    SDL_Rect choix_couleur = SDL_CreerRect(100, 750, 100, 100);
    SDL_Rect valider = SDL_CreerRect(100, 870, 100, 200);

    //Images
    SDL_Rect flecheg1 = SDL_CreerRect(150, 400, 50, 50);
    SDL_Rect flecheg2 = SDL_CreerRect(150, 625, 50, 50);
    SDL_Rect fleched1 = SDL_CreerRect(400, 400, 50, 50);
    SDL_Rect fleched2 = SDL_CreerRect(400, 625, 50, 50);
    SDL_Rect rond_icone = SDL_CreerRect(250, 375, 100, 100);
    SDL_Rect croix_icone = SDL_CreerRect(250, 600, 100, 100);
    SDL_Rect valid_auto = SDL_CreerRect(600, 50, 100, 100);
    SDL_Rect valid_var = SDL_CreerRect(600, 175, 100, 100);
    SDL_Rect couleur = SDL_CreerRect(500, 712, 100, 100);
    SDL_Rect musique = SDL_CreerRect(650, 712, 100, 100);

    // ==== Déclaration des images
    SDL_Texture * images [NB_IMG] = {NULL};
    SDL_Texture * flecheg = NULL ;
    SDL_Texture * fleched = NULL;
    SDL_Texture * couleurtex = NULL, * musiquetex = NULL ;
    char * fichiers [NB_IMG] = {"./src/img/croix.png","./src/img/rond.png","./src/img/AmongUs.png","./src/img/bob.png","./src/img/chochodile.png","./src/img/KanGourou.png","./src/img/minecraft.png","./src/img/Piplup.png","./src/img/TortueGeniale.png","./src/img/stop.png","./src/img/AuSecours.png","./src/img/l.png","./src/img/Rondoudou.png","./src/img/pika.png","./src/img/citrouille.png","./src/img/epouvantaille.png","./src/img/candy.png","./src/img/bougie.png"};
   /* SDL_SetRenderDrawColor(renderer,100,200,40,SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer,&musique);
    SDL_RenderPresent(renderer);*/
    SDL_RenderClear(renderer);
    //SDL_Texture * fleched = NULL;
    //Fond
    if (SDL_SetRenderDrawColor(renderer, options->r, options->g, options->b, SDL_ALPHA_OPAQUE) != 0)
        return 1;
    
    if (SDL_RenderFillRect(renderer, &background) != 0){
        return 1;
    }

    /* =========== TEXTES =============*/

    if (SDL_TextInRect(renderer, bouton_auto, "AUTO-SAUVEGARDE") != 0)
        return 1 ;
    if (SDL_TextInRect(renderer, bouton_var, "VARIANTE") != 0)
        return 1 ;
    if (SDL_TextInRect(renderer, choix_rond, "SYMBOLE DU JOUEUR ROND") != 0)
        return 1 ;
    if (SDL_TextInRect(renderer, choix_croix, "SYMBOLE DU JOUEUR CROIX") != 0)
        return 1 ;
    if (SDL_TextInRect(renderer, choix_couleur, "CHOIX DU THEME : ") != 0)
        return 1 ;
    if (SDL_TextInRect(renderer, valider, "VALIDER") != 0)
        return 1 ;
        

    /* ======== CHARGEMENT DES IMAGES ======== */

    if (SDL_ChargerImage(renderer, fichiers[rcurr], & images[rcurr]) != 0){
            return 2 ;
    }
    if (SDL_ChargerImage(renderer, fichiers[ccurr], & images[ccurr]) != 0){
            return 2 ;
    }
    if (SDL_ChargerImage(renderer, fichiers[0], & images[0]) != 0){
            return 2 ;
    }
    if (SDL_ChargerImage(renderer, fichiers[1], & images[1]) != 0){
            return 2 ;
    }
    if (SDL_ChargerImage(renderer, "./src/img/flechegauche.png", & flecheg) != 0)
        return 2 ;
    if (SDL_ChargerImage(renderer, "./src/img/flechedroite.png", & fleched) != 0)
        return 2 ;

    if (SDL_ChargerImage(renderer, "./src/img/musique_logo.png", &musiquetex) != 0)
        return 2 ;
    if (SDL_ChargerImage(renderer, "./src/img/couleur_logo.png", &couleurtex) != 0)
        return 2 ;

    /* =========== AJOUT DES IMAGES ========== */
    
    if (SDL_ajouter_symbole_dans_case(valid_auto, renderer, images[options->autosave]) != 0)
        return 3 ;
    if (SDL_ajouter_symbole_dans_case(valid_var, renderer, images[options->variante]) != 0)
        return 3 ;
    if (SDL_ajouter_symbole_dans_case(flecheg1, renderer, flecheg) != 0)
        return 3 ;
    if (SDL_ajouter_symbole_dans_case(flecheg2, renderer, flecheg) != 0)
        return 3 ;
    if (SDL_ajouter_symbole_dans_case(fleched1, renderer, fleched) != 0)
        return 3 ;
    if (SDL_ajouter_symbole_dans_case(fleched2, renderer, fleched) != 0)
        return 3 ;
    if (SDL_ajouter_symbole_dans_case(rond_icone, renderer, images[rcurr]) != 0)
        return 3 ;
    if (SDL_ajouter_symbole_dans_case(croix_icone, renderer, images[ccurr]) != 0)
        return 3 ;

    /* =============== THEME =================== */

    if (SDL_SetRenderDrawColor(renderer, options->rs, options->gs, options->bs, SDL_ALPHA_OPAQUE) != 0){
        return 4 ;
    }
    if (SDL_RenderFillRect(renderer, &couleur) != 0)
        return 4 ;

    if (SDL_SetRenderDrawColor(renderer, options->rs, options->gs, options->bs, SDL_ALPHA_OPAQUE) != 0){
        return 4 ;
    }
    if (SDL_RenderFillRect(renderer, &musique) != 0)
        return 4 ;

    if(SDL_ajouter_symbole_dans_case(musique, renderer, musiquetex) != 0){
        return 3 ;
    }

    if(SDL_ajouter_symbole_dans_case(couleur, renderer, couleurtex) != 0){
        return 3;
    }
    
    SDL_RenderPresent(renderer);
    return 0;
}

/**
\fn int optionscreen(SDL_Window * window, SDL_Renderer * renderer, option_t * options)
\brief Options d'affichage.
*/
int optionscreen(SDL_Window * window, SDL_Renderer * renderer, option_t * options){
    
    SDL_bool program_launched = SDL_TRUE ;
    SDL_Event event ;
    int rondcurr = 1 ;
    int croixcurr = 0 ;
    int themecurr = 0 ;
    int music = 0;

    //Images
    SDL_Rect flecheg1 = SDL_CreerRect(150, 400, 50, 50);
    SDL_Rect flecheg2 = SDL_CreerRect(150, 625, 50, 50);
    SDL_Rect fleched1 = SDL_CreerRect(400, 400, 50, 50);
    SDL_Rect fleched2 = SDL_CreerRect(400, 625, 50, 50);
    SDL_Rect valid_auto = SDL_CreerRect(600, 50, 100, 100);
    SDL_Rect valid_var = SDL_CreerRect(600, 175, 100, 100);
    SDL_Rect couleur = SDL_CreerRect(500, 712, 100, 100);
    SDL_Rect musique = SDL_CreerRect(650, 712, 100, 100);
    SDL_Rect valider = SDL_CreerRect(100, 870, 100, 200);
    SDL_Rect invalide = SDL_CreerRect(5, valider.y + 30, 100, 200);

    char * fichiers [NB_IMG] = {"./src/img/croix.png","./src/img/rond.png","./src/img/AmongUs.png","./src/img/bob.png","./src/img/chochodile.png","./src/img/KanGourou.png","./src/img/minecraft.png","./src/img/Piplup.png","./src/img/TortueGeniale.png","./src/img/stop.png","./src/img/AuSecours.png","./src/img/l.png","./src/img/Rondoudou.png","./src/img/pika.png","./src/img/citrouille.png","./src/img/epouvantaille.png","./src/img/candy.png","./src/img/bougie.png"};
    int themes[NB_THEME][6] = {{187, 238, 238, 80, 200, 190},{130, 194, 122, 83, 122, 92}, {126, 147, 191 ,83, 72, 156}, {222, 191, 106,186, 120, 73}, {201, 133, 160,148, 80, 143}, {64, 143, 43, 209, 17, 17}, {218, 133, 0 ,204, 50, 0}};
    char * fich [NB_musique] = {"./src/musique/test.mp3","./src/musique/audio.mp3","./src/musique/ES.mp3","./src/musique/noel.mp3","./src/musique/barbie.mp3","./src/musique/ok.mp3","./src/musique/calme.mp3","./src/musique/pokemon.mp3","./src/musique/urss.mp3"};
    MAJ_option(window, renderer, options, rondcurr, croixcurr, music);


    while(program_launched){ 
        
        //On attends un événement.
        while(SDL_PollEvent(&event)){ 

            switch(event.type){

                case SDL_MOUSEBUTTONDOWN :

                    ///Sauvegarde automatique.
                    if (SDL_ClickInButton(event.button.x, event.button.y, valid_auto)){

                        if (options->autosave == 0){
                            options->autosave = 1 ; 
                        }
                        else {
                            options->autosave = 0 ;                         
                        }
                        MAJ_option(window, renderer, options, rondcurr, croixcurr, music);

                    }

                    //Variante de jeu.
                    if (SDL_ClickInButton(event.button.x, event.button.y, valid_var)){

                        if (options->variante == 0){
                            options->variante = 1 ;
                        }
                        else {
                            options->variante = 0 ;                         
                        }
                        MAJ_option(window, renderer, options, rondcurr, croixcurr,music);
                    }

                    //Clic sur la fleche gauche de rond.
                    if (SDL_ClickInButton(event.button.x, event.button.y, flecheg1)){

                        rondcurr -- ;
                        if (rondcurr < 0) rondcurr = NB_IMG - 1 ;
                        options->rondimg = fichiers[rondcurr] ;

                        MAJ_option(window, renderer, options, rondcurr, croixcurr,music);
                    }

                    //Clic sur la fleche droite de rond.
                    if (SDL_ClickInButton(event.button.x, event.button.y, fleched1)){

                        rondcurr++ ;
                        if (rondcurr >= NB_IMG) rondcurr = 0 ;
                        options->rondimg = fichiers[rondcurr] ;

                        MAJ_option(window, renderer, options, rondcurr, croixcurr,music);
                        
                    }

                    //Clic sur la fleche gauche de croix.
                    if (SDL_ClickInButton(event.button.x, event.button.y, flecheg2)){

                        croixcurr-- ;
                        if (croixcurr < 0) croixcurr = NB_IMG - 1 ;
                        options->croiximg = fichiers[croixcurr] ;

                        MAJ_option(window, renderer, options, rondcurr, croixcurr,music);                        
                    }

                    //Clic sur la fleche droite de croix.
                    if (SDL_ClickInButton(event.button.x, event.button.y, fleched2)){

                        croixcurr++ ;
                        if (croixcurr >= NB_IMG) croixcurr = 0 ;                        
                        options->croiximg = fichiers[croixcurr] ;

                        MAJ_option(window, renderer, options, rondcurr, croixcurr,music);                        
                    }

                    if (SDL_ClickInButton(event.button.x, event.button.y, couleur)){
                        themecurr ++ ;
                        if (themecurr > NB_THEME - 1) themecurr = 0 ;
                        options->r = themes[themecurr][0] ;
                        options->g = themes[themecurr][1] ;
                        options->b = themes[themecurr][2] ;
                        options->rs = themes[themecurr][3] ;
                        options->gs = themes[themecurr][4] ;
                        options->bs = themes[themecurr][5] ;
                        MAJ_option(window, renderer, options, rondcurr, croixcurr,music); 
                    }

                    //Clic sur valider.
                    if (SDL_ClickInButton(event.button.x, event.button.y, valider)){

                            if (options->rondimg != options->croiximg){ //Si les deux logos sont différents
                                menuscreen(window, renderer, options);
                                return 0;
                            }

                            else {
                                if (SDL_TextInRect(renderer, invalide, "Les images ne peuvent pas être identiques.") != 0)
                                    return 1 ;
                            }
                            SDL_RenderPresent(renderer);
                        
                    }
                    if (SDL_ClickInButton(event.button.x, event.button.y, musique)){
                        music++ ;
                        if (music >= NB_musique) music = 0 ;                        
                        options->musique = fich[music] ;
                        Mix_Music *musiques; //Création d'un pointeur de type Mix_Music
                        musiques = Mix_LoadMUS(options->musique); //Chargement de la musique
                        Mix_PlayMusic(musiques, -1); 
                        MAJ_option(window, renderer, options, rondcurr, croixcurr,music); 
                    }
                    continue ;



                //La croix en haut à droite est pressée.
                case SDL_QUIT : 
                    return -1;
                    break ;

                default : break ;
            }
        }
    }
/**
\return 0
*/
    return 0 ;
}