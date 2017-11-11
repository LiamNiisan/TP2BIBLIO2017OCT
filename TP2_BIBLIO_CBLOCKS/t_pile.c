#include "t_pile.h"

/*
*STRATÉGIE : Nous avons décidé d'implémenter la pile dans un tableau statique de MAX_PILE éléments défini dans pile.h
*
*             -à chaque ajout on incrémente le sommet avant d'insérer dans le tableau d'éléments (voir t_pile)
*             - La pile est vide si le somme == PILE_VIDE
*             - La pile est pleine si le sommet == MAX_PILE - 1 (ou sommet + 1 == MAX_PILE)
*             - à chaque retrait, on décrémente le sommet après avoir retourné l'élément pointé par celui-ci
*
*
*/


//Procédure pour initialiser une pile, la pile est vide
//À utiliser pour vider une pile.
void init_pile(t_pile *p)
{
	p->sommet = PILE_VIDE;
}

//Retourne si une pile est pleine ou non
int  est_pleine(const t_pile *p)
{

	//Les indices vont de 0 à MAX_PILE - 1
	return p->sommet == MAX_PILE - 1;
}

//Retourne si une pile est vide ou non
int  est_vide(const t_pile *p)
{
	return p->sommet == PILE_VIDE;
}

//Ajoute l'élément reçu sur le dessus de la pile
void empile(t_pile *p, t_element e)
{
	//On utilise la pré incrémentation du C pour déplacer
	//le sommet avant d'insérer dans le tableau
	p->tab_elements[++p->sommet] = e;
}


//Retourne une copie de l'élément du dessus sans l'enlever de la pile
t_element getSansEnlever(t_pile* p)
{
	//Si on ne déplace pas le sommet, rien ne change et l'objet reste sur le dessus
	return p->tab_elements[p->sommet];
}

//Retourne le nombre d'éléments de la pile
int get_nb_elements(const t_pile* p)
{
	//Le sommet pointe sur l'indice de l'élément qui
	//se trouve 1 de moins que le nombre d'éléments
	return p->sommet + 1;
}


//Retourne l'élément sur le dessus et le retire de la pile
t_element desempile(t_pile* p)
{
	//On utilise la poist décrémentation du C pour déplacer
	//le sommet après avoir retourné l'élément.
	return p->tab_elements[p->sommet--];
}

//variante
//Procédure pour enlever un élément du haut d'une pile
//et le retourner via le paramètre formel en sortie
//void desempiler(t_pile *p, t_element *e)
//{
//  e = p->tab_elements[p->sommet--];
//}
