#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#include"foncTaquin.h"

//Lire foncTaquin.h pour une explication des différentes fonctions.

void sauvegarde(taquin t)
{
  int num = 0;
  char nomSauvegarde[12];
  FILE * f;
  
  printf("Sauvegarde en cours \n");
  // On crée le nom du fichier.
  sprintf(nomSauvegarde,"sauv_%d.txt",num);

  // On regarde si il existe déjà un fichier portant ce nom.
  while((f = fopen(nomSauvegarde, "r")))
    {
      // Si oui on le ferme et on incrémente le nom de notre fichier.
      fclose(f);
      num++;
      sprintf(nomSauvegarde,"sauv_%d.txt",num);
    }

  // Sinon, on écrit notre tableau du taquin dans ce fichier.
  f = fopen(nomSauvegarde,"w+");
  if(f == NULL)
    {
      perror("ERREUR CREATION FICHIER\n");
      exit(-1);
    }
  
  printf("Sauvegarde du taquin dans le fichier : %s\n",nomSauvegarde);
  
  for (int i = 0;i<t.taille*t.taille;i++)
    {
      fprintf(f,"%d",t.tab[i/t.taille][i%t.taille]);
      if(i%t.taille != t.taille-1)
	{
	  fputc(' ',f);
	}
      else
	{
	  fputc('\n',f);
	}
    }
  //Puis on écrit le nombre de coup.
  fprintf(f,"%d",t.nbrCoup);
  fputc('\n',f);
  fclose(f);
}

taquin * allocTaquin(char * fichier)
{
  //On ouvre le fichier 
  char tempo[150];
  FILE * f = fopen(fichier,"r");
  if(f == NULL)
    {
      perror("ERREUR OUVERTURE FICHIER\n");
      exit(-1);
    }

  // On récupère la taille du taquin en comptant le nombre d'espace. 
  fgets(tempo,150,f);
  int size = 1;
  for(int i = 0;i < (int)strlen(tempo);i++)
    {
      if(tempo[i] == ' ')
	{
	  size++;
	}
    }
  //Si il n'y a pas d'espace (exemple fichier vide), alors on peut être sûr qu'il y a un problème (sinon c'est un taquin de taille 1 ... ce qui est inutile).
  if(size == 1)
    {
      perror("ERREUR IMPOSSIBLE DE CREER UN TAQUIN A PARTIR DE CE FICHIER\n");
      exit(-1);
    }
  rewind(f);

  // On crée le taquin.
  taquin * monTaquin = malloc(sizeof(taquin));
  if(monTaquin == NULL)
    {
      perror("ERREUR CREATION TAQUIN\n");
      exit(-1);
    }
  monTaquin->taille = size; 
  monTaquin->tab = malloc(sizeof(int*)* size);
    if(monTaquin->tab == NULL)
    {
      perror("ERREUR CREATION ARRAY2D\n");
      exit(-1);
    }
  for (int i = 0; i<size;i++)
    {
      monTaquin->tab[i] = malloc(sizeof(int)*size);
      if(monTaquin->tab == NULL)
	{
	  perror("ERREUR CREATION ARRAY (LIGNE)\n");
	  exit(-1);
	}
    }

  // On assigne les variables au taquin
  for(int i = 0; i < size*size;i++)
    {
      fscanf(f,"%d",&monTaquin->tab[i/size][i%size]);
      if(monTaquin->tab[i/size][i%size] == -1)
	{
	  monTaquin->posCaseVide = i;
	}
    }

  // Et le nombre De coup.
  fscanf(f,"%d",&monTaquin->nbrCoup);
  
  fclose(f);
  return(monTaquin);
}


void Deplacement(char c,taquin * t)
{
  int tempo;
  // Ces 2 variables servent juste à rendre le code plus lisible en supprimant tous les "t->"
  int taille = t->taille;
  int posCaseVide = t->posCaseVide;

  // On regarde quel mouvement le joueur veut faire et on regarde si c'est possible
  if(c == 'b' && posCaseVide < taille*taille-taille)
    {
      t->nbrCoup += 1;
      tempo = t->tab[posCaseVide/taille][posCaseVide%taille];
      t->tab[posCaseVide/taille][posCaseVide%taille] = t->tab[posCaseVide/taille+1][posCaseVide%taille];
      t->tab[posCaseVide/taille+1][posCaseVide%taille] = tempo;	
      t->posCaseVide += taille;
    }
  else if (c == 'h' && posCaseVide >= taille)
    {
      t->nbrCoup += 1;
      tempo = t->tab[posCaseVide/taille][posCaseVide%taille];
      t->tab[posCaseVide/taille][posCaseVide%taille] = t->tab[posCaseVide/taille-1][posCaseVide%taille];
      t->tab[posCaseVide/taille-1][posCaseVide%taille] = tempo;
      t->posCaseVide -= taille;
    }
  else if (c == 'd' && posCaseVide % taille != taille-1)
    {
      t->nbrCoup += 1;
      tempo = t->tab[posCaseVide/taille][posCaseVide%taille];
      t->tab[posCaseVide/taille][posCaseVide%taille] = t->tab[posCaseVide/taille][posCaseVide%taille+1];
      t->tab[posCaseVide/taille][posCaseVide%taille+1] = tempo;
      t->posCaseVide ++;
    }
  else if (c == 'g' && posCaseVide % taille != 0)
    {
      t->nbrCoup += 1;
      tempo = t->tab[posCaseVide/taille][posCaseVide%taille];
      t->tab[posCaseVide/taille][posCaseVide%taille] = t->tab[posCaseVide/taille][posCaseVide%taille-1];
      t->tab[posCaseVide/taille][posCaseVide%taille-1] = tempo;
      t->posCaseVide --;
    }
}

taquin * creaAlea(int taille)
{
  taquin * t = malloc(sizeof(taquin));
  if(t == NULL)
    {
      perror("ERREUR CREATION TAQUIN\n");
      exit(-1);
    }
    
  t->taille = taille; 
  t->posCaseVide = taille*taille-1;

  t->tab = malloc(sizeof(int*)* taille);
      if(t->tab == NULL)
    {
      perror("ERREUR CREATION ARRAY2D\n");
      exit(-1);
    }

  // On profite de la création du tableau pour le remplir.
  for (int i = 0; i<taille;i++)
    {
      t->tab[i] = malloc(sizeof(int)*taille);
      if(t->tab == NULL)
	{
	  perror("ERREUR CREATION ARRAY (LIGNE)\n");
	  exit(-1);
	}
      for (int j = 0; j<taille;j++)
	{
	  t->tab[i][j] = i*(taille)+j+1;
	}
    }
  
  t->tab[taille-1][taille-1] = -1;

  // Puis on le mélange  un certain nombre de fois. (vu qu'on mélange beaucoup lorsque la taille est grande au dessus d'une dimension de 28. plus aucun mélange n'est fait).
  int nbr = 20<<taille;
  int alea = 0;
  for (int i = 0;i<nbr;i++)
    {
      alea = rand()%4;
      switch(alea)
	{
	case 0: Deplacement('b',t);break;
	case 1: Deplacement('g',t);break;
	case 2: Deplacement('d',t);break;
	case 3: Deplacement('h',t);break;
	}
    }
  return(t);
}
int testVictoire(taquin t)
{
  // On regarde si à la case 0 on à 1, case 1 on à 2 ... dernière case -1.
  // Puis on retourne 0 si c'est faux, 1 sinon.
  for (int i = 0; i < t.taille*t.taille-1;i++)
    { 
      if (t.tab[i/t.taille][i%t.taille]-1 != i)
	{
	  
	  return 0;
	}	
    }
  if(t.tab[t.taille-1][t.taille-1] != -1)
    {
      return 0;
    }
  return 1;
}
