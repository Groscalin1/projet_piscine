#include "../include/Sommet.hpp"
#include <string>
#include <vector>
Sommet::Sommet(int id,std::string nom,int x,int y):m_id{id},m_nom{nom},m_x{x},m_y{y},m_adjacents{0} {}
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
///Recupere le degre
int Sommet::getDegre()const
{
    return (int)m_adjacents.size()-1;
}
///Recupere la liste des adjacents
std::vector<const Sommet*> Sommet::getAdj()
{
    return (std::vector<const Sommet*>)m_adjacents;
}
///Ajouter des adjacents
 void Sommet::ajouterAdjacents(Sommet*id2)
{
    m_adjacents.push_back(id2);
}
///Affichage des objets de type Sommet
void Sommet::afficher () const
{
    std::cout<<"id:"<<m_id<<"  nom:"<<m_nom<<"  (x,y)=("<<m_x<<","<<m_y<<");"<<std::endl;
}
