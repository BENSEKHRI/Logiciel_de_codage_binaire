#include <stdio.h>
#include <stdlib.h>

#define N 10


/** Structures */
/** Structure de l'arbre binaire */
typedef struct node_s {
	char symbol;
	int freq;
	struct node_s * fg;
	struct node_s * fd;
}node;

/** Structure du tas */
typedef struct tas_s {
	int m; /* nombre maximum d'éléménts */
	int n; /* nombre d'élements dans le tas */
	node ** tab;
}tas;

/** Prototypes des fonctions utilisateurs */
node * creer_node (char c, int n);
tas * inic_tas (int m);
int est_vide_tas (tas * H);
void inserer_tas (tas * H, node* A);
tas * saisie_alphabet ();
node * supprimer_tas (tas * H);
void tri_insertion(node** tab, int taille);
void trier_tas (tas* H);
node * creer_arbre (tas * H);
int est_feuille (node * A);
void imprimer_arbre (node * A);
void imprimer_tas (tas* H);
void imprimer_codes (node * A, char * s, int i);
void imprimer_codes_complet (node * A, char * s, int i);
void supprimer_arbre(node * A);
void liberer_memoire_tas (tas * H);
