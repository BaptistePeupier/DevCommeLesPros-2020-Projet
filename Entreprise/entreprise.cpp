#include "entreprise.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Fonctions memrbes de la calsse Entreprise                                                                     //
//                                                                                                               //
// PEUPIER Baptiste MASSELOT Nicolas                                                                             //
// Cree le 06/04/2020, modifié le 18/04/2020                                                                     //
//                                                                                                               //
// Polytech Marseille, informatique 3A                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Les constructeurs
Entreprise::Entreprise(int index, const char* nom, const char* codePostal, const char* mail, Entreprise * next, Entreprise * previous)
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
    _next = next ;
    _previous = previous ;

    return ;
}

// Le destructeur
Entreprise::~Entreprise(void)
{
    Entreprise *ToDelE, *tmpE ;
    Poste *ToDelP, *tmpP ;
    Competence *ToDelC, *tmpC ;

    cout << "Destructeur Entreprise" << endl ;
    tmpE = this ;
    while(tmpE){
        ToDelE = tmpE ;
        tmpE = tmpE->next() ;
        tmpP = ToDelE->profilPoste() ;
        while(tmpP){
            ToDelP = tmpP ;
            tmpP = tmpP->next() ;
            tmpC = ToDelP->CompetencesRequises() ;
            while(tmpC){
                ToDelC = tmpC ;
                tmpC = tmpC->next() ;
                delete ToDelC ;
            }
            delete ToDelP ;
        }
        // delete ToDelE ;
    }

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

Poste * Entreprise::profilPoste(void)
{
    return _profilPoste ;
}


// Modifieurs
void Entreprise::modifIndex(int NewIndex)
{
    _index = NewIndex ;
    return ;
}

void Entreprise::modifNom(const char* NewNom)
{
    int i ;

    i = -1 ;
    do{                             // Si nom vide
        i++ ;                       // Pour mettre le '\0'
        _nom[i] = NewNom[i] ;
    }while (NewNom[i] != '\0') ;
    MAJDBEntreprise() ;

    return ;
}

void Entreprise::modifCodePostal(const char* NewCodePostal)
{
    int i ;

    i = -1 ;
    do{                             // Si code postal vide
        i++ ;                       // Pour mettre le '\0'
        _codePostal[i] = NewCodePostal[i] ;
    }while (NewCodePostal[i] != '\0') ;
    MAJDBEntreprise() ;

    return ;
}

void Entreprise::modifMail(const char * NewMail)
{
    int i ;

    i = -1 ;
    do{                             // Si mail vide
        i++ ;                       // Pour mettre le '\0'
        _mail[i] = NewMail[i] ;
    }while (NewMail[i] != '\0') ;
    MAJDBEntreprise() ;

    return ;
}

void Entreprise::modifNext(Entreprise * next)
{
    _next = next ;
    return ;
}

void Entreprise::modifPrevious(Entreprise * previous)
{
    _previous = previous ;
    return ;
}

// Modifie le pointeur vers la liste de postes à fournir
void Entreprise::modifProfilPoste(Poste * NewListePoste)
{
    _profilPoste = NewListePoste ;
}

// Fonctionnalités
// Ajoute une entreprise à la liste
void Entreprise::addEntreprise(const char* nom, const char* codePostal, const char* mail)
{
    Entreprise * tmp, *  NewE ;

    tmp = this ;
    while (tmp->next()) tmp = tmp->next() ;
    NewE = new Entreprise (tmp->index()+1, nom, codePostal, mail, NULL, tmp) ;
    tmp->modifNext(NewE) ;
    MAJDBEntreprise() ;

    return ;    
}

// Supprime le profile (l'entreprise) ainsi que les postes qui lui sont lié
void Entreprise::deleteProfile(void)
{
    return ;
}

// Met à jour la base de donnée des entreprises, est appelée à chaque fois que des données sont modifiées ou ajoutées
void Entreprise::MAJDBEntreprise(void)
{
    FILE *new_db = fopen("test/FichiersDeTests/entrepriseNew.csv", "w") ;   // A modifier lorsque l'on utilisera la vrai DB
    FILE *prev_db = fopen("test/FichiersDeTests/entreprise.csv", "r") ;     // A modifier lorsque l'on utilisera la vrai DB
    Entreprise * tmp ;
    char schema[128] ;

    tmp = this ;
    while (tmp && tmp->previous()) tmp = tmp->previous() ;          // Reviens au début de la liste des entreprises
    if(new_db && prev_db){
        // Ecriture du schéma de la table
        fscanf(prev_db, "%127[^\n\r]", schema) ;
        fprintf(new_db, "%s", schema) ;
        // Ecriture des tuples de donnes contenus dans la liste des entreprises
        while(tmp){
            fprintf(new_db, "\n%d,%s,%s,%s", tmp->index(), tmp->nom(), tmp->codePostal(), tmp->mail()) ;
            tmp = tmp->next() ;
        }
    }else{
        cout << "Erreur d'ouverture ou de création de la nouvelle db" << endl ;
    }
    fclose(new_db) ;
    fclose(prev_db) ;
    remove("test/FichiersDeTests/entreprise.csv") ;                                             // A modifier lorsque l'on utilisera la vrai DB
    rename("test/FichiersDeTests/entrepriseNew.csv", "test/FichiersDeTests/entreprise.csv") ;   // A modifier lorsque l'on utilisera la vrai DB

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

// Les constructeurs
Poste::Poste(const char* Titre, Poste *next, Poste * previous, Competence * CompetencesRequises)
{
    int i ;

    i = -1 ;
    do{                             // Si titre vide
        i++ ;                       // Pour mettre le '\0'
        _Titre[i] = Titre[i] ;
    }while (Titre[i] != '\0') ;
    _next = next ;
    _previous = previous ;
    _CompetencesRequises = CompetencesRequises ;
    return ;
}

// Le destructeur
// Détruit seulement le Poste "this"
Poste::~Poste(void)
{
    cout << "Destructeur Poste" << endl ;
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
void Poste::modifTitre(const char* NewTitre)
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

// Modifie le pointeur vers la liste de compétence
void Poste::modifCompetencesRequises(Competence * NewListeCompetence)
{
    _CompetencesRequises = NewListeCompetence ;
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

// Les constructeurs
Competence::Competence(const char* label, Competence * next, Competence * previous)
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
// Détruit seulement la compétence "this"
Competence::~Competence(void)
{
    cout << "Destructeur Competence" << endl ;   
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
void Competence::modifLabel(const char* NewLabel)
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
// Nécéssite une première compétence déjà définie (this)
void Competence::AddCompetence (const char* label)
{
    Competence * tmp ;
    tmp = this ;
    while(tmp->_next) tmp = tmp->_next ;
    tmp->_next = new Competence (label, NULL, tmp) ;        // Besoin d'allocation dynamique pour étendre la durée de vie des nouvelles compétences

    return ;
}

// Enlève une compétence dont le label est passé en paramètre
void Competence::delCompetence (const char* label)
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
