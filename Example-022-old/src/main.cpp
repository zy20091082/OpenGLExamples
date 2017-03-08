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
 * main.cpp - the main function for the 'Example-022 (Old Mode)' example.
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

/// The radius <i>'R'</i> for drawing the <i>'Circle'</i> shape of interest.
float radius;

/// The center coordinates <i>'(xc,yc)'</i> for the <i>'Circle'</i> shape of interest.
float xc,yc;

/// The number of the samples, used for approximating the <i>'Circle'</i> shape of interest.
unsigned int num_samples=3;

/// The rendering choice for drawing the specific version <i>'Circle'</i> shape, chosen by the user, i.e., a polyline (the 'l' key and 'char'), a triangle fan (the 'f' key and 'char'), and a polygon (the 'p' key and 'char').
char choice;

/* Prototypes for all functions of interest! */
void draw();
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);

/// The main function for the <i>'Example-022 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-022' Example, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws different versions (formed by an arbitrary number of samples) of the 'Circle' shape with radius 'R' and center '(xc,yc)'."<<endl;
	cout<<"\tThe radius 'R' and the center coodinates '(xc,yc)' are specified by the user, which can also:"<<endl<<endl;
	cout<<"\t\t-) decide to approximate the 'Circle' shape through a polyline by pressing the 'l' key;"<<endl;
	cout<<"\t\t-) decide to approximate the 'Circle' shape through a triangle fan by pressing the 'f' key;"<<endl;
	cout<<"\t\t-) decide to approximate the 'Circle' shape through only one polygon by pressing the 'p' key;"<<endl;
	cout<<"\t\t-) increase the number of the samples for the approximation of interest by pressing the '+' key;"<<endl;
	cout<<"\t\t-) decrease the number of the samples for the approximation of interest by pressing the '-' key."<<endl<<endl;
	cout<<"\tIt is possible to end this program by pressing one among the 'Q' - 'q' - 'Esc' keys."<<endl<<endl;
	cout.flush();
	cout<<"\tPlease, insert the radius 'R' (positive and not null) for the 'Circle' shape of interest: ";
	cin>>radius;
	if( (!cin) || (radius<=0) )
	{
		cout<<"\tPLEASE, INSERT A VALID VALUE FOR THE RADIUS 'R' OF INTEREST. THIS PROGRAM IS CLOSING ..."<<endl<<endl;
		cout.flush();
		return EXIT_FAILURE;
	}
	
	/* Now, we read the center coordinates '(xc,yc)' for the 'Circle' shape of interest. */
	cout<<"\tPlease, insert the center coordinates '(xc,yc)' for the 'Circle' shape of interest (separated by a space): ";
	cout.flush();
	cin>>xc>>yc;
	if(!cin)
	{
		cout<<"\tPLEASE, INSERT THE CENTER COORDINATES '(xc,yc)' FOR THE 'CIRCLE' SHAPE OF INTEREST (SEPARATED BY A SPACE). THIS PROGRAM IS CLOSING ..."<<endl<<endl;
		cout.flush();
		return EXIT_FAILURE;
	}
	
	/* If we arrive here, we can draw the approximation of interest for the 'Circle' shape! */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-022' Example, based on the (Old Mode) OpenGL");
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
   	glOrtho(xc-1.1*radius,xc+1.1*radius,yc-1.1*radius,yc+1.1*radius,-1,1);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	num_samples=3;
	choice='l';
	cout<<endl<<"\tInitially, the 'Circle' shape of center ("<<xc<<","<<yc<<") and radius "<<radius<<", is approximated by a polyline, formed by "<<num_samples<<" samples (the minimum number as possible)."<<endl<<endl;
	cout.flush();
}

/// This function draws the specific version of the <i>'Circle'</i> shape in the OpenGL window of interest by using the current rendering settings (chosen by the user).
void draw()
{
	float t;

	/* We draw the specific version of the <i>'Circle'</i> shape in the OpenGL window of interest by using the current rendering settings (chosen by the user). */
	t=0;
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(1);
	glLineWidth(1);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	if(choice=='l')
	{
		/* We must draw a polyline! */
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_LINE_LOOP);
		for(unsigned int i=0;i<=num_samples;i++)
		{
			glVertex3f(xc+radius*cos(t),yc+radius*sin(t),0);
			t=t+(2*PI/num_samples);
		}
		
		/* If we arrive here, all is ok */
		glEnd();
		glFlush();
		cout<<"\tThe 'Circle' shape of interest is approximated by a polyline, formed by "<<num_samples<<" samples (thus by "<<num_samples<<" vertices and "<<num_samples<<" edges)."<<endl;
		cout.flush();
	}
	else if(choice=='f')
	{
		/* We draw a triangle fan! */
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_TRIANGLE_FAN);
		glVertex3f(xc,yc,0);
		glColor3f(0.5,0.5,0.5);
		for(unsigned int i=0;i<=num_samples;i++)
		{
			glVertex3f(xc+radius*cos(t),yc+radius*sin(t),0);
			t=t+(2*PI/num_samples);
		}
		
		/* If we arrive here, all is ok */
		glEnd();
		glFlush();
		cout<<"\tThe 'Circle' shape of interest is approximated by a triangle fan, formed by "<<num_samples<<" samples (thus by "<<num_samples<<" vertices and "<<num_samples<<" triangles)."<<endl;
		cout.flush();
	}
	else if(choice=='p')
	{
		/* We draw a polyline! */
		glColor3f(1.0,0.0,0.0);
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		glBegin(GL_POLYGON);
		for(unsigned int i=0;i<=num_samples;i++)
		{
			glVertex3f(xc+radius*cos(t),yc+radius*sin(t),0);
			t=t+(2*PI/num_samples);
		}
		
		/* If we arrive here, all is ok */
		glEnd();
		glFlush();
		cout<<"\tThe 'Circle' shape is approximated by only one polygon, formed by "<<num_samples<<" samples (thus by "<<num_samples<<" vertices and "<<num_samples<<" edges)."<<endl;
		cout.flush();
	}
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '+' - '-' - 'l' - 'f' - 'p' keys. */
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
		
		/* The key is '+', thus we increase the number of the samples for drawing the approximation of interest for the 'Circle' shape. */
		num_samples=num_samples+1;
		glutPostRedisplay();
		break;
		
		case '-':
		
		/* The key is '-', thus we decrease the number of the samples (if possible) for drawing the approximation of interest for the 'Circle' shape. */
		if(num_samples>3) num_samples=num_samples-1;
		else cout<<"\tThe minimum number 3 of samples is reached, and it is not possible to decrease again this number."<<endl;
		cout.flush();
		glutPostRedisplay();
		break;
		
		case 'l':
		
		/* The key is 'l', thus we choose to approximate the 'Circle' shape of interest by using a polyline. */
		choice='l';
		glutPostRedisplay();
		break;
		
		case 'f':
		
		/* The key is 'f', thus we choose to approximate the 'Circle' shape of interest by using a triangle fan. */
		choice='f';
		glutPostRedisplay();
		break;
		
		case 'p':
		
		/* The key is 'p', thus we choose to approximate the 'Circle' shape of interest by using only one polygon. */
		choice='p';
		glutPostRedisplay();
		break;

		default:

    	/* Other keys are not important for us! */
    	break;
	}
}
