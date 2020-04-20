///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Effectue les transitions entre chercheur et employe.                                                          //
//                                                                                                               //
// PEUPIER Baptiste MASSELOT Nicolas                                                                             //
// Cree le 08/04/2020, modifié le 08/04/2020                                                                     //
//                                                                                                               //
// Polytech Marseille, informatique 3A                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _GENERAL_H_
#define _GENERAL_H_

#include <stdio.h>

#include "personne.h"

// Construit la liste des Entreprises à partir d'une base de donnée (entreprise + postes)
Entreprise * CreerListeEntreprise(void) ;

// Construit la liste des Personnes à partir d'une base de donnée (employe + chercheurd'emplois)
Personne * CreerListePersonne(void) ;

#endif
