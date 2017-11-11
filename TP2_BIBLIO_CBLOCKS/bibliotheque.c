#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "bibliotheque.h"


#define FICHIERBIBLIO "biblio.txt"


int main()
{
	// Déclaration des variables.
	int choix_menu = 0;
	int lecturefichier=0;
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
		case 2: lire_fichier(&bibli,&lecturefichier); break;
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

void lire_fichier(t_bibliotheque * pBibli, int * lecture)
{
    int cycle=*lecture;

    if(cycle == 0){
        FILE * fichierbiblio;
        int i;
        int nb_livre;
        int type_livre;
        char data[100];
        t_livre livre_temp;

        fichierbiblio = fopen(BIBLIO_FICHIER,"r+");

        if(fichierbiblio==NULL)
        {
            printf("Erreur de lecture du fichier %s ... \n", FICHIERBIBLIO);
        }

        else
        {
            fgets(data, TAILLE_TITRE, fichierbiblio);

            nb_livre = atoi(data);

            for(i = 0; i < nb_livre; i++)
            {
                fgets(data, TAILLE_TITRE, fichierbiblio);//permet de faire un saut de ligne
                fgets(data, TAILLE_TITRE, fichierbiblio); //genre
                type_livre = atoi(data);

                livre_temp.genre = (t_genre)type_livre;

                fgets(data, TAILLE_TITRE, fichierbiblio); //titre
                strcpy(livre_temp.titre, data);
                retirer_sautligne(livre_temp.titre);

                fgets(data, TAILLE_TITRE, fichierbiblio);
                strcpy(livre_temp.auteur_prenom, data);
                retirer_sautligne(livre_temp.auteur_prenom);

                fgets(data, TAILLE_TITRE, fichierbiblio);
                strcpy(livre_temp.auteur_nom, data);
                retirer_sautligne(livre_temp.auteur_nom);

                fgets(data, TAILLE_TITRE, fichierbiblio);
                livre_temp.nb_pages = atoi(data);

                fgets(data, TAILLE_TITRE, fichierbiblio);
                livre_temp.isbn = atoi(data);

                fgets(data, TAILLE_TITRE, fichierbiblio);
                livre_temp.bEmprunte = atoi(data);

                pBibli->livres[type_livre][pBibli->nb_livres[type_livre]] = livre_temp;
                pBibli->nb_livres[type_livre]++;

                if(pBibli->livres[type_livre][i].bEmprunte == 0)
                {
                    pBibli->rapport.nb_livres_dispo++;
                }
                else
                {
                    pBibli->rapport.nb_livres_emprunt++;
                }
            }

            printf("Lecture du fichier de bibliotheque");
            Sleep(500);
            printf(".");
            Sleep(500);
            printf(".");
            Sleep(500);
            printf(".");
            Sleep(500);
            printf("Done\n");
        }

        fclose(fichierbiblio);
        cycle++;
        super_pause();

    }

    else
    {
        printf("Vous avez deja ouvert le fichier %s ...\n",FICHIERBIBLIO);
        super_pause();
    }

    *lecture = cycle;
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
    system("cls");

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
	//Il faut initialiser les livre aussi ?

	//printf("TO BE CONTINUED...\n\n");
}

void initialiser_rapport(t_bibliotheque * pBibli)
{
    pBibli->rapport.nb_livres_dispo=0;
    pBibli->rapport.nb_livres_emprunt=0;
}

void sauvegarder_fichier(t_bibliotheque * pBibli)
{

    if(verifier_disp_bibliotheque(pBibli))
    {

        FILE * fichierbiblio;
        int i;
        int j;
        int nb_livre = 0;
        char data[100];

        fichierbiblio = fopen(BIBLIO_FICHIER,"w+");

        if(fichierbiblio==NULL){
            printf("Erreur de lecture du fichier %s ... \n", FICHIERBIBLIO);
        }

        else{

            for(i = 0; i < NB_GENRES; i++)
            {
                nb_livre += pBibli->nb_livres[i];
            }

            itoa(nb_livre, data, 10);
            fputs(data, fichierbiblio);
            fputs("\n\n", fichierbiblio);

            for(i = 0; i < NB_GENRES; i++)
            {
                for(j = 0; j < pBibli->nb_livres[i]; j++)
                {


                    itoa((int)pBibli->livres[i][j].genre, data, 10);
                    fputs(data, fichierbiblio);
                    fputs("\n", fichierbiblio);

                    strcpy(data, pBibli->livres[i][j].titre);
                    fputs(data, fichierbiblio);
                    fputs("\n", fichierbiblio);

                    strcpy(data, pBibli->livres[i][j].auteur_prenom);
                    fputs(data, fichierbiblio);
                    fputs("\n", fichierbiblio);

                    strcpy(data, pBibli->livres[i][j].auteur_nom);
                    fputs(data, fichierbiblio);
                    fputs("\n", fichierbiblio);

                    itoa(pBibli->livres[i][j].nb_pages, data, 10);
                    fputs(data, fichierbiblio);
                    fputs("\n", fichierbiblio);

                    itoa(pBibli->livres[i][j].isbn, data, 10);
                    fputs(data, fichierbiblio);
                    fputs("\n", fichierbiblio);

                    itoa(pBibli->livres[i][j].bEmprunte, data, 10);
                    fputs(data, fichierbiblio);
                    fputs("\n", fichierbiblio);

                    fputs("\n", fichierbiblio);
                }
            }

            printf("Sauvegarde en cours");
            Sleep(500);
            printf(".");
            Sleep(500);
            printf(".");
            Sleep(500);
            printf(".");
            Sleep(500);
            printf("Done\n");
        }



        fclose(fichierbiblio);
        super_pause();
    }

    else{
        printf("Vous ne pouvez pas sauvegarder vos modificiations avant d'avoir ouvert le fichier...\n");
        super_pause();
    }

}
void trier_livres(t_bibliotheque * pBibli)
{
	t_pile pile_livres;
	t_livre dernier_element;
	int dernier_isbn;
	int i;
	int j;
	int k;
	int nombre_livres = 0;

	init_pile(&pile_livres);

	dernier_element.isbn = 0;
	empile(&pile_livres, dernier_element);
	dernier_isbn = MAX_ISBN;


	nombre_livres = pBibli->rapport.nb_livres_dispo + pBibli->rapport.nb_livres_emprunt;

    for(k = 0; k < nombre_livres; k++)
    {
        empile(&pile_livres, dernier_element);

        for(i = 0; i < NB_GENRES; i++)
        {
            for(j = 0; j < pBibli->nb_livres[i]; j++)
            {
                if((getSansEnlever(&pile_livres).isbn < pBibli->livres[i][j].isbn) && (pBibli->livres[i][j].isbn < dernier_isbn))
                {
                    desempile(&pile_livres);
                    empile(&pile_livres, pBibli->livres[i][j]);
                }
            }
        }

        dernier_isbn = getSansEnlever(&pile_livres).isbn;
    }

    for(i = 0; i < nombre_livres; i++)
    {
        dernier_element = desempile(&pile_livres);
        printf("----------------- \n");
        printf("Titre: %s \n", dernier_element.titre);
        printf("Auteur: %s %s \n", dernier_element.auteur_prenom, dernier_element.auteur_nom);
        printf("Genre: %d \n", dernier_element.genre);
        printf("Pages: %d \n", dernier_element.nb_pages);
        printf("ISBN: %d \n", dernier_element.isbn);
        printf("Emprunte: %d \n", dernier_element.bEmprunte);
        printf("-----------------\n");
    }

    printf("\nLes livres on ete trie par ordre croissant de ISBN\n");
    super_pause();
}

void afficher_bibliotheque(t_bibliotheque * pBibli)
{
    int i;
    int j;


	if(verifier_disp_bibliotheque(pBibli))
    {
        system("cls");

        for(i = 0; i < NB_GENRES; i++)
        {
            for(j = 0; j < pBibli->nb_livres[i]; j++)
            {
                printf("-------------------------------\n");
                printf("Titre: %s \n", pBibli->livres[i][j].titre);
                printf("Auteur: %s %s \n", pBibli->livres[i][j].auteur_prenom, pBibli->livres[i][j].auteur_nom);
                printf("Genre: %d \n", pBibli->livres[i][j].genre);
                printf("Pages: %d \n", pBibli->livres[i][j].nb_pages);
                printf("ISBN: %d \n", pBibli->livres[i][j].isbn);
                printf("Emprunte: %d \n", pBibli->livres[i][j].bEmprunte);
                printf("-------------------------------\n");
            }
        }
    }
    else
    {
        printf("Bibliotheque vide, veuillez l'actualiser... \n");
    }

    super_pause();
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
    int isbn=0;
    int i=0;
    int j=0;

    if(verifier_disp_bibliotheque(pBibli)){

        printf("Entrez le ISBN du livre que vous voulez emprunter : ");
        scanf("%d",&isbn);


        pBibli->rapport.nb_livres_emprunt++;

    }
    else{

        printf("Pour emprunter un livre, vous devez ouvrir le fichier bibliotheque...\n");

    }

	super_pause();
}

void gerer_retours(t_bibliotheque * pBibli)
{
	printf("TO BE CONTINUED...\n\n");
}

void modifier_livre(t_bibliotheque * pBibli)
{
    if(verifier_disp_bibliotheque(pBibli))
    {


        int ISBN = 0;
        int i;
        int j;
        int int_data;
        char char_data[100];

        system("cls");

        printf("Entrez le ISBN du livre a modifier : ");
        scanf("%d", &ISBN);

        for(i = 0; i < NB_GENRES; i++)
        {
            for(j = 0; j < pBibli->nb_livres[i]; j++)
            {
                if(pBibli->livres[i][j].isbn == ISBN)
                {
                    printf("----------------- \n");
                    printf("Titre: %s \n", pBibli->livres[i][j].titre);
                    printf("Auteur: %s %s \n", pBibli->livres[i][j].auteur_prenom, pBibli->livres[i][j].auteur_nom);
                    printf("Genre: %d \n", pBibli->livres[i][j].genre);
                    printf("Pages: %d \n", pBibli->livres[i][j].nb_pages);
                    printf("ISBN: %d \n", pBibli->livres[i][j].isbn);
                    printf("Emprunte: %d \n", pBibli->livres[i][j].bEmprunte);
                    printf("-----------------\n");


                    printf("Entrez le nouveau genre: ");
                    scanf(" %d", &int_data);
                    pBibli->livres[i][j].genre = (t_genre)int_data;

                    printf("Ecrivez le nouveau titre du livre: ");
                    scanf (" %[^\n]%*c", char_data);;
                    strcpy(pBibli->livres[i][j].titre, char_data);

                    printf("Ecrivez le nouveau nom de l'auteur du livre: ");
                    scanf(" %s", char_data);
                    strcpy(pBibli->livres[i][j].auteur_nom, char_data);

                    printf("Ecrivez le nouveau prenom de l'auteur du livre: ");
                    scanf(" %s", char_data);
                    strcpy(pBibli->livres[i][j].auteur_prenom, char_data);

                    printf("Entrez le nouveau nombre de pages: ");
                    scanf(" %d", &int_data);
                    pBibli->livres[i][j].nb_pages = int_data;


                    printf("\nVous avez modifie le livre avec le ISBN: %d\n", ISBN);
                    super_pause();
                }
            }
        }
    }

    else{

        printf("Veuillez charger la bibliotheque avant de faire des modifications...\n");
        super_pause();
   }
}

void retirer_livre(t_bibliotheque * pBibli)
{
	if(verifier_disp_bibliotheque(pBibli))
	{
	    int ISBN = 0;
        int i;
        int j;
        int k;
        t_livre null_livre;
        int dispo = 0;

	    printf("Entrez le ISBN du livre a modifier : ");
        scanf("%d", &ISBN);

        for(i = 0; i < NB_GENRES; i++)
        {
            for(j = 0; j < pBibli->nb_livres[i]; j++)
            {
                if(pBibli->livres[i][j].isbn == ISBN)
                {
                    if(pBibli->livres[i][j].bEmprunte)
                    {
                        pBibli->rapport.nb_livres_emprunt--;
                    }
                    else
                    {
                        pBibli->rapport.nb_livres_dispo--;
                    }


                    for(k = j; k < (pBibli->nb_livres[i] - 1); k++)
                    {
                        pBibli->livres[i][k] = pBibli->livres[i][k + 1];
                    }

                    pBibli->livres[i][pBibli->nb_livres[i]] = null_livre;
                    pBibli->nb_livres[i]--;
                }
            }
        }


	}
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





