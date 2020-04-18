///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Classe Chercheur correspondant aux données d'un chercheur d'emploi et aux différentes fonctionnalités qui lui //
// sont liées.                                                                                                   //
//                                                                                                               //
// PEUPIER Baptiste MASSELOT Nicolas                                                                             //
// Cree le 06/04/2020, modifié le 08/04/2020                                                                     //
//                                                                                                               //
// Polytech Marseille, informatique 3A                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _CHERCHEUR_H_
#define _CHERCHEUR_H_

#include "personne.h"

class Chercheur
{
    private:
        Personne * _EstChercheur ;
    public:
    // Les constructeurs
        Chercheur(Personne & EstChercheur) ;
    // Le destructeur
        ~Chercheur(void) ;
    // Accesseur
        Personne * EstChercheur(void) ;
    // Modifieur
        void modifEstChercheur(Personne & NewEstChercheur) ;
    // Fonctionnalités
        void addAncienCollegue(Personne & NewAncienCollegue) ;
        Personne * TransitionEmploye() ;                                    // Renvoie un pointeur sur une personne en supprimant l'objet, une autre fonction attribuera ce pointeur à un objet Employe
        void deleteProfile(void) ;
        void addCompetence(Competence & NewCompetence) ;
        void RechercheColleguesCompetence(Competence * ListeCompetence) ;  // Affiche les données des anciens collègues employés dans les entreprises qui recherchent ces compétences
} ;

#endif
