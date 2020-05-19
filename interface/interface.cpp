///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// menu_principal de l'application                                                                                    //
//                                                                                                               //
// PEUPIER Baptiste MASSELOT Nicolas                                                                             //
// Cree le 18/05/2020, modifié le 18/05/2020                                                                     //
//                                                                                                               //
// Polytech Marseille, informatique 3A                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "interface.h"

//fonction de vérification de l'addresse mail entrée
bool email_valide(string email)
{
    if (regex_match(email, regex("([a-z]+)([_.a-z0-9]*)([a-z0-9]+)(@)([a-z]+)([.a-z]+)([a-z]+)"))) 
        return true;

    return false;
}

//fonction de vérification du code postal entré
bool cp_valide(string code_postal)
{
    if (regex_match(code_postal, regex("[0-9]*"))) 
        return true;

    return false;
}

//affichage du menu correspondant au profil d'entreprise
void menu_entreprise(Entreprise * utilisateur_entreprise)
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
        cout << endl ;
        cout << "Votre choix ('q' pour revenir au menu principal) : ";
        cin >> choix_action_entreprise ;
        cout << endl ;

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
        menu_principal() ;
    } else {
        menu_entreprise(utilisateur_entreprise) ;
    }
    return ;
}

//connexion des entreprises
void connexion_entreprise()
{
    Entreprise * current_user_entreprise = NULL;
    char choix_entreprise ;
    bool valid_input;
    string nom_entreprise , cp_entreprise , mail_entreprise ;
    cout << "Bienvenue dans LuminIn !" << endl << endl;
    cout << "* Menu entreprise *" << endl ;
    cout << endl ;

    cout << "Veuillez indiquer le nom de votre entreprise : " ;
    cin >> nom_entreprise ;
    do
    {
        cout << "Veuillez indiquer le code postal de votre entreprise : " ;
        cin >> cp_entreprise ;
        valid_input = cp_valide(cp_entreprise) ;
        if (!valid_input) {
            cout << "Code postal invalide" << endl << endl ;
        } 
    } while (!valid_input);

    do {
        cout << "Veuillez indiquer l'adresse mail de votre entreprise : " ;
        cin >> mail_entreprise ;
        valid_input = email_valide(mail_entreprise) ;
        if (!valid_input) {
            cout << "address email invalide" << endl << endl ;
        }
        
    } while (!valid_input);
    //recherche dans la BDD du profil de l'utilisateur
    if (current_user_entreprise) {
        for (int i = 0; i < 5; i++) { //on va à la ligne pour changer de menu
            cout << endl ;
        }
        menu_entreprise(current_user_entreprise) ;         
        
    } else {
        //création de profil
        do
        {
            for (int i = 0; i < 5; i++) { //on va à la ligne pour changer de menu
                cout << endl ;
            }
            cout << "voulez-vous  créer un profil ?" << endl ;
            cout << "1.Oui" << endl ;
            cout << "2.Non" << endl ;
            cout << "Votre choix :" ;
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
            menu_entreprise(current_user_entreprise) ;  
        } else {
            for (int i = 0; i < 5; i++) { //on va à la ligne pour changer de menu
                cout << endl ;
            }
            menu_principal() ;
        }
    }
    return ;
}

//affichage du menu correspondant au profil de chercheur d'emploi
void menu_chercheur(Personne * utilisateur_chercheur)
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
        cout << endl ;
        cout << "Votre choix ('q' pour revenir au menu principal) : " ;
        cin >> choix_action_chercheur ;
        cout << endl ;

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
        menu_principal() ;
    } else {
        menu_chercheur(utilisateur_chercheur) ;
    }
    return ;
}

//connexion des chercheurs d'emploi
void connexion_chercheur()
{
    Personne * current_user_chercheur = NULL;
    char choix_chercheur ;
    bool valid_input ;
    string nom_chercheur , prenom_chercheur , cp_chercheur , mail_chercheur ;
    cout << "Bienvenue dans LuminIn !" << endl << endl;
    cout << "* Menu chercheur d'emploi *" << endl ;
    cout << endl ;

    cout << "Veuillez indiquer votre nom : " ;
    cin >> nom_chercheur ;
    cout << "Veuillez indiquer votre prénom : " ;
    cin >> prenom_chercheur ;
    do
    {
        cout << "Veuillez indiquer votre code postal : " ; 
        cin >> cp_chercheur ;
        valid_input = cp_valide(cp_chercheur) ; 
        if (!valid_input) {
            cout << "Code postal invalide" << endl << endl ;
        }
    } while (!valid_input);

    do {
        cout << "Veuillez indiquer votre adresse mail : " ;
        cin >> mail_chercheur ;
        valid_input = email_valide(mail_chercheur) ;
        if (!valid_input) {
            cout << "address email invalide" << endl << endl ;
        }
        
    } while (!valid_input);
    //recherche dans la BDD du profil de l'utilisateur
    if (current_user_chercheur) {
        for (int i = 0; i < 5; i++) {
            cout << endl ;
        }
        menu_chercheur(current_user_chercheur) ;      
        
    } else {
        //création de profil
        do
        {
            for (int i = 0; i < 5; i++) { //on va à la ligne pour changer de menu
                cout << endl ;
            }
            cout << "voulez-vous  créer un profil ?" << endl ;
            cout << "1.Oui" << endl ;
            cout << "2.Non" << endl ;
            cout << "Votre choix : " ;
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
            menu_chercheur(current_user_chercheur) ;   
        } else {
            for (int i = 0; i < 5; i++) {
                cout << endl ;
            }
            menu_principal() ;
        }
    }
    return ; 
}

//affichage du menu correspondant au profil d'employé
void menu_employe(Personne * utilisateur_employe)
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
        cout << endl ;
        cout << "Votre choix ('q' pour revenir au menu principal) : " ;
        cin >> choix_action_employe ;
        cout << endl ;

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
        menu_principal() ;
    } else {
        menu_employe(utilisateur_employe) ;
    }
    return ;
}
//connexion des employés
void connexion_employe()
{
    Personne * current_user_employe = NULL ;
    char choix_employe ;
    bool valid_input ;
    string nom_employe , prenom_employe , cp_employe , mail_employe , entreprise_employe ;
    cout << "Bienvenue dans LuminIn !" << endl << endl;
    cout << "* Menu employé *" << endl ;
    cout << endl ;

    cout << "Veuillez indiquer votre nom : " ;
    cin >> nom_employe ;
    cout << "Veuillez indiquer votre prénom : " ;
    cin >> prenom_employe ;
    do
    {
        cout << "Veuillez indiquer votre code postal : " ; 
        cin >> cp_employe ;
        valid_input = cp_valide(cp_employe) ; 
        if (!valid_input) {
            cout << "Code postal invalide" << endl << endl ;
        }
    } while (!valid_input);


    do {
        cout << "Veuillez indiquer votre adresse mail : " ;
        cin >> mail_employe ;
        valid_input = email_valide(mail_employe) ;
        if (!valid_input) {
            cout << "address email invalide" << endl << endl ;
        }
        
    } while (!valid_input);

    cout << "Veuillez indiquer votre entreprise : " ;
    cin >> entreprise_employe ;
    //recherche dans la BDD
    if (current_user_employe) {
        for (int i = 0; i < 5; i++) {
            cout << endl ;
        }
        menu_employe(current_user_employe) ;       
        
    } else {
        //création de profil 
        //attention à l'entreprise vérifier qu'elle existe
        do
        {
            for (int i = 0; i < 5; i++) {
                cout << endl ;
            }
            cout << "voulez-vous  créer un profil ?" << endl ;
            cout << "1.Oui" << endl ;
            cout << "2.Non" << endl ;
            cout << "Votre choix : " ;
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
            menu_employe(current_user_employe) ; 
        } else {
            for (int i = 0; i < 5; i++) {
                cout << endl ;
            }
            menu_principal() ;
        }
    }
    return ; 
}

//affichage du menu principal
int menu_principal(void)
{
    char choix ;
    bool valid_input = false ;
    cout << "* Menu principal *" << endl ;
    cout << endl ;

    cout << "vous êtes :" << endl ;
    cout << "1.Une entreprise" << endl ;
    cout << "2.Un employé" << endl ;
    cout << "3.A la recherche d'un emploi" << endl ;
    cout << endl ;
    cout << "Votre choix ('q' pour quitter) : " ;
    cin >> choix ;
    
    do
    {
        switch (choix)
        {
        case '1':
            valid_input = true ;
            connexion_entreprise() ;
            break;
        
        case '2':
            valid_input = true ;
            connexion_employe() ;
            break;

        case '3':
            valid_input = true ;
            connexion_chercheur() ;
            break;

        case 'q':
            valid_input = true ;
            cout << endl ;
            cout << "-------------- Au revoir ------------"<< endl ;
            break;

        default:
            cout << "option inconnue" << endl ;
            break;
        }
    } while (!valid_input);
    
    
    
    
    return 0 ;
}