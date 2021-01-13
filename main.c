#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "foncTaquin.h"
#include "affichage.h"

typedef struct parametre {
  int number;
  int spacing;
  int window;
  int replay;
} parametre;

// Récupération des touches avec la sdl :
int recup_touch(taquin *map, int *test_victoire, parametre *p) {
  int output = 1;
  SDL_Event evenement;
  SDL_WaitEvent(&evenement);
  switch (evenement.type) {
  case SDL_QUIT:
    output = 0;
    break;
  case SDL_KEYDOWN:
    switch (evenement.key.keysym.sym) {

      // Déplacement :
    case SDLK_k:
      Deplacement('b', map);
      break;
    case SDLK_j:
      Deplacement('h', map);
      break;
    case SDLK_h:
      Deplacement('d', map);
      break;
    case SDLK_l:
      Deplacement('g', map);
      break;
    case SDLK_UP:
      Deplacement('b', map);
      break;
    case SDLK_DOWN:
      Deplacement('h', map);
      break;
    case SDLK_LEFT:
      Deplacement('d', map);
      break;
    case SDLK_RIGHT:
      Deplacement('g', map);
      break;

      // Autres :
    case SDLK_ESCAPE:
      p->window = (p->window)? 0:1;
      break;
    case SDLK_n:
      p->number = (p->number)? 0:1;
      break;
    case SDLK_s:
      p->spacing = (p->spacing)? 0:1;
      break;      
    case SDLK_t:
      *test_victoire = testVictoire(*map);
      if (*test_victoire)
	output = 0;
      break;
    case SDLK_q:
      *test_victoire = testVictoire(*map);
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
  int taille = 0;
  int mainbool = 1;
  parametre p = {0, 1, 0, 0};
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
    map->nbrCoup = 0;
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

  // Option de fenêtres :
  SDL_WM_SetCaption("DOOM Taquin", NULL);
  SDL_WM_SetIcon(SDL_LoadBMP("./img/Doom_logo.bmp"), NULL);

  
  // Initialisation des surfaces :
  image = SDL_LoadBMP("./img/doom.bmp");
  if (image == NULL){
    fprintf(stderr, "Error: can't open image\n%s\n", SDL_GetError());
    exit(0);
  }
  if (image->h < 300 && image->w < 600) {
    fprintf(stderr, "Error: wrong image size");
  }
  screen = SDL_SetVideoMode(1000, 800, 32, SDL_HWSURFACE);
  if (screen == NULL){
    fprintf(stderr, "Error: screen\n%s\n", SDL_GetError());
    exit(0);
  }

  // Affiche écran de début :
  mainbool = affiche_ecran_debut(screen, image->w, image->h);
 
  while (mainbool) {
    if (!p.window)
      affichage(screen, image, map, p.spacing, p.number);
    else
      affiche_menu_aide(screen);
    mainbool = recup_touch(map, &test_victoire, &p);
  }

  // Ecran de fin :
  if (test_victoire) {
    affiche_fin(screen, map->nbrCoup);
  } else {
    affiche_sauvgarde(screen, map);
  }

  SDL_FreeSurface(image);
  TTF_Quit();
  SDL_Quit();

  for (i = 0; i < map->taille; i++) {
    free(map->tab[i]);
  }
  free(map->tab);
  free(map);

  return 0;
}
