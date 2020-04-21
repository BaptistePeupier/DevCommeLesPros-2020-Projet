#include "personne.h"
#include <string.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Fonctions memrbes de la classe Personne                                                                       //
//                                                                                                               //
// PEUPIER Baptiste                                                                                              //
// Cree le 06/04/2020, modifié le 21/04/2020                                                                     //
//                                                                                                               //
// Polytech Marseille, informatique 3A                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Un constructeur
Personne::Personne(int index, char* nom, char* prenom, char* mail, char* codePostal, Personne * nextP, Personne * previousP, Competence * CompetencesPropres, AncienCollegue * ListAncienCollegues, Entreprise * EntrepriseActuelle)
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
    _ListAncienCollegues = ListAncienCollegues ;
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

Personne * Personne::previousP(void)
{
    return _previousP ;
}

Personne * Personne::nextP(void)
{
    return _nextP ;
}

Competence * Personne::CompetencePropres(void)
{
    return _CompetencesPropres ;
}

AncienCollegue * Personne::ListAncienCollegues(void)
{
    return _ListAncienCollegues ;
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

void Personne::modifPreviousP(Personne * NewPreviousP)
{
    _previousP = NewPreviousP ;
}

void Personne::modifNextP(Personne * NewNextP)
{
    _nextP = NewNextP ;
}

void Personne::modifEntreprise(Entreprise * NewEntreprise)
{
    _EntrepriseActuelle = NewEntreprise ;
    return ;
}

void Personne::modifCompetencePropres(Competence * NewListeCompetence)
{
    _CompetencesPropres = NewListeCompetence ;
}

void Personne::modifAncienCollegues(AncienCollegue * NewListCollegues)
{
    _ListAncienCollegues = NewListCollegues ;
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
    Personne * tmp ;
    Competence *tmp_skill ;
    AncienCollegue * tmp_collegue ;
    FILE *prev_db_chercheurs ;
    FILE *new_db_chercheurs ;
    FILE *prev_db_employes ;
    FILE *new_db_employes ;
    char schema_db[128] ;
    string skills_to_write ;
    string collegues_to_write ;

    tmp = this ;
    while (tmp->_previousP != NULL) tmp = tmp->previousP() ;                    //retour au début de la liste des personnes
    new_db_employes = fopen("test/FichiersDeTests/employes_new.csv", "w") ;             // A modifier lorsque l'on utilisera la vrai DB
    prev_db_employes = fopen("test/FichiersDeTests/employes.csv", "r") ;                // A modifier lorsque l'on utilisera la vrai DB
    new_db_chercheurs = fopen("test/FichiersDeTests/chercheurd'emploi_new.csv", "w") ;  // A modifier lorsque l'on utilisera la vrai DB
    prev_db_chercheurs = fopen("test/FichiersDeTests/chercheurd'emploi.csv", "r") ;     // A modifier lorsque l'on utilisera la vrai DB 
    fscanf(prev_db_employes, "%127[^\n\r]", schema_db) ;                         //on recopie le schema de la base de données 
    fprintf(new_db_employes, "%s", schema_db) ;
    fscanf(prev_db_chercheurs, "%127[^\n\r]", schema_db) ;                       //on recopie le schema de la base de données 
    fprintf(new_db_chercheurs, "%s", schema_db) ;

    if (new_db_employes && prev_db_employes && new_db_chercheurs && prev_db_chercheurs) {
        while (tmp) {
            tmp_skill = tmp->CompetencePropres() ;               //on parcours les compétences de la personne et on les concatène dans une string qui sera mise dans le csv
            while (tmp_skill) {
                skills_to_write += tmp_skill->label();
                tmp_skill = tmp_skill->next() ;
                if (tmp_skill) {
                    skills_to_write += ";" ;
                }
            }

            tmp_collegue = tmp->ListAncienCollegues() ;          //idem pour les anciens collegues employes
            while (tmp_collegue) {
                if(tmp_collegue->currentA()->EntrepriseActuelle()){
                    collegues_to_write += tmp_collegue->currentA()->index() ;
                    tmp_collegue = tmp_collegue->nextA() ;
                    if (tmp_collegue) {
                        collegues_to_write += ";" ;
                    }
                }
            }       // à tester après la lecture de la db
            collegues_to_write += "," ;

            tmp_collegue = tmp->ListAncienCollegues() ;          //on rajoute les anciens collegues chercheur d'emploi
            while (tmp_collegue) {
                if(!(tmp_collegue->currentA()->EntrepriseActuelle())){
                    collegues_to_write += tmp_collegue->currentA()->index() ;
                    tmp_collegue = tmp_collegue->nextA() ;
                    if (tmp_collegue) {
                        collegues_to_write += ";" ;
                    }
                }
            }       // à tester après la lecture de la db
                    
            if (tmp->EntrepriseActuelle()) {
                fprintf(new_db_employes, "\n%d,%s,%s,%s,%s,%d,%s,%s", tmp->index(), tmp->nom(), tmp->prenom(), tmp->mail(),tmp->codePostal(),tmp->EntrepriseActuelle()->index(),skills_to_write.c_str(),collegues_to_write.c_str()) ; //il faut convertir la string en char* avec c_str pour utiliser fprintf
                skills_to_write.clear() ;       //on réinitialise les string avant de passer à la personne suivante
                collegues_to_write.clear() ;
                tmp = tmp->_nextP ;
            } else {
                fprintf(new_db_chercheurs, "\n%d,%s,%s,%s,%s,%s,%s", tmp->index(), tmp->nom(), tmp->prenom(), tmp->mail(),tmp->codePostal(),skills_to_write.c_str(),collegues_to_write.c_str()) ; //il faut convertir la string en char* avec c_str pour utiliser fprintf
                skills_to_write.clear() ;       //on réinitialise les string avant de passer à la personne suivante
                collegues_to_write.clear() ;
                tmp = tmp->_nextP ;
            }   
        }
    }else{
        cout << "Erreur d'ouverture ou de création de la nouvelle db" << endl ;
    }
    
    fclose(new_db_chercheurs) ;
    fclose(prev_db_chercheurs) ;
    fclose(new_db_employes);
    fclose(prev_db_employes) ;
    remove("test/FichiersDeTests/employes.csv") ;                                                               // A modifier lorsque l'on utilisera la vrai DB
    rename("test/FichiersDeTests/employes_new.csv", "test/FichiersDeTests/employes.csv") ;                      // A modifier lorsque l'on utilisera la vrai DB
    remove("test/FichiersDeTests/chercheurd'emploi.csv") ;                                                      // A modifier lorsque l'on utilisera la vrai DB
    rename("test/FichiersDeTests/chercheurd'emploi_new.csv", "test/FichiersDeTests/chercheurd'emploi.csv") ;    // A modifier lorsque l'on utilisera la vrai DB
    
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

// Un constructeur
AncienCollegue::AncienCollegue(Personne * currentA, AncienCollegue * nextA, AncienCollegue * previousA)
{
    _currentA = currentA ;
    _nextA = nextA ;
    _previousA = previousA ;

    return ;
}

// Le destructeur
AncienCollegue::~AncienCollegue(void)
{
    return ;
}

// Accesseurs
Personne * AncienCollegue::currentA(void)
{
    return NULL ;
}

AncienCollegue * AncienCollegue::nextA(void)
{
    return NULL ;
}

AncienCollegue * AncienCollegue::previousA(void)
{
    return NULL ;
}

// Modifieurs
void AncienCollegue::modifCurrentA(Personne * NewCurrent)
{
    return ;
}

void AncienCollegue::modifNextA(AncienCollegue * NewNextA)
{
    return ;
}

void AncienCollegue::modifPreviousA(AncienCollegue * NewPreviousA)
{
    return ;
}

// Fonctionnalités
// Ajoute une personne à la liste
void AncienCollegue::addAncienCollegue(Personne * NewAncienCollegue)
{
    return ;
}

// Retire une personne de la liste
void AncienCollegue::dellAncienCollegue(Personne * AncienCollegueToDell)
{
    return ;
}
