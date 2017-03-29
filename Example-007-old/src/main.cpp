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
 * main.cpp - the main function for the 'Example-007 (Old Mode)' example.
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

/// The main function for the <i>'Example-007 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-007' Example, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws 12 quadrilaterals by using several colors."<<endl<<endl;
	cout<<"\tIt is possible to end this program by pressing one among the 'Q' - 'q' - 'Esc' keys."<<endl<<endl;
	cout.flush();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(480,480);
	glutCreateWindow("The 'Example-007' Example, based on the (Old Mode) OpenGL");
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
   	glOrtho(-10,120,-10,120,-1,1);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function draws 12 quadrilaterals (with different colors) in the OpenGL window of interest.
void draw()
{
	/* We draw 12 quadrilaterals (with different colors) in the OpenGL window of interest! */
	glClear(GL_COLOR_BUFFER_BIT);
	
	/* We draw the 'black' quadrilateral #0. */
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(20,90,0);
	glVertex3f(40,90,0);
	glVertex3f(40,110,0);
	glVertex3f(20,110,0);
	glEnd();
	
	/* We draw the 'red' quadrilateral #1. */
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(50,90,0);
	glVertex3f(70,90,0);
	glVertex3f(70,110,0);
	glVertex3f(50,110,0);
	glEnd();
	
	/* We draw the 'green' quadrilateral #2. */
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(80,90,0);
	glVertex3f(100,90,0);
	glVertex3f(100,110,0);
	glVertex3f(80,110,0);
	glEnd();
	
	/* We draw the 'blue' quadrilateral #3. */
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(20,60,0);
	glVertex3f(40,60,0);
	glVertex3f(40,80,0);
	glVertex3f(20,80,0);
	glEnd();
	
	/* We draw the 'yellow' quadrilateral #4. */
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(50,60,0);
	glVertex3f(70,60,0);
	glVertex3f(70,80,0);
	glVertex3f(50,80,0);
	glEnd();
	
	/* We draw the 'magenta' quadrilateral #5. */
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(80,60,0);
	glVertex3f(100,60,0);
	glVertex3f(100,80,0);
	glVertex3f(80,80,0);
	glEnd();
	
	/* We draw the 'cyan' quadrilateral #6. */
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(20,30,0);
	glVertex3f(40,30,0);
	glVertex3f(40,50,0);
	glVertex3f(20,50,0);
	glEnd();
	
	/* We draw the quadrilateral #7 by using a custom color. */
	glColor3f(0.2,0.2,0.2);
	glBegin(GL_POLYGON);
	glVertex3f(50,30,0);
	glVertex3f(70,30,0);
	glVertex3f(70,50,0);
	glVertex3f(50,50,0);
	glEnd();
	
	/* We draw the quadrilateral #8 by using a custom color. */
	glColor3f(0.5,0.5,0.5);
	glBegin(GL_POLYGON);
	glVertex3f(80,30,0);
	glVertex3f(100,30,0);
	glVertex3f(100,50,0);
	glVertex3f(80,50,0);
	glEnd();
	
	/* We draw the quadrilateral #9 by using a custom color. */
	glColor3f(0.8,0.8,0.8);
	glBegin(GL_POLYGON);
	glVertex3f(50,0,0);
	glVertex3f(70,0,0);
	glVertex3f(70,20,0);
	glVertex3f(50,20,0);
	glEnd();
	
	/* We draw the quadrilateral #10 by using a custom color. */
	glColor3f(0.8,0,0.8);
	glBegin(GL_POLYGON);
	glVertex3f(20,0,0);
	glVertex3f(40,0,0);
	glVertex3f(40,20,0);
	glVertex3f(20,20,0);
	glEnd();
	
	/* We draw the quadrilateral #11 by using a custom color. */
	glColor3f(0,0.3,0);
	glBegin(GL_POLYGON);
	glVertex3f(80,0,0);
	glVertex3f(100,0,0);
	glVertex3f(100,20,0);
	glVertex3f(80,20,0);
	glEnd();
	
	glFlush();
}

/// This function initializes the OpenGL window of interest. */
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
