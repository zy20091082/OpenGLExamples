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
 * main.cpp - the main function for the 'Example-019 (Old Mode)' example.
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

/// The main function for the <i>'Example-019 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-019' Example, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws the 'filled' and the 'wireframe versions' of the 'Double Square Annulus' shape, both approximated by 2 triangle strips (respectively, in 'red' and in 'blue')."<<endl;
	cout<<"\tIn the 'filled version', the triangles of 2 triangle strips are completely rendered. Instead, only the edges of 2 triangle strips are rendered in the 'wireframe version'."<<endl<<endl;
	cout<<"\tIt is possible to end this program by pressing one among the 'Q' - 'q' - 'Esc' keys."<<endl<<endl;
	cout.flush();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(450,480);
	glutCreateWindow("The 'Example-019' Example, based on the (Old Mode) OpenGL");
	glutDisplayFunc(draw);
	glutReshapeFunc(resize);
	glutKeyboardFunc(manageKeys);
	glewExperimental = GL_TRUE;
   	glewInit();
   	initialize(); 
	glutMainLoop();
	return EXIT_SUCCESS;
}

/// This function initializes the OpenGL window of interest.
void initialize() { glClearColor(1.0, 1.0, 1.0, 0.0); }

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' keys */
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

/// This function updates the viewport for the scene when it is resized. */
void resize(int w, int h)
{
	/* We update the projections and the modeling matrices! */
	glViewport(0, 0, w, h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glOrtho(0,200,0,260,-1,1);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function draws two versions of the <i>'Double Square Annulus'</i> shape, both approximated by 2 triangle strips, in the OpenGL window of interest.
void draw()
{
	/* We draw two versions of the 'Double Square Annulus' shape, both approximated by 2 triangle strips, in the OpenGL window of interest. We start from the 'wireframe version' of the triangle strip #0 (in 'red'), which is connected to the triangle strip #2. */
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(20,120,0);
	glVertex3f(40,100,0);
	glVertex3f(20,10,0);
	glVertex3f(40,30,0);
	glVertex3f(90,10,0);
	glVertex3f(80,30,0);
	glVertex3f(90,120,0);
	glVertex3f(80,100,0);
	glVertex3f(20,120,0);
	glVertex3f(40,100,0);
	glEnd();
	
	/* Now, we draw the 'filled version' of the triangle strip #0 (in 'red'). */
	glColor3f(1.0,0.0,0.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(20,240,0);
	glVertex3f(40,220,0);
	glVertex3f(20,130,0);
	glVertex3f(40,150,0);
	glVertex3f(90,130,0);
	glVertex3f(80,150,0);
	glVertex3f(90,240,0);
	glVertex3f(80,220,0);
	glVertex3f(20,240,0);
	glVertex3f(40,220,0);
	glEnd();
	
	/* Now, we draw the 'wireframe version' of the triangle strip #1 (in 'blue'). */
	glColor3f(0.0,0.0,1.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(90,120,0);
	glVertex3f(100,100,0);
	glVertex3f(90,10,0);
	glVertex3f(100,30,0);
	glVertex3f(180,10,0);
	glVertex3f(160,30,0);
	glVertex3f(180,120,0);
	glVertex3f(160,100,0);
	glVertex3f(90,120,0);
	glVertex3f(100,100,0);
	glEnd();
	
	/* Now, we draw the 'filled version' of the triangle strip #1 (in 'blue'). */
	glColor3f(0.0,0.0,1.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(90,240,0);
	glVertex3f(100,220,0);
	glVertex3f(90,130,0);
	glVertex3f(100,150,0);
	glVertex3f(180,130,0);
	glVertex3f(160,150,0);
	glVertex3f(180,240,0);
	glVertex3f(160,220,0);
	glVertex3f(90,240,0);
	glVertex3f(100,220,0);
	glEnd();
	glFlush();
}
