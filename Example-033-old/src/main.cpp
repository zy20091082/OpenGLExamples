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
 * main.cpp - the main function for the 'Example-033 (Old Mode)' example
 *******************************************************************************************************************************************************/

/* First, we must understand which platform we are using. */
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <string>
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

/// This flag indicates what spiral we must draw.
int orient=0;

/* Prototypes for all functions of interest! */
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);
void draw();

/// The main function for the <i>'Example-033 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a new window! */
	cout<<endl<<"\tThis is the 'Example-033' Example, based on the (Old Mode) OpenGL"<<endl<<endl;
	cout.flush();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-033' Example, based on the (Old Mode) OpenGL");
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
	cout<<"\tWe draw different orientations of the same spiral."<<endl<<endl;
	cout<<"\tIt is possible to modify the number of the samples (by pressing the '+' and '-' keys), as well as the orientation of interest (by pressing the ' ' key)."<<endl<<endl;
	glClearColor(1.0, 1.0, 1.0, 0.0);
	num_samples=5;
	orient=0;
}

/// This function updates the viewport for the scene when it is resized. */
void resize(int w, int h)
{
	/* We update the projections and the modeling matrices! */
	glViewport(0, 0, w, h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glOrtho(-50,50,-50,50,-50,50);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '+' - '-' - '<space bar>' keys */
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
		
		case ' ':
		
		/* The key is ' ', thus we change the orientation of interest! */
		orient=(orient+1)%3;
		num_samples=5;
		glutPostRedisplay();
		break;
		
		case '-':
		
		/* The key is '-', thus we decrease the number of the samples! */
		if(num_samples>5) num_samples=num_samples-1;
		else cout<<"\tThe minimum number 5 of samples is reached"<<endl;
		cout.flush();
		glutPostRedisplay();
		break;

		default:

    	/* Other keys are not important for us */
    	break;
	}
}

/// This function draws the orientation for the spiral (required by the user) in the OpenGL scene of interest.
void draw()
{
	/* Now, we draw the required orientation for the spiral in the OpenGL scene of interest. */
	float d=(20*PI)/(num_samples-1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,0,0);
	glBegin(GL_LINE_STRIP);
	if(orient==0)
	{
		/* Now, we must draw the configuration #0, such that the spiral evolves along the z-axis. */
		for(unsigned int k=0;k<num_samples;k++)
		{
			float t=-10*PI+k*d;
			glVertex3f(40*cos(t),40*sin(t),t);
		}
	}
	else if(orient==1)
	{
		/* Now, we must draw the configuration #1, such that the spiral evolves along the x-axis. */
		for(unsigned int k=0;k<num_samples;k++)
		{
			float t=-10*PI+k*d;
			glVertex3f(t,40*cos(t),40*sin(t));
		}
	}
	else
	{
		/* Now, we must draw the configuration #2, such that the spiral evolves along the y-axis. */
		for(unsigned int k=0;k<num_samples;k++)
		{
			float t=-10*PI+k*d;
			glVertex3f(40*cos(t),t,40*sin(t));
		}
	}
	
	/* If we arrive here, we have finished! */
	glEnd();
	glFlush();
	cout<<"\tApproximated and drawn the configuration #"<<orient<<" for the spiral of interest with "<<num_samples<<" samples by using the ortographic projection."<<endl;
	cout.flush();
}
