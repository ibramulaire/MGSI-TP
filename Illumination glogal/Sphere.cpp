
#include "Sphere.h"

Sphere::Sphere(Sommet centre , double rayon):centre(centre) ,rayon(rayon)
{

}

Sphere::~Sphere()
{
}

Sommet Sphere::intersect(Rayon r)
{

double a=r.direction.ProduitScalaire(r.direction);
double b=(r.point.Foi(2)).ProduitScalaire({r.direction.x,r.direction.y,r.direction.z});
double c=(r.point.ProduitScalaire(r.point)) -(rayon*rayon) ;
/*std::cout<<"a= " <<a<<std::endl;

std::cout<<"b= " <<b<<std::endl;
std::cout<<"c= " <<c<<std::endl;
*/
double delta=(b*b)-(4*a*c);
//if(delta>0)
//std::cout<<"deltat= " <<delta<<std::endl;

if(delta<0)
{
   
 return r.point;
}
else
if(delta==0)
{
    
return r.getPointAtT((-b/2*a));

}
else
{
     
 double t1,t2;
 t1=(-b-sqrt(delta))/2*a;
 t2=(-b+sqrt(delta))/2*a;

 //std::cout<<"t1= " <<t1<<std::endl;
 //std::cout<<"t2= " <<t2<<std::endl;
 if(t1<t2)
    return r.getPointAtT(t1);
    else
     return r.getPointAtT(t2);

}


}