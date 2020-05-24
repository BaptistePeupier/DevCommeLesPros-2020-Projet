///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Projet DCLP                                                                                                   //
//                                                                                                               //
// menu_principal de l'application                                                                               //
//                                                                                                               //
// PEUPIER Baptiste MASSELOT Nicolas                                                                             //
// Cree le 18/05/2020, modifié le 21/05/2020                                                                     //
//                                                                                                               //
// Polytech Marseille, informatique 3A                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "interface.h"

extern Personne * EmployesListe ;
extern Personne * ChercheursListe ;
extern Entreprise * EntrepriseListe ;

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

//fonction de vérification des saisies
bool saisie_valide(string saisie) 
{
    if (regex_match(saisie, regex("[^,;]+"))) 
        return true;

    return false;
}

//fonction demandant à l'utilisateur de continuer
void continuer()
{
    cout << "appuyez sur une touche pour continuer ..." << endl ;
    cin.get() ;
    cin.get() ;
    system("clear") ;
}

//menu confirmation suppression de profil
bool menu_supp_profil(Entreprise *utilisateur_entreprise, Personne * utilisateur) 
{
    int confirmation_ans ;
    bool option_inconnue = true , profil_supprime ;

    system("clear") ;
    cout << "Bienvenue dans LuminIn !" << endl << endl;
    if (utilisateur) {
        if (utilisateur->EntrepriseActuelle()) {
            cout << "* Menu employé *" << endl ;
        } else {
            cout << "* Menu chercheur d'emploi *" << endl ;
        }
    } else if (utilisateur_entreprise) {
        cout << "* Menu entreprise *" << endl ;
    } else {
        return false ;
    }
    
    cout << endl ;
    
    while (option_inconnue)
    {
        cout << "Etes-vous sûr de supprimer votre profil ?" << endl ;
        cout << "1. Oui" << endl ;
        cout << "2. Non" << endl ;
        cout << endl ;
        cout << "Votre choix : " ;
        cin >> confirmation_ans ;
        cout << endl ;

        switch (confirmation_ans)
        {
            case 1:
                
                if (utilisateur) {
                    //appel de la fonction de suppression du profil de personne
                } else if (utilisateur_entreprise) {
                    //appel de la fonction de suppression du profil d'entreprise
                }
                cout << "Profil supprimé avec succès" << endl ;
                option_inconnue = false ;
                profil_supprime = true ;
                break;
            
            case 2:
                cout << "retour en arrière" << endl ;
                option_inconnue = false ;
                profil_supprime = false ;
                break ;

            default:
                cout << "option inconnue veuillez recommencer" << endl ;
                break;
        }
    }
    continuer() ;
    return profil_supprime;
}

// Retourne une personne présente dans une liste de donnée (des employes ou des chercheur)
// L'identification se fait par l'adresse mail
Personne * saisie_personne()
{
    string nom,prenom,cp,mail ;
    bool valid_input, find ;
    Personne *tmpP = NULL ;

    do
    {
        cout << "Veuillez indiquer le nom : " ;
        cin >> nom ;
        valid_input = saisie_valide(nom) ;
        if (!valid_input) {
            cout << "Nom invalide" << endl << endl ;
        } 
        
    } while (!valid_input);

    do
    {
        cout << "Veuillez indiquer le prénom : " ;
        cin >> prenom ;
        valid_input = saisie_valide(prenom) ;
        if (!valid_input) {
            cout << "Prénom invalide" << endl << endl ;
        } 
        
    } while (!valid_input);
    
    do
    {
        cout << "Veuillez indiquer le code postal : " ; 
        cin >> cp ;
        valid_input = cp_valide(cp) ; 
        if (!valid_input) {
            cout << "Code postal invalide" << endl << endl ;
        }
    } while (!valid_input);

    do {
        cout << "Veuillez indiquer  l'adresse mail : " ;
        cin >> mail ;
        valid_input = email_valide(mail) ;
        if (!valid_input) {
            cout << "address mail invalide" << endl << endl ;
        }
        
    } while (!valid_input);
    //recherche dans les base de données
    find = false ;
    tmpP = EmployesListe ;
    while(tmpP && !find){
        if (tmpP->mail() == mail) find = true ;
        tmpP = tmpP->nextP() ;
    }
    if(!find){
            tmpP = ChercheursListe ;
        while(tmpP && !find){
            if (tmpP->mail() == mail) find = true ;
            tmpP = tmpP->nextP() ;
        }
    }

    return tmpP ;
}

//menu de modification de profil
void modif_profil_pers(Personne *current_user)
{
    char choix_modif , choix_ajout;
    bool option_inconnue = true ,  end_saisie = false , valid_input ;
    string new_skill , nouv_cp , nouv_entreprise ;
    Personne * nouv_collegue;

    system("clear") ;
    cout << "Bienvenue dans LuminIn !" << endl << endl;
   if (current_user) {
        if (current_user->EntrepriseActuelle()) {
            cout << "* Menu employé *" << endl ;
        } else {
            cout << "* Menu chercheur d'emploi *" << endl ;
        }
    } else {
        return ;
    }
    
    while (option_inconnue) {
        cout << "Vous voulez :" << endl ;
        cout << "1.Ajouter des compétences" << endl;
        cout << "2.Ajouter un(e) ancien(ne) collègue de travail" << endl ;
        cout << "3.Modifier le code postal" << endl ;
        if (current_user->EntrepriseActuelle()) {
            cout << "4.Modifier l'entreprise actuelle" << endl ;
        }
        cout << "Votre choix ('q' pour revenir en arrière) : ";
        cin >> choix_modif ;

        switch (choix_modif)
        {
            case '1':
                while (!end_saisie)
                {
                    do
                    {
                        cout << "Veuillez entrer les compétences que vous souhaitez ajouter" << endl ;
                        cin >> new_skill ;
                        valid_input = saisie_valide(new_skill) ;
                        if (!valid_input) {             
                            cout << "Label entré invalide" << endl << endl ;
                        } 
                        //vérifier si la compétence est pas déjà dans la liste
                    } while (!valid_input);
                    //appel de l'ajout de compétence à la personne
                    option_inconnue = true ;
                    while (option_inconnue)
                    {
                         cout << "Voulez vous ajouter d'autres compétences ?" << endl ;
                        cout << "1. Oui" << endl ;
                        cout << "2. Non" << endl ;
                        cout << endl ;
                        cout << "Votre choix : " ;
                        cin >> choix_ajout ;
                        if (choix_ajout == '1') {
                            option_inconnue = false ;
                            continuer() ;
                        } else if (choix_ajout == '2') {
                            option_inconnue = false ;
                            end_saisie = true ;
                        } else {
                            cout << "option inconnue veuillez recommencer" << endl ;
                        }
                    }
                }
                option_inconnue = false ;
                
                break;

            case '2':
                while (!end_saisie)
                {
                    nouv_collegue = saisie_personne() ;
                    if (nouv_collegue)
                    {
                        //appel de l'ajout d'ancien collègue
                    } else{
                        cout << "La personne que vous recherchez est introuvable" << endl ;
                        continuer() ;
                    }
                    option_inconnue = true ;
                    while (option_inconnue)
                    {
                        cout << "Voulez vous ajouter d'autres collègues ?" << endl ;
                        cout << "1. Oui" << endl ;
                        cout << "2. Non" << endl ;
                        cout << endl ;
                        cout << "Votre choix : " ;
                        cin >> choix_ajout ;
                        if (choix_ajout == '1') {
                            option_inconnue = false ;
                            continuer() ;
                        } else if (choix_ajout == '2') {
                            option_inconnue = false ;
                            end_saisie = true ;
                        } else {
                            cout << "option inconnue veuillez recommencer" << endl ;
                        }
                    }
                }
                option_inconnue = false ;
                break;
            
            case '3':
                do
                {
                    cout << "Veuillez indiquer votre nouveau : " ;
                    cin >> nouv_cp ;
                    valid_input = cp_valide(nouv_cp) ;
                    if (!valid_input) {
                        cout << "Code postal invalide" << endl << endl ;
                    } 
                } while (!valid_input);
                break;
            
            case '4':
                if (current_user->EntrepriseActuelle()) {
                    do
                    {
                        cout << "Veuillez indiquer votre nouvelle entreprise : " ;
                        cin >> nouv_entreprise ;
                        valid_input = saisie_valide(nouv_entreprise) ;
                        if (!valid_input) {
                            cout << "Nom d'entreprise invalide" << endl << endl ;
                        } 
                        
                    } while (!valid_input);
                    //appel de la modification d'entreprise de la classe personne
                }
                break;

            case 'q':
                option_inconnue = false ;
                break;

            default:
                cout << "option inconnue veuillez recommencer" << endl ;
                break;
        }
    }
    
    continuer() ;
    return ; 

}

//menu de transition de profil
bool menu_transition_pers(Personne * current_user,string nouv_entreprise)
{
    int confirmation_ans ;
    bool option_inconnue = true , succes_transition ;

    system("clear") ;
    cout << "Bienvenue dans LuminIn !" << endl << endl;
    if (current_user) {
        if (current_user->EntrepriseActuelle()) {
            cout << "* Menu employé *" << endl ;
        } else {
            cout << "* Menu chercheur d'emploi *" << endl ;
        }
    } else {
        return false ;
    }
    
    cout << endl ;
    
    while (option_inconnue)
    {
        if (current_user->EntrepriseActuelle()) {
            cout << "Etes-vous sûr de passer au statut 'chercheur d'emploi' ?" << endl ;
        }else {
            cout << "Etes-vous sûr de passer au statut 'employé' ?" << endl ;
        }
        cout << "1. Oui" << endl ;
        cout << "2. Non" << endl ;
        cout << endl ;
        cout << "Votre choix : " ;
        cin >> confirmation_ans ;
        cout << endl ;

        switch (confirmation_ans)
        {
            case 1:
                
                if (current_user) {
                    if ( nouv_entreprise == "no entreprise here" && current_user->EntrepriseActuelle()) {
                        //appel de la fonction de transition du profil vers le status chercheur d'emploi
                    } else {
                        //appel de la fonction de transition du profil vers le statut employé
                    }
                }
                cout << "Transition effectuée avec succès" << endl ;
                option_inconnue = false ;
                succes_transition = true ;
                break;
            
            case 2:
                cout << "retour en arrière" << endl ;
                option_inconnue = false ;
                succes_transition = false ;
                break ;

            default:
                cout << "option inconnue veuillez recommencer" << endl ;
                break;
        }
    }
    continuer() ;
    return succes_transition;
}

//menu permettant de sélectionner le type de recherche parmis les chercheurs d'emploi
void type_recherche_entreprise()
{
    char choix_type ;
    bool option_inconnue = true , valid_input;
    string cp_chercheurs ;

    system("clear") ;
    cout << "Bienvenue dans LuminIn !" << endl << endl;
    cout << "* Menu entreprise *" << endl ;
    cout << endl ;

    while (option_inconnue)
    {
        cout << "Vous voulez :" << endl ;
        cout << "1.Effectuer une recherche des chercheurs d'emploi" << endl ;
        cout << "2.Effectuer une recherche des chercheurs d'emploi avec un code postal précis " << endl ;
        cout << endl ;
        cout << "Votre choix ('q' pour revenir en arrière) : ";
        cin >> choix_type ;
        cout << endl ;

        switch (choix_type)
        {
            case '1':
                option_inconnue = false ;
                cout << "Veuillez saisir les compétences recherchées" << endl ;
                //appel de la fonction de saisie des compétence dans une liste
                
                cout << "Voici le résultat de la recherche :" << endl << endl;
                //appel de la recherche selon les compétences
                break;

            case '2':
                option_inconnue = false ;
                cout << "Veuillez saisir les compétences recherchées" << endl ;
                //appel de la fonction de saisie des compétence dans une liste
                do
                {
                    cout << "Veuillez entrer le code postal que vous recherchez :" ;
                    cin >> cp_chercheurs ;
                    valid_input = cp_valide(cp_chercheurs) ; 
                    if (!valid_input) {
                        cout << "Code postal invalide" << endl << endl ;
                    }
                } while (!valid_input);

                cout << "Voici le résultat de la recherche :" << endl << endl;
                //appel de la recherche selon les compétences et le code postal
                break;

            case 'q':
                option_inconnue = false ;
                break;

            default:
                cout << "option inconnue veuillez recommencer" << endl ;
                break;
        }
    }
    continuer() ;
    return ;
}

//menu de recherche de postes
void recherche_poste_pers(Personne *current_user)
{
    char choix_type_recherche ;
    bool option_inconnue = true ;

    system("clear") ;
    cout << "Bienvenue dans LuminIn !" << endl << endl;
    if (current_user) {
        if (current_user->EntrepriseActuelle()) {
            cout << "* Menu employé *" << endl ;
        } else {
            cout << "* Menu chercheur d'emploi *" << endl ;
        }
    } else {
        return ;
    }
    
    while (option_inconnue) {
        cout << "Vous voulez :" << endl ; 
        cout << "1. Rechercher les postes à pourvoir correspondant à vos compétences" << endl ;
        cout << "2. Rechercher les postes à pourvoir correspondant à vos compétences proche de chez vous" << endl ;
        cout << endl ;
        cout << "Votre choix ('q' pour revenir en arrière) : ";
        cin >> choix_type_recherche ;

        switch (choix_type_recherche)
        {
            case '1':
                option_inconnue = false ;
                cout << "Voici les postes à pourvoir correspondant à vos compétences" << endl ;
                //appel de la recherche de poste par compétence
                break;

            case '2':
                option_inconnue = false ;
                cout << "Voici les postes à pourvoir correspondant à vos compétences proche de chez vous :" << endl ;
                //appel de la recherche de poste par compétence et code postal
                break;

            case 'q':
                cout << "retour en arrière " << endl ;
                option_inconnue = false ;
                break;

            default:
                cout << "option inconnue veuillez recommencer" << endl ;
                break;
        }
    }

    continuer() ;
    return ;
    
}

//menu recherche parmis les anciens collègues
void recherche_collegue_pers(Personne *current_user)
{
    char choix_type_recherche ;
    bool option_inconnue = true , valid_input;
    string entreprise_collegue ;

    system("clear") ;
    cout << "Bienvenue dans LuminIn !" << endl << endl;
   /* if (current_user) {
        if (current_user->EntrepriseActuelle()) {
            cout << "* Menu employé *" << endl ;
        } else {*/
            cout << "* Menu chercheur d'emploi *" << endl ;
        /*}
    } else {
        return ;
    }*/
    
    while (option_inconnue) {
        cout << "Vous voulez :" << endl ; 
        cout << "1. Rechercher les anciens collègues employés dans une entreprise particulière" << endl ;
        cout << "2. Rechercher les anciens collègues employés dans les entreprises recherchant certaines compétences" << endl ;
        cout << endl ;
        cout << "Votre choix ('q' pour revenir en arrière) : ";
        cin >> choix_type_recherche ;

        switch (choix_type_recherche)
        {
            case '1':
                option_inconnue = false ;
                do
                    {
                        cout << "Veuillez indiquer l'entreprise recherchée : " ;
                        cin >> entreprise_collegue ;
                        valid_input = saisie_valide(entreprise_collegue) ;
                        if (!valid_input) {
                            cout << "Nom d'entreprise invalide" << endl << endl ;
                        } 
                        
                    } while (!valid_input);
                cout << "Voici les anciens collègues employés dans l'entreprise " << entreprise_collegue << endl ;
                //appel de la recherche d'anciens collègues dans une entreprise
                break;

            case '2':
                option_inconnue = false ;
                cout << "Veuillez entrer les compétence à rechercher :" << endl ;
                //appel de la saisie de compétence dans une liste 
                cout << "Voici les anciens collègues employés dans les entreprises recherchant les compétences saisies :" << endl ;
                //appel de la recherche de poste par compétence et code postal
                break;

            case 'q':
                cout << "retour en arrière " << endl ;
                option_inconnue = false ;
                break;

            default:
                cout << "option inconnue veuillez recommencer" << endl ;
                break;
        }
    }

    continuer() ;
    return ;
    
}

//affichage du menu correspondant au profil d'entreprise
void menu_entreprise(Entreprise * utilisateur_entreprise)
{
    char choix_action_entreprise ;
    bool option_unknown = true;
    bool profil_deleted , valid_input;
    string titre_poste ;

    system("clear") ;
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
                do
                {
                    cout << "Veuillez entrer le titre du poste à ajouter : ";
                    cin >> titre_poste ;
                    valid_input = saisie_valide(titre_poste) ;
                    if (!valid_input) {             
                        cout << "Titre entré invalide" << endl << endl ;
                    } 
                    //vérifier si le titre du poste est déjà dans la base de données pour l'entreprise en question
                } while (!valid_input);
                cout << "Veuillez saisir les compétences recherchées pour ce poste : " << endl ;
                //appel de la fonction permettant d'entrer des compétences dans une liste
                //ajout du poste à la liste des postes de l'entreprise
                cout << "poste ajouté avec succès" << endl ;
                continuer() ;
                break;

            case '2':
                option_unknown = false ;
                do
                {
                    cout << "Veuillez entrer le titre du poste à supprimer : " ;
                    cin >> titre_poste ;
                    valid_input = saisie_valide(titre_poste) ;
                    if (!valid_input) {
                        cout << "Titre entré invalide" << endl << endl ;
                    } 
                } while (!valid_input);
                //appel de la fonction de suppression de poste
                cout << "suppression du poste" << endl ;
                continuer() ;
                break;

            case '3':
                option_unknown = false ;
                type_recherche_entreprise() ;
                break;
            
            case '4':
                option_unknown = false ;
                profil_deleted = menu_supp_profil(utilisateur_entreprise, NULL) ;
                break;
            
            case 'q':
                option_unknown = false ;
                cout << "retour au menu principal" << endl ;
                continuer() ;
                break ;

            default:
                cout << "option inconnue veuillez recommencer" << endl ;
                break;
        }
    }

    system("clear") ;
    if (choix_action_entreprise == 'q' || profil_deleted) {
        menu_principal() ;
    } else {
        menu_entreprise(utilisateur_entreprise) ;
    }
    return ;
}

//connexion des entreprises
void connexion_entreprise()
{
    Entreprise * current_user_entreprise = NULL, *tmpE ;
    char choix_entreprise ;
    bool valid_input, find ;
    string nom_entreprise , cp_entreprise , mail_entreprise ;

    system("clear") ;
    cout << "Bienvenue dans LuminIn !" << endl << endl;
    cout << "* Menu entreprise *" << endl ;
    cout << endl ;

    do {
        cout << "Veuillez indiquer l'adresse mail de votre entreprise : " ;
        cin >> mail_entreprise ;
        valid_input = email_valide(mail_entreprise) ;
        if (!valid_input) {
            cout << "address email invalide" << endl << endl ;
        }
        
    } while (!valid_input);
    // Recherche dans la BDD du profil de l'utilisateur
    find = false ;
    tmpE = EntrepriseListe ;
    while(tmpE && !find){
        if(tmpE->mail() == mail_entreprise){
            find = true ;
            current_user_entreprise = tmpE ;
        }
        tmpE = tmpE->next() ;
    }
    if (current_user_entreprise) {
        system("clear") ;
        menu_entreprise(current_user_entreprise) ;         
        
    } else {
        // Création de profil
        do
        {
            system("clear") ;
            cout << "Votre profil est introuvable , voulez-vous créer un profil ?" << endl ;
            cout << "1.Oui" << endl ;
            cout << "2.Non" << endl ;
            cout << "Votre choix :" ;
            cin >> choix_entreprise ;
            if (choix_entreprise != '1' && choix_entreprise != '2') {
                cout << "Choix inconnu veuillez recommencer" << endl ;
            }
        } while (choix_entreprise != '1' && choix_entreprise != '2');
        
        if (choix_entreprise == '1') {
            do
            {
                cout << "Veuillez indiquer le nom de votre entreprise : " ;
                cin >> nom_entreprise ;
                valid_input = saisie_valide(nom_entreprise) ;
                if (!valid_input) {
                    cout << "Nom invalide" << endl << endl ;
                } 
                
            } while (!valid_input);

            do
            {
                cout << "Veuillez indiquer le code postal de votre entreprise : " ;
                cin >> cp_entreprise ;
                valid_input = cp_valide(cp_entreprise) ;
                if (!valid_input) {
                    cout << "Code postal invalide" << endl << endl ;
                } 
            } while (!valid_input);

            if(EntrepriseListe){
                EntrepriseListe->addEntreprise(nom_entreprise, cp_entreprise, mail_entreprise) ;
            }else{                  // Si c'est la première entreprise créée
                EntrepriseListe = new Entreprise(1, nom_entreprise, cp_entreprise, mail_entreprise) ;
                EntrepriseListe->MAJDBEntreprise() ;
            }

            system("clear") ;
            menu_entreprise(current_user_entreprise) ;  
        } else {
            system("clear") ;
            menu_principal() ;
        }
    }

    return ;
}

//affichage du menu correspondant au profil de chercheur d'emploi
void menu_chercheur(Personne * utilisateur_chercheur)
{
    char choix_action_chercheur ;
    bool option_unknown = true , deleted_profil , transition_success , valid_input;
    string nouv_entreprise ;

    system("clear") ;
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
                modif_profil_pers(utilisateur_chercheur) ;
                break;

            case '2':
                option_unknown = false ;
                do
                {
                    cout << "Veuillez indiquer votre nouvelle entreprise : " ;
                    cin >> nouv_entreprise ;
                    valid_input = saisie_valide(nouv_entreprise) ;
                    if (!valid_input) {
                        cout << "Nom d'entreprise invalide" << endl << endl ;
                    } 
                    
                } while (!valid_input);
                transition_success = menu_transition_pers(utilisateur_chercheur,nouv_entreprise) ; 
                break;

            case '3':
                option_unknown = false ;
                recherche_poste_pers(utilisateur_chercheur) ;
                break;

            case '4':
                option_unknown = false ;
                recherche_collegue_pers(utilisateur_chercheur) ;
                break;
            
            case '5':
                option_unknown = false ;
                //suppression du profil 
                deleted_profil = menu_supp_profil(NULL, utilisateur_chercheur) ;
                break;
            
            case 'q':
                option_unknown = false ;
                break ;

            default:
                cout << "option inconnue veuillez recommencer" << endl ;
                break;
        }
    }

    system("clear") ;
    if (choix_action_chercheur == 'q' || deleted_profil) {
        menu_principal() ;
    }else if (transition_success) {
        menu_employe(utilisateur_chercheur) ;
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

    system("clear") ;
    cout << "Bienvenue dans LuminIn !" << endl << endl;
    cout << "* Menu chercheur d'emploi *" << endl ;
    cout << endl ;

    do
    {
        cout << "Veuillez indiquer votre nom : " ;
        cin >> nom_chercheur ;
        valid_input = saisie_valide(nom_chercheur) ;
        if (!valid_input) {
            cout << "Nom invalide" << endl << endl ;
        } 
        
    } while (!valid_input);

    do
    {
        cout << "Veuillez indiquer votre prénom : " ;
        cin >> prenom_chercheur ;
        valid_input = saisie_valide(prenom_chercheur) ;
        if (!valid_input) {
            cout << "Prénom invalide" << endl << endl ;
        } 
        
    } while (!valid_input);
    
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
        system("clear") ;
        menu_chercheur(current_user_chercheur) ;      
        
    } else {
        //création de profil
        do
        {
            system("clear") ;
            cout << "Votre profil est introuvable , voulez-vous créer un profil ?" << endl ;
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
            system("clear") ;
            menu_chercheur(current_user_chercheur) ;   
        } else {
            
            menu_principal() ;
        }
    }
    return ; 
}

//affichage du menu correspondant au profil d'employé
void menu_employe(Personne * utilisateur_employe)
{
    char choix_action_employe ;
    bool option_unknown = true , deleted_profil , transition_success;

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
                modif_profil_pers(utilisateur_employe) ;
                break;

            case '2':
                option_unknown = false ;
                transition_success = menu_transition_pers(utilisateur_employe) ; 
                break;

            case '3':
                option_unknown = false ;
                recherche_poste_pers(utilisateur_employe) ;
                break;

            case '4':
                option_unknown = false ;
                recherche_collegue_pers(utilisateur_employe) ;
                break;
            
            case '5':
                option_unknown = false ;
                deleted_profil = menu_supp_profil(NULL, utilisateur_employe) ;
                continuer() ;
                break;
            
            case 'q':
                option_unknown = false ;
                break;
            default:
                cout << "option inconnue veuillez recommencer" << endl ;
                break;
        }
    }

    system("clear") ;
    if (choix_action_employe == 'q' || deleted_profil) {
        menu_principal() ;
    }else if (transition_success) {
        menu_chercheur(utilisateur_employe) ;
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

    system("clear") ;
    cout << "Bienvenue dans LuminIn !" << endl << endl;
    cout << "* Menu employé *" << endl ;
    cout << endl ;


    do
    {
        cout << "Veuillez indiquer votre nom : " ;
        cin >> nom_employe ;
        valid_input = saisie_valide(nom_employe) ;
        if (!valid_input) {
            cout << "Nom invalide" << endl << endl ;
        } 
        
    } while (!valid_input);

    do
    {
        cout << "Veuillez indiquer votre prénom : " ;
        cin >> prenom_employe ;
        valid_input = saisie_valide(prenom_employe) ;
        if (!valid_input) {
            cout << "Prénom invalide" << endl << endl ;
        } 
        
    } while (!valid_input);

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

    

    do
    {
        cout << "Veuillez indiquer votre entreprise : " ;
        cin >> entreprise_employe ;
        valid_input = saisie_valide(entreprise_employe) ;
        if (!valid_input) {
            cout << "Nom d'entreprise invalide" << endl << endl ;
        } 
        
    } while (!valid_input);
    //fonction recherche dans la BDD 
    if (current_user_employe) {
        system("clear") ;
        menu_employe(current_user_employe) ;       
        
    } else {
        //création de profil 
        //attention à l'entreprise vérifier qu'elle existe
        do
        {
            system("clear") ;
            cout << "Votre profil est introuvable , voulez-vous créer un profil ?" << endl ;
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
            system("clear") ;
            menu_employe(current_user_employe) ; 
        } else {
            system("clear") ;
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

    system("clear") ; 
    cout << "* Menu principal *" << endl ;
    cout << endl ;

    cout << "Vous êtes :" << endl ;
    cout << "1.Une entreprise" << endl ;
    cout << "2.Un employé" << endl ;
    cout << "3.A la recherche d'un emploi" << endl ;
    cout << endl ;
    cout << "Votre choix ('q' pour quitter) : " ;
    
    do
    {
        cin >> choix ;
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