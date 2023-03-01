#include "../lib/morpion.h"
#include "../lib/sauvegarde.h"
#include "../lib/screens.h"

void morpion_term (int, option_t);

void menu_term (option_t * opt){
    char res ;

    system("clear");

    printf("Bienvenue dans le morpion fractal !\n\n");
    printf("1 - Commencer une nouvelle partie.\n");
    printf("2 - Charger une partie d'une précédente sauvegarde.\n");
    printf("3 - Options.\n");
    printf("4 - Quitter :(\n");

    res = getchar();
    while (getchar() != '\n'); //On vide le buffer.

    switch (res){
        case '1' : morpion_term(0, *opt); break ;
        case '2' : morpion_term(1, *opt); break ;
        case '3' : option(opt); break ;
        case '4' : free (opt); exit(0); break ;
        default : 
            printf("Saisie invalide.") ;
    }

    menu_term(opt);
}

int main (int argc, char * argv[]){
    option_t * opt = malloc(sizeof(option_t));
    opt->autosave = 1 ;
    menuscreen();
    return 0;
}
