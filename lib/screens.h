#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#define SCREEN_H 800
#define SCREEN_W 800
#define MARGIN 50

void SDL_ExitWithError(const char * message);
SDL_Rect SDL_CreerRect(int x, int y, int w, int h);
int SDL_ClickInButton(int mousex, int mousey, SDL_Rect button);
int menuscreen (void);
int SDL_AfficherGrilleVide(SDL_Renderer * renderer, SDL_Rect contour);
int gamescreen (SDL_Window * window, SDL_Renderer * renderer);