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
 * main.cpp - the main function for the 'Example-027 (Old Mode)' example.
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

/// The number of the samples, used for approximating the <i>'Sine-like'</i> curve of interest.
unsigned int num_samples;

/// The custom exponent to be used for defining and drawing the <i>'Sine-like'</i> curve of interest.
int ee;

/* Prototypes for all functions of interest! */
void draw();
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);

/// The main function for the <i>'Example-027 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-027' Example, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws a polyline (formed by an arbitrary number of samples), which approximates a 'Sine-like' curve, defined in the ["<<-PI<<",+"<<PI<<"] range."<<endl;
	cout<<"\tIn particular, a 'Sine-like' curve is defined in the same spirit of the 'Sine' curve, but it requires an exponent 'n' for computing the sine function to the 'n'-th."<<endl;
	cout<<"\tThe exponent 'n' is specified by the user, which can also:"<<endl<<endl;
	cout<<"\t\t-) increase the number of the samples for the polyline of interest by pressing the '+' key;"<<endl;
	cout<<"\t\t-) decrease the number of the samples for the polyline of interest by pressing the '-' key."<<endl<<endl;
	cout<<"\tIt is possible to end this program by pressing one among the 'Q' - 'q' - 'Esc' keys."<<endl<<endl;
	cout.flush();
	
	/* Now, we read the exponent 'n' for the 'Sine-like' curve of interest. */
	cout<<"\tPlease, insert the exponent 'n' (positive and not null) for the 'Sine-like' curve of interest: ";
	cin>>ee;
	if( (!cin) || (ee<=0) )
	{
		cout<<"\tPLEASE, INSERT A VALID VALUE FOR THE EXPONENT 'N' IN THE 'SINE-LIKE' CURVE OF INTEREST. THIS PROGRAM IS CLOSING ..."<<endl<<endl;
		cout.flush();
		return EXIT_FAILURE;
	}

	/* If we arrive here, we can draw our 'Sine-like' curve. */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	if(ee%2==0) glutInitWindowSize(600,600/(2*PI));
	else glutInitWindowSize(600,2*600/(2*PI));
	glutCreateWindow("The 'Example-027' Example, based on the (Old Mode) OpenGL");
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
   	if(ee%2==0) glOrtho(-PI-0.1,+PI+0.1,-0.1,1.1,-1,1);
   	else glOrtho(-PI-0.1,+PI+0.1,-1.1,1.1,-1,1);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function draws the polyline, approximating the <i>'Sine-like'</i> curve of interest, in the main OpenGL window.
void draw()
{
	float d,t;
	
	/* We draw the polyline, approximating the 'Sine-like' curve of interest, in the main OpenGL window.*/
	d=(2*PI/(num_samples-1));
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINE_STRIP);
	for(unsigned int i=0;i<=num_samples;i++)
	{
		t=-PI+i*d;
		glVertex3f(t,pow(sin(t),ee),0);
	}
	
	/* If we arrive here, all is ok */
	glEnd();
	glFlush();
	cout<<"\tApproximated and drawn the 'Sine-like' curve of interest by using a polyline with "<<num_samples<<" samples."<<endl;
	cout.flush();
}

/// This function initializes the main OpenGL window.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	num_samples=5;
	cout<<endl<<"\tWe draw a polyline, initially formed by "<<num_samples<<" samples (the minimum number as possible), for approximating the 'Sine-like' curve with exponent 'n'="<<ee<<" in the [-"<<PI<<","<<PI<<"] range."<<endl<<endl;
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
		if(num_samples>5) num_samples=num_samples-1;
		else cout<<"\tThe minimum number 5 of samples is reached, and it is not possible to decrease again this number."<<endl;
		cout.flush();
		glutPostRedisplay();
		break;

		default:

    	/* Other keys are not important for us! */
    	break;
	}
}
