#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED
#include "Sommet.hpp"
#include "Arete.hpp"
#include "Svgfile.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
class Graphe
{
private:
    /// Le graphe est constitué d'une collection de Sommets
    std::vector<Sommet> m_ListeSommets;
    std::vector<Arete>m_ListeAretes;
    int orientation,ordre,taille,id1,id2,id3,x,y;
    float poids;
    std::string nom;

public:
    Graphe(std::string nomFichier);
    ~Graphe();
    int getOrdre() const;
    std::vector<Sommet> getListe()const;
    std::string getOrientation()const;
    void chargerPonderation(std::string nomFichier);
    void afficher();
    void afficherSVG(Svgfile& svgout);
};
#endif // GRAPHE_H_INCLUDED
