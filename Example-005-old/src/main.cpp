/*******************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 * 
 * Last update: March 2017
 *
 * This program is Free Software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.                                       
 *                                                                         
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License (http://www.gnu.org/licenses/gpl.txt) for more details.
 * 
 * main.cpp - the main function for the 'Example-005 (Old Mode)' example
 *******************************************************************************************************************************************************/

/* First, we must understand which platform we are using. */
#include <cstdlib>
#include <iostream>
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

/* Prototypes for all functions of interest! */
GLfloat xcoord;
bool eol=false;
void draw();
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);

/// The main function for the <i>'Example-005 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-005' Example, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws a polygon in 'red', obtained as the intersection between the following elements:"<<endl<<endl;
	cout<<"\t\t-) the viewing box (orthographic projection): [0,100] x [0,100] x [-1,1];"<<endl;
	cout<<"\t\t-) the triangle with vertices (x,20,0) - (80,20,0) - (80,80,0)."<<endl<<endl;
	cout.flush();
	cout<<"\tHere, the viewing box is not modified. Instead, the triangle is modified by moving the 'x' coordinate along the x-axis as follows:"<<endl<<endl;
	cout<<"\t\t-) the '+' key increases the 'x' coordinate by 1.0;"<<endl;
	cout<<"\t\t-) the '-' key decreases the 'x' coordinate by 1.0;"<<endl;
	cout<<"\t\t-) the '=' key sets 'x' as its initial value '20'."<<endl<<endl;
	cout<<"\tIt is possible to end this program by pressing one among the 'Q' - 'q' - 'Esc' keys."<<endl<<endl;
	cout.flush();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(480,480);
	glutCreateWindow("The 'Example-005' Example, based on the (Old Mode) OpenGL");
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
   	glOrtho(0,100,0,100,-1,1);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function draws a triangle in the OpenGL window of interest.
void draw()
{
	/* We draw a 'red' triangle in the OpenGL window of interest! */
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
  	glBegin(GL_POLYGON);
	glVertex3f(xcoord,20,0);
	glVertex3f(80,20,0);
	glVertex3f(80,80,0);
   	glEnd();
	glFlush(); 
}

/// This function initializes the OpenGL window of interest. */
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	xcoord=20.0;
	eol=false;
	glClearColor(1.0, 1.0, 1.0, 0.0);
	cout<<"\tThe 'x' coordinate is initially set to "<<xcoord<<" in the current scene."<<endl<<endl;
	cout.flush();
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '+' - '-' - "=" keys */
	switch (key)
	{
		case 'q':
	
		/* The key is 'q' */
		if(eol) cout<<endl;
		exit(EXIT_SUCCESS);
		break;
		
		case 'Q':
	
		/* The key is 'Q' */
		if(eol) cout<<endl;
		exit(EXIT_SUCCESS);
		break;
		
		case 27:
	
		/* The key is 'Esc' */
		if(eol) cout<<endl;
		exit(EXIT_SUCCESS);
		break;
		
		case '+':
		
		/* The key is '+' */
		xcoord=xcoord+(GLfloat)1.0;
		cout<<"\tIncreasing the 'x' coordinate as "<<xcoord<<" in the current scene."<<endl;
		cout.flush();
		eol=true;
		glutPostRedisplay();
		break;
		
		case '-':
		
		/* The key is '-' */
		xcoord=xcoord-(GLfloat)1.0;
		cout<<"\tDecreased the 'x' coordinate as "<<xcoord<<" in the current scene."<<endl;
		cout.flush();
		eol=true;
		glutPostRedisplay();
		break;
		
		case '=':
		
		/* The key is '=' */
		xcoord=20.0;
		eol=true;
		cout<<"\tReinitialized the 'x' coordinate to the default value "<<xcoord<<" in the current scene."<<endl;
		cout.flush();
		glutPostRedisplay();
		break;
		
		default:

    	/* Other keys are not important for us */
    	break;
	}
}
