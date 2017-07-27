/*******************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 *
 * Last update: July 2017
 *
 * This program is Free Software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License (http://www.gnu.org/licenses/gpl.txt) for more details.
 *
 * main.cpp - the main function for the 'Example-003 (Old Mode)' Test.
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
void resize(int w, int h);
void manageKeys(unsigned char key, int x, int y);

/// The main function for the <i>'Example-003 (Old Mode)'</i> Test.
int main(int argc, char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-003' Test, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws the 'filled version' of the quadrilateral (in 'red') with vertices '(30,20,0)' - '(80,20,0)' - '(80,80,0)' - '(20,80,0)' in an OpenGL window, ";
	cout<<"and provides a basic interaction mechanism with the user. In fact,"<<endl;
	cout<<"\tthe user can apply (upon request) the following orthographic projections to the scene:"<<endl<<endl;
	cout<<"\t\t0. the orthographic viewing box '[0,100]' x '[0,100]' x '[-1,1]' is activated by pressing the '0' key (the 'Viewing Configuration #0'). This is the ";
	cout<<"standard orthographic viewing box of the scene, and the"<<endl;
	cout<<"\t\t   quadrilateral is completely rendered in the middle of the scene."<<endl<<endl;
	cout<<"\t\t1. The orthographic viewing box '[-100,100]' x '[-100,100]' x '[-1,1]' is activated by pressing the '1' key (the 'Viewing Configuration #1'). The ";
	cout<<"reduced and scaled quadrilateral is completely rendered in"<<endl;
	cout<<"\t\t   the top right corner of the scene."<<endl<<endl;
	cout<<"\t\t2. The orthographic viewing box '[20,80]' x '[20,80]' x '[-1,1]' is activated by pressing the '2' key (the 'Viewing Configuration #2'). This ";
	cout<<"orthographic viewing box does not cover entirely the ortographic"<<endl;
	cout<<"\t\t   projection of the quadrilateral, which is partially rendered in the middle of the scene."<<endl<<endl;
	cout<<"\t\t3. The orthographic viewing box '[0,100]' x '[0,100]' x '[-2,5]' is activated by pressing the '3' key (the 'Viewing Configuration #3'). The ";
	cout<<"quadrilateral is completely rendered in the middle of the scene as"<<endl;
	cout<<"\t\t   like as when the standard orthographic viewing box is exploited, even if this ortographic viewing box is different."<<endl<<endl;
	cout<<"\t\t4. The orthographic viewing box '[0,200]' x '[0,200]' x '[-1,1]' is activated by pressing the '4' key (the 'Viewing Configuration #4'). The reduced and ";
	cout<<"scaled quadrilateral is completely rendered in the"<<endl;
	cout<<"\t\t   bottom left corner of the scene."<<endl<<endl;
	cout<<"\t\t5. The orthographic viewing box '[120,200]' x '[90,200]' x '[-1,3]' is activated by pressing the '5' key (the 'Viewing Configuration #5'). This ";
	cout<<"orthographic viewing box does not intersect the orthographic"<<endl;
	cout<<"\t\t   projection of the quadrilateral, which is not rendered at all."<<endl<<endl;
	cout<<"\tLikewise, the window of interest can be closed by pressing any among the 'Q', the 'q', and the 'Esc' keys."<<endl<<endl;
	cout.flush();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowPosition(50, 25);
	glutInitWindowSize(480, 480);
	glutCreateWindow("The 'Example-003' Test, based on the (Old Mode) OpenGL");
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
	glOrtho(left_value, right_value, bottom_value, top_value, near_value, far_value);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/// This function draws the <i>'filled version'</i> of a quadrilateral (in <i>'red'</i>) in the OpenGL window of interest by using the orthographic projection, chosen by the user.
void draw()
{
	/* We draw the 'filled version' of a quadrilateral (in 'red') in the OpenGL window of interest by using the orthographic projection, chosen by the user. */
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
	/* We initialize the OpenGL window of interest. */
	left_value = 0.0;
	right_value = 100.0;
	bottom_value = 0.0;
	top_value = 100.0;
	near_value = -1.0;
	far_value = 1.0;
	glClearColor(1.0, 1.0, 1.0, 0.0);
	eol=false;
	cout<<"\tAt the beginning, the 'Viewing Configuration #0', corresponding to the orthographic viewing box '[0,100]' x '[0,100]' x '[-1,1]', is applied to the scene.";
	cout<<endl<<endl;
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
		cout<<"\tThis program is closing correctly ... "<<endl<<endl;
		cout << "\tPress the RETURN key to finish ... ";
		cin.get();
		#ifndef _MSC_VER
			cout << endl;
			cout.flush();
		#endif
		exit(EXIT_SUCCESS);
		break;

		case 'Q':

		/* The key is 'Q', thus we can exit from this program! */
		if(eol) cout<<endl;
		cout<<"\tThis program is closing correctly ... "<<endl<<endl;
		cout << "\tPress the RETURN key to finish ... ";
		cin.get();
		#ifndef _MSC_VER
			cout << endl;
			cout.flush();
		#endif
		exit(EXIT_SUCCESS);
		break;

		case 27:

		/* The key is 'Esc', thus we can exit from this program! */
		if(eol) cout<<endl;
		cout<<"\tThis program is closing correctly ... "<<endl<<endl;
		cout << "\tPress the RETURN key to finish ... ";
		cin.get();
		#ifndef _MSC_VER
			cout << endl;
			cout.flush();
		#endif
		exit(EXIT_SUCCESS);
		break;

		case '0':

		/* The key is '0', thus we exploit the orthographic viewing box '[0,100]' x '[0,100]' x '[-1,1]' (thus, the 'Viewing Configuration #0'). */
		cout<<"\tThe 'Viewing Configuration #0', corresponding to the orthographic viewing box '[0,100]' x '[0,100]' x '[-1,1]', is currently applied to the scene.";
		cout<<endl;
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

		/* The key is '1', thus we exploit the orthographic viewing box '[-100,100]' x '[-100,100]' x '[-1,1]' (thus, the 'Viewing Configuration #1'). */
		cout<<"\tThe 'Viewing Configuration #1', corresponding to the orthographic viewing box '[-100,100]' x '[-100,100]' x '[-1,1]', is currently applied to the ";
		cout<<"scene."<<endl;
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

		/* The key is '2', thus we exploit the orthographic viewing box '[20,80]' x '[20,80]' x '[-1,1]' (thus, the 'Viewing Configuration #2'). */
		cout<<"\tThe 'Viewing Configuration #2', corresponding to the orthographic viewing box '[20,80]' x '[20,80]' x '[-1,1]', is currently applied to the scene.";
		cout<<endl;
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

		/* The key is '3', thus we exploit the orthographic viewing box '[0,100]' x '[0,100]' x '[-2,5]' (thus, the 'Viewing Configuration #3'). */
		cout<<"\tThe 'Viewing Configuration #3', corresponding to the orthographic viewing box '[0,100]' x '[0,100]' x '[-2,5]', is currently applied to the scene.";
		cout<<endl;
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

		/* The key is '4', thus we exploit the orthographic viewing box '[0,200]' x '[0,200]' x '[-1,1]' (thus, the 'Viewing Configuration #4'). */
		cout<<"\tThe 'Viewing Configuration #4', corresponding to the orthographic viewing box '[0,200]' x '[0,200]' x '[-1,1]', is currently applied to the scene.";
		cout<<endl;
		cout.flush();
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

		/* The key is '5', thus we exploit the orthographic viewing box '[120,200]' x '[90,200]' x '[-1,3]' (thus, the 'Viewing Configuration #5'). */
		cout<<"\tThe 'Viewing Configuration #5', corresponding to the orthographic viewing box '[120,200]' x '[90,200]' x '[-1,3]', is currently applied to the scene.";
		cout<<endl;
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

