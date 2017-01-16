/*******************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 * 
 * Last update: January 2017
 *
 * This program is Free Software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.                                       
 *                                                                         
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License (http://www.gnu.org/licenses/gpl.txt) for more details.
 * 
 * main.cpp - the main function for the 'Example-032 (Old Mode)' example
 *******************************************************************************************************************************************************/

/* First, we must understand which platform we are using. */
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <string>
#define PI 3.14159265358979324
using namespace std;
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

/// The number of the samples, used for drawing the scene of interest.
int num_samples=5;

/// The rendering mode for the scene of interest (wireframe or filled).
GLenum mode=GL_FILL;

/* Prototypes for all functions of interest! */
void initialize();
void manageKeys(unsigned char key, int x, int y);
void draw();
void resize(int w,int h);
void drawDisc(float R,float X,float Y,float Z);

/// The main function for the <i>'Example-032 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a new window! */
	cout<<endl<<"\tThis is the 'Example-032' Example, based on the (Old Mode) OpenGL"<<endl<<endl;
	cout.flush();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE|GLUT_DEPTH);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-032' Example, based on the (Old Mode) OpenGL");
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
	cout<<"\tWe draw several concentric circles of different dimensions and colors by using the depth test buffer (z-buffer)."<<endl<<endl;
	cout<<"\tIt is possible to modify the number of the samples (by pressing the '+' and '-' keys), as well as the rendering mode (by pressing the ' ' key)."<<endl<<endl;
	cout.flush();
	glClearColor(1.0, 1.0, 1.0, 0.0);
	num_samples=5;
	mode=GL_FILL;
}

/// This function updates the viewport for the scene when it is resized. */
void resize(int w, int h)
{
	/* We update the projections and the modeling matrices! */
	glViewport(0, 0, w, h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glOrtho(-100,100,-100,100,-100,10);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '+' - '-' - '<space bar>' keys */
	switch (key)
	{
		case 'q':
	
		/* The key is 'q' */
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case 'Q':
	
		/* The key is 'Q' */
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case 27:
	
		/* The key is 'Esc' */
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case '+':
		
		/* The key is '+', thus we increase the number of the samples! */
		num_samples=num_samples+1;
		glutPostRedisplay();
		break;
		
		case ' ':
		
		/* The key is ' ', thus we change the rendering mode! */
		if(mode==GL_FILL) mode=GL_LINE;
		else mode=GL_FILL;
		glutPostRedisplay();
		break;
		
		case '-':
		
		/* The key is '-', thus we decrease the number of the samples! */
		if(num_samples>5) num_samples=num_samples-1;
		else cout<<"\tThe minimum number 5 of samples is reached"<<endl;
		cout.flush();
		glutPostRedisplay();
		break;

		default:

    	/* Other keys are not important for us */
    	break;
	}
}

/// This function draws a disc of radius R and centered at the 3D point (X,Y,Z).
void drawDisc(float R,float X,float Y,float Z)
{
	/* Now, we draw a triangle fan! */
	float d=(2*PI)/(num_samples-1);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(X,Y,Z);
	for(int i=0;i<num_samples;i++)
	{
		float t=i*d;
		glVertex3f(X+R*cos(t),Y+R*sin(t),Z);
	}
	
	/* If we arrive here, all is ok. */
	glEnd();
}

/// This function draws several concentric circles of different dimensions and colors by using the depth test buffer (z-buffer) in the OpenGL window of interest.
void draw()
{
	/* Now, we draw several concentric circles of different dimensions and colors by using the depth test buffer (z-buffer) in the OpenGL window of interest. */
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT,mode);
	glEnable(GL_DEPTH_TEST);
	glColor3f(0,0,0);
	drawDisc(95,0,0,10);
	glColor3f(1,1,0.5);
	drawDisc(20,0,0,80);
	glColor3f(0,0,1);
	drawDisc(60,0,0,40);
	glColor3f(0,1,0);
	drawDisc(80,0,0,20);
	glColor3f(1,0,0);
	drawDisc(40,0,0,60);
	glDisable(GL_DEPTH_TEST);
	glFlush();
	cout<<"\tApproximated and drawn the scene of interest with "<<num_samples<<" samples"<<endl;
	cout.flush();
}
