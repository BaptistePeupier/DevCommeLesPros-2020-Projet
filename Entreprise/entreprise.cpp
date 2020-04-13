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
    int i ;

    i = -1 ;
    do{                             // Si nom vide
        i++ ;                       // Pour mettre le '\0'
        _nom[i] = nom[i] ;
    }while (nom[i] != '\0') ;

    i = -1 ;
    do{                             // Si code postal vide
        i++ ;                       // Pour mettre le '\0'
        _codePostal[i] = codePostal[i] ;
    }while (codePostal[i] != '\0') ;

    i = -1 ;
    do{                             // Si mail vide
        i++ ;                       // Pour mettre le '\0'
        _mail[i] = mail[i] ;
    }while (mail[i] != '\0') ;

    _index = index ;
    _next = &next ;
    _previous = &previous ;

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
    return _index ;
}

char* Entreprise::nom(void)
{
    return _nom ;
}

char* Entreprise::codePostal(void)
{
    return _codePostal;
}

char* Entreprise::mail(void)
{
    return _mail ;
}

Entreprise * Entreprise::next(void)
{
    return _next ;
}

Entreprise * Entreprise::previous(void)
{
    return _previous;
}

// Modifieurs
void Entreprise::modifIndex(int NewIndex)
{
    _index = NewIndex ;
    return ;
}

void Entreprise::modifNom(char* NewNom)
{
    int i ;

    i = -1 ;
    do{                             // Si nom vide
        i++ ;                       // Pour mettre le '\0'
        _nom[i] = NewNom[i] ;
    }while (NewNom[i] != '\0') ;

    return ;
}

void Entreprise::modifCodePostal(char* NewCodePostal)
{
    int i ;

    i = -1 ;
    do{                             // Si code postal vide
        i++ ;                       // Pour mettre le '\0'
        _codePostal[i] = NewCodePostal[i] ;
    }while (NewCodePostal[i] != '\0') ;

    return ;
}

void Entreprise::modifMail(char * NewMail)
{
    int i ;

    i = -1 ;
    do{                             // Si mail vide
        i++ ;                       // Pour mettre le '\0'
        _mail[i] = NewMail[i] ;
    }while (NewMail[i] != '\0') ;
    return ;
}

void Entreprise::modifNext(Entreprise & next)
{
    _next = &next ;
    return ;
}

void Entreprise::modifPrevious(Entreprise & previous)
{
    _previous = &previous ;
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

// Met à jour la base de donnée des entreprises, est appelée à chaque fois que des données sont modifiées
void Entreprise::MAJDBEntreprise(Entreprise * MAJ)
{
    return ;
}

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
    int i ;

    i = -1 ;
    do{                             // Si titre vide
        i++ ;                       // Pour mettre le '\0'
        _Titre[i] = Titre[i] ;
    }while (Titre[i] != '\0') ;
    _next = &next ;
    _previous = &previous ;
    _CompetencesRequises = &CompetencesRequises ;
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
    return _Titre ;
}

Poste * Poste::next(void)
{
    return _next ;
}

Poste * Poste::previous(void)
{
    return _previous ;
}

Competence * Poste::CompetencesRequises(void)
{
    return _CompetencesRequises ;
}

// Modifieurs
void Poste::modifTitre(char* NewTitre)
{
    int i ;

    i = -1 ;
    do{                             // Si titre vide
        i++ ;                       // Pour mettre le '\0'
        _Titre[i] = NewTitre[i] ;
    }while (NewTitre[i] != '\0') ;

    return ;
}

void Poste::modifNext(Poste* NewNext)
{
    _next = NewNext ;
    return ;
}

void Poste::modifPrevious(Poste* NewPrevious)
{
    _previous = NewPrevious ;
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
    Competence * tmp, *toDel ;

    cout << "destructeur Competence" << endl ;
    tmp = this->_next ;
    while (tmp){
        toDel = tmp ;
        tmp = tmp->_next ;
        delete toDel ;
        cout << "destructeur Competence" << endl ;
    }

    return ;
}

// Accesseurs
char* Competence::label(void)
{
    return _label ;
}

Competence * Competence::next(void)
{
    return _next ;
}

Competence * Competence::previous(void)
{
    return _next ;
}

// Modifieurs
void Competence::modifLabel(char* NewLabel)
{
    int i ;

    i = -1 ;
    do{                             // Si label vide
        i++ ;                       // Pour mettre le '\0'
        _label[i] = NewLabel[i] ;
    }while (NewLabel[i] != '\0') ;

    return ;
}

void Competence::modifNext(Competence* NewNext)
{
    _next = NewNext ;
    return ;
}

void Competence::modifPrevious(Competence* NewPrevious)
{
    _previous = NewPrevious ;
    return ;
}

// Fonctionnalité sur les Competences
// Ajoute une compétence en fin de la liste des compétences
void Competence::AddCompetence (char* label)
{
    Competence * tmp ;
    tmp = this ;
    while(tmp->_next != NULL) tmp = tmp->_next ;
    tmp->_next = new Competence (label, NULL, tmp) ;        // Besoin d'allocation dynamique pour étendre la durée de vie des nouvelles compétences

    return ;
}

// Enlève une compétence dont le label est passé en paramètre
void Competence::delCompetence (char* label)
{
    Competence * tmp ;
    char * tmpLabel ;
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
