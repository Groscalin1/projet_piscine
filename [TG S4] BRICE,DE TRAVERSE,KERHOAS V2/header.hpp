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

class Sommet
{
private:
    /// Voisinage : liste d'adjacence
    std::vector<std::pair<const Sommet*,const double>> m_adjacents;
    /// Données spécifiques du sommet
    int m_id;

public:

    /// La construction se fait directement depuis le fichier ouvert en cours de lecture...
    Sommet(int id)
    {
        m_id=id ;
    }

    /// Méthode d'ajouts d'adjacent ( dist= distance)
    void ajouterAdjacents(Sommet *id2,double dist)
    {
        std::pair<Sommet*,double>mapaire;
        mapaire.first=id2;
        mapaire.second=dist;
        m_adjacents.push_back(mapaire);
    }

    /// Retourne le degré du sommet
    int getDegre() const
    {
        return (int)m_adjacents.size();
    }

    ///Recupere son id
    int getId()const
    {
        return (int)m_id;
    }
    ///Recupere la distance avec parametre l'id2 de l'Arete
    double getDist(int i)const
    {
        return (double)m_adjacents[i].second;
    }
    /// Retourne la liste des adjacents
    std::vector<std::pair<const Sommet*,const double>> getAdjacents()
    {
        return (std::vector<std::pair<const Sommet*,const double>>)m_adjacents;
    }
    /// Surcharge de l'opérateur d'insertion vers un flot de sortie
    /// c'est la "méthode d'affichage" des objets de type Sommet
    friend std::ostream& operator<<(std::ostream& out, const Sommet& s)
    {
        out << "Sommet " << std::setw(2) << s.m_id << " : ";
        for (const auto a : s.m_adjacents)
            out << a.first->getId() << " ";
        out << std::endl;
        return out;
    }

};

class Arete
{
private:
    int m_id;
    Sommet m_S1,m_S2;
    std::vector<float>m_poids;
public:
    Arete(int id,Sommet S1,Sommet S2)
    {
        m_id=id;
        m_S1=S1;
        m_S2=S2;
    }
};

class Graphe
{
private:
    /// Le graphe est constitué d'une collection de Sommets
    std::vector<Sommet*> m_ListeSommets;
    std::vector<Arete*>m_ListeAretes;
    int orientation,ordre,taille,id1,id2,id3;
    double distance;

public:
    /// La construction du graphe se fait à partir d'un fichier
    /// dont le nom est passé en paramètre
    Graphe(std::string nomFichier)
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
            m_ListeSommets.push_back( new Sommet(i) );

        ifs >> taille;
        if ( ifs.fail() )
            throw std::runtime_error("Probleme lecture taille du graphe");

        ///Boucle qui créer chaque Arete selon l'orientation et qui donne les adjacents.
        for (int i=0; i<taille; ++i)
        {
            ifs >> id3 >> id1 >> id2;
            m_ListeAretes.push_back(new Arete(id3,m_ListeSommets[id1],m_ListeSommets[id2]));
            ///Deux condition pour les adjacents si le graphe est orienté ou non.
            if(orientation==1)
                m_ListeSommets[id1]->ajouterAdjacents(m_ListeSommets[id2]);
            else if(orientation==0)
            {
                m_ListeSommets[id1]->ajouterAdjacents(m_ListeSommets[id2]);
                m_ListeSommets[id2]->ajouterAdjacents(m_ListeSommets[id1]);
            }
            else
                throw std::runtime_error("Probleme lecture orientation pas de 0 ou 1");
        }
    }

    /// Destructeur du graphe. Les Sommets ont été allouées dynamiquement
    /// lors de la création d'une instance Graphe, le graphe est responsable de leur libération
    ~Graphe()
    {
        for (auto s : m_ListeSommets)
            delete s;
    }

    /// Retourne l'odre du graphe (ordre = nombre de sommets)
    int getOrdre() const
    {
        return (int)m_ListeSommets.size();
    }
    ///Retourne la liste des sommets
    std::vector<Sommet*> getListe()const
    {
        return this->m_ListeSommets;
    }
    /// Retourne l'orientation du graphe
    std::string getOrientation()const
    {
        std::string mess;
        if(orientation==1)
            mess="Graphe oriente";
        if(orientation==0)
            mess="Graphe non oriente";
        return mess;
    }
    /// Surcharge de l'opérateur d'insertion vers un flot de sortie
    /// c'est la "méthode d'affichage" des objets de type Graphe
    friend std::ostream& operator<<(std::ostream& out, const Graphe& g)
    {
        out << g.getOrientation()<<std::endl<< "    ordre= " << g.getOrdre() << std::endl<<"    listes d'adjacents"<<std::endl;
        for (const auto s : g.m_ListeSommets)
            out << *s;
        out << std::endl;
        return out;
    }
};
