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
 * main.cpp - the main function for the 'Example-029 (Old Mode)' example.
 *******************************************************************************************************************************************************/

/* First, we must understand which platform we are using. */
#include <cstdlib>
#include <iostream>
#include <cmath>
#define PI 3.14159265358979324
using namespace std;
#ifdef __APPLE__

	/* We are using a MacOSX platform (Macintosh). */
	#include "GL/glew.h"
	#include "GLUT/glut.h"
	#include "OpenGL/gl.h"

#else

	/* We are not using a MacOSX platform. Thus, we have a generic Unix-like platform, like the GNU Linux, or a Microsoft Windows platform. */
	#include "GL/glew.h"
	#include "GL/glut.h"
	#include "GL/gl.h"

#endif

/// The number of the samples, used for approximating the <i>'Lissajous-like'</i> curve of interest.
unsigned int num_samples;

/// The coefficients 'kx' and 'ky' for the equations, describing the custom <i>'Lissajous-like'</i> curve of interest.
int kx,ky;

/// The coefficients 'rx' and 'ry' for the equations, describing the custom <i>'Lissajous-like'</i> curve of interest.
float rx,ry;

/* Prototypes for all functions of interest! */
void draw();
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);

/// The main function for the <i>'Example-029 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-029' Example, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws a polyline (formed by an arbitrary number of samples), which approximates a custom version of the 'Lissajous-like' curve, defined as follows:"<<endl<<endl;
	cout<<"\tx(t) = Rx * cos( Kx * t)"<<endl;
	cout<<"\ty(t) = Ry * sin( Ky * t)"<<endl<<endl;
	cout<<"\twith 't' belonging to [0,"<<(2*PI)<<"] and 'Kx'>0, 'Ky'>0, 'Rx'>0, 'Ry'>0."<<endl;
	cout<<"\tThe coefficients 'Kx', 'Ky', 'Rx', and 'Ry' are specified by the user, which can also:"<<endl<<endl;
	cout<<"\t\t-) increase the number of the samples for the polyline of interest by pressing the '+' key;"<<endl;
	cout<<"\t\t-) decrease the number of the samples for the polyline of interest by pressing the '-' key."<<endl<<endl;
	cout<<"\tIt is possible to end this program by pressing one among the 'Q' - 'q' - 'Esc' keys."<<endl<<endl;
	cout<<"\tPlease, insert the coefficient 'Rx' (positive and not null) for the custom 'Lissajous-like' curve of interest: ";
	cout.flush();
	cin>>rx;
	if( (!cin) || (rx<=0) )
	{
		cout<<"\tPLEASE, INSERT A VALID VALUE FOR THE COEFFICIENT 'RX' IN THE CUSTOM 'LISSAJOUS-LIKE' CURVE OF INTEREST. THIS PROGRAM IS CLOSING ..."<<endl<<endl;
		cout.flush();
		return EXIT_FAILURE;
	}
	
	/* Now, we read the coefficient 'Ry' (positive and not null) for the custom 'Lissajous-like' curve of interest. */
	cout<<"\tPlease, insert the coefficient 'Ry' (positive and not null) for the custom 'Lissajous-like' curve of interest: ";
	cout.flush();
	cin>>ry;
	if( (!cin) || (ry<=0) )
	{
		cout<<"\tPLEASE, INSERT A VALID VALUE FOR THE COEFFICIENT 'RY' IN THE CUSTOM 'LISSAJOUS-LIKE' CURVE OF INTEREST. THIS PROGRAM IS CLOSING ..."<<endl<<endl;
		cout.flush();
		return EXIT_FAILURE;
	}
	
	/* Now, we read the coefficient 'Kx' (positive and not null) for the custom 'Lissajous-like' curve of interest. */
	cout<<"\tPlease, insert the coefficient 'Kx' (positive and not null) for the custom 'Lissajous-like' curve of interest: ";
	cout.flush();
	cin>>kx;
	if( (!cin) || (kx<=0) )
	{
		cout<<"\tPLEASE, INSERT A VALID VALUE FOR THE COEFFICIENT 'KX' IN THE CUSTOM 'LISSAJOUS-LIKE' CURVE OF INTEREST. THIS PROGRAM IS CLOSING ..."<<endl<<endl;
		cout.flush();
		return EXIT_FAILURE;
	}
	
	/* Now, we read the coefficient 'Ky' (positive and not null) for the custom 'Lissajous-like' curve of interest. */
	cout<<"\tPlease, insert the coefficient 'Ky' (positive and not null) for the custom 'Lissajous-like' curve of interest: ";
	cout.flush();
	cin>>ky;
	if( (!cin) || (ky<=0) )
	{
		cout<<"\tPLEASE, INSERT A VALID VALUE FOR THE COEFFICIENT 'KY' IN THE CUSTOM 'LISSAJOUS-LIKE' CURVE OF INTEREST. THIS PROGRAM IS CLOSING ..."<<endl<<endl;
		cout.flush();
		return EXIT_FAILURE;
	}
	
	/* If we arrive here, we can draw our 'Lissajous-like' curve! */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	if(rx==ry) glutInitWindowSize(500,500);
	else if(rx>ry) { glutInitWindowSize(1000,1000*ry/rx); }
	else { glutInitWindowSize(1000*rx/ry,1000); }
	glutCreateWindow("The 'Example-029' Example, based on the (Old Mode) OpenGL");
	glutReshapeFunc(resize);
	glutKeyboardFunc(manageKeys);
	glutDisplayFunc(draw);
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
   	glOrtho(-1.1*rx,1.1*rx,-1.1*ry,1.1*ry,-1,1);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	num_samples=5;
	cout<<endl<<"\tWe draw a polyline, initially formed by "<<num_samples<<" samples (the minimum number as possible), for approximating the custom 'Lissajous-like' curve of interest."<<endl<<endl;
	cout.flush();
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '+' - '-' keys */
	switch (key)
	{
		case 'q':
	
		/* The key is 'q', thus we can exit from this program. */
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case 'Q':
	
		/* The key is 'Q', thus we can exit from this program. */
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case 27:
	
		/* The key is 'Esc', thus we can exit from this program. */
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case '+':
		
		/* The key is '+', thus we increase the number of the samples in the polyline of interest! */
		num_samples=num_samples+1;
		glutPostRedisplay();
		break;
		
		case '-':
		
		/* The key is '-', thus we decrease the number of the samples (if possible) in the polyline of interest. */
		if(num_samples>5) num_samples=num_samples-1;
		else cout<<"\tThe minimum number 5 of samples is reached, and it is not possible to decrease again this number."<<endl;
		cout.flush();
		glutPostRedisplay();
		break;
	
		default:

    	/* Other keys are not important for us */
    	break;
	}
}

/// This function draws the polyline, approximating the custom <i>'Lissajous-like'</i> curve of interest, in the main OpenGL window.
void draw()
{
	float d,t;

	/* We draw the polyline, approximating the custom 'Lissajous-like' curve of interest, in the main OpenGL window. */
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.1,0.0,1.0);
	glLineWidth(2);
	d=(2*PI)/(num_samples-1);
	t=0.0;
	glBegin(GL_LINE_STRIP);
	for(int k=0;k<num_samples;k++)
	{
		t=k*d;
		glVertex3f(rx*cos(kx*t),ry*sin(ky*t),0);
	}
	
	/* If we arrive here, we have drawn everything! */
	glEnd();
	glFlush();
	cout<<"\tApproximated and drawn the custom 'Lissajous-like' curve of interest by using a polyline with "<<num_samples<<" samples."<<endl;
	cout.flush();
}
