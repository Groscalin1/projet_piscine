#include "../include/Graphe.hpp"
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
            m_ListeSommets[id2]->ajouterAdjacents(m_ListeSommets[id1]);
        }
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
    for(int i=0; i<taille; ++i)
    {
        ifs >> id1 >> poids;
        if(orientation==1)
        {
            int j=0;
            while(m_ListeAretes[j]->getId()!=id1)
            {
                ++j;
            }
            m_ListeAretes[j]->ajouterPonderation(poids);
            m_ListeAretes[j]->getS1()->ajouterPoids(poids);

        }
        if(orientation==0)
        {
            int j=0;
            while(m_ListeAretes[j]->getId()!=id1)
            {
                ++j;
            }
            m_ListeAretes[j]->ajouterPonderation(poids);
            m_ListeAretes[j]->getS1()->ajouterPoids(poids);
            m_ListeAretes[j]->getS2()->ajouterPoids(poids);

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
int Graphe::getOrientation()const
{
    return (int)orientation;
}
///Afficher les aretes
void Graphe::afficherArete()
{
    std::cout<<"Liste des arretes :"<<std::endl;
    for(unsigned i=0; i<m_ListeAretes.size(); ++i)
    {
        std::cout<<"Arete id "<<m_ListeAretes[i]->getId()<<": liant les sommets "<<"("<<m_ListeAretes[i]->getS1()->getNom()<<","<<m_ListeAretes[i]->getS2()->getNom()<<")"<<std::endl;
    }
}
///Ajouter une arete
void Graphe::ajouterArete()
{
    system("cls");
    afficherSommet();
    std::string nom1,nom2;
    Sommet* S1;
    Sommet* S2;
    float ponde;
    if(orientation==1)
    {
        std::cout<<"Vous etes dans un graphe orienté."<<std::endl<<"Pour creer votre arete indiquez le NOM des deux sommets dans l'ordre de l'orientation et sa ponderation"<<std::endl;
        std::cin>>nom1>>nom2>>ponde;
        for(unsigned i=0;i<m_ListeSommets.size();++i)
        {
            if(m_ListeSommets[i]->getNom()==nom1)
            {
                S1=m_ListeSommets[i];
            }
            if(m_ListeSommets[i]->getNom()==nom2)
            {
                S2=m_ListeSommets[i];
            }
        }
        m_ListeAretes.push_back(new Arete(m_ListeAretes.size(),S1,S2));
        S1->ajouterAdjacents(S2);
        m_ListeAretes[m_ListeAretes.size()-1]->ajouterPonderation(ponde);
        S1->ajouterPoids(ponde);
    }
    if(orientation==0)
    {
        std::cout<<"Vous etes dans un graphe non oriente."<<std::endl<<"Pour creer votre arete indiquez le NOM des deux sommets sans ordre precis et sa ponderation"<<std::endl;
        std::cin>>nom1>>nom2>>ponde;
        for(unsigned i=0;i<m_ListeSommets.size();++i)
        {
            if(m_ListeSommets[i]->getNom()==nom1)
            {
                S1=m_ListeSommets[i];
            }
            if(m_ListeSommets[i]->getNom()==nom2)
            {
                S2=m_ListeSommets[i];
            }
        }
        m_ListeAretes.push_back(new Arete(m_ListeAretes.size(),S1,S2));
        S1->ajouterAdjacents(S2);
        S2->ajouterAdjacents(S1);
        m_ListeAretes[m_ListeAretes.size()-1]->ajouterPonderation(ponde);
        S1->ajouterPoids(ponde);
        S2->ajouterPoids(ponde);
    }
    afficherSVG();
}
///Supprimer une arete
void Graphe::supprimerArete(int id)
{
    for(unsigned i=0; i<m_ListeAretes.size(); ++i)
    {
        if(m_ListeAretes[i]->getId()== id)
        {
            m_ListeAretes[i]->getS1()->supprimerAdjacents(m_ListeAretes[i]->getS2());
            m_ListeAretes[i]->getS2()->supprimerAdjacents(m_ListeAretes[i]->getS1());
            m_ListeAretes.erase(m_ListeAretes.begin()+i);
        }
    }
    for(unsigned i=0;i<m_ListeAretes.size();++i)
    {
        m_ListeAretes[i]->changerId(i);
    }
    ///on actualise le svg
    afficherSVG();
}
///Afficher tout les sommets
void Graphe::afficherSommet()
{
    std::cout<<"Liste des Sommets :"<<std::endl;
    for(unsigned i=0; i<m_ListeSommets.size(); ++i)
    {
        std::cout<<"Sommet :"<<m_ListeSommets[i]->getNom()<<" d'id "<<m_ListeSommets[i]->getId()<<" (x,y) "<<"("<<m_ListeSommets[i]->getX()<<","<<m_ListeSommets[i]->getX()<<")"<<std::endl;
    }
}
///Ajouter un sommet
void Graphe::ajouterSommet()
{
    system("cls");
    afficherSommet();
    std::string nom;
    int x,y;
    std::cout<<"Entre le nom puis les coordonnees du nouveau sommet (x puis y):"<<std::endl;
    std::cin>>nom>>x>>y;
    m_ListeSommets.push_back(new Sommet(m_ListeSommets.size(),nom,x,y));
    afficherSVG();

}
///Supprimer un sommet
void Graphe::supprimerSommet()
{
    system("cls");
    std::string nom;
    afficherSommet();
    std::cout<<"Tapez le nom du sommet a supprimer:"<<std::endl;
    std::cin>>nom;
    for(unsigned i=0;i<m_ListeAretes.size();++i)
    {
        if(m_ListeAretes[i]->getS1()->getNom()==nom || m_ListeAretes[i]->getS2()->getNom()==nom)
        {
            supprimerArete(m_ListeAretes[i]->getId());
            i=0;
        }
    }
    for(unsigned i=0;i<m_ListeSommets.size();++i)
    {
        if(m_ListeSommets[i]->getNom()==nom)
        {
            m_ListeSommets.erase(m_ListeSommets.begin()+i);
        }
    }
    for(unsigned i=0;i<m_ListeSommets.size();++i)
    {
        m_ListeSommets[i]->changerId(i);
    }
    afficherSVG();
}
///Affichage console
void Graphe::afficher()
{
    afficherSommet();
    std::cout<<std::endl;
    afficherArete();
}
///Affichage format SVG
void Graphe::afficherSVG()
{
    Svgfile svgout;
    svgout.addGrid();
    ///Affichage sommet
    for(unsigned i=0; i<m_ListeSommets.size(); ++i)
    {
        svgout.addCircle(m_ListeSommets[i]->getX(),m_ListeSommets[i]->getY(),5,5,m_ListeSommets[i]->getCouleur());
        svgout.addText(m_ListeSommets[i]->getX(),m_ListeSommets[i]->getY(),m_ListeSommets[i]->getNom(),"black");
        if(m_ListeSommets[i]->getIndice()!=0)
        {
            svgout.addText(m_ListeSommets[i]->getX()+15,m_ListeSommets[i]->getY(),m_ListeSommets[i]->getIndice(),"black");
        }
    }
    for(unsigned i=0; i<m_ListeAretes.size(); ++i)
    {
        svgout.addLine(m_ListeAretes[i]->getS1()->getX(),m_ListeAretes[i]->getS1()->getY(),m_ListeAretes[i]->getS2()->getX(),m_ListeAretes[i]->getS2()->getY(),"black");
        if(m_ListeAretes[i]->getPonderation()!=9999)
        {
            ///Recupere le milieu de l'arete
            double x=(m_ListeAretes[i]->getS1()->getX()+m_ListeAretes[i]->getS2()->getX())/2;
            double y=(m_ListeAretes[i]->getS1()->getY()+m_ListeAretes[i]->getS2()->getY())/2;
            svgout.addText(x,y+15,m_ListeAretes[i]->getPonderation(),"blue");
        }
    }
}
///Sauvegarder le graphe actuel
void Graphe::sauvegarderGraphe()
{
    std::string nomFichier;
    std::cout<<"Veuillez saisir le nom de votre fichier; (sans precisé si c'est topologique ou ponderation)"<<std::endl;
    std::cin>>nomFichier;
    std::ofstream topo(nomFichier+"_topo"+".txt");
    topo<<orientation<<std::endl<<m_ListeSommets.size()<<std::endl;
    for(unsigned i=0;i<m_ListeSommets.size();++i)
    {
        topo<<m_ListeSommets[i]->getId()<<" "<<m_ListeSommets[i]->getNom()<<" "<<m_ListeSommets[i]->getX()/100<<" "<<m_ListeSommets[i]->getY()/100<<std::endl;
    }
    topo<<m_ListeAretes.size()<<std::endl;
    for(unsigned i=0;i<m_ListeAretes.size();++i)
    {
        topo<<m_ListeAretes[i]->getId()<<" "<<m_ListeAretes[i]->getS1()->getId()<<" "<<m_ListeAretes[i]->getS2()->getId()<<std::endl;
    }
    topo.close();
    std::ofstream ponde(nomFichier+"_ponde"+".txt");
    ponde<<m_ListeAretes.size()<<std::endl;
    for(unsigned i=0;i<m_ListeAretes.size();++i)
    {
        ponde<<m_ListeAretes[i]->getId()<<" "<<m_ListeAretes[i]->getPonderation()<<std::endl;
    }
    ponde.close();
}
///Dijkstra d'un sommet initial à un sommet final
std::map<const Sommet*, std::pair<const Sommet*, float>>Graphe::Dijkstra(Sommet *initial)const
{
    ///Création de la file d'attente avec priorité (Mme Palasi)
    auto cmp = [](std::pair<const Sommet*,float> p1, std::pair<const Sommet*,float> p2)
    {
        return p2.second<p1.second;
    };
    /// déclaration de la file de priorité
    std::priority_queue<std::pair<const Sommet*,float>,std::vector<std::pair<const Sommet*,float>>,decltype(cmp)> file(cmp);

    ///On initialise la liste des prédécesseurs avec un float correspondant au poids
    std::map<const Sommet*, std::pair<const Sommet*, float>> pred;

    ///On initialise tout les sommets comme non vu
    bool *vue= new bool[m_ListeSommets.size()];
    for(unsigned i=0; i<m_ListeSommets.size(); ++i)
        vue[i]=false;

    ///On crée une paire
    file.push(std::make_pair(initial,0));
    vue[initial->getId()]=true;

    ///Boucle d'analyse
    while(!file.empty())
    {
        int compteur=0;
        std::pair<const Sommet*,float>p;
        ///A chaque tour de boucle on fixe p la paire prioritaire, qu'on enleve de la file
        p=file.top();
        file.pop();

        for(auto s : p.first->getAdj())
        {
            float total= p.second + p.first->getPoids()[compteur];
            if(vue[s->getId()]==false || pred[s].second > total)
            {
                vue[s->getId()]=true;
                file.push(std::make_pair(s, total));
                pred[s]=std::make_pair(p.first,total);
            }
            ++compteur;
        }
    }
    return pred;
}
///Dijkstra compte le nombre de fois d'un PCC d'un sommet initial à un sommet final
std::pair<int,int>Graphe::DijkstraAdapte(Sommet *intermediaire,Sommet* initial,Sommet* fin)const
{
    ///Création de la file d'attente avec priorité (Mme Palasi)
    auto cmp = [](std::pair<const Sommet*,float> p1, std::pair<const Sommet*,float> p2)
    {
        return p2.second<p1.second;
    };
    /// déclaration de la file de priorité
    std::priority_queue<std::pair<const Sommet*,float>,std::vector<std::pair<const Sommet*,float>>,decltype(cmp)> file(cmp);

    ///On initialise la liste des prédécesseurs avec un float correspondant au poids
    std::map<const Sommet*, std::pair<const Sommet*, float>> pred;

    ///On initialise tout les sommets comme non vu
    bool *vue= new bool[m_ListeSommets.size()];
    for(unsigned i=0; i<m_ListeSommets.size(); ++i)
        vue[i]=false;

    ///On crée une paire
    file.push(std::make_pair(initial,0));
    vue[initial->getId()]=true;

    ///On ajoute nos deux variables qu'on va return le NbrDePcc et si on passe par le sommet intermediaire
    int nbrIntermediaire=0;
    int nbrPcc=1;
    ///Boucle d'analyse
    while(vue[fin->getId()]!=true)
    {
        ///Le compteur permet de se deplacer dans le vecteur poids du sommet plutot qu'aller chercher le poids de l'arete associé entre les deux sommets
        int compteur=0;
        float total;
        std::pair<const Sommet*,float>p;
        ///A chaque tour de boucle on fixe p la paire prioritaire, qu'on enleve de la file
        p=file.top();
        file.pop();

        for(auto s : p.first->getAdj())
        {
            total= p.second + p.first->getPoids()[compteur];
            if(vue[s->getId()]==false || pred[s].second > total)
            {
                if(pred[s].second==total)
                {
                    nbrPcc++;
                }
                if(p.first->getId()==intermediaire->getId())
                {
                    nbrIntermediaire++;
                }
                vue[s->getId()]=true;
                file.push(std::make_pair(s, total));
                pred[s]=std::make_pair(p.first,total);
                ///Si il croise le sommet on incremente son compteur
            }
            ++compteur;
        }
    }
    ///Création de la paire avec les int a return
    std::pair<int,int>totaux;
    totaux.first=nbrIntermediaire;
    totaux.second=nbrPcc;
    return totaux;
}
///Affichage de dijkstra pour les tests
void Graphe::affichageParcours (std::map<const Sommet*, std::pair<const Sommet*, float>> pred, int premier, int dernier)//affiche le parcours
{
    int nbre = dernier;

    std::cout << m_ListeSommets[nbre]->getId() <<"<--";

    do
    {
        if(pred[m_ListeSommets[nbre]].first->getId() != premier)
        {
            std::cout << pred[m_ListeSommets[nbre]].first->getId() << "<--";
            nbre = pred[m_ListeSommets[nbre]].first->getId();
        }
        else
        {
            std::cout<<premier << " : longeur ";
            nbre = pred[m_ListeSommets[nbre]].first->getId();
        }
    }
    while(pred[m_ListeSommets[nbre]].second != 0);

    nbre = dernier;
    int p;

    do
    {
        p = pred[m_ListeSommets[nbre]].first->getId();
        float poids = pred[m_ListeSommets[nbre]].second - pred[m_ListeSommets[p]].second;

        if(p != premier)
        {
            std::cout << poids << "+";
            nbre = p;
        }
        else
            std::cout << poids << "=" << pred[m_ListeSommets[dernier]].second <<std::endl;
    }
    while(p != premier);
}
///Recupere la valeur de ponderation du PCC
float Graphe::PonderationPCC(std::map<const Sommet*, std::pair<const Sommet*, float>> pred, int premier, int dernier)
{
    return pred[m_ListeSommets[dernier]].second;
}
///BFS TP2 Brice De Traverse
std::vector<int> Graphe::bfs(Sommet *initial)const
{
    ///Création de la file d'attente
    std::queue<int> file;

    ///On initialise tout les sommets comme non vu
    bool *vue= new bool[m_ListeSommets.size()];
    for(unsigned i=0; i<m_ListeSommets.size(); ++i)
    {
        vue[i]=false;
    }

    ///On initialise le premier comme vu et on le place en premier de la file
    int premier=initial->getId();
    vue[premier]=true;
    file.push(premier);
    ///On initialise la liste des prédécesseurs avec un int correspondant a l'Id
    std::vector<int> preds((int)m_ListeSommets.size(),-1);
    ///Boucle d'analyse
    while(!file.empty())
    {
        ///A chaque tour de boucle le premier est initialisé comme le premier de la file
        premier=file.front();
        file.pop();
        /// std::cout<<premier<<std::endl; Test pour bfs avant d'utilisé l'affichage
        std::vector<const Sommet*>Adj=getListe()[premier]->getAdj();
        ///Boucle qui vérifie si les adjacents sont vues
        for(int i=0; i<getListe()[premier]->getDegre(); i++)
        {
            if(vue[Adj[i]->getId()]!=true)
            {
                vue[Adj[i]->getId()]=true;
                file.push(Adj[i]->getId());
                preds[Adj[i]->getId()]=premier;
            }
        }
    }
    return preds;
}
///DFS TP2 Brice De Traverse
std::vector<int> Graphe::dfs(Sommet *initial)const
{
    ///Création de la pile d'attente
    std::stack<int> pile;

    ///On initialise tout les sommets comme non vue
    bool *vue= new bool[m_ListeSommets.size()];
    for(unsigned i=0; i<m_ListeSommets.size(); ++i)
    {
        vue[i]=false;
    }

    ///On initialise le premier comme vue et on le place en premier de la file
    int premier=initial->getId();
    vue[premier]=true;
    pile.push(premier);
    ///On initialise la liste des prédécesseurs avec un int correspondant a l'Id
    std::vector<int> preds((int)m_ListeSommets.size(),-1);
    ///Boucle d'analyse
    while(!pile.empty())
    {
        ///A chaque tour de boucle le premier est initialisé comme le premier de la file
        premier=pile.top();
        pile.pop();
        /// std::cout<<premier<<std::endl; Test pour bfs avant d'utilisé l'affichage
        std::vector<const Sommet*>Adj=getListe()[premier]->getAdj();
        ///Boucle qui vérifie si les adjacents sont vues
        for(int i=0; i<getListe()[premier]->getDegre(); i++)
        {
            if(vue[Adj[i]->getId()]!=true)
            {
                vue[Adj[i]->getId()]=true;
                pile.push(Adj[i]->getId());
                preds[Adj[i]->getId()]=premier;
            }
        }
    }
    return preds;
}
///recherche et affichage des composantes connexes ( CODE MME PALASI) + modification pour afficher le nom sommet plutot que l'indice
void Graphe::rechercher_afficher_CC()
{
    size_t num=0;
    bool test;
    int ncc=0;
    std::vector<Sommet*> initial=getListe();
    ///pour noter les numéros de CC
    std::vector<int> cc(m_ListeSommets.size(),-1);
    do
    {
        cc[num]=num;
        std::cout<<std::endl<<"composante connexe numero "<<(ncc +1)<<" : "<<m_ListeSommets[num]->getNom()<<" ";
        ncc++;
        ///lancement d'un BFS sur le sommet num
        std::vector<int> arbre_BFS=bfs(initial[num]);
        ///affichage des sommets decouverts lors du parcours (ceux qui ont un predecesseur
        for(size_t i=0; i<arbre_BFS.size(); ++i)
        {
            if ((i!=num)&&(arbre_BFS[i]!=-1))
            {
                cc[i]=num;
                std::cout<<m_ListeSommets[i]->getNom()<<" ";
            }
        }
        ///recherche d'un sommet non exploré
        ///pour relancer un BFS au prochain tour
        test=false;
        for(unsigned i=0; i<m_ListeSommets.size(); ++i)
        {
            if (cc[i]==-1)
            {
                num=i;
                test=true;
                break;
            }
        }
    }
    while(test==true);
    std::cout<<std::endl;
}

///Affichage des composantes de forte connexite
void Graphe::rechercher_afficher_CFC()
{
    size_t num=0;
    bool test;
    int ncfc=0;
    ///pour noter les numéros de CFC
    std::vector<int> cfc(m_ListeSommets.size(),-1);
    do
    {
        cfc[num]=num;
        std::cout<<std::endl<<"composante fortement connexe numero "<<(ncfc +1)<<" : "<<m_ListeSommets[num]->getNom()<<" ";
        ncfc++;
        ///lancement d'un DFS sur le sommet num
        std::vector<int> arbre_DFS=dfs(m_ListeSommets[num]);
        ///affichage des sommets decouverts lors du parcours (ceux qui ont un predecesseur
        for(size_t i=0; i<arbre_DFS.size(); ++i)
        {
            if ((i!=num)&&(arbre_DFS[i]!=-1))
            {
                arbre_DFS=dfs(m_ListeSommets[i]);
                if(arbre_DFS[num]!=-1)
                {
                    cfc[i]=num;
                    std::cout<<m_ListeSommets[i]->getNom()<<" ";
                }
            }
        }
        ///recherche d'un sommet non exploré
        ///pour relancer un DFS au prochain tour
        test=false;
        for(unsigned i=0; i<m_ListeSommets.size(); ++i)
        {
            if (cfc[i]==-1)
            {
                num=i;
                test=true;
                break;
            }
        }
    }
    while(test==true);
    std::cout<<std::endl;
}
void Graphe::centraliteDegre()
{
    std::ofstream ofs("Centralite De Degre.txt");
    ///Affichage console
    std::cout<<"Centralite De Degre"<<std::endl;
    for(unsigned i=0; i<m_ListeSommets.size(); ++i)
    {
        std::cout<<"Sommet: "<<m_ListeSommets[i]->getNom()<<" de centralite non normalise "<<m_ListeSommets[i]->getDegre()<<" de centralite normalise "<<m_ListeSommets[i]->getDegre()*100/(m_ListeSommets.size()-1)<<"%"<<std::endl;
        if(m_ListeSommets[i]->getDegre()*100/(m_ListeSommets.size()-1)>80)
        {
            m_ListeSommets[i]->changercouleur("red");
        }
        if(m_ListeSommets[i]->getDegre()*100/(m_ListeSommets.size()-1)<80 && m_ListeSommets[i]->getDegre()*100/(m_ListeSommets.size()-1)>50)
        {
            m_ListeSommets[i]->changercouleur("orange");
        }
        if(m_ListeSommets[i]->getDegre()*100/(m_ListeSommets.size()-1)<50 && m_ListeSommets[i]->getDegre()*100/(m_ListeSommets.size()-1)>30)
        {
            m_ListeSommets[i]->changercouleur("pink");
        }
        m_ListeSommets[i]->ajouterIndice(m_ListeSommets[i]->getDegre()/(m_ListeSommets.size()-1));
        ofs << m_ListeSommets[i]->getId()<<" "<<m_ListeSommets[i]->getDegre()<<" "<<m_ListeSommets[i]->getDegre()*100/(m_ListeSommets.size()-1)<<"%"<<std::endl;
    }
    afficherSVG();
}
///premet d'avoir la centralite de vecteur propre
void Graphe::centraliteVecteurPropre()
{
    ///INITIALISATION
    double lambda=1;
    double lambdaprecedent=0;
    double SommeC=0;
    std::ofstream ofs("Centralite De Vecteur Propre.txt");
    ///Initialisation de tout les Centralites de Vecteurs Propres à 1 (Si = Sommet indice i)
    std::vector<double> C(sizeof(m_ListeSommets));
    std::vector<double> Cvp(sizeof(m_ListeSommets));
    for(unsigned Si=0; Si<m_ListeSommets.size(); ++Si)
    {
        Cvp[Si]=1;
    }
    while((lambda-lambdaprecedent)>0.1)
    {
        lambdaprecedent=lambda;
        SommeC=0;
        for(unsigned Si=0; Si<m_ListeSommets.size(); ++Si)
        {
            C[Si]=0;
            for(unsigned Sj=0; Sj<m_ListeSommets[Si]->getAdj().size(); ++Sj)
            {
                C[Si]+=Cvp[m_ListeSommets[Si]->getAdj()[Sj]->getId()];
            }
            SommeC+= C[Si]*C[Si];
        }
        lambda= sqrt(SommeC);
        for(unsigned Si=0; Si<m_ListeSommets.size(); ++Si)
        {
            Cvp[Si]=C[Si]/lambda;
        }
    }
    std::cout<<"Centralite De Vecteur Propre"<<std::endl;
    for(unsigned i=0; i<m_ListeSommets.size(); ++i)
    {
        std::cout<<"Sommet: "<<m_ListeSommets[i]->getNom()<<" de centralite non normalise "<<Cvp[i]<<std::endl;
        ofs<<m_ListeSommets[i]->getId()<<" "<<Cvp[i]<<std::endl;
        if(Cvp[i]>0.8)
        {
            m_ListeSommets[i]->changercouleur("red");
        }
        if(Cvp[i]<0.8 && Cvp[i]>0.5)
        {
            m_ListeSommets[i]->changercouleur("orange");
        }
        if(Cvp[i]<0.5 && Cvp[i]>0.3)
        {
            m_ListeSommets[i]->changercouleur("pink");
        }
        m_ListeSommets[i]->ajouterIndice(Cvp[i]);
    }
    afficherSVG();
}
///Permet d'avoir la centralite de proximite
void Graphe::centraliteProximite()
{
    std::ofstream ofs("Centralite De Proximite.txt");
    float total;
    std::cout<<"Centralite De Proximite"<<std::endl;
    ///Double boucle pour faire dijkstra à tout les sommets et afficher la non normalise
    for(unsigned i=0; i<m_ListeSommets.size(); ++i)
    {
        total=0;
        for(unsigned j=0; j<m_ListeSommets.size()-1; ++j) ///-1 sommet du a l'initial
        {
            total+=PonderationPCC(Dijkstra(m_ListeSommets[i]),i,j);
        }
        std::cout<<"Sommet: "<<m_ListeSommets[i]->getNom()<<" de centralite non normalise "<<(1/total)<<" de centralite normalise "<<((m_ListeSommets.size()-1)/total)<<std::endl;
        ofs<< m_ListeSommets[i]->getId()<<" "<<(1/total)<<"   "<<((m_ListeSommets.size()-1)/total)<<std::endl;
        if((1/total)>0.8)
        {
            m_ListeSommets[i]->changercouleur("red");
        }
        if((1/total)<0.8 && ((m_ListeSommets.size()-1)/total)>0.5)
        {
            m_ListeSommets[i]->changercouleur("orange");
        }
        if((1/total)<0.5 && ((m_ListeSommets.size()-1)/total)>0.3)
        {
            m_ListeSommets[i]->changercouleur("pink");
        }
        m_ListeSommets[i]->ajouterIndice(((m_ListeSommets.size()-1)/total));
    }
    afficherSVG();
}
///Permet d'obtenir la centralite d'intermediarite
void Graphe::centraliteIntermediaire()
{
    ///On utilise les notations Si,Sj,Sj comme dans l'exemple du sujet pour plus de clarté
    ///Initialisation
    std::ofstream ofs("Centralite D'Intermediarite.txt");
    float centralite=0;
    int i=0;
    bool pairexistente=false;
    double NbrIntermediaire=0;
    double NbrPcc=0;
    ///Boucle qui etudie la centralite d'intermediarite de chaque sommet
    for(unsigned Si=0; Si<m_ListeSommets.size(); ++Si)
    {
        centralite=0;
        i=0;
        ///On creer un tableau de couple de sommet de taille maximale (n-1)(n-2)/2 (formule mathématique classique(n(n-1)/2) mais on enleve une possibilité de couple avec l'intermediaire
        std::pair<unsigned,unsigned>Couple[(m_ListeSommets.size()-1)*(m_ListeSommets.size()-2)/2];
        for(unsigned Sj=0; Sj<m_ListeSommets.size(); ++Sj)
        {
            if(Sj!=Si)
            {
                for(unsigned Sk=0; Sk<m_ListeSommets.size(); ++Sk)
                {
                    if(Sk!=Sj && Sk!=Si)
                    {
                        pairexistente=false;
                        std::pair<unsigned,unsigned>NouvCouple;
                        NouvCouple.first=Sj;
                        NouvCouple.second=Sk;
                        std::pair<unsigned,unsigned>NouvCouple2;
                        NouvCouple2.first=Sk;
                        NouvCouple2.second=Sj;
                        for(unsigned i=0; i<(m_ListeSommets.size()-1)*(m_ListeSommets.size()-2)/2; ++i)
                        {
                            if(NouvCouple==Couple[i] || NouvCouple2==Couple[i])
                            {
                                pairexistente=true;
                            }
                        }
                        if(pairexistente==false)
                        {
                            Couple[i].first=Sj;
                            Couple[i].second=Sk;
                            ++i;
                            ///Appel de djisktra adapte dans chaque morceau de la paire
                            NbrIntermediaire=DijkstraAdapte(m_ListeSommets[Si],m_ListeSommets[Sj],m_ListeSommets[Sk]).first;
                            NbrPcc=DijkstraAdapte(m_ListeSommets[Si],m_ListeSommets[Sj],m_ListeSommets[Sk]).second;
                            centralite+= (NbrIntermediaire)/(NbrPcc);
                            std::cout<<"De "<<m_ListeSommets[Sj]->getNom()<<" a "<<m_ListeSommets[Sk]->getNom()<<" nbr intermediaire ="<<NbrIntermediaire<<" nbr de pcc="<<NbrPcc<<std::endl;
                        }
                    }
                }
            }
        }
        ///Ecriture console et ofs
        std::cout<<"Sommet: "<<m_ListeSommets[Si]->getNom()<<" de centralite "<<centralite<<std::endl;
    }

}
///Test la vulnérabilité: 1 en supprimant des arretes,2 en testant la connexité,3 en recalculant et comparant les indices obtenus
void Graphe::Vulnerabilite()
{
    ///Si jamais des modifications ont eux lieu avant de lancer la vulnerabilite on lance les centralites pour actualiser les bonnes valeurs
    centraliteDegre();
    centraliteProximite();
    centraliteVecteurPropre();
    int nbrArete;
    int id;
    system("cls");
    std::cout<<"Vous allez tester la vulnerabilite."<<std::endl<<"Vous devez choisir le nombre d'aretes a supprimer :"<<std::endl;
    std::cin>>nbrArete;
    if(orientation==0 && nbrArete>0)
    {
        for(int i=0; i<nbrArete; i++)
        {
            system("cls");
            afficherArete();
            std::cout<<"Indiquez l'id de la "<<i+1<<" arete a supprimer:"<<std::endl;
            std::cin>>id;
            supprimerArete(id);
        }
        system("cls");
        std::cout<<"Test de la connexite:";
        rechercher_afficher_CC();
        std::cout<<std::endl;
        ///Comparaison des centralite
        ///Centralite de degre
        std::ifstream ifs("Centralite De Degre.txt");
        std::cout<<"Centralite De Degre avant modification"<<std::endl;
        float id,c,cn;
        std::vector<std::pair<float,float>>centralite(sizeof(m_ListeSommets.size()));
        char pourcent;
        for(unsigned i=0; i<m_ListeSommets.size(); ++i)
        {
            ifs >> id >> c >> cn>> pourcent;
            std::cout<<"Sommet: "<<m_ListeSommets[id]->getNom()<<" de centralite non normalise "<<c<<" de centralite normalise "<<cn<<pourcent<<std::endl;
            centralite[i].first=c;
            centralite[i].second=cn;
        }
        std::cout<<std::endl;
        ifs.close();
        centraliteDegre();
        ///On va faire la difference
        std::cout<<"Difference :"<<std::endl;
        ifs.open("Centralite De Degre.txt");
        for(unsigned i=0; i<m_ListeSommets.size(); ++i)
        {
            ifs >> id >> c >> cn>> pourcent;
            std::cout<<"Sommet: "<<m_ListeSommets[id]->getNom()<<"diff de centralite non normalise "<<c-centralite[i].first<<" diff de centralite normalise "<<cn-centralite[i].second<<pourcent<<std::endl;
        }
        ifs.close();
        std::cout<<std::endl;
        ifs.open("Centralite De Vecteur Propre.txt");
        std::cout<<"Centralite De Vecteur Propre avant modification"<<std::endl;
        for(unsigned i=0; i<m_ListeSommets.size(); ++i)
        {
            ifs >> id >> c;
            std::cout<<"Sommet: "<<m_ListeSommets[id]->getNom()<<" de centralite non normalise "<<c<<std::endl;
            centralite[i].first=c;
            centralite[i].second=0;
        }
        std::cout<<std::endl;
        centraliteVecteurPropre();
        ifs.close();
        std::cout<<"Difference :"<<std::endl;
        ifs.open("Centralite De Vecteur Propre.txt");
        for(unsigned i=0; i<m_ListeSommets.size(); ++i)
        {
            ifs >> id >> c;
            std::cout<<"Sommet: "<<m_ListeSommets[id]->getNom()<<" diff de centralite non normalise "<<c-centralite[i].first<<std::endl;
        }
        ifs.close();
        std::cout<<std::endl;
        ifs.open("Centralite De Proximite.txt");
        std::cout<<"Centralite De Proximite avant modification"<<std::endl;
        for(unsigned i=0; i<m_ListeSommets.size(); ++i)
        {
            ifs >> id >> c>>cn;
            std::cout<<"Sommet: "<<m_ListeSommets[id]->getNom()<<" de centralite non normalise "<<c<<" de centralite normalise "<<cn<<std::endl;
            centralite[i].first=c;
            centralite[i].second=cn;
        }
        std::cout<<std::endl;
        centraliteProximite();
        ifs.close();
        std::cout<<"Difference :"<<std::endl;
        ifs.open("Centralite De Proximite.txt");
        for(unsigned i=0; i<m_ListeSommets.size(); ++i)
        {
            ifs >> id >> c>>cn;
            std::cout<<"Sommet: "<<m_ListeSommets[id]->getNom()<<" de centralite non normalise "<<c-centralite[i].first<<" de centralite normalise "<<cn-centralite[i].second<<std::endl;
        }
        std::cout<<std::endl;

    }
    if(orientation==1 && nbrArete>0)
    {
        for(int i=0; i<nbrArete; i++)
        {
            system("cls");
            afficherArete();
            std::cout<<"Indiquez l'id de la "<<i+1<<" arete a supprimer:"<<std::endl;
            std::cin>>id;
            supprimerArete(id);
        }
        system("cls");
        std::cout<<"Test de la forte connexite:";
        rechercher_afficher_CFC();
        std::cout<<std::endl;
        ///Comparaison des centralite
        ///Centralite de degre
        std::ifstream ifs("Centralite De Degre.txt");
        std::cout<<"Centralite De Degre avant modification"<<std::endl;
        float id,c,cn;
        std::vector<std::pair<float,float>>centralite(sizeof(m_ListeSommets.size()));
        char pourcent;
        for(unsigned i=0; i<m_ListeSommets.size(); ++i)
        {
            ifs >> id >> c >> cn>> pourcent;
            std::cout<<"Sommet: "<<m_ListeSommets[id]->getNom()<<" de centralite non normalise "<<c<<" de centralite normalise "<<cn<<pourcent<<std::endl;
            centralite[i].first=c;
            centralite[i].second=cn;
        }
        std::cout<<std::endl;
        ifs.close();
        centraliteDegre();
        ///On va faire la difference
        std::cout<<"Difference :"<<std::endl;
        ifs.open("Centralite De Degre.txt");
        for(unsigned i=0; i<m_ListeSommets.size(); ++i)
        {
            ifs >> id >> c >> cn>> pourcent;
            std::cout<<"Sommet: "<<m_ListeSommets[id]->getNom()<<"diff de centralite non normalise "<<c-centralite[i].first<<" diff de centralite normalise "<<cn-centralite[i].second<<pourcent<<std::endl;
        }
        ifs.close();
        std::cout<<std::endl;
        ifs.open("Centralite De Vecteur Propre.txt");
        std::cout<<"Centralite De Vecteur Propre avant modification"<<std::endl;
        for(unsigned i=0; i<m_ListeSommets.size(); ++i)
        {
            ifs >> id >> c;
            std::cout<<"Sommet: "<<m_ListeSommets[id]->getNom()<<" de centralite non normalise "<<c<<std::endl;
            centralite[i].first=c;
            centralite[i].second=0;
        }
        std::cout<<std::endl;
        centraliteVecteurPropre();
        ifs.close();
        std::cout<<"Difference :"<<std::endl;
        ifs.open("Centralite De Vecteur Propre.txt");
        for(unsigned i=0; i<m_ListeSommets.size(); ++i)
        {
            ifs >> id >> c;
            std::cout<<"Sommet: "<<m_ListeSommets[id]->getNom()<<" diff de centralite non normalise "<<c-centralite[i].first<<std::endl;
        }
        ifs.close();
        std::cout<<std::endl;
        ifs.open("Centralite De Proximite.txt");
        std::cout<<"Centralite De Proximite avant modification"<<std::endl;
        for(unsigned i=0; i<m_ListeSommets.size(); ++i)
        {
            ifs >> id >> c>>cn;
            std::cout<<"Sommet: "<<m_ListeSommets[id]->getNom()<<" de centralite non normalise "<<c<<" de centralite normalise "<<cn<<std::endl;
            centralite[i].first=c;
            centralite[i].second=cn;
        }
        std::cout<<std::endl;
        centraliteProximite();
        ifs.close();
        std::cout<<"Difference :"<<std::endl;
        ifs.open("Centralite De Proximite.txt");
        for(unsigned i=0; i<m_ListeSommets.size(); ++i)
        {
            ifs >> id >> c>>cn;
            std::cout<<"Sommet: "<<m_ListeSommets[id]->getNom()<<" de centralite non normalise "<<c-centralite[i].first<<" de centralite normalise "<<cn-centralite[i].second<<std::endl;
        }
        std::cout<<std::endl;

    }
}
