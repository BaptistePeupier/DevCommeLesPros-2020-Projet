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

// Fonctionnalités
// Renvoie une liste d'entreprise avec les postes correspondant aux compétences de la personne
void Personne::RecherchePosteCompetence(void)
{
    return ;
}

// Renvoie une liste d'entreprise avec les postes correspondant aux compétences et au code postal de la personne
void Personne::RecherchePosteCompetenceCodePostal(void)
{
    return ;
}

// Renvoie une liste d'ancien collègue travaillant dans une entreprise donnée
void Personne::RechercheColleguesEntreprise(char* nomEntreprise)
{
    return ;
}
// Met à jour la base de donnée des checheurs d'emplois ou des entreprises, est appelée à chaque fois que des données sont modifiées
// Si le pointeur vers une entrepise est null c'est un Chercheur d'emploi
// Si le pointeur vers une entrepise est non null c'est un Employe
void Personne::MAJDBPersonne(Personne * MAJ)
{
    return ;
}
