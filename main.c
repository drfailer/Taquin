#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "foncTaquin.h"
#include "affichage.h"


// Récupération des touches avec la sdl :
int recup_touch(taquin *map, int *test_victoire, int *nb_coup) {
  int output = 1;
  SDL_Event evenement;
  SDL_WaitEvent(&evenement);
  switch (evenement.type) {
  case SDL_QUIT:
    output = 0;
    break;
  case SDL_KEYDOWN:
    switch (evenement.key.keysym.sym) {
    case SDLK_k:
      Deplacement('b', map);
      *nb_coup += 1;
      break;
    case SDLK_j:
      Deplacement('h', map);
      *nb_coup += 1;
      break;
    case SDLK_h:
      Deplacement('d', map);
      *nb_coup += 1;
      break;
    case SDLK_l:
      Deplacement('g', map);
      *nb_coup += 1;
      break;
    case SDLK_UP:
      Deplacement('b', map);
      *nb_coup += 1;
      break;
    case SDLK_DOWN:
      Deplacement('h', map);
      *nb_coup += 1;
      break;
    case SDLK_LEFT:
      Deplacement('d', map);
      *nb_coup += 1;
      break;
    case SDLK_RIGHT:
      Deplacement('g', map);
      *nb_coup += 1;
      break;
    case SDLK_ESCAPE:
      *test_victoire = testVictoire(*map);
      output = 0;
      break;
    case SDLK_t:
      *test_victoire = testVictoire(*map);
      if (*test_victoire)
	output = 0;
      break;
    default:
      break;
    }
  default:
    break;
  }
  return output;
}


int main(int argc, char *argv[])
{
  int i;
  int taille;
  int nb_coup = 0;
  int mainbool = 1;
  int test_victoire = 0;
  SDL_Surface *image = NULL;
  SDL_Surface *screen = NULL;
  taquin *map = NULL;

  // Initialisation de la structure taquin :
  if (argc != 1) {
    map = allocTaquin(argv[1]); 
  } else {
    printf("Entrez une taille pour la génération aléatoire:\n");
    scanf("%d", &taille);
    map = creaAlea(taille);
  }
  if(map == NULL) {
    fprintf(stderr, "Error: map\n");
    exit(0);
  }

  // Initialisation de la sdl et sdl_ttf :
  if (SDL_Init(SDL_INIT_VIDEO) == -1) {
    fprintf(stderr, "%s", SDL_GetError());
    exit(0);
  }
  if (TTF_Init() == -1) {
    fprintf(stderr, "Error: %s\n", TTF_GetError());
    exit(0);
  }

  // TODO: window name and icon :
  SDL_WM_SetCaption("taquin", NULL);

  
  // Initialisation des surfaces :
  image = SDL_LoadBMP("./img/linux.bmp");
  if (image == NULL){
    fprintf(stderr, "Error: can't open image\n%s\n", SDL_GetError());
    exit(0);
  }
  screen = SDL_SetVideoMode(image->w, image->h, 32, SDL_HWSURFACE);
  if (screen == NULL){
    fprintf(stderr, "Error: screen\n%s\n", SDL_GetError());
    exit(0);
  }

  // Affiche écran de début :
  mainbool = affiche_ecran_debut(screen, image->w, image->h);

  while (mainbool) {
    affichage(screen, image, map);
    mainbool = recup_touch(map, &test_victoire, &nb_coup);
  }

  // Ecran de fin :
  if (test_victoire) {
    affiche_fin(screen, nb_coup);
  } else {
    affiche_sauvgarde(screen, map);
  }

  TTF_Quit();
  SDL_Quit();
  SDL_FreeSurface(image);

  for (i = 0; i < map->taille; i++) {
    free(map->tab[i]);
  }
  free(map->tab);
  free(map);

  return 0;
}
