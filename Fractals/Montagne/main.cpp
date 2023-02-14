#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <vector>
#include <sstream>
#include "Sommet.h"

#include<string>
#include <math.h>

using namespace std ;
void affichage(void);

void clavier(unsigned char touche,int x,int y);
void affiche_repere(void);

void mouse(int, int, int, int);
void mouseMotion(int, int);
//void reshape(int,int);
float t=.5 ;
#define N 5
const int n=pow(2,N)+1;

double intervale=10.;
double hauteur =3.;
Sommet montagne[n][n];
double dimenssion=3.;
double hmin;
double hmax;


// variables globales pour OpenGL
bool mouseLeftDown;
bool mouseRightDown;
bool mouseMiddleDown;
float mouseX, mouseY;
float cameraAngleX;
float cameraAngleY;
float cameraDistance=0.;

// constantes pour les materieux
  float no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
    float mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
    float mat_ambient_color[] = {0.8f, 0.8f, 0.2f, 1.0f};
    float mat_diffuse[] = {0.1f, 0.5f, 0.8f, 1.0f};
    float mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    float no_shininess = 0.0f;
    float low_shininess = 5.0f;
    float high_shininess = 100.0f;
    float mat_emission[] = {0.3f, 0.2f, 0.2f, 0.0f};
    
double genererAlea(double miny,double maxy )
{
     double zeroToOne = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX));
      double r = (1.-zeroToOne)*miny + zeroToOne*maxy;

return r;
}

double Moyenne4(Sommet s1,Sommet s2,Sommet s3,Sommet s4,Sommet s5, double h )

{
  double moyenne=(s1.y+s2.y+s3.y+s4.y)/4.;

  double distance=(s1.distance(s5)+s2.distance(s5)+s3.distance(s5)+s4.distance(s5))/4.;

return moyenne+(genererAlea(-1 ,1 )*distance*pow(2.,-h));
}

double Moyenne3(Sommet s1,Sommet s2,Sommet s3,Sommet s5, double h )

{
  double moyenne=(s1.y+s2.y+s3.y)/3.;

  double distance=(s1.distance(s5)+s2.distance(s5)+s3.distance(s5))/3.;

return moyenne+(genererAlea(-1 ,1 )*distance*pow(2.,-h));
}
   


void calcules(double h)
{
    
    //init
    montagne[0][0]= Sommet{0,genererAlea(0.,hauteur),0}.RamenerA(-intervale,intervale ,n-1);
    montagne[0][n-1]=Sommet{0,genererAlea(0.,hauteur),n-1}.RamenerA(-intervale,intervale,n-1);
    montagne[n-1][0]=Sommet{n-1,genererAlea(0.,hauteur),0}.RamenerA(-intervale,intervale,n-1);
    montagne[n-1][n-1]=Sommet{n-1,genererAlea(0.,hauteur),n-1}.RamenerA(-intervale,intervale,n-1);


    int pas=n-1;
    //cout<<"pas"<<pas<<endl;

   
    for(int i=pas;i>1 ;i-=i/2)
    {//cout<<"pas"<<i<<endl;
       //phase diamant
      for(int ki=0;ki<pas;ki+=i)
      {
        for(int kj=0;kj<pas;kj+=i) 
        {
          Sommet s1=montagne[ki][kj];
          Sommet s2=montagne[ki][kj+i];
          Sommet s3=montagne[ki+i][kj];
          Sommet s4=montagne[ki+i][kj+i];
          Sommet s5=Sommet{(double)(ki+(i/2)),0.,(double)(kj+(i/2))}.RamenerA(-intervale,intervale ,n-1);
          montagne[(ki+(i/2))][(kj+(i/2))]={s5.x,Moyenne4( s1,s2,s3,s4,s5,h),s5.z};
        }
      }
    
//phase carre paire
      for(int ki=0;ki<=pas;ki+=i)
      {       
          for(int kj=i/2;kj<pas;kj+=i) 
          {     
              
            if(ki!=0&&ki!=pas)
            {
              
              Sommet s1=montagne[ki-i/2][kj];
              Sommet s2=montagne[ki][kj+i/2];
              Sommet s3=montagne[ki+i/2][kj];
              Sommet s4=montagne[ki][kj-i/2];
              Sommet s5=Sommet{(double)(ki),0.,(double)(kj)}.RamenerA(-intervale,intervale ,n-1);           
              montagne[ki][kj]={s5.x,Moyenne4( s1,s2,s3,s4,s5,h),s5.z}; 
            }
            else
            if(ki==0)
            { 
                
             
              Sommet s2=montagne[ki][kj+i/2];
              Sommet s3=montagne[ki+i/2][kj];
              Sommet s4=montagne[ki][kj-i/2];
              Sommet s5=Sommet{(double)(ki),0.,(double)(kj)}.RamenerA(-intervale,intervale ,n-1);
              montagne[ki][kj]={s5.x,Moyenne3( s2,s3,s4,s5,h),s5.z};
            }
            else
            if(ki==pas)
            {
               
             Sommet s1=montagne[ki-i/2][kj];
              Sommet s2=montagne[ki][kj+i/2];
              Sommet s4=montagne[ki][kj-i/2];
              Sommet s5=Sommet{(double)(ki),0.,(double)(kj)}.RamenerA(-intervale,intervale ,n-1);
              montagne[ki][kj]={s5.x,Moyenne3( s1,s2,s4,s5,h),s5.z};
            }
    
          }
        
      }

      //phase carre impaire
      for(int ki=i/2;ki<pas;ki+=i) 
      {
        for(int kj=0;kj<=pas;kj+=i)
        {      
                    
              if(kj!=0&&kj!=pas)
              {
                
                Sommet s1=montagne[ki-i/2][kj];
                Sommet s2=montagne[ki][kj+i/2];
                Sommet s3=montagne[ki+i/2][kj];
                Sommet s4=montagne[ki][kj-i/2];
                Sommet s5=Sommet{(double)(ki),0.,(double)(kj)}.RamenerA(-intervale,intervale ,n-1);           
                montagne[ki][kj]={s5.x,Moyenne4( s1,s2,s3,s4,s5,h),s5.z}; 
              }
              else
              if(kj==0)
              { 
                Sommet s1=montagne[ki-i/2][kj];
                Sommet s2=montagne[ki][kj+i/2];
                Sommet s3=montagne[ki+i/2][kj];
                Sommet s5=Sommet{(double)(ki),0.,(double)(kj)}.RamenerA(-intervale,intervale ,n-1);
                montagne[ki][kj]={s5.x,Moyenne3( s1,s2,s3,s5,h),s5.z};
              }
              else
              if(kj==pas)
              {
                Sommet s1=montagne[ki-i/2][kj];
                Sommet s3=montagne[ki+i/2][kj];
                Sommet s4=montagne[ki][kj-i/2];
                Sommet s5=Sommet{(double)(ki),0.,(double)(kj)}.RamenerA(-intervale,intervale ,n-1);
                montagne[ki][kj]={s5.x,Moyenne3( s1,s3,s4,s5,h),s5.z};
              }
      
            }
        
      }






      
    }
      
   
   

}

void initOpenGl() 
{ 

//lumiere 

	glClearColor( .5, .5, 0.5, 0.0 );
 
	glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  GLfloat l_pos[] = { 3.,3.5,3.0,1.0 };
  glLightfv(GL_LIGHT0,GL_POSITION,l_pos);

  glLightfv(GL_LIGHT0,GL_DIFFUSE,l_pos);
 glLightfv(GL_LIGHT0,GL_SPECULAR,l_pos);
 glEnable(GL_COLOR_MATERIAL);

  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);
//glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
// glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE|GLUT_RGB);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
         gluPerspective(45.0f,(GLfloat)200/(GLfloat)200,0.1f,1000.0f);
	glMatrixMode(GL_MODELVIEW);
      gluLookAt(0.,0.,4., 0.,0.,0., 0.,1.,0.);

}

//------------------------------------------------------

void displayCourbe(void)
{

 /*glPointSize(5.0);
 for(int i=0;i<n;i++)
   for(int j=0;j<n;j++)
  
   montagne[i][j].affiche();
   */


  for(int i=0;i<n;i++)
   for(int j=0;j<n;j++)
   {
    if(i<n-1)
    {
      glBegin(GL_LINES);
        glColor3f(0.0,1.0,0.0);
        glVertex3f(montagne[i][j].x,montagne[i][j].y,montagne[i][j].z);
        glVertex3f(montagne[i+1][j].x,montagne[i+1][j].y,montagne[i+1][j].z);
      glEnd();
    }

    if(j<n-1)
      {
          glBegin(GL_LINES);
            glColor3f(0.0,1.0,0.0);
            glVertex3f(montagne[i][j].x,montagne[i][j].y,montagne[i][j].z);
            glVertex3f(montagne[i][j+1].x,montagne[i][j+1].y,montagne[i][j+1].z);
          glEnd();
      }
      

   }

    
   



    
        
}



int main(int argc,char **argv)
{
  /* initialisation de glut et creation
     de la fenetre */
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB);
  glutInitWindowPosition(200,200);
  glutInitWindowSize(600,600);
  glutCreateWindow("montages");

  /* Initialisation d'OpenGL */
  glClearColor(0.0,0.0,0.0,0.0);
  glColor3f(1.0,1.0,1.0);
  glPointSize(1.0);
	
	//ifs = new Ifs();
  /* enregistrement des fonctions de rappel */
  glutDisplayFunc(affichage);
  glutKeyboardFunc(clavier);
  glutMouseFunc(mouse);
  glutMotionFunc(mouseMotion);
  //-------------------------------

  srand (time(NULL));
 calcules(dimenssion);
  //-------------------------------
    initOpenGl() ;
//-------------------------------

/* Entree dans la boucle principale glut */
  glutMainLoop();
  return 0;
}
//------------------------------------------------------
void affiche_repere(void)
{
  glBegin(GL_LINES);
  glColor3f(1.0,0.0,0.0);
  glVertex2f(0.,0.);
  glVertex2f(1.,0.);
  glEnd(); 

	 glBegin(GL_LINES);
  glColor3f(0.0,1.0,0.0);
  glVertex2f(0.,0.);
  glVertex2f(0.,1.);
  glEnd(); 
   glBegin(GL_LINES);
  glColor3f(0.0,0.0,1.0);
  glVertex3f(0.,0.,0.);
  glVertex3f(0.,0.,1.);
  glEnd(); 
}

//-----------------------------------------------------



//------------------------------------------------------
void affichage(void)
{
	glMatrixMode(GL_MODELVIEW);
  /* effacement de l'image avec la couleur de fond */
//	glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//       glClearDepth(10.0f);                         // 0 is near, >0 is far

        glPushMatrix();
	glTranslatef(0,0,cameraDistance);
	glRotatef(cameraAngleX,1.,0.,0.)	;
	glRotatef(cameraAngleY,0.,1.,0.);
	affiche_repere();
displayCourbe();
        glPopMatrix();
  /* on force l'affichage du resultat */

          glFlush();
  glutSwapBuffers();

}

//------------------------------------------------------


//------------------------------------------------------
void clavier(unsigned char touche,int x,int y)
{

  switch (touche)
    {
    case '+': //
      t+=.1;
       if (t > 1 ) t=1;
      glutPostRedisplay();
      break;
    case '-': //* ajustement du t
       t-=.1;
        if (t < 0 ) t=0;
      glutPostRedisplay();
      break;
    case 'f': //* affichage en mode fil de fer 
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
      glutPostRedisplay();
      break;
      case 'p': //* affichage du carre plein 
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      glutPostRedisplay();
      break;
  case 's' : //* Affichage en mode sommets seuls 
      glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
      glutPostRedisplay();
      break;

    case 'q' : //*la touche 'q' permet de quitter le programme 
      exit(0);
    }
    
}
void mouse(int button, int state, int x, int y)
{
    mouseX = x;
    mouseY = y;

    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseLeftDown = true;
        }
        else if(state == GLUT_UP)
            mouseLeftDown = false;
    }

    else if(button == GLUT_RIGHT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseRightDown = true;
        }
        else if(state == GLUT_UP)
            mouseRightDown = false;
    }

    else if(button == GLUT_MIDDLE_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseMiddleDown = true;
        }
        else if(state == GLUT_UP)
            mouseMiddleDown = false;
    }
}


void mouseMotion(int x, int y)
{
    if(mouseLeftDown)
    {
        cameraAngleY += (x - mouseX);
        cameraAngleX += (y - mouseY);
        mouseX = x;
        mouseY = y;
    }
    if(mouseRightDown)
    {
        cameraDistance += (y - mouseY) * 0.2f;
        mouseY = y;
    }

    glutPostRedisplay();
}

    
    
