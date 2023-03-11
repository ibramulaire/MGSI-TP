#version 450
uniform struct Light {vec3 position ; vec3 intensities; float ambientCoefficient;float attenuation ;} light;
uniform vec3 cameraPosition;
uniform mat4 MVP;//recuperation de la matrice mvp
uniform mat4 MODEL;
uniform float silhouette;
uniform float shad;
uniform float materialShininess;
uniform vec3 materialSpecularColor;
uniform samplerCube ourTexture0;

uniform sampler2D ourTexture1;
in vec3 fragPosition;
in vec3 fragNormale;
in vec2 TexCoord;
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
   vec3 directionvue= normalize(fragPosition-cameraPosition);
   vec3 normale = normalize(transpose(inverse(mat3(MODEL)))*fragNormale);
   float ratio = 1.00 / 1.33;
   vec3 R=reflect(directionvue,normale);
   vec3 Rf=refract(directionvue,normale,ratio);
   finalColor=texture(ourTexture0,R);
 

}


