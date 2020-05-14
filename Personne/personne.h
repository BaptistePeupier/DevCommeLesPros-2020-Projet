#ifndef _PERSONNE_H_
#define _PERSONNE_H_

#include <assert.h>
#include "entreprise.h"

class AncienCollegue ;
class Personne ;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Classe Personne contenant les données d'une personne.                                                         //
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
        Entreprise * _EntrepriseActuelle ;                                              // Si NULL est un chercheur d'emploi, sinon un employé
        Competence * _CompetencesPropres ;
        AncienCollegue * _ListAncienCollegues ;                                         // Pointeur vers la liste d'ancien collègue
    public:
    // Un constructeur
        Personne(int index, const char* nom, const char* prenom, const char* mail, const char* codePostal, Personne * nextP, Personne * previousP, Competence * CompetencesPropres, AncienCollegue * ListAncienCollegues, Entreprise * EntrepriseActuelle) ;
    // Le destructeur
        virtual ~Personne(void) ;
    // Accesseurs
        int index(void) ;
        char* nom(void) ;
        char* prenom(void) ;
        char* mail(void) ;
        char* codePostal() ;
        Personne * previousP(void) ;
        Personne * nextP(void) ;
        Competence * CompetencePropres(void) ;
        AncienCollegue * ListAncienCollegues(void) ;
        Entreprise * EntrepriseActuelle(void) ;
    // Modifieurs
        void modifIndex(int Newindex) ;
        void modifNom(const char* Newnom) ;
        void modifPrenom(const char* Newprenom) ;
        void modifMail(const char* Newmail) ;
        void modifCodePostal(const char* NewCodePostal) ;
        void modifPreviousP(Personne * NewPreviousP) ;
        void modifNextP(Personne * NewNextP) ;
        void modifEntreprise(Entreprise * NewEntreprise) ;
        void modifCompetencePropres(Competence * NewListeCompetence) ;
        void modifAncienCollegues(AncienCollegue * NewListCollegues) ;
    // Fonctionnalités
        void TransitionStatut(Personne ** ListeEmploye, Personne ** ListeChercheurEmploi, Entreprise * NewEntreprise=NULL) ;// Change un employé en chercheur d'emploi et inversement
                                                                                                                            // Ajoute les anciens collègues si besoin
                                                                                                                            // NewEntreprise est le pointeur vers l'entreprise en cas de recrutement, NULL sinon
        void deleteProfile(Personne ** ListeEmploye, Personne ** ListeChercheurEmploi) ;
        void RecherchePosteCompetence(Entreprise * listeEntreprises) ;                               // Affiche une liste d'entreprise avec les postes correspondant aux compétences de la personne
        void RecherchePosteCompetenceCodePostal(Entreprise * listeEntreprises) ;                     // Affiche une liste d'entreprise avec les postes correspondant aux compétences et au code postal de la personne
        void RechercheColleguesEntreprise(const char* nomEntreprise) ;            // Affiche une liste d'ancien collègue travaillant dans une entreprise donnée
        void MAJDBPersonne(void) ;                                          // Met à jour la base de donnée des checheurs d'emplois ou des entreprises, est appelée à chaque fois que des données sont modifiées
                                                                            // Si le pointeur vers une entrepise est null c'est un Chercheur d'emploi
                                                                            // Si le pointeur vers une entrepise est non null c'est un Employe
        void ChercheurRechercheColleguesCompetence(Competence * ListeCompetence) ;  // Affiche les données des anciens collègues employés dans les entreprises qui recherchent ces compétences
                                                                                    // Seulement pour les chercheurs d'emploi
        void EmployeRechercheColleguesCompetence(Competence * ListeCompetence) ;    // Affiche les données des anciens collègues disposant des compétences passé en liste
                                                                                    // Seulement pour les employés
        void ChercheurCompetence (Competence * listeComp) ;                 // Rechercher parmis les chercheurs par competences, affiche les résutats
        void ChercheurCompetenceCodePostal (Competence * listeComp ,const char * CodePostalRecherche) ;   // Rechercher parmis les chercheurs par competences et code postal, affiche les résutats
} ;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Classe AncienCollegue étant une liste de personnes.                                                           //
//                                                                                                               //
// PEUPIER Baptiste                                                                                              //
// Cree le 06/04/2020, modifié le 21/04/2020                                                                     //
//                                                                                                               //
// Polytech Marseille, informatique 3A                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AncienCollegue
{
    private:
        Personne * _currentA ;
        AncienCollegue * _nextA ;
        AncienCollegue * _previousA ;
    public:
    // Un constructeur
        AncienCollegue(Personne * currentA, AncienCollegue * nextA, AncienCollegue * previousA) ;
    // Le destructeur
        virtual ~AncienCollegue(void) ;
    // Accesseurs
        Personne * currentA(void) ;
        AncienCollegue * nextA(void) ;
        AncienCollegue * previousA(void) ;
    // Modifieurs
        void modifCurrentA(Personne * NewCurrent) ;
        void modifNextA(AncienCollegue * NewNextA) ;
        void modifPreviousA(AncienCollegue * NewPreviousA) ;
    // Fonctionnalités
        void addAncienCollegue(Personne * NewAncienCollegue,Personne * base_pers) ;      // Ajoute une personne à la liste
        void dellAncienCollegue(Personne * AncienCollegueToDell,Personne * base_pers) ;  // Retire une personne de la liste
} ;

#endif

