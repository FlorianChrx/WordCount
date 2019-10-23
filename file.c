#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#define TAILLE 80

int traiter(int f, int* c, int* mot, int* lig){
  //chaine servant de buffer
  char str[TAILLE];
  //resultat de la lecture d'une zone de texte
  int rsread = 0;

  //initialisation à 0 des compteurs
  *c = 0;
  *mot = 0;
  *lig = 0;

  //première lecture
  rsread = read(f, str, TAILLE);

  //parcours par buffer
  while(rsread != 0){
    //si la lecture a echoué on quitte la fonction
    if(rsread <= -1) return -1;

    //on ajoute autant de caractères que de caractères présents
    //dans le buffer
    (*c)+=rsread;

    //on demarre le parcours du buffer
    for(int i = 0; i < rsread; ++i){
      //si le caractère lu est un espace on ajoute un mot
      //ATTENTION A NE PAS OUBLIER D'EN AJOUTER UN APRES TRAITEMENT #1
      //car nbMots = nbEspaces + 1
      if(isspace(c[i])) (*mot)++;
      if(c[i]=='\n') (*lig)++;
    }
    rsread = read(f, str, TAILLE);
  }
  (*mot)++;
  return 0;
}
