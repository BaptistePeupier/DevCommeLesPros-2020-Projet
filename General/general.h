///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Fonctions générales entre les classes Entreprise et Personne.                                                 //
//                                                                                                               //
// PEUPIER Baptiste MASSELOT Nicolas                                                                             //
// Cree le 08/04/2020, modifié le 21/04/2020                                                                     //
//                                                                                                               //
// Polytech Marseille, informatique 3A                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _GENERAL_H_
#define _GENERAL_H_

#include <stdio.h>
#include "personne.h"

// Construit la liste des Entreprises à partir d'une base de donnée (entreprise + postes)
Entreprise * CreerListeEntreprise(void) ;

// Construit la liste des Employe à partir d'une base de donnée (employe)
Personne * CreerListeEmploye(Entreprise * ListeEntreprise) ;

// Construit la liste des Chercheurs d'emploi à partir d'une base de donnée (chercheurd'emplois)
Personne * CreerListeChercheurEmploi(void) ;

// Effectue la lisaison entre la liste des Employes et chercheur d'emploi
void InitAnciensCollegues(Personne * ListeEmploye, Personne * ListeChercheurEmploi) ;

// Fonction auxiliaire aux fonctions CreerListeEntreprise, CreerListeEmploye, CreerListeChercheurEmploi, InitAnciensCollegues
// Créer les listes et fait les liens avec les entreprises et ancien collègues
void Creer_listes(Entreprise ** ListeEntreprise, Personne ** ListeEmploye, Personne ** ListeChercheurEmploi) ;

// Supprime le profile (l'entreprise) ainsi que les postes qui lui sont lié
// Fait également transitionner les employes de cette entreprise en chercheur d'emploi
void deleteProfileEntreprise(Entreprise *ToDellE, Entreprise **ListeEntreprise, Personne **ListeEmploye, Personne **ListeChercheurEmploi) ;

#endif
