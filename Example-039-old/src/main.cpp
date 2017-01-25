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
 * main.cpp - the main function for the 'Example-039 (Old Mode)' example
 *******************************************************************************************************************************************************/

/* First, we must understand which platform we are using. */
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <string>
#include <cfloat>
#define PI 3.14159265358979324
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

/// The number of the samples, used for drawing the scene of interest.
int num_samples=5;

/// The rendering mode for the scene of interest (wireframe or filled).
GLenum mode=GL_FILL;

/// This flag indicates what projection must be used (ortographic or perspective).
int projection=0;

/// This flag indicates how placing the <i>'Ring'</i> shape in the scene (3 possible configurations).
int configuration=0;

/* Prototypes for all functions of interest! */
void initialize();
void manageKeys(unsigned char key, int x, int y);
void draw();
void resize(int w,int h);

/// The main function for the <i>'Example-039 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a new window! */
	cout<<endl<<"\tThis is the 'Example-039' Example, based on the (Old Mode) OpenGL"<<endl<<endl;
	cout.flush();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(600,600);
	glutCreateWindow("The 'Example-039' Example, based on the (Old Mode) OpenGL");
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
	cout<<"\tWe draw the 'Ring' shape of interest in the scene. Specifically, it is possible to modify:"<<endl<<endl;
	cout<<"\t-) the number of the samples by pressing the '+' and '-' keys"<<endl;
	cout<<"\t-) the rendering mode for the scene of interest (filled or wireframe) by pressing the 'r' key"<<endl;
	cout<<"\t-) the projection technique for the scene of interest (orthographic or perspective) by pressing the ' ' key"<<endl;
	cout<<"\t-) the placement of the 'Ring' shape (3 possible placements) by pressing the 'c' key"<<endl<<endl;
	cout.flush();
	glClearColor(1.0, 1.0, 1.0, 0.0);
	num_samples=5;
	mode=GL_FILL;
	projection=0;
	configuration=0;
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '+' - '-' - '<space bar>' -'r' keys */
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
		
		case '+':
		
		/* The key is '+', thus we increase the number of the samples! */
		num_samples=num_samples+1;
		glutPostRedisplay();
		break;
		
		case '-':
		
		/* The key is '-', thus we decrease the number of the samples! */
		if(num_samples>5) num_samples=num_samples-1;
		else cout<<"\tThe minimum number 5 of samples is reached"<<endl;
		cout.flush();
		glutPostRedisplay();
		break;
		
		case 'r':
		
		/* The key is 'r', thus we change the rendering mode to be used! */
		if(mode==GL_FILL) mode=GL_LINE;
		else mode=GL_FILL;
		glutPostRedisplay();
		break;
		
		case 'c':
		
		/* The key is 'c', thus we change the placement of the 'Ring' shape in the scene (3 possible configurations). */
		configuration=(configuration+1)%3;
		resize(600,600);
		glutInitWindowSize(600,600);
		glutPostRedisplay();
		break;
		
		case ' ':
		
		/* The key is ' ', thus we change the projection. */
		projection=(projection+1)%2;
		resize(600,600);
		glutInitWindowSize(600,600);
		glutPostRedisplay();
		break;
		
		default:

    	/* Other keys are not important for us */
    	break;
	}
}

/// This function updates the viewport for the scene when it is resized. */
void resize(int w, int h)
{
	/* We update the projections and the modeling matrices! */
	glViewport(0, 0, w, h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	if(projection==1) { glFrustum(-20,20,-20,20,4,180); }
   	else if(configuration==0) { glOrtho(-45,45,-10,80,105,25); }
   	else if(configuration==1) { glOrtho(-10,80,-45,45,105,25); }
   	else { glOrtho(-45,45,-45,45,105,25); }
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function draws the <i>'Ring'</i> shape in the OpenGL window of interest by using the preferences, chosen by the user.
void draw()
{
	float d=(2*PI)/(num_samples-1);

	/* Now, we draw the 'Ring' shape of interest in the OpenGL window of interest by using the preferences, chosen by the user. */
	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK,mode);
	glColor3f(1,0,0);
	glLineWidth(1);
	glBegin(GL_QUAD_STRIP);
	if(configuration==0)
	{
		/* The domain for the configuration #0 is [-35,35] x [0,70] x [-95,-25]. */
		for(int k=0;k<num_samples;k++) 
		{ 
			glVertex3f(35*cos(-PI+k*d),0,35*sin(-PI+k*d)-60); 
			glVertex3f(35*cos(-PI+k*d),70,35*sin(-PI+k*d)-60);
		}
	}
	else if(configuration==1)
	{
		/* The domain for the configuration #1 is [0,70] x [-35,35] x [-95,-25]. */
		for(int k=0;k<num_samples;k++)
		{
			glVertex3f(0,35*sin(-PI+k*d),35*cos(-PI+k*d)-60);
			glVertex3f(70,35*sin(-PI+k*d),35*cos(-PI+k*d)-60);
		}
	}
	else
	{
		/* The domain for the configuration #2 is [-35,35] x [-35,35] x [-95,-25] */
		for(int k=0;k<num_samples;k++)
		{
			glVertex3f(35*cos(-PI+k*d),35*sin(-PI+k*d),-95);
			glVertex3f(35*cos(-PI+k*d),35*sin(-PI+k*d),-25);
		}
	}
	
	/* If we arrive here, the scene is complete! */
	glEnd();
	glFlush();
	cout<<"\tApproximated the ";
	if(mode==GL_FILL) cout<<"filled ";
	else cout<<"wired ";
	cout<<"configuration #"<<configuration<<" of the 'Ring' shape in the scene by using "<<num_samples<<" samples and the ";
	if(projection==0) cout<<"ortographic ";
	else cout<<"perspective ";
	cout<<"projection"<<endl;
	cout.flush();
}
