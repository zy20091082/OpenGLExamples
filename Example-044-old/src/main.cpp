/*******************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 * 
 * Last update: February 2017
 *
 * This program is Free Software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.                                       
 *                                                                         
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License (http://www.gnu.org/licenses/gpl.txt) for more details.
 * 
 * main.cpp - the main function for the 'Example-044 (Old Mode)' example
 *******************************************************************************************************************************************************/

/* First, we must understand which platform we are using. */
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <string>
#include <cfloat>
#define PI 3.14159265358979324
using namespace std;
#ifdef __APPLE__

	/* We are using a MacOSX platform (Macintosh) */
	#include "GL/glew.h"
	#include "GLUT/glut.h"
	#include "OpenGL/gl.h"

#else

	/* We are not using a MacOSX platform. Thus, we have a generic Unix-like platform, like the GNU Linux, or a Microsoft Windows platform. */
	#include "GL/glew.h"
	#include "GL/glut.h"
	#include "GL/gl.h"

#endif

/// The number of the samples, used for drawing the scene of interest.
int num_samples=5;

/// The rendering mode for the scene of interest (wireframe or filled).
GLenum mode=GL_FILL;

/// The font for drawing the informative labels of interest.
static long font = (long)GLUT_BITMAP_8_BY_13;

/* Prototypes for all functions of interest! */
void initialize();
void manageKeys(unsigned char key, int x, int y);
void draw();
void resize(int w,int h);
void drawString(void *font,string s,GLfloat x,GLfloat y);

/// The main function for the <i>'Example-044 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a new window! */
	cout<<endl<<"\tThis is the 'Example-044' Example, based on the (Old Mode) OpenGL"<<endl<<endl;
	cout.flush();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(560,350);
	glutCreateWindow("The 'Example-044' Example, based on the (Old Mode) OpenGL");
	glutReshapeFunc(resize);
	glutKeyboardFunc(manageKeys);
	glutDisplayFunc(draw);
	glewExperimental = GL_TRUE;
   	glewInit();
   	initialize(); 
	glutMainLoop();
	return EXIT_SUCCESS;
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	num_samples=5;
	mode=GL_FILL;
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '+' - '-' - 'r' keys */
	switch (key)
	{
		case 'q':
	
		/* The key is 'q' */
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case 'Q':
	
		/* The key is 'Q' */
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case 27:
	
		/* The key is 'Esc' */
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case '+':
		
		/* The key is '+', thus we increase the number of the samples! */
		num_samples=num_samples+1;
		glutPostRedisplay();
		break;
		
		case '-':
		
		/* The key is '-', thus we decrease the number of the samples! */
		if(num_samples>5) num_samples=num_samples-1;
		else cout<<"\tThe minimum number 5 of samples is reached"<<endl;
		cout.flush();
		glutPostRedisplay();
		break;
		
		case 'r':
		
		/* The key is 'r', thus we change the rendering mode to be used! */
		if(mode==GL_FILL) mode=GL_LINE;
		else mode=GL_FILL;
		glutPostRedisplay();
		break;
		
		default:

    	/* Other keys are not important for us */
    	break;
	}
}

/// This function updates the viewport for the scene when it is resized. */
void resize(int w, int h)
{
	/* We update the projections and the modeling matrices! */
	glViewport(0, 0, w, h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	gluOrtho2D(-180.0,150.0,-80.0,70.0);
	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function draws three versions of the <i>'Moon'</i> shape in the OpenGL window of interest by using the preferences, chosen by the user.
void draw()
{
	float d=PI/(num_samples-1);
	float d1=120.0/(num_samples-1);
	
	/* Now, we draw three versions of the <i>'Moon'</i> shape in the OpenGL window of interest by using the preferences, chosen by the user. */
	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK,mode);
	glColor3f(1,0,0);
	glLineWidth(1);
	
	/* Now, we draw the first version of the 'Moon' shape. */
	glBegin(GL_QUAD_STRIP);
	for(unsigned int k=0;k<num_samples;k++)
	{
		glVertex2f(-110+60*cos(PI/2+k*d),60*sin(PI/2+k*d));
		glVertex2f(-110+30*cos(PI/2+k*d),60*sin(PI/2+k*d));
	}
	
	/* Now, we draw the second version of the 'Moon' shape.*/
	glEnd();
	glBegin(GL_QUAD_STRIP);
	for(unsigned int k=0;k<num_samples;k++)
	{
		glVertex2f(60*cos(PI/2+k*d),60*sin(PI/2+k*d));
		glVertex2f(0,60-k*d1);
	}
	
	/* Now, we draw the third version of the 'Moon' shape. */
	glEnd();
	glBegin(GL_QUAD_STRIP);
	for(unsigned int k=0;k<num_samples;k++)
	{
		glVertex2f(110+60*cos(PI/2+k*d),60*sin(PI/2+k*d));
		glVertex2f(110-30*cos(PI/2+k*d),60*sin(PI/2+k*d));
	}
	
	/* If we arrive here, we can write the labels, and the scene will be complete! */
	glEnd();
	glColor3f(0,0,0);
	drawString((void*)font,"crescent moon",-170.0,-70.0);
	drawString((void*)font,"half moon",-60.0,-70.0);
	drawString((void*)font,"three quarter moon",60.0,-70.0);
	glFlush();
	cout<<"\tApproximated the ";
	if(mode==GL_FILL) cout<<"filled ";
	else cout<<"wired ";
	cout<<"versions of the 'Moon' shape by using "<<num_samples<<" samples"<<endl;
	cout.flush();
}

/// This function draws a string (label) in the OpenGL scene of interest.
void drawString(void *font,string s,GLfloat x,GLfloat y)
{
	glRasterPos2f(x,y);
	for(string::iterator c=s.begin();c!=s.end();c++) glutBitmapCharacter(font, *c); 
}

