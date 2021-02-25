#include "prog.h"

/**
 *
 *          <  LOGICIEL DE CODAGE version 2.1  >
 *
 *
 *  Commande de compilation du programme:
 *          make
 *  Commande d'exécution du projet:
 *          ./codage
 *
 *
 *  Cette deuxième version du projet permet à l'utilisateur plusieurs
 *  fonctionnalitées, en effet elle lui permet d'utiliser en premier lieu la
 *  version 1.1, en plus de cela coder une chiane de char en bianre ou un fichier
 *  Et enfin lui permettre le décoder ce fichier.
 */

int main(int argc, char const *argv[]) {
  printf("+------------------------------------------------+\n");
  printf("|    * BIENVENUE DANS LE LOGICIEL DE CODAGE *    |\n");
  printf("+------------------------------------------------+\n");

  int menu = affichage_menu_pricipale();   /** afficher le menu pricipal */
  do {
    switch (menu) {
      case 1: system("resize -s 20 110");
              system("clear");
              prog_1();   /** version 1.1 du projet */
              printf("\n                  FIN\n\n");
              menu = affichage_menu_pricipale();
        break;
      case 2: system("resize -s 20 110");
              system("clear");
              prog_2();   /** coder une chaine de char */
              printf("\n                  FIN\n\n");
              menu = affichage_menu_pricipale();
        break;
      case 3: system("resize -s 20 110");
              system("clear");
              prog_3();   /** coder un fichier en binaire */
              viderBuffer();  /** vider le buffer */
              printf("\n                  FIN\n\n");
              menu = affichage_menu_pricipale();
        break;
      case 4: system("resize -s 20 110");
              system("clear");
              prog_4();   /** décoder un fichier.cds en fichier.dcd */
              viderBuffer();  /** vider le buffer */
              printf("\n                  FIN\n\n");

              menu = affichage_menu_pricipale();
        break;
    }
    if(menu == 5) {       /** Quitter le logiciel */
      printf("Fermeture du logiciel ...\n");
      return EXIT_SUCCESS;
    }
  }
  while (menu != 6);

  return EXIT_SUCCESS;
}
