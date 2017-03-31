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

/// The number of the samples, used for defining the approximation of interest for the <i>'Circle'</i> shape.
unsigned int num_samples=3;

/// The setting for choosing which approximation of the <i>'Circle'</i> shape must be drawn.
/**
 * It may be one of the following values:
 *
 * -) the 'l' char value, used for choosing to approximate only the boundary of the <i>'Circle'</i> shape through a polyline, formed by an arbitrary number of vertices and edges. Only the edges of the polyline are rendered ('wireframe version');
 * -) the 'f' char value, used for choosing to approximate the <i>'Circle'</i> shape through a triangle fan, formed by an arbitrary number of triangles. All triangles are incident at the center the <i>'Circle'</i> shape, and completed filled ('filled version').
 * -) the 'p' char value, used for choosing to approximate the <i>'Circle'</i> shape through an unique polygon, formed by an arbitrary number of vertices and edges. The polygon of interest is completely filled ('filled version').
 */
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
	cout<<"\tIt draws different versions (formed by an arbitrary number of samples) of the 'Circle' shape with radius 'R' and center '(xc,yc)'. This latter is defined as follows:"<<endl<<endl;
	cout<<"\tx(t) = xc + R * cos(t), y(t) = yc + R * sin(t)"<<endl<<endl<<"\twith 'R'>0 and 't' in '[-pi,pi]'."<<endl<<endl;
	cout<<"\tThe radius 'R' and the center coodinates '(xc,yc)' are specified by the user, which can also:"<<endl<<endl;
	cout<<"\t\t-) decide to approximate the boundary (in 'red') of the 'Circle' shape through a polyline by pressing the 'l' key;"<<endl;
	cout<<"\t\t-) decide to approximate the 'Circle' shape through the 'filled version' for a triangle fan (in 'dark gray') of several triangles, incident at the reference vertex '(xc,yc)' (in 'red'), by pressing the 'f' key;"<<endl;
	cout<<"\t\t-) decide to approximate the 'Circle' shape through the 'filled version' of only one polygon (in 'red') by pressing the 'p' key;"<<endl;
	cout<<"\t\t-) increase the number of the samples for the approximation of interest by pressing the '+' key;"<<endl;
	cout<<"\t\t-) decrease the number of the samples for the approximation of interest by pressing the '-' key."<<endl<<endl;
	cout<<"\tIt is possible to end this program by pressing one among the 'Q' - 'q' - 'Esc' keys."<<endl<<endl;
	cout.flush();
	cout<<"\tPlease, insert the radius 'R' (positive and not null) for the 'Circle' shape of interest: ";
	cin>>radius;
	if( (!cin) || (radius<=0) )
	{
		cout<<endl<<"\tPLEASE, INSERT A VALID VALUE (POSITIVE AND NOT NULL) FOR THE RADIUS 'R' OF INTEREST."<<endl<<endl<<"\tTHIS PROGRAM IS CLOSING ..."<<endl<<endl;
		cout.flush();
		return EXIT_FAILURE;
	}
	
	/* Now, we read the center coordinates '(xc,yc)' for the 'Circle' shape of interest. */
	cout<<"\tPlease, insert the center coordinates '(xc,yc)' for the 'Circle' shape of interest (separated by a space): ";
	cout.flush();
	cin>>xc>>yc;
	if(!cin)
	{
		cout<<endl<<"\tPLEASE, INSERT THE CENTER COORDINATES '(xc,yc)' FOR THE 'CIRCLE' SHAPE OF INTEREST (SEPARATED BY A SPACE)."<<endl<<endl<<"\tTHIS PROGRAM IS CLOSING ..."<<endl<<endl;
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
		else cout<<"\tThe minimum number 3 of samples is reached in the approximation of interest for the 'Circle' shape, and it is not possible to decrease again this number."<<endl;
		cout.flush();
		glutPostRedisplay();
		break;
		
		case 'l':
		
		/* The key is 'l', thus we choose to approximate only the boundary for the 'Circle' shape of interest by using a polyline with an arbitrary number of vertices and edges. */
		choice='l';
		glutPostRedisplay();
		break;
		
		case 'f':
		
		/* The key is 'f', thus we choose to approximate the 'Circle' shape of interest by using the 'filled version' of a triangle fan with an arbitrary number of triangles, and with the center '(xc,yc)' of the 'Circle' shape as the reference vertex. */
		choice='f';
		glutPostRedisplay();
		break;
		
		case 'p':
		
		/* The key is 'p', thus we choose to approximate the 'Circle' shape of interest by using the 'filled version' of only one polygon with an arbitrary number of vertices and edges. */
		choice='p';
		glutPostRedisplay();
		break;

		default:

    	/* Other keys are not important for us! */
    	break;
	}
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	num_samples=3;
	choice='l';
	cout<<endl<<"\tInitially, the boundary of the 'Circle' shape with center ("<<xc<<","<<yc<<") and radius "<<radius<<", is approximated by a polyline, formed by "<<num_samples<<" samples (the minimum number as possible)."<<endl<<endl;
	cout.flush();
}

/// This function draws the specific approximation of the <i>'Circle'</i> shape in the OpenGL window of interest by using the current rendering settings (chosen by the user).
void draw()
{
	float t;

	/* We draw the specific approximation of the 'Circle' shape in the OpenGL window of interest by using the current rendering settings (chosen by the user). */
	t=0;
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(1);
	glLineWidth(1);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	if(choice=='l')
	{
		/* We must approximate the boundary curve of the 'Circle' shape by using a polyline (in 'red')! */
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
		cout<<"\tOnly the "<<num_samples<<" vertices and "<<num_samples<<" edges in the polyline, approximating the boundary for the 'Circle' shape of interest, are rendered."<<endl;
		cout.flush();
	}
	else if(choice=='f')
	{
		/* We must approximate the 'Circle' shape by using a triangle fan, formed by several filled triangles. The reference vertex is the center '(xc,yc)'. Here, the triangles are shown in 'dark gray', and the reference vertex is shown in 'red'. */
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
		cout<<"\tThe 'filled versions' of "<<num_samples<<" triangles in the triangle fan, approximating the 'Circle' shape of interest, are rendered."<<endl;
		cout.flush();
	}
	else if(choice=='p')
	{
		/* We must approximate the 'Circle' shape by using only one polygon. The polygon is completely filled in 'red'. */
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
		cout<<"\tThe 'filled version' of the polygon with "<<num_samples<<" vertices and "<<num_samples<<" edges, approximating the 'Circle' shape of interest, is rendered."<<endl;
		cout.flush();
	}
}
