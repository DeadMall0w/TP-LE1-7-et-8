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
			{
			printf("--------------------------------------------------------- Livre %d :--------------------------------------------------------- \n",(i+1));
			afficherLivre( &(ptrB->etagere[i])  );
			
			}

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

int emprunt(T_Bibliotheque *ptrB, const char* titre, const T_Emp *emprunteur)
{
	// déclaration de pos(position du livre)
	int pos;
	// vérifie que l'emprunt  est possible
	if (ptrB->nbLivres > 0) 
	{
		pos = rechercherLivreParTitre(ptrB, titre);
		if ( pos >= 0 && pos < ptrB->nbLivres)
		{
			if ( *ptrB->etagere[pos].emprunteur.nomemprunteur == '\0'){
				stpcpy(ptrB->etagere[pos].emprunteur.nomemprunteur,emprunteur->nomemprunteur);
				lireDateSysteme(&ptrB->etagere[pos].emprunteur);
			}else{
				return PAS_OK;
			}
		}else{
			return PAS_OK;
		}
	return OK;
	}
	else 
	{
		return PAS_OK;
	}
} 


int rendre(T_Bibliotheque *ptrB, const char* titre){
	// déclaration de pos(position du livre)
	int pos;
	// vérifie que l'emprunt  est possible
	if (ptrB->nbLivres > 0) 
	{
		pos = rechercherLivreParTitre(ptrB, titre);
		if ( pos >= 0 && pos < ptrB->nbLivres)
		{
			if ( *ptrB->etagere[pos].emprunteur.nomemprunteur != '\0'){
				stpcpy(ptrB->etagere[pos].emprunteur.nomemprunteur,"");
			}else{
				return PAS_OK;
			}
		}
		return OK;
	}
	else 
	{
		return PAS_OK;
	}
}

void swap(T_livre* xp, T_livre* yp){
    T_livre temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Le but de cette fonction est de trier par titre les données
int trier_titre(T_Bibliotheque *ptrB){
	int i, j;
    char swapped;
    for (i = 0; i < ptrB->nbLivres - 1; i++) {
		swapped = 0;
        for (j = 0; j < ptrB->nbLivres - i - 1; j++) {
            if (strcmp(ptrB->etagere[j].titre,ptrB->etagere[j+1].titre) > 0) {
                swap(&ptrB->etagere[j], &ptrB->etagere[j+1]);
                swapped = 1;
            }
        }

        // If no two elements were swapped by inner loop,
        // then break
        if (swapped == 0)
            break;
    }
	
	return OK;
}


// Le but de cette fonction est de trier par titre les données
int trier_auteur(T_Bibliotheque *ptrB){
	int i, j;
    char swapped;
    for (i = 0; i < ptrB->nbLivres - 1; i++) {
		swapped = 0;
        for (j = 0; j < ptrB->nbLivres - i - 1; j++) {
            if (strcmp(ptrB->etagere[j].auteur, ptrB->etagere[j+1].auteur) > 0) {
                swap(&ptrB->etagere[j], &ptrB->etagere[j+1]);
                swapped = 1;
            }
        }

        // If no two elements were swapped by inner loop,
        // then break
        if (swapped == 0)
            break;
    }
	
	return OK;
}

int trier_annee(T_Bibliotheque *ptrB){
	int i, j;
    char swapped;
    for (i = 0; i < ptrB->nbLivres - 1; i++) {
		swapped = 0;
        for (j = 0; j < ptrB->nbLivres - i - 1; j++) {
            if (ptrB->etagere[j].annee < ptrB->etagere[j+1].annee) {
                swap(&ptrB->etagere[j], &ptrB->etagere[j+1]);
                swapped = 1;
            }
        }

        // If no two elements were swapped by inner loop,
        // then break
        if (swapped == 0)
            break;
    }
	
	return OK;
}


void lireDateSysteme(T_Emp *E)
{
	char j[9],m[10],h[9],mer[11],vir[2];
	int d,a;


	system("date > ladate"	);
	FILE * fic=NULL;  // pointeur de fichier
	fic=fopen("ladate","r"); //fileOpen en mode 'r'EAD

	//ici , si fic vaut NULL, alors le fopen a indiquÃ©
	//que le fichier ladate n'est pas accessible
	if (fic!=NULL)
		{
		while(!feof(fic))	
			{
			fscanf(fic,"%s %d %s %d %s %s %s",j,&d,m,&a,vir,h,mer);		
			if (!feof(fic)) 
				//printf("\n-->LU : %s- %d- %s- %d- %s- %s",j,d,m,a,h,mer);		
				printf("\n");
			}
		fclose(fic);

	if (strcmp(j,"lundi")==0) E->lejour=lu;
	if (strcmp(j,"mardi")==0) E->lejour=ma;
	if (strcmp(j,"mercredi")==0) E->lejour=me;
	if (strcmp(j,"jeudi")==0) E->lejour=je;
	if (strcmp(j,"vendredi")==0) E->lejour=ve;
	if (strcmp(j,"samedi")==0) E->lejour=sa;
	if (strcmp(j,"dimanche")==0) E->lejour=di;

	E->ledate=d;

	if (strcmp(m,"janvier")==0) E->lemois=janv;
	if (strcmp(m,"fevrier")==0) E->lemois=fevr;
	if (strcmp(m,"mars")==0) E->lemois=mars;
	if (strcmp(m,"avril")==0) E->lemois=avri;
	if (strcmp(m,"mai")==0) E->lemois=mai;
	if (strcmp(m,"juin")==0) E->lemois=juin;
	if (strcmp(m,"juillet")==0) E->lemois=juil;
	if (strcmp(m,"aout")==0) E->lemois=aout;
	if (strcmp(m,"septembre")==0) E->lemois=sept;
	if (strcmp(m,"octobre")==0) E->lemois=octo;
	if (strcmp(m,"novembre")==0) E->lemois=nove;
	if (strcmp(m,"decembre")==0) E->lemois=dece;

	E->timeStamp = time(NULL);
	E->lannee=a;
		}
		else
		{
			printf("n souci avec la date systeme !!");
			
			//on range une date irrÃ©elle 
			E->lejour=di;
			E->ledate=99;
			E->lemois=dece;
			E->lannee=-999;


		}

}

int livreRetard(T_Bibliotheque* B){
	int currentTime = time(NULL);

	for (int i = 0; i < B->nbLivres; i++)
	{
		if (strcmp(B->etagere[i].emprunteur.nomemprunteur, "") != 0)
		{

			if (B->etagere[i].emprunteur.timeStamp + TEMPS_LOCATION < currentTime){
				// le livre est en retard 
				printf("%s - %s \n", B->etagere[i].titre, B->etagere[i].emprunteur.nomemprunteur);
			}
		}
	}
	

	return OK;

}


int listeLivreDisponible(T_Bibliotheque* ptrB){
	int i;
	if(ptrB->nbLivres==0)
		return PAS_OK;
	else
	{
		for(i=0;i<ptrB->nbLivres;i++)
		{
			
			if (strcmp(ptrB->etagere[i].emprunteur.nomemprunteur, "") == 0)
			{
				printf("--------------------------------------------------------- Livre %d :--------------------------------------------------------- \n",(i+1));
				afficherLivre( &(ptrB->etagere[i])  );
			}
		}

		return OK;
	}
}
