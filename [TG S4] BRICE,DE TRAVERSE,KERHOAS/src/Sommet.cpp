#include "../include/Sommet.hpp"
#include <string>
#include <vector>
Sommet::Sommet(int id,std::string nom,int x,int y):m_id{id},m_nom{nom},m_x{x},m_y{y} {}
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
///Affichage des objets de type Sommet
void Sommet::afficher () const
{
    std::cout<<"id:"<<m_id<<"  nom:"<<m_nom<<"  (x,y)=("<<m_x<<","<<m_y<<");"<<std::endl;
}
