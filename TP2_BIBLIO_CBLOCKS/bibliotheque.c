
/******************************************************************************
//TP2 - Bibliotheque virtuel
//Gabarit originale par Yannick Roy
//****************************************************************************
//TP2 fait par
//Badr Jaidi & Felix-Olivier Moreau
//Les commentaires qui suivent seront pour decrire notre fonctionnement
//*****************************************************************************/

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
	int choix_menu = 0; //choix du menu option
	int lecturefichier=0; //verification de la lecture fichier
	t_bibliotheque bibli; //fichier principale de bibliotheque

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

/******************************************************************************
//Lire_Fichier
// ****************************************************************************
//
// La fonction permet de lire le fichier biblio.txt qui se trouve dans le
// dossier du programme.Ensuite, il est enregistrer dans un tableau bibli.
// Paramètres 	: t_bibliotheque * pBibli, int * lecture.
// Retour 		: Void.
//*****************************************************************************/
void lire_fichier(t_bibliotheque * pBibli, int * lecture)
{

    int cycle=*lecture;

    if(cycle == 0)
    {
        FILE * fichierbiblio; //fichier FILE
        int i; //variable d'incrementation
        int nb_livre;
        int type_livre;
        char data[100]; //pour stocker de l'information
        t_livre livre_temp; //fichier de livre temporaire

        fichierbiblio = fopen(BIBLIO_FICHIER,"r+");

        //verifie si le fichier s'ouvre
        if(fichierbiblio==NULL)
        {
            printf("Erreur de lecture du fichier %s ... \n", FICHIERBIBLIO);
        }

        //Si le fichier s'ouvre et transfert vers livre temporaire
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


                //pour chaque livre analyser, on les classes comme disponible ou emprunter
                if(pBibli->livres[type_livre][i].bEmprunte == 0)
                {
                    pBibli->rapport.nb_livres_dispo++;
                }
                else
                {
                    pBibli->rapport.nb_livres_emprunt++;
                }
            }

            //effet d'attente
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

        fclose(fichierbiblio);//ferme le fichier
        cycle++;
        super_pause();

    }
    //ce else permet d'empecher le reouverture du fichier pour eviter un bug
    else
    {
        printf("Vous avez deja ouvert le fichier %s ...\n",FICHIERBIBLIO);
        super_pause();
    }
    //envois le cycle au pointeur de lecture
    *lecture = cycle;
}

/******************************************************************************
//Super_Pause
// ****************************************************************************
//
// Permet d'avoir un option "Touch Key for Continued"
//*****************************************************************************/
void super_pause()
{
	printf("Appuyez sur une touche pour continuer! \n");
	_getch();
}

/******************************************************************************
//retirer_sautligne
// ****************************************************************************
//
// Permet de garder une chaine de caracteres en une seule ligne
//*****************************************************************************/
void retirer_sautligne(char * chaine)
{
	int pos = strlen(chaine) - 1;
	if (chaine != NULL && chaine[pos] == '\n')
		chaine[pos] = '\0'; // Si on trouve \n à la fin, on le remplace par \0
}

/******************************************************************************
//demander_choix_menu
// ****************************************************************************
//
// Fonction qui permet a l'utilisateur de choisir une option dans le menu
// integration d'une limite si les choix sont hors demande
// Retour 		: Void.
//*****************************************************************************/
int demander_choix_menu(){
    system("cls");//efface l'ecran

    int choix_user=0; //variable pour le choix

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

    }while(choix_user < 0 || choix_user > 9); //limite du choix de l'utilisateur

}

/******************************************************************************
//Initialiser_bibliotheque
// ****************************************************************************
//
//Permet de mettre a 0 tous les livres de tous les genres
//
// Paramètres 	: t_bibliotheque * pBibli.
// Retour 		: Void.
//*****************************************************************************/
void initialiser_bibliotheque(t_bibliotheque * pBibli)
{
    int i;

    for(i = 0; i < NB_GENRES; i++)
    {
        pBibli->nb_livres[i] = 0;
    }
}

/******************************************************************************
//initialiser rapport d'emprunt et de disponibilite
// ****************************************************************************
//
// La fonction permet de lire le fichier biblio.txt qui se trouve dans le
// dossier du programme.Ensuite, il est enregistrer dans un tableau bibli.
// Paramètres 	: t_bibliotheque * pBibli.
// Retour 		: Void.
//*****************************************************************************/
void initialiser_rapport(t_bibliotheque * pBibli)
{
    pBibli->rapport.nb_livres_dispo=0;
    pBibli->rapport.nb_livres_emprunt=0;
}

/******************************************************************************
//Sauvegarder_fichier
// ****************************************************************************
//
// permet de prendre les modifications du tableau de bibli et de les sauvegarder
// dans le fichier de biblio.txt
// Paramètres 	: t_bibliotheque * pBibli.
// Retour 		: Void.
//*****************************************************************************/
void sauvegarder_fichier(t_bibliotheque * pBibli)
{

    if(verifier_disp_bibliotheque(pBibli))
    {

        FILE * fichierbiblio; //fichier de biblio.txt
        int i; //variable d'incrementation
        int j; //variable d'incrementation
        int nb_livre = 0;
        char data[100];

        fichierbiblio = fopen(BIBLIO_FICHIER,"w+"); //ouvre le fichier pour ecriture W+

        //permet de verifier si le fichier ouvre
        if(fichierbiblio==NULL){
            printf("Erreur de lecture du fichier %s ... \n", FICHIERBIBLIO);
        }

        //si le fichier ouvre...
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
            //effet de chargement
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

        fclose(fichierbiblio);//ferme le fichier biblio.txt
        super_pause();
    }
    //message si la lecture n'a pas ete fait
    else
    {
        printf("Vous ne pouvez pas sauvegarder vos modificiations avant d'avoir ouvert le fichier...\n");
        super_pause();
    }

}

/******************************************************************************
//Trier_livres
// ****************************************************************************
//
// Cette fonction est pour le Bonus. Il permet de trier les livre en ordre
// croissant.
//
// Paramètres 	: t_bibliotheque * pBibli.
// Retour 		: Void.
//*****************************************************************************/
void trier_livres(t_bibliotheque * pBibli)
{
    if(verifier_disp_bibliotheque(pBibli))
    {
        t_pile pile_livres;
        t_livre dernier_element;
        int dernier_isbn;
        int i;
        int j;
        int k;
        int nombre_livres = 0;

        init_pile(&pile_livres);

        dernier_element.isbn = 0;//initialiser le dernier element pour etre sur que tout va etre compare a la plus petite valeur possible
        empile(&pile_livres, dernier_element);//mettre la plus petite valeur possible dans la pile au debut pour pouvoir la comparer
        dernier_isbn = MAX_ISBN;//initialiser le dernier ISBN a la valeur max pour que le premier ISBN puisse etre enregistre


        nombre_livres = pBibli->rapport.nb_livres_dispo + pBibli->rapport.nb_livres_emprunt;//le nombre de livres total, donc livres disponibles et empruntes

        for(k = 0; k < nombre_livres; k++) //boucle pour comparer tout les livres un par un
        {
            empile(&pile_livres, dernier_element);//etre sur de comparer a la plus petite valeur possible

            //on compare chacun des livres a tout les autres livres pour touver qui est plus grand
            for(i = 0; i < NB_GENRES; i++)
            {
                for(j = 0; j < pBibli->nb_livres[i]; j++)
                {
                    //Si il est plus grand que le livre dans la pile et plus petit que celui qui etait la avant, on sait que il est a la bonne place
                    if((getSansEnlever(&pile_livres).isbn < pBibli->livres[i][j].isbn) && (pBibli->livres[i][j].isbn < dernier_isbn))
                    {
                        //on remplace dans la pile par celui qui est plus grand
                        desempile(&pile_livres);
                        empile(&pile_livres, pBibli->livres[i][j]);
                    }
                }
            }

            dernier_isbn = getSansEnlever(&pile_livres).isbn;//mettre le dernier livre rajouter pour etre sur que celui qui va suivre ne va pas etre plus grand
        }

        //Les livres sont affiches un par un en ordre croissant a partir de la pile
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
    //ce message est si la lecture de bibliotecque n'a pas ete fait
    else
    {
        printf("Impossible de trier la bibliotheque... Veuillez lire le fichier %s avant de trier\n",FICHIERBIBLIO);
        super_pause();
    }
}

/******************************************************************************
//afficher_bibliotheque
// ****************************************************************************
//
//Fonction avec des boucles afin d'afficher a l'utilisateur tous les livres.
//
// Paramètres 	: t_bibliotheque * pBibli.
// Retour 		: Void.
//*****************************************************************************/
void afficher_bibliotheque(t_bibliotheque * pBibli)
{
    int i; //variable d'incrementation
    int j; //variable d'incrementation


	if(verifier_disp_bibliotheque(pBibli))
    {
        system("cls"); //efface l'ecran

        //va chercher tous les livres de toutes les categories
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
    //le message est si la lecture du fichier biblio.txt n'a pas ete fait
    else
    {
        printf("Bibliotheque vide, veuillez l'actualiser... \n");
    }

    super_pause();
}

/******************************************************************************
//Generer rapport
// ****************************************************************************
//
// Cette fonction permet d'afficher le rapport avec les informations que nous
// avons enregistrer dans la biblio
//
// Paramètres 	: t_bibliotheque * pBibli.
// Retour 		: Void.
//*****************************************************************************/
void generer_rapport(t_bibliotheque * pBibli)
{
    printf("#######################################\n");
	printf("Nombre de livres disponibles : %d\n",pBibli->rapport.nb_livres_dispo);
	printf("Nombre de livres emprunts : %d\n",pBibli->rapport.nb_livres_emprunt);
    printf("#######################################\n");
    super_pause();
}

/******************************************************************************
//emprunter_livre
// ****************************************************************************
//
// Fonction qui permet de gerer l'emprunt des livres
//
// Paramètres 	: t_bibliotheque * pBibli.
// Retour 		: Void.
//*****************************************************************************/
void emprunter_livre(t_bibliotheque * pBibli)
{
    int isbn=0;
    int i=0; //variable d'incrementation
    int j=0; //variable d'incrementation
    int resultat=100;

    if(verifier_disp_bibliotheque(pBibli)){

        resultat = 0;
        //le choix du ISBN de l'utilisateur
        printf("Entrez le ISBN du livre que vous voulez emprunter : ");
        scanf("%d",&isbn);

        //verifie chaque livre afin de voir si le ISBN de l'utilsateur existe
        for(i = 0; i < NB_GENRES; i++)
        {
            for(j = 0; j < pBibli->nb_livres[i]; j++)
            {
                if(pBibli->livres[i][j].isbn == isbn)
                {

                    if(pBibli->livres[i][j].bEmprunte == 1)
                    {
                            resultat = 2;
                    }

                    if(pBibli->livres[i][j].bEmprunte == 0)
                    {
                        pBibli->livres[i][j].bEmprunte = 1 ;
                        resultat = 1;
                    }

                }
            }
        }

        //si le ISBN de l'utilisateur est disponible
        if(resultat == 1 )
        {
            pBibli->rapport.nb_livres_emprunt++;
            pBibli->rapport.nb_livres_dispo--;

            printf("le livre de ISBN %d est maintenant emprunter!...\n",isbn);

        }
        //si le ISBN de l'utilisateur est deja emprunter
        if(resultat == 2)
        {
            printf("Le livre de ISBN %d est deja emprunter ... \n",isbn);
        }

        //si le ISBN de l'utilisateur est pas trouvable
        if(resultat == 0)
        {
            printf("le livre de ISBN %d est introuvable dans le fichier %s ...\n",isbn,FICHIERBIBLIO);
        }
    }
    //ce message est si le fichier biblio.txt n'a pas ete lu
    else
    {
        printf("Pour emprunter un livre, vous devez ouvrir le fichier bibliotheque %s...\n",FICHIERBIBLIO);
    }

	super_pause();
}

/******************************************************************************
//gerer_retours
// ****************************************************************************
//
// Permet de remettre le rapport d'emprunt a 0
// Permet de remettre disponible les livres de la bibliotheque
//
// Paramètres 	: t_bibliotheque * pBibli.
// Retour 		: Void.
//*****************************************************************************/
void gerer_retours(t_bibliotheque * pBibli)
{
    int i=0; //variable d'incrementation
    int j=0; //variable d'incrementation

    //si le fichier biblio.txt a ete lu
    if(verifier_disp_bibliotheque(pBibli))
    {
        pBibli->rapport.nb_livres_dispo += pBibli->rapport.nb_livres_emprunt;//livre disponible obtient la valeur de livre emprunter
        pBibli->rapport.nb_livres_emprunt=0; //livre emprunter devient 0

        //tous les livres de tous les genres mettre leur valeur d'emprunter a 0
        for(i = 0; i < NB_GENRES; i++)
        {
            for(j = 0; j < pBibli->nb_livres[i]; j++)
            {
                    pBibli->livres[i][j].bEmprunte=0;
            }
        }

       printf("Tous les livres sont retourner et disponible ...\n");

	}
    //si le fichier biblio.txt n'a pas ete lu
	else{

        printf("Vous devez lire le fichier %s avant de faire des retours ...\n",FICHIERBIBLIO);
	}


    super_pause();

}
/******************************************************************************
//modifier_livre
// ****************************************************************************
//
//Cette fonction permet de choisir un livre par son ISBN et de modifier son contenue
//
// Paramètres 	: t_bibliotheque * pBibli.
// Retour 		: Void.
//*****************************************************************************/
void modifier_livre(t_bibliotheque * pBibli)
{
    int resultat = 0; //varible qui permet d'avoir des conditions
    int ISBN = 0;

    if(verifier_disp_bibliotheque(pBibli))
    {
        int i; //variable d'incrementation
        int j; //variable d'incrementation
        int int_data;
        char char_data[100];

        system("cls"); //efface l'ecran

        //enregistre le choix de l'utilisateur dans la variable ISBN
        printf("Entrez le ISBN du livre a modifier : ");
        scanf("%d", &ISBN);

        //trouve le ISBN de l'utilisateur parmis le tableau des livres
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

                    //section de modification du livre de l'utilisateur
                    do{
                        printf("Entrez le nouveau genre: ");
                        scanf(" %d", &int_data);
                    }
                    while(int_data < 0 || int_data > 5);

                    pBibli->livres[i][j].genre = (t_genre)int_data;

                    printf("Ecrivez le nouveau titre du livre: ");
                    scanf (" %[^\n]%*c", char_data);
                    strcpy(pBibli->livres[i][j].titre, char_data);

                    printf("Ecrivez le nouveau nom de l'auteur du livre: ");
                    scanf(" %s", char_data);
                    strcpy(pBibli->livres[i][j].auteur_nom, char_data);

                    printf("Ecrivez le nouveau prenom de l'auteur du livre: ");
                    scanf(" %s", char_data);
                    strcpy(pBibli->livres[i][j].auteur_prenom, char_data);

                    do{
                        printf("Entrez le nouveau nombre de pages: ");
                        scanf(" %d", &int_data);
                    }
                    while(int_data<0);

                    pBibli->livres[i][j].nb_pages = int_data;

                    resultat++;// si un livre a ete trouve, on le signale

                    printf("\nVous avez modifie le livre avec le ISBN: %d\n", ISBN);
                    super_pause();

                }
            }
        }

        //si le ISBN de l'utilisateur est introuvable
        if(resultat == 0)
        {
            printf("ISBN %d est introuvable...\n",ISBN);
            super_pause();
        }
    }
    //si le fichier biblio.txt n'a pas ete lu
    else
    {
        printf("Veuillez charger la bibliotheque avant de faire des modifications...\n");
        super_pause();
    }


}
/******************************************************************************
//retirer_livre
// ****************************************************************************
//
// Cette fonction permet de retirer un livre de la bibliotheque
//
// Paramètres 	: t_bibliotheque * pBibli.
// Retour 		: Void.
//*****************************************************************************/
void retirer_livre(t_bibliotheque * pBibli)
{
        //si la lecture du fichier biblio.txt a ete lu
        if(verifier_disp_bibliotheque(pBibli))
        {
            int ISBN = 0;
            int i; //variable d'incrementation
            int j; //variable d'incrementation
            int k; //variable d'incrementation
            t_livre null_livre;
            int dispo = 0;

            //choix de l'tulisateur sur le ISBN a suprimer
            printf("Entrez le ISBN du livre a modifier : ");
            scanf("%d", &ISBN);

            for(i = 0; i < NB_GENRES; i++)
            {
                for(j = 0; j < pBibli->nb_livres[i]; j++)
                {
                    if(pBibli->livres[i][j].isbn == ISBN)
                    {
                        //Mettre a jour le rapport selon le status du livre
                        if(pBibli->livres[i][j].bEmprunte)
                        {
                            pBibli->rapport.nb_livres_emprunt--;
                        }
                        else
                        {
                            pBibli->rapport.nb_livres_dispo--;
                        }


                        //Pousser toutes les cases de livres a gauche a la place du livre enleve
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

        //si le fichier biblio.txt n'a pas ete lu
        else{
            printf("Pour retirer un livre, vous devez lire le fichier de bibliotheque %s \n",FICHIERBIBLIO);
            super_pause();
        }
}

/******************************************************************************
//verifier_disp_bibliotheque
// ****************************************************************************
//
// Cette fonction est tres utiliser dans plusieurs des fonctions. Permet de verifier
// si la le fichier biblio.txt a ete lu dans l'option 2 de choix menu
//
// Paramètres 	: t_bibliotheque * pBibli.
// Retour 		: int.
//*****************************************************************************/
int verifier_disp_bibliotheque(t_bibliotheque * pBibli)
{
    int i; //variable d'incrementation
    int rempli = 0; //variable de return pour savoir si le fichier est lu ou pas
    for(i = 0; i < NB_GENRES; i++)
    {
        if (pBibli->nb_livres[i] != 0)
        {
            rempli++; //s'il y a pas de 0, alors fichier lu
        }
    }

    return rempli;
}





