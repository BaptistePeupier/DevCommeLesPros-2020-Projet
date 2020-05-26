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
#define TEST(x) nbtests++ ;                         \
{                                                   \
    if(x){                                          \
        testreussis++ ;                             \
        cout << "[SUCCES] " ;                       \
        printf(STRINGIZE(__FILE__) ", " STRINGIZE(__LINE__) ": " STRINGIZE(x) "\n") ; \
    }else cout << "[ECHEC]\n" ;                      \
}                                                   \

#define TEST2(x, y) nbtests++ ;                     \
{                                                   \
    if(x == y){                                     \
        testreussis++ ;                             \
        cout << "[SUCCES] " ;                       \
        printf(STRINGIZE(__FILE__) ", " STRINGIZE(__LINE__) ": " STRINGIZE(x) " == " STRINGIZE(y) "\n") ; \
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
        if(strcmp(New_db,"test/FichiersDeTests/chercheurEmploi.csv") == 0){\
            ofstream N(New_db) ;                    \
            ifstream S("test/db_backup/chercheurEmploi.csv") ;\
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
    Personne * ListeEmploye, * ListeChercheurEmploi ;
    Personne *test_employes, *test_chercheur ;
    Personne * tmpP ;
    Poste *tmpPo ;
    Entreprise * tmpE ;
    AncienCollegue *tmpA ;
    // Variables pour les tests de recherches
    Entreprise *tmpERecherche ;
    // Personne *tmpPRecherche ;
    AncienCollegue *tmpARecherche ;

// Tests sur la créations des listes
    Creer_listes(&ListeEntreprise, &ListeEmploye, &ListeChercheurEmploi) ;
    TEST(ListeEntreprise) ;
    TEST(ListeEmploye) ;
    TEST(ListeChercheurEmploi) ;
    // Grâce aux fonctions de mise à jour des DB, on teste à la fois les fonctions de création des listes et de mise à jour des DB
    ListeEntreprise->MAJDBEntreprise() ;
    ListeEmploye->MAJDBPersonne(true) ;
    ListeChercheurEmploi->MAJDBPersonne(false) ;
    TEST_MAJ_DB("test/FichiersDeTests/entreprise.csv", "test/db_backup/entreprise.csv") ;
    TEST_MAJ_DB("test/FichiersDeTests/poste.csv", "test/db_backup/poste.csv") ;
    TEST_MAJ_DB("test/FichiersDeTests/employes.csv", "test/db_backup/employes.csv") ;
    TEST_MAJ_DB("test/FichiersDeTests/chercheurEmploi.csv", "test/db_backup/chercheurEmploi.csv") ;

// Test sur la création d'une personne avec l'ajout d'une compétence 
    Personne test_pers(1,"onsepatro","mister","mronsepatro@gmail.com","75009",NULL,NULL,new Competence ("SQL")) ;
    test_pers.CompetencePropres()->AddCompetence("C") ;
    test_pers.CompetencePropres()->AddCompetence("C++") ;
    TEST2(test_pers.nom(),"onsepatro") ;
    TEST2(test_pers.prenom(),"mister") ;
    TEST2(test_pers.mail(),"mronsepatro@gmail.com") ;
    TEST2(test_pers.codePostal(),"75009") ;
    TEST2(test_pers.CompetencePropres()->label(),"SQL") ;
    TEST2(test_pers.CompetencePropres()->next()->label(),"C") ;
    TEST2(test_pers.CompetencePropres()->next()->next()->label(),"C++") ;

// Test pour la suppression de compétence
    // Au milieu de la chaine
    test_pers.CompetencePropres()->delCompetence("C") ;
    TEST2(test_pers.CompetencePropres()->label(),"SQL") ;
    TEST2(test_pers.CompetencePropres()->next()->label(),"C++") ;
    TEST(!test_pers.CompetencePropres()->next()->next()) ;
    // En début de chaine
    test_pers.CompetencePropres()->delCompetence("SQL") ;
    TEST2(test_pers.CompetencePropres()->label(),"C++") ;
    TEST(!test_pers.CompetencePropres()->next()) ;
    
// Tests sur les fonctions de recherche
    // Tests sur la recherche d'anciens colllègues
    // Sur la dernière personne de la liste des chercheurs d'emploi
    test_chercheur = ListeChercheurEmploi ;
    while (test_chercheur->nextP()) test_chercheur = test_chercheur->nextP() ;
    test_chercheur->CompetencePropres()->AddCompetence("SQL") ;                 // Ajout d'une compétence
    tmpARecherche = test_chercheur->RechercheColleguesEntreprise("Google") ;
    TEST2(tmpARecherche->currentA()->nom(),"Untel") ;
    TEST2(tmpARecherche->currentA()->prenom(),"Michel") ;
    TEST(!tmpARecherche->nextA()) ;
    delete tmpARecherche ;

    // Test de la recherche d'anciens collegues dans les entreprise recherchant les competences dans une liste :
    // La liste des compétences est celle de la personne pour tester
    // Test sur la second personne de la liste
    test_chercheur = ListeChercheurEmploi->nextP() ;
    tmpARecherche = test_chercheur->ChercheurRechercheColleguesCompetence(test_chercheur->CompetencePropres()) ;
    TEST2(tmpARecherche->currentA()->nom(),"Untel") ;
    TEST2(tmpARecherche->currentA()->prenom(),"Michel") ;
    // TEST(!tmpARecherche->nextA()) ;
    delete tmpARecherche ;

    // Test de la recherche d'anciens collegues disposant des competences dans une liste :
    // Sur la dernière personne de la liste des employés
    Competence test_liste("C++") ;
    test_liste.AddCompetence("Python") ;
    test_employes = ListeEmploye ;
    while (test_employes->nextP()) test_employes = test_employes->nextP() ;
    tmpARecherche = test_employes->EmployeRechercheColleguesCompetence(&test_liste) ;
    TEST(!tmpARecherche) ;
    delete tmpARecherche ;

    tmpERecherche = test_pers.RecherchePosteCompetence(ListeEntreprise) ;
    // TEST(tmpERecherche) ;
    // TEST(!tmpERecherche->next()) ;
    delete tmpERecherche ;

    tmpERecherche = test_pers.RecherchePosteCompetenceCodePostal(ListeEntreprise) ;
    TEST(!tmpERecherche) ;
    delete tmpERecherche ;

// Test d'ajout et de suppression d'ancien collègue
    test_employes->ListAncienCollegues()->addAncienCollegue(test_chercheur,test_employes) ;
    tmpA = test_employes->ListAncienCollegues() ;
    while(tmpA->nextA()->nextA()) tmpA = tmpA->nextA() ;        // Pour ne pas garder un pointeur sur l'objet détruit, on utilise son précédent
    TEST2(tmpA->nextA()->currentA(), test_chercheur) ;
    test_employes->ListAncienCollegues()->dellAncienCollegue(test_chercheur,test_employes) ;
    TEST(!tmpA->nextA()) ;

// Test sur la transition de profil
    tmpP = ListeEmploye ;
    tmpE = tmpP->EntrepriseActuelle() ;
    tmpP->TransitionStatut(&ListeEmploye, &ListeChercheurEmploi) ;
    TEST2(ListeChercheurEmploi->nextP()->nextP()->nextP()->nextP(),tmpP) ;
    tmpP->TransitionStatut(&ListeEmploye, &ListeChercheurEmploi, tmpE) ;
    TEST2(ListeEmploye->nextP()->nextP()->nextP(),tmpP) ;
    tmpP = ListeEmploye->nextP() ;
    tmpE = tmpP->EntrepriseActuelle() ;
    tmpP->TransitionStatut(&ListeEmploye, &ListeChercheurEmploi) ;
    TEST2(ListeChercheurEmploi->nextP()->nextP()->nextP()->nextP(),tmpP) ;
    tmpP->TransitionStatut(&ListeEmploye, &ListeChercheurEmploi, tmpE) ;
    TEST2(ListeEmploye->nextP()->nextP()->nextP(),tmpP) ;

// Test sur la suppression du profil d'une entreprise
    tmpE = ListeEntreprise->next() ;
    deleteProfileEntreprise(ListeEntreprise, &ListeEntreprise, &ListeEmploye, &ListeChercheurEmploi) ;
    TEST2(ListeEntreprise, tmpE) ;

// Test sur l'ajout et la suppression d'un poste
    ListeEntreprise->addPoste(new Poste("vendeur", NULL, NULL, new Competence("OS"))) ;
    tmpPo = ListeEntreprise->profilPoste() ;
    while(tmpPo->next()->next()) tmpPo = tmpPo->next() ;        // Pour ne pas garder un pointeur sur l'objet détruit, on utilise son précédent
    TEST2(tmpPo->next()->Titre(), "vendeur") ;
    TEST2(tmpPo->next()->CompetencesRequises()->label(), "OS") ;
    ListeEntreprise->dellPoste("vendeur") ;
    TEST(!tmpPo->next()) ;

// Test de la suppression de profil d'une personne
    // Avec une personne ajoutée à la fin
    test_chercheur = ListeChercheurEmploi ;
    while (test_chercheur->nextP()) {
        test_chercheur = test_chercheur->nextP() ;
    }
    test_pers.modifIndex(test_chercheur->index()+1) ;
    test_chercheur->modifNextP(&test_pers) ;
    test_pers.modifPreviousP(test_chercheur) ;
    test_chercheur->MAJDBPersonne(false) ;
    test_pers.deleteProfile(&ListeEmploye,&ListeChercheurEmploi) ;
    // Avec une personne au début
    test_employes = ListeEmploye ;
    test_employes->deleteProfile(&ListeEmploye,&ListeChercheurEmploi) ;

// Tests sur les MAJ des DB
    // Tests sur la MAJ de la db entreprise
    ListeEntreprise->addEntreprise("test", "7007", "test@gmail.com") ;  // Teste également l'ajout d'entreprise
    ListeEntreprise->next()->modifMail("eMplois@google.com") ;
    ListeEntreprise->modifCodePostal("777007707") ;
    ListeEntreprise->MAJDBEntreprise() ;
    ListeEmploye->MAJDBPersonne(true) ;
    ListeChercheurEmploi->MAJDBPersonne(false) ;
    TEST_MAJ_DB("test/FichiersDeTests/entreprise.csv", "test/db_tests_expected/entreprise.csv") ;
    // Tests sur la MAJ de la db poste
    TEST_MAJ_DB("test/FichiersDeTests/poste.csv", "test/db_tests_expected/poste.csv") ;
    // Tests sur la MAJ de la db employe
    TEST_MAJ_DB("test/FichiersDeTests/employes.csv", "test/db_tests_expected/employes.csv") ;
    // Tests sur la MAJ de la db chercheurEmploi
    TEST_MAJ_DB("test/FichiersDeTests/chercheurEmploi.csv", "test/db_tests_expected/chercheurEmploi.csv") ;

// Fin des tests
    cout << endl << "Appel des destructeurs :" << endl ;
    delete ListeEntreprise ;
    delete ListeEmploye ;
    delete ListeChercheurEmploi ;
    
    cout << "Tests reussis : " << testreussis << "/" << nbtests << endl ;

    return testreussis - nbtests ;
}
