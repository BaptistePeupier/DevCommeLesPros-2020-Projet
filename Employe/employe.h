///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Classe Employee correspondant aux données d'un employé et aux différentes fonctionnalités qui lui sont liées. //
//                                                                                                               //
// PEUPIER Baptiste MASSELOT Nicolas                                                                             //
// Cree le 06/04/2020, modifié le 07/04/2020                                                                     //
//                                                                                                               //
// Polytech Marseille, informatique 3A                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _EMPLOYE_H_
#define _EMPLOYE_H_

#include "personne.h"

class Employe
{
    private:
        Personne * _EstEmploye ;
    public:
    // Les constructeurs
        Employe(Personne & EstEmploye) ;
    // Le destructeur
        ~Employe(void) ;
    // Accesseur
        Personne * EstEmploye(void) ;
    // Modifieur
        void modifEstEmploye(Personne & NewEstEmploye) ;
    // Fonctionnalités
        void addAncienCollegue(Personne & NewAncienCollegue) ;
        Personne * TransitionChercheur(void) ;                              // Renvoie un pointeur sur une personne en supprimant l'objet, ajoute les collègues de l'entrerprise à la liste d'anciens collègue, une autre fonction attribuera ce pointeur à un objet Chercheur
        void deleteProfile(void) ;
        void addCompetence(Competence & NewCompetence) ;
        void RechercheColleguesCompetence(Competence * ListeCompetence) ;  // Affiche les données des anciens collègues disposant des compétences passé en liste
} ;

#endif
