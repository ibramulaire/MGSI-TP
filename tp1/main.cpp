// code à mieux ranger avec des classes pour plus de lisibilité 

#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <vector>
#include <sstream>
#include "Courbe.cpp"
#include <armadillo>
#include "Courbe.h"
#include<string>
using namespace arma;
using namespace std ;
void affichage(void);

void clavier(unsigned char touche,int x,int y);
void affiche_repere(void);

void mouse(int, int, int, int);
void mouseMotion(int, int);
void calcules();
//void reshape(int,int);
int t=50 ;

// variables globales pour OpenGL
bool mouseLeftDown;
bool mouseRightDown;
bool mouseMiddleDown;
float mouseX, mouseY;
float cameraAngleX;
float cameraAngleY;
float cameraDistance=0.;

int n=100;
Courbe c;
Sommet point[1000];
Sommet centre;
Sommet pointcercle[1000];


Sommet pointcercleext[1000][1000];
float rayon=0.3;
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
         gluPerspective(45.0f,(GLfloat)200/(GLfloat)200,0.1f,10.0f);
	glMatrixMode(GL_MODELVIEW);
      gluLookAt(0.,0.,4., 0.,0.,0., 0.,1.,0.);
}

//------------------------------------------------------

void calcules()
{
  float i=0;
  int j=0;
  while(j<n)
    {
cout <<j<<endl;
      mat temp=c.Calculer(j,n);
      point[j]={temp(0,0),temp(0,1),temp(0,2)};
      j++;
     
    }
}
void calculerpointcercle(int tt)
{
  mat temp=c.CalculerFrenet(tt,n);
// mat temp2=c.CalculerFrenet(t,n);
 //cout <<temp2<<endl;
 mat tempse=c.CalculerFrenetse(tt,n);

 Sommet snn={temp(0,0),temp(0,1),temp(0,2)};
 Sommet ssenn={tempse(0,0),tempse(0,1),tempse(0,2)};

 double normeCprime=sqrt(pow(temp(0,0),2)+pow(temp(0,1),2)+pow(temp(0,2),2));
 Sommet s={temp(0,0)/normeCprime,temp(0,1)/normeCprime,temp(0,2)/normeCprime};// T normaliser
 



 Sommet bnn={(snn.y*ssenn.z)-(snn.z*ssenn.y),(s.z*ssenn.x)-(snn.x*ssenn.z),(snn.x*ssenn.y)-(snn.y*ssenn.x)};

 






 //Sommet sse={tempse(0,0)/normeCcarre,tempse(0,1)/normeCcarre,tempse(0,2)/normeCcarre};
 
 double produisca=((snn.x*ssenn.x)+(snn.y*ssenn.y)+(snn.z*ssenn.z));
 Sommet sseT={snn.x*produisca/pow(normeCprime,2),snn.y*produisca/pow(normeCprime,2),snn.z*produisca/pow(normeCprime,2)};
 Sommet sseNnn={ssenn.x-sseT.x,ssenn.y-sseT.y,ssenn.z-sseT.z,};
  double normeCcarre=sqrt(pow(sseNnn.x,2)+pow(sseNnn.y,2)+pow(sseNnn.z,2));
 Sommet sse={sseNnn.x/normeCcarre,sseNnn.y/normeCcarre,sseNnn.z/normeCcarre};// N normaliser



 
 
 Sommet b={(s.y*sse.z)-(s.z*sse.y),(s.z*sse.x)-(s.x*sse.z),(s.x*sse.y)-(s.y*sse.x)};//B normaliser


 centre={point[tt].x+(royon*sse.x),point[tt].y+(royon*sse.y),point[tt].z+(royon*sse.z)};




 
for(int j=0;j<n;j++)
for(int i=0;i<n;i++)
  {
    pointcercleext[j][i]={point[j].x+rayon*((sse.x*cos((i*2*3.14)/n))+(b.x*sin((i*2*3.14)/n))),
                    point[j].y+rayon*((sse.y*cos((i*2*3.14)/n))+(b.y*sin((i*2*3.14)/n))),
                    point[j].z+rayon*((sse.z*cos((i*2*3.14)/n))+(b.z*sin((i*2*3.14)/n)))};

  }

for(int j=0;j<n;j++)
for(int i=0;i<n-1;i++)
  {
    glBegin(GL_LINES);
  glColor3f(0.0,0.0,1.0);
  glVertex3d(pointcercleext[j][i].x,pointcercleext[j][i].y,pointcercleext[j][i].z);
  glVertex3d(pointcercleext[j][i+1].x,pointcercleext[j][i+1].y,pointcercleext[j][i+1].z);
  glEnd(); 

  }






}
void displayCourbe(void)
{
 mat temp=c.CalculerFrenet(t,n);
// mat temp2=c.CalculerFrenet(t,n);
 //cout <<temp2<<endl;
 mat tempse=c.CalculerFrenetse(t,n);

 Sommet snn={temp(0,0),temp(0,1),temp(0,2)};
 Sommet ssenn={tempse(0,0),tempse(0,1),tempse(0,2)};

 double normeCprime=sqrt(pow(temp(0,0),2)+pow(temp(0,1),2)+pow(temp(0,2),2));
 Sommet s={temp(0,0)/normeCprime,temp(0,1)/normeCprime,temp(0,2)/normeCprime};
 
  glBegin(GL_LINES);
  glColor3f(1.0,0.0,0.0);
  glVertex3d(point[t].x,point[t].y,point[t].z);
  glVertex3d(point[t].x+s.x,point[t].y+s.y,point[t].z+s.z);
  glEnd(); 


 Sommet bnn={(snn.y*ssenn.z)-(snn.z*ssenn.y),(s.z*ssenn.x)-(snn.x*ssenn.z),(snn.x*ssenn.y)-(snn.y*ssenn.x)};

 double royon= pow(normeCprime,3)/(sqrt(pow(bnn.x,2)+pow(bnn.y,2)+pow(bnn.z,2)));






 //Sommet sse={tempse(0,0)/normeCcarre,tempse(0,1)/normeCcarre,tempse(0,2)/normeCcarre};
 
 double produisca=((snn.x*ssenn.x)+(snn.y*ssenn.y)+(snn.z*ssenn.z));
 Sommet sseT={snn.x*produisca/pow(normeCprime,2),snn.y*produisca/pow(normeCprime,2),snn.z*produisca/pow(normeCprime,2)};
 Sommet sseNnn={ssenn.x-sseT.x,ssenn.y-sseT.y,ssenn.z-sseT.z,};
  double normeCcarre=sqrt(pow(sseNnn.x,2)+pow(sseNnn.y,2)+pow(sseNnn.z,2));
 Sommet sse={sseNnn.x/normeCcarre,sseNnn.y/normeCcarre,sseNnn.z/normeCcarre};

 glBegin(GL_LINES);
 glColor3f(0.0,1.0,0.0);
 glVertex3d(point[t].x,point[t].y,point[t].z);
glVertex3d(point[t].x+sse.x,point[t].y+sse.y,point[t].z+sse.z);

  glEnd(); 

 
 
 Sommet b={(s.y*sse.z)-(s.z*sse.y),(s.z*sse.x)-(s.x*sse.z),(s.x*sse.y)-(s.y*sse.x)};

  glBegin(GL_LINES);
  glColor3f(0.0,0.0,1.0);
  glVertex3d(point[t].x,point[t].y,point[t].z);
  glVertex3d(point[t].x+b.x,point[t].y+b.y,point[t].z+b.z);
  
  glEnd(); 

 centre={point[t].x+(royon*sse.x),point[t].y+(royon*sse.y),point[t].z+(royon*sse.z)};

  for(int i=0;i<n;i++)
  {
    pointcercle[i]={centre.x+royon*((sse.x*cos((i*2*3.14)/n))+(s.x*sin((i*2*3.14)/n))),
                    centre.y+royon*((sse.y*cos((i*2*3.14)/n))+(s.y*sin((i*2*3.14)/n))),
                    centre.z+royon*((sse.z*cos((i*2*3.14)/n))+(s.z*sin((i*2*3.14)/n)))};

  }

 for(int i=0;i<n-1;i++)
 {

  glBegin(GL_LINES);
  glColor3f(0.0,0.0,1.0);
  glVertex3d(pointcercle[i].x,pointcercle[i].y,pointcercle[i].z);
  glVertex3d(pointcercle[i+1].x,pointcercle[i+1].y,pointcercle[i+1].z);
  glEnd(); 

//courbe
  glBegin(GL_LINES);
  glColor3f(1.0,0.0,0.0);
  glVertex3d(point[i].x,point[i].y,point[i].z);
  glVertex3d(point[i+1].x,point[i+1].y,point[i+1].z);
  glEnd(); 

 }

 
for(int j=0;j<n;j++)
for(int i=0;i<n;i++)
  {
    pointcercleext[j][i]={point[j].x+rayon*((sse.x*cos((i*2*3.14)/n))+(b.x*sin((i*2*3.14)/n))),
                    point[j].y+rayon*((sse.y*cos((i*2*3.14)/n))+(b.y*sin((i*2*3.14)/n))),
                    point[j].z+rayon*((sse.z*cos((i*2*3.14)/n))+(b.z*sin((i*2*3.14)/n)))};

  }

for(int j=0;j<n;j++)
for(int i=0;i<n-1;i++)
  {
    glBegin(GL_LINES);
  glColor3f(0.0,0.0,1.0);
  glVertex3d(pointcercleext[j][i].x,pointcercleext[j][i].y,pointcercleext[j][i].z);
  glVertex3d(pointcercleext[j][i+1].x,pointcercleext[j][i+1].y,pointcercleext[j][i+1].z);
  glEnd(); 

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
  glutCreateWindow("ifs");

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

  calcules();
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
      t+=10;
       if (t > n ) t=n-1;
      glutPostRedisplay();
      break;
    case '-': //* ajustement du t
       t-=10;
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

    
    
