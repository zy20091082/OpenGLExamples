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
 * main.cpp - the main function for the 'Example-018 (Old Mode)' example
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
int iconvex;
int inconvex;
float convex_points[][3]={
			{ 20.0,20.0,0.0},
			{ 50,20,0 },
			{ 80,50,0 },
			{ 80,80,0 },
			{ 20,80,0 }
	};
float not_convex_points[][3]={
			{20,120,0},
			{80,120,0},
			{40,140,0},
			{20,180,0}
};

/// The main function for the <i>'Example-018 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(600,600);
	glutCreateWindow("The 'Example-018' Example, based on the (Old Mode) OpenGL");
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
   	glOrtho(0,200,0,200,-1,1);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function draws several polygons in the OpenGL window of interest.
void draw()
{
	int pp,jj;

	/* We draw several polygons in the OpenGL window of interest. */
	pp = (iconvex%5);
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(10.0);
	glLineWidth(2.0);
	glColor3f(1.0,0.0,0.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_POLYGON);
   	for(int k=0;k<5;k++) 
   	{ 
   		jj=(k+pp)%5;
   		glVertex3f(convex_points[jj][0],convex_points[jj][1],convex_points[jj][2]);
   	}
   	
   	/* Convex polygon (wireframe) */
   	glEnd();
   	glColor3f(1.0,0.0,0.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glBegin(GL_POLYGON);
	for(int k=0;k<5;k++) 
   	{ 
   		jj=(k+pp)%5;
   		glVertex3f(convex_points[jj][0]+100,convex_points[jj][1],convex_points[jj][2]);
   	}
   	
   	/* Not-Convex polygon (filled) */
	glEnd();
	glColor3f(0.0,0.0,1.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_POLYGON);
	for(int k=0;k<4;k++) 
   	{ 
   		jj=(k+pp)%4;
   		glVertex3f(not_convex_points[jj][0],not_convex_points[jj][1],not_convex_points[jj][2]);
   	}
	
	/* Not-Convex polygon (wireframe) */
	glEnd();
	glColor3f(0.0,0.0,1.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	pp=(inconvex%4);
	glBegin(GL_POLYGON);
	for(int k=0;k<4;k++) 
   	{ 
   		jj=(k+pp)%4;
   		glVertex3f(not_convex_points[jj][0]+100,not_convex_points[jj][1],not_convex_points[jj][2]);
   	}
	
	/* If we arrive here, all is ok! */
	glEnd();
	glFlush();
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	cout<<endl<<"\tThis is the 'Example-018' Example, based on the (Old Mode) OpenGL"<<endl<<endl;
	cout<<"\tDrawing several convex and not-convex polygons under several polygon face and mode renderings."<<endl;
	cout<<"\tIf we cycle over the order of their vertices (by pressing the '+' key), then there will be 'strange' situations when rendering not-convex polygons (GL_FILL mode)"<<endl<<endl;
	cout.flush();
	glClearColor(1.0, 1.0, 1.0, 0.0);
	iconvex=0;
	inconvex=0;
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' keys */
	switch (key)
	{
		case 113:
	
		/* The key is 'q' */
		exit(EXIT_SUCCESS);
		break;
		
		case 81:
	
		/* The key is 'Q' */
		exit(EXIT_SUCCESS);
		break;
		
		case 27:
	
		/* The key is 'Esc' */
		exit(EXIT_SUCCESS);
		break;
		
		case 43:
		
		/* The key is '+' */
		iconvex=iconvex+1;
		inconvex=inconvex+1;
		glutPostRedisplay();		
		break;

		default:

    	/* Other keys are not important for us */
    	break;
	}
}