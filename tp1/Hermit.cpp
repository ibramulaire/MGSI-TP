
#include "Hermit.h"

Hermit::Hermit(int nbVertex):Courbes(nbVertex)
{

 }

Hermit::~Hermit()
{
}

arma::mat Hermit::getMat(){
    return hermitMat;
}

arma::mat Hermit::CalculerCourbe(double t){

    float x=t/getNbVertex();
    arma:: mat canonic={{pow(x,3),pow(x,2),x,1} };
    return (canonic*getMat())*getControleMat();
}


arma::mat Hermit::Deriver(double t)
{

  float x=t/getNbVertex();
  arma:: mat canonic={{3*x*x,2*x,1,0} };
  return (canonic*getMat())*getControleMat();
}
arma::mat Hermit::DeriverSeconde(double t)
{

      float x=t/getNbVertex();
  arma:: mat canonic={{6*x,2,0,0} };
  return (canonic*getMat())*getControleMat();
}

void Hermit::TousCalculer()
{
  std::vector<Sommet>& curve= getCurveVertices();
  std::vector<Sommet>& cprime= getDerivations();
  std::vector<Sommet>& csecond= getSecondDerivations();
  for(int i(0);i<getNbVertex();i++)
  {
  arma::mat temporaire1=CalculerCourbe(i);
  arma::mat temporaire2=Deriver(i);
  arma::mat temporaire3=DeriverSeconde(i);
  curve.push_back({temporaire1(0,0),temporaire1(0,1),temporaire1(0,2)});
  cprime.push_back({temporaire2(0,0),temporaire2(0,1),temporaire2(0,2)});
  csecond.push_back({temporaire3(0,0),temporaire3(0,1),temporaire3(0,2)});
  }

  
}