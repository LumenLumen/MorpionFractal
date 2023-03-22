#include "../lib/screens.h"
#include "../lib/morpion.h"
#include "../lib/sauvegarde.h"
#include <time.h>

//fait jouer le joueur "joueur" en utilisant une méthode aléatoire
void ia_random(int * joueur, int grille[N][N], int morpion[M][M], int * xdc, int * ydc, int * x, int * y){
    srand(time(NULL));
    int rdx= rand() % 9;
    int rdy= rand() % 9;
    int val=valideCase(joueur,grille,morpion,xdc,ydc,rdx,rdy);
    
    while(val!=0){
        //printf("IArand : x=%i y=%i val=%i\n",rdx,rdy,val);
        //printf("IArand : Case non valide, relance\n");
        rdx= rand() % 9;
        rdy= rand() % 9;
        val=valideCase(joueur,grille,morpion,xdc,ydc,rdx,rdy);
    }

    //printf("IArand : x=%i y=%i val=%i\n",rdx,rdy,val);
    *x=rdx;
    *y=rdy;
    *xdc=*x;
    *ydc=*y;

}