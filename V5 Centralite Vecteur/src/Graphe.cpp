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
    for(int i=0; i<taille; ++i)
    {
        ifs >> id1 >> poids;
        int a=0;
        for(int j=0; j<m_ListeAretes.size(); ++j)
        {
            if(m_ListeAretes[a]->getId()!=id1)
                a+=1;
            else
                m_ListeAretes[a]->ajouterPonderation(poids);
            m_ListeAretes[a]->getS1()->ajouterPoids(poids);
            m_ListeAretes[a]->getS2()->ajouterPoids(poids);
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

///Affichage console
void Graphe::afficher()
{
    std::cout<<"Liste des sommet:"<<std::endl;
    for(int i=0; i<ordre; ++i)
    {
        m_ListeSommets[i]->afficher();
    }
    std::cout<<"Liste des aretes:"<<std::endl;
    for(int i=0; i<m_ListeAretes.size(); ++i)
    {
        m_ListeAretes[i]->afficher();
    }
}
///Affichage format SVG
void Graphe::afficherSVG(Svgfile& svgout)
{
    ///Affichage sommet
    for(int i=0; i<ordre; ++i)
    {
        svgout.addCircle(m_ListeSommets[i]->getX(),m_ListeSommets[i]->getY(),5,5,"pink");
        svgout.addText(m_ListeSommets[i]->getX(),m_ListeSommets[i]->getY(),m_ListeSommets[i]->getNom(),"black");
    }
    for(int i=0; i<m_ListeAretes.size(); ++i)
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
    for(int i=0; i<m_ListeSommets.size(); ++i)
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
///Recupere la valeur du poids du PCC
float Graphe::PonderationPCC(std::map<const Sommet*, std::pair<const Sommet*, float>> pred, int premier, int dernier)
{
    return pred[m_ListeSommets[dernier]].second;
}
///Permet d'avoir la centralite du degre
void Graphe::centraliteDegre()
{
    std::ofstream ofs("Centralite De Degre.txt");
    ///Affichage console
    std::cout<<"Centralite De Degre"<<std::endl<<"Centralite Non Normalises:"<<std::endl;
    for(int i=0; i<m_ListeSommets.size(); ++i)
    {
        std::cout<<"Sommet: "<<m_ListeSommets[i]->getNom()<<" de centralite "<<m_ListeSommets[i]->getDegre()<<std::endl;
    }
    std::cout<<"Centralite Normalises:"<<std::endl;
    for(int i=0; i<m_ListeSommets.size(); ++i)
    {
        std::cout<<"Sommet: "<<m_ListeSommets[i]->getNom()<<" de centralite "<<m_ListeSommets[i]->getDegre()*100/(m_ListeSommets.size()-1)<<"%"<<std::endl;
    }
    ///Ecriture fichier
    for(int i=0; i<m_ListeSommets.size(); ++i)
    {
        ofs << m_ListeSommets[i]->getId()<<" "<<m_ListeSommets[i]->getDegre()<<" "<<m_ListeSommets[i]->getDegre()*100/(m_ListeSommets.size()-1)<<"%"<<std::endl;
    }
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
    for(int Si=0;Si<m_ListeSommets.size();++Si)
    {
        Cvp[Si]=1;
    }
    while((lambda-lambdaprecedent)>0.1)
    {
        lambdaprecedent=lambda;
        for(int Si=0;Si<m_ListeSommets.size();++Si)
        {
            C[Si]=0;
            for(int Sj=0;Sj<m_ListeSommets[Si]->getAdj().size();++Sj)
            {
                C[Si]+=Cvp[Sj];
            }
            SommeC+= C[Si]*C[Si];
        }
        lambda= sqrt(SommeC);
        for(int Si=0;Si<m_ListeSommets.size();++Si)
        {
            Cvp[Si]=C[Si]/lambda;
        }
    }
    std::cout<<"Centralite De Vecteur Propre"<<std::endl<<"Centralite Non Normalises:"<<std::endl;
    for(int i=0;i<m_ListeSommets.size();++i)
    {
        std::cout<<"Sommet: "<<m_ListeSommets[i]->getNom()<<" de centralite "<<Cvp[i]<<std::endl;
        ofs<<m_ListeSommets[i]->getId()<<" "<<Cvp[i]<<std::endl;
    }
}
///Permet d'avoir la centralite de proximite
void Graphe::centraliteProximite()
{
    std::ofstream ofs("Centralite De Poximite.txt");
    float total=0;
    std::cout<<"Centralite De Proximite"<<std::endl<<"Centralite Non Normalises:"<<std::endl;
    ///Double boucle pour faire dijkstra à tout les sommets et afficher la non normalise
    for(int i=0; i<m_ListeSommets.size(); ++i)
    {
        for(int j=0; j<m_ListeSommets.size()-1; ++j) ///-1 sommet du a l'initial
        {
            total+=PonderationPCC(Dijkstra(m_ListeSommets[i]),i,j);
        }
        std::cout<<"Sommet: "<<m_ListeSommets[i]->getNom()<<" de centralite "<<(1/total)<<std::endl;
    }
    std::cout<<std::endl<<"Centralite Normalises:"<<std::endl;
    ///Double boucle pour faire dijkstra à tout les sommets et afficher la normalise
    for(int i=0; i<m_ListeSommets.size(); ++i)
    {
        for(int j=0; j<m_ListeSommets.size()-1; ++j) ///-1 sommet du a l'initial
        {
            total+=PonderationPCC(Dijkstra(m_ListeSommets[i]),i,j);
        }
        std::cout<<"Sommet: "<<m_ListeSommets[i]->getNom()<<" de centralite "<<(m_ListeSommets.size()-1/total)<<std::endl;
    }
    ///Double boucle pour faire dijkstra à tout les sommets et ecrire les indices dans le fichier
    for(int i=0; i<m_ListeSommets.size(); ++i)
    {
        for(int j=0; j<m_ListeSommets.size()-1; ++j) ///-1 sommet du a l'initial
        {
            total+=PonderationPCC(Dijkstra(m_ListeSommets[i]),i,j);
        }
        ofs<< m_ListeSommets[i]->getId()<<" "<<(1/total)<<"   "<<(m_ListeSommets.size()-1/total)<<std::endl;
    }
}
