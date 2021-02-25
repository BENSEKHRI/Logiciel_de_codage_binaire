#include "prog.h"


/**
 *  Ce fichier contient toutes les fontions utiliser dans le main pricipal
 *  Ces diverses fonctions permettront à l'utilisateur plus de fonctionnalitées
 *  et ainsi exécuter plusieurs programmes complexes en même temps.
 */


/** Definitions des fonctions utilisateur */

/**
 *  Cette fonction permet de vider le buffer.
 *  ALGO: On lit dans le buffer char par char grâce à getchar. On se contente
 *        de récupérer c le int. On boucle tant qu'on n'a pas récupéré le
 *        caractère \n et le symbole EOF (fin de fichier), qui signifient
 *        tous deux l'arrivé à la fin du buffer, on arrete la boucle dé que l'on
 *        tombe sur l'un des deux.
 *  BUT:  Vider le buffer.
 */
void viderBuffer () {
  int c = 0;
  while (c != '\n' && c != EOF) {
    c = getchar();
  }
}

/**
 *  Cette fonction permet de à l'utilisateur a saisi d'un char sans la récupération
 *  de '\n'.
 *  ALGO: La fonction lire va appeler fgets et, si tout s'est bien passé, elle va
 *        rechercher le caractère \n à l'aide de la fonction strchr. Si un \n
 *        est trouvé, elle le remplace par un \0 (fin de chaîne) pour éviter de
 *        conserver une « Entrée ». ET on fait appel a la fonction viderBuffer
 *        dans deux cas si la chaine est tros long ou bien nous avons rencontré
 *        une erreure.
 *  BUT:  permettre la une saisie sécurisée.
 *
 * @param chaine la chaine qui stocke la saisi de l'utilisateur.
 * @param longueur la longueur de chaine.
 * @return 1 si la saisi à été réussi par succés, 0 sinon.
 */
int lire(char *chaine, int longueur) {
  char *positionEntree = NULL;

  if (fgets(chaine, longueur, stdin) != NULL) {
    positionEntree = strchr(chaine, '\n');
    if (positionEntree != NULL) {
        *positionEntree = '\0';
    }
    else {
        viderBuffer();
    }
    return 1;
  }
  else {
    viderBuffer();
    return 0;
  }
}

/**
 *  Cette fonction permet convertir une chaine en long.
 *  ALGO: appel de la fonction lire et ensuite de la fonction strtol qui permet
 *        la conversion d'une chaine de char en long et enfin on return le res.
 *  BUT:  Avoir un nombre au lieu d'une chaine de char.
 *
 * @return le long résultat de la conversion.
 */
long lireLong () {
  char nombreTexte[100] = {0};

  if (lire(nombreTexte, 100)) {
    return strtol(nombreTexte, NULL, 10);
  }
  else {
      return 0;
  }
}

/**
 *  Cette fonction permet d'afficher le menu principale du logiciel et de
 *  demander le choix de l'utilisateur et stocker son chois dans la variable
 *  menu.
 *  NB: Si l'utilisateur entre un nombre autre que les nombre possible il lui
 *      redamnde à nouveau la saisi de son choix.
 *
 * @return le chois de l'utilisateur.
 */
int affichage_menu_pricipale () {
  long menu = 0;
  printf("  +------------------- MENU -------------------+\n");
  printf("  |  1 --- Coder des caractères (version 1.1)  |\n");
  printf("  |  2 --- Coder une chaine de caractère       |\n");
  printf("  |  3 --- Coder un fichier ordinaire en .cds  |\n");
  printf("  |  4 --- Decoder un fichier .cds en .cdc     |\n");
  printf("  |  5 --- Quitter                             |\n");
  printf("  +--------------------------------------------+\n");

  do {
    printf("                    -> ");
    menu = lireLong();
  }
  while ((menu != 1) && (menu != 2) && (menu != 3) && (menu != 4) && (menu != 5));

  return menu;
}

/**
 *  Cette fonction permet à l'utilisateur d'exécuter le programme de la version 1.1
 */
void prog_1 () {
  printf("Vous avez choisi de < coder des caractères (version 1.1) >\n\n");

  /** Initialisation et impréssion du tas */
  tas* tasCodage = saisie_alphabet();
  printf("Voici le tas initial:\n");
  imprimer_tas(tasCodage);


  /** Initialisation et impréssion de l'arbre de codage */
  node* arbreDeCodage = creer_arbre(tasCodage);
  printf("\nVoici l'arbre de codage:\n");
  imprimer_arbre(arbreDeCodage);


  /** Impréssion du code */
  printf("\n\nVoici le codage binaire de votre alphabet: \n");
  /** initialisation de la chaine où écrire le code */
  char* s = (char*)malloc(N*sizeof(char));
  if(s == NULL) {
    printf("Erreur allocation mémoire by prog_1 in main.c\n");
    exit(0);  /** on arrete immédiatement le programme */
  }
  else
    imprimer_codes_complet (arbreDeCodage, s, 0);


  /** libération de la mémoire allouée */
  free(s);
  liberer_memoire_tas(tasCodage);
  supprimer_arbre(arbreDeCodage);
}

/**
 *  Cette fonction permet à l'utilisateur d'exécuter un programme qui permet de
 *  codé une chaine de char.
 *  NB: Il ne faudra pas que la chaine ait un espace. "Sinon le programme tous
 *      entier s'arrete".
 */
void prog_2 () {
  /** CHOIX */
  printf("Vous avez choisi de < Coder une chaine de caractère > \n\n");

  /** Allocation mémoires */
  char* aideScan = (char*) malloc(N*sizeof(char));    /** éviter de récupérer le '\n' de scanf */
  char* chaine = (char*) malloc(T*sizeof(char));
  char* alphabet = (char*) malloc(T*sizeof(char));
  int* tabFreq = (int*)malloc(T*sizeof(int));
  char* s = (char*) malloc(T*sizeof(char));
  char* codeBinaire = (char*) malloc(T*sizeof(char));

  /** teste de réussite des allocation */
  if(chaine == NULL || alphabet == NULL || tabFreq == NULL || s == NULL || codeBinaire == NULL || aideScan == NULL) {
    printf("Erreur allocation mémoire by prog_2 in main.c\n");
    exit(0);  /** on arrete immédiatement le programme */
  }


  /** la saisi de la chiane de caractère par l'utilisateur à coder */
  printf("Donner la chaine de caractres que vous voulez coder en binaire:\n");
  printf("   -> ");
  fgets(chaine, T, stdin);
  int taille = strlen(chaine);
  chaine[taille-1] = '\0';

  /** trouver l'alphabet de la chaine et la fréquence de chaque char */
  alphabet_chaine(chaine, alphabet);
  freq_alphabet_fichier(chaine, alphabet, tabFreq);


  /** création et impression du tas, de l'arbre de codage et des codes des char */
  tas* tasCodage = creer_tas(alphabet, tabFreq);
  printf("\nVoici le tas initial:\n");
  imprimer_tas(tasCodage);
  node* arbreDeCodage = creer_arbre(tasCodage);
  printf("Voici l'arbre de Codage:\n");
  imprimer_arbre(arbreDeCodage);
  printf("\nVoici le code des caractères:\n");
  imprimer_codes_complet(arbreDeCodage, s, 0);


  /** codage de la chaine */
  coder_chaine (arbreDeCodage, chaine, codeBinaire);
  printf("\nCodage ...\n");
  printf("%s = %s\n", chaine, codeBinaire);


  /** libération des mémoires alloués */
  free(aideScan);
  free(chaine);
  free(s);
  free(alphabet);
  free(codeBinaire);
  free(tabFreq);
  liberer_memoire_tas(tasCodage);
  supprimer_arbre(arbreDeCodage);
}

/**
 *  Cette fonction permet à l'utilisateur d'exécuter le programme qui lui permet
 *  de coder un fichier en binaire.
 */
void prog_3 () {
  /** CHOIX */
  printf("Vous avez choisi de < Coder un fichier ordinaire en .cds >\n\n");

  /** Allocation de mémoire pour le chemin du fichier à compresser */
  char* chemin = (char*) malloc(sizeof(char));

  /** teste de réussite de l'allocation de mémoire */
  if((chemin == NULL)) {
    printf("Erreur Allocation mémoire in prog_4 by main.c\n");
    exit(0);  /** on arrete immédiatement le programme */
  }

  /** Saisi du chemin du fichier */
  printf("Entrez le chemin de votre fichier à coder: ");
  scanf("%s", chemin);

  /** Essai d'ouverture et teste de réussite d'ouverture du fichier */
  FILE* fichier = fopen (chemin, "r");

  /** Si le fichier n'est pas ouvert ou il est deja codé */
  while ((fichier == NULL) || test_extension_cds(chemin)) {
    printf("\n     ! Erreur dans l'ouverture de <%s> !\n\n", chemin);
    printf("Entrez le chemin de votre fichier à coder: ");
    scanf("%s", chemin);
    fichier = fopen (chemin, "r");
  }
  rewind(fichier);

  int n = nombre_caracteres_fichier(fichier);
  char* fichierToChaine = (char*) malloc(n*T*sizeof(char));
  trans_fichier_chaine(fichier, fichierToChaine);
  if(strlen(fichierToChaine) == 0) {
    printf("\n\t   Le fichier est vide.\n");
    fclose(fichier);
  }
  else {
    /** codage et Fermeture du fichier */
    coder_fichier(fichier, chemin); /** création du fichier Compression */
    rewind(fichier);
    fclose(fichier);
  }

  /** libération de la mémoire allouée */
  free(chemin);
  free(fichierToChaine);
}


/**
 *  Cette fonction permet à l'utilisateur de décoder un fichier coder par ce
 *  Logiciel.
 */
void prog_4 () {
  /** CHOIX */
  printf("Vous avez choisi de < Decoder un fichier .cds en .cdc >\n\n");

  /** allocations mémoires */
  char* chemincode = (char*) malloc(T*sizeof(char));
  char* chemindecode = (char*) malloc(T*sizeof(char));
  char* radicalCheminCode = (char*) malloc(T*sizeof(char));
  char* radicalCheminDecode = (char*) malloc(T*sizeof(char));

  /** Test de réussite des allocations mémoires */
  if((chemincode == NULL) || (chemindecode == NULL) || (radicalCheminCode == NULL) || (radicalCheminDecode == NULL)) {
    printf("Erreur Allocation mémoire in prog_5 by main.c\n");
    exit(0);  /** on arrete immédiatement le programme */
  }

  /** Saisi du chemin du fichier */
  printf("\n\033[0;31m+---------------------------------------------------------------------+\n");
  printf("| -> NB: Pour décoder un fichier il faut qu'il soit de type <.cds> <- |\n");
  printf("+---------------------------------------------------------------------+\033[0;m\n");
  printf("Entrez le chemin de votre fichier à decoder: ");
  scanf("%s", chemincode);

  /** Essai d'ouverture et teste de réussite d'ouverture du fichier */
  FILE* fichier = fopen (chemincode, "r");

  if((fichier == NULL) || (!test_extension_cds (chemincode))) {
    do {
      do {
        printf("\n     ! Erreur dans l'ouverture de <%s> !\n\n", chemincode);
        printf("Entrez le chemin de votre fichier à decoder: ");
        scanf("%s", chemincode);
        fichier = fopen (chemincode, "r");
      }
      while (!test_extension_cds (chemincode));
    }
    while (fichier == NULL);
  }
  rewind(fichier);

  /** Utilsation du fichier avant codage pour récupérer l'alphabet et les fréquences */
  /** Saisi du chemin du fichier standard decode*/
  printf("\n\033[0;31m+-----------------------------------------------------------------------------------------------+\n");
  printf("| -> NB: Pour décodé <%s> il nous faut le fichier standard qui a permet de l'avoir. <- |\n", chemincode);
  printf("+-----------------------------------------------------------------------------------------------+\033[0;m\n");
  printf("Entrez le chemindu fichier standard de <%s>: ",chemincode);
  scanf("%s", chemindecode);

  /** Essai d'ouverture et teste de réussite d'ouverture du fichier */
  FILE* fichierStandard =  fopen(chemindecode, "r");

  while ((fichierStandard == NULL) || test_extension_cds(chemindecode) || test_extension_dcd(chemindecode)) {
    printf("\n     ! Erreur dans l'ouverture de <%s> !\n\n", chemindecode);
    printf("Entrez le chemin du fichier standard de <%s>: ", chemincode);
    scanf("%s", chemindecode);
    fichierStandard = fopen (chemindecode, "r");
  }
  rewind(fichierStandard);

  /** Suite allocation mémoire */
  int n = nombre_caracteres_fichier(fichierStandard);
  char* alphabet = (char*) malloc(n*T*sizeof(char));
  char* fichierStandardToChaine = (char*) malloc(n*T*sizeof(char));
  int* tabFreq = (int*) malloc(10*n*T*sizeof(int));

  /** Test de réussite des allocations mémoires */
  if((alphabet == NULL) || (fichierStandardToChaine == NULL) || (tabFreq == NULL)) {
    printf("Erreur Allocation mémoire in prog_5 by main.c\n");
    exit(0);  /** on arrete immédiatement le programme */
  }

  int taille1 = strlen(chemincode);
  chaine_sans_extension(chemincode, radicalCheminCode, taille1);

  if (test_exist_extension (chemindecode)) {
    int taille2 = strlen(chemindecode);
    chaine_sans_extension(chemindecode, radicalCheminDecode, taille2);
  }
  else
    strcpy(radicalCheminDecode, chemindecode);

  if (strcmp(radicalCheminCode, radicalCheminDecode) == 0) {

    trans_fichier_chaine(fichierStandard, fichierStandardToChaine);
    /** récupération de l'alphabet et des fréquences du fichier décodé */
    alphabet_fichier(fichierStandard, alphabet);
    freq_alphabet_fichier(fichierStandardToChaine, alphabet, tabFreq);

    /** Décodage du fichier codé */
    decoder_fichier(fichier, alphabet, tabFreq, chemincode);
    rewind(fichier);
    rewind(fichierStandard);

    /** Libération des mémoires et Fermeture des fichiers */
    free(alphabet);
    free(tabFreq);
    free(fichierStandardToChaine);
    free(chemincode);
    free(chemindecode);
    free(radicalCheminCode);
    free(radicalCheminDecode);
    fclose(fichierStandard);
    fclose(fichier);
  }
  else {
    printf("\n\t! Le fichier %s n'est pas le codage de %s !\n",chemincode, chemindecode);
  }
}
