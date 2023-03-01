#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "../lib/morpion.h"

#define SCREEN_H 800
#define SCREEN_W 800
#define MARGIN 50
#define ESPACE_TEXTE 150

void SDL_ExitWithError(const char * message);
SDL_Rect SDL_CreerRect(int x, int y, int w, int h);
int SDL_ClickInButton(int mousex, int mousey, SDL_Rect button);
int menuscreen (void);
int SDL_AfficherGrilleVide(SDL_Renderer * renderer, SDL_Rect contour);
int gamescreen (SDL_Window * window, SDL_Renderer * renderer, int reload);
int SDL_ajouter_symbole_dans_case (SDL_Rect casegrille, SDL_Renderer * renderer, SDL_Texture * croix);
int SDL_AfficherTexte (SDL_Renderer * renderer, TTF_Font * police, SDL_Color couleur, char * chaine/*, SDL_Rect boite_de_texte*/);
int valideCase (int * joueur, int grille[N][N], int morpion[M][M], int * xdc, int * ydc, int x, int y);