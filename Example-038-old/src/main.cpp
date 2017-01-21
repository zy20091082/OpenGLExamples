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
 * main.cpp - the main function for the 'Example-038 (Old Mode)' example
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

/// This flag indicates which approximation technique we must exploit.
int technique=0;

/// The rendering mode for the scene of interest (wireframe or filled).
GLenum mode=GL_FILL;

/// The intersection points between the circles of interest.
float xp1,yp1,xp2,yp2,teta1,teta2;

/* Prototypes for all functions of interest! */
void initialize();
void manageKeys(unsigned char key, int x, int y);
void draw();
void resize(int w,int h);
void drawDisc(float R,float X,float Y,float Z);

/// The main function for the <i>'Example-038 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a new window! */
	cout<<endl<<"\tThis is the 'Example-038' Example, based on the (Old Mode) OpenGL"<<endl<<endl;
	cout.flush();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE|GLUT_DEPTH);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(450,765);
	glutCreateWindow("The 'Example-038' Example, based on the (Old Mode) OpenGL");
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
	cout<<"\tWe draw the 'Eight' shape in the scene. Specifically, it is possible to modify:"<<endl<<endl;
	cout<<"\t-) the number of the samples for the disks of interest by pressing the '+' and '-' keys"<<endl;
	cout<<"\t-) the rendering mode (wireframe or filled) for the shaep by pressing the 'w' key"<<endl;
	cout<<"\t-) the approximation technique by pressing the ' ' key:"<<endl<<endl;
	cout<<"\t\t-) in the first case, the shape is the combination of four disks, drawn by using the depth test (z-buffer)"<<endl;
	cout<<"\t\t-) in the second case, the shape is approximated by a real tessellation"<<endl<<endl;
	cout.flush();
	glClearColor(1.0, 1.0, 1.0, 0.0);
	num_samples=5;
	technique=0;
	mode=GL_FILL;
	yp1=15.0;
	yp2=15.0;
	xp1=sqrt(1275);
	xp2=-sqrt(1275);
	teta1=acos(xp1/50);
	teta2=-teta1;
	teta2=PI/2-teta2;
}

/// This function updates the viewport for the scene when it is resized. */
void resize(int w, int h)
{
	/* We update the projections and the modeling matrices! */
	glViewport(0, 0, w, h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glOrtho(-60,60,-80,110,-10,0);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '+' - '-' - '<space bar>' -'w' keys */
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
		
		case ' ':
		
		/* The key is ' ', thus we change the technique to be used! */
		technique=(technique+1)%2;
		glutPostRedisplay();
		break;
		
		case 'w':
		
		/* The key is 'w', thus we change the rendering mode to be used! */
		if(mode==GL_FILL) mode=GL_LINE;
		else mode=GL_FILL;
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
	for(int i=0;i<=num_samples;i++)
	{
		float t=-PI+i*d;
		glVertex3f(X+R*cos(t),Y+R*sin(t),Z);
	}
	
	/* If we arrive here, all is ok. */
	glEnd();
}

/// This function draws the 'Eight' shape in the OpenGL window of interest by using the preferences, chosen by the user.
void draw()
{
	/* Now, we draw the 'Eight' shape in the OpenGL window of interest by using the preferences, chosen by the user. */
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK,mode);
	glColor3f(1,0,0);
	if(technique==0)
	{
		/* We draw four disks by using the depth test (z-buffer). */
		glEnable(GL_DEPTH_TEST);
		drawDisc(50,0,-20,5);
		drawDisc(50,0,50,3);
		glColor3f(1,1,1);
		drawDisc(20,0,-20,10);
		drawDisc(20,0,50,10);
		glDisable(GL_DEPTH_TEST);
	}
	else
	{
		float e1=-teta1;
		float e2=PI+teta1;
		float d=fabs(e1-e2)/(num_samples-1);
		unsigned int num=(num_samples-1)/4;
		float dl=2*fabs(xp1)/(num);
		float d1=fabs(PI-2*teta1)/(num);

		/* We draw the superior part of the 'Eight' shape. First, we draw the central portion. */
		glBegin(GL_QUAD_STRIP);
		glColor3f(1,0,0);
		for(unsigned int k=0;k<=num;k++)
		{
			glVertex3f(-xp1+k*dl,15,1);
			glVertex3f(20*cos(e2+k*d1),50+20*sin(e2+k*d1),1);
		}
		
		/* Then, we draw the remaining portion! */
		for(unsigned int k=0;k<num_samples;k++)
		{
			glVertex3f(50*cos(e1+k*d),50+50*sin(e1+k*d),1);
			glVertex3f(20*cos(e1+k*d),50+20*sin(e1+k*d),1);
		}
		
		/* Now, we draw the inferior part of the 'Eight' shape. First, we draw the central portion. */
		glEnd();
		glPointSize(5);
		glBegin(GL_QUAD_STRIP);
		for(unsigned int k=0;k<=num;k++)
		{
			glVertex3f(-xp1+k*dl,15,1);
			glVertex3f(20*cos(e2+k*d1),-20-20*sin(e2+k*d1),1);
		}
		
		/* Now, we draw the remaining portion! */
		for(unsigned int k=0;k<num_samples;k++)
		{
			glVertex3f(50*cos(e1+k*d),-20-50*sin(e1+k*d),1);
			glVertex3f(20*cos(e1+k*d),-20-20*sin(e1+k*d),1);
		}
		
		/* Now, the scene is complete. */
		glEnd();
	}
	
	/* If we arrive here, everything is ok! */
	glFlush();
	cout<<"\tApproximated and drawn the 'Eight' shape of interest with "<<num_samples<<" samples and by using ";
	if(technique==0) cout<<"four disks, drawn by using the depth test (z-buffer)"<<endl;
	else cout<<"an effective and real tessellation"<<endl;
	cout.flush();
}
