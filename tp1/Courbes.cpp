#include "Courbes.h"
using namespace std;
using namespace arma;
Courbes::Courbes(int nbVertext):nbVertex(nbVertext)
{

}

Courbes::~Courbes()
{
}

int Courbes::getNbVertex()
{
    return nbVertex;
}

std::vector<Sommet>&Courbes::getCurveVertices() {
return CurveVertices;

};


std::vector<Sommet>&Courbes::getDerivations() {
return Derivations;

};


std::vector<Sommet>&Courbes::getSecondDerivations() {
return SecondDerivations;

};
mat Courbes::getControleMat(){
    return controleMat;
    }





void Courbes::setCurveVertices(int i,Sommet s){

CurveVertices[i]=s;
}
void Courbes::setDerivations(int i,Sommet s){
Derivations[i]=s;
}
void Courbes::setSecondDerivations(int i,Sommet s){
SecondDerivations[i]=s;
}





