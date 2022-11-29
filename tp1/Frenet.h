#ifndef DEF_FRENET
#define DEF_FRENET
#include <iostream>

#include<armadillo>
#include <vector>
#include "Courbes.h"
struct Cercle
{
    Sommet centre;
    double rayon;
    std::vector<Sommet> Point;
  
    
};


class Frenet
{
private:
std::vector<Sommet>vecTangent;
std::vector<Sommet>vecNormale;
std::vector<Sommet>VecOxulateur;
std::vector<Cercle> cercles;
std::vector<Cercle> CerclesBalayant;

double RayonExtrusion;
public:
    Frenet(double RayonExtrusion=1);
    ~Frenet();
    void setRayonExtrusion(double rayon=1);
    std::vector<Sommet>&getvecTangent() ;
    std::vector<Sommet>&getvecNormale() ;
    std::vector<Sommet>&getVecOxulateur();
    std::vector<Cercle>&getCercles() ;
    std::vector<Cercle>&getCerclesBalayant() ;
    void TousCalculer(Courbes c);
};





#endif