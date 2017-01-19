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
 * main.cpp - the main function for the 'Example-037 (Old Mode)' example
 *******************************************************************************************************************************************************/
 
/* First, we must understand which platform we are using. */
#include <cstdlib>
#include <iostream>
#include <cmath>

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

/// This flag indicates what rendering mode we must exploit.
int mode=0;

/// This flag indicates what tessellation we must exploit.
int tessellation=0;

/* Prototypes for all functions of interest! */
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);
void draw();

/// The main function for the <i>'Example-037 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a new window! */
	cout<<endl<<"\tThis is the 'Example-037' Example, based on the (Old Mode) OpenGL"<<endl<<endl;
	cout.flush();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-037' Example, based on the (Old Mode) OpenGL");
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
	cout<<"\tWe draw a letter 'A', choose the rendering mode by pressing the ' ' key, and the tessellation by pressing the 't' key."<<endl<<endl;
	cout.flush();
	glClearColor(0.0, 0.0, 0.0, 0.0);
	mode=0;
	tessellation=0;
}

// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '<space bar>' keys */
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
		
		case ' ':
		
		/* The key is ' ', thus we change the rendering mode of interest! */
		mode=(mode+1)%3;
		glutPostRedisplay();
		break;
		
		case 't':
		
		/* The key is 't', thus we change the tessellation to be rendered! */
		tessellation=(tessellation+1)%3;
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
   	gluOrtho2D(-35,35,-5,65);
}

/// This function draws the letter 'A' in the OpenGL scene of interest by using the rendering mode, requested by the user.
void draw()
{
	/* First, we clear everything. Then, we draw the letter 'A' of interest. */
	glClear(GL_COLOR_BUFFER_BIT);
	if(mode==0) { glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); }
   	if(mode==1) { glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); }
   	if(mode==2) { glPolygonMode(GL_FRONT_AND_BACK,GL_POINT); }
   	glLineWidth(3);
   	glPointSize(8);
   	if(tessellation==0)
   	{
   		/* We draw a basic tessellation, formed only by 11 independent triangles. */
   		glBegin(GL_TRIANGLES);
   	
	   	/* Drawing the triangle #0 (A-B-E) [blue] */
	   	glColor3f(0.0, 0.0, 1.0);
	   	glVertex2f(-15,0);
	   	glVertex2f(-25,0);
	   	glVertex2f(-10.5,15);
	   	
	   	/* Drawing the triangle #1 (B-E-H) [light gray] */
	   	glColor3f(0.8,0.8,0.8);
	   	glVertex2f(-25,0);
	   	glVertex2f(-10.5,15);
	   	glVertex2f(-7.5,25);
	   	
	   	/* Drawing the triangle #2 (I-H-B) [cyan] */
	   	glColor3f(0.0, 1.0, 1.0);
	   	glVertex2f(-7,60);
	   	glVertex2f(-7.5,25);
	   	glVertex2f(-25,0);
	   	
	   	/* Drawing the triangle #3 (H-E-F) [yellow] */
	   	glColor3f(1.0, 1.0, 0.0);
	   	glVertex2f(-7.5,25);
	   	glVertex2f(-10.5,15);
	   	glVertex2f(10.5,15);
	   	
	   	/* Drawing the triangle #4 (H-G-F) [magenta] */
	   	glColor3f(1.0, 0.0, 1.0);
	   	glVertex2f(-7.5,25);
	   	glVertex2f(7.5,25);
	   	glVertex2f(10.5,15);
	   	
	   	/* Drawing the triangle #5 (F-G-D) [gray] */
	   	glColor3f(0.5, 0.5, 0.5);
	   	glVertex2f(10.5,15);
	   	glVertex2f(7.5,25);
	   	glVertex2f(25,0);
	   	
	   	/* Drawing the triangle #6 (F-C-D) [red] */
	   	glColor3f(1.0, 0.0, 0.0);
	   	glVertex2f(10.5,15);
	   	glVertex2f(15,0);
	   	glVertex2f(25,0);
	   	
	   	/* Drawing the triangle #7 (L-G-D) [green] */
	   	glColor3f(0.0, 1.0, 0.0);
	   	glVertex2f(7,60);
	   	glVertex2f(7.5,25);
	   	glVertex2f(25,0);
	   	
	   	/* Drawing the triangle #8 (I-L-M) [brown] */
	   	glColor3f(0.60, 0.40, 0.12);
	   	glVertex2f(-7,60);
	   	glVertex2f(7,60);
	   	glVertex2f(0,50);
	   	
	   	/* Drawing the triangle #9 (I-M-H) [purple]. */
	   	glColor3f(0.98, 0.625, 0.12);
	   	glVertex2f(-7,60);
	   	glVertex2f(0,50);
	   	glVertex2f(-7.5,25);
	   	
	   	/* Drawing the triangle #10 (M-G-L). */
	   	glColor3f(0.5, 0.5, 0);
	   	glVertex2f(0,50);
	   	glVertex2f(7.5,25);
	   	glVertex2f(7,60);
	   	glEnd();
   	}
   	else if(tessellation==1)
   	{
   		/* We draw a tessellation, formed only by 5 independent quadrilaterals and 1 triangle (a quad-dominant mesh). */
   		glLineWidth(3);
   		glPointSize(8);
   		glBegin(GL_QUADS);
   		
   		/* Drawing the quad #0 (E-F-G-H) [blue]. */
   		glColor3f(0.0, 0.0, 1.0);
   		glVertex2d(-10.5,15);
   		glVertex2d(10.5,15);
   		glVertex2d(7.5,25);
   		glVertex2d(-7.5,25);
   		
   		/* Drawing the quad #1 (F-G-D-C) [red]. */
   		glColor3f(1.0, 0.0, 0.0);
   		glVertex2d(10.5,15);
   		glVertex2d(7.5,25);
   		glVertex2d(25,0);
   		glVertex2d(15,0);
   		
   		/* Drawing the quad #2 (L-M-G-D) [green]. */
   		glColor3f(0.0, 1.0, 0.0);
   		glVertex2d(7,60);
   		glVertex2d(0,50);
   		glVertex2d(7.5,25);
   		glVertex2d(25,0);
   		
   		/* Drawing the quad #3 (H-E-A-B) [cyan]. */
   		glColor3f(0.0, 1.0, 1.0);
   		glVertex2d(-7.5,25);
   		glVertex2d(-10.5,15);
   		glVertex2d(-15,0);
   		glVertex2d(-25,0);
   		
   		/* Drawing the quad #4 (I-M-H-B) [yellow]. */
   		glColor3f(1.0, 1.0, 0.0);
   		glVertex2d(-7,60);
   		glVertex2d(0,50);
   		glVertex2d(-7.5,25);
   		glVertex2d(-25,0);
   		glEnd();
   		
   		/* Drawing the triangle #0 (I-L-M) [magenta]. */
   		glColor3f(1,0,1);
   		glBegin(GL_TRIANGLES);
   		glVertex2f(-7,60);
   		glVertex2f(7,60);
   		glVertex2f(0,50);
   		glEnd();
   	}
   	else
   	{
   		/* We draw the same tesselation of the case #0 (with 11 independent triangles), but represented by using 3 triangle fans and 1 triangle strip. */
   		glLineWidth(3);
   		glPointSize(8);
   		
   		/* Drawing the first triangle fan (in red) for the point B, containing the points A-E-H-I. */
   		glBegin(GL_TRIANGLE_FAN);
   		glColor3f(1.0,0.0,0.0);
   		glVertex2f(-25,0);
   		glColor3f(0.8,0.8,0.8);
   		glVertex2f(-15,0);
   		glVertex2f(-10.5,15);
   		glVertex2f(-7.5,25);
   		glVertex2f(-7,60);
   		glEnd();
   		
   		/* Drawing the second triangle fan (in blue) for the point D, containing the points C-F-G-L. */
   		glBegin(GL_TRIANGLE_FAN);
   		glColor3f(0.0,0.0,1.0);
   		glVertex2f(25,0);
   		glColor3f(0.8,0.8,0.8);
   		glVertex2f(15,0);
   		glVertex2f(10.5,15);
   		glVertex2f(7.5,25);
   		glVertex2f(7,60);
   		glEnd();
   		
   		/* Drawing the third triangle fan (in green) for the point M, containing the points H-I-L-G. */
   		glBegin(GL_TRIANGLE_FAN);
   		glColor3f(0.0,1.0,0.0);
   		glVertex2f(0,50);
   		glColor3f(0.8,0.8,0.8);
   		glVertex2f(-7.5,25);
   		glVertex2f(-7,60);
   		glVertex2f(7,60);
   		glVertex2f(7.5,25);
   		glEnd();
   		
   		/* Drawing the triangle strip (in yellow), including the points H-E-F-G */
   		glBegin(GL_TRIANGLE_STRIP);
   		glColor3f(0.8,0.8,0.8);
   		glVertex2f(-10.5,15);
   		glColor3f(1,1,0);
   		glVertex2f(-7.5,25);
   		glVertex2f(10.5,15);
   		glColor3f(0.8,0.8,0.8);
   		glVertex2f(7.5,25);
   		glEnd();
   	}
   	
   	/* If we arrive here, we have finished! */
   	glFlush();
   	cout<<"\tDrawn the letter 'A' of interest by rendering ";
   	if(mode==2) cout<<"only the points ";
   	if(mode==1) cout<<"only the edges (wireframe) ";
   	if(mode==0) cout<<"completely the polygons ";
   	cout<<"in the tesselation #"<<tessellation;
   	if(tessellation==0) cout<<" (pure triangulation, formed by 11 independent triangles)"<<endl;
   	if(tessellation==1) cout<<" (quad-dominant mesh, formed by 5 independent quads and 1 triangle)"<<endl;
   	if(tessellation==2) cout<<" (the same pure triangulation as the case #0, but represented by 3 triangle fans and 1 triangle strip)"<<endl;
   	
   	cout.flush();
}
