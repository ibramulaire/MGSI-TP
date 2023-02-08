#ifndef DEF_SPHERE
#define DEF_SPHERE
#include "Sommet.h"
#include "Vecteur.h"
#include "Rayon.h"
#include <cmath>
#include <iostream>
#include <stdlib.h>


class Sphere
{
    
    public:
    Sommet centre ; 
    double rayon;

    Sommet firstIntersection;
    Sommet otherIntersection;


    Sphere(Sommet centre ={0,0,0}, double rayon=2);
    ~Sphere();


    Sommet getCentre();
    double getRayon();
    Vecteur getNormale(Sommet s);
    
    Sommet intersect(Rayon r);


            
};

#endif