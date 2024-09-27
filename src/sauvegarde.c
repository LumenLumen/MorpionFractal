#include "../lib/sauvegarde.h"

/**
    \file sauvegarde.c
    \brief Fonctions qui gèrent la sauvegarde ou le chargement de partie.
    \author Groupe morpion fractal
    \version 1
    \date 9 février 2023
*/

/**
    \fn void save (char * name, int grille[N][N], int morpion[M][M], int joueur, int xdc, int ydc, int var)
    \brief fonction qui sauvegarde la grille dans un fichier.
    \param name nom du fichier de sauvegarde
    \param grille matrice 9*9
    \param morpion matrice 3*3
    \param joueur joueur dont ce sera le tour au chargement de la partie
    \param xdc abscisse dernier coup joué
    \param ydc ordonnée dernier coup joué
    \param var VRAI si on joue selon les règles de la variante, sinon FAUX.
*/
void save (char * name, int grille[N][N], int morpion[M][M], int joueur, int xdc, int ydc, int var){
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

    fprintf(slot, "%d", var);

    fclose(slot);

}

/**
    \fn int load (char * name, int grille[N][N], int morpion[M][M], int * joueur, int * xdc, int * ydc, int * var)
    \brief fonction qui charge la grille d'un fichier.
    \param name nom du fichier de sauvegarde
    \param grille matrice 9*9
    \param morpion matrice 3*3
    \param joueur pointeur vers le joueur dont ce sera le tour au chargement de la partie
    \param xdc pointeur vers abscisse dernier coup joué
    \param ydc pointeur vers ordonnée dernier coup joué
    \param var pointeur vers la variable qui indique si on joue en variante ou non.
    \return 0 si échoue, 1 si succès.
*/
int load (char * name, int grille[N][N], int morpion[M][M], int * joueur, int * xdc, int * ydc, int * var){
    FILE * slot = fopen(name, "r");
    int i, j ;
    char c[93] ;

    if (slot == NULL){ //On vérifie que le fichier a été trouvé.
        printf("Aucune sauvegarde trouvée.\n");
        return 0;
    }

    fscanf(slot, "%s \n", c);
    if (strlen(c) != 94){ //On vérifie la longueur du fichier
        printf("Fichier invalide.\n");
        return 0;
    }

    for (i = 0 ; i < N ; i++){
        for (j = 0 ; j < N ; j++){
            switch (c[i*N+j]){
                case '0' : grille[i][j] = 0 ; break ;
                case '1' : grille[i][j] = 1 ; break ;
                case '2' : grille[i][j] = 2 ; break ;
                default : printf("Erreur\n"); return 0;
            } 
        }
    }

    switch (c[81]){ //Le prochain joueur est indiqué au 82ème caractère.
        case '1' : *joueur = 1 ; break ;
        case '2' : *joueur = 2 ; break ;
        default : printf("Erreur\n"); return 0;
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
        default : printf("Erreur\n"); return 0;
    }


    switch (c[83]){ //Le ydc est indiqué au 84ème caractère.
        case '0' : *ydc = 0 ; break ;
        case '1' : *ydc = 1 ; break ;
        case '2' : *ydc = 2 ; break ;
        case '3' : *ydc = 3 ; break ;
        case '4' : *ydc = 4 ; break ;
        case '5' : *ydc = 5 ; break ;
        case '6' : *ydc = 6 ; break ;
        case '7' : *ydc = 7 ; break ;
        case '8' : *ydc = 8 ; break ;
        default : printf("Erreur\n"); return 0;
    }

    for (i = 0 ; i < M ; i++){
        for (j = 0 ; j < M ; j++){
            switch (c[84 + i*M + j]){
                case '0' : morpion[i][j] = 0 ; break ;
                case '1' : morpion[i][j] = 1 ; break ;
                case '2' : morpion[i][j] = 2 ; break ;
                default : printf("Erreur\n"); return 0;
            } 
        }
    }

    switch (c[93]){ //Si la variante est activée.
        case '0' : *var = 0 ; break ;
        case '1' : *joueur = 1 ; break ;
        default : printf("Erreur\n"); return 0;
    }    

    fclose(slot);
    return 1 ;
}

