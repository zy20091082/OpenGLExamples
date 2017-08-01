/*******************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 * 
 * Last update: August 2017
 *
 * This program is Free Software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.                                       
 *                                                                         
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License (http://www.gnu.org/licenses/gpl.txt) for more details.
 * 
 * main.cpp - the main function for the 'Example-001 (Old Mode)' Test.
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

/// This function draws only the <i>'black'</i> background in the OpenGL window of interest.
void draw(void)
{
	/* We draw only the 'black' background in the OpenGL window of interest. */
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

/// The main function for the <i>'Example-001 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-001' Test, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt is similar to the classic 'Hello World' program for testing the correctness of the building infrastructure."<<endl;
	cout<<"\tBroadly speaking, it creates an empty OpenGL window with the 'black' background, and provides no interaction mechanism with the user."<<endl<<endl;
	cout<<"\tHere, the window of interest must be stopped through an enforced closure."<<endl<<endl;
	cout.flush();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(50,25);
	glutInitWindowSize(480,480);
	glutCreateWindow("The 'Example-001' Test, based on the (Old Mode) OpenGL");
	glutDisplayFunc(draw);
	glutMainLoop();
	return EXIT_SUCCESS;
}

