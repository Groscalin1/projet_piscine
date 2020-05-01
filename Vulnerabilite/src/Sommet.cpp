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
///Recupere la liste des arretes
std::vector<float> Sommet::getPoids()const
{
    return (std::vector<float>)m_poids;
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
        }
    }
}
///Ajouter le poids des aretes
 void Sommet::ajouterPoids(float poids)
{
    m_poids.push_back(poids);
}
///Affichage des objets de type Sommet
void Sommet::afficher () const
{
    std::cout<<"id:"<<m_id<<"  nom:"<<m_nom<<"  (x,y)=("<<m_x<<","<<m_y<<");"<<std::endl;
}
