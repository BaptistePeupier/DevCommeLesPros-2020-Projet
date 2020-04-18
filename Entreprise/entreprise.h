///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Classe Entreprise correspondant aux données d'une entreprise et aux différentes fonctionnalités qui lui sont  //
// liées. La classe utilise égalment deux autres classes Poste pour les postes à pourvoir et compétences pour les//
// compétences recherchées pour un poste.                                                                        //
//                                                                                                               //
// PEUPIER Baptiste MASSELOT Nicolas                                                                             //
// Cree le 06/04/2020, modifié le 18/04/2020                                                                     //
//                                                                                                               //
// Polytech Marseille, informatique 3A                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _ENTREPRISE_H_
#define _ENTREPRISE_H_

#include <iostream>
using namespace std ;

class Competence
{
    private:
        char _label[128] ;
        Competence * _next ;
        Competence * _previous ;
    public:
    // Les constructeurs
        Competence(const char* label, Competence * next, Competence * previous) ;
    // Le destructeur
        ~Competence(void) ;
    // Accesseurs
        char* label(void) ;
        Competence * next(void) ;
        Competence * previous(void) ;
    // Modifieurs
        void modifLabel(const char* NewLabel) ;
        void modifNext(Competence* NewNext) ;
        void modifPrevious(Competence* NewPrevious) ;
    // Fonctionnalité sur les Competences
        void AddCompetence (const char* label) ;
        void delCompetence (const char* label) ;
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
        Poste(const char* Titre, Poste *next, Poste * previous, Competence * CompetencesRequises) ;
    // Le destructeur
        ~Poste(void) ;
    // Accesseurs
        char* Titre(void) ;
        Poste * next(void) ;
        Poste * previous(void) ;
        Competence * CompetencesRequises(void) ;
    // Modifieurs
        void modifTitre(const char* NewTitre) ;
        void modifNext(Poste* NewNext) ;
        void modifPrevious(Poste* NewPrevious) ;
        void modifCompetencesRequises(Competence * NewListeCompetence) ;        // Modifie le pointeur vers la liste de compétence
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
        Entreprise(int index, const char* nom, const char* codePostal, const char* mail, Entreprise * next, Entreprise * previous) ;
    // Le destructeur
        ~Entreprise(void) ;
    // Accesseurs
        int index(void) ;
        char* nom(void) ;
        char* codePostal(void) ;
        char* mail(void) ;
        Entreprise * next(void) ;
        Entreprise * previous(void) ;
        Poste * profilPoste(void) ;    
    // Modifieurs
        void modifIndex(int NewIndex) ;
        void modifNom(const char* NewNom) ;
        void modifCodePostal(const char* NewCodePostal) ;
        void modifMail(const char * NewMail) ;
        void modifNext(Entreprise * next) ;
        void modifPrevious(Entreprise * previous) ;
        void modifProfilPoste(Poste * NewListePoste) ;                                      // Modifie le pointeur vers la liste de postes à fournir
    // Fonctionnalités
        void addEntreprise(const char* nom, const char* codePostal, const char* mail) ;     // Ajoute une entreprise à la liste
        void addPoste(Poste * ToAdd) ;                                                      // Ajoute un poste à la liste des postes à fournir
        void deleteProfile(void) ;                                                          // Supprime le profile (l'entreprise) ainsi que les postes qui lui sont lié
        void MAJDBEntreprise(Entreprise * MAJ) ;                                            // Met à jour la base de donnée des entreprises, est appelée à chaque fois que des données sont modifiées
} ;

#endif

