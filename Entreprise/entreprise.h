#ifndef _ENTREPRISE_H_
#define _ENTREPRISE_H_

#include <iostream>
#include <string>
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
        string _nom ;
        string _codePostal ;
        string _mail ;
        Entreprise * _next ;
        Entreprise * _previous ;
        Poste * _profilPoste ;
        static string _DBE, _DBP ;          // Chaine de caractère statique à la classe dénottant les DB à utiliser
                                            // Modifier ces variables pour passer des DB du programme de test à celle de l'application
    public:
    // Les constructeurs
        Entreprise(int index, const string nom, const string codePostal, const string mail, Entreprise * next=NULL, Entreprise * previous=NULL, Poste *profilPoste=NULL)
        {_index = index ; _nom = nom ; _codePostal = codePostal ; _mail = mail ; _next = next ; _previous = previous, _profilPoste = profilPoste ; return ;} ;
    // Le destructeur
        virtual ~Entreprise(void) ;
    // Accesseurs
        int index(void){return _index ;} ;
        string nom(void){return _nom ;} ;
        string codePostal(void){return _codePostal ;} ;
        string mail(void){return _mail ;} ;
        Entreprise * next(void){return _next ;} ;
        Entreprise * previous(void){return _previous ;} ;
        Poste * profilPoste(void){return _profilPoste ;} ;
    // Modifieurs
        void modifIndex(int NewIndex){_index = NewIndex ; return ;} ;
        void modifNom(const string NewNom){_nom = NewNom ; MAJDBEntreprise() ; return ;};
        void modifCodePostal(const string NewCodePostal){_codePostal = NewCodePostal ; MAJDBEntreprise() ; return ;} ;
        void modifMail(const string NewMail){_mail = NewMail ; MAJDBEntreprise() ; return ;} ;
        void modifNext(Entreprise * next){_next = next ; return ;} ;
        void modifPrevious(Entreprise * previous){_previous = previous ; return ;} ;
        void modifProfilPoste(Poste * NewListePoste){_profilPoste = NewListePoste ; return ;} ; // Modifie le pointeur vers la liste de postes à fournir
    // Fonctionnalités
        void addEntreprise(const string nom, const string codePostal, const string mail) ;      // Ajoute une entreprise à la liste
        void addPoste(Poste * ToAdd) ;                                                          // Ajoute un poste à la liste des postes à fournir
        void dellPoste(const string TitrePoste) ;                                               // Supprime un poste à la liste des postes à fournir
        void MAJDBEntreprise(string DBE=_DBE, string DBP=_DBP) ;                                // Met à jour la base de donnée des entreprises, est appelée à chaque fois que des données sont modifiées ou ajoutées
                                                                                                // Met également à jour la base de données des postes
} ;

class Poste
{
    private:
        string _Titre ;
        Poste * _next ;
        Poste * _previous ;
        Competence * _CompetencesRequises ;
    public:
    // Les constructeurs
        Poste(const string Titre, Poste *next=NULL, Poste * previous=NULL, Competence * CompetencesRequises=NULL)
        {_Titre = Titre ; _next = next ; _previous = previous ; _CompetencesRequises = CompetencesRequises ; return ;} ;
    // Le destructeur
        virtual ~Poste(void) ;
    // Accesseurs
        string Titre(void){return _Titre ;} ;
        Poste * next(void){return _next ;} ;
        Poste * previous(void){return _previous ;} ;
        Competence * CompetencesRequises(void){return _CompetencesRequises ;} ;
    // Modifieurs
        void modifTitre(const string NewTitre){_Titre = NewTitre ; return ;} ;
        void modifNext(Poste* NewNext){_next = NewNext ; return ;} ;
        void modifPrevious(Poste* NewPrevious){_previous = NewPrevious ; return ;} ;
        void modifCompetencesRequises(Competence * NewListeCompetence){_CompetencesRequises = NewListeCompetence ; return ;} ;        // Modifie le pointeur vers la liste de compétence
} ;

class Competence
{
    private:
        string _label ;
        Competence * _next ;
        Competence * _previous ;
    public:
    // Les constructeurs
        Competence(const string label, Competence * next=NULL, Competence * previous=NULL)
        {_label = label ; _next = next ; _previous = previous ; return ;} ;
    // Le destructeur
        virtual ~Competence(void) ;
    // Accesseurs
        string label(void){return _label ;} ;
        Competence * next(void){return _next ;} ;
        Competence * previous(void){return _next ;} ;
    // Modifieurs
        void modifLabel(const string NewLabel){_label = NewLabel ; return ;} ;
        void modifNext(Competence* NewNext){_next = NewNext ; return ;} ;
        void modifPrevious(Competence* NewPrevious){_previous = NewPrevious ; return ;} ;
    // Fonctionnalité sur les Competences
        void AddCompetence (const string label) ;
        void delCompetence (const string label) ;
        bool IsInList (Competence * listeComp) ;                // Revoie 1 si la compétence est présente dans une liste de compétence passée en argument, 0 sinon
} ;

#endif

