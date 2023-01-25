#version 450
#define PI 3.1415926538

uniform mat4 MVP;//recuperation de la matrice mvp
uniform mat4 MODEL;
uniform float deformation;
layout(location = 0) in vec3 position; // le location permet de dire de quel flux/canal on récupère les données (doit être en accord avec le location du code opengl)
layout (location =3) in vec3 normale;//recuperation des normale
out vec4 color ;
out vec3 fragPosition;
out vec3 fragNormale;

out mat3 matT;


 float pincement(float x,float tmin,float tmax)
{
    float res=1.;

    if(x<tmin)
    res=1.;
    else
      if(x>tmax)
      res=1./2.;
      else
      res=1.-(1./2.*((x-tmin)/(tmax-tmin)));


return res;

}

float tw(float x,float tmin,float tmax,float tethamax)
{
 float res=0;

    if(x<tmin)
    res=0.;
    else
      if(x>tmax)
      res=tethamax;
      else
      res=(tethamax*((x-tmin)/(tmax-tmin)));


return res;
}

void main(){
float tmin=0.;
float tmax=1.;
float tethamax=2*PI;
if(deformation==0.0)
matT=  mat3(
                        1, 0, 0, 
                        0, pincement(position.x,tmin,tmax), 0, 
                        0, 0,pincement(position.x,tmin,tmax) 
                    );
else

if(deformation==1.0)

    
        matT=  mat3(

                     1,0,0,
                     0 ,  cos(tw(position.x,tmin,tmax,tethamax)), -sin(tw(position.x,tmin,tmax,tethamax)),
                     0,  sin(tw(position.x,tmin,tmax,tethamax)), cos(tw(position.x,tmin,tmax,tethamax))
                     
                    );     
                    else   {   
                      float coef=exp(-(position.z*position.z+position.y*position.y));
                      matT=  mat3(

                                  1,0,0,
                                  0 ,  cos(tw(position.x,tmin,tmax,tethamax)*coef), -sin(tw(position.x,tmin,tmax,tethamax)*coef),
                                  0,  sin(tw(position.x,tmin,tmax,tethamax)*coef), cos(tw(position.x,tmin,tmax,tethamax)*coef)
                                  
                                  );  
                    }

    
    color=vec4(position,1.0);
    gl_Position= MVP* vec4((matT*position),1.0);
    fragPosition =vec3(MODEL* vec4((matT*position),1.0));
  	fragNormale =normale;
}





