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
Personne::Personne(int index, const char* nom, const char* prenom, const char* mail, const char* codePostal, Personne * nextP, Personne * previousP, Competence * CompetencesPropres, AncienCollegue * ListAncienCollegues, Entreprise * EntrepriseActuelle)
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
    if(_CompetencesPropres) delete _CompetencesPropres ;
    if(_ListAncienCollegues) delete _ListAncienCollegues ;
    if(_nextP) delete _nextP ;
    _CompetencesPropres = nullptr ;
    _ListAncienCollegues = nullptr ;
    _nextP = _previousP = nullptr ;
    _EntrepriseActuelle = nullptr ;

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
    MAJDBPersonne();

    return ;
}

void Personne::modifNom(const char* Newnom)
{
    int i ;

    i = -1 ;
    do{                             // Si nom vide
        i++ ;                       // Pour mettre le '\0'
        _nom[i] = Newnom[i] ;
    }while (Newnom[i] != '\0') ;
    MAJDBPersonne() ;

    return ;
}

void Personne::modifPrenom(const char* Newprenom)
{
    int i ;

    i = -1 ;
    do{                             // Si prenom vide
        i++ ;                       // Pour mettre le '\0'
        _prenom[i] = Newprenom[i] ;
    }while (Newprenom[i] != '\0') ;
    MAJDBPersonne();

    return ;
}

void Personne::modifMail(const char* Newmail)
{
    int i ;
    
    i = -1 ;
    do{                             // Si mail vide
        i++ ;                       // Pour mettre le '\0'
        _mail[i] = Newmail[i] ;
    }while (Newmail[i] != '\0') ;
    MAJDBPersonne() ;

    return ;
}

void Personne::modifCodePostal(const char* NewCodePostal)
{
    int i ;
    
    i = -1 ;
    do{                             // Si codePostal vide
        i++ ;                       // Pour mettre le '\0'
        _codePostal[i] = NewCodePostal[i] ;
    }while (NewCodePostal[i] != '\0') ;
    MAJDBPersonne() ;

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
    MAJDBPersonne() ;
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
    //suppression de cette même personne dans les anciens collègues
    //suppression de la personne dans la liste
    return ;
}

// Renvoie une liste d'entreprise avec les postes correspondant aux compétences de la personne 
//on prend en paramètre le pointeur sur le début de la liste des entreprises
void Personne::RecherchePosteCompetence(Entreprise * listeEntreprises)
{
    Poste *tmp_poste ;
    Entreprise *tmp_entreprise = listeEntreprises ;
    Competence *tmp_skills_poste ;
    Competence *tmp_skills_personne = _CompetencesPropres ;
    string label_skill_personne , label_skill_poste ;
    int nbcompetences_poste = 0 ,  competences_dispo_pers = 0 ;
    
    while (tmp_entreprise) //parcours de la liste des entreprises 
    {
        tmp_poste = tmp_entreprise->profilPoste() ;
        while (tmp_poste) {
            tmp_skills_poste = tmp_poste->CompetencesRequises() ;               //on compte les compétences du poste
            while (tmp_skills_poste) {
                nbcompetences_poste++ ;
                tmp_skills_poste = tmp_skills_poste->next() ;
            }
            
            tmp_skills_poste = tmp_poste->CompetencesRequises() ; 
            while (tmp_skills_poste) {
                tmp_skills_personne = _CompetencesPropres ;         //on compare les compétences du poste avec celles de la personne
                while (tmp_skills_personne) {
                    label_skill_personne = string(tmp_skills_personne->label()) ;
                    label_skill_poste = string(tmp_skills_poste->label()) ;
                    if (label_skill_personne == label_skill_poste) {
                        competences_dispo_pers++ ;
                    }
                    tmp_skills_personne = tmp_skills_personne->next() ;
                }
                
                tmp_skills_poste = tmp_skills_poste->next() ;
            }
            
            if (competences_dispo_pers == nbcompetences_poste) {
                cout << "-----------------------------------------------" << endl ;
                cout << "titre : " << tmp_poste->Titre() << " | Entreprise : " << tmp_entreprise->nom() << " | mail :" << tmp_entreprise->mail() << " | code Postal :" << tmp_entreprise->codePostal() << endl ;
                cout << "-----------------------------------------------" << endl ;
            }
            
            competences_dispo_pers = 0 ;
            nbcompetences_poste = 0 ;
            tmp_poste = tmp_poste->next() ;
        }
        tmp_entreprise = tmp_entreprise->next() ;
    }

    return ;
}

// Renvoie une liste d'entreprise avec les postes correspondant aux compétences et au code postal de la personne
void Personne::RecherchePosteCompetenceCodePostal(Entreprise * listeEntreprises)
{
    Poste *tmp_poste ;
    Entreprise *tmp_entreprise = listeEntreprises ;
    Competence *tmp_skills_poste ;
    Competence *tmp_skills_personne = _CompetencesPropres ;
    string label_skill_personne , label_skill_poste , cp_entreprise , cp_personne = string(this->codePostal()) ;
    int nbcompetences_poste = 0 ,  competences_dispo_pers = 0 ;
    
    while (tmp_entreprise) //parcours de la liste des entreprises 
    {
        cp_entreprise = string(tmp_entreprise->codePostal()) ;
        tmp_poste = tmp_entreprise->profilPoste() ;

        if (cp_entreprise == cp_personne) {
            while (tmp_poste) {
                tmp_skills_poste = tmp_poste->CompetencesRequises() ;               //on compte les compétences du poste
                while (tmp_skills_poste) {
                    nbcompetences_poste++ ;
                    tmp_skills_poste = tmp_skills_poste->next() ;
                }
            
                tmp_skills_poste = tmp_poste->CompetencesRequises() ; 
                while (tmp_skills_poste) {
                    tmp_skills_personne = _CompetencesPropres ;         //on compare les compétences du poste avec celles de la personne
                    while (tmp_skills_personne) {
                        label_skill_personne = string(tmp_skills_personne->label()) ;
                        label_skill_poste = string(tmp_skills_poste->label()) ;
                        if (label_skill_personne == label_skill_poste) {
                            competences_dispo_pers++ ;
                        }
                        tmp_skills_personne = tmp_skills_personne->next() ;
                    }
                    
                    tmp_skills_poste = tmp_skills_poste->next() ;
                }
                
                if (competences_dispo_pers == nbcompetences_poste) {
                    cout << "-----------------------------------------------" << endl ;
                    cout << "titre : " << tmp_poste->Titre() << " | Entreprise : " << tmp_entreprise->nom() << " | mail :" << tmp_entreprise->mail() << " | code Postal :" << tmp_entreprise->codePostal() << endl ;
                    cout << "-----------------------------------------------" << endl ;
                }
                
                competences_dispo_pers = 0 ;
                nbcompetences_poste = 0 ;
                tmp_poste = tmp_poste->next() ;
            }
        }
        
        tmp_entreprise = tmp_entreprise->next() ;
    }

    return ;
}

// Renvoie une liste d'ancien collègue travaillant dans une entreprise donnée
void Personne::RechercheColleguesEntreprise(const char* nomEntreprise)
{
    AncienCollegue * tmp ;
    char * entreprise_tmp ;
    int i ;
    bool afficher ;

    tmp = this->ListAncienCollegues() ;
    while (tmp) {
        if (tmp->currentA()->EntrepriseActuelle()) {
            entreprise_tmp = tmp->currentA()->EntrepriseActuelle()->nom() ;
            i = 0 ;
            afficher = true ;
            do
            {
                if (entreprise_tmp[i] != nomEntreprise[i]) {
                    afficher = false ;
                }
                i++ ;
            } while (entreprise_tmp[i] != '\0');

            if (afficher) {
                cout << "-------------------------------------------------------------------------------------------" << endl ;
                cout << " Nom : " << tmp->currentA()->nom() << "| Prenom : " << tmp->currentA()->prenom() << "| Mail : " << tmp->currentA()->mail() << endl;
                cout << "--------------------------------------------------------------------------------------------" << endl ;
            }
        }
        tmp = tmp->nextA() ;
    }

    //chercher dans la liste des anciens collègues  vérifier si il faut chercher dans previous
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
    if (this->EntrepriseActuelle()) {                                                               //ouverture du csv chercheurd'emploi ou employes selon la liste où se trouve la personne
        new_db_employes = fopen("test/FichiersDeTests/employes_new.csv", "w") ;             // A modifier lorsque l'on utilisera la vrai DB
        prev_db_employes = fopen("test/FichiersDeTests/employes.csv", "r") ;                // A modifier lorsque l'on utilisera la vrai DB
        fscanf(prev_db_employes, "%127[^\n\r]", schema_db) ;                         //on recopie le schema de la base de données 
        fprintf(new_db_employes, "%s", schema_db) ;
    }else {
        new_db_chercheurs = fopen("test/FichiersDeTests/chercheurd'emploi_new.csv", "w") ;  // A modifier lorsque l'on utilisera la vrai DB
        prev_db_chercheurs = fopen("test/FichiersDeTests/chercheurd'emploi.csv", "r") ;     // A modifier lorsque l'on utilisera la vrai DB 
        
        fscanf(prev_db_chercheurs, "%127[^\n\r]", schema_db) ;                       //on recopie le schema de la base de données 
        fprintf(new_db_chercheurs, "%s", schema_db) ;
    }
    
    if ((new_db_employes && prev_db_employes) || (new_db_chercheurs && prev_db_chercheurs)) {
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
                if(tmp_collegue->currentA() && tmp_collegue->currentA()->EntrepriseActuelle()){                             //attention à CurrentA qui peut être NULL et causer une segfault
                    if (collegues_to_write.length() != 0 && collegues_to_write[collegues_to_write.length()-1] != ',') {
                        collegues_to_write += ";" ;
                    }
                    collegues_to_write += to_string(tmp_collegue->currentA()->index()) ;
                }
                tmp_collegue = tmp_collegue->nextA() ;
                
                
            }       // à tester après la lecture de la db
            collegues_to_write += "," ;

            tmp_collegue = tmp->ListAncienCollegues() ;          //on rajoute les anciens collegues chercheur d'emploi
            while (tmp_collegue) {
                if(tmp_collegue->currentA() && !(tmp_collegue->currentA()->EntrepriseActuelle())){                          //idem
                    if (collegues_to_write.length() != 0 && collegues_to_write[collegues_to_write.length()-1] != ',') {
                        collegues_to_write += ";" ;
                    }
                    collegues_to_write += to_string(tmp_collegue->currentA()->index()) ;   
                }
                tmp_collegue = tmp_collegue->nextA() ;
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
    
    if (this->EntrepriseActuelle()) {
        fclose(new_db_employes);
        fclose(prev_db_employes) ;
        remove("test/FichiersDeTests/employes.csv") ;                                                               // A modifier lorsque l'on utilisera la vrai DB
        rename("test/FichiersDeTests/employes_new.csv", "test/FichiersDeTests/employes.csv") ;                      // A modifier lorsque l'on utilisera la vrai DB
    } else {
        fclose(new_db_chercheurs) ;
        fclose(prev_db_chercheurs) ;
        remove("test/FichiersDeTests/chercheurd'emploi.csv") ;                                                      // A modifier lorsque l'on utilisera la vrai DB
        rename("test/FichiersDeTests/chercheurd'emploi_new.csv", "test/FichiersDeTests/chercheurd'emploi.csv") ;    // A modifier lorsque l'on utilisera la vrai DB
    }
    
    return ;
}
// Affiche les données des anciens collègues employés dans les entreprises qui recherchent ces compétences
// Seulement pour les chercheurs d'emploi
void Personne::ChercheurRechercheColleguesCompetence(Competence * ListeCompetence)
{
    assert(!(this->_EntrepriseActuelle)) ;
    Competence * tmp_comp , *tmp_comp_entreprise;
    AncienCollegue * tmp_collegue ;
    Poste * tmp_poste ;
    string label_skill_entreprise, label_skill_liste ;
    bool displayed ;

    tmp_comp = ListeCompetence ;
    tmp_collegue = _ListAncienCollegues ;               //initialisation des pointeurs
    while (tmp_comp) {
        cout << ">>>>collegues travaillant dans les entreprise qui recherchent la competence " << tmp_comp->label() << endl;
        label_skill_liste = string(tmp_comp->label()) ;                 //recherche dans la liste des compétence fournie
        while (tmp_collegue) {
            displayed = false ;
            if (tmp_collegue->currentA()->EntrepriseActuelle()) {               //recherche dans la liste des anciens collègues seulement sur ceux qui sont employés
                tmp_poste = tmp_collegue->currentA()->EntrepriseActuelle()->profilPoste() ;
                while (tmp_poste) {
                    tmp_comp_entreprise = tmp_poste->CompetencesRequises() ;            //parcours des compétences requises pour un poste
                    while (tmp_comp_entreprise) {
                        label_skill_entreprise = string(tmp_comp_entreprise->label()) ;
                        if (label_skill_entreprise == label_skill_liste && !displayed) {
                            cout << "-------------------------------------------------------------------------------------------" << endl ;
                            cout << " Nom : " << tmp_collegue->currentA()->nom() << "| Prenom : " << tmp_collegue->currentA()->prenom() << "| Mail : " << tmp_collegue->currentA()->mail() << endl;
                            cout << "--------------------------------------------------------------------------------------------" << endl ;
                            displayed = true ; //on évite d'afficher plusieurs fois le même collègue si il y a plusieurs postes recherchant la compétence
                        }
                        tmp_comp_entreprise = tmp_comp_entreprise->next() ;
                    }
                    tmp_poste = tmp_poste->next() ;
                }   
            }
            tmp_collegue = tmp_collegue->nextA() ;
        }
        tmp_collegue = _ListAncienCollegues ; //quand on a recherché pour une compétence on réinitialise le pointeur vers les anciens collègues
        tmp_comp = tmp_comp->next() ;
    }
    
    return ;
}

// Affiche les données des anciens collègues disposant des compétences passé en liste
// Seulement pour les employés
void Personne::EmployeRechercheColleguesCompetence(Competence * ListeCompetence)
{
    assert(this->_EntrepriseActuelle) ;
    AncienCollegue * tmp_collegue = _ListAncienCollegues;
    Competence * tmp_comp_collegue , *tmp_comp = ListeCompetence;           //initialisation des pointeurs
    string label_skill_collegue, label_skill_liste , entreprise_pers , entreprise_collegue;
    int nb_skill_liste = 0 ,  nb_skill_match;

    entreprise_pers = string(_EntrepriseActuelle->nom()) ;

    while (tmp_comp) {
        nb_skill_liste++ ;
        tmp_comp = tmp_comp->next() ; 
    }

    while (tmp_collegue) {
        nb_skill_match = 0 ;

        if (tmp_collegue->currentA()) {                                                 //attention à la donnée membre currentA qui peut être NULL
            if (tmp_collegue->currentA()->EntrepriseActuelle()) {
                entreprise_collegue = string(tmp_collegue->currentA()->EntrepriseActuelle()->nom()) ;
            }else {
                entreprise_collegue = "" ;
            }
            if (entreprise_pers != entreprise_collegue) {
                tmp_comp_collegue = tmp_collegue->currentA()->CompetencePropres() ;

                while (tmp_comp_collegue) {
                    tmp_comp = ListeCompetence ;                //réinitialisation du parcours de la liste des compétences
                    label_skill_collegue = string(tmp_comp_collegue->label()) ;
                    while (tmp_comp) {
                        label_skill_liste = string(tmp_comp->label()) ;
                        if (label_skill_collegue == label_skill_liste) {
                            nb_skill_match++ ;
                        }
                        tmp_comp = tmp_comp->next() ;
                    }
                    tmp_comp_collegue = tmp_comp_collegue->next() ; 
                }

                if (nb_skill_liste == nb_skill_match) {
                    cout << "-------------------------------------------------------------------------------------------" << endl ;
                    cout << " Nom : " << tmp_collegue->currentA()->nom() << "| Prenom : " << tmp_collegue->currentA()->prenom() << "| Mail : " << tmp_collegue->currentA()->mail() << endl;
                    cout << "--------------------------------------------------------------------------------------------" << endl ;
                }
            }
        }
        tmp_collegue = tmp_collegue->nextA() ;
    }

    return ;
}
                                                                            
// Rechercher parmis les chercheurs par competences, affiche les résultats
void Personne::ChercheurCompetence (Competence * listeComp)
{
    Competence * tmp_comp = listeComp , *tmp_comp_pers;
    Personne * tmp_pers = this ;
    string label_skill_pers, label_skill_liste ;
    int nb_skill_match , nb_skill_liste = 0;
    assert(!(this->_EntrepriseActuelle)) ;

    while (tmp_pers->_previousP != NULL) tmp_pers = tmp_pers->previousP() ; //retour au début de la liste des personnes
    while (tmp_comp) {
        nb_skill_liste++ ;
        tmp_comp = tmp_comp->next() ; //on compte le nombre de compétences de la liste
    }
    
    while (tmp_pers) {
        nb_skill_match = 0 ;
        tmp_comp_pers = tmp_pers->CompetencePropres() ;     

        while (tmp_comp_pers) {
            tmp_comp = listeComp ;                //réinitialisation du parcours de la liste des compétences
            label_skill_pers = string(tmp_comp_pers->label()) ;
            while (tmp_comp) {
                label_skill_liste = string(tmp_comp->label()) ;
                if (label_skill_pers == label_skill_liste) {
                    nb_skill_match++ ;
                }
                tmp_comp = tmp_comp->next() ;
            }
            tmp_comp_pers = tmp_comp_pers->next() ; 
        }
        if (nb_skill_liste == nb_skill_match) {
            cout << "-------------------------------------------------------------------------------------------" << endl ;
            cout << " Nom : " << tmp_pers->nom() << "| Prenom : " << tmp_pers->prenom() << "| Mail : " << tmp_pers->mail() << endl;
            cout << "--------------------------------------------------------------------------------------------" << endl ;
        }
        
        tmp_pers = tmp_pers->nextP() ;
    }
    return ;
}

// Rechercher parmis les chercheurs par competences et code postal, affiche les résultats
void Personne::ChercheurCompetenceCodePostal (Competence * listeComp ,const char * CodePostalRecherche)
{
    Competence * tmp_comp = listeComp , *tmp_comp_pers;
    Personne * tmp_pers = this ;
    string label_skill_pers, label_skill_liste , cp_recherche = string(CodePostalRecherche), cp_pers ;
    int nb_skill_match , nb_skill_liste = 0;
    assert(!(this->_EntrepriseActuelle)) ;

    while (tmp_pers->_previousP != NULL) tmp_pers = tmp_pers->previousP() ; //retour au début de la liste des personnes
    while (tmp_comp) {
        nb_skill_liste++ ;
        tmp_comp = tmp_comp->next() ; //on compte le nombre de compétences de la liste
    }
    
    while (tmp_pers) {
        cp_pers = string(tmp_pers->codePostal()) ;
        if (cp_pers == cp_recherche) {                          //si le code postal est pas celui recherché on passe à la personne suivante dans la liste
            nb_skill_match = 0 ;
            tmp_comp_pers = tmp_pers->CompetencePropres() ;     

            while (tmp_comp_pers) {
                tmp_comp = listeComp ;                //réinitialisation du parcours de la liste des compétences
                label_skill_pers = string(tmp_comp_pers->label()) ;
                while (tmp_comp) {
                    label_skill_liste = string(tmp_comp->label()) ;
                    if (label_skill_pers == label_skill_liste) {
                        nb_skill_match++ ;
                    }
                    tmp_comp = tmp_comp->next() ;
                }
                tmp_comp_pers = tmp_comp_pers->next() ; 
            }
            if (nb_skill_liste == nb_skill_match) {
                cout << "-------------------------------------------------------------------------------------------" << endl ;
                cout << " Nom : " << tmp_pers->nom() << "| Prenom : " << tmp_pers->prenom() << "| Mail : " << tmp_pers->mail() << endl;
                cout << "--------------------------------------------------------------------------------------------" << endl ;
            }
        }
        tmp_pers = tmp_pers->nextP() ;
    }
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
    cout << "Destructeur AncienCollegue" << endl ;
    if(_nextA) delete _nextA ;
    _nextA = _previousA = nullptr ;
    _currentA = nullptr ;

    return ;
}

// Accesseurs
Personne * AncienCollegue::currentA(void)
{
    return _currentA ;
}

AncienCollegue * AncienCollegue::nextA(void)
{
    return _nextA ;
}

AncienCollegue * AncienCollegue::previousA(void)
{
    return _previousA ;
}

// Modifieurs
void AncienCollegue::modifCurrentA(Personne * NewCurrent)
{
    _currentA = NewCurrent ;

    return ;
}

void AncienCollegue::modifNextA(AncienCollegue * NewNextA)
{
    _nextA = NewNextA ;

    return ;
}

void AncienCollegue::modifPreviousA(AncienCollegue * NewPreviousA)
{
    _previousA = NewPreviousA ;

    return ;
}

// Fonctionnalités
// Ajoute une personne à la liste
void AncienCollegue::addAncienCollegue(Personne * NewAncienCollegue,Personne * base_pers)
{
    AncienCollegue * tmp_collegue = this ;
    while (tmp_collegue->nextA()) tmp_collegue = tmp_collegue->nextA() ;                //parcours jusqu'à la fin de la liste
    tmp_collegue->modifNextA(new AncienCollegue(NewAncienCollegue,NULL,tmp_collegue)) ; //ajout du nouveau collègue
    base_pers->MAJDBPersonne() ;                                                        //mise à jour de la base de données à partir de la personne qui a la liste d'anciens collègues 
                                                                                        //pour éviter de mettre à jour le mauvais csv 
                                                                                        //on passe en paramètre l'addresse de celle-ci pour éviter de faire des parcours de liste
    return ;
}

// Retire une personne de la liste
void AncienCollegue::dellAncienCollegue(Personne * AncienCollegueToDell,Personne *base_pers)
{
    AncienCollegue * tmp_collegue = this ;
    AncienCollegue * collegue_to_delete ;
    Personne * tmp_pers ; 

    while (tmp_collegue) {
        if (tmp_collegue->currentA() == AncienCollegueToDell) {     //recherche en avant dans la liste 
            collegue_to_delete = tmp_collegue ;
        }
        tmp_collegue = tmp_collegue->nextA() ;
    }
    if (!collegue_to_delete)
    {
        tmp_collegue = this ;
        while (tmp_collegue) {
            if (tmp_collegue->currentA() == AncienCollegueToDell) {     //recherche en arrière dans la liste 
                collegue_to_delete = tmp_collegue ;
            }
            tmp_collegue = tmp_collegue->previousA() ;
        }
    }
    
    if (collegue_to_delete) {
        if (collegue_to_delete != this) {
            if(collegue_to_delete->_previousA != NULL) collegue_to_delete->_previousA->_nextA = collegue_to_delete->_nextA ;
            if(collegue_to_delete->_nextA != NULL) collegue_to_delete->_nextA->_previousA = collegue_to_delete->_previousA ;
            collegue_to_delete->modifNextA(NULL) ;
            collegue_to_delete->modifPreviousA(NULL) ;
            delete collegue_to_delete ;
        } else {
            tmp_pers = _nextA->currentA() ;
            this->dellAncienCollegue(_nextA->currentA(),base_pers) ;
            this->modifCurrentA(tmp_pers) ;
        }     
    }
    
    base_pers->MAJDBPersonne() ; //mise à jour de la base de données à partir de la personne qui a la liste d'anciens collègues 
                                 //pour éviter de mettre à jour le mauvais csv 
                                 //on passe en paramètre l'addresse de celle-ci pour éviter de faire des parcours de liste
    return ;
}
