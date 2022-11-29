#ifndef DEF_BEZIER
#define DEF_BEZIER
#include "Courbes.h"

class Bezier:public Courbes
{
private:
      arma::mat besierMat={
                            {-1,3,-3,1},
                            {3,-6,3,0},
                            {-3,3,0,0},
                            {1,0,0,0}         
                          };
public:
    Bezier(int nbVertex=100);
    ~Bezier();
     arma::mat getMat();
     arma::mat CalculerCourbe(double t=0);
     arma::mat Deriver(double t=0);
     arma::mat DeriverSeconde(double t=0);

     void TousCalculer();
     
};



#endif