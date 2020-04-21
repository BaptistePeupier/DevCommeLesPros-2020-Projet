#ifndef _PERSONNE_H_
#define _PERSONNE_H_

#include <assert.h>
#include "entreprise.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Classe Personne contenant les données d'une personne. Elle sera utilisée dans les classes Employe et Chercheur//
// pour pouvoir faciliter la transition entre Employe et Chercheur.                                              //
//                                                                                                               //
// PEUPIER Baptiste                                                                                              //
// Cree le 06/04/2020, modifié le 21/04/2020                                                                     //
//                                                                                                               //
// Polytech Marseille, informatique 3A                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Personne
{
    private :
        int _index ;
        char _nom[128] ;
        char _prenom[128] ;
        char _mail[128] ;
        char _codePostal[128] ;
        Personne * _nextP ;
        Personne * _previousP ;
        Competence * _CompetencesPropres ;
        Personne * _AncienCollegueNext ;
        Personne * _AncienColleguePrevious ;
        Entreprise * _EntrepriseActuelle ;                                  // Si NULL est un chercheur d'emploi, sinon un employé
    public:
    // Un constructeur
        Personne(int index, char* nom, char* prenom, char* mail, char* codePostal, Personne * nextP, Personne * previousP, Competence * CompetencesPropres, Personne * AncienCollegueNext, Personne * AncienColleguePrevious, Entreprise * EntrepriseActuelle) ;
    // Le destructeur
        ~Personne(void) ;
    // Accesseurs
        int index(void) ;
        char* nom(void) ;
        char* prenom(void) ;
        char* mail(void) ;
        char* codePostal() ;
        Personne * previousP(void) ;
        Personne * nextP(void) ;
        Competence * CompetencePropres(void) ;
        Personne * AncienCollegueNext(void) ;
        Personne * AncienColleguePrevious(void) ;
        Entreprise * EntrepriseActuelle(void) ;
    // Modifieurs
        void modifIndex(int Newindex) ;
        void modifNom(char* Newnom) ;
        void modifPrenom(char* Newprenom) ;
        void modifMail(char* Newmail) ;
        void modifCodePostal(char* NewCodePostal) ;
        void modifPreviousP(Personne * NewPreviousP) ;
        void modifNextP(Personne * NewNextP) ;
        void modifEntreprise(Entreprise * NewEntreprise) ;
        void modifCompetencePropres(Competence * NewListeCompetence) ;
    // Fonctionnalités
        void TransitionStatut(void) ;                                       // Change un employé en chercheur d'emploi et inversement
                                                                            // Ajoute les anciens collègues si besoin
        void deleteProfile(void) ;
        void RecherchePosteCompetence(void) ;                               // Affiche une liste d'entreprise avec les postes correspondant aux compétences de la personne
        void RecherchePosteCompetenceCodePostal(void) ;                     // Affiche une liste d'entreprise avec les postes correspondant aux compétences et au code postal de la personne
        void RechercheColleguesEntreprise(char* nomEntreprise) ;            // Affiche une liste d'ancien collègue travaillant dans une entreprise donnée
        void MAJDBPersonne(void) ;                                          // Met à jour la base de donnée des checheurs d'emplois ou des entreprises, est appelée à chaque fois que des données sont modifiées
                                                                            // Si le pointeur vers une entrepise est null c'est un Chercheur d'emploi
                                                                            // Si le pointeur vers une entrepise est non null c'est un Employe
        void ChercheurRechercheColleguesCompetence(Competence * ListeCompetence) ;  // Affiche les données des anciens collègues employés dans les entreprises qui recherchent ces compétences
                                                                                    // Seulement pour les chercheurs d'emploi
        void EmployeRechercheColleguesCompetence(Competence * ListeCompetence) ;    // Affiche les données des anciens collègues disposant des compétences passé en liste
                                                                                    // Seulement pour les employés
        void ChercheurCompetence (Competence * listeComp) ;                 // Rechercher parmis les chercheurs par competences, affiche les résutats
        void ChercheurCompetenceCodePostal (char * CodePostalRecherche) ;   // Rechercher parmis les chercheurs par competences et code postal, affiche les résutats
} ;

#endif
