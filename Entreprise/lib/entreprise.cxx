#include "entreprise.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Fonctions memrbes de la calsse Entreprise                                                                     //
//                                                                                                               //
// PEUPIER Baptiste                                                                                              //
// Cree le 06/04/2020, modifié le 06/04/2020                                                                     //
//                                                                                                               //
// Polytech Marseille, informatique 3A                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Les constructeurs
Entreprise::Entreprise(int index, char* nom, char* codePostal, char* mail, Entreprise & next, Entreprise & previous)
{
    return ;
}

// Le destructeur
Entreprise::~Entreprise(void)
{
    return ;
}

// Accesseurs
int Entreprise::index(void)
{
    return 0 ;
}

char* Entreprise::nom(void)
{
    return NULL ;
}

char* Entreprise::codePostal(void)
{
    return NULL;
}

char* Entreprise::mail(void)
{
    return NULL ;
}

Entreprise * Entreprise::next(void)
{
    return NULL ;
}

Entreprise * Entreprise::previous(void)
{
    return NULL ;
}

// Modifieurs
void Entreprise::modifIndex(int NewIndex)
{
    return ;
}

void Entreprise::modifNom(char* NewNom)
{
    return ;
}

void Entreprise::modifCodePostal(char* NewCodePostal)
{
    return ;
}

void Entreprise::modifMail(char * NewMail)
{
    return ;
}

void Entreprise::modifNext(Entreprise & next)
{
    return ;
}

void Entreprise::modifPrevious(Entreprise & previous)
{
    return ;
}

// Fonctions de liste
// Renvoie la longueur de la liste d'entreprises
int Entreprise::Longueur(void)
{
    return 0 ;
}

// Fonctionnalités
// Supprime le profile (l'entreprise) ainsi que les postes qui lui sont lié
void Entreprise::deleteProfile(void)
{
    return ;
}

// Rechercher parmis les chercheurs par competences

// Rechercher parmis les chercheurs par competences et code postal

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Fonctions memrbes de la calsse Poste                                                                         //
//                                                                                                               //
// PEUPIER Baptiste                                                                                              //
// Cree le 06/04/2020, modifié le 06/04/2020                                                                     //
//                                                                                                               //
// Polytech Marseille, informatique 3A                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Les constructeurs
Poste::Poste(char* Titre, Poste & next, Poste & previous, Competence & CompetencesRequises)
{
    return ;
}

// Le destructeur
Poste::~Poste(void)
{
    return ;
}

// Accesseurs
char* Poste::Titre(void)
{
    return NULL ;
}

Poste * Poste::next(void)
{
    return NULL ;
}

Poste * Poste::previous(void)
{
    return NULL ;
}

Competence * Poste::CompetencesRequises(void)
{
    return NULL ;
}

// Modifieurs
void Poste::modifTitre(char* NewTitre)
{
    return ;
}

void Poste::modifNext(char* NewNext)
{
    return ;
}

void Poste::modifPrevious(char* NewPrevious)
{
    return ;
}

// Fonctionnalité sur les Competences
void Poste::AddComptence (Competence & NewCompetence)
{
    return ;
}

void Poste::delComptence (char* label)
{
    return ;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Fonctions memrbes de la calsse Competence                                                                     //
//                                                                                                               //
// PEUPIER Baptiste                                                                                              //
// Cree le 06/04/2020, modifié le 06/04/2020                                                                     //
//                                                                                                               //
// Polytech Marseille, informatique 3A                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Les constructeurs
Competence::Competence(char* label)
{
    return ;
}

// Le destructeur
Competence::~Competence(void)
{
    return ;
}

// Accesseurs
char* Competence::label(void)
{
    return NULL ;
}

// Modifieurs
void Competence::modifLabel(char* NewLabel)
{
    return ;
}

