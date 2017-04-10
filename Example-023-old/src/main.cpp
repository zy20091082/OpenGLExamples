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
 * main.cpp - the main function for the 'Example-023 (Old Mode)' example.
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

/// The center coordinates <i>'(xc,yc)'</i> for the <i>'Ellipse'</i> curve of interest.
/**
 * Clearly, it is formed by 2 floating-point values, provided interactively by the user.
 */
float xc,yc;

/// The number of the vertices and edges in the polyline, used for approximating the <i>'Ellipse'</i> curve of interest.
/**
 * It is initially set to '3', which is the minimum number of vertices and edges. It is interactively modified by pressing the '+' and the '-' keys.
 */
unsigned int num_samples=3;

/// The semi-axis <i>'Rx'</i> along the x-axis for drawing the <i>'Ellipse'</i> curve of interest.
/**
 * Clearly, it must be a positive and not null floating-point value, provided interactively by the user.
 */
float Rx;

/// The semi-axis <i>'Ry'</i> along the y-axis for drawing the <i>'Ellipse'</i> curve of interest.
/**
 * Clearly, it must be a positive and not null floating-point value, provided interactively by the user.
 */
float Ry;

/* Prototypes for all functions of interest! */
void draw();
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);

/// The main function for the <i>'Example-023 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-023' Example, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws a polyline (in 'red'), formed by an arbitrary number 'n' of vertices and edges, which approximates the 'Ellipse' curve with semi-axis 'Rx' and 'Ry' (respectively along the x- and the y-axis), as well as center '(xc,yc)'."<<endl;
	cout<<"\tThis curve is defined as follows:"<<endl<<endl;
	cout<<"\tx(t) = xc + Rx * cos(t), y(t) = yc + Ry * sin(t)"<<endl<<endl<<"\twith 'Rx'>0, 'Ry'>0, and 't' in '[-pi,pi]'."<<endl<<endl;
	cout<<"\tThe semi-axis 'Rx' and 'Ry' as well as the center coodinates '(xc,yc)' are specified by the user interactively, which can also:"<<endl<<endl;
	cout<<"\t\t-) increase the number 'n' of the vertices and edges for the polyline of interest by pressing the '+' key;"<<endl;
	cout<<"\t\t-) decrease the number 'n' of the vertices and edges for the polyline of interest by pressing the '-' key."<<endl<<endl;
	cout<<"\tIt is possible to end this program by pressing one among the 'Q' - 'q' - 'Esc' keys."<<endl<<endl;
	cout<<"\tPlease, insert the semi-axis 'Rx' (thus, a positive and not null floating-point value) for the 'Ellipse' curve of interest: ";
	cin>>Rx;
	if( (!cin) || (Rx<=0) )
	{
		cout<<endl<<"\tPLEASE, INSERT A VALID VALUE (THUS, A POSITIVE AND NOT NULL FLOATING-POINT VALUE) FOR THE SEMI-AXIS 'Rx' OF INTEREST."<<endl<<endl<<"\tTHIS PROGRAM IS CLOSING ..."<<endl<<endl;
		cout.flush();
		return EXIT_FAILURE;
	}
	
	/* Now, we read the length of the second semi-axis 'Ry' (along the y-axis) for the 'Ellipse' curve of interest. */
	cout<<"\tPlease, insert the semi-axis 'Ry' (thus, a positive and not null floating-point value) for the 'Ellipse' curve of interest: ";
	cin>>Ry;
	if( (!cin) || (Ry<=0) )
	{
		cout<<endl<<"\tPLEASE, INSERT A VALID VALUE (THUS, A POSITIVE AND NOT NULL FLOATING-POINT VALUE) FOR THE SEMI-AXIS 'Ry' OF INTEREST."<<endl<<endl<<"\tTHIS PROGRAM IS CLOSING ..."<<endl<<endl;
		cout.flush();
		return EXIT_FAILURE;
	}
	
	/* Now, we read the center coordinates '(xc,yc)' for the 'Ellipse' curve of interest. */
	cout<<"\tPlease, insert the center coordinates '(xc,yc)' for the 'Ellipse' curve of interest (thus, 2 floating-point values, separated by a space): ";
	cout.flush();
	cin>>xc>>yc;
	if(!cin)
	{
		cout<<endl<<"\tPLEASE, INSERT THE CENTER COORDINATES '(xc,yc)' FOR THE 'ELLIPSE' CURVE OF INTEREST (THUS, 2 FLOATING-POINT VALUES, SEPARATED BY A SPACE)."<<endl<<endl<<"\tTHIS PROGRAM IS CLOSING ..."<<endl<<endl;
		cout.flush();
		return EXIT_FAILURE;
	}
	
	/* If we arrive here, we can draw the polyline, approximating the 'Ellipse' curve! */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	if(Rx==Ry) glutInitWindowSize(500,500);
	else if(Rx>Ry) { glutInitWindowSize(1000,1000*Ry/Rx); }
	else { glutInitWindowSize(1000*Rx/Ry,1000); }
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

/// This function updates the viewport for the scene when it is resized. */
void resize(int w, int h)
{
	/* We update the projection and the modeling matrices! */
	glViewport(0, 0, w, h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glOrtho(xc-1.1*Rx,xc+1.1*Rx,yc-1.1*Ry,yc+1.1*Ry,-1,1);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	num_samples=3;
	cout<<endl<<"\tAt the beginning, the polyline, approximating the 'Ellipse' curve of center '("<<xc<<","<<yc<<")', semi-axis 'Rx'="<<Rx<<", and semi-axis 'Ry'="<<Ry<<", is formed by 'n'="<<num_samples<<" vertices and edges (thus by the the minimum ";
	cout<<"number of vertices and edges as possible)."<<endl<<endl;
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
		if(num_samples>3) num_samples=num_samples-1;
		else cout<<"\tThe minimum number 'n'=3 of vertices and edges in the polyline of interest is reached, and it is not possible to decrease again this number."<<endl;
		cout.flush();
		glutPostRedisplay();
		break;

		default:

    	/* Other keys are not important for us! */
    	break;
	}
}

/// This function draws the polyline (in <i>'red'</i>), approximating the <i>'Ellipse'</i> curve of interest, in the main OpenGL window.
void draw()
{
	float t;

	/* We draw the polyline (in 'red'), approximating the 'Ellipse' curve of interest, in the main OpenGL window. */
	t=0;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINE_LOOP);
	for(unsigned int i=0;i<=num_samples;i++)
	{
		glVertex3f(xc+Rx*cos(t),yc+Ry*sin(t),0);
		t=t+(2*PI/num_samples);
	}
	
	/* If we arrive here, all is ok */
	glEnd();
	glFlush();
	cout<<"\tThe 'Ellipse' curve of interest is currently approximated by a polyline with 'n'="<<num_samples<<" vertices and 'n'="<<num_samples<<" edges."<<endl;
	cout.flush();
}
