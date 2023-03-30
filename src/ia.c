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

//donne des coordonnées aléatoires en évitant de renvoyer l'adversaire sur une case où il peut jouer où il veut
void ia_random_2(int xdc, int ydc, int * x, int * y, int morpion[M][M], int grille[N][N]){
    
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

//donne des coordonnées aléatoires, en essayant de compléter un morpion quand c'est possible
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

                        //printf("\n");   
                        //afficher_morpion(petit_morpion);
                        //printf("\n");

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

            printf("joiv l & k = %d, %d rdx=%i rdy=%i morpiongagne=%i, cpt1=%i cpt2=%i\n",l, k, k*3+rdx,l*3+rdy,morpiongagne(petit_morpion),cpt,cpt2);

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

            printf("jduc rdx=%i rdy=%i morpiongagne=%i, cpt=%i\n",*x*3+rdx,*y*3+rdy,morpiongagne(petit_morpion),cpt);

        } while(cpt);

        *x=*x*3+rdx;
        *y=*y*3+rdy;

    }

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