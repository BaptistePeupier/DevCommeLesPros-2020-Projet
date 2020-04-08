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

#include "chercheur.h"
#include "employe.h"

// Attribue une personne récupéré d'un Employe à un objet Chercheur
Chercheur * AuxTransitionChercheur (Employe & ToTransit) ;

// Attribue une personne récupéré d'un Chercheur à un objet Employe
Employe * AuxTransitionEmploye (Chercheur & ToTransit) ;

#endif

