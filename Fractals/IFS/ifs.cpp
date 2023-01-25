#include "ifs.h"
#include <GL/glut.h>
#include <iostream>
// #include "../armadillo/include/armadillo"


using namespace arma;
using namespace std;

Ifs::Ifs()
{


}

Ifs::~Ifs(void)
{
}

void Ifs::display(int level)
{

}

void Ifs::ComputeApproximation() // il faut peut être mettre des parametres
{


    for(int i=0;i<mIfs.size();i++)
     mApproximation.push_back(mIfs[i]*mControlPoints);


}
