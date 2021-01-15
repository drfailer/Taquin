#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <SDL/SDL.h>
#include"foncTaquin.h"
#include "affichage.h"
#include"resolutionTaquin.h"

// Va suivre une combinaison de mouvement pour déplacer la case au dessus de la case vide et ceux jusqu'à une position i.
void deplacerCaseDuDessusVers(taquin * t,int posDeLaCase,int i,SDL_Surface * image,SDL_Surface * ecran,int spacing,int number)
{
  //Si notre case que l'on veut bouger se situe sur la ligne de fin , il nous faut bouger cette casse une ligne au dessus pour pouvoir placer la case vide
  if(posDeLaCase/t->taille == t->taille-1)
    {
      deplacerCaseVideVers(t,posDeLaCase - t->taille,image,ecran,spacing,number);
      deplacementV2('b',t,image,ecran,spacing,number);
      posDeLaCase -= t->taille;
    }
  else
    {
      // Sinon on place la case vide directement en dessous
      deplacerCaseVideVers(t,posDeLaCase + t->taille,image,ecran,spacing,number);
    }
  //Tant qu'on a pas atteint la case voulu on continue 
  while(posDeLaCase != i)
    {
      //si notre case est trop à droite
      if(posDeLaCase%t->taille > i%t->taille)
	{
	  deplacementV2('g',t,image,ecran,spacing,number);
	  deplacementV2('h',t,image,ecran,spacing,number);
	  deplacementV2('d',t,image,ecran,spacing,number);
	  deplacementV2('b',t,image,ecran,spacing,number); 
	  deplacementV2('g',t,image,ecran,spacing,number);
	  posDeLaCase--;
	}
      //si notre case est trop à gauche
      else if(posDeLaCase%t->taille < i%t->taille)
	{
	  deplacementV2('d',t,image,ecran,spacing,number);
	  deplacementV2('h',t,image,ecran,spacing,number);
	  deplacementV2('g',t,image,ecran,spacing,number);
	  deplacementV2('b',t,image,ecran,spacing,number);
	  deplacementV2('d',t,image,ecran,spacing,number);
	  posDeLaCase++;
	}
      //si notre case est trop bas (et pas collé tout à droite)
      else if(posDeLaCase/t->taille > i/t->taille && posDeLaCase%t->taille != t->taille-1)
	{
	  deplacementV2('d',t,image,ecran,spacing,number);
	  deplacementV2('h',t,image,ecran,spacing,number);
	  deplacementV2('h',t,image,ecran,spacing,number);
	  deplacementV2('g',t,image,ecran,spacing,number);
	  deplacementV2('b',t,image,ecran,spacing,number);
	  posDeLaCase-=t->taille;
	}
      //si notre case est trop bas (et collé tout à droite)
      else if(posDeLaCase/t->taille > i/t->taille && posDeLaCase%t->taille == t->taille-1)
	{
	  deplacementV2('g',t,image,ecran,spacing,number);
	  deplacementV2('h',t,image,ecran,spacing,number);
	  deplacementV2('h',t,image,ecran,spacing,number);
	  deplacementV2('d',t,image,ecran,spacing,number);
	  deplacementV2('b',t,image,ecran,spacing,number);
	  posDeLaCase-=t->taille;
	}
      // Il n'a normalement pas besoin de mouvement pour aller en bas sauf pour un certain cas qui va nous forcer à reconstruire quelques cases qui était pourtant bien placé
      else if(posDeLaCase/t->taille < i/t->taille && posDeLaCase%t->taille != t->taille-1)
	{
	  deplacementV2('h',t,image,ecran,spacing,number);
	  deplacementV2('d',t,image,ecran,spacing,number);
	  deplacementV2('b',t,image,ecran,spacing,number);
	  deplacementV2('b',t,image,ecran,spacing,number);
	  deplacementV2('g',t,image,ecran,spacing,number);
	  posDeLaCase+=t->taille;
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
    }
  
}

// Même principer que la fonction deplacerCaseDuDessusVers cependant cette fois ci la case vide est situé à droite de la case que l'on veut bouger
void deplacerCaseDeGaucheVers(taquin * t,int posDeLaCase,int i,SDL_Surface * image,SDL_Surface * ecran,int spacing,int number)
{
  // Si notre case est collé au bord droit, on doit la bouger
  if(posDeLaCase%t->taille == t->taille-1)
    { 
      deplacerCaseVideVersGauche(t,posDeLaCase-1,image,ecran,spacing,number);
      deplacementV2('d',t,image,ecran,spacing,number);
      posDeLaCase --;
    }
  // Sinon on va placer directement notre case à droite
  else
    {
      deplacerCaseVideVersGauche(t,posDeLaCase + 1,image,ecran,spacing,number);
    }
  //Tant que la case n'est pas à l'endroit voulu
  while(posDeLaCase != i)
    {
      // Si notre case est trop base
      if(posDeLaCase/t->taille > i/t->taille)
	{
	  deplacementV2('h',t,image,ecran,spacing,number);
	  deplacementV2('g',t,image,ecran,spacing,number);
	  deplacementV2('b',t,image,ecran,spacing,number);
	  deplacementV2('d',t,image,ecran,spacing,number);
	  deplacementV2('b',t,image,ecran,spacing,number);
	  posDeLaCase+=t->taille;
	}
      // Si notre case est trop haut
      else if(posDeLaCase/t->taille < i/t->taille)
	{
	  deplacementV2('b',t,image,ecran,spacing,number);
	  deplacementV2('g',t,image,ecran,spacing,number);
	  deplacementV2('h',t,image,ecran,spacing,number);
	  deplacementV2('d',t,image,ecran,spacing,number);
	  deplacementV2('b',t,image,ecran,spacing,number);
	  posDeLaCase+=t->taille;
	}
      // Si notre case est trop à gauche (et sur la ligne du bas)
      else if(posDeLaCase%t->taille > i%t->taille && posDeLaCase/t->taille == t->taille-1)
	{
	  deplacementV2('h',t,image,ecran,spacing,number);
	  deplacementV2('g',t,image,ecran,spacing,number);
	  deplacementV2('g',t,image,ecran,spacing,number);
	  deplacementV2('b',t,image,ecran,spacing,number);
	  deplacementV2('d',t,image,ecran,spacing,number);
	  posDeLaCase--;
	}
      // Si notre case est trop à gauche (et sur la ligne du haut)
      else if(posDeLaCase%t->taille > i%t->taille && posDeLaCase/t->taille == t->taille-2)
	{	  
	  deplacementV2('b',t,image,ecran,spacing,number);
	  deplacementV2('g',t,image,ecran,spacing,number);
	  deplacementV2('g',t,image,ecran,spacing,number);
	  deplacementV2('h',t,image,ecran,spacing,number);
	  deplacementV2('d',t,image,ecran,spacing,number);
	  posDeLaCase--;
	}
      // Normalement pas besoin de mouvement pour reculer, mais dans certains cas
      else if(posDeLaCase%t->taille < i%t->taille && posDeLaCase/t->taille == t->taille-1)
	{
	  deplacementV2('g',t,image,ecran,spacing,number);
	  deplacementV2('h',t,image,ecran,spacing,number);
	  deplacementV2('d',t,image,ecran,spacing,number);
	  deplacementV2('d',t,image,ecran,spacing,number);
	  deplacementV2('b',t,image,ecran,spacing,number);
	  posDeLaCase++;
	}
      // Si notre case est trop à gauche (et sur la ligne du haut)
      else if(posDeLaCase%t->taille < i%t->taille && posDeLaCase/t->taille == t->taille-2)
	{	  
	  deplacementV2('g',t,image,ecran,spacing,number);
	  deplacementV2('b',t,image,ecran,spacing,number);
	  deplacementV2('d',t,image,ecran,spacing,number);
	  deplacementV2('d',t,image,ecran,spacing,number);
	  deplacementV2('h',t,image,ecran,spacing,number);
	  posDeLaCase++;
	}
      
      
    }
}

// Cette fonction décale la case vide pour jusqu'à une case nombre donnée.
void deplacerCaseVideVers(taquin * t,int nombre,SDL_Surface * image,SDL_Surface * ecran,int spacing,int number)
{
  // Si la case vide est sur la même colonne que la case visé, on peut potentiellement la bouger lors de notre mouvement, pour éviter ce problème on décale d'une colonne notre case vide.
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
  // Tant que la case n'est pas à l'endroit voulu
  while(t->posCaseVide != nombre)
    {
      // Si la case est trop bas
      if(t->posCaseVide / t->taille > nombre/t->taille)
	{
	  deplacementV2('h',t,image,ecran,spacing,number);
	}
      // Si la case est trop haut
      else if (t->posCaseVide / t->taille < nombre/t->taille)
	{
	  deplacementV2('b',t,image,ecran,spacing,number);
	}
      // Si la case est trop à droite
      else if (t->posCaseVide > nombre)
	{
	  deplacementV2('g',t,image,ecran,spacing,number);
	}
      // Si la case est trop à gauche
      else if (t->posCaseVide < nombre)
	{
	  deplacementV2('d',t,image,ecran,spacing,number);
	}
    }
}

//Même principe que deplacerCaseVide, cependant dans celui ci on commencer à bouger la case vide horizontalement puis verticalement
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

// Retourne la position de la position de la pièce de rang nombre
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

// Une fonction qui va Déplacer,afficher puis attendre un petit moment (très rapide pour les taquins de dimension > 10)
void deplacementV2(char c,taquin * t,SDL_Surface * image,SDL_Surface * ecran,int spacing,int number)
{
  Deplacement(c,t);
  affichage(ecran, image,t,spacing,number);
  usleep(4000);
}

// Fonction qui va résoudre notre taquin (! ne marche pas pour les taquins de taille 3)
void resolution(taquin * t,SDL_Surface * image,SDL_Surface * ecran,int spacing,int number)
{
  int posDeLaCase;
  // Pour toutes les lignes (sauf les 2 dernières)
  for (int i = 0; i < t->taille*(t->taille-2);i++)
    {
      // On récupère la position de la case
      posDeLaCase = trouverDansTaquinTrie(*t,i+1);
      
      // Si notre case n'est pas déjà placé ou qu'elle fait partie des deux dernières colonnes
      if((posDeLaCase != i && i%t->taille < t->taille-2) || i%t->taille >= t->taille-2)
	{
	  printf("POUR I = %d\n",i);
	  //Si notre case n'est pas l'une composant les deux dernières colonnes
	  if(i%t->taille < t->taille-2)
	    {
	      // On la place directement à sa position
	      deplacerCaseDuDessusVers(t,posDeLaCase,i,image,ecran,spacing,number);
	    }
	  // Si elle fait partie de l'avant dernière colonne
	  else if(i%t->taille == t->taille-2)
	    {
	      // On place notre case à droite de sa bonne position
	      deplacerCaseDuDessusVers(t,posDeLaCase,i+1,image,ecran,spacing,number);
	    }
	  // Si la case compose la dernière colonne
	  else if(i%t->taille == t->taille-1)
	    {
	      // On la place en bas de sa bonne position
	      deplacerCaseDuDessusVers(t,posDeLaCase,i+t->taille,image,ecran,spacing,number);
	      
	      // Puis on effectue une suite de mouvement pour ranger en un seul coup cette case et la case précédente.
	       
	      deplacementV2('g',t,image,ecran,spacing,number);
	      deplacementV2('h',t,image,ecran,spacing,number);
	      deplacementV2('h',t,image,ecran,spacing,number);
	      deplacementV2('d',t,image,ecran,spacing,number);
	      deplacementV2('b',t,image,ecran,spacing,number);

	      // Il se peut dans certains cas que l'une de nos cases soit légerement décalé avec cette méthode (si lorsque on veut positionner la case de la derniere colonne on doit pousser la case de l'avant derniere), il va donc falloir un peu les repousser puis recommencer.
	      int probleme = 0;
	      for (int j = i-t->taille;j<i;j++)
		{
		  if (trouverDansTaquinTrie(*t,j+1)!= j)
		    {
		      printf("PROBLEME\n");
		      probleme = 1;
		    }
		}
	      if(probleme == 1)
		{
		  printf("RESOLUTION\n");
		  deplacementV2('b',t,image,ecran,spacing,number);
		  deplacementV2('g',t,image,ecran,spacing,number);
		  deplacementV2('h',t,image,ecran,spacing,number);
		  deplacementV2('d',t,image,ecran,spacing,number);
		  deplacementV2('h',t,image,ecran,spacing,number);
		  deplacementV2('g',t,image,ecran,spacing,number);
		  deplacementV2('b',t,image,ecran,spacing,number);
		  deplacementV2('d',t,image,ecran,spacing,number);
		  deplacementV2('b',t,image,ecran,spacing,number);
		  deplacementV2('g',t,image,ecran,spacing,number);
		  deplacementV2('h',t,image,ecran,spacing,number);
		  deplacementV2('d',t,image,ecran,spacing,number);
		  deplacementV2('b',t,image,ecran,spacing,number);
		  i-= i%t->taille;
		  probleme = 0;
		}
	      
	    }
	}
    }
  // Pour les deux dernières lignes (sans les 4 dernières cases).
  for (int i =  t->taille*(t->taille-2); i <  t->taille*(t->taille-2)+t->taille-2;i++)
    {
      printf("POUR I = %d\n",i);
      //On effectue de la même façon que la boucle précédente mais cette fois-ci en remplissant les colonnes en plaçant la case du dessus en bas de sa position originelle, 
      posDeLaCase = trouverDansTaquinTrie(*t,i+1);
      deplacerCaseDeGaucheVers(t,posDeLaCase,i+t->taille,image,ecran,spacing,number);

      printf("POUR I = %d\n",i+t->taille);
      
      //la case du bas à droite de sa position originelle
      posDeLaCase =  trouverDansTaquinTrie(*t,i+1+t->taille);
      
      // Puis on effectue une suite de mouvement pour placer les 2 au bon endroit
      deplacerCaseDeGaucheVers(t,posDeLaCase,i+t->taille+1,image,ecran,spacing,number);
      deplacementV2('h',t,image,ecran,spacing,number);
      deplacementV2('g',t,image,ecran,spacing,number);
      deplacementV2('g',t,image,ecran,spacing,number);
      deplacementV2('b',t,image,ecran,spacing,number);
      deplacementV2('d',t,image,ecran,spacing,number);
      
      //De même dans certains cas la fonction ne marche pas du premier coup.
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
  // On remet notre case vide tout en  bas à droite du tableau
  deplacementV2('d',t,image,ecran,spacing,number);

  //Maintenant il ne reste plus qu'à tourner nos 4 dernières cases jusqu'à tomber sur la bonne combinaison
  for(int i = 0;i<3;i++)
    {
      deplacementV2('h',t,image,ecran,spacing,number);
      deplacementV2('g',t,image,ecran,spacing,number);
      deplacementV2('b',t,image,ecran,spacing,number);
      deplacementV2('d',t,image,ecran,spacing,number);
      if(testVictoire(*t))
	{
	  break;
	}
    }
  sleep(5);
}
  

