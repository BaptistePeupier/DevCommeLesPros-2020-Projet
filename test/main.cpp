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
    // Test sur la création d'une compétence + ajout d'une compétence
    char testchar[128] = "test" ;
    Competence test (testchar, NULL, NULL) ;
    for (int i=0 ; test.label()[i]!='\0' ; i++) cout << test.label()[i] ;
    cout << endl ;

    char testchar2[128] = "test2" ;
    Competence test2 (testchar2, NULL, NULL) ;
    test.AddCompetence(test2) ;
    cout << endl ;

    // test.delCompetence(testchar) ;   // manque la fonction modifLabel
    cout << endl ;

    return 0 ;
}

