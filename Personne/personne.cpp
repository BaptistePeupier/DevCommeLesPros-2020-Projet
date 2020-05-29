#include "personne.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Fonctions memrbes de la classe Personne                                                                       //
//                                                                                                               //
// PEUPIER Baptiste                                                                                              //
// Cree le 06/04/2020, modifié le 16/05/2020                                                                     //
//                                                                                                               //
// Polytech Marseille, informatique 3A                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

string Personne::_DBEmp = "test/FichiersDeTests/employes.csv" ;
string Personne::_DBC = "test/FichiersDeTests/chercheurEmploi.csv" ;


// Le destructeur
// Détruit la liste de Personne
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

// Fonctionnalités
// Change un employé en chercheur d'emploi et inversement
// Ajoute les anciens collègues si besoin
// NewEntreprise est le pointeur vers l'entreprise en cas de recrutement, NULL sinon
void Personne::TransitionStatut(Personne ** ListeEmploye, Personne ** ListeChercheurEmploi, Entreprise * NewEntreprise)
{
    Personne *tmpP ;
    AncienCollegue *tmpA ;
    int tmpIndex ;
    bool inList ;

    if(_EntrepriseActuelle && !NewEntreprise){                          // Employe vers chercheur d'emploi
         // Ajout des anciens collègues s'il en sont pas déjà dans la liste
        tmpP = *ListeEmploye ;
        while (tmpP){
            if(tmpP->EntrepriseActuelle() == _EntrepriseActuelle){
                tmpA = ListAncienCollegues() ;
                inList = false ;
                while (tmpA && !inList){
                    if(tmpA->currentA() == tmpP) inList = true ;
                    tmpA = tmpA->nextA() ;
                }
                if(!inList && tmpP!=this){
                    if(ListAncienCollegues()){
                        ListAncienCollegues()->addAncienCollegue(tmpP, this) ;
                        if(tmpP->ListAncienCollegues()){
                            tmpP->ListAncienCollegues()->addAncienCollegue(this, tmpP) ;
                        }else{      // Si c'est le premier collègue de tmpP
                            tmpP->modifAncienCollegues(new AncienCollegue(this)) ;
                        }
                    }else{          // Si c'est le premier collègue de this
                        modifAncienCollegues(new AncienCollegue(tmpP)) ;
                        if(tmpP->ListAncienCollegues()){
                            tmpP->ListAncienCollegues()->addAncienCollegue(this, tmpP) ;
                        }else{      // Si c'est le premier collègue de tmpP
                            tmpP->modifAncienCollegues(new AncienCollegue(this)) ;
                        }
                    }
                }
            }
            tmpP = tmpP->nextP() ;
        }
        // Ajout de la personne à la liste de chercheur d'emploi
        _EntrepriseActuelle = NULL ;
        tmpP = *ListeChercheurEmploi ;
        if (tmpP) {
            while(tmpP->nextP()) tmpP = tmpP->nextP() ;
            _index = tmpP->index()+1 ;
            // Modification du chaînage
            if(*ListeEmploye == this && !_nextP && !_previousP){
                *ListeEmploye = NULL ;
            }else if(*ListeEmploye == this){
                *ListeEmploye = (*ListeEmploye)->nextP() ;
                (*ListeEmploye)->_previousP = NULL ;
            }else{
                if(_nextP) _nextP->modifPreviousP(_previousP) ;
                if(_previousP) _previousP->modifNextP(_nextP) ;

            }
            _nextP = NULL ;
            _previousP = tmpP ;
            tmpP->modifNextP(this) ;
        } else {
             // Modification du chaînage
            if (*ListeEmploye == this && !_nextP && !_previousP){
                *ListeEmploye = NULL ;
            } else if(*ListeEmploye == this){
                *ListeEmploye = (*ListeEmploye)->nextP() ;
                (*ListeEmploye)->_previousP = NULL ;
            }else{
                if(_nextP) _nextP->modifPreviousP(_previousP) ;
                if(_previousP) _previousP->modifNextP(_nextP) ;

            }
            *ListeChercheurEmploi = this ; //si la  liste des chercheurs d'emploi est vide 
            _nextP = NULL ;
            _previousP = NULL ;
            _index = 1 ;
        }
        // Modification des index
        tmpP = *ListeEmploye ;
        tmpIndex = 1 ;
        while(tmpP){
            tmpP->_index = tmpIndex++ ;
            tmpP = tmpP->nextP() ;
        }
        // Mise a jour des DB
        (*ListeEmploye)->MAJDBPersonne(true) ;
        (*ListeChercheurEmploi)->MAJDBPersonne(false) ;

    }else if(NewEntreprise && !_EntrepriseActuelle){                    // Chercheur d'emploi vers employe
        // Ajout de la personne à la liste d'employé
        _EntrepriseActuelle = NewEntreprise ;
        tmpP = *ListeEmploye ;
        if (tmpP) {
            while(tmpP->nextP()) tmpP = tmpP->nextP() ;
            _index = tmpP->index()+1 ;
            // Modification du chaînage
            if(*ListeChercheurEmploi == this && !_nextP && !_previousP){
                *ListeChercheurEmploi = NULL ;
            }else if(*ListeChercheurEmploi == this){
                *ListeChercheurEmploi = (*ListeChercheurEmploi)->nextP() ;
                (*ListeChercheurEmploi)->_previousP = NULL ;
            }else{
                if(_nextP) _nextP->modifPreviousP(_previousP) ;
                if(_previousP) _previousP->modifNextP(_nextP) ;

            }
            _nextP = NULL ;
            _previousP = tmpP ;
            tmpP->modifNextP(this) ;
        } else {
             // Modification du chaînage
            if (*ListeChercheurEmploi == this && !_nextP && !_previousP){
                *ListeChercheurEmploi = NULL ;
            } else if(*ListeChercheurEmploi == this){
                *ListeChercheurEmploi = (*ListeChercheurEmploi)->nextP() ;
                (*ListeChercheurEmploi)->_previousP = NULL ;
            }else{
                if(_nextP) _nextP->modifPreviousP(_previousP) ;
                if(_previousP) _previousP->modifNextP(_nextP) ;

            }
            *ListeEmploye = this ; //si la  liste des chercheurs d'emploi est vide 
            _nextP = NULL ;
            _previousP = NULL ;
            _index = 1 ;
        }
        // Modification des index
        tmpP = *ListeChercheurEmploi ;
        tmpIndex = 1 ;
        while(tmpP){
            tmpP->_index = tmpIndex++ ;
            tmpP = tmpP->nextP() ;
        }
        // Mise a jour des DB
        (*ListeEmploye)->MAJDBPersonne(true) ;   
        (*ListeChercheurEmploi)->MAJDBPersonne(false) ;
    }else cout << "Error" << endl ;

    return ;
}

void Personne::deleteProfile(Personne ** ListeEmploye, Personne ** ListeChercheurEmploi)
{
    //suppression de la personne des anciens collègues dans les 2 listes
    
    Personne * tmp_employe ;
    Personne * tmp_chercheur ;

    tmp_employe = *ListeEmploye;
    while (tmp_employe) {
        if (tmp_employe->ListAncienCollegues()) {
            tmp_employe->ListAncienCollegues()->dellAncienCollegue(this,tmp_employe) ;
        }
        tmp_employe = tmp_employe->nextP() ;
    }
    
    tmp_chercheur = *ListeChercheurEmploi ;
    while (tmp_chercheur) {
        if (tmp_chercheur->ListAncienCollegues()) {
            tmp_chercheur->ListAncienCollegues()->dellAncienCollegue(this,tmp_chercheur) ;
        }
        tmp_chercheur = tmp_chercheur->nextP() ;
    }
    
    //suppression de la personne dans la liste
    if (_previousP) {
        _previousP->_nextP = _nextP ;
    } else {
        if (_EntrepriseActuelle) {
            *ListeEmploye = _nextP ;
        } else {
            *ListeChercheurEmploi = _nextP ;         //mise à jour des pointeurs sur les liste au cas où on supprime la première personne de la liste
        }
    }
    if (_nextP) {
        _nextP->_previousP = _previousP ;
    }
    _previousP = NULL ;
    _nextP = NULL ;
    
    if (_EntrepriseActuelle) {
        tmp_employe = *ListeEmploye;
        tmp_employe->MAJDBPersonne(true) ;
    } else {
        tmp_chercheur = *ListeChercheurEmploi ;
        tmp_chercheur->MAJDBPersonne(false) ;
    }
    
    
    return ;
}

// Retourne une liste d'entreprise avec les postes correspondant aux compétences de la personne
// La liste est une liste d'entreprise ayant chacune à chaque fois un seul poste qui est un poste qui convient
// Si la liste de poste n'est pas que d'un seul poste, les autres sont ignorés
// On prend en paramètre le pointeur sur le début de la liste des entreprises
Entreprise* Personne::RecherchePosteCompetence(Entreprise * listeEntreprises)
{
    Poste *tmp_poste ;
    Entreprise *ListeToReturn = NULL, *tmpE ;
    Entreprise *tmp_entreprise = listeEntreprises ;
    Competence *tmp_skills_poste ;
    Competence *tmp_skills_personne = _CompetencesPropres ;
    int nbcompetences_poste = 0 ,  competences_dispo_pers = 0 ;
    
    while (tmp_entreprise) //parcours de la liste des entreprises 
    {
        tmp_poste = tmp_entreprise->profilPoste() ;
        while (tmp_poste) {
            tmp_skills_poste = tmp_poste->CompetencesRequises() ;   // On compte les compétences du poste
            while (tmp_skills_poste) {
                nbcompetences_poste++ ;
                tmp_skills_poste = tmp_skills_poste->next() ;
            }
            
            tmp_skills_poste = tmp_poste->CompetencesRequises() ; 
            while (tmp_skills_poste) {
                tmp_skills_personne = _CompetencesPropres ;         // On compare les compétences du poste avec celles de la personne
                while (tmp_skills_personne) {
                    if (tmp_skills_personne->label() == tmp_skills_poste->label()) {
                        competences_dispo_pers++ ;
                    }
                    tmp_skills_personne = tmp_skills_personne->next() ;
                }
                
                tmp_skills_poste = tmp_skills_poste->next() ;
            }
            
            if (competences_dispo_pers == nbcompetences_poste) {
                if(ListeToReturn){
                    tmpE->modifNext(new Entreprise(tmp_entreprise->index(), tmp_entreprise->nom(), tmp_entreprise->codePostal(), tmp_entreprise->mail(), NULL, tmpE)) ;
                    tmpE = tmpE->next() ;
                    tmpE->modifProfilPoste(tmp_poste) ;
                }else{
                    ListeToReturn = new Entreprise(tmp_entreprise->index(), tmp_entreprise->nom(), tmp_entreprise->codePostal(), tmp_entreprise->mail(), NULL, NULL) ;
                    ListeToReturn->modifProfilPoste(tmp_poste) ;
                    tmpE = ListeToReturn ;
                }
            }
            
            competences_dispo_pers = 0 ;
            nbcompetences_poste = 0 ;
            tmp_poste = tmp_poste->next() ;
        }
        tmp_entreprise = tmp_entreprise->next() ;
    }

    return ListeToReturn ;
}

// Renvoie une liste d'entreprise avec les postes correspondant aux compétences et au code postal de la personne
// La liste est une liste d'entreprise ayant chacune à chaque fois un seul poste qui est un poste qui convient
// Si la liste de poste n'est pas que d'un seul poste, les autres sont ignorés
Entreprise* Personne::RecherchePosteCompetenceCodePostal(Entreprise * listeEntreprises)
{
    Poste *tmp_poste ;
    Entreprise *ListeToReturn = NULL, *tmpE ;
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
                        if (tmp_skills_personne->label() == tmp_skills_poste->label()) {
                            competences_dispo_pers++ ;
                        }
                        tmp_skills_personne = tmp_skills_personne->next() ;
                    }
                    
                    tmp_skills_poste = tmp_skills_poste->next() ;
                }
                
                if (competences_dispo_pers == nbcompetences_poste) {
                    if(ListeToReturn){
                        tmpE->modifNext(new Entreprise(tmp_entreprise->index(), tmp_entreprise->nom(), tmp_entreprise->codePostal(), tmp_entreprise->mail(), NULL, tmpE)) ;
                        tmpE = tmpE->next() ;
                        tmpE->modifProfilPoste(tmp_poste) ;
                    }else{
                        ListeToReturn = new Entreprise(tmp_entreprise->index(), tmp_entreprise->nom(), tmp_entreprise->codePostal(), tmp_entreprise->mail(), NULL, NULL) ;
                        ListeToReturn->modifProfilPoste(tmp_poste) ;
                        tmpE = ListeToReturn ;
                    }
                }
                
                competences_dispo_pers = 0 ;
                nbcompetences_poste = 0 ;
                tmp_poste = tmp_poste->next() ;
            }
        }
        
        tmp_entreprise = tmp_entreprise->next() ;
    }

    return ListeToReturn ;
}

// Retourne une liste d'ancien collègue travaillant dans une entreprise donnée
AncienCollegue* Personne::RechercheColleguesEntreprise(const string nomEntreprise)
{
    AncienCollegue *ListeToReturn = NULL, *tmpA ;
    AncienCollegue * tmp, *tmp2 ;
    bool alreadyIn ;

    tmp = this->ListAncienCollegues() ;
    while (tmp) {
        if (tmp->currentA()->EntrepriseActuelle()) {
            if (tmp->currentA()->EntrepriseActuelle()->nom() == nomEntreprise) {
                tmp2 = ListeToReturn ;
                alreadyIn = false ;
                while (tmp2 && !alreadyIn){         // On vérife si la personne n'a pas déjà été trouvée
                    if(tmp2->currentA()->mail() == tmp->currentA()->mail()) alreadyIn = true ;
                    tmp2 = tmp2->nextA() ;
                }
                if(ListeToReturn and !alreadyIn){
                    tmpA->modifNextA(new AncienCollegue(tmp->currentA(), NULL, tmpA)) ;
                    tmpA = tmpA->nextA() ;
                }else if (!alreadyIn){
                    ListeToReturn = new AncienCollegue(tmp->currentA(), NULL, NULL) ;
                    tmpA = ListeToReturn ;
                }
            }
        }
        tmp = tmp->nextA() ;
    }

    return ListeToReturn ;
}
// Met à jour la base de donnée des checheurs d'emplois ou des entreprises, est appelée à chaque fois que des données sont modifiées
// Si le pointeur vers une entrepise est null c'est un Chercheur d'emploi
// Si le pointeur vers une entrepise est non null c'est un Employe
void Personne::MAJDBPersonne(bool employe , string DBE, string DBC)
{
    Personne * tmp;
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
    if (tmp){
        while (tmp->_previousP != NULL) tmp = tmp->previousP() ;                    //retour au début de la liste des personnes
    }
    if (employe) {                                                               //ouverture du csv chercheurEmploi ou employes selon la liste où se trouve la personne
        new_db_employes = fopen("employes_new.csv", "w") ;
        prev_db_employes = fopen(DBE.c_str(), "r") ;
        fscanf(prev_db_employes, "%127[^\n\r]", schema_db) ;                         //on recopie le schema de la base de données 
        fprintf(new_db_employes, "%s", schema_db) ;
    }else {
        new_db_chercheurs = fopen("chercheurEmploi_new.csv", "w") ; 
        prev_db_chercheurs = fopen(DBC.c_str(), "r") ;
        
        fscanf(prev_db_chercheurs, "%127[^\n\r]", schema_db) ;                       //on recopie le schema de la base de données 
        fprintf(new_db_chercheurs, "%s", schema_db) ;
    }
    
    if (tmp)
    {
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
                    
                    
                }
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
                }

                        
                if (tmp->EntrepriseActuelle()) {
                    fprintf(new_db_employes, "\n%d,%s,%s,%s,%s,%d,%s,%s", tmp->index(), tmp->nom().c_str(), tmp->prenom().c_str(), tmp->mail().c_str(),tmp->codePostal().c_str(),tmp->EntrepriseActuelle()->index(),skills_to_write.c_str(),collegues_to_write.c_str()) ; //il faut convertir la string en char* avec c_str pour utiliser fprintf
                    skills_to_write.clear() ;       //on réinitialise les string avant de passer à la personne suivante
                    collegues_to_write.clear() ;
                    tmp = tmp->_nextP ;
                } else {
                    fprintf(new_db_chercheurs, "\n%d,%s,%s,%s,%s,%s,%s", tmp->index(), tmp->nom().c_str(), tmp->prenom().c_str(), tmp->mail().c_str(),tmp->codePostal().c_str(),skills_to_write.c_str(),collegues_to_write.c_str()) ; //il faut convertir la string en char* avec c_str pour utiliser fprintf
                    skills_to_write.clear() ;       //on réinitialise les string avant de passer à la personne suivante
                    collegues_to_write.clear() ;
                    tmp = tmp->_nextP ;
                }   
            }
        }else{
            cout << "Erreur d'ouverture ou de création de la nouvelle db" << endl ;
        }
    }

    if (employe) {
        fclose(new_db_employes);
        fclose(prev_db_employes) ;
        remove(DBE.c_str()) ;
        rename("employes_new.csv", DBE.c_str()) ;
    } else {
        fclose(new_db_chercheurs) ;
        fclose(prev_db_chercheurs) ;
        remove(DBC.c_str()) ;
        rename("chercheurEmploi_new.csv", DBC.c_str()) ;
    }
    
    return ;
}
// Retourne une liste des anciens collègues employés dans les entreprises qui recherchent ces compétences
// Seulement pour les chercheurs d'emploi
AncienCollegue* Personne::ChercheurRechercheColleguesCompetence(Competence * ListeCompetence)
{
    assert(!(this->_EntrepriseActuelle)) ;
    Competence * tmp_comp , *tmp_comp_entreprise;
    AncienCollegue *ListeToReturn = NULL, *tmpA ;
    AncienCollegue * tmp_collegue ;
    AncienCollegue *tmp2 ;
    Poste * tmp_poste ;
    string label_skill_liste ;
    bool displayed, alreadyIn ;

    tmp_comp = ListeCompetence ;
    tmp_collegue = _ListAncienCollegues ;                                       // Initialisation des pointeurs
    while (tmp_comp) {
        label_skill_liste = tmp_comp->label() ;                                 // Recherche dans la liste des compétence fournie
        while (tmp_collegue) {
            displayed = false ;
            if (tmp_collegue->currentA()->EntrepriseActuelle()) {               // Recherche dans la liste des anciens collègues seulement sur ceux qui sont employés
                tmp_poste = tmp_collegue->currentA()->EntrepriseActuelle()->profilPoste() ;
                while (tmp_poste) {
                    tmp_comp_entreprise = tmp_poste->CompetencesRequises() ;    // Parcours des compétences requises pour un poste
                    while (tmp_comp_entreprise) {
                        if (tmp_comp_entreprise->label() == label_skill_liste && !displayed) {
                            tmp2 = ListeToReturn ;
                            alreadyIn = false ;
                            while (tmp2 && !alreadyIn){         // On vérife si la personne n'a pas déjà été trouvée
                                if(tmp2->currentA()->mail() == tmp_collegue->currentA()->mail()) alreadyIn = true ;
                                tmp2 = tmp2->nextA() ;
                            }
                            if(ListeToReturn && !alreadyIn){
                                tmpA->modifNextA(new AncienCollegue(tmp_collegue->currentA(), NULL, tmpA)) ;
                                tmpA = tmpA->nextA() ;
                            }else if (!alreadyIn){
                                ListeToReturn = new AncienCollegue(tmp_collegue->currentA(), NULL, NULL) ;
                                tmpA = ListeToReturn ;
                            }
                            displayed = true ;                                  // On évite d'afficher plusieurs fois le même collègue si il y a plusieurs postes recherchant la compétence
                        }
                        tmp_comp_entreprise = tmp_comp_entreprise->next() ;
                    }
                    tmp_poste = tmp_poste->next() ;
                }   
            }
            tmp_collegue = tmp_collegue->nextA() ;
        }
        tmp_collegue = _ListAncienCollegues ; // Quand on a recherché pour une compétence on réinitialise le pointeur vers les anciens collègues
        tmp_comp = tmp_comp->next() ;
    }
    
    return ListeToReturn ;
}

// Retourne une liste des anciens collègues disposant des compétences passé en liste
// Seulement pour les employés
AncienCollegue* Personne::EmployeRechercheColleguesCompetence(Competence * ListeCompetence)
{
    assert(this->_EntrepriseActuelle) ;
    AncienCollegue *ListeToReturn = NULL, *tmpA, *tmp2 ;
    AncienCollegue * tmp_collegue = _ListAncienCollegues;
    Competence * tmp_comp_collegue , *tmp_comp = ListeCompetence;           //initialisation des pointeurs
    string label_skill_collegue , entreprise_pers , entreprise_collegue;
    int nb_skill_liste = 0 ,  nb_skill_match;
    bool alreadyIn ;

    entreprise_pers = _EntrepriseActuelle->nom() ;

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
                        if (label_skill_collegue == tmp_comp->label()) {
                            nb_skill_match++ ;
                        }
                        tmp_comp = tmp_comp->next() ;
                    }
                    tmp_comp_collegue = tmp_comp_collegue->next() ; 
                }

                if (nb_skill_liste == nb_skill_match) {
                    tmp2 = ListeToReturn ;
                    alreadyIn = false ;
                    while (tmp2 && !alreadyIn){         // On vérife si la personne n'a pas déjà été trouvée
                        if(tmp2->currentA()->mail() == tmp_collegue->currentA()->mail()) alreadyIn = true ;
                        tmp2 = tmp2->nextA() ;
                    }
                    if(ListeToReturn && !alreadyIn){
                        tmpA->modifNextA(new AncienCollegue(tmp_collegue->currentA(), NULL, tmpA)) ;
                        tmpA = tmpA->nextA() ;
                    }else if(!alreadyIn){
                        ListeToReturn = new AncienCollegue(tmp_collegue->currentA(), NULL, NULL) ;
                        tmpA = ListeToReturn ;
                    }
                }
            }
        }
        tmp_collegue = tmp_collegue->nextA() ;
    }

    return ListeToReturn ;
}
                                                                            
// Rechercher parmis les chercheurs par competences, affiche les résultats
Personne* Personne::ChercheurCompetence (Competence * listeComp)
{
    Competence * tmp_comp = listeComp , *tmp_comp_pers;
    Personne * tmp_pers = this, *tmp2 ;
    Personne *ListeToReturn = NULL, *tmpP ;
    string label_skill_pers, label_skill_liste ;
    int nb_skill_match , nb_skill_liste = 0;
    bool alreadyIn ;

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
            tmp2 = ListeToReturn ;
            alreadyIn = false ;
            while (tmp2 && !alreadyIn){         // On vérife si la personne n'a pas déjà été trouvée
                if(tmp2->mail() == tmp_pers->mail()) alreadyIn = true ;
                tmp2 = tmp2->nextP() ;
            }
            if(ListeToReturn && !alreadyIn){
                tmpP->modifNextP(new Personne(tmp_pers->index(), tmp_pers->nom(), tmp_pers->prenom(), tmp_pers->mail(), tmp_pers->codePostal(), NULL, tmpP, NULL, NULL, tmp_pers->EntrepriseActuelle())) ;
                tmpP = tmpP->nextP() ;
            }else if (!alreadyIn){
                ListeToReturn = new Personne(tmp_pers->index(), tmp_pers->nom(), tmp_pers->prenom(), tmp_pers->mail(), tmp_pers->codePostal(), NULL, NULL, NULL, NULL, tmp_pers->EntrepriseActuelle()) ;
                tmpP = ListeToReturn ;
            }
        }
        
        tmp_pers = tmp_pers->nextP() ;
    }
    return ListeToReturn ;
}

// Rechercher parmis les chercheurs par competences et code postal, affiche les résultats
Personne* Personne::ChercheurCompetenceCodePostal (Competence * listeComp ,const string CodePostalRecherche)
{
    Competence * tmp_comp = listeComp , *tmp_comp_pers;
    Personne *ListeToReturn = NULL, *tmpP, *tmp2 ;
    Personne * tmp_pers = this ;
    string label_skill_pers, label_skill_liste , cp_recherche = CodePostalRecherche, cp_pers ;
    int nb_skill_match , nb_skill_liste = 0;
    bool alreadyIn ;
    
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
                tmp2 = ListeToReturn ;
                alreadyIn = false ;
                while (tmp2 && !alreadyIn){         // On vérife si la personne n'a pas déjà été trouvée
                    if(tmp2->mail() == tmp_pers->mail()) alreadyIn = true ;
                    tmp2 = tmp2->nextP() ;
                }
                if(ListeToReturn){
                    tmpP->modifNextP(new Personne(tmp_pers->index(), tmp_pers->nom(), tmp_pers->prenom(), tmp_pers->mail(), tmp_pers->codePostal(), NULL, tmpP, NULL, NULL, tmp_pers->EntrepriseActuelle())) ;
                    tmpP = tmpP->nextP() ;
                }else{
                    ListeToReturn = new Personne(tmp_pers->index(), tmp_pers->nom(), tmp_pers->prenom(), tmp_pers->mail(), tmp_pers->codePostal(), NULL, NULL, NULL, NULL, tmp_pers->EntrepriseActuelle()) ;
                    tmpP = ListeToReturn ;
                }
            }
        }
        tmp_pers = tmp_pers->nextP() ;
    }
    return ListeToReturn ;
}


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

// Le destructeur
AncienCollegue::~AncienCollegue(void)
{
    cout << "Destructeur AncienCollegue" << endl ;
    if(_nextA) delete _nextA ;
    _nextA = _previousA = nullptr ;
    _currentA = nullptr ;

    return ;
}

// Fonctionnalités
// Ajoute une personne à la liste
void AncienCollegue::addAncienCollegue(Personne * NewAncienCollegue,Personne * base_pers)
{
    AncienCollegue * tmp_collegue = this ;
    while (tmp_collegue->nextA()) tmp_collegue = tmp_collegue->nextA() ;                //parcours jusqu'à la fin de la liste
    tmp_collegue->modifNextA(new AncienCollegue(NewAncienCollegue,NULL,tmp_collegue)) ; //ajout du nouveau collègue

    if (base_pers->EntrepriseActuelle()) {
        base_pers->MAJDBPersonne(true) ;                                                        //mise à jour de la base de données à partir de la personne qui a la liste d'anciens collègues 
                                                                                        //pour éviter de mettre à jour le mauvais csv 
                                                                                        //on passe en paramètre l'addresse de celle-ci pour éviter de faire des parcours de liste
    } else {
        base_pers->MAJDBPersonne(false) ;
    }
    return ;
}

// Retire une personne de la liste
void AncienCollegue::dellAncienCollegue(Personne * AncienCollegueToDell,Personne *base_pers)
{
    AncienCollegue * tmp_collegue ;
    AncienCollegue * collegue_to_delete = NULL ;
    Personne * tmp_pers ; 

    tmp_collegue = this ;
    while (tmp_collegue) {
        if (tmp_collegue->currentA() == AncienCollegueToDell) {         //recherche en avant dans la liste 
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
            if(collegue_to_delete->_previousA != NULL) {
                collegue_to_delete->_previousA->_nextA = collegue_to_delete->_nextA ;
            } else {
                base_pers->modifAncienCollegues(collegue_to_delete->nextA()) ;                //on change le pointeur vers la liste des anciens collègues si on supprime un collègue en début de liste
            }
            ;
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
    
    if (base_pers->EntrepriseActuelle() ) {
        base_pers->MAJDBPersonne(true) ; //mise à jour de la base de données à partir de la personne qui a la liste d'anciens collègues 
                                        //pour éviter de mettre à jour le mauvais csv 
                                        //on passe en paramètre l'addresse de celle-ci pour éviter de faire des parcours de liste
    }else {
        base_pers->MAJDBPersonne(false) ;
    }
    return ;
}

