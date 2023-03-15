#include "../lib/morpion.h"
#include "../lib/sauvegarde.h"

int main(){

    int grille[N][N];
    int morpion[M][M];
    int x, y, x1, y1 ;

    printf("============ Début du test pour les fonctions init_grille & init_morpion\n");
    printf("Grille avant init :\n");
    afficher_grille(grille);
    init_grille(grille);
    printf("Grille après init :\n");
    afficher_grille(grille);
    printf("\nMorpion avant init :\n");
    afficher_morpion(morpion);
    init_morpion(morpion);
    printf("Morpion après init :\n");
    afficher_morpion(morpion);



    printf("\n\n\n============ Début du test pour les fonctions morpiongagne\n");
    printf("Test avec morpion =\n");
    afficher_morpion(morpion);
    printf("Le retour est : %d\n", morpiongagne(morpion));

    printf("Test avec morpion =\n");
    morpion[0][0] = 1 ;
    morpion[1][1] = 1 ;
    morpion[2][2] = 1 ;
    afficher_morpion(morpion);
    printf("Le retour est : %d\n", morpiongagne(morpion));

    printf("Test avec morpion =\n");
    morpion[0][0] = 2 ;
    morpion[0][1] = 2 ;
    morpion[0][2] = 2 ;
    afficher_morpion(morpion);
    printf("Le retour est : %d\n", morpiongagne(morpion));

    printf("Test avec morpion =\n");
    init_morpion(morpion);
    morpion[0][0] = 1 ;
    morpion[1][0] = 1 ;
    morpion[2][0] = 1 ;
    afficher_morpion(morpion);
    printf("Le retour est : %d\n", morpiongagne(morpion));

    printf("Test avec morpion =\n");
    morpion[0][0] = 2 ;
    morpion[1][1] = 1 ;
    morpion[1][2] = 2 ;
    afficher_morpion(morpion);
    printf("Le retour est : %d\n", morpiongagne(morpion));


    printf("\n\n\n============ Début du test pour les fonctions coog_to_carr\n");
    for (int i = 0 ; i < M ; i++){
        for (int j = 0 ; j < M ; j++){
            morpion[i][j] = i * 3 + j ;
        }
    }
    printf("On considère les numéros des carrés suivants :\n");
    afficher_morpion(morpion);
    printf("La fonction renvoie le numéro du carré dans lequel le joueur a joué, ou -1 s'il y a une erreur (x ou y non compris entre 0 et 8).\n\n");
    x = 0 ; y = 0 ; 
    printf("Retour de la fonction pour x = %d et y = %d : %d\n", x, y, coog_to_carr(x, y));
    x = 0 ; y = 3 ; 
    printf("Retour de la fonction pour x = %d et y = %d : %d\n", x, y, coog_to_carr(x, y));
    x = 0 ; y = 6; 
    printf("Retour de la fonction pour x = %d et y = %d : %d\n", x, y, coog_to_carr(x, y));
    x = 3 ; y = 0 ; 
    printf("Retour de la fonction pour x = %d et y = %d : %d\n", x, y, coog_to_carr(x, y));
    x = 3 ; y = 3 ; 
    printf("Retour de la fonction pour x = %d et y = %d : %d\n", x, y, coog_to_carr(x, y));
    x = 3 ; y = 6; 
    printf("Retour de la fonction pour x = %d et y = %d : %d\n", x, y, coog_to_carr(x, y));
    x = 6 ; y = 0 ; 
    printf("Retour de la fonction pour x = %d et y = %d : %d\n", x, y, coog_to_carr(x, y));
    x = 6 ; y = 3 ; 
    printf("Retour de la fonction pour x = %d et y = %d : %d\n", x, y, coog_to_carr(x, y));
    x = 6 ; y = 6; 
    printf("Retour de la fonction pour x = %d et y = %d : %d\n", x, y, coog_to_carr(x, y));
    x = 3 ; y = 5 ; 
    printf("Retour de la fonction pour x = %d et y = %d : %d\n", x, y, coog_to_carr(x, y));
    x = 7 ; y = 3 ; 
    printf("Retour de la fonction pour x = %d et y = %d : %d\n", x, y, coog_to_carr(x, y));
    x = 8 ; y = 8 ; 
    printf("Retour de la fonction pour x = %d et y = %d : %d\n", x, y, coog_to_carr(x, y));
    x = 0 ; y = -1 ; 
    printf("Retour de la fonction pour x = %d et y = %d : %d\n", x, y, coog_to_carr(x, y));
    x = 'a' ; y = 0 ; 
    printf("Retour de la fonction pour x = %d et y = %d : %d\n", x, y, coog_to_carr(x, y));


    printf("\n\n\n============ Début du test pour les fonctions check_carre\n");
    init_grille(grille);
    init_morpion(morpion);

    grille[0][0] = 1 ;
    grille[1][1] = 1 ;
    grille[2][2] = 1 ;
    x = 2 ; y = 2 ;
    printf("Coordonnées du dernier coup joué : (%d, %d).\nGrille passée en paramètre :\n", x, y);
    afficher_grille(grille);
    printf("Morpion passé en paramètre :\n");
    afficher_morpion(morpion);
    printf("Réponse de la fonction : %d\nMorpion après l'appel :\n", check_carre(grille, morpion, x, y));
    afficher_morpion(morpion);

    grille[3][0] = 2 ;
    grille[3][1] = 2 ;
    grille[3][2] = 2 ;
    x = 3 ; y = 2 ;
    printf("Coordonnées du dernier coup joué : (%d, %d).\nGrille passée en paramètre :\n", x, y);
    afficher_grille(grille);
    printf("Morpion passé en paramètre :\n");
    afficher_morpion(morpion);
    printf("Réponse de la fonction : %d\nMorpion après l'appel :\n", check_carre(grille, morpion, x, y));
    afficher_morpion(morpion);

    grille[4][0] = 1 ;
    grille[4][1] = 1 ;
    grille[4][2] = 1 ;
    x = 4 ; y = 2 ;
    printf("Coordonnées du dernier coup joué : (%d, %d).\nGrille passée en paramètre :\n", x, y);
    afficher_grille(grille);
    printf("Morpion passé en paramètre :\n");
    afficher_morpion(morpion);
    printf("Réponse de la fonction : %d\nMorpion après l'appel :\n", check_carre(grille, morpion, x, y));
    afficher_morpion(morpion);
    printf("Le premier joueur à gagner une case la conserve (notamment dans le cadre de la variante). Le résultat ici est donc normal.\n");

    grille[6][0] = 2 ;
    grille[7][1] = 2 ;
    grille[8][1] = 2 ;
    x = 8 ; y = 1 ;
    printf("Coordonnées du dernier coup joué : (%d, %d).\nGrille passée en paramètre :\n", x, y);
    afficher_grille(grille);
    printf("Morpion passé en paramètre :\n");
    afficher_morpion(morpion);
    printf("Réponse de la fonction : %d\nMorpion après l'appel :\n", check_carre(grille, morpion, x, y));
    afficher_morpion(morpion);



    printf("\n\n\n============ Début du test pour les fonctions predict_rect\n");
    x = 0, y = 0 ;
    predict_rect(x, y, &x1, &y1);
    printf("Si le dernier coup joué est (%d,%d), le prochain devra jouer le carré (%d,%d) du morpion.\n", x, y, x1, y1);
    x = 0, y = 1 ;
    predict_rect(x, y, &x1, &y1);
    printf("Si le dernier coup joué est (%d,%d), le prochain devra jouer le carré (%d,%d) du morpion.\n", x, y, x1, y1);
    x = 0, y = 2 ;
    predict_rect(x, y, &x1, &y1);
    printf("Si le dernier coup joué est (%d,%d), le prochain devra jouer le carré (%d,%d) du morpion.\n", x, y, x1, y1);
    x = 1, y = 0 ;
    predict_rect(x, y, &x1, &y1);
    printf("Si le dernier coup joué est (%d,%d), le prochain devra jouer le carré (%d,%d) du morpion.\n", x, y, x1, y1);
    x = 1, y = 1 ;
    predict_rect(x, y, &x1, &y1);
    printf("Si le dernier coup joué est (%d,%d), le prochain devra jouer le carré (%d,%d) du morpion.\n", x, y, x1, y1);
    x = 1, y = 2 ;
    predict_rect(x, y, &x1, &y1);
    printf("Si le dernier coup joué est (%d,%d), le prochain devra jouer le carré (%d,%d) du morpion.\n", x, y, x1, y1);
    x = 2, y = 0 ;
    predict_rect(x, y, &x1, &y1);
    printf("Si le dernier coup joué est (%d,%d), le prochain devra jouer le carré (%d,%d) du morpion.\n", x, y, x1, y1);
    x = 2, y = 1 ;
    predict_rect(x, y, &x1, &y1);
    printf("Si le dernier coup joué est (%d,%d), le prochain devra jouer le carré (%d,%d) du morpion.\n", x, y, x1, y1);
    x = 2, y = 2 ;
    predict_rect(x, y, &x1, &y1);
    printf("Si le dernier coup joué est (%d,%d), le prochain devra jouer le carré (%d,%d) du morpion.\n", x, y, x1, y1);
    x = 4, y = 7 ;
    predict_rect(x, y, &x1, &y1);
    printf("Si le dernier coup joué est (%d,%d), le prochain devra jouer le carré (%d,%d) du morpion.\n", x, y, x1, y1);
    x = 8, y = 2 ;
    predict_rect(x, y, &x1, &y1);
    printf("Si le dernier coup joué est (%d,%d), le prochain devra jouer le carré (%d,%d) du morpion.\n", x, y, x1, y1);
    x = 8, y = 8 ;
    predict_rect(x, y, &x1, &y1);
    printf("Si le dernier coup joué est (%d,%d), le prochain devra jouer le carré (%d,%d) du morpion.\n", x, y, x1, y1);

    return 0;
}