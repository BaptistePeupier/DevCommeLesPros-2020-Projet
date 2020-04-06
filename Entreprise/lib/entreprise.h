#ifndef _V3_H_
#define _V3_H_
#include <iostream>
#include <math.h>
using namespace std ;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Classe Entreprise correspondant aux données d'une entreprise et aux différentes fonctionnalités qui lui sont  //
// liées. La classe utilise égalment deux autres classes Poste pour les postes à pourvoir et compétences pour les//
// compétences recherchées pour un poste.                                                                        //
//                                                                                                               //
// PEUPIER Baptiste                                                                                              //
// Cree le 06/04/2020, modifié le 06/04/2020                                                                     //
//                                                                                                               //
// Polytech Marseille, informatique 3A                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Competence
{
    private:
        char _label[128] ;
    public:
    // Les constructeurs
        Competence(char* label) ;
    // Le destructeur
        ~Competence(void) ;
    // Accesseurs
        char* label(void) ;
    // Modifieurs
        void modifLabel(char* NewLabel) ;
} ;

class Poste
{
    private:
        char _Titre[128] ;
        Poste * _next ;
        Poste * _previous ;
        Competence * _CompetencesRequises ;
    public:
    // Les constructeurs
        Poste(char* Titre, Poste & next, Poste & previous, Competence & CompetencesRequises) ;
    // Le destructeur
        ~Poste(void) ;
    // Accesseurs
        char* Titre(void) ;
        Poste * next(void) ;
        Poste * previous(void) ;
        Competence * CompetencesRequises(void) ;
    // Modifieurs
        void modifTitre(char* NewTitre) ;
        void modifNext(char* NewNext) ;
        void modifPrevious(char* NewPrevious) ;
    // Fonctionnalité sur les Competences
        void AddComptence (Competence & NewCompetence) ;
        void delComptence (char* label) ;
} ;

class Entreprise
{
    private :
        int _index ;
        char _nom[128] ;
        char _codePostal[128] ;
        char _mail[128] ;
        Entreprise * _next ;
        Entreprise * _previous ;
        Poste * _profilPoste ;
    public:
    // Les constructeurs
        Entreprise(int index, char* nom, char* codePostal, char* mail, Entreprise & next, Entreprise & previous) ;
    // Le destructeur
        ~Entreprise(void) ;
    // Accesseurs
        int index(void) ;
        char* nom(void) ;
        char* codePostal(void) ;
        char* mail(void) ;
        Entreprise * next(void) ;
        Entreprise * previous(void) ;
    // Modifieurs
        void modifIndex(int NewIndex) ;
        void modifNom(char* NewNom) ;
        void modifCodePostal(char* NewCodePostal) ;
        void modifMail(char * NewMail) ;
        void modifNext(Entreprise & next) ;
        void modifPrevious(Entreprise & previous) ;
    // Fonctions de liste
        int Longueur(void) ;                        // Renvoie la longueur de la liste d'entreprises
    // Fonctionnalités
        void deleteProfile(void) ;                  // Supprime le profile (l'entreprise) ainsi que les postes qui lui sont lié
        // Rechercher parmis les chercheurs par competences
        // Rechercher parmis les chercheurs par competences et code postal

} ;

#endif
