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
* main.cpp - the main function for the 'Example-003 (Old Mode)' example.
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

/* Global variables */
GLfloat left_value, right_value, bottom_value, top_value, near_value, far_value;
bool eol=false;

/* Prototypes for all functions of interest! */
void draw();
void initialize();
void resize(int w, int h);
void manageKeys(unsigned char key, int x, int y);

/// The main function for the <i>'Example-003 (Old Mode)'</i> example.
int main(int argc, char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-003' Example, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws a quadrilateral in 'red' with vertices (30,20,0) - (80,20,0) - (80,80,0) - (20,80,0) by applying several viewport configurations (chosen by pressing the '0-1-2-3-4-5' keys)."<<endl<<endl;
	cout<<"\tIt is possible to end this program by pressing one among the 'Q' - 'q' - 'Esc' keys."<<endl<<endl;
	cout.flush();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowPosition(50, 25);
	glutInitWindowSize(480, 480);
	glutCreateWindow("The 'Example-003' Example, based on the (Old Mode) OpenGL");
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
	glOrtho(left_value, right_value, bottom_value, top_value, near_value, far_value);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/// This function draws a quadrilateral in <i>'red'</i> in the OpenGL window of interest.
void draw()
{
	/* We draw a quadrilateral in 'red' in the OpenGL window of interest. */
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(30.0, 20.0, 0.0);
	glVertex3f(80.0, 20.0, 0.0);
	glVertex3f(80.0, 80.0, 0.0);
	glVertex3f(20.0, 80.0, 0.0);
	glEnd();
	glFlush();
}

/// This function initializes the OpenGL window of interest. */
void initialize()
{
	/* We initialize the OpenGL window of interest */
	left_value = 0.0;
	right_value = 100.0;
	bottom_value = 0.0;
	top_value = 100.0;
	near_value = -1.0;
	far_value = 1.0;
	glClearColor(1.0, 1.0, 1.0, 0.0);
	eol=false;
	cout<<"\tThe configuration #0 with the viewing box [0,100] x [0,100] x [-1,1] is initially applied to the current scene."<<endl<<endl;
	cout.flush();
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '0' - '1' - '2' - '3' - '4' - '5' keys. */
	switch (key)
	{
		case 'q':

		/* The key is 'q', thus we can exit from this program! */
		if(eol) cout<<endl;
		exit(EXIT_SUCCESS);
		break;

		case 'Q':

		/* The key is 'Q', thus we can exit from this program! */
		if(eol) cout<<endl;
		exit(EXIT_SUCCESS);
		break;

		case 27:

		/* The key is 'Esc', thus we can exit from this program! */
		if(eol) cout<<endl;
		exit(EXIT_SUCCESS);
		break;

		case '0':

		/* The key is '0', thus we apply the initial configuration #0: glOrtho(0,100,0,100,-1,1). */
		cout<<"\tApplying the configuration #0 with the viewing box [0,100] x [0,100] x [-1,1] to the current scene."<<endl;
		cout.flush();
		eol=true;
		left_value = 0.0;
		right_value = 100.0;
		bottom_value = 0.0;
		top_value = 100.0;
		near_value = -1.0;
		far_value = 1.0;
		resize(480, 480);
		glutReshapeWindow(480, 480);
		glutPostRedisplay();
		break;

		case '1':

		/* The key is '1', thus we apply the configuration #1: glOrtho(-100,100,-100,100,-1,1). */
		cout<<"\tApplying the configuration #1 with the viewing box [-100,100] x [-100,100] x [-1,1] to the current scene."<<endl;
		cout.flush();
		eol=true;
		left_value = -100.0;
		right_value = 100.0;
		bottom_value = -100.0;
		top_value = 100.0;
		near_value = -1.0;
		far_value = 1.0;
		resize(480, 480);
		glutReshapeWindow(480, 480);
		glutPostRedisplay();
		break;

		case '2':

		/* The key is '2', thus we apply the configuration #2: glOrtho(20,80,20,80,-1,1). */
		cout<<"\tApplying the configuration #2 with the viewing box [20,80] x [20,80] x [-1,1] to the current scene."<<endl;
		cout.flush();
		eol=true;
		left_value = 20;
		right_value = 80;
		bottom_value = 20;
		top_value = 80;
		near_value = -1.0;
		far_value = 1.0;
		resize(480, 480);
		glutReshapeWindow(480, 480);
		glutPostRedisplay();
		break;

		case '3':

		/* The key is '3', thus we apply the configuration #3: glOrtho(0,100,0,100,-2,5). */
		cout<<"\tApplying the configuration #3 with the viewing box [0,100] x [0,100] x [-2,5] to the current scene."<<endl;
		cout.flush();
		eol=true;
		left_value = 0;
		right_value = 100;
		bottom_value = 0;
		top_value = 100;
		near_value = -2.0;
		far_value = 5.0;
		resize(480, 480);
		glutReshapeWindow(480, 480);
		glutPostRedisplay();
		break;

		case '4':

		/* The key is '4', thus we apply the configuration #4: glOrtho(0,200,0,200,-1,1). */
		cout<<"\tApplying the configuration #4 with the viewing box [0,200] x [0,200] x [-1,1] to the current scene."<<endl;
		std::cout.flush();
		eol=true;
		left_value = 0;
		right_value = 200;
		bottom_value = 0;
		top_value = 200;
		near_value = -1.0;
		far_value = 1.0;
		resize(480, 480);
		glutReshapeWindow(480, 480);
		glutPostRedisplay();
		break;

		case '5':

		/* The key is '5', thus we apply the configuration #5: glOrtho(120,200,90,200,-1,3). */
		cout<<"\tApplying the configuration #5 with the viewing box [120,200] x [90,200] x [-1,3] to the current scene."<<endl;
		cout.flush();
		eol=true;
		left_value = 120;
		right_value = 200;
		bottom_value = 90;
		top_value = 200;
		near_value = -1.0;
		far_value = 3.0;
		resize(480, 480);
		glutReshapeWindow(480, 480);
		glutPostRedisplay();
		break;

		default:

		/* Other keys are not important for us! */
		break;
	}
}
