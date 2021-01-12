#ifndef _AFF_
#define _AFF_

// Fonction de récupération des touches pour l'écran de début et de fin
int attend_touche();

// Affichage de l'écran de début :
int affiche_ecran_debut(SDL_Surface *screen, int w, int h);

// Demande à l'utilisateur si il souhaite sauvegarder :
void affiche_sauvgarde(SDL_Surface *screen, taquin *map);

// Afichage du tableau avec la sdl :
void affichage(SDL_Surface * screen, SDL_Surface * image, taquin *map, int
spacing, int number);

// Affichage du menu :
void affiche_menu_aide(SDL_Surface *screen);

// Affichage de l'écran de victoire avec le nombre de coup :
void affiche_fin(SDL_Surface *screen, int nb_coup);


#endif
