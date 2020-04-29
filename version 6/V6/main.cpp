#include <iostream>
#include "include/Graphe.hpp"
#include "include/Svgfile.hpp"

void menu();

int main()
{
    ///Initialisation
    menu();
    /* Svgfile svgout;
     svgout.addGrid();
     Graphe graphe("graphe_etoile1_topo.txt");
     graphe.chargerPonderation("graphe_etoile1_ponde.txt");
     ///Affichage svg
     graphe.afficherSVG(svgout);
     ///Affichage texte
     //graphe.afficher();
     //graphe.centraliteDegre();
     //graphe.centraliteProximite();
     graphe.centraliteVecteurPropre();*/

}



void menu()
{

    int choix=0;
    std::string fichierPonderation;
    std::string fichierGraphe;
    int choixPonderation;
    int choixIndice;
    do
    {
        system("cls");
        std::cout<<"1 : charger et afficher un graphe"<<std::endl;
        std::cout<<"2 : changer le système de pondération du graphe"<<std::endl;
        std::cout<<"3 : calculer, afficher et sauvgader les indices de centralité "<<std::endl;
        std::cout<<"4 : tester le vulnérabilité du graphe"<<std::endl;
        std::cout<<"5 : quitter"<<std::endl;
        std::cin>>choix;


        if (choix==1)
        {
            std::cout<<" "<<std::endl;
            std::cout<<"veuillez saisir le nom du fihier à inserer (.txt)"<<std::endl;
            std::cin>>fichierGraphe;
            std::cout<<" "<<std::endl;
            std::cout<<"voulez vous inserer un fichier de ponderation ? "<<std::endl;
            std::cout<<"1 : ajouter un fichier de ponderation et afficher le graphe "<<std::endl;
            std::cout<<"2 : afficher le graphe sans fichier de ponderation"<<std::endl;
            std::cout<<"3 : retour au menu"<<std::endl;
            std::cin>>choixPonderation;

            if (choixPonderation==1)
            {
                std::cout<<" "<<std::endl;
                std::cout<<"saisir le nom du fichier ponderation"<<std::endl;
                std::cin>>fichierPonderation;
                Svgfile svgout;
                svgout.addGrid();
                Graphe graphe(fichierGraphe);
                graphe.chargerPonderation(fichierPonderation);
                graphe.afficherSVG(svgout);
                graphe.afficher();
                std::cout<<"retour menu tapez 0"<<std::endl;
                std::cin>>choix;

            }
            if (choixPonderation==2)
            {
                Svgfile svgout;
                svgout.addGrid();
                Graphe graphe(fichierGraphe);
                graphe.afficherSVG(svgout);
                graphe.afficher();
                std::cout<<"retour menu tapez 0"<<std::endl;
                std::cin>>choix;
            }
            if (choixPonderation==3)
            {
                choix=0;
            }

        }

        if(choix==2)
        {
            std::cout<<" "<<std::endl;
            std::cout<<"Veuillez saisir le nom du nouveau fichier de ponderation (.txt)"<<std::endl;
            std::cin>>fichierPonderation;
            Svgfile svgout;
            svgout.addGrid();
            Graphe graphe(fichierGraphe);
            graphe.chargerPonderation(fichierPonderation);
            graphe.afficherSVG(svgout);
            graphe.afficher();
            std::cout<<"retour menu tapez 0"<<std::endl;
            std::cin>>choix;
        }
        if (choix==3)
        {
            std::cout<<"choisissez l'indice que vous voulez calculer"<<std::endl;
            std::cout<<"le resultat sera indiqué sous ca forme normalise et non normalisé"<<std::endl;
            std::cout<<"les resultats seront par la suite enregistré dans un fichier texte"<<std::endl;
            std::cout<<" "<<std::endl;
            std::cout<<"1 : Indice de centralite de degre "<<std::endl;
            std::cout<<"2 : Indice de vecteur propre "<<std::endl;
            std::cout<<"3 : Indice de proximité "<<std::endl;
            std::cin>>choixIndice;

            if (choixIndice==1)
            {
                std::cout<<" "<<std::endl;
                Graphe graphe(fichierGraphe);
                graphe.chargerPonderation(fichierPonderation);
                graphe.centraliteDegre();
                std::cout<<"retour menu tapez 0"<<std::endl;
                std::cin>>choix;
            }
            if (choixIndice==2)
            {
                std::cout<<" "<<std::endl;
                Graphe graphe(fichierGraphe);
                graphe.chargerPonderation(fichierPonderation);
                graphe.centraliteProximite();
                std::cout<<"retour menu tapez 0"<<std::endl;
                std::cin>>choix;
            }
            if (choixIndice==3)
            {
                std::cout<<" "<<std::endl;
                Graphe graphe(fichierGraphe);
                graphe.chargerPonderation(fichierPonderation);
                graphe.centraliteVecteurPropre();
                std::cout<<"retour menu tapez 0"<<std::endl;
                std::cin>>choix;
            }
        }

        if(choix==4)
        {

        }

        if (choix==5)
        {
            exit(0);
        }


    }
    while (choix==1 || choix==2 || choix==3 || choix==4 || choix==0);
}

