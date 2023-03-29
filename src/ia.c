#include "../lib/screens.h"
#include "../lib/morpion.h"
#include "../lib/sauvegarde.h"

//donne des coordonnées aléatoire
void ia_random(int * x, int * y){
    int rdx= rand() % 9;
    int rdy= rand() % 9;
    *x=rdx;
    *y=rdy;
}

void ia_random_2(int xdc, int ydc, int * x, int * y, int morpion[M][M], int grille[N][N]){
    int rdx= rand() % 9;
    int rdy= rand() % 9;
    int cpt=0;
    
    if(morpion[xdc%3][ydc%3]!=0){
        while(grille[rdx][rdy]!=0){
            rdx= rand() % 9;
            rdy= rand() % 9;
        }

        *x=rdx;
        *y=rdy;
    }

    else{
        rdx= rand() % 3;
        rdy= rand() % 3;

        while((xdc%3)!=0) xdc--;
        while((ydc%3)!=0) ydc--;

        while(!(morpion[rdx][rdy]==0 && grille[xdc*3+rdx][ydc*3+rdy]==0) && cpt<300){
            rdx= rand() % 3;
            rdy= rand() % 3;
            cpt++;
        }

        *x=rdx+xdc*3;
        *y=rdy+ydc*3;
    }

    printf("IArand : x=%i y=%i morpion=%i, grille=%i, cpt=%i\n",rdx,rdy,morpion[rdx%3][rdy%3], grille[rdx][rdy],cpt);
}

void ia_random_completionniste(int joueur, int xdc, int ydc, int * x, int * y, int grille[N][N]){
    predict_rect(xdc,ydc,x,y);
    int rdx, rdy;
    int morpion[3][3];
    int i,j;
    int cpt=100;

    while((xdc%3)!=0) xdc--;
    while((ydc%3)!=0) ydc--;
    
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            morpion[i][j]=grille[xdc+i][ydc+j];
        }
    }

    do{
        rdx= rand() % 3;
        rdy= rand() % 3;

        if(morpion[rdx][rdy]!=0){
            morpion[rdx][rdy]=joueur;
        } 

        cpt--;

    } while(morpiongagne(morpion)!=joueur && cpt);

    *x=xdc*3+rdx;
    *y=ydc*3+rdy;
}






















//fait jouer le joueur "joueur" en utilisant une méthode aléatoire (fonction pour tester)
int ia_random_test(int * joueur, int grille[N][N], int morpion[M][M], int * xdc, int * ydc, int x, int y){
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

    printf("IArand : x=%i y=%i val=%i\n",rdx,rdy,val);
    return 0;
}

//fait jouer le joueur "joueur" en utilisant une méthode aléatoire (fonction pour tester)
int ia_random_var_test(int * joueur, int grille[N][N], int morpion[M][M], int * xdc, int * ydc, int x, int y){
    int rdx= rand() % 9;
    int rdy= rand() % 9;
    int val=valideCase_var(joueur,grille,morpion,xdc,ydc,rdx,rdy);
    
    while(val!=0){
        //printf("IArand : x=%i y=%i val=%i\n",rdx,rdy,val);
        //printf("IArand : Case non valide, relance\n");
        rdx= rand() % 9;
        rdy= rand() % 9;
        val=valideCase_var(joueur,grille,morpion,xdc,ydc,rdx,rdy);
    }

    printf("IArand : x=%i y=%i val=%i\n",rdx,rdy,val);
    return 0;
}