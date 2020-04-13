///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Fonctions générales d'utilisation du programme :                                                              //
//              - transitions entre Employe et Chercheur                                                         //
//              - interface graphique                                                                            //
//                                                                                                               //
// PEUPIER Baptiste                                                                                              //
// Cree le 08/04/2020, modifié le 08/04/2020                                                                     //
//                                                                                                               //
// Polytech Marseille, informatique 3A                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "general.h"

// Construit la liste des Entreprises à partir d'une base de donnée (Entreprise + postes)
Entreprise * CreerListeEntreprise(void)
{
    return NULL ;
}

// Construit la liste des Employes à partir d'une base de donnée
Employe * CreerListeEmploye(void)
{
    return NULL ;
}

// Construit la liste des Chercheurs à partir d'une base de donnée
Chercheur * CreerListeChercheur(void)
{
    return NULL ;
}

// Attribue une personne récupéré d'un Employe à un objet Chercheur
Chercheur * AuxTransitionChercheur (Employe & ToTransit)
{
    return NULL ;
}

// Attribue une personne récupéré d'un Chercheur à un objet Employe
Employe * AuxTransitionEmploye (Chercheur & ToTransit)
{
    return NULL ;
}

// Rechercher parmis les chercheurs par competences, affiche les résutats
void ChercheurCompetence (Chercheur & listeChercheur, Competence * listeComp)
{
    return ;
}

// Rechercher parmis les chercheurs par competences et code postal, affiche les résutats
void ChercheurCompetenceCodePostal (Chercheur & listeChercheur, char * CodePostalRecherche)
{
    return ;
}

