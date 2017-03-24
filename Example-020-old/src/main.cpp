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
 * main.cpp - the main function for the 'Example-020 (Old Mode)' example.
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

/// The main function for the <i>'Example-020 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-020' Example, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws the 'filled' and the 'wireframe versions' of the 'Double Square Annulus' shape, both approximated by only one triangle strip (in 'red')."<<endl;
	cout<<"\tIn the 'filled version', the triangles of the triangle strip are completely rendered. Instead, only the edges of the triangle strip are rendered in the 'wireframe version'."<<endl<<endl;
	cout<<"\tIt is possible to end this program by pressing one among the 'Q' - 'q' - 'Esc' keys."<<endl<<endl;
	cout.flush();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(450,480);
	glutCreateWindow("The 'Example-020' Example, based on the (Old Mode) OpenGL");
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
   	glOrtho(0,200,0,300,-1,1);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
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

/// This function draws 2 versions of the <i>'Double Square Annulus'</i> shape, both approximated by one triangle strip (in <i>'red'</i>), in the OpenGL window of interest.
void draw()
{
	/* We draw 2 versions of the 'Double Square Annulus' shape, both approximated by one triangle strip (in 'red'), in the OpenGL window of interest. First, we draw the 'wireframe version' for the triangle strip of interest (in 'red'). */
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(95,10,0);
	glVertex3f(80,30,0);
	glVertex3f(10,10,0);
	glVertex3f(30,30,0);
	glVertex3f(10,140,0);
	glVertex3f(30,110,0);
	glVertex3f(50,140,0);
	glVertex3f(80,110,0);
	glVertex3f(95,140,0);
	glVertex3f(110,110,0);
	glVertex3f(140,140,0);
	glVertex3f(140,110,0);
	glVertex3f(180,140,0);
	glVertex3f(160,110,0);
	glVertex3f(180,10,0);
	glVertex3f(160,30,0);
	glVertex3f(95,10,0);
	glVertex3f(110,30,0);
	glVertex3f(80,30,0);
	glVertex3f(110,110,0);
	glVertex3f(80,110,0);
	glEnd();
	
	/* Now, we draw the 'filled version' for the triangle strip of interest (in 'red'). */
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(95,160,0);
	glVertex3f(80,180,0);
	glVertex3f(10,160,0);
	glVertex3f(30,180,0);
	glVertex3f(10,290,0);
	glVertex3f(30,260,0);
	glVertex3f(50,290,0);
	glVertex3f(80,260,0);
	glVertex3f(95,290,0);
	glVertex3f(110,260,0);
	glVertex3f(140,290,0);
	glVertex3f(140,260,0);
	glVertex3f(180,290,0);
	glVertex3f(160,260,0);
	glVertex3f(180,160,0);
	glVertex3f(160,180,0);
	glVertex3f(95,160,0);
	glVertex3f(110,180,0);
	glVertex3f(80,180,0);
	glVertex3f(110,260,0);
	glVertex3f(80,260,0);
	glEnd();
	glFlush();
}
