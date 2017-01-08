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
 * main.cpp - the main function for the 'Example-024 (Old Mode)' example
 *******************************************************************************************************************************************************/

/* First, we must understand which platform we are using. */
#include <cstdlib>
#include <iostream>
#include <cmath>
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

/// The coordinates for the center of the circular annulus of interest.
float xc,yc;

/// The radius of the external circle in the circular annulus of interest.
float radiusE;

/// The radius of the internal circle in the circular annulus of interest.
float radiusI;

/// The number of the samples, used for drawing the circular annulus of interest.
unsigned int num_samples;

/// The rendering choice for the circular annulus of interest.
char choice;

/* Prototypes for all functions of interest! */
void draw();
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);

/// The main function for the <i>'Example-024 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-024' Example, based on the (Old Mode) OpenGL"<<endl<<endl;
	cout.flush();
	cout<<"\tPlease, insert the radius 'rE' (positive and not null) for the external circle in the circular annulus of interest: ";
	cin>>radiusE;
	if( (!cin) || (radiusE<=0) )
	{
		cout<<"\tPLEASE, INSERT A VALID VALUE FOR THE RADIUS OF THE EXTERNAL CIRCLE IN THE CIRCULAR ANNULUS OF INTEREST. THIS PROGRAM IS CLOSING..."<<endl<<endl;
		cout.flush();
		return EXIT_FAILURE;
	}
	
	/* Now, we read the radius 'rI' for the internal circle in the circular annulus of interest. */ 
	cout<<"\tPlease, insert the radius 'rI' (positive and not null) for the internal circle in the circular annulus of interest, it must be less than "<<radiusE<<": ";
	cin>>radiusI;
	if( (!cin) || (radiusI<=0) || (radiusI>=radiusE) )
	{
		cout<<"\tPLEASE, INSERT A VALID VALUE FOR THE RADIUS OF THE INTERNAL CIRCLE IN THE CIRCULAR ANNULUS OF INTEREST. THIS PROGRAM IS CLOSING..."<<endl<<endl;
		cout.flush();
		return EXIT_FAILURE;
	}
	
	/* Now, we read the coordinates of the center for the circular annulus of interest! */
	cout<<"\tPlease, insert the coordinates (xc,yc) of the center for the circular annulus of interest: ";
	cout.flush();
	cin>>xc>>yc;
	if(!cin)
	{
		cout<<"\tPLEASE, INSERT THE COORDINATES (xc,yc) OF THE CENTER FOR THE CIRCULAR ANNULUS OF INTEREST. THIS PROGRAM IS CLOSING..."<<endl<<endl;
		cout.flush();
		return EXIT_FAILURE;
	}
	
	/* If we arrive here, we can draw our circular annulus! */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-024' Example, based on the (Old Mode) OpenGL");
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
void initialize() 
{
	/* We initialize the OpenGL window of interest! */	
	cout<<endl<<"\tWe draw a circular annulus having center ("<<xc<<","<<yc<<"), internal radius 'rI'="<<radiusI<<", and external radius 'rE'="<<radiusE<<endl<<endl;
	cout.flush();
	glClearColor(1.0, 1.0, 1.0, 0.0);
	num_samples=3;
	choice='l';
}

/// This function updates the viewport for the scene when it is resized. */
void resize(int w, int h)
{
	/* We update the projections and the modeling matrices! */
	glViewport(0, 0, w, h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glOrtho(xc-1.1*radiusE,xc+1.1*radiusE,yc-1.1*radiusE,yc+1.1*radiusE,-1,1);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '+' - '-' - 'l' - 'f' - 'p' keys */
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
		
		case '+':
		
		/* The key is '+', thus we increase the number of the samples! */
		num_samples=num_samples+1;
		glutPostRedisplay();
		break;
		
		case '-':
		
		/* The key is '-', thus we decrease the number of the samples! */
		if(num_samples>3) num_samples=num_samples-1;
		else cout<<"\tThe minimum number 3 of samples is reached"<<endl;
		cout.flush();
		glutPostRedisplay();
		break;
		
		case 'l':
		
		/* The key is 'l', thus we choose to render only the polyline */
		choice='l';
		glutPostRedisplay();
		break;
		
		case 'f':
		
		/* The key is 'f', thus we choose to render only the filled quad strip */
		choice='f';
		glutPostRedisplay();
		break;
		
		case 'p':
		
		/* The key is 'p', thus we choose to render only the points */
		choice='p';
		glutPostRedisplay();
		break;

		default:

    	/* Other keys are not important for us */
    	break;
	}
}

/// This function draws the quad strip, describing the circular annulus, in the OpenGL window of interest.
void draw()
{
	float t;

	/* We draw the quad strip, describing the circular annulus, in the OpenGL window of interest. */
	t=0;
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(3);
	glLineWidth(3);
	glColor3f(1.0,0.0,0.0);
	if(choice=='l') glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	if(choice=='f') glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	if(choice=='p') glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
	glBegin(GL_QUAD_STRIP);
	for(unsigned int i=0;i<=num_samples;i++)
	{
		glVertex3f(xc+radiusI*cos(t),yc+radiusI*sin(t),0);
		glVertex3f(xc+radiusE*cos(t),yc+radiusE*sin(t),0);
		t=t+(2*PI/num_samples);
	}
	
	/* If we arrive here, all is ok */
	glEnd();
	glFlush();
	glFlush();
    if(choice=='l') cout<<"\tApproximated and drawn the circular annulus of interest (polyline) with "<<num_samples<<" samples"<<endl;
    if(choice=='f') cout<<"\tApproximated and drawn the circular annulus of interest (filled quad strip) with "<<num_samples<<" samples"<<endl;
    if(choice=='p') cout<<"\tApproximated and drawn the circular annulus of interest (points) with "<<num_samples<<" samples"<<endl;
	cout.flush();
}
