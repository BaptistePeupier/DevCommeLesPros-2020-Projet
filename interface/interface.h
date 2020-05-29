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
#include <time.h>

#include <fstream>
#include <iostream>
#include <string>
#include <regex>

// Fonction permettant de générer le journal d'utilisation de l'application
// le nom de la fonction utilisée ainsi la valeur de ses arguments sont passées en paramètre dans des strings
void Logs(string fonction, string arguments="none") ;

//fonction de vérification de l'addresse mail entrée
bool email_valide(string email) ;

//fonction de vérification du code postal entré
bool cp_valide(string code_postal) ;

//fonction de vérification des saisies
bool saisie_valide(string saisie) ;

//fonction demandant à l'utilisateur de continuer en appuyant sur une touche
void continuer() ;

//lancement de l'interface pour éviter les mises à jour de BDD inutiles
int lancement_interface() ;

//affichage du menu principal
void menu_principal(void) ;

//connexion des employés
void connexion_employe() ;

//connexion des chercheurs d'emploi
void connexion_chercheur() ;

//connexion des entreprises
void connexion_entreprise() ;

//affichage du menu correspondant au profil d'entreprise
void menu_entreprise(Entreprise * utilisateur_entreprise) ;

//menu permettant de sélectionner le type de recherche parmis les chercheurs d'emploi
void type_recherche_entreprise() ;

//menu confirmation suppression de profil
bool menu_supp_profil(Entreprise *utilisateur_entreprise, Personne * utilisateur) ;

// Retourne une personne présente dans une liste de donnée (des employes ou des chercheur)
// L'identification se fait par l'adresse mail
Personne * saisie_personne() ;

//affichage du menu correspondant au profil de chercheur d'emploi
void menu_chercheur(Personne * utilisateur_chercheur) ;

//menu de modification de profil
void modif_profil_pers(Personne *current_user) ;

//menu de recherche de postes
void recherche_poste_pers(Personne *current_user) ;

//menu recherche parmis les anciens collègues
void recherche_collegue_pers(Personne *current_user) ;

//menu de transition de profil
bool menu_transition_pers(Personne * current_user) ;

//affichage du menu correspondant au profil d'employé
void menu_employe(Personne * utilisateur_employe) ;

#endif