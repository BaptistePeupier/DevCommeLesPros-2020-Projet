#ifndef _ENTREPRISE_H_
#define _ENTREPRISE_H_

#include <iostream>
using namespace std ;

// Prototypes

class Competence ;
class Poste ;
class Entreprise ;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Classe Entreprise correspondant aux données d'une entreprise et aux différentes fonctionnalités qui lui sont  //
// liées. La classe utilise égalment deux autres classes Poste pour les postes à pourvoir et compétences pour les//
// compétences recherchées pour un poste.                                                                        //
//                                                                                                               //
// PEUPIER Baptiste MASSELOT Nicolas                                                                             //
// Cree le 06/04/2020, modifié le 12/05/2020                                                                     //
//                                                                                                               //
// Polytech Marseille, informatique 3A                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
        virtual ~Entreprise(void) ;
    // Accesseurs
        int index(void){return _index ;} ;
        char* nom(void){return _nom ;} ;
        char* codePostal(void){return _codePostal ;} ;
        char* mail(void){return _mail ;} ;
        Entreprise * next(void){return _next ;} ;
        Entreprise * previous(void){return _previous ;} ;
        Poste * profilPoste(void){return _profilPoste ;} ;
    // Modifieurs
        void modifIndex(int NewIndex){_index = NewIndex ; return ;} ;
        void modifNom(const char* NewNom) ;
        void modifCodePostal(const char* NewCodePostal) ;
        void modifMail(const char * NewMail) ;
        void modifNext(Entreprise * next){_next = next ; return ;} ;
        void modifPrevious(Entreprise * previous){_previous = previous ; return ;} ;
        void modifProfilPoste(Poste * NewListePoste){_profilPoste = NewListePoste ; return ;} ; // Modifie le pointeur vers la liste de postes à fournir
    // Fonctionnalités
        void addEntreprise(const char* nom, const char* codePostal, const char* mail) ;         // Ajoute une entreprise à la liste
        void addPoste(Poste * ToAdd) ;                                                          // Ajoute un poste à la liste des postes à fournir
        void MAJDBEntreprise(void) ;                                                            // Met à jour la base de donnée des entreprises, est appelée à chaque fois que des données sont modifiées ou ajoutées
                                                                                                // Met également à jour la base de données des postes
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
        virtual ~Poste(void) ;
    // Accesseurs
        char* Titre(void){return _Titre ;} ;
        Poste * next(void){return _next ;} ;
        Poste * previous(void){return _previous ;} ;
        Competence * CompetencesRequises(void){return _CompetencesRequises ;} ;
    // Modifieurs
        void modifTitre(const char* NewTitre) ;
        void modifNext(Poste* NewNext){_next = NewNext ; return ;} ;
        void modifPrevious(Poste* NewPrevious){_previous = NewPrevious ; return ;} ;
        void modifCompetencesRequises(Competence * NewListeCompetence) ;        // Modifie le pointeur vers la liste de compétence
} ;

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
        virtual ~Competence(void) ;
    // Accesseurs
        char* label(void){return _label ;} ;
        Competence * next(void){return _next ;} ;
        Competence * previous(void){return _next ;} ;
    // Modifieurs
        void modifLabel(const char* NewLabel) ;
        void modifNext(Competence* NewNext){_next = NewNext ; return ;} ;
        void modifPrevious(Competence* NewPrevious){_previous = NewPrevious ; return ;} ;
    // Fonctionnalité sur les Competences
        void AddCompetence (const char* label) ;
        void delCompetence (const char* label) ;
} ;

#endif

