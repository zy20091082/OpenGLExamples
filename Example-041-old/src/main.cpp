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
 * main.cpp - the main function for the 'Example-041 (Old Mode)' Test.
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

/// The number <i>'n'</i> of the vertices and the edges in the polyline, used for approximating the variant of the <i>'Spiral'</i> curve of interest.
/**
 * It is initially set to 'n=100', which is the minimum number 'n' of the vertices and the edges in the polyline of interest. It is interactively modified by pressing the '+' and the '-' keys.
 */
int num_samples=100;

/* Prototypes for all functions of interest! */
void draw();
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);

/// The main function for the <i>'Example-041 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-041' Test, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws a polyline (in 'red'), formed by an arbitrary number 'n' of the vertices and the edges, in an OpenGL window. The polyline of interest approximates a variant of the 'Spiral' curve. This latter is a curve on a plane that winds"<<endl;
	cout<<"\taround a fixed center point at a continuously increasing or decreasing distance from the point. In this test, we consider a variant of the 'Spiral' curve, defined as follows:"<<endl<<endl;
	cout<<"\tx(t) = R(t) * cos(t), y(t) = R(t) * sin(t)"<<endl<<endl<<"\tfor every 't' in '[-10 * pi, 10 * pi]', such that 'R(0) = 0.5' and 'R(t) = R(t-1) + 0.05'."<<endl<<endl;
	cout<<"\tThis test also provides a very basic interaction mechanism with the user, which can:"<<endl<<endl;
	cout<<"\t\t-) increase the number 'n' of the vertices and the edges in the polyline of interest by pressing the '+' key;"<<endl;
	cout<<"\t\t-) decrease the number 'n' of the vertices and the edges in the polyline of interest by pressing the '-' key."<<endl<<endl;
	cout<<"\tLikewise, the window of interest can be closed by pressing any among the 'Q', the 'q', and the 'Esc' keys."<<endl<<endl;
	cout.flush();
	
	/* If we arrive here, we can draw the polyline, approximating the variant of the 'Spiral' curve! */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-041' Test, based on the (Old Mode) OpenGL");
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
   	glOrtho(-20,22,-20,20,-1,1);
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	num_samples=100;
	cout<<"\tAt the beginning, the polyline, approximating the variant of the 'Spiral' curve, is formed by 'n="<<num_samples<<"' vertices and edges (thus by the minimum number 'n' as possible of the vertices and the edges)."<<endl<<endl;
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
		if(num_samples>100) num_samples=num_samples-1;
		else cout<<"\tThe minimum number 'n=100' of the vertices and the edges in the polyline of interest is reached, and it is not possible to decrease again this number."<<endl;
		cout.flush();
		glutPostRedisplay();
		break;

		default:

    	/* Other keys are not important for us! */
    	break;
	}
}

/// This function draws the polyline (in <i>'red'</i>), approximating the variant of the <i>'Spiral'</i> curve of interest, in the main OpenGL window.
void draw()
{
	int c=5;
	float radius=0.5,d=(2*c*PI)/(num_samples-1);

	/* We draw the polyline (in 'red'), approximating the variant of the 'Spiral' curve of interest, in the main OpenGL window. */
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,0,0);
	glLineWidth(1.5);
	glBegin(GL_LINE_STRIP);
	for(unsigned int j=0;j<num_samples;j++)
	{
		float t=-c*PI+j*d;
		glVertex2f(radius*cos(t),radius*sin(t));
		radius=radius+0.05;
	}
	
	/* If we arrive here, then all is ok! */
	glEnd();
	glFlush();
	cout<<"\tThe variant of the 'Spiral' curve of interest is currently approximated by a polyline with 'n="<<num_samples<<"' vertices and 'n="<<num_samples<<"' edges."<<endl;
	cout.flush();
}
