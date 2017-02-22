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
 * main.cpp - the main function for the 'Example-062 (Old Mode)' example
 *******************************************************************************************************************************************************/

/* First, we must understand which platform we are using. */
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <string>
#include <cfloat>
#define PI 3.14159265358979324
using namespace std;
#ifndef uint
	typedef unsigned int uint;
#endif
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

/// The number of the samples for the circles of interest in the <i>'Bull-Eye'</i> shape.
unsigned int num_samples=3;

/// The unique array for containing all Euclidean coordinates and the colors for the circles of interest in the <i>'Bull-Eye'</i> shape.
GLfloat *quads;

/// The matrix for containing the indices for drawing the circles of interest in the <i>'Bull-Eye'</i> shape.
uint** inds;

/// The unique array for containing the number of the points for the circles of interest in the <i>'Bull-Eye'</i> shape.
int *cnt;

/// The rendering mode for the circle of interest in the <i>'Bull-Eye'</i> shape.
int mode=0;

/* Prototypes for all functions of interest! */
void initialize();
void manageKeys(unsigned char key, int x, int y);
void draw();
void resize(int w,int h);
void computePoints();
void destroyPoints();

/// The main function for the <i>'Example-062 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a new window! */
	cout<<endl<<"\tThis is the 'Example-062' Example, based on the (Old Mode) OpenGL"<<endl<<endl;
	cout.flush();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-062' Example, based on the (Old Mode) OpenGL");
	glutReshapeFunc(resize);
	glutKeyboardFunc(manageKeys);
	glutDisplayFunc(draw);
	glewExperimental = GL_TRUE;
   	glewInit();
   	initialize(); 
	glutMainLoop();
	return EXIT_SUCCESS;
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(0.0, 0.0, 0.0, 0.0);
	quads=NULL;
	num_samples=3;
	inds=NULL;
	cnt=NULL;
	mode=0;
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	computePoints();
	cout<<"\tDrawing the 'Bull-Eye' shape by using the vertex array, implemented by only one 'glDrawElements()' statement. It is possible to:"<<endl<<endl;
	cout<<"\t-) change the rendering mode for the 'Bull-Eye' shape by pressing the 'r' key"<<endl;
	cout<<"\t-) modify the number of the vertices for the 'Bull-Eye' shape to be considered by pressing the '+' (increase) and the '-' (decrease) keys"<<endl<<endl;
	cout.flush();
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '+' - '-' - 'r' keys. */
	switch (key)
	{
		case 27:
	
		/* The key is 'Esc', thus we must exit. But first, we destroy correctly all auxiliary arrays of interest. Here, we know their actual sizes. */
		cout<<endl;
		cout.flush();
		destroyPoints();
		exit(EXIT_SUCCESS);
		break;
		
		case 'q':
		
		/* The key is 'q', thus we must exit. But first, we destroy correctly all auxiliary arrays of interest. Here, we know their actual sizes. */
		cout<<endl;
		cout.flush();
		destroyPoints();
		exit(EXIT_SUCCESS);
		break;
		
		case 'Q':
		
		/* The key is 'Q', thus we must exit. But first, we destroy correctly all auxiliary arrays of interest. Here, we know their actual sizes. */
		cout<<endl;
		cout.flush();
		destroyPoints();
		exit(EXIT_SUCCESS);
		break;
		
		case '+':
		
		/* The key is '+', thus we must increase the number of the samples. But first, we destroy correctly all auxiliary arrays of interest. Here, we know their actual sizes. */
		destroyPoints();
		num_samples=num_samples+1;
		computePoints();
		glutPostRedisplay();
		break;
		
		case '-':
		
		/* The key is '-', thus we must decrease the number of the samples. But first, we destroy correctly all auxiliary arrays of interest. Here, we know their actual sizes. */
		if(num_samples>3)
		{
			destroyPoints();
			num_samples=num_samples-1;
			computePoints();
			glutPostRedisplay();
			break;
		}
		else cout<<"\tThe minimum number 3 of the samples is reached"<<endl;
		break;
		
		case 'r':
		
		/* The key 'r', thus we must change the rendering mode. */
		mode=(mode+1)%3;
		glutPostRedisplay();
		break;
		
		default:

    	/* Other keys are not important for us */
    	break;
	}
}

/// This function updates the viewport for the scene when it is resized. */
void resize(int w, int h)
{
	/* We update the projections and the modeling matrices! */
	glViewport(0, 0, w, h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glOrtho(-30,30,-30,30,-1,1);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function allocates and computes all auxiliary arrays for drawing the circles of interest in the <i>'Bull-Eye'</i> shape. */
void computePoints()
{
	float delta=(2*PI)/(num_samples);
	unsigned int v;

	/* Now, we allocate and compute all auxiliary arrays for drawing the circles of interest in the 'Bull-Eye' shape. */
	inds=new uint*[3];
	for(unsigned int k=0;k<3;k++) { inds[k]=new uint[2*(num_samples+1)]; }
	cnt=new int[3];
	for(unsigned int k=0;k<3;k++) { cnt[k]=2*(num_samples+1); }
	quads=new GLfloat[36*(num_samples+1)];

	/* Now, we compute everything, starting from annulus #0. The color for all vertices in this annulus is 'green'. */
	for(unsigned int k=0;k<=num_samples;k++)
	{
		/* Contributed point #0 */
		v=2*k;		
		inds[0][2*k]=v;
		quads[6*v]=5*cos(k*delta);
		quads[6*v+1]=5*sin(k*delta);
		quads[6*v+2]=0;
		quads[6*v+3]=0.0;
		quads[6*v+4]=1.0;
		quads[6*v+5]=0.0;
		
		/* Contributed point #1 */
		v=v+1;
		inds[0][2*k+1]=v;
		quads[6*v]=10*cos(k*delta);
		quads[6*v+1]=10*sin(k*delta);
		quads[6*v+2]=0;
		quads[6*v+3]=0.0;
		quads[6*v+4]=1.0;
		quads[6*v+5]=0.0;
	}

	/* Now, we compute everything, starting from annulus #1. The color for all vertices in this annulus is 'white'. */
	for(unsigned int k=0;k<=num_samples;k++)
	{
		/* Contributed point #0 */
		v=(2*k+2*(num_samples+1));
		inds[1][2*k]=v;
		quads[6*v]=10*cos(k*delta);
		quads[6*v+1]=10*sin(k*delta);
		quads[6*v+2]=0;
		quads[6*v+3]=1.0;
		quads[6*v+4]=1.0;
		quads[6*v+5]=1.0;
		
		/* Contributed point #1 */
		v=v+1;
		inds[1][2*k+1]=v;
		quads[6*v]=15*cos(k*delta);
		quads[6*v+1]=15*sin(k*delta);
		quads[6*v+2]=0;
		quads[6*v+3]=1.0;
		quads[6*v+4]=1.0;
		quads[6*v+5]=1.0;
	}
	
	/* Now, we compute everything, starting from annulus #2. The color for all vertices in this annulus is 'red'. */
	for(unsigned int k=0;k<=num_samples;k++)
	{
		/* Contributed point #0 */
		v=(2*k+4*(num_samples+1));
		inds[2][2*k]=v;
		quads[6*v]=15*cos(k*delta);
		quads[6*v+1]=15*sin(k*delta);
		quads[6*v+2]=0;
		quads[6*v+3]=1.0;
		quads[6*v+4]=0.0;
		quads[6*v+5]=0.0;
		
		/* Contributed point #1 */
		v=v+1;
		inds[2][2*k+1]=v;
		quads[6*v]=20*cos(k*delta);
		quads[6*v+1]=20*sin(k*delta);
		quads[6*v+2]=0;
		quads[6*v+3]=1.0;
		quads[6*v+4]=0.0;
		quads[6*v+5]=0.0;
	}
}

/// This function destroys all auxiliary arrays for drawing the circles of interest in the <i>'Bull-Eye'</i> shape. */
void destroyPoints()
{
	/* Now, we destroy all auxiliary arrays for drawing the circles of interest in the 'Bull-Eye' shape. */
	if(quads!=NULL) delete quads;
	quads=NULL;
	if(cnt!=NULL) delete cnt;
	cnt=NULL;
	if(inds!=NULL)
	{
		for(unsigned int k=0;k<3;k++) if(inds[k]!=NULL) { delete inds[k]; inds[k]=NULL; }
		delete inds;
		inds=NULL;
	}
}

/// This function draws the <i>'Bull-Eye'</i> shape in the OpenGL window of interest by using the preferences, chosen by the user.
void draw()
{
	/* This function draws the 'Bull-Eye' shape in the OpenGL window of interest by using the preferences, chosen by the user. */
	glClear(GL_COLOR_BUFFER_BIT);
	if(mode==0) glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	if(mode==1) glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	if(mode==2) glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
	glPointSize(5);
	glLineWidth(2);
	
	/* Now, we exploit only one 'glMultiDrawElement()' statement. */
	glVertexPointer(3,GL_FLOAT,6*sizeof(float),&quads[0]);
	glColorPointer(3,GL_FLOAT,6*sizeof(float),&quads[3]);
	glMultiDrawElements(GL_QUAD_STRIP,cnt,GL_UNSIGNED_INT,(const void**)inds,3);
	glFlush();
	cout<<"\tDrawn the 'Bull'Eye' shape of interest by using "<<num_samples<<" samples by using the vertex array, implemented by only one 'glDrawElements()' statement."<<endl;
	cout.flush();
}	
