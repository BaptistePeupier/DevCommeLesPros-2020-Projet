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
#include <string.h>
#include <signal.h>
// #include <stddef.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// Nombre total de tests exécutés. 
int nbtests = 0 ;
// Pour chaque test qui réussi, cette variable sera incrémentée de 1.
// Le but est de la garder égale à test_executes.
int testreussis = 0 ;

#define STRINGIZE_(x) #x
#define STRINGIZE(x) STRINGIZE_(x)

// Incrémente le nombre de test exécutés de 1.
// Si le test réussi, incrémente le nombre de tests réussis de 1.
#define TEST_STR(a, b) nbtests++ ;                  \
{                                                   \
    if(strcmp(a, b) == 0){                          \
        testreussis++ ;                             \
        cout << "[SUCCES] " ;                       \
        printf(STRINGIZE(__FILE__) ", " STRINGIZE(__LINE__) ": " STRINGIZE(a) " == " STRINGIZE(b) "\n") ; \
    }else cout << "[ECHEC] " ;                      \
}                                                   \

#define TEST(x) nbtests++ ;                         \
{                                                   \
    if(x){                                          \
        testreussis++ ;                             \
        cout << "[SUCCES] " ;                       \
        printf(STRINGIZE(__FILE__) ", " STRINGIZE(__LINE__) ": " STRINGIZE(x) "\n") ; \
    }else cout << "[ECHEC] " ;                      \
}                                                   \

// Fonction à executer lors d'une segmentation fault.
// On imprime les résultats obtenus jusqu'à lors et on arrête immédiatement le programme.
void segfault_sigaction(int signal, siginfo_t *si, void *arg)
{
    printf("[SEGFAULT]\n");
    printf("%d/%d\n", testreussis, nbtests);
    exit(testreussis - nbtests);
}

int main()
{
    char test_recherche_entreprise[128] = "" ;
    int i ;
    Competence test ("SQL", NULL, NULL) ;

    Entreprise * ListeEntreprise ;
    Personne * ListeEmploye, * ListeChercheurEmploi , *test_chercheur , *test_employes;

    // Tests sur la créations des listes
    Creer_listes(&ListeEntreprise, &ListeEmploye, &ListeChercheurEmploi) ;
    TEST(ListeEntreprise) ;
    TEST(ListeEmploye) ;
    TEST(ListeChercheurEmploi) ;
      
    // Test sur la création d'une personne avec l'ajout d'une compétence 
    Personne test_pers(1,"onsepatro","mister","mronsepatro@gmail.com","75009",NULL,NULL,&test,NULL,NULL) ;
    test.AddCompetence("C") ;
    test.AddCompetence("C++") ;
    TEST_STR(test_pers.nom(),"onsepatro") ;
    TEST_STR(test_pers.prenom(),"mister") ;
    TEST_STR(test_pers.mail(),"mronsepatro@gmail.com") ;
    TEST_STR(test_pers.codePostal(),"75009") ;
    TEST_STR(test_pers.CompetencePropres()->label(),"SQL") ;
    
    /*test.delCompetence(testchar) ;
    cout << endl ;*/
    
    // Tests sur la recherche d'anciens colllègues
    // Sur la dernière personne de la liste des chercheurs d'emploi
    cout << "test de la recherche d'anciens collegues chez google " << endl ;
    test_chercheur = ListeChercheurEmploi ;
    while (test_chercheur->nextP()) {
        test_chercheur = test_chercheur->nextP() ;
    }
    test_chercheur->CompetencePropres()->AddCompetence(testchar) ;    //ajout d'une compétence 
    test_chercheur->RechercheColleguesEntreprise("Google") ;

    // La liste des compétences est celle de la personne pour tester
    cout << "test de la recherche d'anciens collegues dans les entreprise recherchant les competences dans une liste " << endl ;
    test_chercheur->ChercheurRechercheColleguesCompetence(test_chercheur->CompetencePropres()) ;

    // Test sur la dernière de la liste des employés
    cout << "test de la recherche d'anciens collegues disposant des competences dans une liste " << endl ;
    cout << endl ;
    Competence test_liste("C++" , NULL,NULL) ;
    test_liste.AddCompetence("Python") ;
    test_employes = ListeEmploye ;
    while (test_employes->nextP()) {
        test_employes = test_employes->nextP() ;
    }
    test_employes->EmployeRechercheColleguesCompetence(&test_liste) ;

    test_pers.RecherchePosteCompetence(ListeEntreprise) ;
    cout << endl ;
    test_pers.RecherchePosteCompetenceCodePostal(ListeEntreprise) ;

    // Tests sur la MAJ de la db entreprise
    ListeEntreprise->next()->modifMail("eMplois@google.com") ;
    ListeEntreprise->modifCodePostal("777007707") ;
    ListeEntreprise->addEntreprise("test", "7007", "test@gmail.com") ;

    delete ListeEntreprise ;
    
    cout << "Tests reussis : " << testreussis << "/" << nbtests << endl ;

    return testreussis - nbtests ;
}

