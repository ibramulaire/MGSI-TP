#version 450
uniform struct Light {vec3 position ; vec3 intensities; float ambientCoefficient;float attenuation ;} light;
uniform vec3 cameraPosition;
uniform mat4 MVP;//recuperation de la matrice mvp
uniform mat4 MODEL;
uniform float silhouette;
uniform float shad;
uniform float materialShininess;
uniform vec3 materialSpecularColor;
in vec3 fragPosition;
in vec3 fragNormale;
out vec4 finalColor;
in vec4 color;
vec4 bordcolor=vec4(0,0,0,0);
vec4 ambient;
vec4 difuse ;
vec4 speculaire;
float eps=0.5;

vec3 CoolColor = vec3(0, 0, 0.6);

vec3 WarmColor = vec3(0.6, 0.6, 0);

void main() 
{
    ambient=vec4(light.intensities,1.0)*light.ambientCoefficient;
    vec3 directionlumiere= normalize(light.position-fragPosition); 
    vec3 normale = normalize(transpose(inverse(mat3(MODEL)))*fragNormale);
    float diffcoef = max(dot(normale, directionlumiere), 0.0);
  //  difuse =vec4(light.intensities,1.0)*color;
    
   if(shad==1.0)
   { 
     if(diffcoef<0.10)
        difuse =vec4(0.1,0,0.0,1.0);
        else
          if(diffcoef<0.30)
            difuse =vec4(0.3,0,0.0,1.0);
            else
            if(diffcoef<0.60)
                difuse =vec4(0.6,0,0.0,1.0);
                else
                if(diffcoef<0.90)
                  difuse =vec4(0.9,0,0.0,1.0);
                    else
                    difuse =vec4(light.intensities,1.0);
   }
   else
   {
    float alpha=0.5;
    float beta=0.9;
    vec3 kcool    =min(CoolColor,1);
    vec3 kwarm    =min(WarmColor,1);


    float temp=(dot(directionlumiere,normale)+1)*0.5;
   
    vec3 kfinal   = mix(kcool, kwarm, temp);
   

    difuse = vec4(min(kfinal , 1.0), 1.0);


   }
    
    vec3 directionvue= normalize(cameraPosition-fragPosition);
    float vuedircoeff=max(dot(normale, directionvue), 0.0);
    
    vec3 reflectDir = reflect(-directionlumiere, normale);
    float specoeff = pow(max(dot(directionvue, reflectDir), 0.0), materialShininess);
    vec4 specular =vec4( specoeff *materialSpecularColor,1.0);

    if(silhouette==1.0&&vuedircoeff<eps)
    finalColor=bordcolor;
    else
    finalColor=(difuse+ambient+specular);


}


