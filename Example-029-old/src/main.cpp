/*******************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 * 
 * Last update: April 2017
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

	/* We are not using a MacOSX platform. Thus, we have a generic Unix-like platform, like the GNU/Linux, or a Microsoft Windows platform. */
	#include "GL/glew.h"
	#include "GL/glut.h"
	#include "GL/gl.h"

#endif

/// The number of the vertices and edges in the polyline, used for approximating the <i>'Lissajous-like'</i> curve of interest.
/**
 * It is initially set to '7', which is the minimum number 'n' of vertices and edges. It is interactively modified by pressing the '+' and the '-' keys.
 */
unsigned int num_samples=7;

/// The coefficients <i>'Kx'</i> and <i>'Ky'</i> to be used for defining and drawing the polyline, approximating the <i>'Lissajous-like'</i> curve of interest.
/**
 * The <i>'Lissajous-like'</i> curve is defined as follows: x(t) = Rx * cos( Kx * t ), y(t) = Ry * sin( Ky * t ). The coefficients 'Kx' and 'Ky' must be positive and not null 'integer' values.
 */
int Kx,Ky;

/// The coefficients <i>'Rx'</i> and <i>'Ry'</i> to be used for defining and drawing the polyline, approximating the <i>'Lissajous-like'</i> curve of interest.
/**
 * The <i>'Lissajous-like'</i> curve is defined as follows: x(t) = Rx * cos( Kx * t ), y(t) = Ry * sin( Ky * t ). The coefficients 'Rx' and 'Ry' must be positive and not null 'integer' values.
 */
int Rx,Ry;

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
	cout<<"\tIt draws a polyline (in 'blue'), formed by an arbitrary number 'n' of vertices and edges, which approximates the 'Lissajous-like' curve with parameters 'Rx', 'Ry', 'Kx', and 'Ky'. This curve is defined as follows:"<<endl<<endl;
	cout<<"\tx(t) = Rx * cos( Kx * t ), y(t) = Ry * sin( Ky * t )"<<endl<<endl;
	cout<<"\tfor every 't' in '[0,2*pi]', and for any 'Kx'>0, 'Ky'>0, 'Rx'>0, 'Ry'>0. For the sake of the simplicity, the parameters 'Rx', 'Ry', 'Kx', and 'Ky' are positive and not null 'integer' values, and are provided ";
	cout<<"interactively by the user, which can also:"<<endl<<endl<<"\t\t-) increase the number 'n' of the vertices and edges for the polyline of interest by pressing the '+' key;"<<endl;
	cout<<"\t\t-) decrease the number 'n' of the vertices and edges for the polyline of interest by pressing the '-' key."<<endl<<endl;
	cout<<"\tIt is possible to end this program by pressing one among the 'Q' - 'q' - 'Esc' keys."<<endl<<endl;
	cout<<"\tPlease, insert the coefficient 'Kx' (thus, a positive and not null 'integer' value) for the 'Lissajous-like' curve of interest: ";
	cin>>Kx;
	if( (!cin) || (Kx<=0) )
	{
		cout<<endl<<"\tPLEASE, INSERT A VALID VALUE (THUS, A POSITIVE AND NOT NULL 'INTEGER' VALUE) FOR THE COEFFICIENT 'Kx' OF INTEREST."<<endl<<endl<<"\tTHIS PROGRAM IS CLOSING ..."<<endl<<endl;
		cout.flush();
		return EXIT_FAILURE;
	}
	
	/* Now, we read the coefficient 'Ky' for the 'Lissajous-like' curve of interest. */
	cout<<"\tPlease, insert the coefficient 'Ky' (thus, a positive and not null 'integer' value) for the 'Lissajous-like' curve of interest: ";
	cin>>Ky;
	if( (!cin) || (Ky<=0) )
	{
		cout<<endl<<"\tPLEASE, INSERT A VALID VALUE (THUS, A POSITIVE AND NOT NULL 'INTEGER' VALUE) FOR THE COEFFICIENT 'Ky' OF INTEREST."<<endl<<endl<<"\tTHIS PROGRAM IS CLOSING ..."<<endl<<endl;
		cout.flush();
		return EXIT_FAILURE;
	}
	
	/* Now, we read the coefficient 'Rx' for the 'Lissajous-like' curve of interest. */
	cout<<"\tPlease, insert the coefficient 'Rx' (thus, a positive and not null 'integer' value) for the 'Lissajous-like' curve of interest: ";
	cin>>Rx;
	if( (!cin) || (Rx<=0) )
	{
		cout<<endl<<"\tPLEASE, INSERT A VALID VALUE (THUS, A POSITIVE AND NOT NULL 'INTEGER' VALUE) FOR THE COEFFICIENT 'Rx' OF INTEREST."<<endl<<endl<<"\tTHIS PROGRAM IS CLOSING ..."<<endl<<endl;
		cout.flush();
		return EXIT_FAILURE;
	}
	
	/* Now, we read the coefficient 'Ry' for the 'Lissajous-like' curve of interest. */
	cout<<"\tPlease, insert the coefficient 'Ry' (thus, a positive and not null 'integer' value) for the 'Lissajous-like' curve of interest: ";
	cin>>Ry;
	if( (!cin) || (Ry<=0) )
	{
		cout<<endl<<"\tPLEASE, INSERT A VALID VALUE (THUS, A POSITIVE AND NOT NULL 'INTEGER' VALUE) FOR THE COEFFICIENT 'Ry' OF INTEREST."<<endl<<endl<<"\tTHIS PROGRAM IS CLOSING ..."<<endl<<endl;
		cout.flush();
		return EXIT_FAILURE;
	}
	
	/* If we arrive here, we can draw the polyline, approximating the 'Lissajous-like' curve! */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	if(Rx==Ry) glutInitWindowSize(500,500);
	else if(Rx>Ry) { glutInitWindowSize(1000,1000*Ry/Rx); }
	else { glutInitWindowSize(1000*Rx/Ry,1000); }
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
	/* We update the projection and the modeling matrices! */
	glViewport(0, 0, w, h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glOrtho(-1.1*Rx,1.1*Rx,-1.1*Ry,1.1*Ry,-1,1);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	num_samples=7;
	cout<<endl<<"\tAt the beginning, the polyline, approximating the 'Lissajous-like' curve with the coefficients 'Rx'="<<Rx<<", 'Ry'="<<Ry<<", 'Kx'="<<Kx<<", and 'Ky'="<<Ky<<", is formed by 'n'="<<num_samples<<" vertices and edges (thus by the minimum number 'n'";
	cout<<" of vertices and edges as possible)."<<endl<<endl;
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
		
		/* The key is '+', thus we increase the number of the vertices and edges in the polyline of interest! */
		num_samples=num_samples+1;
		glutPostRedisplay();
		break;
		
		case '-':
		
		/* The key is '-', thus we decrease the number of the vertices and edges (if possible) in the polyline of interest. */
		if(num_samples>7) num_samples=num_samples-1;
		else cout<<"\tThe minimum number 'n'=7 of vertices and edges in the polyline of interest is reached, and it is not possible to decrease again this number."<<endl;
		cout.flush();
		glutPostRedisplay();
		break;

		default:

    	/* Other keys are not important for us! */
    	break;
	}
}

/// This function draws the polyline (in <i>'blue'</i>), approximating the <i>'Lissajous-like'</i> curve of interest, in the main OpenGL window.
void draw()
{
	/* We draw the polyline (in 'blue'), approximating the 'Lissajous-like' curve of interest, in the main OpenGL window. */
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.1,0.0,1.0);
	glLineWidth(2);
	float d=(2*PI)/(num_samples-1);
	float t=0.0;
	glBegin(GL_LINE_STRIP);
	for(int k=0;k<num_samples;k++)
	{
		t=k*d;
		glVertex3f(Rx*cos(Kx*t),Ry*sin(Ky*t),0);
	}
	
	/* If we arrive here, all is ok */
	glEnd();
	glFlush();
	cout<<"\tThe 'Lissajous-like' curve of interest is currently approximated by a polyline with 'n'="<<num_samples<<" vertices and 'n'="<<num_samples<<" edges."<<endl;
	cout.flush();
}
