/*******************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 * 
 * Last update: May 2017
 *
 * This program is Free Software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.                                       
 *                                                                         
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License (http://www.gnu.org/licenses/gpl.txt) for more details.
 * 
 * main.cpp - the main function for the 'Example-004 (Old Mode)' Test.
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

/// These global variables define the orthographic view of interest to be applied in the scene.
/*
 * -) the 'left_value' global variable indicates the minimum value of the range along the 'x'-axis;
 * -) the 'right_value' global variable indicates the maximum value of the range along the 'x'-axis;
 * -) the 'bottom_value' global variable indicates the minimum value of the range along the 'y'-axis;
 * -) the 'top_value' global variable indicates the maximum value of the range along the 'y'-axis;
 * -) the '-far_value' global variable indicates the minimum value of the range along the 'z'-axis;
 * -) the '-near_value' global variable indicates the maximum value of the range along the 'z'-axis.
 */
GLfloat left_value, right_value, bottom_value, top_value, near_value, far_value;

/// This boolean flag is useful for completing the textual interface.
bool eol=false;

/* Prototypes for all functions of interest! */
void draw();
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);

/// The main function for the <i>'Example-004 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-004' Test, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws the 'filled versions' of the following quadrilaterals in the scene:"<<endl<<endl;
	cout<<"\t\t0) the quadrilateral #0 (in 'red') with vertices '(20,20,0)' - '(80,20,0)' - '(80,80,0)' - '(20,80,0)';"<<endl;
	cout<<"\t\t1) the quadrilateral #1 (in 'green') with vertices '(120,120,0)' - '(180,120,0)' - '(180,180,0)' - '(120,180,0)';"<<endl<<endl;
	cout<<"\tby using the following orthographic projections (activated upon request by the user):"<<endl<<endl;
	cout<<"\t\t0) the ortographic viewing box '[0,100]' x '[0,100]' x '[-1,1]' is activated by pressing the '0' key (the 'viewing configuration #0'). In this case, only the quadrilateral #0 is shown in the scene."<<endl;
	cout<<"\t\t1) The ortographic viewing box '[0,200]' x '[0,200]' x '[-1,1]' is activated by pressing the '1' key (the 'viewing configuration #1'). In this case, both the quadrilaterals #0 and #1 are shown in the scene."<<endl<<endl;
	cout<<"\tIt is possible to end this program by pressing one among the 'Q' - 'q' - 'Esc' keys."<<endl<<endl;
	cout.flush();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(480,480);
	glutCreateWindow("The 'Example-004' Test, based on the (Old Mode) OpenGL");
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
   	glOrtho(left_value,right_value,bottom_value,top_value,near_value,far_value);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function draws the <i>'filled versions'</i> of 2 quadrilaterals (respectively, in <i>'red'</i> and in <i>'green'</i>) in the OpenGL window of interest by using the orthographic projection, chosen by the user.
void draw()
{
	/* We draw the 'filled versions' of 2 quadrilaterals (respectively, in 'red' and in 'green') in the OpenGL window of interest by using the orthographic projection, chosen by the user. */
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

/// This function initializes the OpenGL window of interest. */
void initialize() 
{
	/* We initialize the OpenGL window of interest. */
	left_value=0.0;
	right_value=100.0;
	bottom_value=0.0;
	top_value=100.0;
	near_value=-1.0;
	far_value=1.0;
	glClearColor(1.0, 1.0, 1.0, 0.0);
	eol=false;
	cout<<"\tThe 'viewing configuration #0', corresponding to the orthographic viewing box '[0,100]' x '[0,100]' x '[-1,1]', is initially applied to the scene."<<endl<<endl;
	cout.flush();
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '0' - '1' keys. */
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
		
		case '0':
		
		/* The key is '0', thus we exploit the orthographic viewing box '[0,100]' x '[0,100]' x '[-1,1]' (the 'viewing configuration #0'). */
		cout<<"\tThe 'viewing configuration #0', corresponding to the orthographic viewing box '[0,100]' x '[0,100]' x '[-1,1]', is currently applied to the scene."<<endl;
		cout.flush();
		eol=true;
		left_value=0.0;
		right_value=100.0;
		bottom_value=0.0;
		top_value=100.0;
		near_value=-1.0;
		far_value=1.0;
		resize(480,480);
		glutReshapeWindow(480,480);
		glutPostRedisplay();
		break;
		
		case '1':
		
		/* The key is '1', thus we exploit the orthographic viewing box '[0,200]' x '[0,200]' x '[-1,1]' (the 'viewing configuration #1'). */
		cout<<"\tThe 'viewing configuration #1', corresponding to the orthographic viewing box '[0,200]' x '[0,200]' x '[-1,1]', is currently applied to the scene."<<endl;
		cout.flush();
		eol=true;
		left_value=0.0;
		right_value=200.0;
		bottom_value=0;
		top_value=200.0;
		near_value=-1;
		far_value=1.0;
		resize(480,480);
		glutReshapeWindow(480,480);
		glutPostRedisplay();
		break;
	
		default:

    	/* Other keys are not important for us! */
    	break;
	}	
}
