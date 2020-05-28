#include "entreprise.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Fonctions memrbes de la calsse Entreprise                                                                     //
//                                                                                                               //
// PEUPIER Baptiste MASSELOT Nicolas                                                                             //
// Cree le 06/04/2020, modifié le 16/05/2020                                                                     //
//                                                                                                               //
// Polytech Marseille, informatique 3A                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

string Entreprise::_DBEnt = "test/FichiersDeTests/entreprise.csv" ;
string Entreprise::_DBP = "test/FichiersDeTests/poste.csv" ;

// Le destructeur
Entreprise::~Entreprise(void)
{
    cout << "Destructeur Entreprise" << endl ;
    if(_profilPoste) delete _profilPoste ;
    if(_next) delete _next ;
    _profilPoste = nullptr ;
    _next = _previous = nullptr ;

    return ;
}

// Fonctionnalités
// Ajoute une entreprise à la liste
void Entreprise::addEntreprise(const string nom, const string codePostal, const string mail)
{
    Entreprise * tmp, *  NewE ;

    tmp = this ;
    while (tmp->next()) tmp = tmp->next() ;
    NewE = new Entreprise (tmp->index()+1, nom, codePostal, mail, NULL, tmp) ;
    tmp->modifNext(NewE) ;
    MAJDBEntreprise() ;

    return ;    
}

// Met à jour la base de donnée des entreprises, est appelée à chaque fois que des données sont modifiées ou ajoutées
// Met également à jour la base de données des postes
void Entreprise::MAJDBEntreprise(string DBE, string DBP)
{
    FILE *new_db_en = fopen("entrepriseNew.csv", "w") ;
    FILE *prev_db_en = fopen(DBE.c_str(), "r") ;
    FILE *new_db_poste = fopen("posteNew.csv", "w") ;
    FILE *prev_db_poste = fopen(DBP.c_str(), "r") ;
    Entreprise * tmp ;
    Competence *tmpC ;
    Poste *tmpP ;
    int indexPoste = 1 ;
    char schema[128] ;

    tmp = this ;
    while (tmp && tmp->previous()) tmp = tmp->previous() ;          // Reviens au début de la liste des entreprises
    if(new_db_en && prev_db_en){
        // Ecriture du schéma de la table
        fscanf(prev_db_en, "%127[^\n\r]", schema) ;
        fprintf(new_db_en, "%s", schema) ;
        fscanf(prev_db_poste, "%127[^\n\r]", schema) ;
        fprintf(new_db_poste, "%s", schema) ;
        // Ecriture des tuples de donnes contenus dans la liste des entreprises
        while(tmp){
            fprintf(new_db_en, "\n%d,%s,%s,%s", tmp->index(), tmp->nom().c_str(), tmp->codePostal().c_str(), tmp->mail().c_str()) ;
            tmpP = tmp->profilPoste() ;
            while(tmpP){
                tmpC = tmpP->CompetencesRequises() ;
                fprintf(new_db_poste, "\n%d,%s,%d,", indexPoste++, tmpP->Titre().c_str(), tmp->index()) ;
                // Ecriture des compétences du poste
                while(tmpC){
                    fprintf(new_db_poste, "%s", tmpC->label().c_str()) ;
                    if(tmpC->next()) fprintf(new_db_poste, ";") ;
                    tmpC = tmpC->next() ;
                }
                tmpP = tmpP->next() ;
            }
            tmp = tmp->next() ;
        }
    }else{
        cout << "Erreur d'ouverture ou de création de la nouvelle db" << endl ;
    }
    fclose(new_db_en) ;
    fclose(prev_db_en) ;
    fclose(new_db_poste) ;
    fclose(prev_db_poste) ;
    remove(DBE.c_str()) ;
    rename("entrepriseNew.csv", DBE.c_str()) ;
    remove(DBP.c_str()) ;
    rename("posteNew.csv", DBP.c_str()) ;

    return ;
}

// Ajoute un poste à la liste des postes à fournir
void Entreprise::addPoste(Poste * ToAdd)
{
    Poste * tmp ;
    
    tmp = this->profilPoste() ;
    while (tmp && tmp->next()) tmp = tmp->next() ;
    tmp->modifNext(ToAdd) ;
    ToAdd->modifPrevious(tmp) ;
    MAJDBEntreprise() ;

    return ;
}

// Supprime un poste à la liste des postes à fournir
void Entreprise::dellPoste(const string TitrePoste)
{
    Poste *tmp ;
    
    tmp = _profilPoste ;
    while(tmp && tmp->Titre()!=TitrePoste) tmp = tmp->next() ;
    if (tmp){                                                           // Si on a trouvé le poste, sinon rien à faire
        if(tmp->next()) tmp->next()->modifPrevious(tmp->previous()) ;
        if(tmp->previous()) tmp->previous()->modifNext(tmp->next()) ;
        if(tmp == _profilPoste) _profilPoste = _profilPoste->next() ;
        tmp->modifNext(nullptr) ;
        tmp->modifPrevious(nullptr) ;
        delete tmp ;
        MAJDBEntreprise() ;
    }

    return ;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Fonctions memrbes de la calsse Poste                                                                          //
//                                                                                                               //
// PEUPIER Baptiste MASSELOT Nicolas                                                                             //
// Cree le 06/04/2020, modifié le 18/04/2020                                                                     //
//                                                                                                               //
// Polytech Marseille, informatique 3A                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Le destructeur
// Détruit seulement le Poste "this"
Poste::~Poste(void)
{
    cout << "Destructeur Poste" << endl ;
    if (_CompetencesRequises) delete _CompetencesRequises ;
    if (_next) delete _next ;
    _CompetencesRequises = nullptr ;
    _next = _previous = nullptr ;

    return ;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Fonctions memrbes de la calsse Competence                                                                     //
//                                                                                                               //
// PEUPIER Baptiste MASSELOT Nicolas                                                                             //
// Cree le 06/04/2020, modifié le 18/04/2020                                                                     //
//                                                                                                               //
// Polytech Marseille, informatique 3A                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Le destructeur
// Détruit la liste de compétence
Competence::~Competence(void)
{
    cout << "Destructeur Competence" << endl ;
    if(_next) delete _next ;
    _next = _previous = nullptr ;

    return ;
}

// Fonctionnalité sur les Competences
// Ajoute une compétence en fin de la liste des compétences
// Nécéssite une première compétence déjà définie (this)
void Competence::AddCompetence (const string label)
{
    Competence * tmp ;
    tmp = this ;
    while(tmp->_next) tmp = tmp->_next ;
    tmp->_next = new Competence (label, NULL, tmp) ;    // Besoin d'allocation dynamique pour étendre la durée de vie des nouvelles compétences

    return ;
}

// Enlève une compétence dont le label est passé en paramètre
void Competence::delCompetence (const string label)
{
    Competence * tmp ;
    string tmpLabel ;
    bool mememot ;

    tmp = this ;
    if(tmp != NULL){
        mememot = false ;
        while (tmp!=NULL && mememot==false){
            mememot = true ;
            if(label != tmp->_label){
                mememot = false ;
                tmp = tmp->_next ;
            }
        }
        if(tmp != NULL){                                                        // Si on a trouvé le label
            if(tmp != this){
                if(tmp->_previous != NULL) tmp->_previous->_next = tmp->_next ;
                if(tmp->_next != NULL) tmp->_next->_previous = tmp->_previous ;
                tmp->modifNext(NULL) ;
                tmp->modifPrevious(NULL) ;
                delete tmp ;
            }else{                                                              // Si on supprime la première compétence, on recopie la seconde compétence et on suprime cette dernière
                tmpLabel = _next->_label ;
                this->delCompetence(_next->_label) ;
                this->modifLabel(tmpLabel) ;
            }
        }
    }

    return ;
}

// Revoie 1 si la compétence est présente dans une liste de compétence passée en argument, 0 sinon
bool Competence::IsInList (Competence * listeComp)
{
    bool InList ;
    
    InList = false ;
    while (listeComp && !InList){
        if(_label == listeComp->_label) InList = true ;
        listeComp = listeComp->_next ;
    }

    return InList ;
}
