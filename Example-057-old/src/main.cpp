/*******************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 * 
 * Last update: February 2017
 *
 * This program is Free Software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.                                       
 *                                                                         
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License (http://www.gnu.org/licenses/gpl.txt) for more details.
 * 
 * main.cpp - the main function for the 'Example-057 (Old Mode)' example
 *******************************************************************************************************************************************************/

/* First, we must understand which platform we are using. */
#include <cstdlib>
#include <iostream>
#include <cmath>
using namespace std;
#define PI 3.14159265358979324
#ifdef __APPLE__

	/* We are using a MacOSX platform (Macintosh) */
	#include "GL/glew.h"
	#include "GLUT/glut.h"
	#include "OpenGL/gl.h"

#else

	/* We are not using a MacOSX platform. Thus, we have a generic Unix-like platform, like the GNU Linux, or a Microsoft Windows platform. */
	#include "GL/glew.h"
	#include "GL/glut.h"
	#include "GL/gl.h"

#endif

/// The rendering mode for the scene of interest (filled triangles, if mode=0 | wireframe triangles, if mode=1 | triangles points, if mode=2).
int mode=0;

/// The number of the vertices to be analyzed for drawing the <i>'Circle'</i> shapes of interest.
int num=5;

/// The plain array, containing the coordinates of all vertices for the <i>'Circle'</i> shape of interest.
float *pnts=NULL;

/* Prototypes for all functions of interest! */
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);
void draw();
void computeCircleVertices();

/// The main function for the <i>'Example-057 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-057' Example, based on the (Old Mode) OpenGL");
	glutDisplayFunc(draw);
	glutReshapeFunc(resize);
	glutKeyboardFunc(manageKeys);
	glewExperimental = GL_TRUE;
   	glewInit();
   	initialize(); 
	glutMainLoop();
	return EXIT_SUCCESS;
}

/// This function updates the viewport for the scene when it is resized. */
void resize(int w, int h)
{
	/* We update the projections and the modeling matrices! */
	glViewport(0, 0, w, h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glOrtho(-50,50,-50,50,-1,1);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - ' ' - '+' - '-' keys */
	switch (key)
	{
		case 'q':
	
		/* The key is 'q' */
		if(pnts!=NULL) delete pnts;
		pnts=NULL;
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case 'Q':
	
		/* The key is 'Q' */
		if(pnts!=NULL) delete pnts;
		pnts=NULL;
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case 27:
	
		/* The key is 'Esc' */
		if(pnts!=NULL) delete pnts;
		pnts=NULL;
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case ' ':
		
		/* We update the rendering mode. */
		mode=(mode+1)%3;
		glutPostRedisplay();
		break;
		
		case '+':
		
		/* We increase the number of the vertices to be considered for drawing the 'Circle' shape. */
		num=num+1;
		computeCircleVertices();
		glutPostRedisplay();
		break;
		
		case '-':
		
		/* We decrease the number of the vertices to be considered for drawing the 'Circle' shape. */
		if(num>5)
		{
			num=num-1;
			computeCircleVertices();
		}
		else cout<<"\tThe minimum number 5 of the vertices is reached"<<endl;
		glutPostRedisplay();
		break;

		default:

    	/* Other keys are not important for us */
    	break;
	}
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	cout<<endl<<"\tThis is the 'Example-057' Example, based on the (Old Mode) OpenGL"<<endl<<endl;
	cout<<"\tDrawing the 'Circle' shape, approximated by a triangle fan, by using a unique 'glDrawArrays()' statement. It is possible to:"<<endl<<endl;
	cout<<"\t-) change the rendering mode by pressing the ' ' key"<<endl;
	cout<<"\t-) modify the number of the vertices for the 'Circle' shape to be considered by pressing the '+' (increase) and the '-' (decrease) keys"<<endl<<endl;
	cout.flush();
	glClearColor(0.0, 0.0, 0.0, 0.0);
	mode=0;
	num=5;
	glEnableClientState(GL_VERTEX_ARRAY);
	computeCircleVertices();
}

/// This function computes all vertices for drawing the 'Circle' shape of interest.
void computeCircleVertices()
{
	float delta=(2*PI)/(num-1),xk;

	/* First, we check the 'pnts' array! */
	if(pnts!=NULL) delete pnts;
	pnts=NULL;
	pnts=new float[3*(num+1)];
	pnts[0]=0.0;
	pnts[1]=0.0;
	pnts[2]=0.0;
	for(int k=0;k<num;k++)
	{
		xk=-PI+k*delta;
		pnts[ 3*(k+1) ]=30.0*cos(xk);
		pnts[ 3*(k+1)+1 ]=30.0*sin(xk);
		pnts[ 3*(k+1)+2 ]=0.0;
	}
	
	/* Now, we enable the 'vertex array' for the 'pnts' array. */
	glVertexPointer(3,GL_FLOAT,0,pnts);
}

/// This function draws one triangles fan, forming the <i>'Circle'</i> shape in the OpenGL window of interest.
void draw()
{
	/* We must draw the triangles fan, approximating the 'Circle' shape of interest. */
	glClear(GL_COLOR_BUFFER_BIT);
	if(mode==0) glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	if(mode==1) glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	if(mode==2) glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
	glPointSize(8);
	glLineWidth(2);
	glColor3f(1,1,1);
	glDrawArrays(GL_TRIANGLE_FAN,0,num+1);
	glFlush();
	cout<<"\tDrawn the 'Circle' of interest by using "<<num<<" vertices and the 'glDrawArrays' statement. "<<endl;
	cout.flush();
}
