/*******************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 * 
 * Last update: December 2016
 *
 * This program is Free Software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.                                       
 *                                                                         
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License (http://www.gnu.org/licenses/gpl.txt) for more details.
 * 
 * main.cpp - the main function for the 'Example-010 (Old Mode)' example
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
int rendering;

/// The main function for the <i>'Example-010 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(480,480);
	glutCreateWindow("The 'Example-010' Example, based on the (Old Mode) OpenGL");
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
   	glOrtho(0,130,0,120,-1,1);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function draws the scene in the OpenGL window of interest by using the primitive, chosen by the user.
void draw()
{
	/* We draw the scene by using the primitive, chosen by the user. */
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(10.0);
	glLineWidth(2.0);
	glColor3f(1,0,0);
	glBegin(rendering);
	glVertex3f(20,80,0);
	glVertex3f(20,50,0);
	glVertex3f(50,20,0);
	glVertex3f(80,20,0);
	glVertex3f(110,50,0);
	glVertex3f(110,80,0);
	glVertex3f(80,100,0);
	glVertex3f(50,100,0);
	glEnd();
	glFlush();
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	cout<<endl<<"\tThis is the 'Example-010' Example, based on the (Old Mode) OpenGL"<<endl<<endl;
	cout.flush();
	glClearColor(1.0, 1.0, 1.0, 0.0); 
	rendering=GL_POINTS;
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '0' - '1' - '2' - '3' - '4' - '5' keys */
	switch (key)
	{
		case 113:
	
		/* The key is 'q' */
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case 81:
	
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
		
		case 48:
		
		/* The key is '0', thus the GL_POINTS primitive is required. */
		rendering=GL_POINTS;
		glutPostRedisplay();
		cout<<"\tUsing the GL_POINTS primitive for drawing the scene"<<endl;
		cout.flush();
		break;
		
		case 49:
		
		/* The key is '1', thus the GL_LINES primitive is required. */
		rendering=GL_LINES;
		glutPostRedisplay();
		cout<<"\tUsing the GL_LINES primitive for drawing the scene"<<endl;
		cout.flush();
		break;
		
		case 50:
		
		/* The key is '2', thus the GL_LINE_STRIP primitive is required. */
		rendering=GL_LINE_STRIP;
		glutPostRedisplay();
		cout<<"\tUsing the GL_LINE_STRIP primitive for drawing the scene"<<endl;
		cout.flush();
		break;
		
		case 51:
		
		/* The key is '3', thus the GL_LINE_LOOP primitive is required. */
		rendering=GL_LINE_LOOP;
		glutPostRedisplay();
		cout<<"\tUsing the GL_LINE_LOOP primitive for drawing the scene"<<endl;
		cout.flush();
		break;
		
		case 52:
		
		/* The key is '4', thus the GL_POLYGON primitive is required. */
		rendering=GL_POLYGON;
		glutPostRedisplay();
		cout<<"\tUsing the GL_POLYGON primitive for drawing the scene"<<endl;
		cout.flush();
		break;
		
		case 53:
		
		/* The key is '5', thus the GL_TRIANGLES primitive is required. */
		rendering=GL_TRIANGLES;
		glutPostRedisplay();
		glutPostRedisplay();
		cout<<"\tUsing the GL_TRIANGLES primitive for drawing the scene"<<endl;
		cout.flush();
		break;
		
		default:

    	/* Other keys are not important for us */
    	break;
	}
}
