#include "fichier.h"


/**
 *	Ce fichier contient toutes les fonctions qu'on a juger être utile pour
 *	le codage et décodage d'un char, d'une chaine de char ou d'un fichier.
 */


/** Definitions des fonctions utilisateurs */

/**
 *  Cette fonction permet de calculer le nombre de char qu'un fichier possède.
 *  ALGO: parcour le fichier jusqu'à sa fin et a chaque fois incrémente le cpt.
 *  BUT: 	fonction qui nous permettra par la suite d'allouer la mémoire qu'il
 *				pour les différente chaine de caractères et ainsi éviter les Erreur
 *				free().
 * @param fichier fichier au quel calculer le nombre de ses char.
 * @return le nombre de caracteres que contient le fichier.
 */
int nombre_caracteres_fichier (FILE* fichier) {
	int cpt = 0;
	char c;
	do {
		if (fscanf (fichier, "%c", &c) == 1 && c != '\0')
		cpt++;
	}
	while (!feof(fichier));
	rewind(fichier);
	return cpt;
}

/**
 *  Cette fonction permet de tester si un caractere est contenu dans une chaine
 *  de caracteres.
 *  ALGO: On parcour les char de la chaine jusqu'a '\0' et on retourne 1 si
 *  l'un des char de s est == à c sinon return 0.
 *  BUT: fonction qui permettra de trouver l'alphabet utilisé dans le ficher.
 *
 * @param s la chaine sur laquelle tester l'appartenance du char.
 * @param c le char à tester.
 * @return 1 si c est trouver, 0 sinon.
 */
int appartient_chaine (char* s, char c) {
	int i = 0;
	while (s[i] != '\0') {
		if(s[i] == c)
			return 1;
		i++;
	}
}

/**
 *	Cette fonction permet de transformer un fichier en une chaine de caracteres
 *	et cela en lisant son contenu et en le stockant dans une chaine de char.
 *	ALGO: parcourir le fichier et a chaque fois rajouter le char trouvé à la chaine
 *				et à la fin remettre le curceur du fichier au début et mettre le char
 *				de fin de chaine de char à la chaine.
 *	BUT:  faciliter l'utlisation des fichier et ainsi éviter a chaque fois
 *				d'utiliser fscanf pour parcourir le fichier.
 *
 * @param fichier le fichier à transformer.
 * @param chaine la chaine qui stock le contenu du fichier.
 */
void trans_fichier_chaine(FILE* fichier, char* chaine) {
	int i = 0;
	char c;
	do {
		if (fscanf(fichier, "%c", &c) == 1 && c != '\0') {
			chaine[i] = c;
			i++;
		}
	}
	while (!feof(fichier));
	chaine[i] = '\0';

  rewind(fichier);  /** remise du curseur au debut du fichier. */
}

/**
 *	Cette fonction permet de trouver tous les caractères qui sont différents
 *	dans une chaine de char et enfin les met dans alphabet.
 *	ALGO: parcourir la chaine et chaque fois que l'on trouve que un char de
 *				chaine n'appartient pas à alphabet on l'ajoute à cette dernière.
 *	BUT:	trouver les symbol (alphabet) utilisé dans un fichier.
 *
 * @param chaine
 * @param alphabet
 */
void alphabet_chaine (char* chaine, char* alphabet) {
	int i = 0, j = 0;
  char c;
	while (chaine[j] != '\0') {
      if(!appartient_chaine(alphabet, chaine[j])) {
        alphabet[i] = chaine[j];
        i++;
      }
			j++;
  }
  alphabet[i] = '\0';
}

/**
 *  Cette fonction permet de trouver tout les caracteres utilisé dans le ficher.
 *  ALGO: Allocation de mémoire pour la chaine alphabet ou mettre les char.
 *  si l'allocation a réussi on parcour les caractères du fichier jusqu'au
 *  dernier caractere et a chaque fois en rajoute le caractere si il
 *  n'appartient pas deja a la chaine alphabet.
 *  BUT: Cette alphabet sera rajouter par la suite au tas qui construira l'arbre de
 *  codage.
 *
 * @param fichier le fichier auquel trouvé l'alphabet utilisé.
 * @param l'alphabet utilisé dans le fichier.
 */
void alphabet_fichier (FILE* fichier, char* alphabet) {
  int i = 0;
  char c;
  do {
    if (fscanf (fichier, "%c", &c) == 1 && c != '\0')
      if(!appartient_chaine(alphabet, c)) {
        alphabet[i] = c;
        i++;
      }
  }
  while (!feof(fichier));
  alphabet[i-1] = '\0';

  rewind(fichier);  /** remise du curseur au debut du fichier. */
}

/**
 *	Cette fonction permet de trouver le nombre d'occurance qu'un char est présent
 *	dans une chaine de caractere.
 *	ALGO: On parcour la chaine s et à chaque fois que l'on trouve c on incrémente
 *				le cpt et à la fin on le renvoi.
 *	BUT:	fonction à utiliser pour trouver le nombre d'occurance de chaque char
 *				de l'alphaber dans le un fichier.
 *
 * @param s la chaine où chercher c.
 * @param c le char pour lequel trouvé le nombre d'occurance dans s.
 * @retrun cpt le nombre d'occurance de c dans s.
 */
int nombre_occu_charInChain(char* s, char c) {
	int n = strlen(s);
	int i = 0;
	int cpt = 0;
	for(i = 0; i < n; i++) {
		if(c == s[i])
			cpt++;
	}
	return cpt;
}

/**
 *	Cette fonction permet de trouver trouver et stocker toutes les occurances
 *	de tous les char de l'alphabet du fichier trouvé ce dernier.
 *	ALGO: parcourir l'alphabet et pour chaque char de cette dernière trouver
 *				son occurance dans fichier et enfin la mettre dans le tableau.
 *  BUT:  Ce tableau sera rajouter par la suite au tas qui construira l'arbre de
 *  		  codage.
 *
 * @param fichier le fichier dans lequel chercher qui est un chaine de char.
 * @param alphabet tous les char auxquels trouvé l'occurance dans fichier.
 * @param tab le tableau de int qui stockera chaque occurance de chaque char.
 */
void freq_alphabet_fichier (char* fichier, char* alphabet, int* tab) {
	int i = 0, j=0, cpt=0;

	for(i = 0;i < strlen(alphabet);i++) {
		tab[j] = nombre_occu_charInChain(fichier, alphabet[i]);
		j++;
	}
}

/**
 *	Cette fonction permet de creer et Initialiser un tas et cela grace a la chaine
 *	alphabet et au tableau de freq de alphabet[i].
 *	BUT: c'est le tas qui crééera l'arbre de codage.
 *
 * @param alphabet l'alphabet utiliser dans le fichier.
 * @param tabFreq la fréquence de cette alphabet.
 * @return tas le tas initial.
 */
tas * creer_tas (char* alphabet, int* tabFreq) {
	int n = strlen(alphabet);
	tas* H = inic_tas(n);
	int i = 0;

	for(i = 0; i < n; i++) {
		node* A = creer_node(alphabet[i],tabFreq[i]);
		inserer_tas(H, A);
	}
	return H;
}

/**
 *	Cette fonction permet de coder un char en binaire.
 *	ALGO: meme principe que imprimer_codes.
 *	BUT:  trouver le code bianire d'une chaine de char par la suite et ainsi
 *				un fichier.
 *
 * @param A l'abre de codage.
 * @param c le char à coder.
 * @param s chaine tmp qui parcour l'arbre de codage.
 * @param dest le code binaire de c.
 * @param i le compteur qui incrémente s.
 */
void coder_char (node * A, char c, char* s, char* dest, int i) {
	if(A->fg) {
		s[i]='0';
		coder_char (A->fg,c, s, dest, i+1);
	}

	if (est_feuille (A)) {
		s[i] = '\0';
		if(A->symbol == c) {
			strcat(dest, s);
		}
	}

	if(A->fd) {
		s[i]='1';
		coder_char (A->fd,c, s, dest, i+1);
	}
}

/**
 *	Cette fonction et complémentaire à la précédente; elle permet de coder un
 *	char en binaire.
 *	ALGO: meme principe que imprimer_codes_complet.
 *	BUT:  trouver le code bianire d'une chaine de char par la suite et ainsi
 *				un fichier.
 *
 * @param A l'abre de codage.
 * @param c le char à coder.
 * @param s chaine tmp qui parcour l'arbre de codage.
 * @param dest le code binaire de c.
 * @param i le compteur qui incrémente s.
 */
void coder_char_complet (node * A, char c, char* s,char* dest, int i) {
  if (est_feuille (A)) {
		s[i] = '0';
		s[i+1] = '\0';
		strcat(dest, s);
  }
  else
    coder_char(A, c, s, dest, i);
}

/**
 *	Cette fonctio permet de coder une chaine de char en binaire.
 *	ALGO: on parcour la chaine et à pour chaque char de cette dernière on génére
 *				un code bianire que l'on met dans code.
 *	BUT:	coder un fichier par la suite.
 *
 * @param A L'arbre de codage.
 * @param chaine la chaine à coder.
 * @param code le code binaire généré par cette chaine.
 */
void coder_chaine (node* A, char* chaine, char* code) {
	int i = 0;
	char* s = (char*) malloc(T*sizeof(char));
	for(i = 0;i < strlen(chaine); i++) {
		coder_char_complet(A, chaine[i], s, code, 0);
	}

	free(s);
}

/**
 *	Cette fonction permet de tester si un chemin qui permet d'ouvrir un fichier
 *	est contituer d'un extension.
 *	Cette fontion renvoi 1 si le chemin a une extension, 0 sino.
 *	ALGO:	On calcule la longueur de chemin si à chemin[taille-4] il y un '.'
 *				alors le chemin est contituer d'une extension.
 *	BUT:	Cela nous permettra de decoder un fichier avec une certaine extension,
 *				et notamment de faciliter l'ajout des extension au fichiers qui seront
 *				créés.
 *
 * @param chemin le chemin qui ouvre le fichier.
 * @return si le chemin à une extension, 0 sinon.
 */
int test_exist_extension (char* chemin) {
	int taille = strlen(chemin);
	if (chemin[taille-4] == '.')
		return 1;
	return 0;
}

/**
 *	Cette fonction permet de tester si un chemin qui permet l'ouverture d'un fichier
 *	est contituer de l'extension ".cds".
 *	ALGO:	On regard si les 4 derniers char de chemin son identique à ".cds".
 *				on retour 1 si oui, 0 sinon.
 *	BUT:  permet de détercté les fichier qui sont codé par ce logiciel.
 *
 * @param chemin le chemin qui ouvre le fichier.
 * @return si le chemin à l'extension ".cds", 0 sinon.
 */
int test_extension_cds (char* chemin) {
	int taille = strlen(chemin);
	if((chemin[taille-1] == 's') && (chemin[taille-2] == 'd') && (chemin[taille-3] == 'c') && (chemin[taille-4] == '.'))
		return 1;
	return 0;
}

/**
 *	Cette fonction permet de tester si un chemin qui permet l'ouverture d'un fichier
 *	est contituer de l'extension ".dcd".
 *	ALGO:	On regard si les 4 derniers char de chemin son identique à ".dcd".
 *				on retour 1 si oui, 0 sinon.
 *	BUT:  permet de détercté les fichier qui sont codé par ce logiciel.
 *
 * @param chemin le chemin qui ouvre le fichier.
 * @return si le chemin à l'extension ".dcd", 0 sinon.
 */
int test_extension_dcd (char* chemin) {
	int taille = strlen(chemin);
	if((chemin[taille-1] == 'd') && (chemin[taille-2] == 'c') && (chemin[taille-3] == 'd') && (chemin[taille-4] == '.'))
		return 1;
	return 0;
}

/**
 *	Cette fonction pemet de enlever l'extension d'un chemin.
 *	ALGO: On parcour la chaine s jusqu'a l'indice n-4 et a chaque fois on met
 *				le char trouvé dans dest.
 *	BUT: faciliter la mise à jour des extensions.
 *
 * @param s la chaine avec extension.
 * @param dest la chaine resultat après suppression de l'extension.
 * @param n la longueur de s.
 */
void chaine_sans_extension (char* s, char* dest, int n) {
	int i = 0;
	while(i != n-4) {
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
}

/**
 *	Cette fonction permet de coder un fichier en binaire.
 *	ALGO: On commence par transformer le fichier en chaine de caratères ensuite
 *				on trouve tous l'alphabet utiliser dans ce fichier avec la fréquence
 *				de chacun. apres cela on construit l'arbre de codage grâce au tas
 *				créé par l'alphabet et les fréquence. et enfin grâce à cet arbre on
 *				on code la chaine contenu dans le fichier en binaire et on l'ecrit dans
 *				le fichier.cds créé.
 *	NB: 	le fichier créée après codage est forcément d'extension ".cds". Si un
 *				fichier que l'on veut coder à deja une extension, on commence par le lui
 *				enlever, ainsi on pourrai mettre ".cds" à la place.
 *	BUT: 	graĉe à cette fonction on aura pu coder un fichier ordinaire en bianire
 *				sous l'extension ".cds".
 *
 * @param ficher le fichier à coder.
 * @param le chemin du fichier.
 */
void coder_fichier(FILE* fichier, char* chemin) {
	rewind(fichier);
	int n = nombre_caracteres_fichier(fichier);
	/** Allocation mémoire */
	char* fichierToChaine = (char*) malloc(n*T*sizeof(char));
  char* alphabet = (char*) malloc(n*T*sizeof(char));
	char* codeBinaire = (char*) malloc(2*n*T*sizeof(char));
  int* tabFreq = (int*)malloc(n*T*sizeof(int));
	char* s = (char*) malloc(n*T*sizeof(char));
	char* extension = (char*) malloc(T*sizeof(char));

	/** test de réussite d'allocation mémoire */
	if((fichierToChaine == NULL) || (alphabet == NULL) || (codeBinaire == NULL) || (tabFreq == NULL) || (s == NULL) || (extension == NULL)) {
		printf("Erreur allocation mémoire by coder_fichier in fichier.c\n");
		exit(0);  /** on arrete immédiatement le programme */
	}


	/** ajout de l'extension .cds au fichier codé créé */
	if (!test_exist_extension(chemin)) {	/** fichier à coder sans extension au départ */
		strcpy(extension, chemin);
		strcat(extension,".cds");
	}
	else {		/** fichier à coder avec extension au départ */
		int taille = strlen(chemin);
		chaine_sans_extension (chemin, extension, taille);
		strcat(extension,".cds");
	}

	/** trasfomation du fichier to chaine, récupérationde l'alphabet
	 *	utilisé et de la fréquence de chaqu'un */
  trans_fichier_chaine(fichier, fichierToChaine);
  alphabet_fichier(fichier, alphabet);
  freq_alphabet_fichier(fichierToChaine, alphabet, tabFreq);

	/** création du tas et de l'arbre de codage */
  tas* tasCodage = creer_tas(alphabet, tabFreq);
  node* arbreDeCodage = creer_arbre(tasCodage);

	/** Création du fichier codé */
	FILE* fichierCoder = fopen(extension, "w+");
	if (fichierCoder == NULL) {
		printf("Erreur création du fichier codé.\n");
		exit(0);  /** on arrete immédiatement le programme */
	}
	rewind(fichierCoder);
	coder_chaine (arbreDeCodage, fichierToChaine, codeBinaire);
	fprintf(fichierCoder, "%s", codeBinaire);
	rewind(fichierCoder);

	/** affichage du contenu des deux fichiers et des codes de l'alphabet utilisé */
	printf("\n\t\t\tCodage ...\nLe fichier < %s > vient d'être créé dans votre répertoire.\n", extension);
	printf("\nVoici le contenu de <%s>: <%s>\n",chemin, fichierToChaine);
	printf("\nVoici les codes des caratères: \n");
	imprimer_codes_complet(arbreDeCodage, s, 0);
	printf("\nVoici le contenu de <%s>: <%s>\n", extension, codeBinaire);


	/** Libération des mémoires allouées */
  free(fichierToChaine);
	free(s);
  free(alphabet);
	free(codeBinaire);
  free(tabFreq);
	free(extension);
  liberer_memoire_tas(tasCodage);
  supprimer_arbre(arbreDeCodage);
	/** fermeture du fichier coder créé */
	rewind(fichier);
	rewind(fichierCoder);
	fclose(fichierCoder);
}

/**
 * 	Cette fonction permet de décoder un code bianre en un char.
 *	ALGO: On parcour la chaine s et qui l'on trouve un 0 on va au fils gauche,
 *				si l'on trouve un 1 on va au fils droite et si on arrive à la feuille
 *				on met le résultat dans dest et on retour l'index atteint en parcourant
 *				s. Cet index nous permettra par la suite de decoder un code binaire
 *				complet en une chaine de char
 *	BUT: 	Cette fonction nous permettra par la suite de decoder un code binaire
 *				complet en une chaine de char
 *
 * @param A l'abre de codage.
 * @param s le code bianire.
 * @param i index qui parcour s.
 * @param c un char tmp.
 * @param dest le résultat donné par s, après décodage.
 * @return  i l'index de s auquel on n'a pu attendre la feuille et stocker
 *					sa valeur dans dest.
 */
int decoder_char (node* A, char* s, int i, char c, char* dest) {
	if (est_feuille (A)) {
		dest[0] = A->symbol;
		dest[1] = '\0';
		return i--;
	}
	c = s[i];
	i++;
	if(c == '0')
		decoder_char (A->fg, s, i, c, dest);
	if(c == '1')
		decoder_char (A->fd, s, i, c, dest);
}

/**
 *	Cette fonction permet de couper une chaine de char et de laisse que le début
 *	de cette dernière jusqu'à n.
 *	ALGO:	On parcour s jusqu'à n et à chaque fois on met le résultat dans dest.
 *	BUT:	Cette fonction nous permettra de récupérer le reste du code binaire
 *				qui n'est pas décoder par decoder_char.
 *
 * @param s la chaine de char complete.
 * @param dest ce qu'il reste de s après l'indice n.
 * @param n indice qui parcour s.
 */
void reste_chaine (char* s, char* dest, int n) {
	int i = 0;
	while(s[n] != '\0') {
		dest[i] = s[n];
		i++;
		n++;
	}
	dest[i] = '\0';
}

/**
 * 	Cette fonction permet de décoder un code binaire complet en une chiane de char.
 *	ALGO: on parcour la chaine s et à chaque fois en la decode grace à la fonction
 *				decoder_char le résulat qui est dans dest on l'ajoute à chaine, et en
 *				laisse le reste qui est pas decodé de s grace à la fonction reste_chaine
 *				et on recommence tant que s n'est pas fini.
 *	BUT: 	Cette fonction nous permettra de décoder un fichier binaire.
 *
 * @param A l'arbre de codage.
 * @param s le code bianire.
 * @param i index qui parcour s.
 * @param c char tmp.
 * @param dest le char décoder à chaque fois.
 * @param chaine le résulat final du décodage de s.
 * @param n int tmp pour indiquer la taille de mémoire à allouer.
 */
void decoder_chaine (node* A, char* s, int i, char c, char* dest, char* chaine, int n) {
	char* suite = (char*) malloc(n*T* sizeof(char));

	int pos = 0;
	int j = 0;
	while (s[pos] != '\0') {
		pos = decoder_char (A, s, 0, c, dest);

		chaine[j] = dest[0];
		j++;

		reste_chaine (s, suite, pos);

		s = suite;
	}

	chaine[j+1] = '\0';
	free(suite);
}

/**
 *	Cette fonction permet de décoder en une chaine de char un fichier codé en
 *	binaire.
 *	ALGO:	on transformer le fichier décoder en une chaine de char et on la décode
 *				grace à la focntion decoder_chaine on on écrit le résulat dans le
 *				fihicer.dcd créé.
 *	NB:		-> Un fichier peut être décoder que si sont extension est ".cds".
 *				-> Le fichier décoder créé est forcément d'extension ".dcd".
 *	BUT: 	Cette fonction nous permet de décoder n'importe quel fichier codé grace
 *				à ce logiciel en ayant les bon éléments.
 *
 * @param fichierCoder le fichier à décoder.
 * @param alphabet l'alphaber du fichier décoder.
 * @param tabFreq la fréquence de alphabet.
 * @param chemin le chemin qui ouvre le fichier décoder.
 */
void decoder_fichier(FILE* fichierCoder, char* alphabet, int* tabFreq, char* chemin) {
	rewind(fichierCoder);
	/** Initialisation et Allocation mémoire */
	int n = nombre_caracteres_fichier(fichierCoder);
	char c;

	char* extension = (char*) malloc(n*T*sizeof(char));
	char* fichierCoderToChaine = (char*) malloc(n*T*sizeof(char));
	char* tmp = (char*) malloc(n*T*sizeof(char));
	char* chaine = (char*) malloc(n*T*sizeof(char));
	char* s = (char*) malloc(n*T*sizeof(char));

	/** test de réussite des allocations mémoires */
	if((extension == NULL) || (fichierCoderToChaine == NULL) || (tmp == NULL) || (chaine == NULL) || (s == NULL)) {
		printf("Erreur allocation mémoire by decoder_fichier in fichier.c\n");
		exit(0);  /** on arrete immédiatement le programme */
	}

	if(!test_extension_cds(chemin) || !test_exist_extension(chemin))		/** test d'extension si ce n'est pas .cds rien faire ou si il n'a pas du tout d'extension */
		printf("Le fichier n'est pas décodable car il n'est pas codé.\n");

	else {	/** sinon */

		/** trasfomation du fichier en chaine de caracteres */
		trans_fichier_chaine(fichierCoder, fichierCoderToChaine);

		/** création du tas et de l'arbre de codage */
		tas* tasCodage = creer_tas(alphabet, tabFreq);
		node* arbreDeCodage = creer_arbre(tasCodage);

		/** mise à jour de l'extension du fichier qui sera créé qui est: .dcd*/
		int taille = strlen(chemin);
		chaine_sans_extension (chemin, extension, taille);
		strcat(extension, ".dcd");

		/** Création du fichier décodé */
		FILE* fichierDecoder = fopen(extension, "w+");
		if(fichierDecoder == NULL) {
			printf("Erreur création du fichier décodé.\n");
			exit(0);  /** on arrete immédiatement le programme */
		}
		rewind(fichierDecoder);
		/** On décode le fichier */
		decoder_chaine (arbreDeCodage, fichierCoderToChaine, 0, c, tmp, chaine, n);
		/** On écrit le résultat dans le fichier créé */

		fprintf(fichierDecoder, "%s", chaine);
		rewind(fichierDecoder);
		/*affichage du contenu des deux fichiers et des codes de l'alphabet utilisé */
		printf("\n\t\t\tDecodage ...\nLe fichier < %s > vient d'être créé dans votre répertoire.\n", extension);
		printf("\nVoici le contenu de <%s>: <%s>\n",chemin, fichierCoderToChaine);
		printf("\nVoici les codes des caratères: \n");
		imprimer_codes_complet(arbreDeCodage, s, 0);
		printf("\nVoici le contenu de <%s>: <%s>\n", extension, chaine);

		/** Libération des mémoires allouées */
		free(extension);
		free(fichierCoderToChaine);
		free(tmp);
		free(chaine);
		free(s);
		liberer_memoire_tas(tasCodage);
		supprimer_arbre(arbreDeCodage);
		/** Fermeture du fichier Decoder */
		rewind(fichierDecoder);
		rewind(fichierCoder);
		fclose(fichierDecoder);
	}
}
