#ifndef DEF_COURBE
#define DEF_COURBE

#include <armadillo>

typedef struct {

        double x;
        double y;
        double z;
       
} Sommet ;
class Courbe
{
    public:
    Courbe();



    Sommet S1={0,0,0};
    Sommet S2={0,1,0};
    Sommet S3={1,1,0} ;
    Sommet S4={1,0,0};
    int type=1;
 
    arma::mat Besier={
                        {-1,3,-3,1},
                        {3,-6,3,0},
                        {-3,3,0,0},
                        {1,0,0,0}
                        
                        };

    arma::mat controle={
                        {S1.x,S1.y,S1.z},
                        {S2.x,S2.y,S2.z},
                        {S3.x,S3.y,S3.z},
                        {S4.x,S4.y,S4.z}
                                        
                        };  


    
    
    arma::mat Calculer(double t,int n);
    arma::mat CalculerFrenet(double t,int n);
    arma::mat CalculerFrenetse(double t,int n);
    protected:
    
           
};

#endif

