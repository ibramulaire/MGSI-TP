#include "Courbe.h"
using namespace std;
using namespace arma;
Courbe::Courbe()
{


}


mat Courbe::Calculer(double t,int n)
{
  float x=t/n;
  mat tem={{pow(x,3),pow(x,2),x,1} };
  mat temp=(tem*Besier)*controle;
//  cout <<x <<" "<<temp(0,0)<<" "<<temp(0,1)<<" "<<temp(0,2)<<" "<<endl;
return temp ;
}

mat Courbe::CalculerFrenet(double t,int n)
{
  float x=t/(float)n;
  mat temfrenet={{3*x*x,2*x,1,0} };
  mat temp=(temfrenet*Besier)*controle;
  cout <<t<<" "<<x <<" "<<temp(0,0)<<" "<<temp(0,1)<<" "<<temp(0,2)<<" "<<endl;
return temp ;

}

mat Courbe::CalculerFrenetse(double t,int n)
{
  float x=t/n;
  mat temfrenetse={{6*x,2,0,0} };
  mat temp=(temfrenetse*Besier)*controle;
//  cout <<x <<" "<<temp(0,0)<<" "<<temp(0,1)<<" "<<temp(0,2)<<" "<<endl;
return temp ;

}