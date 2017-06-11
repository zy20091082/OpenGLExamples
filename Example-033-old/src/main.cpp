/*******************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 * 
 * Last update: June 2017
 *
 * This program is Free Software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.                                       
 *                                                                         
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License (http://www.gnu.org/licenses/gpl.txt) for more details.
 * 
 * main.cpp - the main function for the 'Example-033 (Old Mode)' Test.
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

/// The number <i>'n'</i> of the vertices and the edges in the polyline, used for approximating the <i>'Helix-like'</i> curve of interest.
/**
 * It is initially set to 'n=10', which is the minimum number 'n' of the vertices and the edges. It is interactively modified by pressing the '+' and the '-' keys.
 */
unsigned int num_samples=10;

/// This flag indicates which variant of the <i>'Helix-like'</i> curve must be drawn.
/**
 * It may assume the following values:
 *
 * -) 0, if the 'Variant #0' of the 'Helix-like' curve (evolving along the z-axis) must be drawn. It is defined by: x(t) = 40 * cos(t), y(t) = 40 * sin(t), z(t) = t, for every 't' in '[-10*pi,10*pi]'.
 * -) 1: if the 'Variant #1' of the 'Helix-like' curve (evolving along the x-axis) must be drawn. It is defined by: x(t) = t, y(t) = 40 * cos(t), z(t) = 40 * sin(t), for every 't' in '[-10*pi,10*pi]'.
 * -) 2: if the 'Variant #2' of the 'Helix-like' curve (evolving along the y-axis) must be drawn. It is defined by: x(t) = 40 * cos(t), y(t) = t, z(t) = 40 * sin(t), for every 't' in '[-10*pi,10*pi]'.
 *
 * The user can choose the variant of interest by pressing cyclically the ' ' (space) key.
 */
int orient=0;

/* Prototypes for all functions of interest! */
void draw();
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);

/// The main function for the <i>'Example-033 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-033' Test, based on the (Old Mode) OpenGL."<<endl;
    cout<<"\tIt draws 3 variants of the 'Helix-like' curve with center at the origin of the 3D space in an OpenGL window. Broadly speaking, any 'Helix-like' curve turns around an axis at a constant or continuously varying"<<endl;
    cout<<"\tdistance, while moving parallel to the axis."<<endl<<endl;
    cout<<"\tIn this test, we consider all variants of the 'Helix-like' curve, evolving along 3 Cartesian axes. Every variant of interest is approximated by a polyline (in 'red'), formed by an arbitrary number 'n' of the"<<endl; 
    cout<<"\tvertices and the edges, and is drawn by using the same orthographic projection viewing box '[-50,50]' x '[-50,50]' x '[-50,50]'."<<endl<<endl;
    cout<<"\tHere, the 'Variant #0' of the 'Helix-like' curve, evolving along the z-axis, is defined as follows:"<<endl<<endl;
	cout<<"\tx(t) = 40 * cos(t), y(t) = 40 * sin(t), z(t) = t"<<endl<<endl<<"\tfor every 't' in '[-10*pi,10*pi]'."<<endl<<endl;
	cout<<"\tInstead, the 'Variant #1' of the 'Helix-like' curve, evolving along the x-axis, is defined as follows:"<<endl<<endl;
	cout<<"\tx(t) = t, y(t) = 40 * cos(t), z(t) = 40 * sin(t)"<<endl<<endl<<"\tfor every 't' in '[-10*pi,10*pi]'."<<endl<<endl;
	cout<<"\tFinally, the 'Variant #2' of the 'Helix-like' curve, evolving along the y-axis, is defined as follows:"<<endl<<endl;
	cout<<"\tx(t) = 40 * cos(t), y(t) = t, z(t) = 40 * sin(t)"<<endl<<endl<<"\tfor every 't' in '[-10*pi,10*pi]'."<<endl<<endl;
	cout<<"\tHere, the user cannot modify the projection and the size for 3 variants of the 'Helix-like' curve, since they are fixed in advance. Instead, the user can:"<<endl<<endl;
	cout<<"\t\t-) increase the number 'n' of the vertices and the edges in the polyline of interest by pressing the '+' key;"<<endl;
	cout<<"\t\t-) decrease the number 'n' of the vertices and the edges in the polyline of interest by pressing the '-' key;"<<endl;
	cout<<"\t\t-) choose what variant of the 'Helix-like' curve must be drawn by pressing cyclically the ' ' (space) key. At each choice, the number 'n' of the samples is resetted to the default value '10'."<<endl<<endl;
	cout<<"\tLikewise, the window of interest can be closed by pressing any among the 'Q', the 'q', and the 'Esc' keys."<<endl<<endl;
	cout.flush();
	
	/* If we arrive here, we can draw the polyline, approximating the 'Helix-like' curve! */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-033' Test, based on the (Old Mode) OpenGL");
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
   	glOrtho(-50,50,-50,50,-50,50);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	num_samples=10;
	orient=0;
	cout<<"\tAt the beginning, the polyline, approximating the 'Variant #"<<orient<<"' of the 'Helix-like' curve, is formed by 'n="<<num_samples<<"' vertices and edges (thus by the minimum number 'n' as possible of the vertices and the edges)."<<endl<<endl;
	cout.flush();
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '+' - '-' - ' ' (space) keys. */
	switch (key)
	{
		case 'q':
	
		/* The key is 'q', thus we can exit from this program. */
		cout<<endl<<"\tThis program is closing correctly ... "<<endl<<endl;
		cout << "\tPress the RETURN key to finish ... ";
		cin.get();
		#ifndef _MSC_VER
			cout << endl;
			cout.flush();
		#endif
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case 'Q':
	
		/* The key is 'Q', thus we can exit from this program. */
		cout<<endl<<"\tThis program is closing correctly ... "<<endl<<endl;
		cout << "\tPress the RETURN key to finish ... ";
		cin.get();
		#ifndef _MSC_VER
			cout << endl;
			cout.flush();
		#endif
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case 27:
	
		/* The key is 'Esc', thus we can exit from this program. */
		cout<<endl<<"\tThis program is closing correctly ... "<<endl<<endl;
		cout << "\tPress the RETURN key to finish ... ";
		cin.get();
		#ifndef _MSC_VER
			cout << endl;
			cout.flush();
		#endif
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case '+':
		
		/* The key is '+', thus we increase the number 'n' of the vertices and the edges in the polyline of interest! */
		num_samples=num_samples+1;
		glutPostRedisplay();
		break;
		
		case '-':
		
		/* The key is '-', thus we decrease the number 'n' of the vertices and the edges (if possible) in the polyline of interest. */
		if(num_samples>10) num_samples=num_samples-1;
		else cout<<"\tThe minimum number 'n=10' of the vertices and the edges in the polyline of interest is reached, and it is not possible to decrease again this number."<<endl;
		cout.flush();
		glutPostRedisplay();
		break;
		
		case ' ':
		
		/* The key is ' ' (space), thus we change the variant of the 'Helix-like' curve to be drawn. */
		orient=(orient+1)%3;
		num_samples=10;
		glutPostRedisplay();
		break;

		default:

    	/* Other keys are not important for us! */
    	break;
	}
}

/// This function draws the polyline (in <i>'red'</i>), approximating the <i>'Helix-like'</i> curve of interest, in the main OpenGL window.
void draw()
{
	/* We draw the polyline (in 'red'), approximating the 'Helix-like' curve of interest, in the main OpenGL window. */
	float d=(20*PI)/(num_samples-1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,0,0);
	glBegin(GL_LINE_STRIP);
	if(orient==0)
	{
		/* Now, we must draw the 'Variant #0' of the 'Helix-like' curve, evolving along the z-axis. */
		for(unsigned int k=0;k<num_samples;k++)
		{
			float t=-10*PI+k*d;
			glVertex3f(40*cos(t),40*sin(t),t);
		}	
	}
	else if(orient==1)
	{
		/* Now, we must draw the 'Variant #1' of the 'Helix-like' curve, evolving along the x-axis. */
		for(unsigned int k=0;k<num_samples;k++)
		{
			float t=-10*PI+k*d;
			glVertex3f(t,40*cos(t),40*sin(t));
		}
	}
	else
	{
		/* Now, we must draw the 'Variant #2' of the 'Helix-like' curve, evolving along the y-axis. */
		for(unsigned int k=0;k<num_samples;k++)
		{
			float t=-10*PI+k*d;
			glVertex3f(40*cos(t),t,40*sin(t));
		}
	}
	
	/* If we arrive here, we have finished! */
	glEnd();
	glFlush();
	cout<<"\tThe 'Variant #"<<orient<<"' of the 'Helix-like' curve of interest is currently approximated by a polyline with 'n="<<num_samples<<"' vertices and 'n="<<num_samples<<"' edges."<<endl;
	cout.flush();
}
