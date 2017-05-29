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
 * main.cpp - the main function for the 'Example-035 (Old Mode)' Test.
 *******************************************************************************************************************************************************/

/* First, we must understand which platform we are using. */
#include <cstdlib>
#include <iostream>
#include <cmath>
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

/// This flag indicates what projection we must exploit while drawing the scene.
/**
 * This flag assumes the following values:
 *
 * 0: it indicates to use the viewing orthographic box '[-40,40]' x '[-40,40]' x '[-80,80]'
 * 1: it indicates to use the viewing perspective box (frustum) '[-2.7,2.7]' x '[-2.7,2.7]' x '[2.0,7.0]'
 *
 * The user can choose what projection must be used by pressing cyclically the the ' ' (space) key.
 */
int projection=0;

/* Prototypes for all functions of interest! */
void draw();
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);

/// The main function for the <i>'Example-035 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-035' Test, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws a specific 'Cube' shape in an OpenGL window. Broadly speaking, any 'Cube' shape is formed by 8 vertices, 12 edges, and 6 square faces, with three meeting at each vertex. In other words, it is the boundary of the 'Cube' (or"<<endl;
	cout<<"\tthe 'Regular Hexahedron') solid."<<endl<<endl;
	cout<<"\tIn this test, we consider a specific 'Cube' shape, such that a different color is assigned with each face, and such that its domain is '[-30,30]' x '[-30,30]' x '[-60,-30]'."<<endl<<endl;
	cout<<"\tHere, the user cannot modify the orientations and the colors for 6 square faces in the 'Cube' shape of interest. Instead, the user can press cyclically the ' ' (space) key for choosing what viewing configuration has to be applied"<<endl;
	cout<<"\tbetween the following viewing configurations:"<<endl<<endl;
	cout<<"\t\t-) the 'Viewing Configuration #0' is based on the orthographic box '[-40,40]' x '[-40,40]' x '[-80,80]';"<<endl;
	cout<<"\t\t-) the 'Viewing Configuration #1' is based on the perspective box '[-2.7,2.7]' x '[-2.7,2.7]' x '[2.0,70]'."<<endl<<endl;
	cout<<"\tLikewise, the window of interest can be closed by pressing any among the 'Q', the 'q', and the 'Esc' keys."<<endl<<endl;
	cout.flush();
	
	/* If we arrive here, we can draw the 'Cube' shape of interest. */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-035' Test, based on the (Old Mode) OpenGL");
	glutReshapeFunc(resize);
	glutKeyboardFunc(manageKeys);
	glutDisplayFunc(draw);
	glewExperimental = GL_TRUE;
   	glewInit();
   	initialize(); 
	glutMainLoop();
	return EXIT_SUCCESS;
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - ' ' (space) keys. */
	switch (key)
	{
		case 'q':
	
		/* The key is 'q', thus we can exit from this program. */
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case 'Q':
	
		/* The key is 'Q', thus we can exit from this program. */
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case 27:
	
		/* The key is 'Esc', thus we can exit from this program. */
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case ' ':
		
		/* The key is ' ' (space), thus we change the projection of interest! */
		projection=(projection+1)%2;
		resize(500,500);
		glutInitWindowSize(500,500);
		glutPostRedisplay();
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
   	if(projection==0) glOrtho(-40.0, 40.0, -40.0, 40.0, -80, 80);
   	else glFrustum(-2.7, 2.7, -2.7, 2.7, 2.0, 70.0);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	projection=0;
	cout<<"\tAt the beginning, the 'Cube' shape of interest is drawn by using the ";
	if(projection==0) cout<<"viewing orthographic box '[-40,40]' x '[-40,40]' x '[-80,80]' (thus, the 'Viewing Configuration #0').";
	else cout<<"viewing perspective box (frustum) [-2.7,2.7]' x '[-2.7,2.7]' x '[2.0,7.0]' (thus, the 'Viewing Configuration #1').";
	cout<<endl<<endl;
	cout.flush();
}

/// This function draws the 'Cube' shape of interest in the main OpenGL window.
void draw()
{
	/* First, we clear everything. Then, we draw the 3D cube of interest. */
	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	if(projection==1)
	{
		/* We must exploit the 'glFrustum()' perspective projection! */
		
		/* Face #0 for the cube (red). */
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_POLYGON);
		glVertex3f(30,-30,-30);
		glVertex3f(30,30,-30);
		glVertex3f(-30,30,-30);
		glVertex3f(-30,-30,-30);
		glEnd();
	
		/* Face #1 for the cube (black). */
		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_POLYGON);
		glVertex3f(-30,30,-60);
		glVertex3f(30,30,-60);
		glVertex3f(30,-30,-60);
		glVertex3f(-30,-30,-60);
		glEnd();
		
		/* Face #2 for the cube (green). */
		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_POLYGON);
		glVertex3f(30,-30,-60);
		glVertex3f(30,-30,-30);
		glVertex3f(30,30,-30);
		glVertex3f(30,30,-60);
		glEnd();
	
		/* Face #3 for the cube (yellow). */
		glColor3f(1.0f, 1.0f, 0.0f);
		glBegin(GL_POLYGON);
		glVertex3f(-30,30,-30);
		glVertex3f(-30,30,-60);
		glVertex3f(-30,-30,-60);
		glVertex3f(-30,-30,-30);
		glEnd();
		
		/* Face #4 for the cube (blue). */
		glColor3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_POLYGON);
		glVertex3f(-30,30,-60);
		glVertex3f(30,30,-60);
		glVertex3f(30,30,-30);
		glVertex3f(-30,30,-30);
		glEnd();
		
		/* Face #5 for the cube (orange). */
		glColor3f(1.0f, 0.5f, 0.0f);
		glBegin(GL_POLYGON);
		glVertex3f(-30,-30,-60);
		glVertex3f(30,-30,-60);
		glVertex3f(30,-30,-30);
		glVertex3f(-30,-30,-30);
		glEnd();
		glFlush();
	}
	else
	{
		/* We must exploit the 'glOrtho()' ortographic projection! */
		
		/* Face #0 for the cube (black). */
		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_POLYGON);
		glVertex3f(-30,30,-60);
		glVertex3f(30,30,-60);
		glVertex3f(30,-30,-60);
		glVertex3f(-30,-30,-60);
		glEnd();
		
		/* Face #1 for the cube (green). */
		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_POLYGON);
		glVertex3f(30,-30,-60);
		glVertex3f(30,-30,-30);
		glVertex3f(30,30,-30);
		glVertex3f(30,30,-60);
		glEnd();
	
		/* Face #2 for the cube (yellow). */
		glColor3f(1.0f, 1.0f, 0.0f);
		glBegin(GL_POLYGON);
		glVertex3f(-30,30,-30);
		glVertex3f(-30,30,-60);
		glVertex3f(-30,-30,-60);
		glVertex3f(-30,-30,-30);
		glEnd();
		
		/* Face #3 for the cube (blue). */
		glColor3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_POLYGON);
		glVertex3f(-30,30,-60);
		glVertex3f(30,30,-60);
		glVertex3f(30,30,-30);
		glVertex3f(-30,30,-30);
		glEnd();
		
		/* Face #4 for the cube (orange). */
		glColor3f(1.0f, 0.5f, 0.0f);
		glBegin(GL_POLYGON);
		glVertex3f(-30,-30,-60);
		glVertex3f(30,-30,-60);
		glVertex3f(30,-30,-30);
		glVertex3f(-30,-30,-30);
		glEnd();
		
		/* Face #5 for the cube (red). */
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_POLYGON);
		glVertex3f(30,-30,-30);
		glVertex3f(30,30,-30);
		glVertex3f(-30,30,-30);
		glVertex3f(-30,-30,-30);
		glEnd();
		glFlush();
	}
	
	/* Now, we finalize this function! */
	cout<<"\tThe 'Cube' shape of interest is currently drawn by using the ";
	if(projection==0) cout<<"viewing orthographic box '[-40,40]' x '[-40,40]' x '[-80,80]' (thus, the 'Viewing Configuration #0').";
	else cout<<"viewing perspective box (frustum) [-2.7,2.7]' x '[-2.7,2.7]' x '[2.0,7.0]' (thus, the 'Viewing Configuration #1').";
	cout<<endl;
	cout.flush();
}
