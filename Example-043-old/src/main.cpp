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
 * main.cpp - the main function for the 'Example-043 (Old Mode)' example
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

/// The coordinates for the center of the 'Sphere' shape.
float Xvalue=0.0,Yvalue=0.0;

/// The rotation angle for the 'Sphere' shape.
float Angle=0.0;

/* Prototypes for all functions of interest! */
void initialize();
void manageKeys(unsigned char key, int x, int y);
void manageSpecialKeys(int key,int x,int y);
void draw();
void resize(int w,int h);

/// The main function for the <i>'Example-043 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a new window! */
	cout<<endl<<"\tThis is the 'Example-043' Example, based on the (Old Mode) OpenGL"<<endl<<endl;
	cout.flush();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-043' Example, based on the (Old Mode) OpenGL");
	glutReshapeFunc(resize);
	glutKeyboardFunc(manageKeys);
	glutSpecialFunc(manageSpecialKeys);
	glutDisplayFunc(draw);
	glewExperimental = GL_TRUE;
   	glewInit();
   	initialize(); 
	glutMainLoop();
	return EXIT_SUCCESS;
}

/// This function draws the <i>'Sphere'</i> shape in the OpenGL window of interest by using the preferences, chosen by the user.
void draw()
{
	/* Now, we draw the 'Sphere' shape in the OpenGL window of interest by using the preferences, chosen by the user. */
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
   	glTranslatef(Xvalue, Yvalue, -5.0);
   	glRotatef(Angle, 1.0, 1.0, 1.0);
   	glColor3f(0,0,1);
   	glutWireSphere(0.5, 16, 10);
   	glutSwapBuffers();
   	cout<<"\tDrawn the 'Sphere' shape by exploiting the rotation angle: "<<Angle<<", the translation value along the x-axis: "<<Xvalue<<", and the translation value along the y-axis: "<<Yvalue<<endl;
   	cout.flush();
}

/// This function updates the viewport for the scene when it is resized. */
void resize(int w, int h)
{
	/* We update only the projection matrix! */
	glViewport(0, 0, w, h); 
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	Xvalue=0.0;
	Yvalue=0.0;
	Angle=0.0;
	cout<<"\tWe draw the wireframe version of a sphere. It is possible to:"<<endl<<endl;
	cout<<"\t-) rotate the sphere by pressing the ' ' (space) key"<<endl;
	cout<<"\t-) translate the center of the sphere along the two directions of the x-axis by pressing the 'left' and the 'right' arrows"<<endl;
	cout<<"\t-) translate the center of the sphere along the two directions of the y-axis by pressing the 'up' and the 'down' arrows"<<endl;
	cout<<"\t-) reset all transformations by pressing the 'r' key"<<endl<<endl;
	cout.flush();
}

/// This function is the keyboard input processing routine for the OpenGL window of interest (non-ASCII keys).
void manageSpecialKeys(int key, int x, int y)
{
	/* We are interested only in the 'up' - 'down' - 'left' - 'right' arrows. */
	switch(key)
	{
		case GLUT_KEY_UP:
		
		/* The special key is the 'up' arrow. Thus, we increase the 'Yvalue' translation value (towards the positive y-values) and redraw the scene. */
		Yvalue+=0.1;
		glutPostRedisplay();
		break;
			
		case GLUT_KEY_DOWN:
		
		/* The special key is the 'down' arrow. Thus, we decrease the 'Yvalue' translation value (towards the negative y-values) and redraw the scene. */
		Yvalue-=0.1;
		glutPostRedisplay();
		break;
			
		case GLUT_KEY_LEFT:
		
		/* The special key is the 'left' arrow. Thus, we decrease the 'Xvalue' translation value (towards the negative x-values) and redraw the scene  */
		Xvalue-=0.1;
		glutPostRedisplay();
		break;
			
		case GLUT_KEY_RIGHT:
		
		/* The special key is the 'right' arrow. Thus, we increase the 'Xvalue' translation value (towards the positive x-values) and redraw the scene. */
		Xvalue+=0.1;
		glutPostRedisplay();
		break;
		
		default:
		
		/* Other keys are not important for us */
		break;
	}
}

/// This function is the keyboard input processing routine for the OpenGL window of interest (ASCII keys).
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - 'r' - ' ' (space) keys */
	switch (key)
	{
		case 27:
	
		/* The key is 'Esc', thus we close the program. */
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case 'q':
		
		/* The key is 'q', thus we close the program. */
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case 'Q':
	
		/* The key is 'Q', thus we close the program. */
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case 'r':
		
		/* The key is 'r', thus we reset the rotation angle and the translations. */
		Xvalue=0;
		Yvalue=0;
		Angle=0;
		glutPostRedisplay();
		break;
		
		case ' ':
		
		/* The key is ' ' (space), thus we increase the rotation angle. */
		Angle+=10.0;
		glutPostRedisplay();
		break;
		
		default:
		
		/* Other keys are not important for us */
		break;
	}
}
