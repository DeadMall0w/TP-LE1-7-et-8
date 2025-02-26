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
	return 1;
	}
	
	
return 0;
	
}


int  afficherBibliotheque(const T_Bibliotheque  *ptrB)
{
	int i;
		if(ptrB->nbLivres==0)
	return 0;
	else
	{
		for(i=0;i<ptrB->nbLivres;i++)
			afficherLivre( &(ptrB->etagere[i])  );
			
		return 1;
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
int supprimerLivre(T_Bibliotheque *ptrB, const char* titre)
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
        }
    return 1;
    }
    else 
    {
        return 0;
    }
}




