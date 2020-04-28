#include "../include/Graphe.hpp"
#include "../include/Svgfile.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

/// La construction du graphe se fait à partir d'un fichier topo
/// dont le nom est passé en paramètre
Graphe::Graphe(std::string nomFichier)
{
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );

    ifs >> orientation;
    if(ifs.fail())
        throw std::runtime_error("Probleme lecture orientation");

    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");

    ///Boucle qui créer chaque sommet
    for (int i=0; i<ordre; ++i)
    {
        ifs >> id1 >> nom >> x >> y;
        m_ListeSommets.push_back(new Sommet(id1,nom,x*100,y*100));
    }

    ifs >> taille;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");

    ///Boucle qui créer chaque Arete selon l'orientation et qui donne les adjacents.
    for (int i=0; i<taille; ++i)
    {
        ifs >> id3 >> id1 >> id2;
        ///Deux condition pour les adjacents si le graphe est orienté ou non.
        if(orientation==1)
        {
            m_ListeAretes.push_back(new Arete(id3,m_ListeSommets[id1],m_ListeSommets[id2]));
            m_ListeSommets[id1]->ajouterAdjacents(m_ListeSommets[id2]);
        }
        if(orientation==0)
        {
            ///PREMIER SENS
            m_ListeAretes.push_back(new Arete(id3,m_ListeSommets[id1],m_ListeSommets[id2]));
            m_ListeSommets[id1]->ajouterAdjacents(m_ListeSommets[id2]);
            ///DEUXIEME SENS
            id3+=taille;
            m_ListeAretes.push_back(new Arete(id3,m_ListeSommets[id2],m_ListeSommets[id1]));
            m_ListeSommets[id2]->ajouterAdjacents(m_ListeSommets[id1]);
        }
        else
            throw std::runtime_error("Probleme lecture orientation pas de 0 ou 1");
    }
}

/// Destructeur du graphe. Les Sommets ont été allouées dynamiquement
/// lors de la création d'une instance Graphe, le graphe est responsable de leur libération
Graphe::~Graphe()
{}

///Charger le fichier de pondération
void Graphe::chargerPonderation(std::string nomFichier)
{
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
    ifs>>taille;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");
    for(int i=0;i<taille;++i)
    {
        ifs >> id1 >> poids;
        int a=0;
        for(int j=0;j<m_ListeAretes.size();++j)
        {
            if(m_ListeAretes[a]->getId()!=id1)
                a+=1;
            else
                m_ListeAretes[a]->ajouterPonderation(poids);
        }
    }
}
/// Retourne l'odre du graphe (ordre = nombre de sommets)
int Graphe::getOrdre() const
{
    return (int)m_ListeSommets.size();
}
///Retourne la liste des sommets
std::vector<Sommet*> Graphe::getListe()const
{
    return this->m_ListeSommets;
}
/// Retourne l'orientation du graphe
std::string Graphe::getOrientation()const
{
    std::string mess;
    if(orientation==1)
        mess="Graphe oriente";
    if(orientation==0)
        mess="Graphe non oriente";
    return mess;
}
///Permet d'avoir la centralite du degre
void Graphe::centraliteDegre()
{
    std::ofstream ofs("Centralite De Degre.txt");
    ///Affichage console
    std::cout<<"Centralite Non Normalises:"<<std::endl;
    for(int i=0;i<m_ListeSommets.size();++i)
    {
        std::cout<<"Sommet: "<<m_ListeSommets[i]->getNom()<<" de centralite "<<m_ListeSommets[i]->getDegre()<<std::endl;
    }
    std::cout<<"Centralite Normalises:"<<std::endl;
    for(int i=0;i<m_ListeSommets.size();++i)
    {
        std::cout<<"Sommet: "<<m_ListeSommets[i]->getNom()<<" de centralite "<<m_ListeSommets[i]->getDegre()*100/(m_ListeSommets.size()-1)<<"%"<<std::endl;
    }
    ///Ecriture fichier
    for(int i=0;i<m_ListeSommets.size();++i)
    {
        ofs << m_ListeSommets[i]->getId()<<" "<<m_ListeSommets[i]->getDegre()<<" "<<m_ListeSommets[i]->getDegre()*100/(m_ListeSommets.size()-1)<<"%"<<std::endl;
    }
}
void Graphe::afficher()
{
    std::cout<<"Liste des sommet:"<<std::endl;
    for(int i=0;i<ordre;++i)
    {
        m_ListeSommets[i]->afficher();
    }
    std::cout<<"Liste des aretes:"<<std::endl;
    for(int i=0;i<m_ListeAretes.size();++i)
    {
        m_ListeAretes[i]->afficher();
    }
}
void Graphe::afficherSVG(Svgfile& svgout)
{
    ///Affichage sommet
    for(int i=0;i<ordre;++i)
    {
        svgout.addCircle(m_ListeSommets[i]->getX(),m_ListeSommets[i]->getY(),5,5,"pink");
        svgout.addText(m_ListeSommets[i]->getX(),m_ListeSommets[i]->getY(),m_ListeSommets[i]->getNom(),"black");
    }
    for(int i=0;i<m_ListeAretes.size();++i)
    {
        svgout.addLine(m_ListeAretes[i]->getS1()->getX(),m_ListeAretes[i]->getS1()->getY(),m_ListeAretes[i]->getS2()->getX(),m_ListeAretes[i]->getS2()->getY(),"black");
        if(m_ListeAretes[i]->getPonderation()!=9999)
        {
            ///Recupere le milieu de l'arete
            double x=(m_ListeAretes[i]->getS1()->getX()+m_ListeAretes[i]->getS2()->getX())/2;
            double y=(m_ListeAretes[i]->getS1()->getY()+m_ListeAretes[i]->getS2()->getY())/2;
            svgout.addText(x,y,m_ListeAretes[i]->getPonderation(),"blue");
        }
    }

}
