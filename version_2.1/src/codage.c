#include "codage.h"


/**
 *	Ce fichier contient toutes les fonction pour le logiciel de codage en
 *	général, et on particulier pour la version 1.1
 */


/** Definitions des fonctions utilisateurs */

/**
 *	Initialisation d'un nouveau noeud grâce à un symbol c de type char et
 *	un entier n qui représente la fréquece de c.
 *	Allocation de mémoire pour un nouveau noeud de type "node".
 *
 * @param c symbol du noeud.
 * @param n fréquence de c.
 * @return un nouveau noeud.
 */
node * creer_node (char c, int n) {
	node* new = (node*)malloc(sizeof(node));
	if(new == NULL) {
		printf("Erreur allocation mémoire by creer_node in codage.c\n");
		exit(0);	/** on arrete immédiatement le programme */
	}
	else {
		new->symbol = c;
		new->freq = n;
		new->fg = NULL;
		new->fd = NULL;
		return new;
	}
}

/**
 *	Initialise un nouveau tas grâce à un entier m qui représente le maximum
 *	de node que contiendra le tas.
 * 	Allocation de mémoire pour un tableau de node.
 *	Allocation de mémoire pour un tas.
 *
 * @param m le maximum du tas.
 * @return un nouveau tas.
 */
tas * inic_tas (int m) {
	tas* new = (tas*)malloc(sizeof(tas));
	node* * tab = (node**)malloc(m*sizeof(node*));
	if(new == NULL || tab == NULL) {
		printf("Erreur allocation mémoire by inic_tas in codage.c\n");
		exit(0);	/** on arrete immédiatement le programme */
	}
	else {
		new->m = m;
		new->n = 0;
		new->tab = tab;
		return new;
	}
}

/**
 *	Cette fonction permet de vérifier si un tas est vide ou pas.
 *
 * @param H le tas à vérifier.
 * @return 1 si le tas est vide, 0 sinon.
 */
int est_vide_tas (tas * H) {
	if(H->n == 0)
		return 1;
	return 0;
}

/**
 *	Insert un node à un tas (tas minimum). Et cela en fonction des fréquences
 *	des caracteres.
 *
 * @param H le tas auquel ajouter le noeud.
 * @param A le noeud à ajouter.
 */
void inserer_tas (tas * H, node* A) {
	if(H->n == H->m) {
		H->tab = realloc(H->tab, 2*sizeof(H->tab));
	}
	H->tab[H->n] = A;
	int i = H->n;
	int j = (i-1)/2;	/** père */

	while(j >= 0 && H->tab[i]->freq < H->tab[j]->freq) {
		node* tmp = H->tab[i];
		H->tab[i] = H->tab[j];
		H->tab[j] = tmp;
		i = j;
		j = (i-1)/2;
	}

	H->n++;
}

/**
 *	Demande à l'utilisateur le nombre de caractere de l'alphabet avec test qu'il
 *	soit strictement positif sinon le redemander à nouveau, créée le tas avec comme
 *  maximum le nombre de caractere, ensuite demande à l'utilisateur d'entrer
 *  les caracteres et leurs fréquences qui seront ensuite insérer dans le tas.
 *	Si l'utilisateur entre une fréquence <= 0 le programme lui demande une
 *	nouvelle fréquence car la fréquence ne peut être que strictement positive.
 *
 *	Complexité: O(log(n)).
 */
tas * saisie_alphabet () {
	int n;							/** nombre de lettres de l'alphabet */
	char aideScan[N];		/** pour éviter le '\n' de scanf */

	do {
		printf("Entrer le nombre de lettres que contient l'alphabet: ");
		scanf("%d", &n);
		fgets(aideScan, N, stdin);
	} while(n<=0);

	printf("\n Saisi des %d caracteres et leurs fréquences respectives: \n", n);
	printf("*******************************************************\n");

	tas* H = inic_tas(n);
	int i = 0;

	for(i = 0; i < n; i++) {
		node* A = creer_node('\0',0);

		printf("Caractere n° %d: ",i+1);
		scanf("%c", &A->symbol);
		fgets(aideScan, N, stdin);
    do {
			printf(" Frequence (%c): ", A->symbol);
			scanf("%d", &A->freq);
			fgets(aideScan, N, stdin);
		} while (A->freq <= 0);

		inserer_tas(H, A);
		printf("\n");
	}

	return H;
}

/**
 *	Supprime le minimum du tas qui est dans la position 0 du tableau et met à
 *	jour ce dernier le minimum est calculer en fonction des fréquences des char.
 *
 * @param H le tas du quel supprimer le node.
 * @return le node supprimer qui était le minimum du tas.
 */
node * supprimer_tas (tas * H ) {
	if(est_vide_tas(H)) {
		printf("Le tas est vide. suppression impossible in supprimer_tas by codage.c\n");
		exit(0);	/** on arrete immédiatement le programme */
	}
	node* supprimer = H->tab[0];
	H->tab[0] = H->tab[H->n-1];
	int i = 0;
	int fg = 2*i+1;
	int fd = 2*i+2;
	int k = 0;			/** index de min(fils g, fils d); */
	int continuer = 1;
	H->n--;

	while(i < H->n/2 && continuer) {
		if(H->tab[fd] != NULL) {
			if(H->tab[fd]->freq <= H->tab[fg]->freq)
				k = fd;
			k = fg;
		}
		k = fg;

		if(H->tab[i]->freq > H->tab[k]->freq) {
			node* tmp = H->tab[i];
			H->tab[i] = H->tab[k];
			H->tab[k] = tmp;
			i = k;
		}
		else
			continuer = 0;
	}
	return supprimer;
}

/**
 *	Effectue un tri insertion croissant sur un tableau de node et cela en
 *	fonction des fréquences du caractere du node.
 *
 * @param tab le tableau de node à trier.
 * @param taille la taille du tableau.
 */
void tri_insertion(node** tab, int taille){
   int i, j;
   for (i = 1; i < taille; ++i) {
       node* elem = tab[i];
       for (j = i; j > 0 && tab[j-1]->freq > elem->freq; j--) {
				 node* tmp = tab[j];
				 tab[j] = tab[j-1];
				 tab[j-1] = tmp;
			 }

			 node* tmp2 = tab[j];
       tab[j] = elem;
			 elem = tmp2;
   }
}

/**
 *	Cette fonction tri le tableau de node du tas (utilisation de la fonction
 *	tri_insertion pour trier le tableau).
 *
 * @param H le tas à trier.
 */
/** fonction qui tri un tas en fonction des fréquences des noeuds */
void trier_tas (tas* H) {
	int n = H->n;
	node** tab = (node**)malloc(n*sizeof(node*));
	if(tab == NULL) {
		printf("Erreur allocation mémoire in trier_tas by codage.c\n");
		exit(0);	/** on arrete immédiatement le programme */
	}
	else {
		int i =0;
		for(i = 0; i < H->n; i++) {
			tab[i] = H->tab[i];
		}
		i=0;
		while(i != H->n) {
		  supprimer_tas(H);
		}
		tri_insertion(tab, n);
		for(i = 0; i < n; i++) {
			inserer_tas(H, tab[i]);
		}
	}
	free(tab);
}

/**
 *	Initiale un arbre de codage et cela grâce à un tas.
 *	Fonctionnement:
 *	On tri le tas passé en paramètre et à chaque fois en retire les deux minimum
 *	du tas et on crée un node fusion qui aura comme symbol le char de fin de '\0'
 *	et comme fréquence la somme des deux fréquence des deux symbol contenu dans
 *  les deux minimum extrait. Ensuite on ajoute le nouveau node au tas et on
 *  re tri le tas.
 *  On refait l'étape précedente tant qu'il ne reste pas plus d'un node dans le
 *	tas.
 *
 * @param
 * @return
 */
node * creer_arbre (tas * H) {
	trier_tas(H);	/** tas trier */
	int n = H->n;	/** nombre de caracteres chaque un à une freq */
	int i = 0;

	for(i = 1; i < n; i++) {
		node* min1 = supprimer_tas(H);
		node* min2 = supprimer_tas(H);

		node* fusion = creer_node('\0', min1->freq + min2->freq);
		fusion->fg = min1;
		fusion->fd = min2;
		inserer_tas(H, fusion);
		trier_tas(H);
	}
	return supprimer_tas(H);
}

/**
 *	Cette fonction permet de vérifier si un node est une feuille ou pas,
 *	si il a des fils ou pas.
 *
 * @param A le node à vérifier.
 * @return 1 si le node est une feuille, 0 sinon.
 */
int est_feuille (node * A) {
	if(A->fg == NULL && A->fd == NULL)
		return 1;
	return 0;
}

/**
 *	Cette fonction permet un affichage infixe d'un node (G R D).
 *	Si le caractere du node est '\0' on affiche seulement [freq] sa fréquence
 *	si non on affiche [symbol: freq].
 *
 * @param A le node à afficher.
 */
void imprimer_arbre (node * A) {
	if(A != NULL) {
		imprimer_arbre(A->fg);

		if(A->symbol == '\0')
			printf("[%d]  ", A->freq);
		else
			printf("[%c: %d]  ", A->symbol, A->freq);

		imprimer_arbre(A->fd);
	}
}

/**
 * 	Cette fonction permet un affichage du tas;
 *	le contenu du tableau de node du tas.
 *	Si le caractere du node est '\0' on affiche seulement | freq | sa fréquence
 *	si non on affiche |symbol: freq |.
 *
 * @param H le tas à afficher.
 */
void imprimer_tas (tas* H) {
	if(H->n == 0) {
		printf("Le tas est vide.\n");
	}
	else {
		int i = 0;
		while (i<H->n){
			if(H->tab[i]->symbol == '\0')
				printf("| %d ", H->tab[i]->freq);
			else {
				printf("| %c:%d ", H->tab[i]->symbol, H->tab[i]->freq);
			}
			i++;
		}
		printf("|\n");
	}
}

/**
 * 	Cette fonction permet de donner le codage binaire des symbol contenus dans
 *	les feuilles de l'arbre de codage.
 *	Fonctionnement:
 *	l'index de la chaine s ou écrire le code est égal à 0, on fait un parcour
 *	infixe de l'arbre et si on visite le fils gauche on rajoute un 0 a s
 *	et on incrémente i et on fait un appel récursivement la fonction avec le
 *	fils gauche, la nouvelle chaine s et i+1. On fait pareil pour le fils droit,
 *	mais au lieu d'un 0 on ajoute un 1 à la chaine dans la position i. Et si on
 *	arrive à la feuille on peut déja écrire le code du symbol trouvé juste
 *	après l'ajout du caractere de fin de chaine de char.
 *
 * @param A l'arbre de codage.
 * @param s la chaine ou écrire le code.
 * @param i l'index de a chaine où écrire
 */
void imprimer_codes (node * A, char * s, int i) {
	if(A->fg) {
		s[i]='0';
		imprimer_codes (A->fg,s,i+1);
	}

	if (est_feuille (A)) {
		s[i] = '\0';
		printf("%c : %s\n", A->symbol, s);
	}

	if(A->fd) {
		s[i]='1';
		imprimer_codes (A->fd,s,i+1);
	}
}

/**
 *  Cette fonction est complémentaire à la précédente fonction: imprimer_codes
 *  en effet elle permet de plus que imprimer_codes de donner un codage même si
 *  l'utilisateur entre qu'un seul caractere lors de l'exécution et le code de
 *  ce dernier sera de 0. la fonction imprimer_codes ne donne pas de code pour
 *  un arbre de codage sans branches (fils).
 *
 * @param A l'arbre de codage.
 * @param s la chaine ou écrire le code.
 * @param i l'index de a chaine où écrire
 */
void imprimer_codes_complet (node * A, char * s, int i) {
  if (est_feuille (A)) {
    s[i] = '0';
    s[i+1] = '\0';
    printf("%c : %s\n", A->symbol, s);
  }
  else
    imprimer_codes(A, s, i);
}

/**
 *	Libère la mémoire alloué à un node.
 *
 * @param A l'arbre à libérer.
 */
void supprimer_arbre(node * A) {
	if (A != NULL) {
		supprimer_arbre(A->fg);
		supprimer_arbre(A->fd);
		free(A);
	}
}

/**
 *	Libèrer la mémoire alloué à un tas.
 *
 * @param H le tas à libérer.
 */
void liberer_memoire_tas (tas * H) {
	int i = 0;
	for(i = 0; i < H->n; i++) {
		supprimer_arbre(H->tab[i]);
	}
	free(H->tab);
	free(H);
}
