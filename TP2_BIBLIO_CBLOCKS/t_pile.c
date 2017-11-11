#include "t_pile.h"

/*
*STRAT�GIE : Nous avons d�cid� d'impl�menter la pile dans un tableau statique de MAX_PILE �l�ments d�fini dans pile.h
*
*             -� chaque ajout on incr�mente le sommet avant d'ins�rer dans le tableau d'�l�ments (voir t_pile)
*             - La pile est vide si le somme == PILE_VIDE
*             - La pile est pleine si le sommet == MAX_PILE - 1 (ou sommet + 1 == MAX_PILE)
*             - � chaque retrait, on d�cr�mente le sommet apr�s avoir retourn� l'�l�ment point� par celui-ci
*
*
*/


//Proc�dure pour initialiser une pile, la pile est vide
//� utiliser pour vider une pile.
void init_pile(t_pile *p)
{
	p->sommet = PILE_VIDE;
}

//Retourne si une pile est pleine ou non
int  est_pleine(const t_pile *p)
{

	//Les indices vont de 0 � MAX_PILE - 1
	return p->sommet == MAX_PILE - 1;
}

//Retourne si une pile est vide ou non
int  est_vide(const t_pile *p)
{
	return p->sommet == PILE_VIDE;
}

//Ajoute l'�l�ment re�u sur le dessus de la pile
void empile(t_pile *p, t_element e)
{
	//On utilise la pr� incr�mentation du C pour d�placer
	//le sommet avant d'ins�rer dans le tableau
	p->tab_elements[++p->sommet] = e;
}


//Retourne une copie de l'�l�ment du dessus sans l'enlever de la pile
t_element getSansEnlever(t_pile* p)
{
	//Si on ne d�place pas le sommet, rien ne change et l'objet reste sur le dessus
	return p->tab_elements[p->sommet];
}

//Retourne le nombre d'�l�ments de la pile
int get_nb_elements(const t_pile* p)
{
	//Le sommet pointe sur l'indice de l'�l�ment qui
	//se trouve 1 de moins que le nombre d'�l�ments
	return p->sommet + 1;
}


//Retourne l'�l�ment sur le dessus et le retire de la pile
t_element desempile(t_pile* p)
{
	//On utilise la poist d�cr�mentation du C pour d�placer
	//le sommet apr�s avoir retourn� l'�l�ment.
	return p->tab_elements[p->sommet--];
}

//variante
//Proc�dure pour enlever un �l�ment du haut d'une pile
//et le retourner via le param�tre formel en sortie
//void desempiler(t_pile *p, t_element *e)
//{
//  e = p->tab_elements[p->sommet--];
//}
