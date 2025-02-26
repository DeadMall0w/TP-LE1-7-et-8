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
<<<<<<< Updated upstream
int i;
if(ptrB->nbLivres==0)
	return 0;
=======
	int i;
		if(ptrB->nbLivres==0)
	return PAS_OK;
>>>>>>> Stashed changes
	else
		{
		for(i=0;i<ptrB->nbLivres;i++)
			{
			afficherLivre( &(ptrB->etagere[i])  );
			
<<<<<<< Updated upstream
=======
		return OK;
	}
}

int rechercherLivresParAuteur(const T_Bibliotheque *ptrB, const char * auteur)
{
	int i;
	if(ptrB->nbLivres==0)
		return PAS_OK;
	else
	{
		for(i=0; i < ptrB->nbLivres; i++){
			if(strcmp((ptrB->etagere[i].auteur), auteur) == 0){
				afficherLivre( &(ptrB->etagere[i]));
>>>>>>> Stashed changes
			}

<<<<<<< Updated upstream

		
		return 1;
		}
=======
		return OK;
	}

}

int rechercherLivreParTitre(const T_Bibliotheque *ptrB, const char * titre)
{
	int i;
	if(ptrB->nbLivres==0)
		return PAS_OK;
	else
	{
		for(i=0; i < ptrB->nbLivres; i++){
			if(strcmp((ptrB->etagere[i].titre), titre) == 0){
				afficherLivre( &(ptrB->etagere[i]));
				return i;
			}
		}

		return PAS_OK; // si le livre n'est pas trouvé

	}

>>>>>>> Stashed changes
}

// fonction : supprimerLivre 
// entrée : T_Bibliotheque *ptrB, const char* titre
// sortie : 1 pour une suppression réussite 0 pour une suppression impossible 
// principe : recherche la position du titre du livre afin de décaler tous les livres précédent pour ecraser le livre. On decrémente de un le nombre de livres de la bibliothéque.
// ptrB = nom de la bibliothéque 
// titre = titre du livre à supprimer
int supprimerLivre(T_Bibliotheque *ptrB, const char* titre )
{
<<<<<<< Updated upstream
	// déclaration de i(variable utilitaire) et pos(position du livre)
	int pos,i;
	// vérifie que la suppression est possible
	if (ptrB->nbLivres > 0) 
	{
		pos = rechercheLivreParTitre(&ptrB, titre);
		if ( pos >= 0 && pos < ptrB->nbLivres)
		{
			// décale tous les livres pour ecraser le livre à supprimer 
			for ( i = pos ; i < ptrB->nbLivres ; i++)
			{
				ptrB->etagere[i]= ptrB->etagere[i+1];
			}
			// decrémente de un le nombre de livres de la bibliothéque
			ptrB->nbLivres = ptrB->nbLivres - 1;
		}
	return 1;
	}
	else 
	{
		return 0;
	}
=======
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
        }
    return OK;
    }
    else 
    {
        return PAS_OK;
    }
>>>>>>> Stashed changes
}




