///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Interface de l'application                                                                                    //
//                                                                                                               //
// PEUPIER Baptiste MASSELOT Nicolas                                                                             //
// Cree le 18/05/2020, modifié le 18/05/2020                                                                     //
//                                                                                                               //
// Polytech Marseille, informatique 3A                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "interface.h"

int interface(void)
{
    string choix ;
    cout << "* Menu principal *" << endl ;
    cout << endl ;

    cout << "vous êtes :" << endl ;
    cout << "1.Une entreprise" << endl ;
    cout << "2.Un employé" << endl ;
    cout << "3.A la recherche d'un emploi" << endl ;
    cout << endl ;
    cout << "Votre choix ('q' pour quitter) : " ;
    
    do
    {
        cin >> choix ;
        if (choix != "1" && choix != "2" && choix != "3" && choix != "q") {
            cout << "option inconnue" << endl ;
        }
    } while (choix != "1" && choix != "2" && choix != "3" && choix != "q" );
    
    if (choix == "1") {
        cout << "menu entreprise (coming soon)" << endl ;
    } else if (choix == "2") {
        cout << "menu employé (coming soon)" << endl ;
    } else if (choix == "3") {
        cout << "menu chercheur d'emploi (coming soon)" << endl ;
    }
    return 0 ;
}