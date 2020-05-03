#include <iostream>
#include "include/Graphe.hpp"
#include "include/Svgfile.hpp"
///source : Les TP réalisés pendant le semestre, donc une partie de code de Mme.Palasi et de M.Fercoq
int main()
{
    ///Initialisation
    Svgfile svgout;
    svgout.addGrid();
    Graphe graphe("graphe_cycle4_topo.txt");
    graphe.chargerPonderation("graphe_cycle4_ponde.txt");
    ///Affichage svg
    graphe.afficherSVG(svgout);
    ///Affichage texte
    //graphe.afficher();
    //graphe.centraliteDegre();
    //graphe.centraliteVecteurPropre();
    //graphe.centraliteProximite();


}
