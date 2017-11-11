/*
* Ce module représente une pile qui peut contenir des données d'un seul et même type
*défini par t_element dont l'accès est dernier arrivé-premier servi (Last In First Out)
*
*Il suffit de changer le type de référence pour que la pile change de type
*ex: typedef int t_element
*    typedef char t_element
*    typedef t_ t_element
*
* ou t_ est un type quelconque utilisable par sizeof
*
*
*/
#ifndef _T_PILE__
#define _T_PILE__

#define  MAX_PILE  50
#define  PILE_VIDE  -1

#define TAILLE_TITRE	80
#define TAILLE_NOM		30
#define TAILLE_PRENOM	30

typedef enum {AUCUN = 0, FICTION = 1, HISTOIRE = 2, SCIENCE = 3, ENFANTS = 4, INFORMATIQUE = 5} t_genre;

typedef struct
{
    t_genre genre;
    int nb_pages;
    char auteur_prenom[TAILLE_PRENOM];
    char auteur_nom[TAILLE_NOM];
    char titre[TAILLE_TITRE];
    int isbn;
    int bEmprunte; // 1: Le livre a ete emprunte, 0: le livre est disponible.
} t_livre;

//changer cette déclaration pour obtenir des piles d'un autre type
typedef t_livre t_element;

typedef struct {

	 //L'endroit de stockage des données
   t_element  tab_elements[MAX_PILE];

	 //L'endroit où est la donnée à désempiler
   int      sommet;
} t_pile;

//Procédure pour initialiser une pile, la pile est vide
//À utiliser pour vider une pile(new)
void init_pile(t_pile* p);

//Retourne si une pile est pleine ou non(is_full)
int  est_pleine(const t_pile* p);

//Retourne si une pile est vide ou non(is_empty)
int  est_vide(const t_pile* p);

//Ajoute l'élément reçu sur le dessus de la pile(push)
void empile(t_pile* p, t_element e);

//Retourne l'élément sur le dessus et le retire de la pile(pop)
t_element desempile(t_pile* p);

//(*NOUVEAU*) Retourne une copie de l'élément du dessus sans l'enlever de la pile(peek)
t_element getSansEnlever(t_pile* p);

//Retourne le nombre d'éléments de la pile(size)
int get_nb_elements(const t_pile* p);

//variante
//Procédure pour enlever un élément du haut d'une pile
//et le retourner via le paramètre formel en sortie
//void desempiler(t_pile* p, t_element* e);

#endif
