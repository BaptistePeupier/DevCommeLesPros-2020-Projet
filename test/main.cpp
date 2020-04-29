///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Programme de tests                                                                                            //
//                                                                                                               //
// PEUPIER Baptiste MASSELOT Nicolas                                                                             //
// Cree le 06/04/2020, modifié le 18/04/2020                                                                     //
//                                                                                                               //
// Polytech Marseille, informatique 3A                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "general.h"
#include "string.h"

int main()
{
    char testchar[128] = "SQL" ;
    char testchar2[128] = "C" ;
    char testchar3[128] = "Python" ;
    char newMail[128] = "eMplois@google.com" ;
    char newCodePostal[128] = "777007707" ;
    char testnom[128] = "onsepatro" ;
    char testprenom[128] = "mister" ;
    char testmail[128] = "mronsepatro@gmail.com" ;
    char testcodepostal[128] = "75009" ;
    int i , testrates = 0 ;
    Competence test (testchar, NULL, NULL) ;

    Entreprise * ListeEntreprise, * tmp ;
    Personne * ListeEmploye, * ListeChercheurEmploi;

    Creer_listes(&ListeEntreprise, &ListeEmploye, &ListeChercheurEmploi) ;


    // Test sur la création d'une compétence + ajout d'une compétence
    for (i=0 ; test.label()[i]!='\0' ; i++) cout << test.label()[i] ;
    cout << endl ;

    //test sur la création d'une personne avec l'ajout d'une compétence 
    Personne test_pers(1,testnom,testprenom,testmail,testcodepostal,NULL,NULL,&test,NULL,NULL) ;
    test.AddCompetence(testchar2) ;
    test.AddCompetence(testchar3) ;
    cout << endl ;
    cout << test_pers.nom() << endl;
    if (strcmp(test_pers.nom(),"onsepatro") == 0) {
        testrates++ ;
    }
    cout << test_pers.prenom() << endl ;
    if (strcmp(test_pers.prenom(),"mister") == 0) {
        testrates++ ;
    }
    cout << test_pers.mail() << endl ;
    if (strcmp(test_pers.mail(),"mronsepatro@gmail.com") == 0) {
        testrates++ ;
    }
    
    cout << test_pers.codePostal() << endl ;
    if (strcmp(test_pers.codePostal(),"75009" ) == 0) {
        testrates++ ;
    }
    cout << test_pers.CompetencePropres()->label() << endl ;
    if (strcmp(test_pers.CompetencePropres()->label(),"SQL" ) == 0) {
        testrates++ ;
    }

    cout << "tests reussis sur la classe personne " << testrates << "/5" << endl ;

    test_pers.MAJDBPersonne() ;
    
    
    /*test.delCompetence(testchar) ;
    cout << endl ;*/
    
    // Tests sur la création de la liste d'Entrerpise
    tmp = ListeEntreprise ;
    while (tmp != NULL){
        cout << tmp->index() << " " ;
        tmp = tmp->next() ;
    }
    cout << endl ;

    
    test_pers.RecherchePosteCompetence(ListeEntreprise) ;
    cout << endl ;
    test_pers.RecherchePosteCompetenceCodePostal(ListeEntreprise) ;

    // Tests sur la MAJ de la db entreprise
    ListeEntreprise->next()->modifMail(newMail) ;
    ListeEntreprise->modifCodePostal(newCodePostal) ;
    ListeEntreprise->addEntreprise("test", "7007", "test@gmail.com") ;

    delete ListeEntreprise ;
    
    return 0 ;
}

