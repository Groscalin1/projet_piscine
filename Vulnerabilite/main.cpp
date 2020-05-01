#include <iostream>
#include "include/Graphe.hpp"
#include "include/Svgfile.hpp"
///source :
///Les TP réalisés pendant le semestre, donc une partie de code de Mme.Palasi et de M.Fercoq
/// Cpluplus.com reference
int main()
{
    ///Initialisation
    Graphe graphe("graphe_exemple_topo.txt"); ///DANS L'Affichage ajouter une option afficher les id des arretes ou la ponderation des arretes.
    graphe.chargerPonderation("graphe_exemple_ponde.txt");
    ///Affichage svg
    graphe.afficherSVG();
    ///Affichage texte
    //graphe.afficher();
    graphe.centraliteDegre();
    graphe.centraliteVecteurPropre();
    graphe.centraliteProximite();
    ///à finir
    //graphe.centraliteIntermediaire();
    graphe.Vulnerabilite();


}
