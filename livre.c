#include "livre.h"


void saisirLivre(T_livre * ptrL)
{
lireChaine("TITRE :", (ptrL->titre), MAX_TITRE );
lireChaine("AUTEUR :", (ptrL->auteur ), MAX);
lireChaine("CODE :", (ptrL->code), MAX_TITRE );
lireChaine("EDITEUR :", (ptrL->editeur ), MAX);
printf("ANNEE : ");
scanf("%d", &(ptrL->annee ));
}

void afficherLivre(const T_livre *ptrL)
{
afficherChaine("TITRE :", (ptrL->titre));
printf(" - ");
afficherChaine("AUTEUR :", (ptrL->auteur ));
printf("\n");
afficherChaine("CODE :", (ptrL->code));
printf(" - ");
afficherChaine("EDITEUR :", (ptrL->editeur ));
printf("\n");
printf("ANNEE : %d ",(ptrL->annee));
printf(" - ");
afficherChaine("EMPRUNTEUR :", (ptrL->emprunteur.nomemprunteur));
printf("\n");
}

