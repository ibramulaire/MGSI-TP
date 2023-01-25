#ifndef __IFS
#define __IFS

#define NB_TRANSFOS 3
#include<armadillo>

#define BARY 1
#define HOMOGENE 2
#include <GL/glut.h>

using namespace arma;
using namespace std ;

class Ifs 
{
	public:
	vector <mat> mIfs={   { {1,0,0},
                            {1/2,1/2,0},
                            {1/2,1/2,0},
	                      },

                          { {0,0,0},
                            {1,1,0},
                            {0,1,0},
	                      },

						   {  {0,0,0},
                            {1,1,0},
                            {0,1,0},
	                      }

	                   };
	mat mPrimitive={   {     {-1,3,-3,},
                            {3,-6,3,},
                            {-3,3,0,},
							{-1,3,-3,},
                            {3,-6,3,},
                            {-3,3,0,},
							{-1,3,-3,},
                            {3,-6,3,},
                            {-3,3,0,},
							{-1,3,-3,},
                            {3,-6,3,},
                            {-3,3,0,},
                        }  
	               };
    mat mControlPoints={    {0,0,0},
                            {1,1,0},
                            {0,1,0},
	                   };
  
	vector <mat> mApproximation;


	Ifs();
	~Ifs(void);
	void display(int level);
   void ComputeApproximation(); // il faut peut être mettre des parametres
};

#endif
