#include "../lib/sauvegarde.h"

/*Sauvegarde la grille dans un fichier.
Prends en paramètre le fichier de sauvegarde, la grille de la partie, 
et le joueur à qui sera le prochain tour.*/
void save (char * name, int grille[N][N], int morpion[M][M], int joueur, int xdc, int ydc){
    FILE * slot = fopen(name, "w");
    int i, j ;

    for (i = 0 ; i < N ; i++){
        for (j = 0 ; j < N ; j++){
            fprintf(slot, "%d", grille[i][j]);
        }
    }

    fprintf(slot, "%d", joueur);
    fprintf(slot, "%d", xdc);
    fprintf(slot, "%d", ydc);

    for (i = 0 ; i < M ; i++){
        for (j = 0 ; j < M ; j++){
            fprintf(slot, "%d", morpion[i][j]);
        }
    }

    fclose(slot);

}

/*Charge une sauvegarde à partir d'un fichier.
Prends en paramètre le fichier source, la grille et l'adresse du prochain joueur.*/
void load (char * name, int grille[N][N], int morpion[M][M], int * joueur, int * xdc, int * ydc){
    FILE * slot = fopen(name, "r");
    int i, j ;
    char c[92] ;

    if (slot == NULL){ //On vérifie que le fichier a été trouvé.
        printf("Aucune sauvegarde trouvée.");
        return;
    }

    fscanf(slot, "%s \n", c);

    for (i = 0 ; i < N ; i++){
        for (j = 0 ; j < N ; j++){
            switch (c[i*N+j]){
                case '0' : grille[i][j] = 0 ; break ;
                case '1' : grille[i][j] = 1 ; break ;
                case '2' : grille[i][j] = 2 ; break ;
                default : printf("Erreur\n");
            } 
        }
    }

    switch (c[81]){ //Le prochain joueur est indiqué au 82ème caractère.
        case '1' : *joueur = 1 ; break ;
        case '2' : *joueur = 2 ; break ;
        default : printf("Erreur\n");
    }

    switch (c[82]){ //Le xdc est indiqué au 83ème caractère.
        case '0' : *xdc = 0 ; break ;
        case '1' : *xdc = 1 ; break ;
        case '2' : *xdc = 2 ; break ;
        case '3' : *xdc = 3 ; break ;
        case '4' : *xdc = 4 ; break ;
        case '5' : *xdc = 5 ; break ;
        case '6' : *xdc = 6 ; break ;
        case '7' : *xdc = 7 ; break ;
        case '8' : *xdc = 8 ; break ;
        default : printf("Erreur\n");
    }


    switch (c[83]){ //Le ydc est indiqué au 83ème caractère.
        case '0' : *ydc = 0 ; break ;
        case '1' : *ydc = 1 ; break ;
        case '2' : *ydc = 2 ; break ;
        case '3' : *ydc = 3 ; break ;
        case '4' : *ydc = 4 ; break ;
        case '5' : *ydc = 5 ; break ;
        case '6' : *ydc = 6 ; break ;
        case '7' : *ydc = 7 ; break ;
        case '8' : *ydc = 8 ; break ;
        default : printf("Erreur\n");
    }

    for (i = 0 ; i < M ; i++){
        for (j = 0 ; j < M ; j++){
            switch (c[84 + i*M + j]){
                case '0' : morpion[i][j] = 0 ; break ;
                case '1' : morpion[i][j] = 1 ; break ;
                case '2' : morpion[i][j] = 2 ; break ;
                default : printf("Erreur\n");
            } 
        }
    }

    fclose(slot);
}

