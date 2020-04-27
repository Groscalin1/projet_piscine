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
    std::string m_nom;

public:
    Sommet(int id,std::string nom,int x,int y);
    Sommet();
    int getId()const;
    int getX()const;
    int getY()const;
    std::string getNom()const;
    void afficher() const;
};
#endif // SOMMET_H_INCLUDED
