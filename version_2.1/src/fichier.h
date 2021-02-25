#include <string.h>
#include "codage.h"

#define T 130


/** Prototypes des fonctions utilisateurs */
int nombre_caracteres_fichier (FILE* fichier);
int appartient_chaine (char* s, char c);
void trans_fichier_chaine(FILE* fichier, char* chaine);
void alphabet_chaine (char* chaine, char* alphabet);
void alphabet_fichier (FILE* fichier, char* alphabet);
int nombre_occu_charInChain(char* s, char c);
void freq_alphabet_fichier (char* fichier, char* s, int* tab);
tas * creer_tas (char* alphabet, int* freq);
void coder_char(node * A, char c, char* s,char* dest, int i);
void coder_char_complet (node * A, char c, char* s,char* dest, int i);
void coder_chaine (node* A, char* chaine, char* code);
int test_exist_extension (char* chemin);
int test_extension_cds(char* chamin);
int test_extension_dcd (char* chemin);
void chaine_sans_extension (char* s, char* dest, int n);
void coder_fichier(FILE* fichier, char* chemin);
int decoder_char (node* A, char* s, int i, char c, char* dest);
void reste_chaine (char* s, char* dest, int n);
void decoder_chaine(node* A, char* s, int i, char c, char* dest,  char* chaine, int n);
void decoder_fichier(FILE* fichier, char* alphabet, int* tabFreq, char* chemin);
