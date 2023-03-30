#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "../lib/morpion.h"

#define SCREEN_H 800
#define SCREEN_W 800
#define MARGIN 50
#define ESPACE_TEXTE 150


typedef struct option_s {
    int autosave ;
    int variante ;
    char * rondimg ;
    char * croiximg ;
    int r, g, b, rs, gs, bs ; //rgb principal+rgb secondaire
    //char * theme ;
    char * musique;
} option_t ;


SDL_Rect SDL_CreerRect(int x, int y, int w, int h);
int SDL_ClickInButton(int mousex, int mousey, SDL_Rect button);
int menuscreen (SDL_Window * window, SDL_Renderer * renderer, option_t *);
int SDL_AfficherGrilleVide(SDL_Renderer * renderer, SDL_Rect contour, option_t * options);
int gamescreen (SDL_Window * window, SDL_Renderer * renderer, int reload, option_t * options);
int SDL_ajouter_symbole_dans_case (SDL_Rect casegrille, SDL_Renderer * renderer, SDL_Texture * croix);
int SDL_AfficherTexte (SDL_Renderer * renderer, TTF_Font * police, char * chaine);
int SDL_MiseAJourRenderer (SDL_Renderer * renderer, int grille_int[N][N], int morpion_int[M][M], SDL_Rect grille[N][N], SDL_Texture * croix, SDL_Texture * rond, int xdc, int ydc, option_t * options);
int optionscreen(SDL_Window * window, SDL_Renderer * renderer, option_t * options);
void init_option(option_t * options);
int SDL_TextInRect (SDL_Renderer * renderer, SDL_Rect boite, char * message);
int SDL_ChargerImage(SDL_Renderer * renderer, char * fichier, SDL_Texture ** texture);
int ecran_inter (SDL_Window * window, SDL_Renderer * renderer, option_t * options);
int ecran_sauv (SDL_Window * window, SDL_Renderer * renderer, option_t * options);
int tour_de_jeu (SDL_Renderer * renderer, int grille_int[9][9], int morpion_int[3][3], SDL_Rect grille[9][9], SDL_Texture * croix, SDL_Texture * rond, int i, int j, int * xdc, int * ydc, int * joueur, option_t * options, int (*fonction) (int *, int(*)[9], int(*)[3], int *, int *, int, int));
int regles_du_jeu (SDL_Window * window, SDL_Renderer * renderer, option_t * options);