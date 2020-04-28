#include <iostream>
#include "include/Graphe.hpp"
#include "include/Svgfile.hpp"

int main()
{
    ///Initialisation
    Svgfile svgout;
    svgout.addGrid();
    Graphe graphe("graphe_etoile1_topo.txt");
    graphe.chargerPonderation("graphe_etoile1_ponde.txt");
    ///Affichage svg
    graphe.afficherSVG(svgout);
    ///Affichage texte
    //graphe.afficher();
    //graphe.centraliteDegre();
    //graphe.centraliteProximite();
    graphe.centraliteVecteurPropre();

}
