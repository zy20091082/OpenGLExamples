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
 * main.cpp - the main function for the 'Example-032 (Old Mode)' Test.
 *******************************************************************************************************************************************************/

/* First, we must understand which platform we are using. */
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <string>
#define PI 3.14159265358979324
using namespace std;
#ifdef __APPLE__

	/* We are using a MacOSX platform (Macintosh) */
	#include "GL/glew.h"
	#include "GLUT/glut.h"
	#include "OpenGL/gl.h"

#else

	/* We are not using a MacOSX platform. Thus, we have a generic Unix-like platform, like the GNU/Linux, or a Microsoft Windows platform. */
	#include "GL/glew.h"
	#include "GL/glut.h"
	#include "GL/gl.h"

#endif

/// The number <i>'n'</i> of the samples in the triangle fans, approximating the <i>'Bullseye'</i> shape.
/**
 * It is initially set to 'n=5', which is the minimum number of the vertices (including the center) for constructing the triangle fans of interest, approximating the 'Bullseye' shape.
 */
unsigned int num_samples=5;

/// The setting for rendering all triangles in the triangle fans, used for approximating the <i>'Bullseye'</i> shape.
/**
 * The value of this flag may be one of the following values:
 *
 * -) the 'GL_LINE' value, used for rendering the 'wireframe versions' for all triangles in the triangle fans of interest;
 * -) the 'GL_FILL' value, used for rendering the 'filled versions' for all triangles in the triangle fans of interest.
 *
 * It is possible to cycle between these 2 renderings by pressing the ' ' (space) key.
 */
GLenum mode=GL_FILL;

/* Prototypes for all functions of interest! */
void initialize();
void manageKeys(unsigned char key, int x, int y);
void draw();
void resize(int w,int h);
void drawDisc(float R,float X,float Y,float Z);

/// The main function for the <i>'Example-032 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a new window! */
	cout<<endl<<"\tThis is the 'Example-032' Test, based on the (Old Mode) OpenGL."<<endl<<endl;
	cout<<"\tIt draws an approximation of the 'Bullseye' shape in an OpenGL window. A generic 'Bullseye' shape is defined by several concentric 'Circle' shapes (disks) of different colors, same center '(xc,yc)', and radii of different"<<endl;
	cout<<"\tlengths. Recall that the 'Circle' shape with radius 'R' and center '(xc,yc)' is defined as follows:"<<endl<<endl;
	cout<<"\t| x(t) - xc | <= R * cos(t), | y(t) - yc | <= R * sin(t)"<<endl<<endl<<"\tfor any 'R>0', and for every 't' in '[-pi,pi]'."<<endl<<endl;
	cout<<"\tIn other words, any 'Bullseye' shape is the union of all circular crowns, bounded by the 'Circle' curves, that are the boundary for the pairs of the consecutive disks in the 'Bullseye' shape, if sorted with respect to the"<<endl;
	cout<<"\tlengths of their radii. The 'Bullseye' shape often represents the targets in the shooting and the archery competitions."<<endl<<endl;
	cout<<"\tHere, we restrict our attention to the approximation of the 'Bullseye' shape, formed by 5 concentric disks. However, the approximation of interest is not 'real', since it is the result of drawing the approximations of 5"<<endl;
	cout<<"\t'Circle' shapes, placed at different z-depths. In this context, the scene is drawn by using the orthographic projection, such that the centers of the 'Circle' shapes are projected on the same point. Every 'Circle' shape"<<endl;
	cout<<"\tof interest is approximated by a triangle fan of 'n' vertices (including the center), and is drawn by using the z-buffer (depth test) technique. Thus, the result will be a 'false' version of the 'Bullseye' shape, and will"<<endl;
	cout<<"\tbe always the same, despite the rendering order of 5 'Circle' shapes."<<endl<<endl;
	cout<<"\tHere, the user cannot modify the radius, the number, and the colors for the 'Circle' shapes of interest, since they are fixed in advance. Instead, the user can:"<<endl<<endl;
	cout<<"\t\t-) increase the number 'n' of all vertices in the triangle fans of interest by pressing the '+' key;"<<endl;
	cout<<"\t\t-) decrease the number 'n' of all vertices in the triangle fans of interest by pressing the '-' key;"<<endl;
	cout<<"\t\t-) choose to render the 'wireframe' or the 'filled versions' for all triangles in the triangle fans of interest by pressing cyclically the ' ' (space) key."<<endl<<endl;
	cout<<"\tLikewise, the window of interest can be closed by pressing any among the 'Q', the 'q', and the 'Esc' keys."<<endl<<endl;
	cout.flush();

	/* If we arrive here, we can draw the approximation of the 'Bullseye' shape in the scene. */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE|GLUT_DEPTH);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-032' Test, based on the (Old Mode) OpenGL");
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
	cout<<"\tAt the beginning, the 'Bullseye' shape is approximated by the ";
	if(mode==GL_FILL) cout<<"'filled versions' ";
	else cout<<"'wireframe versions' ";
	cout<<"of several triangles in 5 triangle fans with 'n="<<num_samples<<"' vertices (thus with the minimum number 'n' as possible of the vertices)."<<endl<<endl;
	cout.flush();
}

/// This function updates the viewport for the scene when it is resized. */
void resize(int w, int h)
{
	/* We update the projection and the modeling matrices! */
	glViewport(0, 0, w, h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glOrtho(-100,100,-100,100,-100,10);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function draws a triangle fan, approximating a given <i>'Circle'</i> shape.
void drawDisc(float R,float X,float Y,float Z)
{
	/* Now, we draw a triangle fan with radius 'R' and center '(X,Y,Z)'. */
	float d=(2*PI)/(num_samples-1);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(X,Y,Z);
	for(int i=0;i<num_samples;i++)
	{
		float t=i*d;
		glVertex3f(X+R*cos(t),Y+R*sin(t),Z);
	}
	
	/* If we arrive here, all is ok. */
	glEnd();
}

/// This function draws the approximation of the <i>'Bullseye'</i> shape in the OpenGL window of interest by using the rendering settings, chosen by the user.
void draw()
{
	/* Here, the approximation of interest for the 'Bullseye' shape is not 'real', since it is the result of drawing the approximations of 5 'Circle' shapes, placed at different z-depths. In this context, the scene is drawn by using the orthographic
	 * projection, such that the centers of the 'Circle' shapes are projected on the same point. Every 'Circle' shape of interest is approximated by a triangle fan of 'n' vertices (including the center), and is drawn by using the z-buffer (depth test) 
	 * technique. Thus, the result will be a 'false' version of the 'Bullseye' shape, and will be always the same, despite the rendering order of 5 'Circle' shapes. */
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT,mode);
	glEnable(GL_DEPTH_TEST);
	glColor3f(0,0,0);
	drawDisc(95,0,0,10);
	glColor3f(1,1,0.5);
	drawDisc(20,0,0,80);
	glColor3f(0,0,1);
	drawDisc(60,0,0,40);
	glColor3f(0,1,0);
	drawDisc(80,0,0,20);
	glColor3f(1,0,0);
	drawDisc(40,0,0,60);
	glDisable(GL_DEPTH_TEST);
	glFlush();
	
	/* If we arrive here, all is ok! */
	glFlush();
	cout<<"\tThe 'Bullseye' shape is currently approximated by the ";
	if(mode==GL_FILL) cout<<"'filled versions' ";
	else cout<<"'wireframe versions' ";
	cout<<"of several triangles in 5 triangle fans with 'n="<<num_samples<<"' vertices (including the center)."<<endl;
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
		
		/* The key is '+', thus we increase the number 'n' of the vertices (including the center) in the triangle fans approximating 5 'Circle' shapes in the 'Bullseye' shape of interest! */
		num_samples=num_samples+1;
		glutPostRedisplay();
		break;
		
		case '-':
		
		/* The key is '-', thus we decrease (if possible) the number 'n' of the vertices (including the center) in the triangle fans, approximating 5 'Circle' shapes in the 'Bullseye' shape of interest! */
		if(num_samples>5) num_samples=num_samples-1;
		else cout<<"\tThe minimum number 'n=5' of the vertices in the triangle fans of interest is reached, and it is not possible to decrease again this number."<<endl;
		cout.flush();
		glutPostRedisplay();
		break;
		
		case ' ':
		
		/* The key is ' ' (space), thus we change the rendering mode! */
		if(mode==GL_FILL) mode=GL_LINE;
		else mode=GL_FILL;
		glutPostRedisplay();
		break;

		default:

    	/* Other keys are not important for us! */
    	break;
	}			
}
