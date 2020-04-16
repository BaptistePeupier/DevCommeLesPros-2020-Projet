///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Effectue les transitions entre chercheur et employe.                                                          //
//                                                                                                               //
// PEUPIER Baptiste                                                                                              //
// Cree le 08/04/2020, modifié le 08/04/2020                                                                     //
//                                                                                                               //
// Polytech Marseille, informatique 3A                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _GENERAL_H_
#define _GENERAL_H_

#include <stdio.h>

#include "chercheur.h"
#include "employe.h"

// Construit la liste des Entreprises à partir d'une base de donnée (Entreprise + postes)
Entreprise * CreerListeEntreprise(void) ;

// Construit la liste des Employes à partir d'une base de donnée
Employe * CreerListeEmploye(void) ;

// Construit la liste des Chercheurs à partir d'une base de donnée
Chercheur * CreerListeChercheur(void) ;

// Attribue une personne récupéré d'un Employe à un objet Chercheur
Chercheur * AuxTransitionChercheur (Employe & ToTransit) ;

// Attribue une personne récupéré d'un Chercheur à un objet Employe
Employe * AuxTransitionEmploye (Chercheur & ToTransit) ;

// Rechercher parmis les chercheurs par competences, affiche les résutats
void ChercheurCompetence (Chercheur & listeChercheur, Competence * listeComp) ;

// Rechercher parmis les chercheurs par competences et code postal, affiche les résutats
void ChercheurCompetenceCodePostal (Chercheur & listeChercheur, char * CodePostalRecherche) ;

#endif

