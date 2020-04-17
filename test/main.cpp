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
    char testchar[128] = "test" ;
    char testchar2[128] = "test2" ;
    char newMail[128] = "eMplois@google.com" ;
    int i ;
    Competence test (testchar, NULL, NULL) ;
    Entreprise * ListeEntreprise, * tmp ;

    // Test sur la création d'une compétence + ajout d'une compétence
    for (i=0 ; test.label()[i]!='\0' ; i++) cout << test.label()[i] ;
    cout << endl ;

    test.AddCompetence(testchar2) ;
    cout << endl ;
    test.delCompetence(testchar) ;
    cout << endl ;

    // Tests sur la création de la liste d'Entrerpise
    ListeEntreprise = CreerListeEntreprise() ;
    tmp = ListeEntreprise ;
    while (tmp != NULL){
        cout << tmp->index() << " " ;
        tmp = tmp->next() ;
    }
    cout << endl ;
    ListeEntreprise->next()->modifMail(newMail) ;
    ListeEntreprise->MAJDBEntreprise(ListeEntreprise->next()) ;

    delete ListeEntreprise ;

    return 0 ;
}

