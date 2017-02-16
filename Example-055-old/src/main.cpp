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
 * main.cpp - the main function for the 'Example-055 (Old Mode)' example
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

/// The number of the longitudinal slices in the <i>'Hemisphere'</i> shape of interest.
unsigned int long_slices_num=3;

/// The number of the latitudinal slides in the <i>'Hemisphere'</i> shape of interest.
unsigned int lat_slices_num=3;

/// The radius for the hemisphere of interest.
float radius=5.0;

/// The rotation angle along the x-axis.
float Xangle=0.0;

/// The rotation angle along the y-axis.
float Yangle=0.0;

/// The rotation angle along the z-axis.
float Zangle=0.0;

/// The vertices, belonging to the <i>'Hemisphere'</i> shape of interest.
GLfloat **vertices=NULL;

/// The indices for the vertices to be considered for drawing the <i>'Hemisphere'</i> shape of interest.
unsigned int *inds=NULL;

/* Prototypes for all functions of interest! */
void initialize();
void manageKeys(unsigned char key, int x, int y);
void draw();
void resize(int w,int h);
void computePoints();

/// The main function for the <i>'Example-055 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a new window! */
	cout<<endl<<"\tThis is the 'Example-055' Example, based on the (Old Mode) OpenGL"<<endl<<endl;
	cout.flush();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-055' Example, based on the (Old Mode) OpenGL");
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
	long_slices_num=3;
	lat_slices_num=3;
	radius=5.0;
	vertices=NULL;
	inds=NULL;
	glEnableClientState(GL_VERTEX_ARRAY);
	computePoints();
	cout<<"\tWe draw the wireframe version of the 'Hemisphere' shape with radius R="<<radius<<" by using the 'vertex array' technique, implemented throgh several 'glDrawElements()' statements. It is possible to:"<<endl<<endl;
	cout<<"\t-) modify the number of the latitudinal slices in the 'Hemisphere' shape by pressing the 'q' (decrease) and the 'Q' (increase) keys"<<endl;
	cout<<"\t-) modify the number of the longitudinal slices in the 'Hemisphere' shape by pressing the 'p' (decrease) and the 'P' (increase) keys"<<endl;
	cout<<"\t-) rotate the 'Hemisphere' shape along the x-axis by pressing the 'x' (decrease the angle) and the 'X' (increase the angle) keys"<<endl;
	cout<<"\t-) rotate the 'Hemisphere' shape along the y-axis by pressing the 'y' (decrease the angle) and the 'Y' (increase the angle) keys"<<endl;
	cout<<"\t-) rotate the 'Hemisphere' shape along the z-axis by pressing the 'z' (decrease the angle) and the 'Z' (increase the angle) keys"<<endl<<endl;
	cout.flush();
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'p' - 'P' - 'x' - 'X' - 'y' - 'Y' - 'z' - 'Z' - 'Esc' - keys */
	switch (key)
	{
		case 27:
	
		/* The key is 'Esc', thus we must exit. But first, we destroy correctly the 'inds' array and the 'vertices' matrix (if it is necessary). */
		cout<<endl;
		cout.flush();
		if(inds!=NULL) delete inds;
		inds=NULL;
		if(vertices!=NULL)
		{
			/* We destroy the 'vertices' matrix. */
			for(unsigned int j=0;j<lat_slices_num;j++) if(vertices[j]!=NULL) { delete vertices[j]; vertices[j]=NULL; } 
			delete vertices;
			vertices=NULL;
		}
		
		/* Finally, we can exit successfully! */
		exit(EXIT_SUCCESS);
		break;
		
		case 'q':
	
		/* The key is 'q', thus we must reduce the number of the latitudinal slices. But first, we destroy correctly the 'inds' array and the 'vertices' matrix (if it is necessary). Here, we know their actual sizes. */
		if(lat_slices_num>3) 
		{	
			/* First, we clear the 'inds' array and the 'vertices' matrix. */
			if(inds!=NULL) delete inds;
			inds=NULL;
			if(vertices!=NULL)
			{
				for(unsigned int j=0;j<lat_slices_num;j++) if(vertices[j]!=NULL) { delete vertices[j]; vertices[j]=NULL; } 
				delete vertices;
				vertices=NULL;
			}
			
			/* Now, we can compute everything! */
			lat_slices_num=lat_slices_num-1;
			computePoints();
			glutPostRedisplay();
		}
		else cout<<"\tThe minimum number 3 of the latitudinal slices is reached"<<endl;
		break;
		
		case 'Q':
	
		/* The key is 'Q', thus we must increase the number of the latitudinal slices. But first, we destroy correctly the 'inds' array and the 'vertices' matrix (if it is necessary). Here, we know their actual sizes. */
		if(inds!=NULL) delete inds;
		inds=NULL;
		if(vertices!=NULL)
		{
			for(unsigned int j=0;j<lat_slices_num;j++) if(vertices[j]!=NULL) { delete vertices[j]; vertices[j]=NULL; } 
			delete vertices;
			vertices=NULL;
		}
		
		/* Now, we can compute everything! */
		lat_slices_num=lat_slices_num+1;
		computePoints();
		glutPostRedisplay();
		break;
		
		case 'P':
	
		/* The key is 'P', thus we must increase the number of the longitudinal slices. But first, we destroy correctly the 'inds' array and the 'vertices' matrix (if it is necessary). Here, we know their actual sizes. */
		if(inds!=NULL) delete inds;
		inds=NULL;
		if(vertices!=NULL)
		{
			for(unsigned int j=0;j<lat_slices_num;j++) if(vertices[j]!=NULL) { delete vertices[j]; vertices[j]=NULL; } 
			delete vertices;
			vertices=NULL;
		}
		
		/* Now, we can compute everything! */
		long_slices_num=long_slices_num+1;
		computePoints();
		glutPostRedisplay();
		break;
		
		case 'p':
	
		/* The key is 'p', thus we must reduce the number of the longitudinal slices. But first, we destroy correctly the 'inds' array and the 'vertices' matrix (if it is necessary). Here, we know their actual sizes. */
		if(long_slices_num>3) 
		{
			/* First, we clear the 'inds' array and the 'vertices' matrix. */
			if(inds!=NULL) delete inds;
			inds=NULL;
			if(vertices!=NULL)
			{
				for(unsigned int j=0;j<lat_slices_num;j++) if(vertices[j]!=NULL) { delete vertices[j]; vertices[j]=NULL; } 
				delete vertices;
				vertices=NULL;
			}
			
			/* Now, we can compute everything! */
			long_slices_num=long_slices_num-1;
			computePoints();
			glutPostRedisplay();
		}
		else cout<<"\tThe minimum number 3 of the longitudinal slices is reached"<<endl;
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

/// This function updates the viewport for the scene when it is resized. */
void resize(int w, int h)
{
	/* We update the projections and the modeling matrices! */
	glViewport(0, 0, w, h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
}

/// This function draws the <i>'Hemisphere'</i> shape in the OpenGL window of interest by using the preferences, chosen by the user.
void draw()
{
	/* Now, we draw the 'Hemisphere' shape in the OpenGL window of interest by using the preferences, chosen by the user. */
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -10.0);
	glRotatef(Zangle, 0.0, 0.0, 1.0);
	glRotatef(Yangle, 0.0, 1.0, 0.0);
	glRotatef(Xangle, 1.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glColor3f(0,0,1);
	glLineWidth(1);
	glPointSize(5);
	
	/* Now, we draw the 'Hemisphere' shape by using the 'glDrawElements' statement! */
	for(unsigned int j=0;j<lat_slices_num;j++)
	{
		glVertexPointer(3,GL_FLOAT,0,vertices[j]);
		glDrawElements(GL_QUAD_STRIP,2*(long_slices_num+1),GL_UNSIGNED_INT,inds);
	}

	/* If we arrive here, we have finished! */
	glFlush();
	cout<<"\tDrawn the 'Hemisphere' shape (through several 'glDrawElements()' statements) by using "<<lat_slices_num<<" latitudinal slices and "<<long_slices_num<<" longitudinal slices, rotation angle around the x-axis: "<<Xangle<<", rotation ";
	cout<<"angle around the y-axis: "<<Yangle<<", rotation angle around the z-axis: "<<Zangle<<endl;
	cout.flush();
}

/// This function computes in advance all vertices of the <i>'Hemisphere'</i> shape to be drawn in the OpenGL scene of interest.
void computePoints()
{
	float delta_p,delta_q;
	
	/* First, we allocate the 'inds' array! */
	if(inds!=NULL) delete inds;
	inds=NULL;
	inds=new uint[2*(long_slices_num+1)];
	for(unsigned int h=0;h<2*(long_slices_num+1);h++) inds[h]=h;
	delta_p=(2.0*PI)/(long_slices_num);
	delta_q=PI/(2.0*lat_slices_num);
	vertices=new GLfloat* [lat_slices_num];
	for(unsigned int j=0;j<lat_slices_num;j++)
	{
		/* Now, we consider the current latitudinal slice of the 'Hemisphere' shape (a quad strip). */
		float psij=(float)j*delta_q,ppsi_j=(float)(j+1)*delta_q;
		vertices[j]=new GLfloat[6*(long_slices_num+1)];
		for(unsigned int i=0;i<=long_slices_num;i++)
		{
			float tetha_i=(float)i*delta_p;
			vertices[j][6*i+0]=radius*cos(ppsi_j)*cos(tetha_i);
			vertices[j][6*i+1]=radius*sin(ppsi_j);
			vertices[j][6*i+2]=radius*cos(ppsi_j)*sin(tetha_i);
			vertices[j][6*i+3]=radius*cos(psij)*cos(tetha_i);
			vertices[j][6*i+4]=radius*sin(psij);
			vertices[j][6*i+5]=radius*cos(psij)*sin(tetha_i);
		}
	}
}
