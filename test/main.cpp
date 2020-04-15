///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Programme de tests                                                                                            //
//                                                                                                               //
// PEUPIER Baptiste                                                                                              //
// Cree le 06/04/2020, modifié le 06/04/2020                                                                     //
//                                                                                                               //
// Polytech Marseille, informatique 3A                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "general.h"

int main()
{
    Entreprise * ListeEntreprise, * tmp ; ;

    // Test sur la création d'une compétence + ajout d'une compétence
    char testchar[128] = "test" ;
    Competence test (testchar, NULL, NULL) ;
    for (int i=0 ; test.label()[i]!='\0' ; i++) cout << test.label()[i] ;
    cout << endl ;

    char testchar2[128] = "test2" ;
    test.AddCompetence(testchar2) ;
    cout << endl ;

    test.delCompetence(testchar) ;
    cout << endl ;

    ListeEntreprise = CreerListeEntreprise() ;
    tmp = ListeEntreprise ;
    while (tmp != NULL){
        cout << tmp->index() << " " ;
        tmp = tmp->next() ;
    }

    return 0 ;
}

