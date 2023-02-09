#include "Surface.h"
using namespace std;
using namespace arma;
Surface::Surface()
{

  grille[0][0]=S1;
  grille[0][1]=S2;
  grille[0][2]=S3;
  grille[0][3]=S4;
  grille[1][0]=S5;
  grille[1][1]=S6;
  grille[1][2]=S7;
  grille[1][3]=S8;
  grille[2][0]=S9;
  grille[2][1]=S10;
  grille[2][2]=S11;
  grille[2][3]=S12;
  grille[3][0]=S13;
  grille[3][1]=S14;
  grille[3][2]=S15;
  grille[3][3]=S16;

  tenseur.push_back(controlei1);
  tenseur.push_back(controlei2);
  tenseur.push_back(controlei3); 
  tenseur.push_back(controlei4);


}


mat Surface::Calculer(double i, double j)
{
 

  mat canonici={{pow(i,3),pow(i,2),i,1} };
  mat canonicj={{pow(j,3),pow(j,2),j,1} };
  mat polynomei=canonici*Besier;
  mat polynomej=canonicj*Besier;

  mat result=(polynomei*tenseur[0])*polynomej(0);
  for (int z=1;z<4;z++)
  
    result+=(polynomei*tenseur[z])*polynomej(z);

  

return result ;
}


mat Surface::DeriverI(double i,double j)
{
   mat canonici={{3*i*i,2*i,1,0} };
  mat canonicj={{pow(j,3),pow(j,2),j,1} };
  mat polynomei=canonici*Besier;
  mat polynomej=canonicj*Besier;

  mat result=(polynomei*tenseur[0])*polynomej(0);
  for (int z=1;z<4;z++)
  
    result+=(polynomei*tenseur[z])*polynomej(z);

  

return result ;

}

mat Surface::DeriverJ(double i,double j)
{
   mat canonicj={{3*i*i,2*i,1,0} };
  mat canonici={{pow(j,3),pow(j,2),j,1} };
  mat polynomei=canonici*Besier;
  mat polynomej=canonicj*Besier;

  mat result=(polynomei*tenseur[0])*polynomej(0);
  for (int z=1;z<4;z++)
  
    result+=(polynomei*tenseur[z])*polynomej(z);

  

return result ;


}

