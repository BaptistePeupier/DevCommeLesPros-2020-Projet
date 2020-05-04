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
    char testchar2_5[128] = "C++" ;
    char testchar3[128] = "Python" ;
    char testchar4[128] = "comedie" ;
    char newMail[128] = "eMplois@google.com" ;
    char newCodePostal[128] = "777007707" ;
    char cp_recherche_pers[128] = "77700" ;
    char testnom[128] = "onsepatro" ;
    char testprenom[128] = "mister" ;
    char testmail[128] = "mronsepatro@gmail.com" ;
    char testcodepostal[128] = "75009" ;
    char test_recherche_entreprise[128] = "Google" ;
    int i , testreussis = 0 ;
    Competence test (testchar, NULL, NULL) ;

    Entreprise * ListeEntreprise, * tmp ;
    Personne * ListeEmploye, * ListeChercheurEmploi , *test_chercheur , *test_employes;

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
        testreussis++ ;
    }
    cout << test_pers.prenom() << endl ;
    if (strcmp(test_pers.prenom(),"mister") == 0) {
        testreussis++ ;
    }
    cout << test_pers.mail() << endl ;
    if (strcmp(test_pers.mail(),"mronsepatro@gmail.com") == 0) {
        testreussis++ ;
    }
    
    cout << test_pers.codePostal() << endl ;
    if (strcmp(test_pers.codePostal(),"75009" ) == 0) {
        testreussis++ ;
    }
    cout << test_pers.CompetencePropres()->label() << endl ;
    if (strcmp(test_pers.CompetencePropres()->label(),"SQL" ) == 0) {
        testreussis++ ;
    }

    cout << "tests reussis sur la classe personne " << testreussis << "/5" << endl ;
    
    
    /*test.delCompetence(testchar) ;
    cout << endl ;*/
    
    //tests sur la recherche d'anciens colllègues
    //sur la dernière personne de la liste des chercheurs d'emploi
    cout << "test de la recherche d'anciens collegues chez google " << endl ;
    test_chercheur = ListeChercheurEmploi ;
    while (test_chercheur->nextP()) {
        test_chercheur = test_chercheur->nextP() ;
    }
    test_chercheur->CompetencePropres()->AddCompetence(testchar) ;    //ajout d'une compétence 
    test_chercheur->RechercheColleguesEntreprise(test_recherche_entreprise) ;

    //la liste des compétences est celle de la personne pour tester
    cout << "test de la recherche d'anciens collegues dans les entreprise recherchant les competences dans une liste " << endl ;
    test_chercheur->ChercheurRechercheColleguesCompetence(test_chercheur->CompetencePropres()) ;
    

    //test sur la dernière de la liste des employés
    cout << "test de la recherche d'anciens collegues disposant des competences dans une liste " << endl ;
    cout << endl ;
    Competence test_liste(testchar2_5 , NULL,NULL) ;
    test_liste.AddCompetence(testchar3) ;
    test_employes = ListeEmploye ;
    while (test_employes->nextP()) {
        test_employes = test_employes->nextP() ;
    }
    test_employes->EmployeRechercheColleguesCompetence(&test_liste) ;

    //tests sur la recherche de chercheurs d'emploi par compétence
    cout << "test de la recherche des chercheurs d'emplois disposant des competences dans une liste " << endl ;
    Competence test_recherche_list(testchar4 ,NULL , NULL) ;
    test_recherche_list.AddCompetence(testchar3) ;
    test_chercheur->ChercheurCompetence(&test_recherche_list) ;

    //tests sur la recherche de chercheurs d'emploi par compétence et par code postal
    cout << "test de la recherche des chercheurs d'emplois disposant des competences dans une liste avec le code postal recherche " << endl ;
    test_chercheur->ChercheurCompetenceCodePostal(&test_recherche_list,cp_recherche_pers);
    
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

