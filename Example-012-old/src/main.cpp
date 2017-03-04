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
 * main.cpp - the main function for the 'Example-012 (Old Mode)' example
 *******************************************************************************************************************************************************/

/* First, we must understand which platform we are using. */
#include <cstdlib>
#include <iostream>
using namespace std;
#ifdef __APPLE__

	/* We are using a MacOSX platform (Macintosh) */
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
GLenum face,mode;

/// The main function for the <i>'Example-012 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(480,480);
	glutCreateWindow("The 'Example-012' Example, based on the (Old Mode) OpenGL");
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
   	glOrtho(0,100,0,100,-1,1);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function draws a triangle strip in the OpenGL window of interest by using the face and the mode rendering, chosen by the user.
void draw()
{
	/* We draw a triangle strip in the OpenGL window of interest by using the face and the mode rendering, chosen by the user. */
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(10.0);
	glLineWidth(2.0);
	glColor3f(0.6,0.7,0.7);
	glPolygonMode(face,mode);
	glPolygonMode(face,mode);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(10.0, 90.0, 0.0);
   	glVertex3f(10.0, 10.0, 0.0);
   	glVertex3f(35.0, 75.0, 0.0);
    glVertex3f(30.0, 20.0, 0.0);
    glVertex3f(90.0, 90.0, 0.0);
   	glVertex3f(80.0, 40.0, 0.0);
	glEnd();
	glFlush();
	glFlush();
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	cout<<endl<<"\tThis is the 'Example-012' Example, based on the (Old Mode) OpenGL"<<endl;
	cout<<"\tIt draws a triangle strip in the scene, and it allows to modify its rendering as follows:"<<endl<<endl;
	cout<<"\t-) only the 'front' side of the triangles in the triangle strip is rendered by pressing the 'f' and 'F' keys"<<endl;
	cout<<"\t-) only the 'back' side of the triangles in the triangle strip is rendered by pressing the 'b' and 'B' keys"<<endl;
	cout<<"\t-) both the sides of the triangles in the triangle strip are rendered by pressing the 't' and 'T' keys"<<endl;
	cout<<"\t-) only the vertices of the triangles in the triangle strip are rendered by pressing the 'p' and 'P' keys"<<endl;
	cout<<"\t-) only the edges of the triangles in the triangle strip (wireframe version) are rendered by pressing the 'l' and the 'L' keys"<<endl;
	cout<<"\t-) the triangles in the triangle strip are entirely rendered (filled version) by pressing the 'i' and 'I' keys"<<endl<<endl;
	cout<<"\tIt is possible to end this program by pressing one among the 'Q' - 'q' - 'Esc' keys."<<endl<<endl;
	cout.flush();
	glClearColor(1.0, 1.0, 1.0, 0.0);
	face=GL_FRONT;
	mode=GL_FILL;
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - 'f' - 'F' - 'b' - 'F' - 't' - 'T' - 'i' - 'I' - 'l' - 'L' - 'P' - 'p' keys */
	switch (key)
	{
		case 'q':
	
		/* The key is 'q' */
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case 'Q':
	
		/* The key is 'Q' */
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case 27:
	
		/* The key is 'Esc' */
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case 'F':

		/* The key is 'F' */
		face=GL_FRONT;
		cout<<"\tRendering only the front side of the triangle strip"<<endl;
		cout.flush();
		glutPostRedisplay();
		break;
		
		case 'f':

		/* The key is 'f' */
		face=GL_FRONT;
		cout<<"\tRendering only the front side of the triangle strip"<<endl;
		cout.flush();
		glutPostRedisplay();
		break;
		
		case 'B':

		/* The key is 'B' */
		face=GL_BACK;
		cout<<"\tRendering only the back side of the triangle strip"<<endl;
		cout.flush();
		glutPostRedisplay();
		break;
		
		case 'b':

		/* The key is 'b' */
		face=GL_BACK;
		cout<<"\tRendering only the back side of the triangle strip"<<endl;
		cout.flush();
		glutPostRedisplay();
		break;
		
		case 'T':

		/* The key is 'T' */
		face=GL_FRONT_AND_BACK;
		cout<<"\tRendering both the front and the back side of the triangle strip"<<endl;
		cout.flush();
		glutPostRedisplay();
		break;
		
		case 't':

		/* The key is 't' */
		face=GL_FRONT_AND_BACK;
		cout<<"\tRendering both the front and the back side of the triangle strip"<<endl;
		cout.flush();
		glutPostRedisplay();
		break;
		
		case 'I':

		/* The key is 'I' */
		mode=GL_FILL;
		cout<<"\tRendering completely the triangle strip (filled)"<<endl;
		cout.flush();
		glutPostRedisplay();
		break;
		
		case 'i':

		/* The key is 'i' */
		mode=GL_FILL;
		cout<<"\tRendering completely the triangle strip (filled)"<<endl;
		cout.flush();
		glutPostRedisplay();
		break;
		
		case 'L':

		/* The key is 'L' */
		mode=GL_LINE;
		cout<<"\tRendering only the lines of the triangle strip (wireframe)"<<endl;
		cout.flush();
		glutPostRedisplay();
		break;
		
		case 'l':

		/* The key is 'l' */
		mode=GL_LINE;
		cout<<"\tRendering only the lines of the triangle strip (wireframe)"<<endl;
		cout.flush();
		glutPostRedisplay();
		break;
		
		case 'P':
		
		/* The key is 'P' */
		mode=GL_POINT;
		cout<<"\tRendering only the vertices of the triangle strip"<<endl;
		cout.flush();
		glutPostRedisplay();
		break;
		
		case 'p':
		
		/* The key is 'p' */
		mode=GL_POINT;
		cout<<"\tRendering only the vertices of the triangle strip"<<endl;
		cout.flush();
		glutPostRedisplay();
		break;
		
		default:

    	/* Other keys are not important for us */
    	break;
	}
}
