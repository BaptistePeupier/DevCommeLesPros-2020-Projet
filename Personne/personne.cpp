#include "personne.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Fonctions memrbes de la classe Personne                                                                       //
//                                                                                                               //
// PEUPIER Baptiste                                                                                              //
// Cree le 06/04/2020, modifié le 17/04/2020                                                                     //
//                                                                                                               //
// Polytech Marseille, informatique 3A                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Un constructeur
Personne::Personne(int index, char* nom, char* prenom, char* mail, char* codePostal, Personne * nextP, Personne * previousP, Competence * CompetencesPropres, Personne * AncienCollegueNext, Personne * AncienColleguePrevious, Entreprise * EntrepriseActuelle)

{
    int i ;
    _index = index ;
    

    i = -1 ;
    do{                             // Si nom vide
        i++ ;                       // Pour mettre le '\0'
        _nom[i] = nom[i] ;
    }while (nom[i] != '\0') ;

    i = -1 ;
    do{                             // Si prenom vide
        i++ ;                       // Pour mettre le '\0'
        _prenom[i] = prenom[i] ;
    }while (prenom[i] != '\0') ;

    i = -1 ;
    do{                             // Si mail vide
        i++ ;                       // Pour mettre le '\0'
        _mail[i] = mail[i] ;
    }while (mail[i] != '\0') ;

    i = -1 ;
    do{                             // Si codePostal vide
        i++ ;                       // Pour mettre le '\0'
        _codePostal[i] = codePostal[i] ;
    }while (codePostal[i] != '\0') ;

    _CompetencesPropres = CompetencesPropres ;
    _nextP = nextP ;
    _previousP = previousP ;
    _AncienCollegueNext = AncienCollegueNext ;
    _AncienColleguePrevious = AncienColleguePrevious ;
    _EntrepriseActuelle = EntrepriseActuelle ;

    return ;
}

// Le destructeur
Personne::~Personne(void)
{
    cout << "Destructeur Personne" << endl ; 
    return ;
}

// Accesseurs
int Personne::index(void)
{
    return _index ;
}

char* Personne::nom(void)
{
    return _nom ;
}

char* Personne::prenom(void)
{
    return _prenom ;
}

char* Personne::mail(void)
{
    return _mail ;
}

char* Personne::codePostal()
{
    return _codePostal ;
}

Competence * Personne::CompetencePropres(void)
{
    return _CompetencesPropres ;
}

Personne * Personne::AncienCollegueNext(void)
{
    return _AncienCollegueNext ;
}

Personne * Personne::AncienColleguePrevious(void)
{
    return _AncienColleguePrevious ;
}

Entreprise * Personne::EntrepriseActuelle(void)
{
    return _EntrepriseActuelle ;
}

// Modifieurs
void Personne::modifIndex(int Newindex)
{
    _index = Newindex ;
    return ;
}

void Personne::modifNom(char* Newnom)
{
    int i ;

    i = -1 ;
    do{                             // Si nom vide
        i++ ;                       // Pour mettre le '\0'
        _nom[i] = Newnom[i] ;
    }while (Newnom[i] != '\0') ;
    return ;
}

void Personne::modifPrenom(char* Newprenom)
{
    int i ;

    i = -1 ;
    do{                             // Si prenom vide
        i++ ;                       // Pour mettre le '\0'
        _prenom[i] = Newprenom[i] ;
    }while (Newprenom[i] != '\0') ;

    return ;
}

void Personne::modifMail(char* Newmail)
{
    int i ;
    
    i = -1 ;
    do{                             // Si mail vide
        i++ ;                       // Pour mettre le '\0'
        _mail[i] = Newmail[i] ;
    }while (Newmail[i] != '\0') ;

    return ;
}

void Personne::modifCodePostal(char* NewCodePostal)
{
    int i ;
    
    i = -1 ;
    do{                             // Si codePostal vide
        i++ ;                       // Pour mettre le '\0'
        _codePostal[i] = NewCodePostal[i] ;
    }while (NewCodePostal[i] != '\0') ;

    return ;
}

void Personne::modifEntreprise(Entreprise * NewEntreprise)
{
    _EntrepriseActuelle = NewEntreprise ;
    return ;
}

// Fonctionnalités
// Change un employé en chercheur d'emploi et inversement
// Ajoute les anciens collègues si besoin
void Personne::TransitionStatut(void)
{
    return ;
}

void Personne::deleteProfile(void)
{
    return ;
}

// Renvoie une liste d'entreprise avec les postes correspondant aux compétences de la personne
void Personne::RecherchePosteCompetence(void)
{
    //récupération des entreprises et recherche dans la liste des postes
    return ;
}

// Renvoie une liste d'entreprise avec les postes correspondant aux compétences et au code postal de la personne
void Personne::RecherchePosteCompetenceCodePostal(void)
{
    //idem avec comparaison avec le code postal 
    return ;
}

// Renvoie une liste d'ancien collègue travaillant dans une entreprise donnée
void Personne::RechercheColleguesEntreprise(char* nomEntreprise)
{
    return ;
}
// Met à jour la base de donnée des checheurs d'emplois ou des entreprises, est appelée à chaque fois que des données sont modifiées
// Si le pointeur vers une entrepise est null c'est un Chercheur d'emploi
// Si le pointeur vers une entrepise est non null c'est un Employe
void Personne::MAJDBPersonne(void)
{
    return ;
}
// Affiche les données des anciens collègues employés dans les entreprises qui recherchent ces compétences
// Seulement pour les chercheurs d'emploi
void Personne::ChercheurRechercheColleguesCompetence(Competence * ListeCompetence)
{
    assert(!(this->_EntrepriseActuelle)) ;


    return ;
}

// Affiche les données des anciens collègues disposant des compétences passé en liste
// Seulement pour les employés
void Personne::EmployeRechercheColleguesCompetence(Competence * ListeCompetence)
{
    assert(this->_EntrepriseActuelle) ;


    return ;
}
                                                                            
// Rechercher parmis les chercheurs par competences, affiche les résutats
void Personne::ChercheurCompetence (Competence * listeComp)
{
    return ;
}

// Rechercher parmis les chercheurs par competences et code postal, affiche les résutats
void Personne::ChercheurCompetenceCodePostal (char * CodePostalRecherche)
{
    return ;
}

