#include "entreprise.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Fonctions memrbes de la calsse Entreprise                                                                     //
//                                                                                                               //
// PEUPIER Baptiste MASSELOT Nicolas                                                                             //
// Cree le 06/04/2020, modifié le 12/05/2020                                                                     //
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
    cout << "Destructeur Entreprise" << endl ;
    if(_profilPoste) delete _profilPoste ;
    if(_next) delete _next ;
    _profilPoste = nullptr ;
    _next = _previous = nullptr ;

    return ;
}

// Modifieurs
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

// Met à jour la base de donnée des entreprises, est appelée à chaque fois que des données sont modifiées ou ajoutées
// Met également à jour la base de données des postes
void Entreprise::MAJDBEntreprise(void)
{
    FILE *new_db_en = fopen("test/FichiersDeTests/entrepriseNew.csv", "w") ;     // A modifier lorsque l'on utilisera la vrai DB
    FILE *prev_db_en = fopen("test/FichiersDeTests/entreprise.csv", "r") ;       // A modifier lorsque l'on utilisera la vrai DB
    FILE *new_db_poste = fopen("test/FichiersDeTests/posteNew.csv", "w") ;       // A modifier lorsque l'on utilisera la vrai DB
    FILE *prev_db_poste = fopen("test/FichiersDeTests/poste.csv", "r") ;         // A modifier lorsque l'on utilisera la vrai DB
    Entreprise * tmp ;
    Competence *tmpC ;
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
            fprintf(new_db_en, "\n%d,%s,%s,%s", tmp->index(), tmp->nom(), tmp->codePostal(), tmp->mail()) ;
            if(tmp->profilPoste()){
                tmpC = tmp->profilPoste()->CompetencesRequises() ;
                fprintf(new_db_poste, "\n%d,%s,%d,", indexPoste++, tmp->profilPoste()->Titre(), tmp->index()) ;
                // Ecriture des compétences du poste
                while(tmpC){
                    fprintf(new_db_poste, "%s", tmpC->label()) ;
                    if(tmpC->next()) fprintf(new_db_poste, ";") ;
                    tmpC = tmpC->next() ;
                }
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
    remove("test/FichiersDeTests/entreprise.csv") ;                                             // A modifier lorsque l'on utilisera la vrai DB
    rename("test/FichiersDeTests/entrepriseNew.csv", "test/FichiersDeTests/entreprise.csv") ;   // A modifier lorsque l'on utilisera la vrai DB
    remove("test/FichiersDeTests/poste.csv") ;                                                  // A modifier lorsque l'on utilisera la vrai DB
    rename("test/FichiersDeTests/posteNew.csv", "test/FichiersDeTests/poste.csv") ;             // A modifier lorsque l'on utilisera la vrai DB

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
    if (_CompetencesRequises) delete _CompetencesRequises ;
    if (_next) delete _next ;
    _CompetencesRequises = nullptr ;
    _next = _previous = nullptr ;

    return ;
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
// Détruit seulement la liste de compétence
Competence::~Competence(void)
{
    cout << "Destructeur Competence" << endl ;
    if(_next) delete _next ;
    _next = _previous = nullptr ;

    return ;
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

// Fonctionnalité sur les Competences
// Ajoute une compétence en fin de la liste des compétences
// Nécéssite une première compétence déjà définie (this)
void Competence::AddCompetence (const char* label)
{
    Competence * tmp ;
    tmp = this ;
    while(tmp->_next) tmp = tmp->_next ;
    tmp->_next = new Competence (label, NULL, tmp) ;    // Besoin d'allocation dynamique pour étendre la durée de vie des nouvelles compétences

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

