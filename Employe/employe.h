///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Classe Employee correspondant aux données d'un employé et aux différentes fonctionnalités qui lui sont liées. //
//                                                                                                               //
// PEUPIER Baptiste                                                                                              //
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
        // Transitionner le profil vers Chercheur
        void deleteProfile(void) ;

} ;

#endif
