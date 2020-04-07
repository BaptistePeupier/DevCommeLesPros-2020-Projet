#include "personne.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Fonctions memrbes de la calsse Personne                                                                       //
//                                                                                                               //
// PEUPIER Baptiste                                                                                              //
// Cree le 06/04/2020, modifié le 07/04/2020                                                                     //
//                                                                                                               //
// Polytech Marseille, informatique 3A                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Un constructeur
Personne::Personne(int index, char* nom, char* prenom, char* mail, char* codePostal, Competence & CompetencesPropres, Personne & AncienCollegueNext, Personne & AncienColleguePrevious, Entreprise & EntrepriseActuelle)
{
    return ;
}

// Le destructeur
Personne::~Personne(void)
{
    return ;
}

// Accesseurs
int Personne::index(void)
{
    return 0 ;
}

char* Personne::nom(void)
{
    return NULL ;
}

char* Personne::prenom(void)
{
    return NULL ;
}

char* Personne::mail(void)
{
    return NULL ;
}

char* Personne::codePostal()
{
    return NULL ;
}

Competence * Personne::CompetencePropres(void)
{
    return NULL ;
}

Personne * Personne::AncienCollegueNext(void)
{
    return NULL ;
}

Personne * Personne::AncienColleguePrevious(void)
{
    return NULL ;
}

Entreprise * Personne::EntrepriseActuelle(void)
{
    return NULL ;
}

// Modifieurs
void Personne::modifIndex(int Newindex)
{
    return ;
}

void Personne::modifNom(char* Newnom)
{
    return ;
}

void Personne::modifPrenom(char* Newprenom)
{
    return ;
}

void Personne::modifMail(char* Newmail)
{
    return ;
}

void Personne::modifCodePostal(char* NewCodePostal)
{
    return ;
}

void Personne::modifEntreprise(Entreprise & NewEntreprise)
{
    return ;
}
