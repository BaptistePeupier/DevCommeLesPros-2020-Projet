#include "entreprise.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Fonctions memrbes de la calsse Entreprise                                                                     //
//                                                                                                               //
// PEUPIER Baptiste                                                                                              //
// Cree le 06/04/2020, modifié le 06/04/2020                                                                     //
//                                                                                                               //
// Polytech Marseille, informatique 3A                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Les constructeurs
Entreprise::Entreprise(int index, char* nom, char* codePostal, char* mail, Entreprise & next, Entreprise & previous)
{
    return ;
}

// Le destructeur
Entreprise::~Entreprise(void)
{
    return ;
}

// Accesseurs
int Entreprise::index(void)
{
    return 0 ;
}

char* Entreprise::nom(void)
{
    return NULL ;
}

char* Entreprise::codePostal(void)
{
    return NULL;
}

char* Entreprise::mail(void)
{
    return NULL ;
}

Entreprise * Entreprise::next(void)
{
    return NULL ;
}

Entreprise * Entreprise::previous(void)
{
    return NULL ;
}

// Modifieurs
void Entreprise::modifIndex(int NewIndex)
{
    return ;
}

void Entreprise::modifNom(char* NewNom)
{
    return ;
}

void Entreprise::modifCodePostal(char* NewCodePostal)
{
    return ;
}

void Entreprise::modifMail(char * NewMail)
{
    return ;
}

void Entreprise::modifNext(Entreprise & next)
{
    return ;
}

void Entreprise::modifPrevious(Entreprise & previous)
{
    return ;
}

// Fonctions de liste
// Renvoie la longueur de la liste d'entreprises
int Entreprise::Longueur(void)
{
    return 0 ;
}

// Fonctionnalités
// Supprime le profile (l'entreprise) ainsi que les postes qui lui sont lié
void Entreprise::deleteProfile(void)
{
    return ;
}

// Rechercher parmis les chercheurs par competences

// Rechercher parmis les chercheurs par competences et code postal

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Fonctions memrbes de la calsse Poste                                                                         //
//                                                                                                               //
// PEUPIER Baptiste                                                                                              //
// Cree le 06/04/2020, modifié le 06/04/2020                                                                     //
//                                                                                                               //
// Polytech Marseille, informatique 3A                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Les constructeurs
Poste::Poste(char* Titre, Poste & next, Poste & previous, Competence & CompetencesRequises)
{
    return ;
}

// Le destructeur
Poste::~Poste(void)
{
    return ;
}

// Accesseurs
char* Poste::Titre(void)
{
    return NULL ;
}

Poste * Poste::next(void)
{
    return NULL ;
}

Poste * Poste::previous(void)
{
    return NULL ;
}

Competence * Poste::CompetencesRequises(void)
{
    return NULL ;
}

// Modifieurs
void Poste::modifTitre(char* NewTitre)
{
    return ;
}

void Poste::modifNext(char* NewNext)
{
    return ;
}

void Poste::modifPrevious(char* NewPrevious)
{
    return ;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Fonctions memrbes de la calsse Competence                                                                     //
//                                                                                                               //
// PEUPIER Baptiste                                                                                              //
// Cree le 06/04/2020, modifié le 06/04/2020                                                                     //
//                                                                                                               //
// Polytech Marseille, informatique 3A                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Les constructeurs
Competence::Competence(char* label, Competence * next, Competence * previous)
{
    int i ;

    i = -1 ;
    do{                             // Si label vide
        i++ ;                       // Pour mettre le '\0'
        _label[i] = label[i] ;
    }while (label[i] != '\0') ;
    _next = next ;
    _previous = previous ;
    
    return ;
}

// Le destructeur
Competence::~Competence(void)
{
    return ;
}

// Accesseurs
char* Competence::label(void)
{
    return _label ;
}

Competence * Competence::next(void)
{
    return NULL ;
}

Competence * Competence::previous(void)
{
    return NULL ;
}

// Modifieurs
void Competence::modifLabel(char* NewLabel)
{
    return ;
}

void Competence::modifNext(char* NewNext)
{
    return ;
}

void Competence::modifPrevious(char* NewPrevious)
{
    return ;
}

// Fonctionnalité sur les Competences
// Ajoute une compétence en fin de la liste des compétences
void Competence::AddCompetence (Competence & NewCompetence)
{
    Competence * tmp ;

    tmp = this ;
    while(tmp->_next != NULL) tmp = tmp->_next ;
    tmp->_next = &NewCompetence ;
    NewCompetence._previous = tmp ;

    return ;
}

// Enlève une compétence dont le label est passé en paramètre
void Competence::delCompetence (char* label)
{
    Competence * tmp ;
    int i ;
    bool mememot ;

    tmp = this ;
    if(tmp != NULL){
        mememot = false ;
        while (tmp!=NULL && mememot==false){
            i = 0 ;
            mememot = true ;
            while (tmp->_label[i]!='\0' && label[i]!='\0'){
                if(label[i] != tmp->_label[i]) mememot = false ;
                i++ ;
            }
            if((label[i]=='\0' && tmp->_label[i]!='\0') || (tmp->_label[i]=='\0' && label[i]!='\0')) mememot = false ;        // Si les labels sont de longueur différentes
            if(mememot == false) tmp = tmp->_next ;
        }
        if(tmp != NULL){                                                        // Si on a trouvé le label
            if(tmp != this){
                if(tmp->_previous != NULL) tmp->_previous->_next = tmp->_next ;
                if(tmp->_next != NULL) tmp->_next->_previous = tmp->_previous ;
            }else{                                                              // Si on supprime la première compétence, on recopie la seconde compétence et on suprime cette dernière
                this->modifLabel(_next->_label) ;
                this->delCompetence(_next->_label) ;
            }
        }
    }

    return ;
}