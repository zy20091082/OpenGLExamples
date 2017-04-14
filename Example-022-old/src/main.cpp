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

	/* We are not using a MacOSX platform. Thus, we have a generic Unix-like platform, like the GNU/Linux, or a Microsoft Windows platform. */
	#include "GL/glew.h"
	#include "GL/glut.h"
	#include "GL/gl.h"

#endif

/// The radius <i>'R'</i> to be used for defining and drawing the approximation of interest for the <i>'Circle'</i> shape.
/**
 * Clearly, it must be a positive and not null floating-point value, provided interactively by the user.
 */
float radius;

/// The center coordinates <i>'(xc,yc)'</i> to be used for defining and drawing the approximation of interest for the <i>'Circle'</i> shape.
/**
 * Clearly, the center for the 'Circle' shape of interest is formed by 2 floating-point values, provided interactively by the user.
 */
float xc,yc;

/// The number of the samples for drawing the approximation of interest for the <i>'Circle'</i> shape.
/**
 * It is initially set to '3', which is the minimum number 'n' of samples in the approximation of interest. More specifically:
 *
 * -) if the polyline, approximating the boundary of the 'Circle' shape, is drawn, then this number is the number 'n' of its vertices;
 * -) if the 'Circle' shape is approximated by a triangle fan, centered at '(xc,yc)', then this number is the number 'n' of its triangles;
 *- ) if the 'Circle' shape is approximated by only one polygon, then this number is the number 'n' of its vertices and edges.
 *
 * The number 'n' of the samples is interactively modified by pressing the '+' and the '-' keys.
 */
unsigned int num_samples=3;

/// The settings for choosing which approximation of the <i>'Circle'</i> shape must be drawn.
/**
 * The value of this flag may be one of the following values:
 *
 * -) the 'l' char value, used for choosing to approximate only the boundary of the 'Circle' shape through a polyline, formed by an arbitrary number 'n' of vertices and edges.
 * -) The 'f' char value, used for choosing to approximate the 'Circle' shape through the 'filled version' of a triangle fan, formed by an arbitrary number 'n' of triangles. All triangles are incident at the center '(xc,yc)' of the 'Circle' shape.
 * -) the 'p' char value, used for choosing to approximate the 'Circle' shape through the 'filled version' of only one polygon, formed by an arbitrary number 'n' of vertices and edges.
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
	cout<<"\tIt draws 3 approximations of the 'Circle' shape with radius 'R' and center '(xc,yc)'. The approximations of interest are activated upon request, and are formed by an arbitrary number 'n' of samples."<<endl;
	cout<<"\tThe 'Circle' shape is defined as follows:"<<endl<<endl;
	cout<<"\t| x(t) - xc | <= R * cos(t), | y(t) - yc | <= R * sin(t)"<<endl<<endl<<"\tfor any 'R'>0, and for every 't' in '[-pi,pi]'."<<endl<<endl;
	cout<<"\tThe radius 'R' and the center coodinates '(xc,yc)' are specified by the user interactively, which can also:"<<endl<<endl;
	cout<<"\t\t-) approximate the boundary (in 'red') of the 'Circle' shape through a polyline with 'n' vertices and edges (indicated as the 'Approximation #0') by pressing the 'l' key;"<<endl;
	cout<<"\t\t-) approximate the 'Circle' shape through the 'filled version' for a triangle fan (in 'dark gray') of 'n' triangles (indicated as the 'Approximation #1'), incident at the reference vertex '(xc,yc)' (in 'red'), by pressing the 'f' key;"<<endl;
	cout<<"\t\t-) approximate the 'Circle' shape through the 'filled version' of only one polygon (in 'red') with 'n' vertices and edges (indicated as the 'Approximation #2') by pressing the 'p' key;"<<endl;
	cout<<"\t\t-) increase the number 'n' of the samples for the approximation of interest by pressing the '+' key;"<<endl;
	cout<<"\t\t-) decrease the number 'n' of the samples for the approximation of interest by pressing the '-' key."<<endl<<endl;
	cout<<"\tIt is possible to end this program by pressing one among the 'Q' - 'q' - 'Esc' keys."<<endl<<endl;
	cout.flush();
	cout<<"\tPlease, insert the radius 'R' (thus, a positive and not null floating-point value) for the 'Circle' shape of interest: ";
	cin>>radius;
	if( (!cin) || (radius<=0) )
	{
		cout<<endl<<"\tPLEASE, INSERT A VALID VALUE (THUS, A POSITIVE AND NOT NULL FLOATING-POINT VALUE) FOR THE RADIUS 'R' OF INTEREST."<<endl<<endl<<"\tTHIS PROGRAM IS CLOSING ..."<<endl<<endl;
		cout.flush();
		return EXIT_FAILURE;
	}
	
	/* Now, we read the center coordinates '(xc,yc)' for the 'Circle' shape of interest. */
	cout<<"\tPlease, insert the center coordinates '(xc,yc)' for the 'Circle' shape of interest (thus, 2 floating-point values, separated by a space): ";
	cout.flush();
	cin>>xc>>yc;
	if(!cin)
	{
		cout<<endl<<"\tPLEASE, INSERT THE CENTER COORDINATES '(xc,yc)' FOR THE 'CIRCLE' SHAPE OF INTEREST (THUS, 2 FLOATING-POINT VALUES, SEPARATED BY A SPACE)."<<endl<<endl<<"\tTHIS PROGRAM IS CLOSING ..."<<endl<<endl;
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
	/* We update the projection and the modeling matrices! */
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
	cout<<endl<<"\tAt the beginning, the boundary of the 'Circle' shape with center '("<<xc<<","<<yc<<")' and radius '"<<radius<<"', is approximated by a polyline, formed by 'n'="<<num_samples<<" vertices and 'n'="<<num_samples<<" edges (thus by the ";
	cout<<"minimum number 'n' of vertices and edges as possible) [ Approximation #0 ]."<<endl<<endl;
	cout.flush();
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
		
		/* The key is '+', thus we increase the number of the samples in the approximation of interest for the 'Curve' shape. */
		num_samples=num_samples+1;
		glutPostRedisplay();
		break;
		
		case '-':
		
		/* The key is '-', thus we decrease the number of the samples (if possible) in the approximation of interest for the 'Curve' shape. */
		if(num_samples>3) num_samples=num_samples-1;
		else
		{
			cout<<"\tThe minimum number 'n'=3 of ";
			if(choice=='l') { cout<<" vertices and edges in the polyline, approximating the boundary of the 'Curve' shape [ Approximation #0 ], "; }
			if(choice=='f') { cout<<" triangles in the 'filled version' of the triangle fan, approximating the 'Curve' shape [ Approximation #1 ], "; }
			if(choice=='p') { cout<<" vertices and edges in the 'filled version' of the only one polygon, approximating the 'Curve' shape [ Approximation #2 ], "; }
			cout<<"is reached, and it is not possible to decrease again this number."<<endl;
			cout.flush();
		}
		
		/* We finalize this case. */
		glutPostRedisplay();
		break;
		
		case 'l':
		
		/* The key is 'l', thus we choose to approximate only the boundary for the 'Circle' shape of interest by using a polyline with an arbitrary number 'n' of vertices and edges. */
		choice='l';
		glutPostRedisplay();
		break;
		
		case 'f':
		
		/* The key is 'f', thus we choose to approximate the 'Circle' shape of interest by using the 'filled version' of a triangle fan with an arbitrary number 'n' of triangles, and with the center '(xc,yc)' of the 'Circle' shape as the reference vertex. */
		choice='f';
		glutPostRedisplay();
		break;
		
		case 'p':
		
		/* The key is 'p', thus we choose to approximate the 'Circle' shape of interest by using the 'filled version' of the only one polygon with an arbitrary number 'n' of vertices and edges. */
		choice='p';
		glutPostRedisplay();
		break;

		default:

    	/* Other keys are not important for us! */
    	break;
	}
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
		/* We must approximate the boundary curve of the 'Circle' shape by using a polyline (in 'red') with 'n' vertices and edges! */
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
		cout<<"\tCurrently, the boundary for the 'Circle' shape of interest is approximated by a polyline with 'n'="<<num_samples<<" vertices and 'n'="<<num_samples<<" edges [ Approximation #0 ]."<<endl;
		cout.flush();
	}
	else if(choice=='f')
	{
		/* We must approximate the 'Circle' shape by using the 'filled version' of a triangle fan. The reference vertex is the center '(xc,yc)'. Here, the triangles are shown in 'dark gray', and the reference vertex is shown in 'red'. */
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
		cout<<"\tCurrently, the 'Circle' shape of interest is approximated by the 'filled version' of a triangle fan with 'n'="<<num_samples<<" triangles [ Approximation #1 ]."<<endl;
		cout.flush();
	}
	else if(choice=='p')
	{
		/* We must approximate the 'Circle' shape by using the 'filled version' of only one polygon (in 'red') with 'n' vertices and edges! */
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
		cout<<"\tCurrently, the 'Circle' shape of interest is approximated by the 'filled version' of only one polygon with 'n'="<<num_samples<<" vertices and 'n'="<<num_samples<<" edges [ Approximation #2 ]."<<endl;
		cout.flush();
	}
}
