#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <iostream>
#include<fstream>
#include<string>
#include<vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <utility>
#include <tuple>

class Sommet
{
private:
    /// Données spécifiques du sommet
    int m_id,m_x,m_y;
    float m_indice=0;
    std::string m_nom;
    std::vector<const Sommet*> m_adjacents;
    std::vector<float>m_poids;
    std::string m_couleur="cyan";


public:
    Sommet(int id,std::string nom,int x,int y);
    Sommet();
    ~Sommet();
    int getId()const;
    int getX()const;
    int getY()const;
    int getDegre()const;
    std::string getNom()const;
    std::string getCouleur()const;
    float getIndice()const;
    std::vector<const Sommet*> getAdj()const;
    std::vector<float>getPoids()const;
    void ajouterAdjacents(Sommet* id2);
    void supprimerAdjacents(Sommet*id2);
    void ajouterPoids(float poids);
    void changercouleur(std::string couleur);
    void ajouterIndice(float indice);
    void changerId(int id);

};
#endif // SOMMET_H_INCLUDED
