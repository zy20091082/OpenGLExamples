/*******************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 * 
 * Last update: January 2017
 *
 * This program is Free Software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.                                       
 *                                                                         
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License (http://www.gnu.org/licenses/gpl.txt) for more details.
 * 
 * main.cpp - the main function for the 'Example-031 (Old Mode)' example
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

/// The number of the samples, used for drawing the scene of interest.
int num_samples=5;

/// The rendering mode for the scene of interest (wireframe or filled).
GLenum mode=GL_FILL;

/// The rendering mode for the disks of interest (0: rendering the red disc first, then the blue disc | 1: rendering the blue disc first, then the red disc).
int odmode=0;

/// The font for drawing the informative labels of interest.
static long font = (long)GLUT_BITMAP_8_BY_13;

/* Prototypes for all functions of interest! */
void initialize();
void manageKeys(unsigned char key, int x, int y);
void draw();
void resize(int w,int h);
void drawDisc(float R,float X,float Y,float Z);
void drawString(void *font,string s);

/// The main function for the <i>'Example-031 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a new window! */
	cout<<endl<<"\tThis is the 'Example-031' Example, based on the (Old Mode) OpenGL"<<endl<<endl;
	cout.flush();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE|GLUT_DEPTH);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-031' Example, based on the (Old Mode) OpenGL");
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
	cout<<"\tWe draw three examples of the circular annuluses, defined as follows"<<endl<<endl;
	cout<<"\t-) the first 'annulus' is not a real annulus, and is formed by two overwritten discs."<<endl; 
	cout<<"\t-) Also the second 'annulus' is not a real annulus. It is drawn by using the depth buffer, and is formed by two overwritten discs."<<endl;
	cout<<"\t-) The third annulus is real, and is formed by only one triangle strip."<<endl<<endl;
	cout<<"\tIt is possible to modify the number of the samples (by pressing the '+' and '-' keys), as well as the rendering mode (by pressing the ' ' key) and the order rendering for the disks (by pressing the 'o' key)"<<endl<<endl;
	cout.flush();
	glClearColor(1.0, 1.0, 1.0, 0.0);
	num_samples=5;
	mode=GL_FILL;
	odmode=0;
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
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '+' - '-' - '<space bar>' - 'o' keys */
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
		else cout<<"\tThe minimum number 5 of samples is reached"<<endl;
		cout.flush();
		glutPostRedisplay();
		break;
		
		case 'o':
		
		/* The key is 'o', thus we change the rendering order for the disks of interest! */
		odmode=( (odmode+1)%2);
		glutPostRedisplay();
		
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

/// This function draws the 'false' and the 'true' circular annuluses in the OpenGL window of interest.
void draw()
{
	float d=(2*PI)/(num_samples-1);

	/* Now, we draw the first 'false' circular annulus by using two overlapping disks. The red disk is external, while the blue disk is internal. If we change the rendering order, then the result will be different. */
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT,mode);
	if(odmode==0)
	{
		glColor3f(1,0,0);
		drawDisc(20,25,75,0);
		glColor3f(0,0,1);
		drawDisc(10,25,75,0);
	}
	else
	{
		glColor3f(0,0,1);
		drawDisc(10,25,75,0);
		glColor3f(1,0,0);
		drawDisc(20,25,75,0);
	}
	
	/* Now, we draw the second 'false' circular annulus by using two overlapping disks. The red disk is external, while the blue disk is internal. Here, we exploit the depth test buffer. */
	glEnable(GL_DEPTH_TEST);
	if(odmode==0)
	{
		glColor3f(1,0,0);
		drawDisc(20,75,75,0);
		glColor3f(0,0,1);
		drawDisc(10,75,75,0.5);
	}
	else
	{
		glColor3f(0,0,1);
		drawDisc(10,75,75,0.5);
		glColor3f(1,0,0);
		drawDisc(20,75,75,0);
	}
	glDisable(GL_DEPTH_TEST);
	
	/* Now, we draw the 'true' circular annulus by using only triangle strip. */
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
   	glRasterPos3f(10,1,0);
   	drawString((void*)font,"A real circular annulus with only one triangle strip");
	
	/* If we arrive here, we have drawn the entire scene! */
	glFlush();
	cout<<"\tApproximated and drawn the scene of interest with "<<num_samples<<" samples"<<endl;
	cout.flush();
}
