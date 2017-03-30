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
 * main.cpp - the main function for the 'Example-017 (Old Mode)' example.
 *******************************************************************************************************************************************************/

/* First, we must understand which platform we are using. */
#include <cstdlib>
#include <iostream>
using namespace std;
#ifdef __APPLE__

	/* We are using a MacOSX platform (Macintosh). */
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
void draw();
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);

/// The main function for the <i>'Example-017 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-017' Example, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws 6 rectangles, defined through the 'glRectf()' function, by using several rendering settings."<<endl<<endl;
	cout<<"\tIt is possible to end this program by pressing one among the 'Q' - 'q' - 'Esc' keys."<<endl<<endl;
	cout.flush();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(480,480);
	glutCreateWindow("The 'Example-017' Example, based on the (Old Mode) OpenGL");
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
   	glOrtho(0,150,0,150,-1,1);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function draws 6 rectangles by using several rendering settings in the OpenGL window of interest.
void draw()
{
	/* We draw 6 rectangles, defined through the 'glRectf()' function, by using several rendering settings in the OpenGL window of interest. */
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(10.0);
	glLineWidth(2.0);
	glColor3f(1.0,0.0,0.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glRectf(20.0,20.0,70.0,50.0);
	glColor3f(0.0,1.0,0.0);
	glRectf(80.0,20.0,130.0,50.0);
	glColor3f(1.0,0.3,1.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glRectf(130.0,90.0,80.0,60.0);
	glColor3f(0.6,0.6,0.6);
	glRectf(20.0,60.0,70.0,90.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glRectf(20.0,100.0,70.0,140.0);
	glColor3f(0.0,0.0,1.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
	glRectf(20.0,100.0,70.0,140.0);
	glRectf(130,140.0,80.0, 100.0);
	glFlush();
}

/// This function initializes the OpenGL window of interest.
void initialize() { glClearColor(1.0, 1.0, 1.0, 0.0); }

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' keys. */
	switch (key)
	{
		case 'q':
	
		/* The key is 'q', thus we can exit from this program. */
		exit(EXIT_SUCCESS);
		break;
		
		case 'Q':
	
		/* The key is 'Q', thus we can exit from this program. */
		exit(EXIT_SUCCESS);
		break;
		
		case 27:
	
		/* The key is 'Esc', thus we can exit from this program. */
		exit(EXIT_SUCCESS);
		break;
		
		default:

    	/* Other keys are not important for us! */
    	break;
	}
}
