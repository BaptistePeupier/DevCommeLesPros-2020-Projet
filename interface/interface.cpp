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


void menu_profil_entreprise(Entreprise * utilisateur_entreprise)
{
    char choix_action_entreprise ;
    bool option_unknown = true;
    cout << "Bienvenue dans LuminIn !" << endl << endl;
    cout << "* Menu entreprise *" << endl ;
    cout << endl ;
    
    while (option_unknown) {
        cout << "Vous voulez :" << endl ; 
        cout << "1. Créer le profil d'un poste à pourvoir" << endl ;
        cout << "2. Supprimer le profil d'un poste maintenant pourvu" << endl ;
        cout << "3. Faire une recherche parmi les chercheurs d'emploi" << endl ;
        cout << "4. Supprimer votre profil" << endl ;
        cout << "Votre choix ('q' pour revenir au menu principal) : ";
        cin >> choix_action_entreprise ;

        switch (choix_action_entreprise)
        {
            case '1':
                option_unknown = false ;
                //création de poste 
                cout << "création de poste (coming soon)" << endl ;
                break;

            case '2':
                option_unknown = false ;
                //suppression de poste 
                cout << "suppression de poste (coming soon)" << endl ;
                break;

            case '3':
                option_unknown = false ;
                //recherche parmis les chercheurs d'emplois 
                cout << "recherche (coming soon)" << endl ;
                break;
            
            case '4':
                option_unknown = false ;
                //suppression du profil 
                cout << "suppression (coming soon)" << endl ;
                break;
            
            case 'q':
                option_unknown = false ;
                break ;

            default:
                cout << "option inconnue veuillez recommencer" << endl ;
                break;
        }
    }

    for (int i = 0; i < 5; i++) {
        cout << endl ;
    }
    if (choix_action_entreprise == 'q') {
        interface() ;
    } else {
        menu_profil_entreprise(utilisateur_entreprise) ;
    }
    return ;
}

void menu_entreprise()
{
    Entreprise * current_user_entreprise = NULL;
    char choix_entreprise ;
    string nom_entreprise , cp_entreprise , mail_entreprise ;
    cout << "Bienvenue dans LuminIn !" << endl << endl;
    cout << "* Menu entreprise *" << endl ;
    cout << endl ;

    cout << "Veuillez indiquer le nom de votre entreprise : " ;
    cin >> nom_entreprise ;
    cout << "Veuillez indiquer le code postal de votre entreprise : " ;
    cin >> cp_entreprise ; 
    cout << "Veuillez indiquer l'adresse mail de votre entreprise : " ;
    cin >> mail_entreprise ;
    //recherche dans la BDD
    if (current_user_entreprise) {
        for (int i = 0; i < 5; i++) { //on va à la ligne pour changer de menu
            cout << endl ;
        }
        menu_profil_entreprise(current_user_entreprise) ;         
        
    } else {
        //création de profil
        for (int i = 0; i < 5; i++) { //on va à la ligne pour changer de menu
            cout << endl ;
        }
        cout << "voulez-vous  créer un profil ?" << endl ;
        cout << "1.Oui" << endl ;
        cout << "2.Non" << endl ;
        cout << "Votre choix :" ;
        do
        {
            cin >> choix_entreprise ;
            if (choix_entreprise != '1' && choix_entreprise != '2') {
                cout << "Choix inconnu veuillez recommencer" << endl ;
            }
        } while (choix_entreprise != '1' && choix_entreprise != '2');
        
        if (choix_entreprise == '1') {
            //appel de la fonction de création du profil
            for (int i = 0; i < 5; i++) { //on va à la ligne pour changer de menu
                cout << endl ;
            }
            menu_profil_entreprise(current_user_entreprise) ;  
        } else {
            for (int i = 0; i < 5; i++) { //on va à la ligne pour changer de menu
                cout << endl ;
            }
            interface() ;
        }
    }
    return ;
}

void menu_profil_chercheur(Personne * utilisateur_chercheur)
{
    char choix_action_chercheur ;
    bool option_unknown = true;
    cout << "Bienvenue dans LuminIn !" << endl << endl;
    cout << "* Menu chercheur d'emploi *" << endl ;
    cout << endl ;
    
    while (option_unknown) {
        cout << "Vous voulez :" << endl ; 
        cout << "1. modifier votre profil" << endl ;
        cout << "2. Transitionner votre profil vers un profil d'employé" << endl ;
        cout << "3. Effectuer une recherche parmis les postes à pourvoir" << endl ;
        cout << "4. Effectuer une recherche parmis vos anciens collègues" << endl ;
        cout << "5. Supprimer votre profil" << endl ;
        cout << "Votre choix ('q' pour revenir au menu principal) : " ;
        cin >> choix_action_chercheur ;

        switch (choix_action_chercheur)
        {
            case '1':
                option_unknown = false ;
                //modif de profil
                cout << "modif de profil (coming soon)" << endl ;
                break;

            case '2':
                option_unknown = false ;
                //transition profil
                cout << "transition de profil (coming soon)" << endl ; 
                break;

            case '3':
                option_unknown = false ;
                //recherche de postes
                cout << "recherche de posts (coming soon)" << endl ;
                break;

            case '4':
                option_unknown = false ;
                //recherche parmis les anciens collègues
                cout << "recherche parmis les anciens collègues (coming soon)" << endl ;
                break;
            
            case '5':
                option_unknown = false ;
                //suppression du profil 
                cout << "suppression du profil(coming soon)" << endl ;
                break;
            
            case 'q':
                option_unknown = false ;
                break ;

            default:
                cout << "option inconnue veuillez recommencer" << endl ;
                break;
        }
    }

    for (int i = 0; i < 5; i++) {
        cout << endl ;
    }
    if (choix_action_chercheur == 'q') { //retour au menu principal
        interface() ;
    } else {
        menu_profil_chercheur(utilisateur_chercheur) ;
    }
    return ;
}

void menu_chercheur()
{
    Personne * current_user_chercheur = NULL;
    char choix_chercheur ;
    string nom_chercheur , prenom_chercheur , cp_chercheur , mail_chercheur ;
    cout << "Bienvenue dans LuminIn !" << endl << endl;
    cout << "* Menu chercheur d'emploi *" << endl ;
    cout << endl ;

    cout << "Veuillez indiquer votre nom : " ;
    cin >> nom_chercheur ;
    cout << "Veuillez indiquer votre prénom : " ;
    cin >> prenom_chercheur ;
    cout << "Veuillez indiquer votre code postal : " ; 
    cin >> cp_chercheur ;
    cout << "Veuillez indiquer votre adresse mail : " ;
    cin >> mail_chercheur ;
    //recherche dans la BDD
    if (current_user_chercheur) {
        for (int i = 0; i < 5; i++) {
            cout << endl ;
        }
        menu_profil_chercheur(current_user_chercheur) ;      
        
    } else {
        //création de profil
        for (int i = 0; i < 5; i++) { //on va à la ligne pour changer de menu
            cout << endl ;
        }
        cout << "voulez-vous  créer un profil ?" << endl ;
        cout << "1.Oui" << endl ;
        cout << "2.Non" << endl ;
        cout << "Votre choix : " ;
        do
        {
            cin >> choix_chercheur ;
            if (choix_chercheur != '1' && choix_chercheur != '2') {
                cout << "Choix inconnu veuillez recommencer" << endl ;
            }
        } while (choix_chercheur != '1' && choix_chercheur != '2');
        
        if (choix_chercheur == '1') {
            //appel de la fonction de création du profil
            for (int i = 0; i < 5; i++) {       //on va à la ligne pour changer de menu
                cout << endl ;
            }
            menu_profil_chercheur(current_user_chercheur) ;   
        } else {
            for (int i = 0; i < 5; i++) {
                cout << endl ;
            }
            interface() ;
        }
    }
    return ; 
}

void menu_profil_employe(Personne * utilisateur_employe)
{
    char choix_action_employe ;
    bool option_unknown = true;
    cout << "Bienvenue dans LuminIn !" << endl << endl;
    cout << "* Menu employé *" << endl ;
    cout << endl ;
    
    while (option_unknown) {
        cout << "Vous voulez :" << endl ; 
        cout << "1. modifier votre profil" << endl ;
        cout << "2. Transitionner votre profil vers un profil de chercheur d'emploi" << endl ;
        cout << "3. Effectuer une recherche parmis les postes à pourvoir" << endl ;
        cout << "4. Effectuer une recherche parmis vos anciens collègues" << endl ;
        cout << "5. Supprimer votre profil" << endl ;
        cout << "Votre choix ('q' pour revenir au menu principal) : " ;
        cin >> choix_action_employe ;

        switch (choix_action_employe)
        {
            case '1':
                option_unknown = false ;
                //modif de profil
                cout << "modif de profil (coming soon)" << endl ;
                break;

            case '2':
                option_unknown = false ;
                //transition profil
                cout << "transition de profil (coming soon)" << endl ; 
                break;

            case '3':
                option_unknown = false ;
                //recherche de postes
                cout << "recherche de posts (coming soon)" << endl ;
                break;

            case '4':
                option_unknown = false ;
                //recherche parmis les anciens collègues
                cout << "recherche parmis les anciens collègues (coming soon)" << endl ;
                break;
            
            case '5':
                option_unknown = false ;
                //suppression du profil 
                cout << "suppression du profil(coming soon)" << endl ;
                break;
            
            case 'q':
                option_unknown = false ;
                break;
            default:
                cout << "option inconnue veuillez recommencer" << endl ;
                break;
        }
    }

    for (int i = 0; i < 5; i++) {
        cout << endl ;
    }
    if (choix_action_employe == 'q') {
        interface() ;
    } else {
        menu_profil_employe(utilisateur_employe) ;
    }
    return ;
}

void menu_employe()
{
    Personne * current_user_employe = NULL ;
    char choix_employe ;
    string nom_employe , prenom_employe , cp_employe , mail_employe , entreprise_employe ;
    cout << "Bienvenue dans LuminIn !" << endl << endl;
    cout << "* Menu employé *" << endl ;
    cout << endl ;

    cout << "Veuillez indiquer votre nom : " ;
    cin >> nom_employe ;
    cout << "Veuillez indiquer votre prénom : " ;
    cin >> prenom_employe ;
    cout << "Veuillez indiquer votre code postal : " ; 
    cin >> cp_employe ;
    cout << "Veuillez indiquer votre adresse mail : " ;
    cin >> mail_employe ;
    cout << "Veuillez indiquer votre entreprise : " ;
    cin >> entreprise_employe ;
    //recherche dans la BDD
    if (current_user_employe) {
        for (int i = 0; i < 5; i++) {
            cout << endl ;
        }
        menu_profil_employe(current_user_employe) ;       
        
    } else {
        //création de profil
        for (int i = 0; i < 5; i++) {
            cout << endl ;
        }
        cout << "voulez-vous  créer un profil ?" << endl ;
        cout << "1.Oui" << endl ;
        cout << "2.Non" << endl ;
        cout << "Votre choix : " ;
        do
        {
            cin >> choix_employe ;
            if (choix_employe != '1' && choix_employe != '2') {
                cout << "Choix inconnu veuillez recommencer" << endl ;
            }
        } while (choix_employe != '1' && choix_employe != '2');
        
        if (choix_employe == '1') {
            //appel de la fonction de création du profil
            for (int i = 0; i < 5; i++) {
                cout << endl ;
            }
            menu_profil_employe(current_user_employe) ; 
        } else {
            for (int i = 0; i < 5; i++) {
                cout << endl ;
            }
            interface() ;
        }
    }
    return ; 
}

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
        menu_entreprise() ;
    } else if (choix == "2") {
        menu_employe() ;
    } else if (choix == "3") {
        menu_chercheur() ;
    }
    return 0 ;
}