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
 * main.cpp - the main function for the 'Example-019 (Old Mode)' Test.
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

/// The main function for the <i>'Example-019 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */ 
	cout<<endl<<"\tThis is the 'Example-019' Test, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws '2' versions of the 'Double Square Annulus' shape in an OpenGL window. This shape is bounded by an 'external' axis-parallel rectangle, and by '2'";
	cout<<" 'internal' axis-parallel rectangles, entirely contained in the 'external'"<<endl;
	cout<<"\trectangle. Broadly speaking, any 'Double Square Annulus' shape is the union of '2' 'Square Annulus' shapes, connected along one side of their 'external' ";
	cout<<"rectangles. Recall that any 'Square Annulus' shape is contained between '2'"<<endl;
	cout<<"\t(concentric) axis-parallel rectangles of different size."<<endl<<endl;
	cout<<"\tHere, the 'Double Square Annulus' shape of interest is approximated by '2' triangle strips (respectively, in 'red' and in 'blue'), where a bunch of ";
	cout<<"'Steiner' points are added in order to make this possible. They approximate,"<<endl;
	cout<<"\trespectively, the 'Square Annulus' shapes (mentioned above), such that their union form the 'Double Square Annulus' shape. Specifically, this test draws ";
	cout<<"the 'filled' and the 'wireframe versions' of all triangles in '2' triangle"<<endl;
	cout<<"\tstrips, just mentioned."<<endl<<endl;
	cout<<"\tThis test also provides a very basic interaction mechanism with the user. Here, the window of interest can be closed by pressing any among the 'Q', the ";
	cout<<"'q', and the 'Esc' keys."<<endl<<endl;
	cout.flush();

	/* If we arrive here, then we draw the 'wireframe' and the 'filled' versions for the triangle strips of interest. */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(450,480);
	glutCreateWindow("The 'Example-019' Test, based on the (Old Mode) OpenGL");
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
	/* We are interested only in the 'q' - 'Q' - 'Esc' keys. */
	switch (key)
	{
		case 'q':
	
		/* The key is 'q', thus we can exit from this program. */
		cout<<"\tThis program is closing correctly ... "<<endl<<endl;
		cout << "\tPress the RETURN key to finish ... ";
		cin.get();
		#ifndef _MSC_VER
			cout << endl;
			cout.flush();
		#endif
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case 'Q':
	
		/* The key is 'Q', thus we can exit from this program. */
		cout<<"\tThis program is closing correctly ... "<<endl<<endl;
		cout << "\tPress the RETURN key to finish ... ";
		cin.get();
		#ifndef _MSC_VER
			cout << endl;
			cout.flush();
		#endif
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case 27:
	
		/* The key is 'Esc', thus we can exit from this program. */
		cout<<"\tThis program is closing correctly ... "<<endl<<endl;
		cout << "\tPress the RETURN key to finish ... ";
		cin.get();
		#ifndef _MSC_VER
			cout << endl;
			cout.flush();
		#endif
		cout.flush();
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
	/* We update the projection and the modeling matrices! */
	glViewport(0, 0, w, h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glOrtho(0,200,0,260,-1,1);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function draws the <i>'filled'</i> and the <i>'wireframe versions'</i> of all triangles in 2 triangle strips (respectively, in <i>'red'</i> and in <i>'blue'</i>), that approximate the <i>'Double Square Annulus'</i> shape, in the OpenGL window of interest.
void draw()
{
	/* We draw the 'filled' and the 'wireframe versions' of all triangles in 2 triangle strips (respectively, in 'red' and in 'blue'), that approximate the 'Double
	 * Square Annulus' shape, in the OpenGL window of interest. We start from the 'wireframe versions' of all triangles in the triangle strip #0 (in 'red'). */
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
	
	/* Now, we draw the 'filled versions' of all triangles in the triangle strip #0 (in 'red'). */
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
	
	/* Now, we draw the 'wireframe versions' of all triangles in the triangle strip #1 (in 'blue'). */
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
	
	/* Now, we draw the 'filled versions' of all triangles in the triangle strip #1 (in 'blue'). */
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

