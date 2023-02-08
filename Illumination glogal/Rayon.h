#ifndef DEF_RAYON
#define DEF_RAYON
#include<cmath>
#include "Sommet.h"
#include "Vecteur.h" 
struct Rayon {
        Sommet point;
        Vecteur direction;

        Sommet getPointAtT(double t )

        {
            Vecteur temps=direction.Foi(t);
            return point.Plus({temps.x,temps.y,temps.z});
           
        }



     
       
    }; 

#endif