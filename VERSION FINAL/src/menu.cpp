#include "../include/menu.hpp"
#include "../include/Graphe.hpp"
#include <stdio.h>
#include <string.h>

void menu(Graphe g)
{
    int choix;
    system("cls");
    do
    {
        std::cout<<"Veuillez choisir votre action"<<std::endl<<"1) Etudier le graphe actuel"<<std::endl<<"2) Modifier le graphe actuel"<<std::endl<<"3) Sauvegarder le graphe actuel"<<std::endl<<"0) Quitter"<<std::endl;
        std::cin>>choix;
        if(choix==1)
        {
            int choixAction;
            system("cls");
            std::cout<<"Veuillez choisir votre action"<<std::endl<<"1) Calculer l'indice de Degre"<<std::endl<<"2) Calculer l'indice de Vecteur Propre"<<std::endl<<"3) Calculer l'indice de Proximite"<<std::endl<<"4) Calculer l'indice d'intermediarite"<<std::endl<<"5) Tester la connectivite"<<std::endl<<"6) Calculer la vulnerabilite"<<std::endl;
            std::cin>>choixAction;
            switch(choixAction)
            {
            case 1:
                system("cls");
                g.centraliteDegre();
                break;
            case 2:
                system("cls");
                g.centraliteVecteurPropre();
                break;
            case 3:
                system("cls");
                g.centraliteProximite();
                break;
            case 4:
                system("cls");
                g.centraliteIntermediaire();
                break;
            case 5:
                system("cls");
                if(g.getOrientation()==0)
                    g.rechercher_afficher_CC();
                if(g.getOrientation()==1)
                    g.rechercher_afficher_CFC();
                break;
            case 6:
                system("cls");
                g.Vulnerabilite();
                break;
            }
        }
        if(choix ==2)
        {
            int choixAction;
            system("cls");
            std::cout<<"Veuillez choisir votre action"<<std::endl<<"1) Ajouter un Sommet"<<std::endl<<"2) Supprimer un Sommet"<<std::endl<<"3) Ajouter une Arete"<<std::endl<<"4) Supprimer une Arete"<<std::endl<<"5) Charger un fichier de ponderation"<<std::endl;
            std::cin>>choixAction;
            switch(choixAction)
            {
            case 1:
                system("cls");
                g.ajouterSommet();
                break;
            case 2:
                system("cls");
                g.supprimerSommet();
                break;
            case 3:
                system("cls");
                g.ajouterArete();
                break;
            case 4:
                system("cls");
                int id;
                g.afficherArete();
                std::cout<<"Indiquez l'id de l'arete a supprimer:"<<std::endl;
                std::cin>>id;
                g.supprimerArete(id);
                break;
            case 5:
                system("cls");
                std::string nomFichier;
                std::cout<<"Veuillez saisir le nom du fichier"<<std::endl;
                std::cin>>nomFichier;
                g.chargerPonderation(nomFichier+".txt");
                break;
            }
        }
        if(choix==3)
        {
            g.sauvegarderGraphe();
        }
    }
    while(choix!=0);
}

