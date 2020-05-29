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

// Fonction permettant de générer le journal d'utilisation de l'application
// le nom de la fonction utilisée ainsi la valeur de ses arguments sont passées en paramètre dans des strings
void Logs(string fonction, string arguments)
{
    char time_s[100] ;
    time_t now = time(0) ;

    FILE * FichierLogs = fopen("logs.log", "a") ;
    strftime(time_s, 100, "%Y-%m-%d %H:%M:%S.000", localtime(&now)) ;
    if(arguments == "none") fprintf(FichierLogs, "[%s] %s appelée.\n", time_s, fonction.c_str()) ;
    else fprintf(FichierLogs, "[%s] %s appelée avec '%s' comme paramètre.\n", time_s, fonction.c_str(), arguments.c_str()) ;
    fclose(FichierLogs) ;

    return ;
}

//fonction de vérification de l'addresse mail entrée
bool email_valide(string email)
{
    const regex pattern_mail("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+") ;
    if (regex_match(email, pattern_mail)) 
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
                    Logs("deleteProfile", utilisateur->mail()) ;
                    utilisateur->deleteProfile(&EmployesListe,&ChercheursListe) ;
                } else if (utilisateur_entreprise) {
                    Logs("deleteProfileEntreprise", utilisateur_entreprise->mail()) ;
                    deleteProfileEntreprise(utilisateur_entreprise, &EntrepriseListe, &EmployesListe, &ChercheursListe) ;
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

//fonction de saisie d'une compétences
Competence * saisie_competence()
{
    Competence * liste_comp = NULL , *tmp_skill_list;
    string label_comp ;
    bool fin_saisie = false , unknown_ans, valid_input;
    string choix ;

    while (!fin_saisie)
    {
        unknown_ans = true ;
        do
        {
            cout << "Veuillez entrer les compétence dans la liste:" << endl ;
            cin >> label_comp ;
            valid_input = saisie_valide(label_comp) ;
            if (!valid_input) {             
                cout << "Label entré invalide" << endl << endl ;
            } else {
                tmp_skill_list = new Competence(label_comp) ;

                if (liste_comp && tmp_skill_list->IsInList(liste_comp)) {
                    valid_input = false ;
                    cout << "La compétence recherchée est déjà dans la liste" << endl << endl ; 
                    delete tmp_skill_list ;
                }
            }
            //vérifier si la compétence est pas déjà dans la liste
        } while (!valid_input);
        if (liste_comp) {
            liste_comp->AddCompetence(label_comp) ;
        }else {
            liste_comp = new Competence(label_comp) ;
        }
        while (unknown_ans) {
            cout << "voulez-vous ajouter d'autre compétences ? " << endl ;
            cout << "1.Oui" << endl ;
            cout << "2.Non" << endl ;
            cout << "Votre choix : " ;
            cin >> choix ;
            if (choix == "1") {
                fin_saisie = false ;
                unknown_ans = false ;
            } else if (choix == "2") {
                fin_saisie = true ;
                unknown_ans = false ;
            } else {
                cout << "choix inconnue " << endl ;
                unknown_ans = true ;
            }
        }
    }
    return liste_comp ;
}

//fonction de saisie pour la création de profil
Personne * saisie_personne(bool employe)
{
    string nom,prenom,cp,mail,entreprise_pers , choix_annulation ;
    bool valid_input ;
    Entreprise * tmp_ent ;
    Personne * resultat_saisie ;

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

    if (employe) {
        do {
            cout << "Veuillez indiquer  l'entreprise: " ;
            cin >> entreprise_pers ;
            valid_input = saisie_valide(entreprise_pers) ;
            if (!valid_input) {
                cout << "nom d'entreprise invalide" << endl << endl ;
            } else {
                tmp_ent = EntrepriseListe ;
                while (tmp_ent && tmp_ent->nom() != entreprise_pers) {
                    tmp_ent = tmp_ent->next() ;
                }
                if (!tmp_ent) {
                    
                    cout << "L'entreprise recherchée est introuvable" << endl << endl ;
                    cout << "Voulez vous rééssayer ?" << endl ;
                    cout << "1.Oui" << endl ;
                    cout << "2.Non" << endl ;
                    cout << "Votre choix : " ;
                    cin >> choix_annulation ;
                    if (choix_annulation == "1") {
                        valid_input = false ;
                    } else if (choix_annulation == "2") {
                        valid_input = true ;
                    }
                } else if(tmp_ent){
                    valid_input = true ;
                }
            }
        } while (!valid_input);

    }
    if (employe) {
        if (tmp_ent) {
             resultat_saisie = new Personne(1,nom,prenom,mail,cp,NULL,NULL,NULL,NULL,tmp_ent) ;
        } else {
            resultat_saisie = NULL ;
        }
    } else {
        resultat_saisie = new Personne(1,nom,prenom,mail,cp) ;
    }
    return resultat_saisie ;
}

//menu de modification de profil
void modif_profil_pers(Personne *current_user)
{
    char choix_modif , choix_ajout;
    bool option_inconnue = true ,  end_saisie = false , valid_input ;
    string new_skill , nouv_cp , nouv_entreprise , ancien_collegue_mail ;
    Personne * nouv_collegue = NULL;
    Competence * tmp_skill_pers ;
    AncienCollegue * nouveau_collegue, *tmpA ;
    Entreprise * tmp_ent ;

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
                        } else {
                            tmp_skill_pers = new Competence(new_skill) ;
                            //vérifier si la compétence est pas déjà dans la liste
                            if (current_user->CompetencePropres() && tmp_skill_pers->IsInList(current_user->CompetencePropres())) {
                                valid_input = false ;
                                cout << "La compétence recherchée est déjà associée à votre profil" << endl << endl ; 
                                delete tmp_skill_pers ;
                            }
                        }
                    } while (!valid_input);
                    if (current_user->CompetencePropres()) {
                        current_user->CompetencePropres()->AddCompetence(new_skill) ;
                    } else {
                        current_user->modifCompetencePropres(tmp_skill_pers) ;  
                    }
                    Logs("AddCompetence", new_skill) ;
                                  
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
                    do {
                        cout << "Veuillez indiquer  l'adresse mail : " ;
                        cin >>  ancien_collegue_mail ;
                        valid_input = email_valide(ancien_collegue_mail) ;
                        if (!valid_input) {
                            cout << "addresse mail invalide" << endl << endl ;
                        }
                        if (ancien_collegue_mail == current_user->mail()) {
                            valid_input = false ;
                            cout << "Vous ne pouvez pas vous ajouter à votre liste d'anciens collègues" << endl ;
                        }
                        tmpA = current_user->ListAncienCollegues() ;
                        while(tmpA && valid_input){
                            if (tmpA->currentA()->mail() == ancien_collegue_mail){
                                cout << "Cette personne est déjà dans votre liste d'anciens collègues" << endl ;
                                valid_input = false ;
                            }
                            tmpA = tmpA->nextA() ;
                        }
                        
                    } while (!valid_input);
                    nouv_collegue = EmployesListe ;
                    while (nouv_collegue && nouv_collegue->mail() !=  ancien_collegue_mail) {
                        nouv_collegue = nouv_collegue->nextP() ;
                    }
                    if (!nouv_collegue) {
                        nouv_collegue = ChercheursListe ;
                        while (nouv_collegue && nouv_collegue->mail() !=  ancien_collegue_mail) {   
                            nouv_collegue = nouv_collegue->nextP() ;
                        }
                    }
                    if (nouv_collegue) {
                        if (current_user->ListAncienCollegues()) {
                            current_user->ListAncienCollegues()->addAncienCollegue(nouv_collegue,current_user) ;
                        } else {
                            nouveau_collegue = new AncienCollegue(nouv_collegue) ;
                            current_user->modifAncienCollegues(nouveau_collegue) ;
                        }
                        Logs("addAncienCollegue", ancien_collegue_mail) ;
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
                    cout << "Veuillez indiquer votre nouveau code postal : " ;
                    cin >> nouv_cp ;
                    valid_input = cp_valide(nouv_cp) ;
                    if (!valid_input) {
                        cout << "Code postal invalide" << endl << endl ;
                    } 
                } while (!valid_input);
                current_user->modifCodePostal(nouv_cp) ;
                Logs("modifCodePostal", nouv_cp) ;
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
                        } else {
                            tmp_ent = EntrepriseListe ;
                            while (tmp_ent && tmp_ent->nom() != nouv_entreprise) {
                                tmp_ent = tmp_ent->next() ;
                            }
                            if (!tmp_ent) {
                                valid_input = false ;
                                cout << "L'entreprise recherchée est introuvable" << endl << endl ; 
                            }
                        }
                        
                    } while (!valid_input);
                    // On transitionne 2 fois pour pouvoir ajouter les anciens collègues de l'entreprise précédente et changer l'entreprise
                    current_user->TransitionStatut(&EmployesListe, &ChercheursListe) ;
                    current_user->TransitionStatut(&EmployesListe, &ChercheursListe, tmp_ent) ;
                    Logs("modifEntreprise", tmp_ent->mail()) ;
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
bool menu_transition_pers(Personne * current_user)
{
    int confirmation_ans ;
    bool option_inconnue = true , succes_transition , valid_input ;
    Entreprise * tmp_ent ;
    string nouvelle_entreprise ;

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
                    if ( current_user->EntrepriseActuelle()) {
                        current_user->TransitionStatut(&EmployesListe,&ChercheursListe) ;
                        Logs("TransitionStatut", current_user->mail()) ;
                    } else {
                        do
                        {
                            cout << "Veuillez indiquer votre nouvelle entreprise : " ;
                            cin >> nouvelle_entreprise ;
                            valid_input = saisie_valide(nouvelle_entreprise) ;
                            if (!valid_input) {
                                cout << "Nom d'entreprise invalide" << endl << endl ;
                            } else {
                                tmp_ent = EntrepriseListe ;
                                while (tmp_ent && tmp_ent->nom() != nouvelle_entreprise) {
                                    tmp_ent = tmp_ent->next() ;
                                }
                                if (!tmp_ent) {
                                    valid_input = false ;
                                    cout << "L'entreprise recherchée est introuvable" << endl << endl ; 
                                }
                            }
                            
                        } while (!valid_input) ;
                        Logs("TransitionStatut", current_user->mail()+"->"+tmp_ent->mail()) ;
                        current_user->TransitionStatut(&EmployesListe,&ChercheursListe,tmp_ent) ;
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
void type_recherche_entreprise(Entreprise  * utilisateur_entreprise)
{
    char choix_type ;
    bool option_inconnue = true , valid_input, find ;
    Competence *listeComp, *tmpC ;
    Personne *tmpP ;
    string listeComp_string, titre_poste ;
    string ans ;
    Poste *tmpPoste ;

    system("clear") ;
    cout << "Bienvenue dans LuminIn !" << endl << endl;
    cout << "* Menu entreprise *" << endl ;
    cout << endl ;

    while (option_inconnue)
    {
        cout << "Vous voulez :" << endl ;
        cout << "1.Effectuer une recherche des chercheurs d'emploi selon des compétences pour un poste" << endl ;
        cout << "2.Effectuer une recherche des chercheurs d'emploi selon des compétences pour un poste et un code postal (celui votre entreprise)" << endl ;
        cout << endl ;
        cout << "Votre choix ('q' pour revenir en arrière) : ";
        cin >> choix_type ;
        cout << endl ;

        switch (choix_type)
        {
            case '1':
                option_inconnue = false ;
                do {
                    cout << "Veuillez saisir le titre du poste à pourvoir" << endl ;
                    cin >> titre_poste ;
                    valid_input = saisie_valide(titre_poste) ;
                    if (!valid_input) {
                        cout << "Titre invalide" << endl << endl ;
                    }
                    else{
                        tmpPoste = utilisateur_entreprise->profilPoste() ;
                        find = false ;
                        while(tmpPoste && !find){
                            if(tmpPoste->Titre() == titre_poste){
                                listeComp = tmpPoste->CompetencesRequises() ;
                                find = true ;
                            }
                            tmpPoste = tmpPoste->next() ;
                        }
                        if(!find){
                            cout << "Poste introuvable, recherche annulée" << endl ;
                            cout << "Voulez-vous réessayer ?" << endl << "1.Oui" << endl << "2.non" << endl ;
                            // ans.clear() ;
                            // getline(cin, ans) ;
                            cin >> ans ;
                            if(ans == "1") valid_input = false ;
                            else if (ans == "2") ;
                            else{
                                cout << "Option inconnue, retour au menu" << endl ;
                                ans.clear() ;
                                continuer() ;
                                system("clear") ;
                            }
                        }
                    }
                } while (!valid_input);

                if(find){
                    tmpC = listeComp ;
                    while(tmpC){
                        listeComp_string += tmpC->label()+" " ;
                        tmpC = tmpC->next() ;
                    }
                    cout << "Voici le résultat de la recherche :" << endl << endl;
                    //appel de la recherche selon les compétences
                    if (listeComp) tmpP = ChercheursListe->ChercheurCompetence(listeComp) ;
                    else tmpP = NULL ;
                    Logs("ChercheurCompetence", titre_poste+" : "+listeComp_string) ;
                    if (!tmpP) {
                        cout << "-----------------------------------------------" << endl ;
                        cout << "Aucun résultat trouvé" << endl ;
                    }
                    while (tmpP) {
                        cout << "-----------------------------------------------" << endl ;
                        cout << "Nom : " << tmpP->nom() << " | Prénom : " << tmpP->prenom() << " | mail : " << tmpP->mail() << endl ;
                        tmpP = tmpP->nextP() ;
                    }
                    cout << "-----------------------------------------------" << endl ;                
                }
                break;

            case '2':
                option_inconnue = false ;
                do {
                    cout << "Veuillez saisir le titre du poste à pourvoir" << endl ;
                    cin >> titre_poste ;
                    valid_input = saisie_valide(titre_poste) ;
                    if (!valid_input) {
                        cout << "Titre invalide" << endl << endl ;
                    }
                } while (!valid_input);
                tmpPoste = utilisateur_entreprise->profilPoste() ;
                find = false ;
                while(tmpPoste && !find){
                    if(tmpPoste->Titre() == titre_poste){
                        listeComp = tmpPoste->CompetencesRequises() ;
                        find = true ;
                    }
                    tmpPoste = tmpPoste->next() ;
                }
                if(!find) cout << "Poste introuvable, recherche annulée" << endl ;
                else{
                    tmpC = listeComp ;
                    while(tmpC){
                        listeComp_string += tmpC->label()+" " ;
                        tmpC = tmpC->next() ;
                    }
                    cout << "Voici le résultat de la recherche :" << endl << endl;
                    //appel de la recherche selon les compétences et le code postal
                    tmpP = ChercheursListe->ChercheurCompetenceCodePostal(listeComp, utilisateur_entreprise->codePostal()) ;
                    Logs("ChercheurCompetence", listeComp_string+" | "+listeComp_string+" | "+utilisateur_entreprise->codePostal()) ;
                    if (!tmpP) {
                        cout << "-----------------------------------------------" << endl ;
                        cout << "Aucun résultat trouvé" << endl ;
                    }
                    while (tmpP) {
                        cout << "-----------------------------------------------" << endl ;
                        cout << "Nom : " << tmpP->nom() << " | Prénom : " << tmpP->prenom() << " | mail : " << tmpP->mail() << endl ;
                        tmpP = tmpP->nextP() ;
                    }
                    cout << "-----------------------------------------------" << endl ;
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

//menu de recherche de postes
void recherche_poste_pers(Personne *current_user)
{
    char choix_type_recherche ;
    bool option_inconnue = true ;
    Entreprise * resultat_recherche , *tmpE;

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
                cout << "Voici les entreprise disposant de postes à pourvoir correspondant à vos compétences" << endl ;
                resultat_recherche = current_user->RecherchePosteCompetence(EntrepriseListe) ;
                Logs("RecherchePosteCompetence", current_user->mail()) ;
                tmpE = resultat_recherche ;
                if (!tmpE) {
                    cout << "-----------------------------------------------" << endl ;
                    cout << "Aucun résultat trouvé" << endl ;
                }
                while (tmpE) {
                    cout << "-----------------------------------------------" << endl ;
                    cout << "Titre du poste: " << tmpE->profilPoste()->Titre() << " | Nom de l'entreprise: " << tmpE->nom() << " | mail de l'entreprise : " << tmpE->mail() << " | code postal de l'entreprise : "  << tmpE->codePostal() << endl ;
                    tmpE = tmpE->next() ;
                }
                cout << "-----------------------------------------------" << endl ;
                break;

            case '2':
                option_inconnue = false ;
                cout << "Voici les les entreprise disposant de postes à pourvoir correspondant à vos compétences proche de chez vous :" << endl ;
                resultat_recherche = current_user->RecherchePosteCompetenceCodePostal(EntrepriseListe) ;
                Logs("RecherchePosteCompetence", current_user->mail()+" | Cp : "+current_user->codePostal()) ;
                tmpE = resultat_recherche ;
                if (!tmpE) {
                    cout << "-----------------------------------------------" << endl ;
                    cout << "Aucun résultat trouvé" << endl ;
                }
                
                while (tmpE) {
                    cout << "-----------------------------------------------" << endl ;   
                    cout << "Titre du poste: " << tmpE->profilPoste()->Titre() << " | Nom de l'entreprise: " << tmpE->nom() << " | mail de l'entreprise : " << tmpE->mail() << " | code postal de l'entreprise : "  << tmpE->codePostal() << endl ;
                    tmpE = tmpE->next() ;
                }
                cout << "-----------------------------------------------" << endl ;
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
    string entreprise_collegue, collegue_skill ;
    Entreprise * tmp_ent ;
    AncienCollegue * resultat_recherche , *tmpA;
    Competence * comp_recherchees = NULL, *tmpC ;
    string comp_recherchees_string ;

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
        cout << "1. Rechercher les anciens collègues employés dans une entreprise particulière" << endl ;
        if (current_user->EntrepriseActuelle()) {
            cout << "2. Rechercher les anciens collègues disposant de certaines compétences" << endl ;
        }else {
            cout << "2. Rechercher les anciens collègues employés dans les entreprises recherchant vos compétences" << endl ;
        }
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
                        } else {
                            tmp_ent = EntrepriseListe ;
                            while (tmp_ent && tmp_ent->nom() != entreprise_collegue) {
                                tmp_ent = tmp_ent->next() ;
                            }
                            if (!tmp_ent) {
                                valid_input = false ;
                                cout << "L'entreprise recherchée est introuvable" << endl << endl ; 
                            }
                        }
                    } while (!valid_input);
                cout << "Voici les anciens collègues employés dans l'entreprise " << entreprise_collegue << endl ;
                Logs("RechercheColleguesEntreprise", current_user->mail()+" | Entreprise :"+entreprise_collegue) ;
                resultat_recherche = current_user->RechercheColleguesEntreprise(entreprise_collegue) ;
                tmpA = resultat_recherche ;
                if (!tmpA) {
                    cout << "-----------------------------------------------" << endl ;
                    cout << "Aucun résultat trouvé" << endl ;
                }
                while (tmpA) {
                    cout << "-----------------------------------------------" << endl ;
                    cout << "Nom : " << tmpA->currentA()->nom() << " | Prénom : " << tmpA->currentA()->prenom() << " | mail : " << tmpA->currentA()->mail() << endl;
                    tmpA = tmpA->nextA() ;
                }
                cout << "-----------------------------------------------" << endl ;
                break;

            case '2':
                option_inconnue = false ;
                if (current_user->EntrepriseActuelle()) {
                    comp_recherchees = saisie_competence() ;
                    cout << "Voici les anciens collègues disposant des compétences recherchées :" << endl ;
                    tmpC = comp_recherchees ;
                    while(tmpC){
                        comp_recherchees_string += tmpC->label()+" " ;
                        tmpC = tmpC->next() ;
                    }
                    resultat_recherche = current_user->EmployeRechercheColleguesCompetence(comp_recherchees) ;
                    Logs("EmployeRechercheColleguesCompetence", current_user->mail()+" | Compétences : "+comp_recherchees_string) ;
                    tmpA = resultat_recherche ;
                    if (!tmpA) {
                        cout << "-----------------------------------------------" << endl ;
                        cout << "Aucun résultat trouvé" << endl ;
                    }
                    while (tmpA) {
                        cout << "-----------------------------------------------" << endl ;
                        cout << "Nom : " << tmpA->currentA()->nom() << " | Prénom : " << tmpA->currentA()->prenom() << " | mail : " << tmpA->currentA()->mail() << endl;
                        tmpA = tmpA->nextA() ;
                    }
                    cout << "-----------------------------------------------" << endl ;
                }else {
                    cout << "Voici les anciens collègues employés dans les entreprises recherchant vos compétences :" << endl ;
                    tmpC = current_user->CompetencePropres() ;
                    while(tmpC){
                        comp_recherchees_string += tmpC->label()+" " ;
                        tmpC = tmpC->next() ;
                    }
                    resultat_recherche = current_user->ChercheurRechercheColleguesCompetence(current_user->CompetencePropres()) ;
                    Logs("ChercheurRechercheColleguesCompetence", current_user->mail()+" | Compétences : "+comp_recherchees_string) ;
                    tmpA = resultat_recherche ;
                    if (!tmpA) {
                        cout << "-----------------------------------------------" << endl ;
                        cout << "Aucun résultat trouvé" << endl ;
                    }
                    while (tmpA) {
                        cout << "-----------------------------------------------" << endl ;
                        cout << "Nom : " << tmpA->currentA()->nom() << " | Prénom : " << tmpA->currentA()->prenom() << " | mail : " << tmpA->currentA()->mail() << endl;
                        tmpA = tmpA->nextA() ;
                    }
                    cout << "-----------------------------------------------" << endl ;
                }
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
    bool profil_deleted , valid_input ;
    string titre_poste, label_competence, ans ;
    Poste *tmpP ;
    Competence *tmpC ;

    system("clear") ;
    cout << "Bienvenue dans LuminIn " << utilisateur_entreprise->nom() << " !" << endl << endl;
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
                    tmpP = utilisateur_entreprise->profilPoste() ;
                    //vérifier si le titre du poste est déjà dans la base de données pour l'entreprise en question
                    while(tmpP && valid_input){
                        if(tmpP->Titre()==titre_poste){
                            valid_input = false ;
                            cout << "Saisie invalide,le poste existe déjà" << endl ;
                        }
                        tmpP = tmpP->next() ;
                    }
                } while (!valid_input);
                if(utilisateur_entreprise->profilPoste()){
                    utilisateur_entreprise->addPoste(new Poste(titre_poste)) ;
                }else{      // Si c'est le premier poste
                    utilisateur_entreprise->modifProfilPoste(new Poste(titre_poste)) ;
                }
                Logs("addPoste", titre_poste) ;
                cout << "Veuillez saisir les compétences recherchées pour ce poste : " << endl ;
                //appel de la fonction permettant d'entrer des compétences dans une liste
                tmpP = utilisateur_entreprise->profilPoste() ;
                while (tmpP->next()) tmpP = tmpP->next() ;
                tmpC = tmpP->CompetencesRequises() ;
                do
                {
                    cin >> label_competence ;
                    valid_input = saisie_valide(label_competence) ;
                    if (!valid_input) {             
                        cout << "Compétence entrée invalide" << endl << endl ;
                    }
                    //vérifier si la compétence a déja été entrée
                    while(tmpC && valid_input){
                        if(tmpC->label()==label_competence){
                            valid_input = false ;
                            cout << "Saisie invalide, la compétence existe déjà" << endl ;
                        }
                        tmpC = tmpC->next() ;
                    }
                    if(valid_input){
                        if(tmpP->CompetencesRequises()){
                            tmpP->CompetencesRequises()->AddCompetence(label_competence) ;
                        }else{                              // Ajout de la première compétence
                            tmpP->modifCompetencesRequises(new Competence(label_competence)) ;
                        }
                        cout << "Entrer de nouvelles compétences ? (Y/N)" << endl ;
                        cin >> ans ;
                        if(ans == "Y") valid_input = false ;
                    }
                } while (!valid_input);

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
                utilisateur_entreprise->dellPoste(titre_poste) ;
                Logs("dellPoste", titre_poste) ;
                cout << "suppression du poste" << endl ;
                continuer() ;
                break;

            case '3':
                option_unknown = false ;
                type_recherche_entreprise(utilisateur_entreprise) ;
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
        Logs("connexion_entreprise", current_user_entreprise->mail()) ;
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
            do {
                cout << "Veuillez indiquer l'adresse mail de votre entreprise : " ;
                cin >> mail_entreprise ;
                valid_input = email_valide(mail_entreprise) ;
                if (!valid_input) {
                    cout << "address email invalide" << endl << endl ;
                }
                
            } while (!valid_input);

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
                current_user_entreprise = EntrepriseListe ;
                while(current_user_entreprise->next()) current_user_entreprise = current_user_entreprise->next() ;

            }else{                  // Si c'est la première entreprise créée
                EntrepriseListe = new Entreprise(1, nom_entreprise, cp_entreprise, mail_entreprise) ;
                EntrepriseListe->MAJDBEntreprise() ;
                current_user_entreprise = EntrepriseListe ;
            }
            Logs("addEntreprise", mail_entreprise) ;
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
    bool option_unknown = true , deleted_profil , transition_success ;

    system("clear") ;
    cout << "Bienvenue dans LuminIn " << utilisateur_chercheur->prenom() <<" " << utilisateur_chercheur->nom() << " !" << endl << endl;
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
                transition_success = menu_transition_pers(utilisateur_chercheur) ; 
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
    string mail_chercheur ;
    Personne * tmp ;

    system("clear") ;
    cout << "Bienvenue dans LuminIn !" << endl << endl;
    cout << "* Menu chercheur d'emploi *" << endl ;
    cout << endl ;

    do {
        cout << "Veuillez indiquer votre adresse mail : " ;
        cin >> mail_chercheur ;
        valid_input = email_valide(mail_chercheur) ;
        if (!valid_input) {
            cout << "address email invalide" << endl << endl ;
        }
        
    } while (!valid_input);

    current_user_chercheur = ChercheursListe ;
    while (current_user_chercheur && mail_chercheur != current_user_chercheur->mail()) {
        current_user_chercheur = current_user_chercheur->nextP() ;
    }

    if (current_user_chercheur) {
        system("clear") ;
        Logs("connexion_chercheur", mail_chercheur) ;
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
            current_user_chercheur = saisie_personne(false) ;
            tmp = ChercheursListe ;
            if (tmp) {
                while (tmp->nextP()) {
                    tmp = tmp->nextP() ;
                }
                current_user_chercheur->modifIndex(tmp->index()+1) ;
                tmp->modifNextP(current_user_chercheur) ;
                current_user_chercheur->modifPreviousP(tmp) ;
            }else {
                ChercheursListe = current_user_chercheur ;   
            }
            ChercheursListe->MAJDBPersonne(false) ;
            Logs("Créer Chercheur d'Emploi", current_user_chercheur->mail()) ;
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

     cout << "Bienvenue dans LuminIn " << utilisateur_employe->prenom() <<" " << utilisateur_employe->nom() << " !" << endl << endl;
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
    Personne * current_user_employe = NULL , *tmp;
    char choix_employe ;
    bool valid_input ;
    string nom_employe , prenom_employe , cp_employe , mail_employe , entreprise_employe ;

    system("clear") ;
    cout << "Bienvenue dans LuminIn !" << endl << endl;
    cout << "* Menu employé *" << endl ;
    cout << endl ;


    do {
        cout << "Veuillez indiquer votre adresse mail : " ;
        cin >> mail_employe ;
        valid_input = email_valide(mail_employe) ;
        if (!valid_input) {
            cout << "address email invalide" << endl << endl ;
        }
        
    } while (!valid_input);

    current_user_employe = EmployesListe ;
    while (current_user_employe && mail_employe != current_user_employe->mail()) {
        current_user_employe = current_user_employe->nextP() ;
    }

    if (current_user_employe) {
        system("clear") ;
        Logs("connexion_employe", mail_employe) ;
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
            current_user_employe = saisie_personne(1) ;
            if (current_user_employe) {
                tmp = EmployesListe ;
                if (tmp) {
                    while (tmp->nextP()) {
                        tmp = tmp->nextP() ;
                    }
                    current_user_employe->modifIndex(tmp->index()+1) ;
                    tmp->modifNextP(current_user_employe) ;
                    current_user_employe->modifPreviousP(tmp) ;
                }else {
                    EmployesListe = current_user_employe ;   
                }
                EmployesListe->MAJDBPersonne(true) ;
                system("clear") ;
                Logs("Créer Employe", current_user_employe->mail()) ;
                menu_employe(current_user_employe) ; 
            } else {
                cout << "Création de profil annulée retour au menu principal" << endl ;
                continuer() ;
                system("clear") ;
                menu_principal() ;
            }  
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
    
    // Dernière MAJ avant de quitter le programme (sécurité)
    EmployesListe->MAJDBPersonne(true) ;
    ChercheursListe->MAJDBPersonne(false) ;
    EntrepriseListe->MAJDBEntreprise() ;

    return 0 ;
}