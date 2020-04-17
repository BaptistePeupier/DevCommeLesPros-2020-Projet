#ifndef _PERSONNE_H_
#define _PERSONNE_H_

#include "entreprise.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Classe Personne contenant les données d'une personne. Elle sera utilisée dans les classes Employe et Chercheur//
// pour pouvoir faciliter la transition entre Employe et Chercheur.                                              //
//                                                                                                               //
// PEUPIER Baptiste                                                                                              //
// Cree le 06/04/2020, modifié le 07/04/2020                                                                     //
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
        Competence * _CompetencesPropres ;
        Personne * _AncienCollegueNext ;
        Personne * _AncienColleguePrevious ;
        Entreprise * _EntrepriseActuelle ;
    public:
    // Un constructeur
        Personne(int index, char* nom, char* prenom, char* mail, char* codePostal, Competence * CompetencesPropres, Personne * AncienCollegueNext, Personne * AncienColleguePrevious, Entreprise * EntrepriseActuelle) ;
    // Le destructeur
        ~Personne(void) ;
    // Accesseurs
        int index(void) ;
        char* nom(void) ;
        char* prenom(void) ;
        char* mail(void) ;
        char* codePostal() ;
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
        void modifEntreprise(Entreprise * NewEntreprise) ;
    // Fonctionnalités
        void RecherchePosteCompetence(void) ;                       // Affiche une liste d'entreprise avec les postes correspondant aux compétences de la personne
        void RecherchePosteCompetenceCodePostal(void) ;             // Affiche une liste d'entreprise avec les postes correspondant aux compétences et au code postal de la personne
        void RechercheColleguesEntreprise(char* nomEntreprise) ;    // Affiche une liste d'ancien collègue travaillant dans une entreprise donnée
        void MAJDBPersonne(Personne * MAJ) ;                        // Met à jour la base de donnée des checheurs d'emplois ou des entreprises, est appelée à chaque fois que des données sont modifiées
                                                                    // Si le pointeur vers une entrepise est null c'est un Chercheur d'emploi
                                                                    // Si le pointeur vers une entrepise est non null c'est un Employe
} ;

#endif
