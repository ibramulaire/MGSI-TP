// code à mieux ranger avec des classes pour plus de lisibilité 

#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <vector>
#include <sstream>

#include <armadillo>

#include<string>
using namespace arma;
using namespace std ;

typedef struct {

        double x;
        double y;
        double z;
       
} Sommet ;
void affichage(void);

void clavier(unsigned char touche,int x,int y);
void affiche_repere(void);

void mouse(int, int, int, int);
void mouseMotion(int, int);

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
int n=1000000;
Sommet point[1000000];
Sommet point2[1000000];
Sommet S1={-1,0,1};
Sommet S2={1,0,0};
Sommet S3={0,2,-1};
Sommet Scourantr={0.5,0.5,1};
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


  
 
point[0]=Scourantr;
point2[0]=Scourantr;
  for(int i=1;i<n;i++)
  {
   int nrandom = rand() % 3 + 1;
  // cout<<nrandom<<endl;;
   if(nrandom==1)
   {
   point[i]={S1.x+ point[i-1].x/2,S1.y+point[i-1].y/2,S1.z+point[i-1].z/2};


   point2[i]={(S1.x+ point2[i-1].x/2)+S1.x- point2[i-1].x,(S1.y+point2[i-1].y/2)+S1.y-point2[i-1].y,(S1.z+point2[i-1].z/2)+S1.z-point2[i-1].z};
   }
   else 
    if(nrandom==2)
    {
   point[i]={S2.x+ point[i-1].x/2,S2.y+point[i-1].y/2,S2.z+point[i-1].z/2};
   point2[i]={(S2.x+ point2[i-1].x/2)+S2.x- point2[i-1].x,(S2.y+point2[i-1].y/2)+S2.y-point2[i-1].y,(S2.z+point2[i-1].z/2)+S2.z-point2[i-1].z};
    }
   else 
   {
    point[i]={S3.x+ point[i-1].x/2,S3.y+point[i-1].y/2,S3.z+point[i-1].z/2};
   point2[i]={(S3.x+ point2[i-1].x/2)+S3.x- point2[i-1].x,(S3.y+point2[i-1].y/2)+S3.y-point2[i-1].y,(S3.z+point2[i-1].z/2)+S3.z-point2[i-1].z};
   }

  }



}

void displayCourbe(void)
{
  for(int i=1;i<n;i++)
  {
   // cout<<point[i].x<<" "<<point[i].y<<" "<<point[i].z<<endl;
   glBegin(GL_POINTS);
   glColor3f(1.0,0.0,0.0);
   glVertex3f(point[i].x,point[i].y,point[i].z);
   glEnd();

    glBegin(GL_POINTS);
   glColor3f(0.0,1.0,0.0);
   glVertex3f(point2[i].x,point2[i].y,point2[i].z);
   //cout<<point2[i].x<<" "<<point2[i].y<<" "<<point2[i].z<<endl;
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
srand (time(NULL));
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

    
    
