#include "../lib/screens.h"
#include "../lib/morpion.h"
#include "../lib/sauvegarde.h"
/**
\file screen_menu.c
\brief programme ...
\author Groupe morpion fractal
\version 1
\date 9 février 2023
*/

#define TAILLE_DU_TEXTE 50

int ecran_inter (SDL_Window * window, SDL_Renderer * renderer, option_t * options){

    SDL_bool program_launched = SDL_TRUE ;
    SDL_Event event ;

    SDL_Rect background = SDL_CreerRect(0, 0, SCREEN_W, SCREEN_H+ESPACE_TEXTE);
    SDL_Rect local = SDL_CreerRect(SCREEN_W/3 - MARGIN/2, 150, SCREEN_W/3 + MARGIN, SCREEN_H/6);
    SDL_Rect iaVsJoueur = SDL_CreerRect(SCREEN_W/3 - MARGIN/2, 200 + SCREEN_H/6, SCREEN_W/3 + MARGIN, SCREEN_H/6);
    SDL_Rect iaVsIa = SDL_CreerRect(SCREEN_W/3 - MARGIN/2, 250 + 2*SCREEN_H/6, SCREEN_W/3 + MARGIN, SCREEN_H/6);
    SDL_Rect regles = SDL_CreerRect(SCREEN_W/3 - MARGIN/2, 300 + 3*SCREEN_H/6, SCREEN_W/3 + MARGIN, SCREEN_H/6);

    SDL_RenderClear(renderer);

    //Fond
    if (SDL_SetRenderDrawColor(renderer, options->r, options->g, options->b, SDL_ALPHA_OPAQUE) != 0)
        return 1;
    
    if (SDL_RenderFillRect(renderer, &background) != 0){
        return 1;
    }
   
    //Création des boutons
    if (SDL_SetRenderDrawColor(renderer, options->rs, options->gs, options->bs, SDL_ALPHA_OPAQUE) != 0)
        return 1;
    
    if (SDL_RenderFillRect(renderer, &local) != 0){
        return 1;
    }

    if (SDL_RenderFillRect(renderer, &iaVsJoueur) != 0){
        return 1;
    }

    if (SDL_RenderFillRect(renderer, &iaVsIa) != 0){
        return 1;
    }

    if (SDL_RenderFillRect(renderer, &regles) != 0){
        return 1;
    }

    //Texte

    local.x = local.x + 30 ;
    local.y = local.y + 60 ;
    if (SDL_TextInRect(renderer, local, "JOUER EN LOCAL") !=  0){
        return 2 ;
    }

    iaVsJoueur.x = iaVsJoueur.x + 40 ;
    iaVsJoueur.y = iaVsJoueur.y + 60 ;
    if (SDL_TextInRect(renderer, iaVsJoueur, "JOUEUR VS IA") !=  0){
        return 2 ;
    }

    iaVsIa.x = iaVsIa.x + 95 ;
    iaVsIa.y = iaVsIa.y + 20 ;
    if (SDL_TextInRect(renderer, iaVsIa, "SORTEZ") !=  0){
        return 2 ;
    }
    iaVsIa.x = iaVsIa.x - 55;
    iaVsIa.y = iaVsIa.y + 70 ;
    if (SDL_TextInRect(renderer, iaVsIa, "LES POP-CORNS") !=  0){
        return 2 ;
    }

    regles.x = regles.x + 35 ;
    regles.y = regles.y + 60 ;
    if (SDL_TextInRect(renderer, regles, "REGLES DU JEU") !=  0){
        return 2 ;
    }

    local = SDL_CreerRect(SCREEN_W/3 - MARGIN/2, 150, SCREEN_W/3 + MARGIN, SCREEN_H/6);
    iaVsJoueur = SDL_CreerRect(SCREEN_W/3 - MARGIN/2, 200 + SCREEN_H/6, SCREEN_W/3 + MARGIN, SCREEN_H/6);
    iaVsIa = SDL_CreerRect(SCREEN_W/3 - MARGIN/2, 250 + 2*SCREEN_H/6, SCREEN_W/3 + MARGIN, SCREEN_H/6);
    regles = SDL_CreerRect(SCREEN_W/3 - MARGIN/2, 300 + 3*SCREEN_H/6, SCREEN_W/3 + MARGIN, SCREEN_H/6);

    SDL_RenderPresent(renderer);


    //DEBUT DES EVENTS
    while(program_launched){ 
        
        //On attends un événement.
        while(SDL_PollEvent(&event)){ 

            switch(event.type){
                
                case SDL_MOUSEBUTTONDOWN :
                    //clic sur le bouton nouvelle partie
                    if (SDL_ClickInButton(event.button.x, event.button.y, local)){
                        gamescreen(window, renderer, 0, options);
                        return 0 ;
                    }

                    if (SDL_ClickInButton(event.button.x, event.button.y, iaVsJoueur)){
                        printf("Pas encore implémenté !\n");
                        return 0 ;
                    }

                    if (SDL_ClickInButton(event.button.x, event.button.y, iaVsIa)){
                        printf("Le maïs est dans le micro-ondes...\n");
                        return 0 ;
                    }

                    if (SDL_ClickInButton(event.button.x, event.button.y, regles)){
                        regles_du_jeu(window, renderer, options);
                        return 0 ;
                    }

                    continue ;

                //La croix en haut à droite est pressée.
                case SDL_QUIT : 
                    return 0 ;
                    break ;
            }
        }
    }
    return 0;
}

int ecran_sauv (SDL_Window * window, SDL_Renderer * renderer, option_t * options){
    SDL_bool program_launched = SDL_TRUE ;
    SDL_Event event ;

    SDL_Rect background = SDL_CreerRect(0, 0, SCREEN_W, SCREEN_H + ESPACE_TEXTE);
    SDL_Rect manualsave = SDL_CreerRect(SCREEN_W/3 - MARGIN/2, 150, SCREEN_W/3 + MARGIN, SCREEN_H/6);
    SDL_Rect autosave = SDL_CreerRect(SCREEN_W/3 - MARGIN/2, 200 + SCREEN_H/6, SCREEN_W/3 + MARGIN, SCREEN_H/6);

    SDL_RenderClear(renderer);

    //Fond
    if (SDL_SetRenderDrawColor(renderer, options->r, options->g, options->b, SDL_ALPHA_OPAQUE) != 0)
        return 1;
    
    if (SDL_RenderFillRect(renderer, &background) != 0){
        return 1;
    }
   
    //Création des boutons
    if (SDL_SetRenderDrawColor(renderer, options->rs, options->gs, options->bs, SDL_ALPHA_OPAQUE) != 0)
        return 1;
    
    if (SDL_RenderFillRect(renderer, &manualsave) != 0){
        return 1;
    }

    if (SDL_RenderFillRect(renderer, &autosave) != 0){
        return 1;
    }

    //Texte

    manualsave.x = manualsave.x + 65;
    manualsave.y = manualsave.y + 25 ;
    if (SDL_TextInRect(renderer, manualsave, "SAUVEGARDE") !=  0){
        return 2 ;
    }
    manualsave.x = manualsave.x + 20 ;
    manualsave.y = manualsave.y + 60 ;
    if (SDL_TextInRect(renderer, manualsave, "MANUELLE") !=  0){
        return 2 ;
    }

    autosave.x = autosave.x + 20;
    autosave.y = autosave.y + 55 ;
    if (SDL_TextInRect(renderer, autosave, "AUTO-SAUVEGARDE") !=  0){
        return 2 ;
    }

    manualsave = SDL_CreerRect(SCREEN_W/3 - MARGIN/2, 150, SCREEN_W/3 + MARGIN, SCREEN_H/6);
    autosave = SDL_CreerRect(SCREEN_W/3 - MARGIN/2, 200 + SCREEN_H/6, SCREEN_W/3 + MARGIN, SCREEN_H/6);


    SDL_RenderPresent(renderer);


    //DEBUT DES EVENTS
    while(program_launched){ 
        
        //On attends un événement.
        while(SDL_PollEvent(&event)){ 

            switch(event.type){
                
                case SDL_MOUSEBUTTONDOWN :
                    //clic sur le bouton nouvelle partie
                    if (SDL_ClickInButton(event.button.x, event.button.y, autosave)){
                        gamescreen(window, renderer, 1, options);
                        return 0 ;
                    }

                    if (SDL_ClickInButton(event.button.x, event.button.y, manualsave)){
                        gamescreen(window, renderer, 2, options);
                        return 0 ;
                    }

                    continue ;

                //La croix en haut à droite est pressée.
                case SDL_QUIT : 
                    return 0 ;
                    break ;
            }
        }
    }
    return 0;
}

/**
\fn int menuscreen (SDL_Window * window, SDL_Renderer * renderer, option_t * options)
\brief Fonction qui gère les boutons.

*/
int menuscreen (SDL_Window * window, SDL_Renderer * renderer, option_t * options){

    SDL_bool program_launched = SDL_TRUE ;
    SDL_Event event ;
    SDL_Color noir = {37, 47, 61};
    SDL_Texture * texte_tex ;
    SDL_Surface * texte ;

    SDL_Rect background = SDL_CreerRect(0, 0, SCREEN_W, SCREEN_H+ESPACE_TEXTE);
    SDL_Rect newgame = SDL_CreerRect(SCREEN_W/3 - MARGIN/2, 150, SCREEN_W/3 + MARGIN, SCREEN_H/6);
    SDL_Rect loadgame = SDL_CreerRect(SCREEN_W/3 - MARGIN/2, 200 + SCREEN_H/6, SCREEN_W/3 + MARGIN, SCREEN_H/6);
    SDL_Rect optiongame = SDL_CreerRect(SCREEN_W/3 - MARGIN/2, 250 + 2*SCREEN_H/6, SCREEN_W/3 + MARGIN, SCREEN_H/6);
    SDL_Rect quitgame = SDL_CreerRect(SCREEN_W/3 - MARGIN/2, 300 + 3*SCREEN_H/6, SCREEN_W/3 + MARGIN, SCREEN_H/6);
    // A revoir si on resize la fenêtre

    //Fond
    if (SDL_SetRenderDrawColor(renderer, options->r, options->g, options->b, SDL_ALPHA_OPAQUE) != 0)
        return 1;
    
    if (SDL_RenderFillRect(renderer, &background) != 0){
        return 1;
    }

    //Carrés menu
    TTF_Font *police=NULL;
    if( (police = TTF_OpenFont("src/font/Coder'sCrux.ttf", TAILLE_DU_TEXTE)) == NULL){
        return 1;
    }

   
    //Création des boutons
    if (SDL_SetRenderDrawColor(renderer, options->rs, options->gs, options->bs, SDL_ALPHA_OPAQUE) != 0)
        return 1;
    
    if (SDL_RenderFillRect(renderer, &newgame) != 0){
        return 1;
    }

    if (SDL_RenderFillRect(renderer, &loadgame) != 0){
        return 1;
    }

    if (SDL_RenderFillRect(renderer, &optiongame) != 0){
        return 1;
    }

    if (SDL_RenderFillRect(renderer, &quitgame) != 0){
        return 1;
    }


    /* ============== TEXTE DES BOUTONS ============================= */

    /* === NEWGAME === */
    texte=TTF_RenderUTF8_Blended(police,"NOUVELLE PARTIE",noir);
    if(!texte){
        return 2;
    }

    texte_tex = SDL_CreateTextureFromSurface(renderer,texte);

    if(!texte_tex){
        return 2;
    }
 
    newgame.y = newgame.y + (newgame.h/2 + TAILLE_DU_TEXTE)/2 ;
    newgame.x = SCREEN_W/3 - MARGIN/4 ;
    SDL_QueryTexture(texte_tex,NULL,NULL,&(newgame.w),&(newgame.h));
    SDL_RenderCopy(renderer,texte_tex,NULL,&newgame);

    /*=== CHARGER PARTIE ===*/
    texte=TTF_RenderUTF8_Blended(police,"CHARGER PARTIE",noir);
    if(!texte){
        return 2;
    }

    texte_tex = SDL_CreateTextureFromSurface(renderer,texte);

    if(!texte_tex){
        return 2;
    }
 
    loadgame.y = loadgame.y + (loadgame.h/2 + TAILLE_DU_TEXTE)/2 ;
    loadgame.x = SCREEN_W/3 - MARGIN/4 + 10;
    SDL_QueryTexture(texte_tex,NULL,NULL,&(loadgame.w),&(loadgame.h));
    SDL_RenderCopy(renderer,texte_tex,NULL,&loadgame);

    /*=== OPTION ===*/
    texte=TTF_RenderUTF8_Blended(police,"OPTIONS",noir);
    if(!texte){
        return 2;
    }

    texte_tex = SDL_CreateTextureFromSurface(renderer,texte);

    if(!texte_tex){
        return 2;
    }
 
    optiongame.y = optiongame.y + (optiongame.h/2 + TAILLE_DU_TEXTE)/2 ;
    optiongame.x = SCREEN_W/3 + MARGIN/2 + 37;
    SDL_QueryTexture(texte_tex,NULL,NULL,&(optiongame.w),&(optiongame.h));
    SDL_RenderCopy(renderer,texte_tex,NULL,&optiongame);

    /*=== QUIT ===*/
    texte=TTF_RenderUTF8_Blended(police,"QUITTER",noir);
    if(!texte){
        return 2;
    }

    texte_tex = SDL_CreateTextureFromSurface(renderer,texte);

    if(!texte_tex){
        return 2;
    }
 
    quitgame.y = quitgame.y + (quitgame.h/2 + TAILLE_DU_TEXTE)/2 ;
    quitgame.x = SCREEN_W/3 + MARGIN + 15;
    SDL_QueryTexture(texte_tex,NULL,NULL,&(quitgame.w),&(quitgame.h));
    SDL_RenderCopy(renderer,texte_tex,NULL,&quitgame);

    SDL_FreeSurface(texte);
    TTF_CloseFont(police);
    SDL_RenderPresent(renderer);

    newgame = SDL_CreerRect(SCREEN_W/3 - MARGIN/2, 150, SCREEN_W/3 + MARGIN, SCREEN_H/6);
    loadgame = SDL_CreerRect(SCREEN_W/3 - MARGIN/2, 200 + SCREEN_H/6, SCREEN_W/3 + MARGIN, SCREEN_H/6);
    optiongame = SDL_CreerRect(SCREEN_W/3 - MARGIN/2, 250 + 2*SCREEN_H/6, SCREEN_W/3 + MARGIN, SCREEN_H/6);
    quitgame = SDL_CreerRect(SCREEN_W/3 - MARGIN/2, 300 + 3*SCREEN_H/6, SCREEN_W/3 + MARGIN, SCREEN_H/6);

    //DEBUT DES EVENTS
    while(program_launched){ 
        
        //On attends un événement.
        while(SDL_PollEvent(&event)){ 

            switch(event.type){
                
                case SDL_MOUSEBUTTONDOWN :
                    //clic sur le bouton nouvelle partie
                    if (SDL_ClickInButton(event.button.x, event.button.y, newgame)){
                        ecran_inter(window, renderer, options);
                        return 0;
                    }
                    
                    //clic sur chargement d'une partie
                    else if (SDL_ClickInButton(event.button.x, event.button.y, loadgame)){
                        ecran_sauv(window,renderer, options);
                        return 0;
                    }
                    //clic sur options
                    else if (SDL_ClickInButton(event.button.x, event.button.y, optiongame)){
                        optionscreen(window, renderer, options);
                        return 0;
                    }

                    //clic sur quitter
                    else if (SDL_ClickInButton(event.button.x, event.button.y, quitgame)){
                        SDL_DestroyRenderer(renderer);
                        SDL_DestroyWindow(window);
                        free(options);
                        TTF_Quit();
                        SDL_Quit();
                        exit(0);
                    }
                    continue;
                    

                //La croix en haut à droite est pressée.
                case SDL_QUIT : 
                    return 0 ;

                default : break ;
            }
        }
    }

    return 0 ;
}