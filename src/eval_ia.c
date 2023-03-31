#include "../lib/screens.h"
#include "../lib/morpion.h"

//donne le nombre de coups gagnants possible pour le joueur dans le morpion, donne -1 si le morpion est déjà gagné
float nb_coups_gagnants(int joueur, int morpion[M][M]){
    if(!morpiongagne(morpion)){
        
        int i,j,cpt=0;
        
        for(i=0;i<M;i++){
            for(j=0;j<M;j++){
                
                if(morpion[i][j]==0){
                    morpion[i][j]=joueur;
                    if(morpiongagne(morpion)) cpt++;
                    morpion[i][j]=0;
                }

            }
        }

        return (float)cpt;

    }

    else return -1.0;
}

//donne la "valeur stratégique" du morpion de coordonnées (i,j) selon le tableau suivant
// 3 1 3
// 1 2 1
// 3 1 3
float strat_val(int i, int j){
    if(i==1 && j==1) return 2.0;
    else if(i==1 && j!=1) return 1.0;
    else if(i!=1 && j==1) return 1.0;
    else return 3.0;
}

//évalue si la position courante du morpion est favorable pour le joueur, négatif signifie défavorable et positif signifie favorable
float eval_morpion(int joueur, int morpion[M][M], int grille[N][N]){

    float eval_grille[9];
    int temp_morpion[M][M];
    int i,j,n=0,k,l;
    float eval=0.0;
    
    for(i=0;i<M;i++){
        for(j=0;j<M;j++){

            if(morpion[i][j]==joueur){
                eval_grille[n]=strat_val(i,j);
            }

            else if(morpion[i][j]==3-joueur){
                eval_grille[n]=-strat_val(i,j);
            }

            else{

                for(k=0;k<M;k++){
                    for(l=0;l<M;l++){
                        temp_morpion[k][l]=grille[i*3+k][j*3+l];
                    }
                }
                
                if(morpiongagne(temp_morpion)){
                    eval_grille[n]=strat_val(i,j);
                }
                else{
                    eval_grille[n]=strat_val(i,j)*nb_coups_gagnants(joueur,temp_morpion)/5.0-strat_val(i,j)*nb_coups_gagnants(3-joueur,temp_morpion)/5.0;
                }
            }


            n++;
        }
    }


    for(i=0;i<9;i++){
        eval += eval_grille[i];
    }

    return eval;
}