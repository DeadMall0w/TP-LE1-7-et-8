# include "biblio.h"



void init (T_Bibliotheque *ptrB)
{

ptrB->nbLivres=0;
// ou (*ptrB).nbLivres=0;
}

int ajouterLivre(T_Bibliotheque  *ptrB)
{
	if (ptrB->nbLivres<CAPACITE_BIBLIO)// reste t il de la place?
		{
		saisirLivre(&(ptrB->etagere[ptrB->nbLivres]));
		ptrB->nbLivres++;
		return OK;
		}
		
		
	return PAS_OK;
	
}


int  afficherBibliotheque(const T_Bibliotheque  *ptrB)
{
	int i;
	if(ptrB->nbLivres==0)
		return PAS_OK;
	else
	{
		for(i=0;i<ptrB->nbLivres;i++)
			afficherLivre( &(ptrB->etagere[i]));	

		return OK;
	}
}

int rechercherLivresParAuteur(const T_Bibliotheque *ptrB, const char * auteur)
{
	int i;
	if(ptrB->nbLivres==0)
		return 0;
	else
	{
		for(i=0; i < ptrB->nbLivres; i++){
			if(strcmp((ptrB->etagere[i].auteur), auteur) == 0){
				afficherLivre( &(ptrB->etagere[i]));
			}
		}

		return 1;
	}

}

int rechercherLivreParTitre(const T_Bibliotheque *ptrB, const char * titre)
{
	int i;
	if(ptrB->nbLivres==0)
		return -1;
	else
	{
		for(i=0; i < ptrB->nbLivres; i++){
			if(strcmp((ptrB->etagere[i].titre), titre) == 0){
				afficherLivre( &(ptrB->etagere[i]));
				return i;
			}
		}

		return -1; // si le livre n'est pas trouvé
	}
}

// fonction : supprimerLivre 
// entrée : T_Bibliotheque *ptrB, const char* titre
// sortie : 1 pour une suppression réussite 0 pour une suppression impossible 
// principe : recherche la position du titre du livre afin de décaler tous les livres précédent pour ecraser le livre. On decrémente de un le nombre de livres de la bibliothéque.
// ptrB = nom de la bibliothéque 
// titre = titre du livre à supprimer
int supprimerLivre(T_Bibliotheque *ptrB, const char* titre )
{
	// déclaration de i(variable utilitaire) et pos(position du livre)
	int pos,i;
	// vérifie que la suppression est possible
	if (ptrB->nbLivres > 0) 
	{
		pos = rechercherLivreParTitre(ptrB, titre);
		if ( pos >= 0 && pos < ptrB->nbLivres)
		{
			// décale tous les livres pour ecraser le livre à supprimer 
			for ( i = pos ; i < ptrB->nbLivres ; i++)
			{
				ptrB->etagere[i]= ptrB->etagere[i+1];
			}
			// decrémente de un le nombre de livres de la bibliothéque
			ptrB->nbLivres = ptrB->nbLivres - 1;

			return OK;
		}
	return PAS_OK;
	}
	else 
	{
		return PAS_OK;
	}
}

void sauvegarde(T_Bibliotheque *ptrB)
{
	FILE *fic=NULL; //le type FILE
	int i;
	fic=fopen("baseLivres","w"); // w = le mode = write avec ECRASEMENT
	//fopen renvoie NULL si probleme (disque plein, disque non accessible ...
	if (fic!=NULL)
	{
		for(i=0;i<ptrB->nbLivres;i++)
		{
	//fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
		fwrite(  &(ptrB->etagere[i])        ,sizeof(T_livre),1,fic);
		}
		fclose(fic);
		puts("SAUVEGARDE REUSSIE ..............");

	}
	else puts("ECHEC DE SAUVEGARDE  !!!!!  ");
}

void chargement(T_Bibliotheque *ptrB)
{
	FILE *fic=NULL; //le type FILE
	int i=0;
	fic=fopen("baseLivres","r"); // r = le mode read
	//fopen renvoie NULL si probleme (disque plein, disque non accessible ...
	if (fic!=NULL)
	{
		do
		{
			fread(  &(ptrB->etagere[i]) ,sizeof(T_livre),1,fic);
			i++;
		}while(!feof(fic));

		fclose(fic);
		ptrB->nbLivres=i-1;
		puts("CHARGEMENT  REUSSI ..............");
	}
	else puts("ECHEC DE CHARGEMENT  !!!!!  ");
}

int emprunt(T_Bibliotheque *ptrB, const char* titre, const char* nom)
{
	// déclaration de pos(position du livre)
	int pos;
	// vérifie que l'emprunt  est possible
	if (ptrB->nbLivres > 0) 
	{
		pos = rechercherLivreParTitre(ptrB, titre);
		if ( pos >= 0 && pos < ptrB->nbLivres)
		{
			stpcpy(ptrB->etagere[pos].emprunteur.nomemprunteur,nom);
		}
	return OK;
	}
	else 
	{
		return PAS_OK;
	}
} 



