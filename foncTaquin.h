#ifndef FONCTAQUIN_H
#define FONCTAQUIN_H

// Notre structure représentant le taquin (renommée taquin).
typedef struct taquin
{
  // La grille pour le taquin.
  int ** tab;
  // L'emplacement de la case vide.
  int posCaseVide;
  // La taille de notre taquin.
  int taille;
  // Le nombre de coup jusqu'ici.
  int nbrCoup;
  
} taquin;

// Déplace la case vide de notre taquin t dans la direction c.
void Deplacement(char c,taquin * t);

// Sauvegarde le taquin actuelle.
void sauvegarde(taquin t);

// Créer un taquin lorsque qu'on donne le fichier en argument lors de l'exécutable.
taquin * allocTaquin(char * fichier);

// Créer un taquin aléatoire d'une taille donnée.
taquin * creaAlea(int taille);

// Regarde si le taquin t est bien rangé.
int testVictoire(taquin t);

#endif
