#include "employe.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Fonctions memrbes de la calsse Employe                                                                        //
//                                                                                                               //
// PEUPIER Baptiste                                                                                              //
// Cree le 06/04/2020, modifié le 07/04/2020                                                                     //
//                                                                                                               //
// Polytech Marseille, informatique 3A                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Les constructeurs
Employe::Employe(Personne & EstEmploye)
{
    return ;
}

// Le destructeur
Employe::~Employe(void)
{
    return ;
}

// Accesseur
Personne * Employe::EstEmploye(void)
{
    return NULL ;
}

// Modifieur
void Employe::modifEstEmploye(Personne & NewEstEmploye)
{
    return ;
}

// Fonctionnalités
void Employe::addAncienCollegue(Personne & NewAncienCollegue)
{
    return ;
}

// Renvoie un pointeur sur une personne en supprimant l'objet, ajoute les collègues de l'entrerprise à la liste d'anciens collègue, une autre fonction attribuera ce pointeur à un objet Chercheur
Personne * Employe::TransitionChercheur(void)
{
    return NULL ;
}

// Transitionner le profil vers Chercheur

void Employe::deleteProfile(void)
{
    return ;
}

void Employe::addCompetence(Competence & NewCompetence)
{
    return ;
}

// Affiche les données des anciens collègues disposant des compétences passé en liste
void Employe::RechercheColleguesCompetence(Competence * ListeCompetence)
{
    return ;
}


