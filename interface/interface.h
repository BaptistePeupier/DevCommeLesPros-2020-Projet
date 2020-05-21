#ifndef _INTERFACE_H_
#define _INTERFACE_H_

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Interface de l'application                                                                                    //
//                                                                                                               //
// PEUPIER Baptiste MASSELOT Nicolas                                                                             //
// Cree le 18/05/2020, modifié le 18/05/2020                                                                     //
//                                                                                                               //
// Polytech Marseille, informatique 3A                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "general.h"
#include <string.h>
// #include <stddef.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <string>
#include <regex>

//fonction de vérification de l'addresse mail entrée
bool email_valide(string email) ;

//fonction de vérification du code postal entré
bool cp_valide(string code_postal) ;

//fonction de vérification des saisies
bool saisie_valide(string saisie) ;

//affichage du menu principal
int menu_principal(void) ;

//connexion des employés
void connexion_employe() ;

//connexion des chercheurs d'emploi
void connexion_chercheur() ;

//connexion des entreprises
void connexion_entreprise() ;

//affichage du menu correspondant au profil d'entreprise
void menu_entreprise(Entreprise * utilisateur_entreprise) ;

//affichage du menu correspondant au profil de chercheur d'emploi
void menu_chercheur(Personne * utilisateur_chercheur) ;

//affichage du menu correspondant au profil d'employé
void menu_employe(Personne * utilisateur_employe) ;

#endif