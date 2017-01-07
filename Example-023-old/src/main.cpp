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
 * main.cpp - the main function for the 'Example-023 (Old Mode)' example
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

/// The coordinates of the center for the ellipse of interest.
float xc,yc;

/// The lengths of the semi-axis for the ellipse of interest
float radius_x,radius_y;

/// The number of the samples, used for drawing the ellipse of interest.
unsigned int num_samples;

/* Prototypes for all functions of interest! */
void draw();
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);

/// The main function for the <i>'Example-023 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-023' Example, based on the (Old Mode) OpenGL"<<endl<<endl;
	cout.flush();
	cout<<"\tPlease, insert the length of the semi-axis 'Rx' along the x-axis (positive and not null) for the ellipse of interest: ";
	cin>>radius_x;
	if( (!cin) || (radius_x<=0) )
	{
		cout<<"\tPLEASE, INSERT A VALID VALUE FOR THE LENGTH OF THE SEMI-AXIS 'RX' IN THE ELLIPSE OF INTEREST. THIS PROGRAM IS CLOSING..."<<endl<<endl;
		cout.flush();
		return EXIT_FAILURE;
	}
	
	/* Now, we read the length of the second semi-axis */
	cout<<"\tPlease, insert the length of the semi-axis 'Ry' along the y-axis (positive and not null) for the ellipse of interest: ";
	cin>>radius_y;
	if( (!cin) || (radius_y<=0) )
	{
		cout<<"\tPLEASE, INSERT A VALID VALUE FOR THE LENGTH OF THE SEMI-AXIS 'RY' IN THE ELLIPSE OF INTEREST. THIS PROGRAM IS CLOSING..."<<endl<<endl;
		cout.flush();
		return EXIT_FAILURE;
	}
	
	/* Now, we read the coordinates for the center! */
	cout<<"\tPlease, insert the coordinates (xc,yc) of the center for the ellipse of interest: ";
	cout.flush();
	cin>>xc>>yc;
	if(!cin)
	{
		cout<<"\tPLEASE, INSERT THE COORDINATES (xc,yc) OF THE CENTER FOR THE ellipse OF INTEREST. THIS PROGRAM IS CLOSING..."<<endl<<endl;
		cout.flush();
		return EXIT_FAILURE;
	}
	
	/* If we arrive here, we can draw our ellipse! */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	if(radius_x==radius_y) glutInitWindowSize(500,500);
	else if(radius_x>radius_y) { glutInitWindowSize(1000,1000*radius_y/radius_x); }
	else { glutInitWindowSize(1000*radius_x/radius_y,1000); }
	glutCreateWindow("The 'Example-023' Example, based on the (Old Mode) OpenGL");
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
	cout<<endl<<"\tWe draw an ellipse, having center ("<<xc<<","<<yc<<"), semi-axis 'Rx'="<<radius_x<<" (along the x-axis), and semi-axis 'Ry'="<<radius_y<<" (along the y axis)"<<endl<<endl;
	cout.flush();
	glClearColor(1.0, 1.0, 1.0, 0.0);
	num_samples=3;
}

/// This function updates the viewport for the scene when it is resized. */
void resize(int w, int h)
{
	/* We update the projections and the modeling matrices! */
	glViewport(0, 0, w, h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glOrtho(xc-1.1*radius_x,xc+1.1*radius_x,yc-1.1*radius_y,yc+1.1*radius_y,-1,1);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '+' - '-' keys */
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

		default:

    	/* Other keys are not important for us */
    	break;
	}
}

/// This function draws the polyline, approximating the ellipse of interest, in the OpenGL window of interest.
void draw()
{
	float t;

	/* We draw the polyline, approximating the ellipse of interest. */
	t=0;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINE_LOOP);
	for(unsigned int i=0;i<=num_samples;i++)
	{
		glVertex3f(xc+radius_x*cos(t),yc+radius_y*sin(t),0);
		t=t+(2*PI/num_samples);
	}
	
	/* If we arrive here, all is ok */
	glEnd();
	glFlush();
	cout<<"\tApproximated and drawn the ellipse of interest with "<<num_samples<<" samples"<<endl;
	cout.flush();
}
