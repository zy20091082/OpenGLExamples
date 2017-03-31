/*******************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 * 
 * Last update: April 2017
 *
 * This program is Free Software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.                                       
 *                                                                         
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License (http://www.gnu.org/licenses/gpl.txt) for more details.
 * 
 * main.cpp - the main function for the 'Example-006 (Old Mode)' example.
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

	/* We are not using a MacOSX platform. Thus, we have a generic Unix-like platform, like the GNU/Linux, or a Microsoft Windows platform. */
	#include "GL/glew.h"
	#include "GL/glut.h"
	#include "GL/gl.h"

#endif

/* Prototypes for all functions of interest! */
void draw();
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);

/// The main function for the <i>'Example-006 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-006' Example, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws the 'filled version' of the polygon (in 'red'), which is the intersection with the maximum number 7 of edges and vertices between the following elements:"<<endl<<endl;
	cout<<"\t\t-) the ortographic viewing box '[0,100]' x '[0,100]' x '[-1,1]';"<<endl;
	cout<<"\t\t-) the triangle with vertices '(-50,-30,0)' - '(150,-50,0)' - '(50,150,0)'."<<endl<<endl;
	cout<<"\tIt is possible to end this program by pressing one among the 'Q' - 'q' - 'Esc' keys."<<endl<<endl;
	cout.flush();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(480,480);
	glutCreateWindow("The 'Example-006' Example, based on the (Old Mode) OpenGL");
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
	/* We update the projection and the modeling matrices! */
	glViewport(0, 0, w, h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glOrtho(0,100,0,100,-1,1);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function draws the <i>'filled version'</i> of the polygon (in <i>'red'</i>), which is the intersection with the maximum number of edges and vertices between a triangle and the ortographic viewing box, in the OpenGL window of interest.
void draw()
{
	/* We draw the 'filled' version' of a polygon (in 'red') in the OpenGL window of interest. It is the intersection with the maximum number 7 of edges and vertices between:
	 *
	 * -) the ortographic viewing box '[0,100]' x '[0,100]' x '[-1,1];
	 * -) the triangle with vertices '(-50,-30,0)' - '(150,-50,0)' - '(50,150,0).
	 */
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
  	glBegin(GL_POLYGON);
	glVertex3f(-50,30,0);
	glVertex3f(150,-50,0);
	glVertex3f(50,150,0);
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
