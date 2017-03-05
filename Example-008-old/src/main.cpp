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
 * main.cpp - the main function for the 'Example-008 (Old Mode)' example
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
int choice;
bool eol=false;

/// The main function for the <i>'Example-008 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(480,480);
	glutCreateWindow("The 'Example-008' Example, based on the (Old Mode) OpenGL");
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

/// This function draws 2 quadrilaterals in the OpenGL window of interest.
void draw()
{
	/* We draw 2 quadrilaterals in the OpenGL window of interest! */
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	if(choice==0)
	{
		glBegin(GL_POLYGON);
		glVertex3f(20,20,0);
		glVertex3f(80,20,0);
		glVertex3f(80,80,0);
		glVertex3f(20,80,0);
		glEnd();
	}
	else
	{
		glBegin(GL_POLYGON);
		glVertex3f(40,40,0);
		glVertex3f(60,40,0);
		glVertex3f(60,60,0);
		glVertex3f(40,60,0);
		glEnd();
	}
	
	/* Now, we draw the second quadrilateral! */
	glColor3f(0.0,0.0,1.0);
	if(choice==0)
	{
		glBegin(GL_POLYGON);
		glVertex3f(40,40,0);
		glVertex3f(60,40,0);
		glVertex3f(60,60,0);
		glVertex3f(40,60,0);
		glEnd();
	}
	else
	{
		glBegin(GL_POLYGON);
		glVertex3f(20,20,0);
		glVertex3f(80,20,0);
		glVertex3f(80,80,0);
		glVertex3f(20,80,0);
		glEnd();
	}
	
	/* If we arrive here, all is finished! */
	glFlush();
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	cout<<endl<<"\tThis is the 'Example-008' Example, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tTwo quadrilaterals with a not empty intersection are drawn, and their rendering order can be changed as follows:"<<endl<<endl;
	cout<<"\t\t-) The quadrilateral in 'red' is defined and rendered before in the code (inferior rendering level)."<<endl;
	cout<<"\t\t-) The quadrilateral in 'blue' is defined and rendered after in the code (superior rendering level)."<<endl<<endl;
	cout<<"\tThe rendering order of these quadrilaterals, corresponding to two configurations, can be changed by pressing the '0' and '1' keys."<<endl<<endl;
	cout<<"\tIt is possible to end this program by pressing one among the 'Q' - 'q' - 'Esc' keys."<<endl<<endl;
	cout.flush();
	choice=0;
	glClearColor(1.0, 1.0, 1.0, 0.0);
	eol=false;
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '0' - '1' keys */
	switch (key)
	{
		case 'q':
	
		/* The key is 'q' */
		if(eol) cout<<endl;
		exit(EXIT_SUCCESS);
		break;
		
		case 'Q':
	
		/* The key is 'Q' */
		if(eol) cout<<endl;
		exit(EXIT_SUCCESS);
		break;
		
		case 27:
	
		/* The key is 'Esc' */
		if(eol) cout<<endl;
		exit(EXIT_SUCCESS);
		break;
		
		case '0':
		
		/* The key is '0' */
		choice=0;
		cout<<"\tDrawing the rendering configuration #0."<<endl;
		cout.flush();
		eol=true;
		glutPostRedisplay();
		break;
		
		case '1':
		
		/* The key is '1' */
		choice=1;
		cout<<"\tDrawing the rendering configuration #1."<<endl;
		cout.flush();
		eol=true;
		glutPostRedisplay();
		break;
		
		default:

    	/* Other keys are not important for us */
    	break;
	}
}
