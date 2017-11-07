#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bibliotheque.h"


#define FICHIERBIBLIO "biblio.txt"


int main()
{
	// Déclaration des variables.
	int choix_menu = 0;
	t_bibliotheque bibli;





	// Initialisation de la fonction rand()
	srand(time(NULL));

	// Initialisation de la bibliotheque
	initialiser_bibliotheque(&bibli);

    //initialisation du rapport
    initialiser_rapport(&bibli);


	do
	{
		// Gestion du menu.
		choix_menu = demander_choix_menu();

		switch (choix_menu)
		{
		case 1: afficher_bibliotheque(&bibli); break;
		case 2: lire_fichier(&bibli); break;
		case 3: modifier_livre(&bibli); break;
		case 4: retirer_livre(&bibli); break;
		case 5: emprunter_livre(&bibli); break;
		case 6: gerer_retours(&bibli); break;
		case 7: generer_rapport(&bibli); break;
		case 8: sauvegarder_fichier(&bibli); break;
		case 9: trier_livres(&bibli); break;
		case 0: break; // Quitter.
		default: exit(0); break;
		}
	} while (choix_menu != 0);

	exit(0);
	return EXIT_SUCCESS;
}

void lire_fichier(t_bibliotheque * pBibli)
{

    FILE * fichierbiblio;

    fichierbiblio = fopen("biblio.txt","rt");

    if(fichierbiblio==NULL){
        printf("Erreur de lecture du fichier %s ... \n", FICHIERBIBLIO);
        fclose(fichierbiblio);
    }

    else{

        


       fclose(fichierbiblio);
    }


    printf("Lecture du fichier de bibliotheque... Done\n");




}

void simuler_lire_fichier(t_bibliotheque * pBibli)
{
	t_livre livre1;
	t_livre livre2;
	t_livre livre3;

	livre1.genre = INFORMATIQUE;
	strcpy(livre1.titre, "Les Ninjas de l'Info 2");
	strcpy(livre1.auteur_prenom, "Yannick");
	strcpy(livre1.auteur_nom, "Roy");
	livre1.nb_pages = 252;
	livre1.isbn = 369;
	livre1.bEmprunte = DISPONIBLE;
	pBibli->livres[INFORMATIQUE][pBibli->nb_livres[INFORMATIQUE]] = livre1;
	pBibli->nb_livres[INFORMATIQUE]++;

	livre2.genre = INFORMATIQUE;
	strcpy(livre2.titre, "Les fous du code");
	strcpy(livre2.auteur_prenom, "Hugues");
	strcpy(livre2.auteur_nom, "Saulnier");
	livre2.nb_pages = 355;
	livre2.isbn = 1001;
	livre2.bEmprunte = DISPONIBLE;
	pBibli->livres[INFORMATIQUE][pBibli->nb_livres[INFORMATIQUE]] = livre2;
	pBibli->nb_livres[INFORMATIQUE]++;

	livre3.genre = FICTION;
	strcpy(livre3.titre, "Un tableau de pointeurs");
	strcpy(livre3.auteur_prenom, "Pasdor");
	strcpy(livre3.auteur_nom, "Mi");
	livre3.nb_pages = 180;
	livre3.isbn = 1234;
	livre3.bEmprunte = DISPONIBLE;
	pBibli->livres[FICTION][pBibli->nb_livres[FICTION]] = livre3;
	pBibli->nb_livres[FICTION]++;
}

void super_pause()
{
	printf("Appuyez sur une touche pour continuer! \n");
	_getch();
}

void retirer_sautligne(char * chaine)
{
	int pos = strlen(chaine) - 1;
	if (chaine != NULL && chaine[pos] == '\n')
		chaine[pos] = '\0'; // Si on trouve \n à la fin, on le remplace par \0
}

int demander_choix_menu(){
    int choix_user=0;

	printf("================================================================================\n");
	printf("                                Bibliotheque 2000\n");
	printf("================================================================================\n");

	printf("1 - Afficher Bibliotheque\n");
	printf("2 - Lire Fichier Bibliotheque\n");
	printf("3 - Modifier Livre\n");
	printf("4 - Retirer Livre\n");
	printf("5 - Emprunter Livre\n");
	printf("6 - Retourner Livre (Lundi Matin)\n");
	printf("7 - Generer Rapport\n");
	printf("8 - Sauvegarder Bibliotheque\n");
	printf("9 - Trier Livres (bonus)\n");
    printf("0 - Quitter");
    printf("\n\n");

	printf("================================================================================\n");

        do{

         scanf("%d",&choix_user);

        }while(choix_user < 0 || choix_user > 9);

}

void initialiser_bibliotheque(t_bibliotheque * pBibli)
{
    int i;

    for(i = 0; i < NB_GENRES; i++)
    {
        pBibli->nb_livres[i] = 0;
    }
}

void initialiser_livre(t_livre * pLivre)
{
	printf("TO BE CONTINUED...\n\n");
}

void initialiser_rapport(t_bibliotheque * pBibli)
{

        pBibli->rapport.nb_livres_dispo=0;
        pBibli->rapport.nb_livres_emprunt=0;

}

void sauvegarder_fichier(t_bibliotheque * pBibli)
{
	printf("TO BE CONTINUED...\n\n");
}

void trier_livres(t_bibliotheque * pBibli)
{
	printf("TO BE CONTINUED...\n\n");
}

void afficher_bibliotheque(t_bibliotheque * pBibli)
{
	if(verifier_disp_bibliotheque(pBibli))
    {
        printf("La bibliothque est charger...\n");
        super_pause();


    }
    else
    {
        printf("Bibliotheque vide, veuillez l'actualiser... \n");
        super_pause();
    }
}

void generer_rapport(t_bibliotheque * pBibli)
{


    printf("#######################################\n");
	printf("Nombre de livres disponibles : %d\n",pBibli->rapport.nb_livres_dispo);
	printf("Nombre de livres emprunts : %d\n",pBibli->rapport.nb_livres_emprunt);
    printf("#######################################\n");
    super_pause();

}

void emprunter_livre(t_bibliotheque * pBibli)
{
	printf("TO BE CONTINUED...\n\n");
}

void gerer_retours(t_bibliotheque * pBibli)
{
	printf("TO BE CONTINUED...\n\n");
}

void modifier_livre(t_bibliotheque * pBibli)
{
	printf("TO BE CONTINUED...\n\n");
}

void retirer_livre(t_bibliotheque * pBibli)
{
	printf("TO BE CONTINUED...\n\n");
}


int verifier_disp_bibliotheque(t_bibliotheque * pBibli)
{
    int i;
    int rempli = 0;
    for(i = 0; i < NB_GENRES; i++)
    {
        if (pBibli->nb_livres[i] != 0)
        {
            rempli++;
        }
    }

    return rempli;
}


