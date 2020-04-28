//
//  main.cpp
//  TP2
//
//  Created by Charles HAMERY on 28/02/2020.
//  Copyright © 2020 Charles HAMERY. All rights reserved.
//

//source code cours professeurs de l'ECE

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <stack>
#include <map>


/* Classe sommet*/

class Sommet
{
    private :
    
        int m_num;//identifiant du sommet
        int m_marque;//ordre du mrquage pour disjtra
        std::vector<Sommet*> m_adjacents;//vecteur de sommet adjacent
        std::vector<int> m_poids;//vecteur des poids associé au sommet adjacent
    
    public :
    
           Sommet(int i)//constructeur de la classe sommet
           {
               m_num = i;
               m_marque = -1;
           }
    
            void setAdjacent (Sommet* adjacent)//rajoute un sommet adjacent au vecteur
            {
                m_adjacents.push_back(adjacent);
            }
    
            void setPoids (int poids)//rajoute un poids au vecteur
            {
                m_poids.push_back( poids );
            }
    
            void setMarque(int selec)//donne une valeur au paramètre
            {
                m_marque = selec;
            }
    
            std::vector<Sommet*> getAdjacents()//retourne le vecteur d'adjacent
            {
                return m_adjacents;
            }
    
            int getNum()//retourne la valeur du numero du sommet
            {
                return m_num;
            }
    
            int getpoids(int selec)//retourne le poids d'une arrete
            {
                return m_poids[selec];
            }
    
            int getMarque()//retourne la valeur de la marque
            {
                return m_marque;
            }
    
            void afficher()//affiche une instance de sommet
            {
                std::cout<<std::endl<<m_num<<" :"<<std::endl;
                
                for(auto i=0;i<m_adjacents.size();++i)
                {
                    std::cout<<"sommet adjacent : "<<m_adjacents[i]->getNum()<<" poids : "<<m_poids[i]<<std::endl;
                }
            }
};

/* Classe CompareSommet, classe créé pour priorityqueue, source https://www.journaldev.com/35189/priority-queue-in-c-plus-plus */

class CompareSommet
{
    public:

        bool operator() (std::pair<Sommet*, int> const & a, std::pair<Sommet*, int> const & b)
        {
            if (a.second > b.second) //compare le poids entre un sommmet initial et celui de deux autres
                return true;
            return false;
        }
};

 
/* classe graphe*/

class Graphe
{
    private :
    
        int m_ordre;//nombre de sommet
        std::vector<Sommet*> m_sommets;//vecteur de sommmet
    
    public :
    
        Graphe(std::string nomFichier)//constructeur de graphe
        {
            std::ifstream ifs{nomFichier};//lecture du fichier
            if (!ifs)
                throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
            
            ifs >> m_ordre;
            if ( ifs.fail() )
                throw std::runtime_error("Probleme lecture ordre du graphe");
            
            for (int i=0; i<m_ordre; ++i)
            {
                m_sommets.push_back( new Sommet(i) );
            }
            
            int taille;
            ifs >> taille;

            int nbre1, nbre2, nbre3;
            
            for (int i=0; i<taille; ++i)//crée taille instance de sommet
            {
                ifs >> nbre1 >> nbre2 >> nbre3;
                
                m_sommets[nbre1]->setAdjacent(m_sommets[nbre2]);
                m_sommets[nbre1]->setPoids(nbre3);
            }
        }
    
        ~Graphe()//destructeur de graphe
        {
            for (auto s : m_sommets)
                delete s;
        }
        
        void afficher() const//affichage du graphe
        {
            std::cout<< "ordre = " << m_ordre <<std::endl << std::endl << "liste d'adjacence :" << std::endl;
            
            for(auto s : m_sommets)
                s->afficher();
            
            std::cout<< std::endl <<std::endl;
        }
    
         std::map<Sommet*, std::pair<Sommet*, int>> disjtra (int premier)//parcours disjtra
        {
            std::priority_queue< std::pair<Sommet*, int>, std::vector<std::pair<Sommet*,int> >,CompareSommet > maFile;
            std::map<Sommet*, std::pair<Sommet*, int>> pred_I_total;

            for(auto s : m_sommets)//initialisation des marques des sommets à 0 et création de predI
                s->setMarque(0);

            maFile.push(std::make_pair(m_sommets[premier], 0) );
            m_sommets[premier]->setMarque(1);

            while(!maFile.empty())
            {
                int compt = 0;
                std::pair<Sommet*,int> buffer;

                buffer = maFile.top();
                maFile.pop();

                for(auto s : buffer.first->getAdjacents())
                {
                    int total = buffer.second + buffer.first->getpoids(compt);

                    if (s->getMarque() == 0 || pred_I_total[s].second > total)
                    {
                        s->setMarque(1);
                        maFile.push(std::make_pair(s, total));
                        pred_I_total[s] = std::make_pair(buffer.first, total);
                    }

                    ++compt;
                }
            }
            
            return pred_I_total;
        }
    
        void affichageParcours (std::map<Sommet*, std::pair<Sommet*, int>> pred_I_total, int premier, int dernier)//affiche le parcours
        {
            int nbre = dernier;
            
            std::cout << m_sommets[nbre]->getNum() <<"<--";
            
            do
            {
                if(pred_I_total[m_sommets[nbre]].first->getNum() != premier)
                {
                    std::cout << pred_I_total[m_sommets[nbre]].first->getNum() << "<--";
                    nbre = pred_I_total[m_sommets[nbre]].first->getNum();
                }
                else
                {
                    std::cout<<premier << " : longeur ";
                    nbre = pred_I_total[m_sommets[nbre]].first->getNum();
                }
            }
            while(pred_I_total[m_sommets[nbre]].second != 0);
            
            nbre = dernier;
            int buffer;
            
            do
            {
                buffer = pred_I_total[m_sommets[nbre]].first->getNum();
                int poids = pred_I_total[m_sommets[nbre]].second - pred_I_total[m_sommets[buffer]].second;
            
                if(buffer != premier)
                {
                    std::cout << poids << "+";
                    nbre = buffer;
                }
                else
                    std::cout << poids << "=" << pred_I_total[m_sommets[dernier]].second <<std::endl;
            }
            while(buffer != premier);
            
        }
            
};

int main(int argc, const char * argv[])
{
    Graphe graphe{"graphe.txt"};//instance de graphe
    
    std::vector<Sommet*> pred_I;
    int premier, dernier;
    
    graphe.afficher();

    std::cout<< "Selectionner un sommet de départ pour lancer le parcours : ";
    std::cin>>premier;
    std::cout<< "Selectionner un sommet d'arrivé pour lancer le parcours : ";
    std::cin>>dernier;
    std::cout << std::endl;

    graphe.affichageParcours(graphe.disjtra(premier), premier, dernier);//affichage disjtra
    
    return 0;
}
