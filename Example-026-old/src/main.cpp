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
 * main.cpp - the main function for the 'Example-026 (Old Mode)' example.
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

/// The center coordinates <i>'(xc,yc)'</i> for the <i>'Ellipse-like'</i> curve of interest.
float xc,yc;

/// The lengths <i>'Rx'</i> and <i>'Ry'</i> of the semi-axis for the <i>'Ellipse-like'</i> curve of interest.
float radius_x,radius_y;

/// The number of the samples, used for approximating the <i>'Ellipse-like'</i> curve of interest.
unsigned int num_samples;

/// The custom exponent to be used in the functions, used for defining and drawing the <i>'Ellipse-like'</i> curve of interest.
int ee;

/* Prototypes for all functions of interest! */
void draw();
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);

/// The main function for the <i>'Example-026 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-026' Example, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws a polyline (formed by an arbitrary number of samples), which approximates an 'Ellipse-like' curve with semiaxis 'Rx' and 'Ry' (respectively along the x- and the y-axis), and center '(xc,yc)'."<<endl;
	cout<<"\tIn particular, an 'Ellipse-like' curve is defined in the same spirit of the 'Ellipse' curve, but it requires an exponent 'n' for computing the cosine and the sine functions to the 'n'-th."<<endl;
	cout<<"\tThe semiaxis 'Rx' and 'Ry', as well as the center coodinates '(xc,yc)' and the exponent 'n', are specified by the user, which can also:"<<endl<<endl;
	cout<<"\t\t-) increase the number of the samples for the polyline of interest by pressing the '+' key;"<<endl;
	cout<<"\t\t-) decrease the number of the samples for the polyline of interest by pressing the '-' key."<<endl<<endl;
	cout<<"\tIt is possible to end this program by pressing one among the 'Q' - 'q' - 'Esc' keys."<<endl<<endl;
	cout.flush();
	cout<<"\tPlease, insert the semi-axis 'Rx' along the x-axis (positive and not null) for the 'Ellipse-like' curve of interest: ";
	cin>>radius_x;
	if( (!cin) || (radius_x<=0) )
	{
		cout<<"\tPLEASE, INSERT A VALID VALUE FOR THE SEMI-AXIS 'Rx' IN THE 'ELLIPSE-LIKE' CURVE OF INTEREST. THIS PROGRAM IS CLOSING ..."<<endl<<endl;
		cout.flush();
		return EXIT_FAILURE;
	}
	
	/* Now, we read the length of the second semi-axis for the 'Ellipse-like' curve of interest. */
	cout<<"\tPlease, insert the semi-axis 'Ry' along the y-axis (positive and not null) for the 'Ellipse-like' curve of interest: ";
	cin>>radius_y;
	if( (!cin) || (radius_y<=0) )
	{
		cout<<"\tPLEASE, INSERT A VALID VALUE FOR THE SEMI-AXIS 'Ry' IN THE 'ELLIPSE-LIKE' CURVE OF INTEREST. THIS PROGRAM IS CLOSING ..."<<endl<<endl;
		cout.flush();
		return EXIT_FAILURE;
	}
	
	/* Now, we read the center coordinates '(xc,yc)' for the 'Ellipse-like' curve of interest. */
	cout<<"\tPlease, insert the center coordinates '(xc,yc)' for the 'Ellipse-like' curve of interest (separated by a space): ";
	cout.flush();
	cin>>xc>>yc;
	if(!cin)
	{
		cout<<"\tPLEASE, INSERT THE CENTER COORDINATES '(xc,yc)' FOR THE 'ELLIPSE-LIKE' CURVE OF INTEREST. THIS PROGRAM IS CLOSING ..."<<endl<<endl;
		cout.flush();
		return EXIT_FAILURE;
	}
	
	/* Now, we read the exponent 'n' for drawing and defining the 'Ellipse-like' curve of interest. */
	cout<<"\tPlease, insert the exponent 'n' (positive and not null) for the the 'Ellipse-like' curve of interest: ";
	cin>>ee;
	if( (!cin) || (ee<=0) )
	{
		cout<<"\tPLEASE, INSERT A VALID VALUE FOR THE EXPONENT 'N' IN THE THE 'ELLIPSE-LIKE' CURVE OF INTEREST. THIS PROGRAM IS CLOSING ..."<<endl<<endl;
		cout.flush();
		return EXIT_FAILURE;
	}

	/* If we arrive here, we can draw our 'Ellipse-like' curve! */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	if(radius_x==radius_y) glutInitWindowSize(500,500);
	else if(radius_x>radius_y) { glutInitWindowSize(1000,1000*radius_y/radius_x); }
	else { glutInitWindowSize(1000*radius_x/radius_y,1000); }
	glutCreateWindow("The 'Example-026' Example, based on the (Old Mode) OpenGL");
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
   	glOrtho(xc-1.1*radius_x,xc+1.1*radius_x,yc-1.1*radius_y,yc+1.1*radius_y,-1,1);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	num_samples=3;
	cout<<endl<<"\tWe draw a polyline, initially formed by "<<num_samples<<" samples (the minimum number as possible), for approximating the 'Ellipse-like' curve of center ("<<xc<<","<<yc<<"), exponent 'n'="<<ee<<", semi-axis 'Rx'="<<radius_x<<" (along the ";
	cout<<"x-axis), and semi-axis 'Ry'="<<radius_y<<" (along the y axis)."<<endl<<endl;
	cout.flush();
}

/// This function draws the polyline, approximating the <i>'Ellipse-like'</i> curve of interest, in the main OpenGL window.
void draw()
{
	float t;
	
	/* We draw the polyline, approximating the 'Ellipse-like' curve of interest, in the main OpenGL window. */
	t=0;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINE_LOOP);
	for(unsigned int i=0;i<=num_samples;i++)
	{
		glVertex3f(xc+radius_x*pow(cos(t),ee),yc+radius_y*pow(sin(t),ee),0);
		t=t+(2*PI/num_samples);
	}
	
	/* If we arrive here, all is ok */
	glEnd();
	glFlush();
	cout<<"\tApproximated and drawn the 'Ellipse-like' curve of interest by using a polyline with "<<num_samples<<" samples."<<endl;
	cout.flush();
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '+' - '-' keys. */
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
		if(num_samples>3) num_samples=num_samples-1;
		else cout<<"\tThe minimum number 3 of samples is reached, and it is not possible to decrease again this number."<<endl;
		cout.flush();
		glutPostRedisplay();
		break;

		default:

    	/* Other keys are not important for us! */
    	break;
	}
}
