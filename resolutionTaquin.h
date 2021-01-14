#ifndef RESOLUTION_H
#define RESOLUTION_H

void deplacerCaseVideVers(taquin * t,int nombre,SDL_Surface * image,SDL_Surface * ecran,int spacing,int number);
void deplacerCaseVideVersGauche(taquin * t,int nombre,SDL_Surface * image,SDL_Surface * ecran,int spacing,int number);
int trouverDansTaquinTrie(taquin t,int nombre);
void resolution(taquin * t,SDL_Surface * image,SDL_Surface * ecran,int spacing,int number);
void deplacementV2(char c,taquin * t,SDL_Surface * image,SDL_Surface * ecran,int spacing,int number);

#endif 
