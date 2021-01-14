#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <SDL/SDL.h>
#include"foncTaquin.h"
#include "affichage.h"
#include"resolutionTaquin.h"

void deplacerCaseDuDessusVers(taquin * t,int posDeLaCase,int i,SDL_Surface * image,SDL_Surface * ecran,int spacing,int number)
{
  if(posDeLaCase/t->taille == t->taille-1)
    {
      deplacerCaseVideVers(t,posDeLaCase - t->taille,image,ecran,spacing,number);
      deplacementV2('b',t,image,ecran,spacing,number);
      posDeLaCase -= t->taille;
    }
  else
    {
      deplacerCaseVideVers(t,posDeLaCase + t->taille,image,ecran,spacing,number);
    }
  while(posDeLaCase != i)
    {
      printf("BOUCLE RESOLUTION %d et %d\n",posDeLaCase,i);
      if(posDeLaCase%t->taille > i%t->taille)
	{
	  deplacementV2('g',t,image,ecran,spacing,number);
	  deplacementV2('h',t,image,ecran,spacing,number);
	  deplacementV2('d',t,image,ecran,spacing,number);
	  deplacementV2('b',t,image,ecran,spacing,number); 
	  deplacementV2('g',t,image,ecran,spacing,number);
	  posDeLaCase--;
	}
      else if(posDeLaCase%t->taille < i%t->taille)
	{
	  deplacementV2('d',t,image,ecran,spacing,number);
	  deplacementV2('h',t,image,ecran,spacing,number);
	  deplacementV2('g',t,image,ecran,spacing,number);
	  deplacementV2('b',t,image,ecran,spacing,number);
	  deplacementV2('d',t,image,ecran,spacing,number);
	  posDeLaCase++;
	}
      else if(posDeLaCase/t->taille > i/t->taille && posDeLaCase%t->taille != t->taille-1)
	{
	  deplacementV2('d',t,image,ecran,spacing,number);
	  deplacementV2('h',t,image,ecran,spacing,number);
	  deplacementV2('h',t,image,ecran,spacing,number);
	  deplacementV2('g',t,image,ecran,spacing,number);
	  deplacementV2('b',t,image,ecran,spacing,number);
	  posDeLaCase-=t->taille;
	}
      else if(posDeLaCase/t->taille > i/t->taille && posDeLaCase%t->taille == t->taille-1)
	{
	  deplacementV2('g',t,image,ecran,spacing,number);
	  deplacementV2('h',t,image,ecran,spacing,number);
	  deplacementV2('h',t,image,ecran,spacing,number);
	  deplacementV2('d',t,image,ecran,spacing,number);
	  deplacementV2('b',t,image,ecran,spacing,number);
	  posDeLaCase-=t->taille;
	}
      else if(posDeLaCase/t->taille < i/t->taille && posDeLaCase%t->taille == t->taille-1)
	{
	  deplacementV2('h',t,image,ecran,spacing,number);
	  deplacementV2('g',t,image,ecran,spacing,number);
	  deplacementV2('b',t,image,ecran,spacing,number);
	  deplacementV2('b',t,image,ecran,spacing,number);
	  deplacementV2('d',t,image,ecran,spacing,number);
	  posDeLaCase+=t->taille;
	}
      else if(posDeLaCase/t->taille < i/t->taille && posDeLaCase%t->taille != t->taille-1)
	{
	  deplacementV2('h',t,image,ecran,spacing,number);
	  deplacementV2('d',t,image,ecran,spacing,number);
	  deplacementV2('b',t,image,ecran,spacing,number);
	  deplacementV2('b',t,image,ecran,spacing,number);
	  deplacementV2('g',t,image,ecran,spacing,number);
	  posDeLaCase+=t->taille;
	}
    }
  
}


void deplacerCaseDeGaucheVers(taquin * t,int posDeLaCase,int i,SDL_Surface * image,SDL_Surface * ecran,int spacing,int number)
{
  if(posDeLaCase%t->taille == t->taille-1)
    { 
      deplacerCaseVideVersGauche(t,posDeLaCase-1,image,ecran,spacing,number);
      deplacementV2('d',t,image,ecran,spacing,number);
      posDeLaCase --;
    }
  else
    {
      deplacerCaseVideVersGauche(t,posDeLaCase + 1,image,ecran,spacing,number);
    }
  while(posDeLaCase != i)
    {
      printf("BOUCLE RESOLUTION GAUCHE %d et %d\n",posDeLaCase,i);
      if(posDeLaCase/t->taille > i/t->taille)
	{
	  deplacementV2('h',t,image,ecran,spacing,number);
	  deplacementV2('g',t,image,ecran,spacing,number);
	  deplacementV2('b',t,image,ecran,spacing,number);
	  deplacementV2('d',t,image,ecran,spacing,number);
	  deplacementV2('b',t,image,ecran,spacing,number);
	  posDeLaCase+=t->taille;
	}
      else if(posDeLaCase/t->taille < i/t->taille)
	{
	  deplacementV2('b',t,image,ecran,spacing,number);
	  deplacementV2('g',t,image,ecran,spacing,number);
	  deplacementV2('h',t,image,ecran,spacing,number);
	  deplacementV2('d',t,image,ecran,spacing,number);
	  deplacementV2('b',t,image,ecran,spacing,number);
	  posDeLaCase+=t->taille;
	}
		    
      else if(posDeLaCase%t->taille > i%t->taille && posDeLaCase/t->taille == t->taille-1)
	{
	  printf("LIGNE DU BAS\n");
	  deplacementV2('h',t,image,ecran,spacing,number);
	  deplacementV2('g',t,image,ecran,spacing,number);
	  deplacementV2('g',t,image,ecran,spacing,number);
	  deplacementV2('b',t,image,ecran,spacing,number);
	  deplacementV2('d',t,image,ecran,spacing,number);
	  posDeLaCase--;
	}
      else if(posDeLaCase%t->taille > i%t->taille && posDeLaCase/t->taille == t->taille-2)
	{
	  printf("LIGNE DU HAUT\n");	  
	  deplacementV2('b',t,image,ecran,spacing,number);
	  deplacementV2('g',t,image,ecran,spacing,number);
	  deplacementV2('g',t,image,ecran,spacing,number);
	  deplacementV2('h',t,image,ecran,spacing,number);
	  deplacementV2('d',t,image,ecran,spacing,number);
	  posDeLaCase--;
	}
        else if(posDeLaCase%t->taille < i%t->taille && posDeLaCase/t->taille == t->taille-1)
	{
	  printf("RECUL LIGNE DU BAS\n");
	  deplacementV2('g',t,image,ecran,spacing,number);
	  deplacementV2('h',t,image,ecran,spacing,number);
	  deplacementV2('d',t,image,ecran,spacing,number);
	  deplacementV2('d',t,image,ecran,spacing,number);
	  deplacementV2('b',t,image,ecran,spacing,number);
	  posDeLaCase++;
	}
      else if(posDeLaCase%t->taille < i%t->taille && posDeLaCase/t->taille == t->taille-2)
	{
	  printf("RECUL LIGNE DU HAUT\n");	  
	  deplacementV2('g',t,image,ecran,spacing,number);
	  deplacementV2('b',t,image,ecran,spacing,number);
	  deplacementV2('d',t,image,ecran,spacing,number);
	  deplacementV2('d',t,image,ecran,spacing,number);
	  deplacementV2('h',t,image,ecran,spacing,number);
	  posDeLaCase++;
	}
    }
}
  
void deplacerCaseVideVers(taquin * t,int nombre,SDL_Surface * image,SDL_Surface * ecran,int spacing,int number)
{
  if(t->posCaseVide%t->taille == nombre%t->taille)
    {
      printf("DEPLACEMENT POUR NE PAS CHANGER LA POSITION DU NOMBRE VISE\n");
      if(t->posCaseVide%t->taille == t->taille-1)
	{
	  deplacementV2('g',t,image,ecran,spacing,number);
	}
      else
	{
	  deplacementV2('d',t,image,ecran,spacing,number);
	}
    }
  while(t->posCaseVide != nombre)
    {
      printf("BOUCLE DEPLACEMENT %d et %d\n",t->posCaseVide,nombre);
      if(t->posCaseVide / t->taille > nombre/t->taille)
	{
	  deplacementV2('h',t,image,ecran,spacing,number);
	}
      else if (t->posCaseVide / t->taille < nombre/t->taille)
	{
	  deplacementV2('b',t,image,ecran,spacing,number);
	}
      else if (t->posCaseVide > nombre)
	{
	  deplacementV2('g',t,image,ecran,spacing,number);
	}
      else if (t->posCaseVide < nombre)
	{
	  deplacementV2('d',t,image,ecran,spacing,number);
	}
    }
}
void deplacerCaseVideVersGauche(taquin * t,int nombre,SDL_Surface * image,SDL_Surface * ecran,int spacing,int number)
{
  if(t->posCaseVide / t->taille == nombre/t->taille)
    {
      printf("DEPLACEMENT POUR NE PAS CHANGER LA POSITION DU NOMBRE VISE\n");
      if(t->posCaseVide/t->taille == t->taille-2)
	{
	  deplacementV2('b',t,image,ecran,spacing,number);
	}
      else
	{
	  deplacementV2('h',t,image,ecran,spacing,number);
	}
    }
  while(t->posCaseVide != nombre)
    {
      printf("BOUCLE DEPLACEMENT %d et %d\n",t->posCaseVide,nombre);
      if (t->posCaseVide%t->taille > nombre%t->taille)
	{
	  deplacementV2('g',t,image,ecran,spacing,number);
	}
      else if (t->posCaseVide%t->taille < nombre%t->taille)
	{
	  deplacementV2('d',t,image,ecran,spacing,number);
	}
      else if(t->posCaseVide / t->taille > nombre/t->taille)
	{
	  deplacementV2('h',t,image,ecran,spacing,number);
	}
      else if (t->posCaseVide / t->taille < nombre/t->taille)
	{
	  deplacementV2('b',t,image,ecran,spacing,number);
	}

    }
}

int trouverDansTaquinTrie(taquin t,int nombre)
{
  for (int i = 0; i < t.taille*t.taille;i++)
    {
      if (t.tab[i/t.taille][i%t.taille] == nombre)
	{
	  return i;
	}
    }
  return -1;
}

void deplacementV2(char c,taquin * t,SDL_Surface * image,SDL_Surface * ecran,int spacing,int number)
{
  Deplacement(c,t);
  affichage(ecran, image,t,spacing,number);

}

void resolution(taquin * t,SDL_Surface * image,SDL_Surface * ecran,int spacing,int number)
{
  int posDeLaCase;
  for (int i = 0; i < t->taille*(t->taille-2);i++)
    {
      posDeLaCase = trouverDansTaquinTrie(*t,i+1);
      if((posDeLaCase != i && i%t->taille < t->taille-2) || i%t->taille >= t->taille-2)
	{
	  printf("POUR I = %d\n",i);
	  if(i%t->taille < t->taille-2)
	    {
	      deplacerCaseDuDessusVers(t,posDeLaCase,i,image,ecran,spacing,number);
	    }
	  else if(i%t->taille == t->taille-2)
	    {
	      int posAutreCase = trouverDansTaquinTrie(*t,i+2);
	      if(posAutreCase == i+1)
		{
		  printf("\n\nMOUVEMENT NECESSAIRE POUR LA CASE %d\n\n",i+1);
		   deplacerCaseVideVers(t,posAutreCase -1,image,ecran,spacing,number);
		   deplacementV2('d',t,image,ecran,spacing,number);
		}
	      deplacerCaseDuDessusVers(t,posDeLaCase,i+1,image,ecran,spacing,number);
	    }
	  else if(i%t->taille == t->taille-1)
	    {
	      deplacerCaseDuDessusVers(t,posDeLaCase,i+t->taille,image,ecran,spacing,number);
	      deplacementV2('g',t,image,ecran,spacing,number);
	      deplacementV2('h',t,image,ecran,spacing,number);
	      deplacementV2('h',t,image,ecran,spacing,number);
	      deplacementV2('d',t,image,ecran,spacing,number);
	      deplacementV2('b',t,image,ecran,spacing,number);
	      
	      
	    }
	}
    }
  for (int i =  t->taille*(t->taille-2); i <  t->taille*(t->taille-2)+t->taille-2;i++)
    {
      printf("POUR I = %d\n",i);
      posDeLaCase = trouverDansTaquinTrie(*t,i+1);
      deplacerCaseDeGaucheVers(t,posDeLaCase,i+t->taille,image,ecran,spacing,number);
      int posAutreCase = trouverDansTaquinTrie(*t,i+t->taille+1);
      if(posAutreCase == i+t->taille || posAutreCase == i+1+t->taille )
	{
	  printf("\n\nMOUVEMENT NECESSAIRE POUR LA CASE %d\n\n",i+t->taille);
	  deplacerCaseVideVersGauche(t,posAutreCase-t->taille,image,ecran,spacing,number);
	  deplacementV2('b',t,image,ecran,spacing,number);
	}
      if(posAutreCase == i+1+t->taille && posDeLaCase == i)
	{
	   printf("\n\n\n\nMOUVEMENT NECESSAIRE POUR LA CASE %d\n\n\n\n\n",i+t->taille);
	   deplacerCaseVideVers(t,posAutreCase+1,image,ecran,spacing,number);
	   deplacementV2('g',t,image,ecran,spacing,number);
	   
	}
    
      printf("POUR I = %d\n",i+t->taille);
      posDeLaCase =  trouverDansTaquinTrie(*t,i+1+t->taille);
      deplacerCaseDeGaucheVers(t,posDeLaCase,i+t->taille+1,image,ecran,spacing,number);
      deplacementV2('h',t,image,ecran,spacing,number);
      deplacementV2('g',t,image,ecran,spacing,number);
      deplacementV2('g',t,image,ecran,spacing,number);
      deplacementV2('b',t,image,ecran,spacing,number);
      deplacementV2('d',t,image,ecran,spacing,number);
      if(trouverDansTaquinTrie(*t,i+1+t->taille) != i+t->taille || trouverDansTaquinTrie(*t,i+1)!= i)
	{
	  deplacementV2('g',t,image,ecran,spacing,number);
	  deplacementV2('h',t,image,ecran,spacing,number);
	  deplacementV2('d',t,image,ecran,spacing,number);
	  deplacementV2('d',t,image,ecran,spacing,number);
	  deplacementV2('b',t,image,ecran,spacing,number);
	  deplacementV2('g',t,image,ecran,spacing,number);
	  i--;

	}
    }
  deplacementV2('d',t,image,ecran,spacing,number);
  while(!testVictoire(*t))
    {
      deplacementV2('h',t,image,ecran,spacing,number);
      deplacementV2('g',t,image,ecran,spacing,number);
      deplacementV2('b',t,image,ecran,spacing,number);
      deplacementV2('d',t,image,ecran,spacing,number);
    }
  sleep(5);
}
  

