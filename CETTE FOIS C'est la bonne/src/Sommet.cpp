#include "../include/Sommet.hpp"
#include <string>
#include <vector>
Sommet::Sommet(int id,std::string nom,int x,int y):m_id{id},m_nom{nom},m_x{x},m_y{y},m_adjacents{} {}
Sommet::Sommet() {}

///Recupere son id
int Sommet::getId()const
{
    return (int)m_id;
}
///Recupere le X
int Sommet::getX()const
{
    return (int)m_x;
}
///Recupere le Y
int Sommet::getY()const
{
    return (int)m_y;
}
///Recupere le Nom
std::string Sommet::getNom() const
{
    return(std::string)m_nom;
}
///Recuper la couleur
std::string Sommet::getCouleur()const
{
    return(std::string)m_couleur;
}
///Recupere le degre
int Sommet::getDegre()const
{
    return (int)m_adjacents.size();
}
///Recupere la liste des adjacents
std::vector<const Sommet*> Sommet::getAdj()const
{
    return (std::vector<const Sommet*>)m_adjacents;
}
///Recupere la liste des poids
std::vector<float> Sommet::getPoids()const
{
    return (std::vector<float>)m_poids;
}
///Recuper la veleur de l'indice pour l'afficher sur le svgfile
float Sommet::getIndice()const
{
    return(float)m_indice;
}
///Ajouter un indice
void Sommet::ajouterIndice(float indice)
{
    m_indice=indice;
}
///Ajouter des adjacents
 void Sommet::ajouterAdjacents(Sommet*id2)
{
    m_adjacents.push_back(id2);
}
///Supprimer des adjacents
void Sommet::supprimerAdjacents(Sommet*id2)
{
    for(unsigned i=0;i<m_adjacents.size();++i)
    {
        if(m_adjacents[i]->getId()==id2->getId())
        {
            m_adjacents.erase(m_adjacents.begin()+i);
            m_poids.erase(m_poids.begin()+i);
        }
    }
}
///Ajouter le poids des aretes
 void Sommet::ajouterPoids(float poids)
{
    m_poids.push_back(poids);
}
///Changer la couleur du sommet
void Sommet::changercouleur(std::string couleur)
{
    m_couleur=couleur;
}
///Changer l'indice
void Sommet::changerId(int id)
{
    m_id=id;
}

