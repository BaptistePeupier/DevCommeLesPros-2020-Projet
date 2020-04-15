///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Fonctions générales d'utilisation du programme :                                                              //
//              - transitions entre Employe et Chercheur                                                         //
//              - interface graphique                                                                            //
//                                                                                                               //
// PEUPIER Baptiste                                                                                              //
// Cree le 08/04/2020, modifié le 08/04/2020                                                                     //
//                                                                                                               //
// Polytech Marseille, informatique 3A                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "general.h"

// Construit la liste des Entreprises à partir d'une base de donnée (Entreprise + postes)
Entreprise * CreerListeEntreprise(void)
{

    Entreprise * ListeEntreprise = NULL, * tmp = NULL ;
    int tmpindex ;
    int tmpentreprise ;
    char tmpnom[128] ;
    char tmpcodePostal[128] ;
    char tmpmail[128] ;
    char tmpcompetence[128] ;

    // Lecture de la base de donnée des entreprises
    FILE *db_entreprise = fopen("test/FichiersDeTests/entreprise.csv", "r") ;
    if(db_entreprise){
        fscanf(db_entreprise, "%*s") ;
        // id,nom,code_postal,mail -> entreprise
        while(fscanf(db_entreprise, "%d,%127[^,],%127[^,],%127[^\n]", &tmpindex, tmpnom, tmpcodePostal, tmpmail) == 4)
        {
            Entreprise * NewEntreprise = new Entreprise (tmpindex, tmpnom, tmpcodePostal, tmpmail, NULL, NULL) ;
            if(tmp == NULL){                                 // Première entreprise
                ListeEntreprise = NewEntreprise ;
                tmp = ListeEntreprise ;
            }else{
                NewEntreprise->modifPrevious(*tmp) ;
                tmp->modifNext(*NewEntreprise) ;
                tmp = NewEntreprise ;
            }
        }
        fclose(db_entreprise) ;
    }else{
        cout << "Erreur d'ouverture de la base de donnée des entreprises" << endl ;
    }

    // Lecture de la base de donnée des postes
    FILE *db_poste = fopen("test/FichiersDeTests/poste.csv", "r") ;
    if(db_poste){
        fscanf(db_poste, "%*s") ;
        // id,titre,entreprise,competences(multiples) -> poste
        while (fscanf(db_poste, "%d,%127[^,],%d", &tmpindex,tmpnom,&tmpentreprise) == 3)
        {
            Poste * NewPoste = new Poste (tmpnom, NULL, NULL, NULL) ;
            while (fscanf(db_poste, "%127[^;\n]", tmpcompetence) == 1)        // Lecture des compétences demandées
            {
                if(NewPoste->CompetencesRequises()){
                    NewPoste->CompetencesRequises()->AddCompetence(tmpcompetence) ;
                }else{                                                        // La première compétence
                    NewPoste->modifCompetencesRequises(new Competence (tmpcompetence, NULL, NULL)) ;
                }
            }
            tmp = ListeEntreprise ;
            while (tmp && tmpentreprise!=tmp->index()) tmp = tmp->next() ;  // Association à l'entreprise
            tmp->addPoste(NewPoste) ;
        }
        fclose(db_poste);
    }else{
        cout << "Erreur d'ouverture de la base de donnée des postes" << endl ;
    }


    return ListeEntreprise ;
}

// Construit la liste des Employes à partir d'une base de donnée
Employe * CreerListeEmploye(void)
{
    return NULL ;
}

// Construit la liste des Chercheurs à partir d'une base de donnée
Chercheur * CreerListeChercheur(void)
{
    return NULL ;
}

// Attribue une personne récupéré d'un Employe à un objet Chercheur
Chercheur * AuxTransitionChercheur (Employe & ToTransit)
{
    return NULL ;
}

// Attribue une personne récupéré d'un Chercheur à un objet Employe
Employe * AuxTransitionEmploye (Chercheur & ToTransit)
{
    return NULL ;
}

// Rechercher parmis les chercheurs par competences, affiche les résutats
void ChercheurCompetence (Chercheur & listeChercheur, Competence * listeComp)
{
    return ;
}

// Rechercher parmis les chercheurs par competences et code postal, affiche les résutats
void ChercheurCompetenceCodePostal (Chercheur & listeChercheur, char * CodePostalRecherche)
{
    return ;
}

