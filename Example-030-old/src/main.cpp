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
 * main.cpp - the main function for the 'Example-030 (Old Mode)' example
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

	/* We are not using a MacOSX platform. Thus, we have a generic Unix-like platform, like the GNU Linux, or a Microsoft Windows platform. */
	#include "GL/glew.h"
	#include "GL/glut.h"
	#include "GL/gl.h"

#endif

/// The number of the samples, used for drawing the <i>'Circular Annulus'</i> shapes in the scene of interest.
int num_samples=5;

/// The rendering mode, used for drawing the <i>'Circular Annulus'</i> shapes in the scene of interest.
GLenum mode=GL_FILL;

/// The font for drawing the informative labels of interest.
static long font = (long)GLUT_BITMAP_8_BY_13;

/* Prototypes for all functions of interest! */
void initialize();
void manageKeys(unsigned char key, int x, int y);
void draw();
void resize(int w,int h);
void drawDisc(float R,float X,float Y,float Z);
void drawString(void *font,string s);

/// The main function for the <i>'Example-030 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a new window! */
	cout<<endl<<"\tThis is the 'Example-030' Example, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws three variants of the 'Circular Annulus' shape, defined as follows"<<endl<<endl;
	cout<<"\t-) the first variant of the 'Circular Annulus' shape is not a real annulus, and is formed by drawing two overwritten disks;"<<endl;
	cout<<"\t-) also the second 'Circular Annulus' shape is not a real annulus, and is formed by drawing two overwritten disks through the depth buffer technique (z-buffer);"<<endl;
	cout<<"\t-) the third 'Circular Annulus' shape is approximated by one (real) triangle strip."<<endl<<endl;
	cout<<"\tUpon request, the user can:"<<endl<<endl;
	cout<<"\t-) increase the number of samples for the disks and the triangle strip of interest, by pressing the '+' key;"<<endl;
	cout<<"\t-) decrease the number of samples for the disks and the triangle strip of interest, by pressing the '-' key;"<<endl;
	cout<<"\t-) modify the rendering mode ('wireframe' or 'filled' mode) for the disks and the triangle strip of interest by pressing the ' ' key (space)."<<endl<<endl;
	cout<<"\tIt is possible to end this program by pressing one among the 'Q' - 'q' - 'Esc' keys."<<endl<<endl;
	cout.flush();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE|GLUT_DEPTH);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-030' Example, based on the (Old Mode) OpenGL");
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
	cout<<"\tWe draw 3 variants of the 'Circular Annulus' shape through several ";
	if(mode==GL_FILL) cout<<"filled ";
	else cout<<"wireframe ";
	cout<<"disks and triangles in one (real) triangle strip, initially formed by "<<num_samples<<" samples (the minimum number as possible)."<<endl<<endl;
	cout.flush();
}

/// This function updates the viewport for the scene when it is resized. */
void resize(int w, int h)
{
	/* We update the projections and the modeling matrices! */
	glViewport(0, 0, w, h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glOrtho(0,100,0,100,-1,1);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '+' - '-' - '<space bar>' keys */
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
		
		case ' ':
		
		/* The key is ' ', thus we change the rendering mode! */
		if(mode==GL_FILL) mode=GL_LINE;
		else mode=GL_FILL;
		glutPostRedisplay();
		break;
		
		case '-':
		
		/* The key is '-', thus we decrease the number of the samples! */
		if(num_samples>5) num_samples=num_samples-1;
		else cout<<"\tThe minimum number 5 of samples is reached, and it is not possible to decrease again this number."<<endl;
		cout.flush();
		glutPostRedisplay();
		break;
		
		default:

    	/* Other keys are not important for us */
    	break;
	}
}

/// This function draws a disc of radius R and centered at the 3D point (X,Y,Z).
void drawDisc(float R,float X,float Y,float Z)
{
	/* Now, we draw a triangle fan! */
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

/// This function draws a bitmap character string in the scene.
void drawString(void *font,string s) { for(string::iterator c=s.begin();c!=s.end();c++) glutBitmapCharacter(font, *c); }

/// This function draws 3 variants of the <i>'Circular Annuluses'</i> shapes in the OpenGL window of interest.
void draw()
{
	float d=(2*PI)/(num_samples-1);

	/* Now, we draw the first (false) variant of the 'Circular Annulus' shape by using two overlapping disks. The 'red' disk is external, while the 'blue' disk is internal. If we change the rendering order, then the result will be different. */
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT,mode);
	glColor3f(1,0,0);
	drawDisc(20,25,75,0);
	glColor3f(0,0,1);
	drawDisc(10,25,75,0);
	
	/* Now, we draw the second (false) variant of the 'Circular Annulus' shape by using two overlapping disks. The 'red' disk is external, while the 'blue' disk is internal. Here, we exploit the depth test buffer (z-buffer). */
	glEnable(GL_DEPTH_TEST);
	glColor3f(1,0,0);
	drawDisc(20,75,75,0);
	glColor3f(0,0,1);
	drawDisc(10,75,75,0.5);
	glDisable(GL_DEPTH_TEST);
	
	/* Now, we draw the third  (true) variant of the 'Circular Annulus' shape by using only triangle strip. */
	glColor3f(1,0,0);
	glBegin(GL_TRIANGLE_STRIP);
	for(int i=0;i<num_samples;i++)
	{
		float t=i*d;
		glVertex3f(50+10*cos(t),25+10*sin(t),0);
		glVertex3f(50+20*cos(t),25+20*sin(t),0);
	}

	/* If we arrive here, we can draw the informative labels! */
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
    glRasterPos3f(5.0, 51.0, 0.0);
    drawString((void*)font,"Overlapping disks without");
    glRasterPos3f(8.0, 48.0, 0.0);
    drawString((void*)font,"the depth test buffer");
   	glRasterPos3f(55.0, 51.0, 0.0);
   	drawString((void*)font,"Overlapping disks with the");
   	glRasterPos3f(65.0,48.0,0.0);
   	drawString((void*)font,"depth test buffer");
   	glRasterPos3f(7,1,0);
   	drawString((void*)font,"A 'Circular Annulus' shape with only one triangle strip");
	
	/* If we arrive here, we have drawn the entire scene! */
	glFlush();
	cout<<"\tWe draw several ";
	if(mode==GL_FILL) cout<<"filled ";
	else cout<<"wireframe ";
	cout<<"disks and triangle in one (real) triangle strip, formed by "<<num_samples<<" samples, for approximating 3 variants of the 'Circular Annulus' shape."<<endl;
	cout.flush();
}
