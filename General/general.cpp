///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Fonctions générales entre les classes Entreprise et Personne.                                                 //
//                                                                                                               //
// PEUPIER Baptiste MASSELOT Nicolas                                                                             //
// Cree le 08/04/2020, modifié le 21/04/2020                                                                     //
//                                                                                                               //
// Polytech Marseille, informatique 3A                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "general.h"

// Construit la liste des Entreprises à partir d'une base de donnée (entreprise + postes)
Entreprise * CreerListeEntreprise(string DBEnt, string DBP)
{
    Entreprise * ListeEntreprise = NULL, * tmp = NULL ;
    int tmpindex ;
    int tmpentreprise ;
    char tmpnom[128] ;
    char tmpcodePostal[128] ;
    char tmpmail[128] ;
    char tmpcompetence[128] ;

    // Lecture de la base de donnée des entreprises
    FILE *db_entreprise = fopen(DBEnt.c_str(), "r") ;
    if(db_entreprise){
        fscanf(db_entreprise, "%*s") ;
        // id,nom,code_postal,mail -> entreprise
        while(fscanf(db_entreprise, "%d,%127[^,],%127[^,],%127[^\n\r]", &tmpindex, tmpnom, tmpcodePostal, tmpmail) == 4)
        {
            Entreprise * NewEntreprise = new Entreprise (tmpindex, tmpnom, tmpcodePostal, tmpmail, NULL, NULL) ;
            if(tmp == NULL){                                 // Première entreprise
                ListeEntreprise = NewEntreprise ;
                tmp = ListeEntreprise ;
            }else{
                NewEntreprise->modifPrevious(tmp) ;
                tmp->modifNext(NewEntreprise) ;
                tmp = NewEntreprise ;
            }
        }
        fclose(db_entreprise) ;
    }else{
        cout << "Erreur d'ouverture de la base de donnée des entreprises" << endl ;
    }

    // Lecture de la base de donnée des postes
    FILE *db_poste = fopen(DBP.c_str(), "r") ;
    if(db_poste){
        fscanf(db_poste, "%*s") ;
        // id,titre,entreprise,competences(multiples) -> poste
        while (fscanf(db_poste, "%d,%127[^,],%d,", &tmpindex,tmpnom,&tmpentreprise) == 3)
        {
            Poste * NewPoste = new Poste (tmpnom, NULL, NULL, NULL) ;
            while (fscanf(db_poste, "%127[^;\n];", tmpcompetence) == 1)         // Lecture des compétences demandées
            {
                if(NewPoste->CompetencesRequises()){
                    NewPoste->CompetencesRequises()->AddCompetence(tmpcompetence) ;
                }else{                                                          // La première compétence
                    NewPoste->modifCompetencesRequises(new Competence (tmpcompetence, NULL, NULL)) ;
                }
            }
            tmp = ListeEntreprise ;
            while (tmp && tmpentreprise!=tmp->index()) tmp = tmp->next() ;      // Association à l'entreprise
            if (tmp->profilPoste()){
                tmp->addPoste(NewPoste) ;
            }else{                                                              // Premier poste à pourvoir
                tmp->modifProfilPoste(NewPoste) ;
            }
        }
        fclose(db_poste) ;
    }else{
        cout << "Erreur d'ouverture de la base de donnée des postes" << endl ;
    }

    return ListeEntreprise ;
}

// Construit la liste des Employe à partir d'une base de donnée (employe)
Personne * CreerListeEmploye(Entreprise * ListeEntreprise, string DBEmp)
{
    Personne * ListeEmploye = NULL, * tmp = NULL ;
    Entreprise * tmpentreprise ;
    int tmpindex ;
    int tmpindexentreprise ;
    char tmpnom[128] ;
    char tmpprenom[128] ;
    char tmpmail[128] ;
    char tmpcodePostal[128] ;
    char tmpcompetence[128] ;

    FILE *db_employe = fopen(DBEmp.c_str(), "r") ;
    if(db_employe && ListeEntreprise){                      // On a besoin de la liste des entreprises
        fscanf(db_employe, "%*s") ;
        // id,nom,prenom,mail,code_postal,entreprise,competences,collegues_employes,collegues_chercheur_d'emploi
        while(fscanf(db_employe, "%d,%127[^,],%127[^,],%127[^,],%127[^,],%d,", &tmpindex,tmpnom,tmpprenom,tmpmail,tmpcodePostal,&tmpindexentreprise) == 6)
        {
            tmpentreprise = ListeEntreprise ;
            while (tmpentreprise && tmpentreprise->index()!=tmpindexentreprise) tmpentreprise = tmpentreprise->next() ;
            Personne * NewEmploye = new Personne (tmpindex,tmpnom,tmpprenom,tmpmail,tmpcodePostal,NULL,NULL,NULL,NULL,tmpentreprise) ;

            // Lecture des compétences
            while(fscanf(db_employe, "%127[^;,];", tmpcompetence) == 1){
                if(NewEmploye->CompetencePropres()){
                    NewEmploye->CompetencePropres()->AddCompetence(tmpcompetence) ;
                }else{                      // Première compétence
                    NewEmploye->modifCompetencePropres(new Competence (tmpcompetence, NULL, NULL)) ;
                }
            }
            fscanf(db_employe, "%*s") ;     // On va à la ligne

            // Chainage
            if(ListeEmploye){
                NewEmploye->modifPreviousP(tmp) ;
                tmp->modifNextP(NewEmploye) ;
                tmp = NewEmploye ;
            }else{                          // Premier Employe
                ListeEmploye = NewEmploye ;
                tmp = ListeEmploye ;
            }
        }
        fclose(db_employe) ;
    }else cout << "Erreur d'ouverture de la base de donnée employe" << endl ;

    return ListeEmploye ;
}

// Construit la liste des Chercheurs d'emploi à partir d'une base de donnée (chercheurEmplois)
Personne * CreerListeChercheurEmploi(string DBC)
{
    Personne * ListeChercheurEmploi = NULL, * tmp = NULL ;
    int tmpindex ;
    char tmpnom[128] ;
    char tmpprenom[128] ;
    char tmpmail[128] ;
    char tmpcodePostal[128] ;
    char tmpcompetence[128] ;

    FILE *db_chercheur_emploi = fopen(DBC.c_str(), "r") ;
    if(db_chercheur_emploi){
        fscanf(db_chercheur_emploi, "%*s") ;
        // id,nom,prenom,mail,code_postal,competences,collegues_employes,collegues_chercheur_d'emploi
        while(fscanf(db_chercheur_emploi, "%d,%127[^,],%127[^,],%127[^,],%127[^,],", &tmpindex,tmpnom,tmpprenom,tmpmail,tmpcodePostal) == 5)
        {
            Personne * NewEmploye = new Personne (tmpindex,tmpnom,tmpprenom,tmpmail,tmpcodePostal,NULL,NULL,NULL,NULL,NULL) ;

            // Lecture des compétences
            while(fscanf(db_chercheur_emploi, "%127[^;,];", tmpcompetence) == 1){
                if(NewEmploye->CompetencePropres()){
                    NewEmploye->CompetencePropres()->AddCompetence(tmpcompetence) ;
                }else{                              // Première compétence
                    NewEmploye->modifCompetencePropres(new Competence (tmpcompetence, NULL, NULL)) ;
                }
            }
            fscanf(db_chercheur_emploi, "%*s") ;     // On va à la ligne

            // Chainage
            if(ListeChercheurEmploi){
                NewEmploye->modifPreviousP(tmp) ;
                tmp->modifNextP(NewEmploye) ;
                tmp = NewEmploye ;
            }else{                                  // Premier Employe
                ListeChercheurEmploi = NewEmploye ;
                tmp = ListeChercheurEmploi ;
            }
        }
        fclose(db_chercheur_emploi) ;
    }else cout << "Erreur d'ouverture de la base de donnée des chercheur d'emploi" << endl ;

    return ListeChercheurEmploi ;
}

// Effectue la lisaison entre la liste des Employes et chercheur d'emploi
void InitAnciensCollegues(Personne * ListeEmploye, Personne * ListeChercheurEmploi, string DBEmp, string DBC)
{
    Personne * tmp, * tmp2 ;
    AncienCollegue * tmpA ;
    char tmpIndexCollegue[128] ;
    int indexCollegue ;
    FILE *db_employe = fopen(DBEmp.c_str(), "r") ;
    FILE *db_chercheur_emploi = fopen(DBC.c_str(), "r") ;

    if(db_employe && db_chercheur_emploi){
        fscanf(db_employe, "%*s") ;
        // id,nom,prenom,mail,code_postal,entreprise,competences,collegues_employes,collegues_chercheur_d'emploi
        tmp = ListeEmploye ;
        while(tmp){
            fscanf(db_employe, "%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,]") ;
            fscanf(db_employe, ",") ;
            // Recherche des collegues employes
            while(fscanf(db_employe, "%127[^;,];", tmpIndexCollegue) == 1){
                indexCollegue = atoi(tmpIndexCollegue) ;
                tmp2 = ListeEmploye ;
                while(tmp2 && tmp2->index()!=indexCollegue) tmp2 = tmp2->nextP() ;  // On retrouve la personne d'index recherché
                if(tmp2){
                    AncienCollegue * NewAncienCollegue = new AncienCollegue(tmp2,NULL,NULL) ;
                    tmp2 = tmp ;
                    if(tmp2->ListAncienCollegues()){
                        tmpA = tmp2->ListAncienCollegues() ;
                        while(tmpA->nextA()) tmpA = tmpA->nextA() ;
                        NewAncienCollegue->modifPreviousA(tmpA) ;
                        tmpA->modifNextA(NewAncienCollegue) ;
                    }else{                                                              // Premier collegue
                        tmp2->modifAncienCollegues(NewAncienCollegue) ;
                    }
                }
            }
            fscanf(db_employe, "%1[,]", tmpIndexCollegue) ;
            // Recherche des collegues chercheurs d'emploi
            while(fscanf(db_employe, "%127[^;\n];", tmpIndexCollegue) == 1){
                indexCollegue = atoi(tmpIndexCollegue) ;
                tmp2 = ListeChercheurEmploi ;
                while(tmp2 && tmp2->index()!=indexCollegue) tmp2 = tmp2->nextP() ;  // On retrouve la personne d'index recherché
                if(tmp2){
                    AncienCollegue * NewAncienCollegue = new AncienCollegue(tmp2,NULL,NULL) ;
                    tmp2 = tmp ;
                    if(tmp2->ListAncienCollegues()){
                        tmpA = tmp2->ListAncienCollegues() ;
                        while(tmpA->nextA()) tmpA = tmpA->nextA() ;
                        NewAncienCollegue->modifPreviousA(tmpA) ;
                        tmpA->modifNextA(NewAncienCollegue) ;
                    }else{                                                              // Premier collegue
                        tmp2->modifAncienCollegues(NewAncienCollegue) ;
                    }
                }
            }
            tmp = tmp->nextP() ;
        }

        fscanf(db_chercheur_emploi, "%*s") ;
        // id,nom,prenom,mail,code_postal,competences,collegues_employes,collegues_chercheur_d'emploi
        tmp = ListeChercheurEmploi ;
        while(tmp){
            fscanf(db_chercheur_emploi, "%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,]") ;
            fscanf(db_chercheur_emploi, ",") ;
            // Recherche des collegues employes
            while(fscanf(db_chercheur_emploi, "%127[^;,];", tmpIndexCollegue) == 1){
                indexCollegue = atoi(tmpIndexCollegue) ;
                tmp2 = ListeEmploye ;
                while(tmp2 && tmp2->index()!=indexCollegue) tmp2 = tmp2->nextP() ;  // On retrouve la personne d'index recherché
                if(tmp2){
                    AncienCollegue * NewAncienCollegue = new AncienCollegue(tmp2,NULL,NULL) ;
                    tmp2 = tmp ;
                    if(tmp2->ListAncienCollegues()){
                        tmpA = tmp2->ListAncienCollegues() ;
                        while(tmpA->nextA()) tmpA = tmpA->nextA() ;
                        NewAncienCollegue->modifPreviousA(tmpA) ;
                        tmpA->modifNextA(NewAncienCollegue) ;
                    }else{                                                              // Premier collegue
                        tmp2->modifAncienCollegues(NewAncienCollegue) ;
                    }
                }
            }
            fscanf(db_chercheur_emploi, "%1[,]", tmpIndexCollegue) ;
            // Recherche des collegues chercheurs d'emploi
            while(fscanf(db_chercheur_emploi, "%127[^;\n];", tmpIndexCollegue) == 1){
                indexCollegue = atoi(tmpIndexCollegue) ;
                tmp2 = ListeChercheurEmploi ;
                while(tmp2 && tmp2->index()!=indexCollegue) tmp2 = tmp2->nextP() ;  // On retrouve la personne d'index recherché
                if(tmp2){
                    AncienCollegue * NewAncienCollegue = new AncienCollegue(tmp2,NULL,NULL) ;
                    tmp2 = tmp ;
                    if(tmp2->ListAncienCollegues()){
                        tmpA = tmp2->ListAncienCollegues() ;
                        while(tmpA->nextA()) tmpA = tmpA->nextA() ;
                        NewAncienCollegue->modifPreviousA(tmpA) ;
                        tmpA->modifNextA(NewAncienCollegue) ;
                    }else{                                                              // Premier collegue
                        tmp2->modifAncienCollegues(NewAncienCollegue) ;
                    }
                }
            }
            tmp = tmp->nextP() ;
        }

        fclose(db_employe) ;
        fclose(db_chercheur_emploi) ;
    }else cout << "Erreur d'ouverture de la base de donnée employe ou chercheur d'emploi" << endl ;

    return ;
}

// Fonction auxiliaire aux fonctions CreerListeEntreprise, CreerListeEmploye, CreerListeChercheurEmploi, InitAnciensCollegues
// Créer les listes et fait les liens avec les entreprises et ancien collègues
void Creer_listes(Entreprise ** ListeEntreprise, Personne ** ListeEmploye, Personne ** ListeChercheurEmploi, string DBEnt, string DBP, string DBEmp, string DBC)
{
    (*ListeEntreprise)->modifDBEnt(DBEnt) ;
    (*ListeEntreprise)->modifDBP(DBP) ;
    (*ListeEmploye)->modifDBEmp(DBEmp) ;
    (*ListeEmploye)->modifDBC(DBC) ;
    *ListeEntreprise = CreerListeEntreprise(DBEnt, DBP) ;
    *ListeEmploye = CreerListeEmploye(*ListeEntreprise, DBEmp) ;
    *ListeChercheurEmploi = CreerListeChercheurEmploi(DBC) ;
    InitAnciensCollegues(*ListeEmploye, *ListeChercheurEmploi, DBEmp, DBC) ;

    return ;
}

// Supprime le profile (l'entreprise) ainsi que les postes qui lui sont lié
// Fait également transitionner les employes de cette entreprise en chercheur d'emploi
void deleteProfileEntreprise(Entreprise *ToDellE, Entreprise **ListeEntreprise, Personne **ListeEmploye, Personne **ListeChercheurEmploi)
{
    Personne *tmpP, *nextP ;
    Entreprise *tmpE ;
    int i ;

    // Transition des employes de l'entreprise en chercheur d'emploi
    tmpP = *ListeEmploye ;
    while(tmpP){
        nextP = tmpP->nextP() ;
        if(tmpP->EntrepriseActuelle() == ToDellE) tmpP->TransitionStatut(ListeEmploye,ListeChercheurEmploi) ;
        tmpP = nextP ;
    }
    // Suppresion de l'entreprise + ses postes, on retire l'entreprise de la liste pour que le destructeur ne supprime qu'elle
    if(ToDellE->next()) ToDellE->next()->modifPrevious(ToDellE->previous()) ;
    if(ToDellE->previous()) ToDellE->previous()->modifNext(ToDellE->next()) ;
    if(*ListeEntreprise == ToDellE) *ListeEntreprise = (*ListeEntreprise)->next() ;
    ToDellE->modifNext(nullptr) ;
    ToDellE->modifPrevious(nullptr) ;
    delete ToDellE ;
    // Mise à jour des indices
    tmpE = *ListeEntreprise ;
    i = 1 ;
    while(tmpE){
        tmpE->modifIndex(i++) ;
        tmpE = tmpE->next() ;
    }
    // Mise à jour des DB
    (*ListeEntreprise)->MAJDBEntreprise() ;
     (*ListeEmploye)->MAJDBPersonne(true) ;
    (*ListeChercheurEmploi)->MAJDBPersonne(false) ;

    return ;
}
