#ifndef DEF_COURBE
#define DEF_COURBE

#include <armadillo>
#include <vector>
typedef struct {

        double x;
        double y;
        double z;
       
} Sommet ;
class Surface
{
    public:
    Surface();

    Sommet grille[4][4];

    Sommet S1={-1,-0.5,0};
    Sommet S2={-0.5,-0.5,0.3};
    Sommet S3={0,-0.5,0.3} ;
    Sommet S4={0.5,-0.5,0};

    Sommet S5={-1,1,0};
    Sommet S6={-0.5,1,0};
    Sommet S7={0,1,1};
    Sommet S8={0.5,1,0};

    Sommet S9={-1,1.5,0};
    Sommet S10={-0.5,1.5,0};
    Sommet S11={0,1.5,0};
    Sommet S12={0.5,1.5,0};


    Sommet S13={-1,2,0};
    Sommet S14={-0.5,2,0};
    Sommet S15={0,2,0};
    Sommet S16={0.5,2,0};

 
    arma::mat Besier={
                        {-1,3,-3,1},
                        {3,-6,3,0},
                        {-3,3,0,0},
                        {1,0,0,0}
                        
                        };

    arma::mat controlei1={
                            {S1.x,S1.y,S1.z},
                            {S2.x,S2.y,S2.z},
                            {S3.x,S3.y,S3.z},
                            {S4.x,S4.y,S4.z}
                        };

    arma::mat controlei2={

                            {S5.x,S5.y,S5.z},
                            {S6.x,S6.y,S6.z},
                            {S7.x,S7.y,S7.z},
                            {S8.x,S8.y,S8.z}
                        };

     arma::mat controlei3={
                            {S9.x,S9.y,S9.z},
                            {S10.x,S10.y,S10.z},
                            {S11.x,S11.y,S11.z},
                            {S12.x,S12.y,S12.z}
                        };

    arma::mat controlei4={
                            {S13.x,S13.y,S13.z},
                            {S14.x,S14.y,S14.z},
                            {S15.x,S15.y,S15.z},
                            {S16.x,S16.y,S16.z}                          
                        };  


  std::vector<arma::mat> tenseur;


    
     
    arma::mat Calculer(double i,double j);
    arma::mat DeriverI(double i,double j);
    arma::mat DeriverJ(double i,double j);
    protected:
    
        
};

#endif

