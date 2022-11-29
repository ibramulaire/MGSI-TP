#ifndef DEF_HERMIT
#define DEF_HERMIT
#include "Courbes.h"

class Hermit:public Courbes
{
private:
      arma::mat hermitMat={
                            {2,-2,1,1},
                            {-3,3,-2,-1},
                            {0,0,1,0},
                            {1,0,0,0}
                        
                        };
public:
    Hermit(int nbVertex=100);
    ~Hermit();
     arma::mat getMat();
     arma::mat CalculerCourbe(double t=0);
     arma::mat Deriver(double t=0);
     arma::mat DeriverSeconde(double t=0);

     void TousCalculer();
     
};
#endif