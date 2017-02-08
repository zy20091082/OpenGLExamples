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
 * main.cpp - the main function for the 'Example-051 (Old Mode)' example
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

/// The rendering mode for the scene of interest (filled triangles, if mode=0 | wireframe triangles, if mode=1 | triangles points, if mode=2).
int mode=0;

/* Prototypes for all functions of interest! */
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);
void draw();

/// The main function for the <i>'Example-051 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-051' Example, based on the (Old Mode) OpenGL");
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

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	cout<<endl<<"\tThis is the 'Example-051' Example, based on the (Old Mode) OpenGL"<<endl<<endl;
	cout<<"\tDrawing the 'Square Annulus' shape by using only one triangle strip. It is possible to change the rendering mode by pressing the ' ' key."<<endl<<endl;
	cout.flush();
	glClearColor(0.0, 0.0, 0.0, 0.0);
	mode=0;
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - ' ' keys */
	switch (key)
	{
		case 'q':
	
		/* The key is 'q' */
		exit(EXIT_SUCCESS);
		break;
		
		case 'Q':
	
		/* The key is 'Q' */
		exit(EXIT_SUCCESS);
		break;
		
		case 27:
	
		/* The key is 'Esc' */
		exit(EXIT_SUCCESS);
		break;
		
		case ' ':
		
		/* We update the rendering mode. */
		mode=(mode+1)%3;
		glutPostRedisplay();
		break;

		default:

    	/* Other keys are not important for us */
    	break;
	}
}

/// This function draws only one triangle strip, forming the <i>'Square Annulus'</i> shape of interest, in the OpenGL window of interest.
void draw()
{
	/* We draw only one triangle strip, forming the 'Square Annulus' shape of interest. */
	glClear(GL_COLOR_BUFFER_BIT);
	if(mode==0) glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	if(mode==1) glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	if(mode==2) glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
	glPointSize(8);
	glLineWidth(2);
	glBegin(GL_TRIANGLE_STRIP);
	
	/* Point #0: (30,30,0) with color (1,1,1). */
	glColor3f(1,1,1);
	glVertex3f(30,30,0);
	
	/* Point #1: (10,10,0) with color (1,0,0). */
	glColor3f(1,0,0);
	glVertex3f(10,10,0);
	
	/* Point #2: (70,30,0) with color (0,1,0). */
	glColor3f(0,1,0);
	glVertex3f(70,30,0);
	
	/* Point #3: (90,10,0) with color (0,0,1). */
	glColor3f(0,0,1);
	glVertex3f(90,10,0);
	
	/* Point #4: (70,70,0) with color (1,1,0). */
	glColor3f(1,1,0);
	glVertex3f(70,70,0);
	
	/* Point #5: (90,90,0) with color (1,0,1). */
	glColor3f(1,0,1);
	glVertex3f(90,90,0);
	
	/* Point #6: (30,70,0) with color (0,1,1). */
	glColor3f(0,1,1);
	glVertex3f(30,70,0);
	
	/* Point #7: (10,90,0) with color (1,0,0). */
	glColor3f(1,0,0);
	glVertex3f(10,90,0);
	
	/* Point #0: (30,30,0) with color (1,1,1). */
	glColor3f(1,1,1);
	glVertex3f(30,30,0);
	
	/* Point #1: (10,10,0) with color (1,0,0). */
	glColor3f(1,0,0);
	glVertex3f(10,10,0);
	
	glEnd();
	glFlush();
}
