/*******************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 * 
 * Last update: May 2017
 *
 * This program is Free Software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.                                       
 *                                                                         
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License (http://www.gnu.org/licenses/gpl.txt) for more details.
 * 
 * main.cpp - the main function for the 'Example-022 (Old Mode)' Test.
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

/// The number <i>'n'</i> of the samples for drawing the approximation of interest for the <i>'Circle'</i> shape.
/**
 * It is initially set to 'n=3', which is the minimum number 'n' of the samples in the approximation of interest. More specifically:
 *
 * -) if the polyline, approximating the boundary of the 'Circle' shape, is drawn, then this number is the number 'n' of its vertices and edges;
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
 * -) the 'l' char value, used for choosing to approximate only the boundary of the 'Circle' shape through a polyline, formed by an arbitrary number 'n' of the vertices and the edges.
 * -) The 'f' char value, used for choosing to approximate the 'Circle' shape through the 'filled version' of a triangle fan, formed by an arbitrary number 'n' of the triangles. All triangles are incident at the center '(xc,yc)' of the 'Circle' shape.
 * -) the 'p' char value, used for choosing to approximate the 'Circle' shape through the 'filled version' of only one polygon, formed by an arbitrary number 'n' of the vertices and the edges.
 */
char choice;

/* Prototypes for all functions of interest! */
void draw();
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);

/// The main function for the <i>'Example-022 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-022' Test, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws 3 approximations of the 'Circle' shape with radius 'R' and center '(xc,yc)' in an OpenGL window. The approximations of interest are activated upon request, and are formed by an arbitrary number 'n' of the samples."<<endl;
	cout<<"\tThe 'Circle' shape is defined as follows:"<<endl<<endl;
	cout<<"\t| x(t) - xc | <= R * cos(t), | y(t) - yc | <= R * sin(t)"<<endl<<endl<<"\tfor any 'R'>0, and for every 't' in '[-pi,pi]'."<<endl<<endl;
	cout<<"\tThis test also provides a very basic interaction mechanism with the user, which must provide the radius 'R' and the center '(xc,yc)'. The user can:"<<endl<<endl;
	cout<<"\t\t-) approximate the boundary (in 'red') of the 'Circle' shape through a polyline with an arbitrary number 'n' of the vertices and the edges [ 'Approximation #0' ] by pressing the 'l' key."<<endl<<endl;
	cout<<"\t\t-) Approximate the 'Circle' shape through the 'filled versions' of 'n' triangles in a triangle fan [ 'Approximation #1' ] by pressing the 'f' key. All triangles (in 'dark gray') are incident at the center '(xc,yc)'"<<endl;
	cout<<"\t\t   (in 'red')."<<endl<<endl;
	cout<<"\t\t-) Approximate the 'Circle' shape through the 'filled version' of only one polygon (in 'red') with 'n' vertices and edges [ 'Approximation #2' ] by pressing the 'p' key."<<endl<<endl;
	cout<<"\t\t-) Increase the number 'n' of the samples in the approximation of interest by pressing the '+' key."<<endl<<endl;
	cout<<"\t\t-) Decrease the number 'n' of the samples in the approximation of interest by pressing the '-' key."<<endl<<endl;
	cout<<"\tLikewise, the window of interest can be closed by pressing any among the 'Q', the 'q', and the 'Esc' keys."<<endl<<endl;
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
	glutCreateWindow("The 'Example-022' Test, based on the (Old Mode) OpenGL");
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
	cout<<endl<<"\tAt the beginning, the boundary of the 'Circle' shape with center '("<<xc<<","<<yc<<")' and radius '"<<radius<<"' is approximated by a polyline, formed by 'n="<<num_samples<<"' vertices and 'n="<<num_samples<<"' edges (thus by the ";
	cout<<"minimum number 'n' as possible of the vertices"<<endl;
	cout<<"\tand the edges) [ 'Approximation #0' ]."<<endl<<endl;
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
		
		/* The key is '+', thus we increase the number 'n' of the samples in the approximation of interest for the 'Curve' shape. */
		num_samples=num_samples+1;
		glutPostRedisplay();
		break;
		
		case '-':
		
		/* The key is '-', thus we decrease the number 'n' of the samples (if possible) in the approximation of interest for the 'Curve' shape. */
		if(num_samples>3) num_samples=num_samples-1;
		else
		{
			cout<<"\tThe minimum number 'n=3' of";
			if(choice=='l') { cout<<" the vertices and the edges in the polyline, approximating the boundary of the 'Curve' shape [ 'Approximation #0' ], "; }
			if(choice=='f') { cout<<" the 'filled versions' for all triangles in the triangle fan, approximating the 'Curve' shape [ 'Approximation #1' ], "; }
			if(choice=='p') { cout<<" the vertices and the edges in the 'filled version' of the only one polygon, approximating the 'Curve' shape [ 'Approximation #2' ], "; }
			cout<<"is reached, and it is not possible to decrease again this number."<<endl;
			cout.flush();
		}
		
		/* We finalize this case. */
		glutPostRedisplay();
		break;
		
		case 'l':
		
		/* The key is 'l', thus we choose to approximate only the boundary for the 'Circle' shape of interest by using a polyline with an arbitrary number 'n' of the vertices and the edges. */
		choice='l';
		glutPostRedisplay();
		break;
		
		case 'f':
		
		/* The key is 'f', thus we choose to approximate the 'Circle' shape of interest by using the 'filled versions' of an arbitrary number 'n' of the triangles in a triangle fan with the center '(xc,yc)' of the 'Circle' shape as the reference vertex. */
		choice='f';
		glutPostRedisplay();
		break;
		
		case 'p':
		
		/* The key is 'p', thus we choose to approximate the 'Circle' shape of interest by using the 'filled version' of the only one polygon with an arbitrary number 'n' of the vertices and the edges. */
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
		cout<<"\tThe boundary for the 'Circle' shape of interest is currently approximated by a polyline with 'n="<<num_samples<<"' vertices and 'n="<<num_samples<<"' edges [ 'Approximation #0' ]."<<endl;
		cout.flush();
	}
	else if(choice=='f')
	{
		/* We must approximate the 'Circle' shape by using the 'filled versions' of all triangles in a triangle fan. The reference vertex is the center '(xc,yc)'. Here, all triangles are shown in 'dark gray', and the reference vertex 
		 * is shown in 'red'. */
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
		cout<<"\tThe 'Circle' shape of interest is currently approximated by the 'filled versions' of 'n="<<num_samples<<"' triangles in a triangle fan [ 'Approximation #1' ]."<<endl;
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
		cout<<"\tThe 'Circle' shape of interest is currently approximated by the 'filled version' of only one polygon with 'n="<<num_samples<<"' vertices and 'n="<<num_samples<<"' edges [ 'Approximation #2' ]."<<endl;
		cout.flush();
	}
}
