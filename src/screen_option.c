#include "../lib/screens.h"
#include "../lib/morpion.h"
#include "../lib/sauvegarde.h"

#define NB_IMG 12

/*Initialise les options à false et logo de base*/
void init_option(option_t * options){
    options->autosave = 0 ;
    options->variante = 0 ;
    options->rondimg = "./src/img/rond.png" ;
    options->croiximg = "./src/img/croix.png" ;
}

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

    SDL_FreeSurface(texte);
    return 0;
}

/*Charge une image dans la surface passée en paramètre*/
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

int optionscreen(SDL_Window * window, SDL_Renderer * renderer, option_t * options){
    
    SDL_bool program_launched = SDL_TRUE ;
    SDL_Event event ;
    int rondcurr = 1 ;
    int croixcurr = 0 ;

    // ==== Déclaration des rectangles
    SDL_Rect background = SDL_CreerRect(0, 0, SCREEN_W, SCREEN_H+ESPACE_TEXTE);

    //Texte
    SDL_Rect bouton_auto = SDL_CreerRect(100, 100, 100, 200);
    SDL_Rect bouton_var = SDL_CreerRect(100, 225, 100, 100);
    SDL_Rect choix_rond = SDL_CreerRect(100, 350, 100, 100);
    SDL_Rect choix_croix = SDL_CreerRect(100, 600, 100, 100);
    SDL_Rect valider = SDL_CreerRect(100, 800, 100, 200);
    SDL_Rect invalide = SDL_CreerRect(5, 850, 100, 200);

    //Images
    SDL_Rect flecheg1 = SDL_CreerRect(150, 450, 50, 50);
    SDL_Rect flecheg2 = SDL_CreerRect(150, 700, 50, 50);
    SDL_Rect fleched1 = SDL_CreerRect(400, 450, 50, 50);
    SDL_Rect fleched2 = SDL_CreerRect(400, 700, 50, 50);
    SDL_Rect rond_icone = SDL_CreerRect(250, 425, 100, 100);
    SDL_Rect croix_icone = SDL_CreerRect(250, 675, 100, 100);
    SDL_Rect valid_auto = SDL_CreerRect(600, 50, 100, 100);
    SDL_Rect valid_var = SDL_CreerRect(600, 175, 100, 100);

    // ==== Déclaration des images
    SDL_Texture * images [NB_IMG] = {NULL};
    SDL_Texture * flecheg = NULL ;
    SDL_Texture * fleched = NULL;
    char * fichiers [NB_IMG] = {"./src/img/croix.png","./src/img/rond.png","./src/img/AmongUs.png","./src/img/bob.png","./src/img/chochodile.png","./src/img/KanGourou.png","./src/img/mary_lyft.png","./src/img/minecraft.png","./src/img/Piplup.png","./src/img/TortueGeniale.png","./src/img/stop.png","./src/img/AuSecours.png"};

    SDL_RenderClear(renderer);

    //Fond
    if (SDL_SetRenderDrawColor(renderer, 187, 238, 238, SDL_ALPHA_OPAQUE) != 0)
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
    if (SDL_TextInRect(renderer, valider, "VALIDER") != 0)
        return 1 ;

    /* ======== CHARGEMENT DES IMAGES ======== */

    for (int i = 0 ; i < NB_IMG ; i++){
        if (SDL_ChargerImage(renderer, fichiers[i], & images[i]) != 0)
            return 2 ;
    }

    if (SDL_ChargerImage(renderer, "./src/img/flechegauche.png", & flecheg) != 0)
        return 2 ;
    if (SDL_ChargerImage(renderer, "./src/img/flechedroite.png", & fleched) != 0)
        return 2 ;

    /* =========== AJOUT DES IMAGES ========== */
    
    if (SDL_ajouter_symbole_dans_case(valid_auto, renderer, images[0]) != 0)
        return 3 ;
    if (SDL_ajouter_symbole_dans_case(valid_var, renderer, images[0]) != 0)
        return 3 ;
    if (SDL_ajouter_symbole_dans_case(flecheg1, renderer, flecheg) != 0)
        return 3 ;
    if (SDL_ajouter_symbole_dans_case(flecheg2, renderer, flecheg) != 0)
        return 3 ;
    if (SDL_ajouter_symbole_dans_case(fleched1, renderer, fleched) != 0)
        return 3 ;
    if (SDL_ajouter_symbole_dans_case(fleched2, renderer, fleched) != 0)
        return 3 ;
    if (SDL_ajouter_symbole_dans_case(rond_icone, renderer, images[1]) != 0)
        return 3 ;
    if (SDL_ajouter_symbole_dans_case(croix_icone, renderer, images[0]) != 0)
        return 3 ;

    SDL_RenderPresent(renderer);

    while(program_launched){ 
        
        //On attends un événement.
        while(SDL_PollEvent(&event)){ 

            switch(event.type){

                case SDL_MOUSEBUTTONDOWN :

                    //Sauvegarde automatique.
                    if (SDL_ClickInButton(event.button.x, event.button.y, valid_auto)){

                        if (options->autosave == 0){
                            if (SDL_RenderFillRect(renderer, &valid_auto) != 0 )
                                return 4;
                            if (SDL_ajouter_symbole_dans_case(valid_auto, renderer, images[1]) != 0)
                                return 3 ;
                            options->autosave = 1 ;
                        }
                        else {
                            if (SDL_RenderFillRect(renderer, &valid_auto) != 0 )
                                return 4;
                            if (SDL_ajouter_symbole_dans_case(valid_auto, renderer, images[0]) != 0)
                                return 3 ;
                            options->autosave = 0 ;                         
                        }

                    }

                    //Variante de jeu.
                    if (SDL_ClickInButton(event.button.x, event.button.y, valid_var)){

                        if (options->variante == 0){
                            if (SDL_RenderFillRect(renderer, &valid_var) != 0 )
                                return 4;
                            if (SDL_ajouter_symbole_dans_case(valid_var, renderer, images[1]) != 0)
                                return 3 ;
                            options->variante = 1 ;
                        }
                        else {
                            if (SDL_RenderFillRect(renderer, &valid_var) != 0 )
                                return 4;
                            if (SDL_ajouter_symbole_dans_case(valid_var, renderer, images[0]) != 0)
                                return 3 ;
                            options->variante = 0 ;                         
                        }
                        
                    }

                    //Clic sur la fleche gauche de rond.
                    if (SDL_ClickInButton(event.button.x, event.button.y, flecheg1)){

                        rondcurr-- ;
                        if (rondcurr < 0) rondcurr = NB_IMG - 1 ;

                        if (SDL_RenderFillRect(renderer, &rond_icone) != 0 )
                            return 4;
                        if (SDL_ajouter_symbole_dans_case(rond_icone, renderer, images[rondcurr]) != 0)
                            return 3 ;
                        
                        options->rondimg = fichiers[rondcurr] ;
                        
                    }

                    //Clic sur la fleche droite de rond.
                    if (SDL_ClickInButton(event.button.x, event.button.y, fleched1)){

                        rondcurr++ ;
                        if (rondcurr >= NB_IMG) rondcurr = 0 ;

                        if (SDL_RenderFillRect(renderer, &rond_icone) != 0 )
                            return 4;
                        if (SDL_ajouter_symbole_dans_case(rond_icone, renderer, images[rondcurr]) != 0)
                            return 3 ;
                        
                        options->rondimg = fichiers[rondcurr] ;
                        
                    }

                    //Clic sur la fleche gauche de croix.
                    if (SDL_ClickInButton(event.button.x, event.button.y, flecheg2)){

                        croixcurr-- ;
                        if (croixcurr < 0) croixcurr = NB_IMG - 1 ;

                        if (SDL_RenderFillRect(renderer, &croix_icone) != 0 )
                            return 4;
                        if (SDL_ajouter_symbole_dans_case(croix_icone, renderer, images[croixcurr]) != 0)
                            return 3 ;
                        
                        options->croiximg = fichiers[croixcurr] ;
                        
                    }

                    //Clic sur la fleche droite de croix.
                    if (SDL_ClickInButton(event.button.x, event.button.y, fleched2)){

                        croixcurr++ ;
                        if (rondcurr >= NB_IMG) croixcurr = 0 ;

                        if (SDL_RenderFillRect(renderer, &croix_icone) != 0 )
                            return 4;
                        if (SDL_ajouter_symbole_dans_case(croix_icone, renderer, images[croixcurr]) != 0)
                            return 3 ;
                        
                        options->croiximg = fichiers[croixcurr] ;
                        
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
                        
                    }

                    SDL_RenderPresent(renderer);
                    continue ;



                //La croix en haut à droite est pressée.
                case SDL_QUIT : 
                    return -1;
                    break ;

                default : break ;
            }
        }
    }

    return 0 ;
}