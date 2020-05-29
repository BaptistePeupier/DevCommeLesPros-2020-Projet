///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Programme général, permettant soit de lancer l'application soit le lancer les tests.                          //
//                                                                                                               //
// PEUPIER Baptiste MASSELOT Nicolas                                                                             //
// Cree le 06/05/2020, modifié le 06/05/2020                                                                     //
//                                                                                                               //
// Polytech Marseille, informatique 3A                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "tests.h"
#include "interface.h"

Personne * EmployesListe ;
Personne * ChercheursListe ;
Entreprise * EntrepriseListe ;

int main()
{
    int code ;

    system("clear") ;
    cout << "Bienvenue dans LuminIn !" << endl ;    //<< "(Tapez 0 pour lancer le programme de tests, n'importe quelle autre touche sinon.)" << endl ;
    // code = 0 ;           // On n'exécute que les tests
    code = 1 ;              // On n'exécute que l'application
    if(code == 0){
        code = tests() ;
        if(code != 0) cout << "Echec du programme de test" << endl ;
    }else{
        Creer_listes(&EntrepriseListe, &EmployesListe, &ChercheursListe, "Database/entreprise.csv", "Database/poste.csv", "Database/employes.csv", "Database/chercheurEmploi.csv") ;
        code = lancement_interface() ;
        // code = 0 ;
        delete EmployesListe ;
        delete ChercheursListe ;
        delete EntrepriseListe ;
    }

    return code ;
}

