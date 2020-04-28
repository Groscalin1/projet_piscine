#include "../include/Arete.hpp"
#include "../include/Sommet.hpp"

///Recupere S1
Sommet* Arete::getS1()
{
    return (Sommet*)m_S1;
}
///Recupere S2
Sommet* Arete::getS2()
{
    return (Sommet*)m_S2;
}
///Recupere l'Id
int Arete::getId()const
{
    return (int)m_id;
}
///Recupere la ponderation
float Arete::getPonderation()const
{
    return (float)m_ponderation;
}
///Ajout de la ponderation lors du chargement fichier ponderation
void Arete::ajouterPonderation(float ponderation)
{
    m_ponderation=ponderation;
}
/// c'est la "méthode d'affichage" des objets de type Arete
void Arete::afficher () const
{
    std::cout<<"id:"<<m_id<<" du sommet: "<<m_S1->getNom()<<" au sommet : "<<m_S2->getNom()<<std::endl;
}
