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

int main()
{
    int code ;

    cout << "Bienvenue dans LuminIn !" << endl << "(Tapez 0 pour lancer le programme de tests, n'importe quelle autre touche sinon.)" << endl ;
    //cin >> code ;
    code = 0 ;          // On n'exécute que les tests pour l'instant
    if(code == 0){
        code = tests() ;
        if(code != 0) cout << "Echec du programme de test" << endl ;
    }else{
        code = menu_principal() ;
        code = 0 ;
        // A remplacer par l'interface graphique
    }

    return code ;
}
