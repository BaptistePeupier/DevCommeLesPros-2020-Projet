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
// Cree le 06/04/2020, modifié le 16/05/2020                                                                     //
//                                                                                                               //
// Polytech Marseille, informatique 3A                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Personne
{
    private :
        int _index ;
        string _nom ;
        string _prenom ;
        string _mail ;
        string _codePostal ;
        Personne * _nextP ;
        Personne * _previousP ;
        Entreprise * _EntrepriseActuelle ;                                              // Si NULL est un chercheur d'emploi, sinon un employé
        Competence * _CompetencesPropres ;
        AncienCollegue * _ListAncienCollegues ;                                         // Pointeur vers la liste d'ancien collègue
        static string _DBE, _DBC ;                                                      // Chaine de caractère statique à la classe dénottant les DB à utiliser
                                                                                        // Modifier ces variables pour passer des DB du programme de test à celle de l'application
    public:
    // Un constructeur
        Personne(int index, const string nom, const string prenom, const string mail, const string codePostal, Personne * nextP=NULL, Personne * previousP=NULL, Competence * CompetencesPropres=NULL, AncienCollegue * ListAncienCollegues=NULL, Entreprise * EntrepriseActuelle=NULL)
        {_index = index ; _nom = nom ; _prenom = prenom ; _mail = mail ; _codePostal = codePostal ; _CompetencesPropres = CompetencesPropres ; _nextP = nextP ; _previousP = previousP ; _ListAncienCollegues = ListAncienCollegues ; _EntrepriseActuelle = EntrepriseActuelle ; return ;} ;
    // Le destructeur
        virtual ~Personne(void) ;
    // Accesseurs
        int index(void){return _index ;} ;
        string nom(void){return _nom ;} ;
        string prenom(void){return _prenom ;} ;
        string mail(void){return _mail ;} ;
        string codePostal(){return _codePostal ;} ;
        Personne * previousP(void){return _previousP ;} ;
        Personne * nextP(void){return _nextP ;} ;
        Competence * CompetencePropres(void){return _CompetencesPropres ;} ;
        AncienCollegue * ListAncienCollegues(void){return _ListAncienCollegues ;} ;
        Entreprise * EntrepriseActuelle(void){return _EntrepriseActuelle ;} ;
    // Modifieurs
        void modifIndex(int Newindex){_index = Newindex ; if(_EntrepriseActuelle){MAJDBPersonne(true);} else{MAJDBPersonne(false);}   return ;} ;
        void modifNom(const string Newnom){_nom = Newnom ; if(_EntrepriseActuelle){MAJDBPersonne(true);} else{MAJDBPersonne(false);} return ;} ;
        void modifPrenom(const string Newprenom){_prenom = Newprenom ; if(_EntrepriseActuelle){MAJDBPersonne(true);} else{MAJDBPersonne(false);} return ;} ;
        void modifMail(const string Newmail){_mail = Newmail ; if(_EntrepriseActuelle){MAJDBPersonne(true);} else{MAJDBPersonne(false);} return ;} ;
        void modifCodePostal(const string NewCodePostal){_codePostal = NewCodePostal ; if(_EntrepriseActuelle){MAJDBPersonne(true);} else{MAJDBPersonne(false);} return ;} ;
        void modifPreviousP(Personne * NewPreviousP){_previousP = NewPreviousP ; return ;} ;
        void modifNextP(Personne * NewNextP){_nextP = NewNextP ; return ;} ;
        void modifEntreprise(Entreprise * NewEntreprise){_EntrepriseActuelle = NewEntreprise ; if(_EntrepriseActuelle){MAJDBPersonne(true);} else{MAJDBPersonne(false);} return ;} ;
        void modifCompetencePropres(Competence * NewListeCompetence){_CompetencesPropres = NewListeCompetence ; return ;} ;
        void modifAncienCollegues(AncienCollegue * NewListCollegues){_ListAncienCollegues = NewListCollegues ; return ;} ;
        static void modifDBE(string NewDBE){_DBE = NewDBE ; return ;} ;
        static void modifDBC(string NewDBC){_DBC = NewDBC ; return ;} ;
        // Fonctionnalités
        void TransitionStatut(Personne ** ListeEmploye, Personne ** ListeChercheurEmploi, Entreprise * NewEntreprise=NULL) ;// Change un employé en chercheur d'emploi et inversement
                                                                                                                            // Ajoute les anciens collègues si besoin
                                                                                                                            // NewEntreprise est le pointeur vers l'entreprise en cas de recrutement, NULL sinon
        void deleteProfile(Personne ** ListeEmploye, Personne ** ListeChercheurEmploi) ;
        void MAJDBPersonne(bool employe,string DBE=_DBE, string DBC=_DBC) ;              // Met à jour la base de donnée des checheurs d'emplois ou des entreprises, est appelée à chaque fois que des données sont modifiées
                                                                            // Si le pointeur vers une entrepise est null c'est un Chercheur d'emploi
                                                                            // Si le pointeur vers une entrepise est non null c'est un Employe
        Entreprise* RecherchePosteCompetence(Entreprise * listeEntreprises) ;           // Retourne une liste d'entreprise avec les postes correspondant aux compétences de la personne
        Entreprise* RecherchePosteCompetenceCodePostal(Entreprise * listeEntreprises) ; // Retourne une liste d'entreprise avec les postes correspondant aux compétences et au code postal de la personne
        Personne* ChercheurCompetence (Competence * listeComp) ;                                                // Rechercher parmis les chercheurs par competences, affiche les résutats
        Personne* ChercheurCompetenceCodePostal (Competence * listeComp ,const string CodePostalRecherche) ;    // Rechercher parmis les chercheurs par competences et code postal, affiche les résutats
        AncienCollegue* RechercheColleguesEntreprise(const string nomEntreprise) ;      // Retourne une liste d'ancien collègue travaillant dans une entreprise donnée
        AncienCollegue* ChercheurRechercheColleguesCompetence(Competence * ListeCompetence) ;   // Retourne une liste des anciens collègues employés dans les entreprises qui recherchent ces compétences
                                                                                                // Seulement pour les chercheurs d'emploi
        AncienCollegue* EmployeRechercheColleguesCompetence(Competence * ListeCompetence) ;     // Retourne une liste des anciens collègues disposant des compétences passé en liste
                                                                                                // Seulement pour les employés
} ;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Classe AncienCollegue étant une liste de personnes.                                                           //
//                                                                                                               //
// PEUPIER Baptiste                                                                                              //
// Cree le 06/04/2020, modifié le 16/05/2020                                                                     //
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
        AncienCollegue(Personne * currentA, AncienCollegue * nextA=NULL, AncienCollegue * previousA=NULL)
        {_currentA = currentA ; _nextA = nextA ; _previousA = previousA ; return ;} ;
    // Le destructeur
        virtual ~AncienCollegue(void) ;
    // Accesseurs
        Personne * currentA(void){return _currentA ;} ;
        AncienCollegue * nextA(void){return _nextA ;} ;
        AncienCollegue * previousA(void){return _previousA ;} ;
    // Modifieurs
        void modifCurrentA(Personne * NewCurrent){_currentA = NewCurrent ; return ;} ;
        void modifNextA(AncienCollegue * NewNextA){_nextA = NewNextA ; return ;} ;
        void modifPreviousA(AncienCollegue * NewPreviousA){_previousA = NewPreviousA ; return ;} ;
    // Fonctionnalités
        void addAncienCollegue(Personne * NewAncienCollegue,Personne * base_pers) ;      // Ajoute une personne à la liste
        void dellAncienCollegue(Personne * AncienCollegueToDell,Personne * base_pers) ;  // Retire une personne de la liste
} ;

#endif
