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
 * main.cpp - the main function for the 'Example-005 (Old Mode)' example.
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
	cout<<"\tIt draws the 'filled version' of a polygon (in 'red'), obtained as the intersection between the following elements:"<<endl<<endl;
	cout<<"\t\t-) the ortographic viewing box '[0,100]' x '[0,100]' x '[-1,1]';"<<endl;
	cout<<"\t\t-) the triangle with vertices '(x,20,0)' - '(80,20,0)' - '(80,80,0)', for any 'x' coordinate along the x-axis."<<endl<<endl;
	cout<<"\tHere, the orthographic viewing box is not modified. Instead, the 'x' coordinate of the triangle, initially set to '20', can be moved by the user along the x-axis. The user can:"<<endl<<endl;
	cout<<"\t\t-) increase the 'x' coordinate for the triangle of interest by 1.0 by pressing the '+' key;"<<endl;
	cout<<"\t\t-) decrease the 'x' coordinate for the triangle of interest by 1.0 by pressing the '-' key;"<<endl;
	cout<<"\t\t-) reset the 'x' coordinate for the triangle of interest to its initial value '20' by pressing the '=' key."<<endl<<endl;
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
	/* We update the projection and the modeling matrices! */
	glViewport(0, 0, w, h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glOrtho(0,100,0,100,-1,1);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function draws the <i>'filled version'</i> of the polygon (in <i>'red'</i>), which is the intersection between a triangle and the ortographic viewing box, in the OpenGL window of interest.
void draw()
{
	/* We draw the 'filled version' of the polygon (in 'red'), which is the intersection between the following components, in the OpenGL window of interest:
	 *
	 * -) the ortographic viewing box '[0,100]' x '[0,100]' x '[-1,1]';
	 * -) the triangle with vertices '(x,20,0)' - '(80,20,0)' - '(80,80,0)'.
	 */
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
	cout<<"\tThe 'x' coordinate for the triangle of interest is initially set to "<<xcoord<<" in the current scene."<<endl<<endl;
	cout.flush();
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '+' - '-' - "=" keys. */
	switch (key)
	{
		case 'q':
	
		/* The key is 'q', thus we can exit from this program. */
		if(eol) cout<<endl;
		exit(EXIT_SUCCESS);
		break;
		
		case 'Q':
	
		/* The key is 'Q', thus we can exit from this program. */
		if(eol) cout<<endl;
		exit(EXIT_SUCCESS);
		break;
		
		case 27:
	
		/* The key is 'Esc', thus we can exit from this program. */
		if(eol) cout<<endl;
		exit(EXIT_SUCCESS);
		break;
		
		case '+':
		
		/* The key is '+, thus we increase the 'x' coordinate for the triangle of interest. */
		xcoord=xcoord+(GLfloat)1.0;
		cout<<"\tThe 'x' coordinate for the triangle of interest is increased to "<<xcoord<<" in the current scene."<<endl;
		cout.flush();
		eol=true;
		glutPostRedisplay();
		break;
		
		case '-':
		
		/* The key is '-', thus we decrease the 'x' coordinate for the triangle of interest. */
		xcoord=xcoord-(GLfloat)1.0;
		cout<<"\tThe 'x' coordinate for the triangle of interest is decreased to "<<xcoord<<" in the current scene."<<endl;
		cout.flush();
		eol=true;
		glutPostRedisplay();
		break;
		
		case '=':
		
		/* The key is '=', thus we reinitialize the 'x' coordinate for the triangle of interest. */
		xcoord=20.0;
		eol=true;
		cout<<"\tThe 'x' coordinate for the triangle of interest is set to its default value "<<xcoord<<" in the current scene."<<endl;
		cout.flush();
		glutPostRedisplay();
		break;
		
		default:

    	/* Other keys are not important for us! */
    	break;
	}
}
