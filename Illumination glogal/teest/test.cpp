#include <iostream>
#include <stdlib.h>


#include "Sphere.h"


using namespace std;
int main(int argc, char const *argv[])
{
    
 Sphere S;
 Rayon r={{0,0,10},{0,0,-1}};

 //cout<<S.rayon<<endl;
Sommet res=S.intersect(r);

 cout<<res.x<<" "<<res.y<<" "<<res.z<<endl;


    return 0;
}
