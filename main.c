#include <stdio.h>
#include "file.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char* argv[]){
  // --------------- TRAITEMENT DES PARAMETRES ------------------------

  //on initialise 3 booléens pour la présence du paramètre correspondant
  int c = 0;
  int w = 0;
  int l = 0;

  //on parcours chaque argument
  for(int i = 1; i < argc; i++){
    //cas ou l'argument est un paramètre
    if(argv[i][0] == '-'){
      for(int j = 1; argv[i][j] != '\0'; j++){
	if(argv[i][j] == 'c'){
	  c = 1;
	} else if(argv[i][j] == 'w'){
	  w = 1;
	} else if(argv[i][j] == 'l'){
	  l = 1;
	} else {
	  printf("bad use\n");
	  return -1;
	}
      }
    }
  }
  
  if(c+w+l == 0) {
    c = 1;
    w = 1;
    l = 1;
  }
    
  //------------------------------ EXECUTION ----------------------------
  int tnc = 0;
  int tnw = 0;
  int tnl = 0;

  int fpresent = 0;

  for(int i = 1; i < argc; i++){ 
    if(argv[i][0] != '-'){
      fpresent++;
      int f = open(argv[i],O_RDONLY);
      int nc = 0;
      int nw = 0;
      int nl = 0;
      int success = traiter(f,&nc,&nw,&nl);
      if (success < 0) {
	perror(argv[i]);
      } else {
	printf("%s --- ",argv[i]);
	if(c == 1){
	  printf("caracteres: %d ",nc);
	}
	if(w == 1){
	  printf("mots: %d ",nw);
	}
	if(l == 1){
	  printf("lignes: %d ",nl);
	}
	printf("\n");
	tnc += nc;
	tnw += nw;
	tnl += nl;
      }
    }
  }

  if(fpresent == 0){
    int nc = 0;
    int nw = 0;
    int nl = 0;
    traiter(0,&nc,&nw,&nl);
    printf("Standard --- ");
    if(c == 1){
      printf("caracteres: %d ",nc);
    }
    if(w == 1){
      printf("mots: %d ",nw);
    }
    if(l == 1){
      printf("lignes: %d ",nl);
    }
    printf("\n");
  }
  
  if(fpresent > 1) {
    printf("TOTAL --- ");
    if(c == 1){
      printf("caracteres: %d ",tnc);
    }
    if(w == 1){
      printf("mots: %d ",tnw);
    }
    if(l == 1){
      printf("lignes: %d \n",tnl);
    }
  }
  return 0;
}
