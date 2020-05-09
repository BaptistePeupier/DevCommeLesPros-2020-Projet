///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// Programme de tests                                                                                            //
//                                                                                                               //
// PEUPIER Baptiste MASSELOT Nicolas                                                                             //
// Cree le 06/04/2020, modifié le 06/05/2020                                                                     //
//                                                                                                               //
// Polytech Marseille, informatique 3A                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "tests.h"

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
    }else cout << "[ECHEC] (val : "<<a<<")"<< endl ;\
}                                                   \

#define TEST(x) nbtests++ ;                         \
{                                                   \
    if(x){                                          \
        testreussis++ ;                             \
        cout << "[SUCCES] " ;                       \
        printf(STRINGIZE(__FILE__) ", " STRINGIZE(__LINE__) ": " STRINGIZE(x) "\n") ; \
    }else cout << "[ECHEC]\n" ;                      \
}                                                   \

// Compare le contenu de deux fichiers aux chemins a et b avec la commande diff. Incrémente test_reussis si les fichiers sont pareils.
// Réinitialise ensuite la DB en question
#define TEST_MAJ_DB(New_db, Expected_db) nbtests++ ;\
{                                                   \
    int const r = system("diff --text --strip-trailing-cr " New_db " " Expected_db " > /dev/null");    \
    if(!WEXITSTATUS(r)){                            \
        testreussis++ ;                             \
        cout << "[SUCCES] " ;                       \
        printf(STRINGIZE(__FILE__) ", " STRINGIZE(__LINE__) ": Succes MAJ " STRINGIZE(New_db) " Reinitialisation\n") ; \
        if(strcmp(New_db,"test/FichiersDeTests/chercheurd'emploi.csv") == 0){\
            ofstream N(New_db) ;                    \
            ifstream S("test/db_backup/chercheurd'emploi.csv") ;\
            string line ;                           \
            getline(S, line) ;                      \
            N << line ;                             \
            while(getline(S, line)) N << endl << line ;\
        }                                           \
        else if(strcmp(New_db,"test/FichiersDeTests/employes.csv") == 0){\
            ofstream N(New_db) ;                    \
            ifstream S("test/db_backup/employes.csv") ;\
            string line ;                           \
            getline(S, line) ;                      \
            N << line ;                             \
            while(getline(S, line)) N << endl << line ;\
        }                                           \
        else if(strcmp(New_db,"test/FichiersDeTests/entreprise.csv") == 0){\
            ofstream N(New_db) ;                    \
            ifstream S("test/db_backup/entreprise.csv") ;\
            string line ;                           \
            getline(S, line) ;                      \
            N << line ;                             \
            while(getline(S, line)) N << endl << line ;\
        }                                           \
        else if(strcmp(New_db,"test/FichiersDeTests/poste.csv") == 0){\
            ofstream N(New_db) ;                    \
            ifstream S("test/db_backup/poste.csv") ;\
            string line ;                           \
            getline(S, line) ;                      \
            N << line ;                             \
            while(getline(S, line)) N << endl << line ;\
        }                                           \
    }else cout << "[ECHEC]\n" ;                     \
}                                                   \

int tests(void)
{
    Entreprise * ListeEntreprise ;
    Personne * ListeEmploye, * ListeChercheurEmploi , *test_chercheur , *test_employes;

    // Tests sur la créations des listes
    Creer_listes(&ListeEntreprise, &ListeEmploye, &ListeChercheurEmploi) ;
    TEST(ListeEntreprise) ;
    TEST(ListeEmploye) ;
    TEST(ListeChercheurEmploi) ;
      
    // Test sur la création d'une personne avec l'ajout d'une compétence 
    Personne test_pers(1,"onsepatro","mister","mronsepatro@gmail.com","75009",NULL,NULL,new Competence ("SQL", NULL, NULL),NULL,NULL) ;
    test_pers.CompetencePropres()->AddCompetence("C") ;
    test_pers.CompetencePropres()->AddCompetence("C++") ;
    TEST_STR(test_pers.nom(),"onsepatro") ;
    TEST_STR(test_pers.prenom(),"mister") ;
    TEST_STR(test_pers.mail(),"mronsepatro@gmail.com") ;
    TEST_STR(test_pers.codePostal(),"75009") ;
    TEST_STR(test_pers.CompetencePropres()->label(),"SQL") ;
    TEST_STR(test_pers.CompetencePropres()->next()->label(),"C") ;
    TEST_STR(test_pers.CompetencePropres()->next()->next()->label(),"C++") ;

    // Test pour la suppression de compétence
    // Au milieu de la chaine
    test_pers.CompetencePropres()->delCompetence("C") ;
    TEST_STR(test_pers.CompetencePropres()->label(),"SQL") ;
    TEST_STR(test_pers.CompetencePropres()->next()->label(),"C++") ;
    TEST(!test_pers.CompetencePropres()->next()->next()) ;
    // En début de chaine
    test_pers.CompetencePropres()->delCompetence("SQL") ;
    TEST_STR(test_pers.CompetencePropres()->label(),"C++") ;
    TEST(!test_pers.CompetencePropres()->next()) ;
    
    // Tests sur la recherche d'anciens colllègues
    // Sur la dernière personne de la liste des chercheurs d'emploi
    cout << "Test de la recherche d'anciens collegues chez google :" << endl ;
    test_chercheur = ListeChercheurEmploi ;
    while (test_chercheur->nextP()) test_chercheur = test_chercheur->nextP() ;
    test_chercheur->CompetencePropres()->AddCompetence("SQL") ;                 //ajout d'une compétence 
    test_chercheur->RechercheColleguesEntreprise("Google") ;

    // La liste des compétences est celle de la personne pour tester
    cout << "Test de la recherche d'anciens collegues dans les entreprise recherchant les competences dans une liste :" << endl ;
    test_chercheur->ChercheurRechercheColleguesCompetence(test_chercheur->CompetencePropres()) ;

    // Test sur la dernière de la liste des employés
    cout << "Test de la recherche d'anciens collegues disposant des competences dans une liste :" << endl ;
    cout << endl ;
    Competence test_liste("C++" , NULL,NULL) ;
    test_liste.AddCompetence("Python") ;
    test_employes = ListeEmploye ;
    //while (test_employes->nextP()) test_employes = test_employes->nextP() ;
    test_employes->EmployeRechercheColleguesCompetence(&test_liste) ;

    test_pers.RecherchePosteCompetence(ListeEntreprise) ;
    cout << endl ;
    test_pers.RecherchePosteCompetenceCodePostal(ListeEntreprise) ;

    test_employes->ListAncienCollegues()->addAncienCollegue(test_chercheur,test_employes) ;
    test_employes->ListAncienCollegues()->dellAncienCollegue(test_chercheur,test_employes) ;

    // Tests sur la MAJ de la db entreprise
    ListeEntreprise->next()->modifMail("eMplois@google.com") ;
    ListeEntreprise->modifCodePostal("777007707") ;
    ListeEntreprise->addEntreprise("test", "7007", "test@gmail.com") ;
    TEST_MAJ_DB("test/FichiersDeTests/entreprise.csv", "test/db_tests_expected/entreprise.csv") ;

    // Tests sur la MAJ de la db poste


    // Tests sur la MAJ de la db employe
    ListeEmploye->nextP()->nextP()->modifNom("Souris") ;
    TEST_MAJ_DB("test/FichiersDeTests/employes.csv", "test/db_tests_expected/employes.csv") ;

    // Tests sur la MAJ de la db chercheurd'emploi

    cout << endl << "Appel des destructeurs :" << endl ;
    delete ListeEntreprise ;
    delete ListeEmploye ;
    delete ListeChercheurEmploi ;
    
    cout << "Tests reussis : " << testreussis << "/" << nbtests << endl ;

    return testreussis - nbtests ;
}
