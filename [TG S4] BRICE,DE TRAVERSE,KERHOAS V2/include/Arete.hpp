#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED
#include "Sommet.hpp"
class Arete
{
private:
    int m_id;
    Sommet m_S1,m_S2;
    float m_ponderation=9999;
public:
    Arete(int id,Sommet S1,Sommet S2);
    Arete();
    Sommet getS1()const;
    Sommet getS2()const;
    int getId()const;
    float getPonderation()const;
    void ajouterPonderation(float ponderation);
    void afficher()const;
};
#endif // ARETE_H_INCLUDED
