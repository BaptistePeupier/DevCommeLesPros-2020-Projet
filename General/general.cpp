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

#include <stdio.h>
// #include <string.h>

#include "general.h"

// Construit la liste des Entreprises à partir d'une base de donnée (Entreprise + postes)
Entreprise * CreerListeEntreprise(void)
{

    Entreprise * ListeEntreprise = NULL, * tmp = NULL ;
    int tmpindex ;
    char tmpnom[128] ;
    char tmpcodePostal[128] ;
    char tmpmail[128] ;

    // Lecture de la base de donnée des entreprises
    FILE *db_entreprise = fopen("test/fichier_de_tests/entreprise.csv", "r");
    // id,nom,code postal,mail -> entreprise
    while(fscanf(db_entreprise, "%d,%127[^,],%127[^,],%127[^,]", &tmpindex, tmpnom, tmpcodePostal, tmpmail) == 4)
    {
        // site_amu *site = malloc(sizeof(site_amu));
        Entreprise * NewEntreprise = new Entreprise (tmpindex, tmpnom, tmpcodePostal, tmpmail, NULL, NULL) ;
        // l_append(&sites, l_make_node(site));
        if(tmp == NULL){                                 // Première entreprise
            ListeEntreprise = NewEntreprise ;
        }else{
            NewEntreprise->modifPrevious(*tmp) ;
            tmp->modifNext(*NewEntreprise) ;
            tmp = NewEntreprise ;
        }
    }
    fclose(db_entreprise);

    // Lecture de la base de donnée des postes
    // id,titre,competences,entreprise -> poste


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

