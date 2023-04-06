#include "../lib/screens.h"
#include "../lib/morpion.h"
#include "../lib/sauvegarde.h"

/**
    \file ia.c
    \brief Programme contenant toutes les fonctions nécessaires à la génération des coups de la machine.
    \author Groupe morpion fractal
    \version 1
    \date 22 mars 2023
*/

/**
    \fn ia_random(int joueur, int xdc, int ydc, int * x, int * y, int morpion[M][M], int grille[N][N])
    \brief donne des coordonnées aléatoires
    \param joueur le jouer dont c'est le tour
    \param xdc abscisse dernier coup joué
    \param ydc ordonnée dernier coup joué
    \param x pointeur vers l'abscisse que va retourner la fonction
    \param y pointeur vers l'ordonnée que va retourner la fonction
    \param morpion matrice 3*3
    \param grille matrice 9*9
*/
void ia_random(int joueur, int xdc, int ydc, int * x, int * y, int morpion[M][M], int grille[N][N]){
    int rdx= rand() % 9;
    int rdy= rand() % 9;
    *x=rdx;
    *y=rdy;
}

/**
    \fn void ia_random_2(int joueur, int xdc, int ydc, int * x, int * y, int morpion[M][M], int grille[N][N])
    \brief donne des coordonnées aléatoires en évitant de renvoyer l'adversaire sur une case où il peut jouer où il veut
    \param joueur le jouer dont c'est le tour
    \param xdc abscisse dernier coup joué
    \param ydc ordonnée dernier coup joué
    \param x pointeur vers l'abscisse que va retourner la fonction
    \param y pointeur vers l'ordonnée que va retourner la fonction
    \param morpion matrice 3*3
    \param grille matrice 9*9
*/
void ia_random_prudent(int joueur, int xdc, int ydc, int * x, int * y, int morpion[M][M], int grille[N][N]){
    
    int rdx; //coordonnées random 
    int rdy;
    int cpt=50; //compteur pour éviter de tourner à l'infini si aucune case n'est valide
    
    if(morpion[xdc%3][ydc%3]!=0){ //si on joue où on veut

        do{
            rdx= rand() % 9;
            rdy= rand() % 9;
            cpt--;
        } while(!(morpion[rdx%3][rdy%3]==0 && grille[rdx][rdy]==0) && cpt); //on vérifie qu'on a le droit de jouer  dans cette case et qu'on ne fera pas jouer l'adversaire où il veut

        *x=rdx;
        *y=rdy;
    }

    else{ //si on joue dans un petit morpion en particulier

        predict_rect(xdc,ydc,x,y); //on attribue les coordonnées du petit morpion à x et y

        do {
            rdx= rand() % 3;
            rdy= rand() % 3;
            cpt--;
        } while(!(morpion[rdx][rdy]==0 && grille[*x*3+rdx][*y*3+rdy]==0) && cpt); //on vérifie qu'on a le droit de jouer  dans cette case et qu'on ne fera pas jouer l'adversaire où il veut

        *x=rdx+*x*3;
        *y=rdy+*y*3;
    }
}

/**
    \fn void ia_random_completionniste(int joueur, int xdc, int ydc, int * x, int * y, int morpion[M][M], int grille[N][N])
    \brief donne des coordonnées aléatoires, en essayant de compléter un morpion quand c'est possible
    \param joueur le jouer dont c'est le tour
    \param xdc abscisse dernier coup joué
    \param ydc ordonnée dernier coup joué
    \param x pointeur vers l'abscisse que va retourner la fonction
    \param y pointeur vers l'ordonnée que va retourner la fonction
    \param morpion matrice 3*3
    \param grille matrice 9*9
*/
void ia_random_completionniste(int joueur, int xdc, int ydc, int * x, int * y, int morpion[M][M], int grille[N][N]){
    
    int rdx, rdy;
    int petit_morpion[3][3];
    int i, j, k, l;
    int cpt=30, cpt2=30;
    
    predict_rect(xdc,ydc,x,y);

    if(morpion[*x][*y]!=0){
        do{

            l= rand() % 3;
            k= rand() % 3;

            if (morpion[k][l] == 0){

                cpt=30;

                for(i=0;i<3;i++){
                    for(j=0;j<3;j++){
                        petit_morpion[i][j]=grille[k*3+i][l*3+j];
                    }
                }

                do{
                    rdx= rand() % 3;
                    rdy= rand() % 3;

                    if(petit_morpion[rdx][rdy]==0){
                        petit_morpion[rdx][rdy]=joueur;

                        if(!morpiongagne(petit_morpion)){
                            petit_morpion[rdx][rdy]=0;
                            cpt--;
                        }

                        else{
                            cpt=0;
                            cpt2=0;
                        }
                    }

                    else{
                        cpt--;
                    }

                } while(cpt);

                if(cpt2>0) cpt2--;
            }

            else{
                cpt2--;
            }

        } while (cpt2);

        *x=k*3+rdx;
        *y=l*3+rdy;

    }

    else{
        for(i=0;i<3;i++){
            for(j=0;j<3;j++){
                petit_morpion[i][j]=grille[*x*3+i][*y*3+j];
            }
        }

        do{
            rdx= rand() % 3;
            rdy= rand() % 3;

            if(petit_morpion[rdx][rdy]==0){
                petit_morpion[rdx][rdy]=joueur;

                if(!morpiongagne(petit_morpion)){
                    petit_morpion[rdx][rdy]=0;
                    cpt--;
                }

                else{
                    cpt=0;
                }
            }

            else{
                cpt--;
            }

        } while(cpt);

        *x=*x*3+rdx;
        *y=*y*3+rdy;

    }

}

/**
    \fn void ia_eval_simple(int joueur, int xdc, int ydc, int * x, int * y, int morpion[M][M], int grille[N][N])
    \brief donne des coordonnées basées sur le coup qui donne le "meilleur" tableau pour le joueur immédiatement après le coup
    \param joueur le joueur dont c'est le tour
    \param xdc abscisse dernier coup joué
    \param ydc ordonnée dernier coup joué
    \param x pointeur vers l'abscisse que va retourner la fonction
    \param y pointeur vers l'ordonnée que va retourner la fonction
    \param morpion matrice 3*3
    \param grille matrice 9*9
*/
void ia_eval_simple(int joueur, int xdc, int ydc, int * x, int * y, int morpion[M][M], int grille[N][N]){
    
    float max=-20.0,temp;
    int maxx=0, maxy=0;
    int i,j;

    //cas où on joue où on veut
    if(morpion[xdc%M][ydc%M]!=0){
        //printf("joov\n");
        for(i=0;i<N;i++){
            for(j=0;j<N;j++){

                if(morpion[i%M][j%M]==0){
                    if(grille[i][j]==0){

                        grille[i][j]=joueur;
                        temp=eval_morpion(joueur,morpion,grille);
                        grille[i][j]=0;

                        if(temp>max){
                            max=temp;
                            maxx=i;
                            maxy=j;
                        }
                        else if(temp==max){
                            if(rand()%10<2){
                            max=temp;
                            maxx=i;
                            maxy=j;
                            }
                        }

                        //printf("i=%i j=%i max=%f temp=%f\n",i,j,max,temp);

                    }
                }
            }
        }
    }

    //cas où on joue dans une case spécifique
    else{
        //printf("jduc\n");
        int temp_morpion[M][M];
        predict_rect(xdc,ydc,x,y);

        for(i=0;i<M;i++){
            for(j=0;j<M;j++){
                temp_morpion[i][j]=grille[*x*3+i][*y*3+j];
            }
        }

        for(i=0;i<M;i++){
            for(j=0;j<M;j++){

                    if(temp_morpion[i][j]==0){

                        grille[*x*3+i][*y*3+j]=joueur;
                        temp=eval_morpion(joueur,morpion,grille);
                        grille[*x*3+i][*y*3+j]=0;

                        if(temp>max){
                            max=temp;
                            maxx=*x*3+i;
                            maxy=*y*3+j;
                        }
                        else if(temp==max){
                            if(rand()%10<2){
                            max=temp;
                            maxx=*x*3+i;
                            maxy=*y*3+j;
                            }
                        }

                        //printf("i=%i j=%i max=%f temp=%f\n",i,j,max,temp);

                    }
                }
            }
    }

    *x=maxx;
    *y=maxy;

}

//fait jouer le joueur "joueur" en utilisant une méthode aléatoire (fonction pour tester)
int ia_random_test(int * joueur, int grille[N][N], int morpion[M][M], int * xdc, int * ydc, int * x, int * y){
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
    *x=rdx;
    *y=rdy;
    return 0;
}

//fait jouer le joueur "joueur" en utilisant une méthode aléatoire (fonction pour tester)
int ia_random_var_test(int * joueur, int grille[N][N], int morpion[M][M], int * xdc, int * ydc, int * x, int * y){
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
    *x=rdx;
    *y=rdy;
    return 0;
}