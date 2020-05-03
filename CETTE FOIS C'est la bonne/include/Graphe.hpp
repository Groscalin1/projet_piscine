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
#include <algorithm>
#include <cmath>
#include <queue>
#include <utility>
#include <tuple>
#include <map>
#include <stack>
#include <stdlib.h>
class Graphe
{
private:
    /// Le graphe est constitué d'une collection de Sommets
    std::vector<Sommet*> m_ListeSommets;
    std::vector<Arete*>m_ListeAretes;
    int orientation,ordre,taille,id1,id2,id3,x,y;
    float poids;
    std::string nom;

public:
    Graphe(std::string nomFichier);
    ~Graphe();
    int getOrdre() const;
    std::vector<Sommet*> getListe()const;
    int getOrientation()const;
    void chargerPonderation(std::string nomFichier);
    void afficherArete();
    void ajouterArete();
    void supprimerArete(int id);
    void afficherSommet();
    void ajouterSommet();
    void supprimerSommet();
    void afficher();
    void afficherSVG();
    void sauvegarderGraphe();
    std::map<const Sommet*, std::pair<const Sommet*, float>> Dijkstra(Sommet *initial)const;
    std::pair<int,int>DijkstraAdapte(Sommet *intermediaire,Sommet* initial,Sommet*fin)const;
    void affichageParcours (std::map<const Sommet*, std::pair<const Sommet*, float>> pred, int premier, int dernier);
    float PonderationPCC(std::map<const Sommet*, std::pair<const Sommet*, float>> pred, int premier, int dernier);
    std::vector<int> bfs(Sommet *initial)const;
    std::vector<int> dfs(Sommet *initial)const;
    void rechercher_afficher_CC();
    void rechercher_afficher_CFC();
    void centraliteDegre();
    void centraliteVecteurPropre();
    void centraliteProximite();
    void centraliteIntermediaire();
    void Vulnerabilite();
};
#endif // GRAPHE_H_INCLUDED
