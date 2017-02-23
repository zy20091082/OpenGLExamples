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
 * main.cpp - the main function for the 'Example-061 (Old Mode)' example
 *******************************************************************************************************************************************************/

/* First, we must understand which platform we are using. */
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <string>
#include <cfloat>
using namespace std;
#ifndef uint
	typedef unsigned int uint;
#endif
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

/// The vertices, belonging to the <i>'Slide'</i> shape of interest.
GLfloat *vertices=NULL;

/// The indices for the vertices to be considered for drawing the <i>'Slide'</i> shape of interest.
unsigned int **inds=NULL;

/// The number of the (indexed) locations to be considered for drawing the <i>'Slide'</i> shape of interest.
int *cnt=NULL;

/* Prototypes for all functions of interest! */
void initialize();
void manageKeys(unsigned char key, int x, int y);
void draw();
void resize(int w,int h);
float evaluateSlide(float v);
void computePoints();
void destroyPoints();

/// The main function for the <i>'Example-061 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a new window! */
	cout<<endl<<"\tThis is the 'Example-061' Example, based on the (Old Mode) OpenGL"<<endl<<endl;
	cout.flush();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-061' Example, based on the (Old Mode) OpenGL");
	glutReshapeFunc(resize);
	glutKeyboardFunc(manageKeys);
	glutDisplayFunc(draw);
	glewExperimental = GL_TRUE;
   	glewInit();
   	initialize(); 
	glutMainLoop();
	return EXIT_SUCCESS;
}

/// This function evaluates the profile for the <i>'Slide'</i> shape at a given point.
float evaluateSlide(float v) { return ( 0.03875*pow(v,2)-1.225*v+10.0); }

/// This function updates the viewport for the scene when it is resized. */
void resize(int w, int h)
{
	/* We update the projections and the modeling matrices! */
	glViewport(0, 0, w, h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glFrustum(-5.0, 5.0, -10.0, 10.0, 4.0, 100.0);
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
	vertices=NULL;
	inds=NULL;
	cnt=NULL;
	glEnableClientState(GL_VERTEX_ARRAY);
	computePoints();
	cout<<"\tWe draw the wireframe version of the 'Slide' shape of interest by using the 'vertex array' technique, implemented throgh one unique call to 'glMultiDrawElements()' statement. It is possible to::"<<endl<<endl;
	cout<<"\t-) modify the number of the samples in the 'Slide' shape by pressing the '-' (decrease) and the '+' (increase) keys"<<endl;
	cout<<"\t-) rotate the 'Slide' shape along the x-axis by pressing the 'x' (decrease the angle) and the 'X' (increase the angle) keys"<<endl;
	cout<<"\t-) rotate the 'Slide' shape along the y-axis by pressing the 'y' (decrease the angle) and the 'Y' (increase the angle) keys"<<endl;
	cout<<"\t-) rotate the 'Slide' shape along the z-axis by pressing the 'z' (decrease the angle) and the 'Z' (increase the angle) keys"<<endl<<endl;
	cout.flush();
}

/// This function deallocates all vertices of the <i>'Slide'</i> shape to be drawn in the OpenGL scene of interest.
void destroyPoints()
{
	/* First, we destroy the 'vertices' and the 'cnt' arrays. Finally, we destroy the 'inds' matrix. */
	if(vertices!=NULL) delete vertices;
	vertices=NULL;
	if(cnt!=NULL) delete cnt;
	cnt=NULL;
	if(inds!=NULL)
	{
		for(unsigned int j=0;j<4;j++) if(inds[j]!=NULL) { delete inds[j]; inds[j]=NULL; } 
		delete inds;
		inds=NULL;
	}
}

/// This function draws the <i>'Slide'</i> shape in the OpenGL window of interest by using the preferences, chosen by the user.
void draw()
{
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

	/* Now, we exploit only one 'glMultiDrawElement()' statement. */
	glVertexPointer(3,GL_FLOAT,0,vertices);
	glMultiDrawElements(GL_QUAD_STRIP,cnt,GL_UNSIGNED_INT,(const void**)inds,4);
	
	/* If we arrive here, we have finished! */
	glFlush();
	cout<<"\tApproximated and drawn the 'Slide' shape (through only one 'glMultiDrawElements()' statement) by using "<<num_samples<<" samples, rotation angle around the x-axis: "<<Xangle<<", rotation angle around the y-axis: "<<Yangle<<", ";
	cout<<"rotation angle around the z-axis: "<<Zangle<<endl;
	cout.flush();
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'Esc' - 'q' - 'Q' - '+' - '-' - 'x' - 'X' - 'y' - 'Y' - 'z' - 'Z' keys */
	switch (key)
	{
		case 27:
	
		/* The key is 'Esc', thus we must exit. But first, we destroy correctly all auxiliary arrays of interest. Here, we know their actual sizes. */
		destroyPoints();
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case 'q':
		
		/* The key is 'q', thus we must exit. But first, we destroy correctly all auxiliary arrays of interest. Here, we know their actual sizes. */
		destroyPoints();
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case 'Q':
		
		/* The key is 'Q', thus we must exit. But first, we destroy correctly all auxiliary arrays of interest. Here, we know their actual sizes. */
		destroyPoints();
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case '+':
		
		/* The key is '+', thus we increase the number of the samples! */
		destroyPoints();
		num_samples=num_samples+1;
		computePoints();
		glutPostRedisplay();
		break;
		
		case '-':
		
		/* The key is '-', thus we decrease the number of the samples! */
		if(num_samples>3)
		{
			destroyPoints();
			num_samples=num_samples-1;
			computePoints();
			glutPostRedisplay();
		}
		else cout<<"\tThe minimum number 3 of the samples is reached"<<endl;
		cout.flush();
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

/// This function computes in advance all vertices of the <i>'Hemisphere'</i> shape to be drawn in the OpenGL scene of interest.
void computePoints()
{
	float dv=40.0/(num_samples-1);
	uint ind=0;

	/* Now, we allocate all auxiliary arrays, and other variables. */
	inds=new uint*[4];
	for(uint k=0;k<4;k++) inds[k]=NULL;
	cnt=new int[4];
	for(uint k=0;k<4;k++) cnt[k]=(int)0;
	vertices=new GLfloat[3*(2*num_samples+4)+3*(2*num_samples)+3*(2*num_samples)+3*(2*num_samples)];
	
	/* Now, we add the data for the first quad-strip, containing 'num_samples+4' actual vertices. */
	cnt[0]=2*num_samples+4;
	inds[0]=new uint[2*num_samples+4];
	ind=0;
	inds[0][ind]=ind;
	vertices[3*ind]=5;
	vertices[3*ind+1]=0;
	vertices[3*ind+2]=-20;
	ind=ind+1;
	inds[0][ind]=ind;
	vertices[3*ind]=-5;
	vertices[3*ind+1]=0;
	vertices[3*ind+2]=-20;
	for(unsigned int k=0;k<num_samples;k++)
	{
		float v=-20.0+k*dv;
		float p=evaluateSlide(v);
		
		/* Now, we analyze the samples of the parabola! */
		ind=ind+1;
		inds[0][ind]=ind;
		vertices[3*ind]=5;
		vertices[3*ind+1]=p;
		vertices[3*ind+2]=v;
		ind=ind+1;
		inds[0][ind]=ind;
		vertices[3*ind]=-5;
		vertices[3*ind+1]=p;
		vertices[3*ind+2]=v;
	}
	
	/* If we arrive here, we complete the two vertical basis (front and back). */
	ind=ind+1;
	inds[0][ind]=ind;
	vertices[3*ind]=5;
	vertices[3*ind+1]=0;
	vertices[3*ind+2]=20;
	ind=ind+1;
	inds[0][ind]=ind;
	vertices[3*ind]=-5;
	vertices[3*ind+1]=0;
	vertices[3*ind+2]=20;

	/* Now, we compute the points for the second quad-strip, which contains 'num_samples' actual vertices. */
	cnt[1]=2*num_samples;
	inds[1]=new uint[2*num_samples];
	for(unsigned int k=0;k<num_samples;k++)
	{
		float v=-20.0+k*dv;
		float p=evaluateSlide(v);
		
		/* Now, we add two vertices of this slide! */
		ind=ind+1;
		inds[1][2*k]=ind;
		vertices[3*ind]=5;
		vertices[3*ind+1]=p;
		vertices[3*ind+2]=v;
		ind=ind+1;
		inds[1][2*k+1]=ind;
		vertices[3*ind]=5;
		vertices[3*ind+1]=0;
		vertices[3*ind+2]=v;
	}
	
	/* Now, we compute the points for the third quad-strip, which contains 'num_samples' actual vertices. */
	cnt[2]=2*num_samples;
	inds[2]=new uint[2*num_samples];
	for(unsigned int k=0;k<num_samples;k++)
	{
		float v=-20.0+k*dv;
		float p=evaluateSlide(v);
		
		/* Now, we add two vertices of this slide! */
		ind=ind+1;
		inds[2][2*k]=ind;
		vertices[3*ind]=-5;
		vertices[3*ind+1]=p;
		vertices[3*ind+2]=v;
		ind=ind+1;
		inds[2][2*k+1]=ind;
		vertices[3*ind]=-5;
		vertices[3*ind+1]=0;
		vertices[3*ind+2]=v;
	}
	
	/* Now, we compute the points for the fourth (last) quad-strip, which contains 'num_samples' actual vertices. */
	cnt[3]=2*num_samples;
	inds[3]=new uint[2*num_samples];
	for(unsigned int k=0;k<num_samples;k++)
	{
		float v=-20.0+k*dv;
		ind=ind+1;
		inds[3][2*k]=ind;
		vertices[3*ind]=5;
		vertices[3*ind+1]=0;
		vertices[3*ind+2]=v;
		ind=ind+1;
		inds[3][2*k+1]=ind;
		vertices[3*ind]=-5;
		vertices[3*ind+1]=0;
		vertices[3*ind+2]=v;
	}
}
