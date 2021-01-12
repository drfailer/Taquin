#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "foncTaquin.h"


// Fonction de récupération des touches pour l'écran de début et de fin
int attend_touche() {
  int output = 1;
  int bool = 1;
  SDL_Event evenement;
  while (bool) {
    SDL_WaitEvent(&evenement);
    switch (evenement.type) {
    case SDL_QUIT:
      bool = 0;
      output = 0;
      break;
    case SDL_KEYDOWN:
      bool = 0;
      break;
    default:
      break;
    }
  }
  return output;
}


// Affichage de l'écran de début :
int affiche_ecran_debut(SDL_Surface *screen) {
  int output = 1;
  SDL_Surface *texte = NULL;
  SDL_Rect text_pos;

  // Chargement de l'image contenant le texte :
  texte = SDL_LoadBMP("./img/start.bmp");
  if (texte == NULL) {
    fprintf(stderr, "%s\n", SDL_GetError());
    exit(0);
  }
  text_pos.y = (screen->h - texte->h)/2;
  text_pos.x = (screen->w - texte->w)/2;
  
  SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 30, 33, 39));
  SDL_BlitSurface(texte, NULL, screen, &text_pos);
  SDL_Flip(screen);
  output = attend_touche();

  SDL_FreeSurface(texte);
  
  return output;
}


// Demande à l'utilisateur si il souhaite sauvegarder :
void affiche_sauvgarde(SDL_Surface *screen, taquin *map) {
  int bool = 1;
  SDL_Event evenement;
  SDL_Surface *texte = NULL;
  SDL_Rect text_pos;
  
  // Chargement de l'image contenant le texte :
  texte = SDL_LoadBMP("./img/save.bmp");
  if (texte == NULL) {
    fprintf(stderr, "%s\n", SDL_GetError());
    exit(0);
  }

  SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 30, 33, 39));
  
  // Collage de l'image avec le texte de victoire :
  text_pos.y = (screen->h - texte->h)/2 - 18;
  text_pos.x = (screen->w - texte->w)/2;
  SDL_BlitSurface(texte, NULL, screen, &text_pos);
  SDL_Flip(screen);

  while (bool) {
    SDL_WaitEvent(&evenement);
    switch (evenement.type) {
    case SDL_QUIT:
      bool = 0;
      break;
    case SDL_KEYDOWN:
      switch (evenement.key.keysym.sym) {
      case SDLK_y:
	sauvegarde(*map);
	bool = 0;
	break;
      default:
	bool = 0;
	break;
      }
      break;
    default:
      break;
    }
  }

  SDL_FreeSurface(texte);
}


// Afichage du tableau avec la sdl :
void affichage(SDL_Surface * screen, SDL_Surface * image, taquin *map, int spacing, int number) {
  int i, j;
  int h = image->h / map->taille;
  int w = image->w / map->taille;
  char number_str[4];
  SDL_Rect pos_on_image;
  pos_on_image.w = w;
  pos_on_image.h = h;
  SDL_Rect pos_on_screen;

  // Permet d'afficher les nombres :
  SDL_Surface *texte_nombre = NULL;
  TTF_Font *police = NULL;
  SDL_Color color = {0, 0, 0, 255};
  if (number) {
    police = TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeMonoBold.ttf", 10);
    if (police == NULL) {
      fprintf(stderr, "Error: %s\n", TTF_GetError());
    }
  }

  // Remplie l'ecran de gris
  SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 30, 33, 39));

  for (i = 0; i < map->taille; i++) {
    for (j = 0; j < map->taille; j++) {

      if (map->tab[i][j] != -1) {
	
	// Position de la partie de l'image à blitter sur l'écran :
	pos_on_screen.x = j * w + spacing*j;
	pos_on_screen.y = i * h + spacing*i;
	// Partie de l'image à blitter :
	pos_on_image.x = ((map->tab[i][j] - 1)%map->taille) * w;
	pos_on_image.y = ((map->tab[i][j] - 1)/map->taille) * h;

	// Colle la partie de l'image correspondant au numéro inscrit dans la
	// case du tableau :
	SDL_BlitSurface(image, &pos_on_image, screen, &pos_on_screen);

	if (number) {
	  sprintf(number_str, "%d", map->tab[i][j]);
	  texte_nombre = TTF_RenderText_Blended(police, number_str, color);
	  SDL_BlitSurface(texte_nombre, NULL, screen, &pos_on_screen);
	}	
      }      
    }
  }
  
  if (police != NULL)
    TTF_CloseFont(police);
  if (texte_nombre != NULL)
    SDL_FreeSurface(texte_nombre);
  
  SDL_Flip(screen);
}


// Affichage du menu :
void affiche_menu_aide(SDL_Surface *screen) {
  SDL_Surface *texte = NULL;
  SDL_Rect text_pos;

  // Chargement de l'image contenant le texte :
  texte = SDL_LoadBMP("./img/menu_aide.bmp");
  if (texte == NULL) {
    fprintf(stderr, "%s\n", SDL_GetError());
    exit(0);
  }
  text_pos.y = (screen->h - texte->h)/2;
  text_pos.x = (screen->w - texte->w)/2;
  
  SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 30, 33, 39));
  SDL_BlitSurface(texte, NULL, screen, &text_pos);
  SDL_Flip(screen);

  SDL_FreeSurface(texte);
}


// Affichage de l'écran de victoire avec le nombre de coup :
void affiche_fin(SDL_Surface *screen, int nb_coup) {
  char nb_coup_str[25];
  SDL_Surface *texte = NULL;
  SDL_Rect text_pos;
  TTF_Font *police = NULL;
  SDL_Color color = {255, 255, 255, 255};
  
  // Conversion de nb_coup en string :
  sprintf(nb_coup_str, "Nombre de coup: %d", nb_coup);

  // Chargement de la police :
  police = TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeMonoBold.ttf", 18);
  if (police == NULL) {
    fprintf(stderr, "Error: %s\n", TTF_GetError());
  }
  
  // Chargement de l'image contenant le texte :
  texte = SDL_LoadBMP("./img/win.bmp");
  if (texte == NULL) {
    fprintf(stderr, "%s\n", SDL_GetError());
    exit(0);
  }

  SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 30, 33, 39));
  
  // Collage de l'image avec le texte de victoire :
  text_pos.y = (screen->h - texte->h)/2 - 18;
  text_pos.x = (screen->w - texte->w)/2;
  SDL_BlitSurface(texte, NULL, screen, &text_pos);

  // Ajout du nombre de coups :
  text_pos.y = (screen->h - texte->h)/2 + texte->h;
  texte = TTF_RenderText_Blended(police, nb_coup_str, color);
  text_pos.x = (screen->w - texte->w)/2;
  SDL_BlitSurface(texte, NULL, screen, &text_pos);
  
  SDL_Flip(screen);
  attend_touche();
  
  TTF_CloseFont(police);
  SDL_FreeSurface(texte);
}
