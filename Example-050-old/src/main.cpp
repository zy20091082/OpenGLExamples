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
 * main.cpp - the main function for the 'Example-050 (Old Mode)' example
 *******************************************************************************************************************************************************/

/* First, we must understand which platform we are using. */
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <string>
#include <cfloat>
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

/// The rotation angle along the x-axis.
float Xangle=10.0;

/// The rotation angle along the y-axis.
float Yangle=0.0;

/// The rotation angle along the z-axis.
float Zangle=0.0;

/// The number of the samples.
unsigned int num_samples=3;

/* Prototypes for all functions of interest! */
void initialize();
void manageKeys(unsigned char key, int x, int y);
void draw();
void resize(int w,int h);
float evaluateSlide(float v);

/// The main function for the <i>'Example-050 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a new window! */
	cout<<endl<<"\tThis is the 'Example-050' Example, based on the (Old Mode) OpenGL"<<endl<<endl;
	cout.flush();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-050' Example, based on the (Old Mode) OpenGL");
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
	/* We update the projections and the modeling matrices! */
	glViewport(0, 0, w, h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glFrustum(-5.0, 5.0, -10.0, 10.0, 4.0, 100.0);
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'Esc' - 'q' - 'Q' - '+' - '-' - 'x' - 'X' - 'y' - 'Y' - 'z' - 'Z' keys */
	switch (key)
	{
		case 27:
	
		/* The key is 'Esc', thus we can exit! */
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case 'q':
		
		/* The key is 'q', thus we can exit! */
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case 'Q':
		
		/* The key is 'Q', thus we can exit! */
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
		if(num_samples>3) num_samples=num_samples-1;
		else cout<<"\tThe minimum number 3 of the samples is reached"<<endl;
		cout.flush();
		glutPostRedisplay();
		break;
		
		case 'x':
		
		/* The key is 'x', thus, we decrease the rotation angle along the x-axis. */
		Xangle -= 5.0;
		if(Xangle < 0.0) Xangle += 360.0;
        glutPostRedisplay();
        break;
        
        case 'y':
		
		/* The key is 'y', thus, we decrease the rotation angle along the y-axis. */
		Yangle -= 5.0;
		if(Yangle < 0.0) Yangle += 360.0;
        glutPostRedisplay();
        break;
        
        case 'z':
        
        /* The key is 'z', thus, we decrease the rotation angle along the z-axis. */
		Zangle -= 5.0;
		if(Zangle < 0.0) Zangle += 360.0;
        glutPostRedisplay();
        break;
        
        case 'X':
		
		/* The key is 'X', thus, we increase the rotation angle along the x-axis. */
        Xangle += 5.0;
		if (Xangle > 360.0) Xangle -= 360.0;
        glutPostRedisplay();
        break;
        
        case 'Y':
		
		/* The key is 'Y', thus, we increase the rotation angle along the Y-axis. */
        Yangle += 5.0;
		if (Yangle > 360.0) Yangle -= 360.0;
        glutPostRedisplay();
        break;
        
        case 'Z':
		
		/* The key is 'Z', thus, we increase the rotation angle along the z-axis. */
        Zangle += 5.0;
		if (Zangle > 360.0) Zangle -= 360.0;
        glutPostRedisplay();
        break;
		
		default:

    	/* Other keys are not important for us */
    	break;
	}
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	Xangle=10.0;
	Yangle=0.0;
	Zangle=0.0;
	num_samples=3;
	cout<<"\tWe draw the wireframe version of the 'Slide' shape of interest. It is possible to::"<<endl<<endl;
	cout<<"\t-) modify the number of the samples in the 'Slide' shape by pressing the '-' (decrease) and the '+' (increase) keys"<<endl;
	cout<<"\t-) rotate the 'Slide' shape along the x-axis by pressing the 'x' (decrease the angle) and the 'X' (increase the angle) keys"<<endl;
	cout<<"\t-) rotate the 'Slide' shape along the y-axis by pressing the 'y' (decrease the angle) and the 'Y' (increase the angle) keys"<<endl;
	cout<<"\t-) rotate the 'Slide' shape along the z-axis by pressing the 'z' (decrease the angle) and the 'Z' (increase the angle) keys"<<endl<<endl;
	cout.flush();
}

/// This function evaluates the profile for the <i>'Slide'</i> shape at a given point.
float evaluateSlide(float v) { return ( 0.03875*pow(v,2)-1.225*v+10.0); }

/// This function draws the <i>'Slide'</i> shape in the OpenGL window of interest by using the preferences, chosen by the user.
void draw()
{
	float dv=40.0/(num_samples-1);

	/* Now, we draw the 'Slide' shape in the OpenGL window of interest by using the preferences, chosen by the user. */
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
   	glTranslatef(0.0, 0.0, -30.0);
   	glRotatef(Zangle, 0.0, 0.0, 1.0);
   	glRotatef(Yangle, 0.0, 1.0, 0.0);
  	glRotatef(Xangle, 1.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glColor3f(0,0,1);
	glLineWidth(1);
	glPointSize(5);
	glBegin(GL_QUAD_STRIP);
	glVertex3f(5,0,-20);
	glVertex3f(-5,0,-20);
	for(unsigned int k=0;k<num_samples;k++)
	{
		float v=-20.0+k*dv;
		float p=evaluateSlide(v);
		glVertex3f(5,p,v);
		glVertex3f(-5,p,v);
	}
	
	/* If we arrive here, we complete the two vertical basis (front and back). */
	glVertex3f(5,0,20);
	glVertex3f(-5,0,20);
	glEnd();
	
	/* If we arrive here, we draw the side #0 of the 'Slide' shape. */
	glBegin(GL_QUAD_STRIP);
	for(unsigned int k=0;k<num_samples;k++)
	{
		float v=-20.0+k*dv;
		float p=evaluateSlide(v);
		glVertex3f(5,p,v);
		glVertex3f(5,0,v);
	}
	
	/* If we arrive here, we draw the side #1 of the 'Slide' shape. */
	glEnd();
	glBegin(GL_QUAD_STRIP);
	for(unsigned int k=0;k<num_samples;k++)
	{
		float v=-20.0+k*dv;
		float p=evaluateSlide(v);
		glVertex3f(-5,p,v);
		glVertex3f(-5,0,v);
	}
	
	/* Now, we add the bottom basis. */
	glEnd();
	glBegin(GL_QUAD_STRIP);
	for(unsigned int k=0;k<num_samples;k++)
	{
		float v=-20.0+k*dv;
		glVertex3f(5,0,v);
		glVertex3f(-5,0,v);
	}
	
	/* Finally, the scene is complete */
	glEnd();
	cout<<"\tApproximated and drawn the 'Slide' shape by using "<<num_samples<<" samples, rotation angle around the x-axis: "<<Xangle<<", rotation angle around the y-axis: "<<Yangle<<", rotation angle around the z-axis: "<<Zangle<<endl;
	glFlush();	
}
