/*******************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 * 
 * Last update: December 2016
 *
 * This program is Free Software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.                                       
 *                                                                         
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License (http://www.gnu.org/licenses/gpl.txt) for more details.
 * 
 * main.cpp - the main function for the 'Example-004 (Old Mode)' example
 *******************************************************************************************************************************************************/

/* First, we must understand which platform we are using. */
#include <cstdlib>
#include <iostream>
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
void draw();
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);

/* Global variables */
GLfloat left,right,bottom,top,near,far;

/// The main function for the <i>'Example-004 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(480,480);
	glutCreateWindow("The 'Example-004' Example, based on the (Old Mode) OpenGL");
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
   	glOrtho(left,right,bottom,top,near,far);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function draws a new window with the black background, and nothing else.
void draw()
{
	/* We draw two quadrilaterals in the window! */
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
  	glBegin(GL_POLYGON);
	glVertex3f(20.0, 20.0, 0.0);
	glVertex3f(80.0, 20.0, 0.0);
	glVertex3f(80.0, 80.0, 0.0);
	glVertex3f(20.0, 80.0, 0.0);
   	glEnd();
	glFlush();

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(120.0, 120.0, 0.0);
	glVertex3f(180.0, 120.0, 0.0);
	glVertex3f(180.0, 180.0, 0.0);
	glVertex3f(120.0, 180.0, 0.0);
   	glEnd();
	glFlush();
}

/// This function initializes the window. It draws a white background. */
void initialize() 
{
	left=0.0;
	right=100.0;
	bottom=0.0;
	top=100.0;
	near=-1.0;
	far=1.0;
	std::cout<<std::endl<<"\tDrawing two quadrilaterals in the scene"<<std::endl<<std::endl;
	std::cout<<"\t\tQuadrilateral #0 (in red) with vertices (20,20,0) - (80,20,0) - (80,80,0) - (20,80,0) "<<std::endl;
	std::cout<<"\t\tQuadrilateral #1 (in green) with vertices (120,120,0) - (180,120,0) - (180,180,0) - (120,180,0) "<<std::endl;
	std::cout.flush();
	glClearColor(1.0, 1.0, 1.0, 0.0); 
}

// Keyboard input processing routine.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' keys */
	switch (key)
	{
		case 113:
	
		/* The key is 'q' */
		std::cout<<std::endl;
		exit(EXIT_SUCCESS);
		break;
		
		case 81:
	
		/* The key is 'Q' */
		std::cout<<std::endl;
		exit(EXIT_SUCCESS);
		break;
		
		case 27:
	
		/* The key is 'Esc' */
		std::cout<<std::endl;
		exit(EXIT_SUCCESS);
		break;
		
		case 48:
		
		/* The key is '0' - initial configuration #0: glOrtho(0,100,0,100,-1,1) */
		std::cout<<std::endl<<"\tApplying the initial configuration #0 with the viewing box [0,100] x [0,100] x [-1,1]"<<std::endl;
		std::cout.flush();
		left=0.0;
		right=100.0;
		bottom=0.0;
		top=100.0;
		near=-1.0;
		far=1.0;
		resize(480,480);
		glutReshapeWindow(480,480);
		glutPostRedisplay();
		break;
		
		case 49:
		
		/* The key is '1' - configuration #1: glOrtho(-100,100,-100,100,-1,1) */
		std::cout<<std::endl<<"\tApplying the configuration #1 with the viewing box [0,200] x [0,200] x [-1,1]"<<std::endl;
		std::cout.flush();
		left=0.0;
		right=200.0;
		bottom=0;
		top=200.0;
		near=-1;
		far=1.0;
		resize(480,480);
		glutReshapeWindow(480,480);
		glutPostRedisplay();
		break;
	
		default:

    		/* Other keys are not important for us */
    		break;
	}	
}

