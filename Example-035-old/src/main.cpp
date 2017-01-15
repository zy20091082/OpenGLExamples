/*******************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 * 
 * Last update: January 2017
 *
 * This program is Free Software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.                                       
 *                                                                         
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License (http://www.gnu.org/licenses/gpl.txt) for more details.
 * 
 * main.cpp - the main function for the 'Example-035 (Old Mode)' example
 *******************************************************************************************************************************************************/
 
/* First, we must understand which platform we are using. */
#include <cstdlib>
#include <iostream>
#include <cmath>
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

/// This flag indicates what projection we must exploit.
int projection=0;

/* Prototypes for all functions of interest! */
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);
void draw();

/// The main function for the <i>'Example-035 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a new window! */
	cout<<endl<<"\tThis is the 'Example-035' Example, based on the (Old Mode) OpenGL"<<endl<<endl;
	cout.flush();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-035' Example, based on the (Old Mode) OpenGL");
	glutReshapeFunc(resize);
	glutKeyboardFunc(manageKeys);
	glutDisplayFunc(draw);
	glewExperimental = GL_TRUE;
   	glewInit();
   	initialize(); 
	glutMainLoop();
	return EXIT_SUCCESS;
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	cout<<"\tWe draw a cube by choosing the projection to be used (orthographic or prospective) by pressing the ' ' key."<<endl<<endl;
	cout.flush();
	glClearColor(1.0, 1.0, 1.0, 0.0);
	projection=0;
}

/// This function updates the viewport for the scene when it is resized. */
void resize(int w, int h)
{
   /* We update the projections and the modeling matrices! */
	glViewport(0, 0, w, h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	if(projection==0) glOrtho(-40.0, 40.0, -40.0, 40.0, -80, 80);
   	else glFrustum(-2.7, 2.7, -2.7, 2.7, 2.0, 70.0);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - ' ' keys */
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
		
		case ' ':
		
		/* The key is ' ', thus we change the projection of interest! */
		projection=(projection+1)%2;
		resize(500,500);
		glutInitWindowSize(500,500);
		glutPostRedisplay();
		break;

		default:

    	/* Other keys are not important for us */
    	break;
	}
}

/// This function draws the 3D cube by using the projection (requested by the user) in the OpenGL scene of interest.
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
		cout<<"\tDrawn the 3D cube of interest by using the perspective projection (see the 'glFrustum()' function)"<<endl;
		cout.flush();
	}
	else
	{
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
		cout<<"\tDrawn the 3D cube of interest by using the orthogonal projection (see the 'glOrtho()' function)"<<endl;
		cout.flush();
	}
}
