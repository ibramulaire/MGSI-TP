#ifndef DEF_COURBES
#define DEF_COURBES
 
#include <iostream>

#include<armadillo>
#include <vector>
#include "Sommet.h"





class Courbes
{
private:
    Sommet S1={0,0,0};
    Sommet S2={0,1,0};
    Sommet S3={1,1,1} ;
    Sommet S4={1,0,0};
   
    arma::mat controleMat={
                        {S1.x,S1.y,S1.z},
                        {S2.x,S2.y,S2.z},
                        {S3.x,S3.y,S3.z},
                        {S4.x,S4.y,S4.z},              
                        };  


     int nbVertex;
     std::vector<Sommet>CurveVertices;
     std::vector<Sommet>Derivations;
     std::vector<Sommet>SecondDerivations;
                    
                        

public:
    Courbes(int nbVertex=100);
    ~Courbes();
    arma::mat getControleMat();
  
    int getNbVertex();
    std::vector<Sommet>&getCurveVertices() ;
    std::vector<Sommet>&getDerivations() ;
    std::vector<Sommet>&getSecondDerivations() ;

    void setCurveVertices(int i,Sommet s);
    void setDerivations(int i,Sommet s);
    void setSecondDerivations(int i,Sommet s);
};

#endif
