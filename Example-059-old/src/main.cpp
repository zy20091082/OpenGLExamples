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
 * main.cpp - the main function for the 'Example-059 (Old Mode)' example
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

/// The rotation angle along the x-axis.
float Xangle=0.0;

/// The rotation angle along the y-axis.
float Yangle=0.0;

/// The rotation angle along the z-axis.
float Zangle=0.0;

/// The number of the horizontal slices along the y-axis.
unsigned int height_slices_num=3;

/// The number of the radial slices.
unsigned int radial_slices_num=3;

/// The vertices for the bottom basis of the <i>'Truncated Cone'</i> shape.
GLfloat *bottom_basis=NULL;

/// The vertices for the top basis of the <i>'Truncated Cone'</i> shape.
GLfloat *top_basis=NULL;

/// The vertices for the lateral part of the <i>'Truncated Cone'</i> shape.
GLfloat **sides=NULL;

/// The indices for the vertices to be considered for drawing the lateral part of the <i>'Truncated Cone'</i> shape.
unsigned int *ind_side=NULL;

/// The indices for the vertices to be considered for drawing the top and the bottom basis for the <i>'Truncated Cone'</i> shape.
unsigned int *ind_basis=NULL;

/* Prototypes for all functions of interest! */
void initialize();
void manageKeys(unsigned char key, int x, int y);
void draw();
void resize(int w,int h);
void computePoints();

/// The main function for the <i>'Example-059 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a new window! */
	cout<<endl<<"\tThis is the 'Example-059' Example, based on the (Old Mode) OpenGL"<<endl<<endl;
	cout.flush();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-059' Example, based on the (Old Mode) OpenGL");
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
   	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'Esc' - 'h' - 'H' - 'r' - 'R' - 'x' - 'X' - 'y' - 'Y' - 'z' - 'Z' keys */
	switch (key)
	{
		case 27:
	
		/* The key is 'Esc' */
		cout<<endl;
		cout.flush();
		if(bottom_basis!=NULL) delete bottom_basis;
		bottom_basis=NULL;
		if(top_basis!=NULL) delete top_basis;
		top_basis=NULL;
		if(ind_basis!=NULL) delete ind_basis;
		ind_basis=NULL;
		if(ind_side!=NULL) delete ind_side;
		ind_side=NULL;
		if(sides!=NULL)
		{
			for(unsigned int k=0;k<height_slices_num;k++) if(sides[k]!=NULL) { delete sides[k]; sides[k]=NULL; }
			delete sides;
			sides=NULL;
		}
		
		/* Now, we can exit! */
		exit(EXIT_SUCCESS);
		break;
		
		case 'h':
		
		/* The key is 'h', thus we reduce the number of the horizontal slices. */
		if(height_slices_num>3) 
		{
			/* Now, we clear the 'sides' matrix. Here, we know its actual size! */
			if(sides!=NULL)
			{
				for(unsigned int k=0;k<height_slices_num;k++) if(sides[k]!=NULL) { delete sides[k]; sides[k]=NULL; }
				delete sides;
				sides=NULL;
			}
			
			/* Now, we update the 'height_slices_num' variable! */
			height_slices_num=height_slices_num-1;
			computePoints();
		}
		else { cout<<"\tThe minimum number 3 of the horizontal slices is reached"<<endl; }
		cout.flush();
		glutPostRedisplay();
		break;
		
		case 'H':
		
		/* The key is 'H', thus we increase the number of the horizontal slices. But first, we clear the 'sides' matrix. Here, we know its actual size! */
		if(sides!=NULL)
		{
			for(unsigned int k=0;k<height_slices_num;k++) if(sides[k]!=NULL) { delete sides[k]; sides[k]=NULL; }
			delete sides;
			sides=NULL;
		}
			
		/* Now, we update the 'height_slices_num' variable! */
		height_slices_num=height_slices_num+1;
		computePoints();
		glutPostRedisplay();
		break;
		
		case 'r':
		
		/* The key is 'r', thus we reduce the number of the radial slices. */
		if(radial_slices_num>3) 
		{
			/* Now, we clear the 'sides' matrix. Here, we know its actual size! */
			if(sides!=NULL)
			{
				for(unsigned int k=0;k<height_slices_num;k++) if(sides[k]!=NULL) { delete sides[k]; sides[k]=NULL; }
				delete sides;
				sides=NULL;
			}
			
			/* Now, we update the 'radial_slices_num' variable! */
			radial_slices_num=radial_slices_num-1;
			computePoints();
		}
		else { cout<<"\tThe minimum number 3 of the radial slices is reached"<<endl; }
		cout.flush();
		glutPostRedisplay();
		break;
		
		case 'R':
		
		/* The key is 'R', thus we increase the number of the radial slices. But first, we clear the 'sides' matrix. Here, we know its actual size! */
		if(sides!=NULL)
		{
			for(unsigned int k=0;k<height_slices_num;k++) if(sides[k]!=NULL) { delete sides[k]; sides[k]=NULL; }
			delete sides;
			sides=NULL;
		}
		
		/* Now, we update the 'radial_slices_num' variable! */
		radial_slices_num=radial_slices_num+1;
		computePoints();
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
	height_slices_num=3;
	radial_slices_num=3;
	Xangle=0.0;
	Yangle=0.0;
	Zangle=0.0;
	bottom_basis=NULL;
	top_basis=NULL;
	ind_basis=NULL;
	sides=NULL;
	ind_side=NULL;
	glEnableClientState(GL_VERTEX_ARRAY);
	computePoints();
	cout<<"\tWe draw the wireframe version of the 'Truncated Cone' shape of interest by using the 'vertex array' technique, implemented throgh several 'glDrawElements()' statements. It is possible to::"<<endl<<endl;
	cout<<"\t-) modify the number of the horizontal slices by pressing the 'h' (decrease) and the 'H' (increase) keys"<<endl;
	cout<<"\t-) modify the number of the radial slices by pressing the 'r' (decrease) and the 'R' (increase) keys"<<endl;
	cout<<"\t-) rotate the 'Truncated Cone' shape along the x-axis by pressing the 'x' (decrease the angle) and the 'X' (increase the angle) keys"<<endl;
	cout<<"\t-) rotate the 'Truncated Cone' shape along the y-axis by pressing the 'y' (decrease the angle) and the 'Y' (increase the angle) keys"<<endl;
	cout<<"\t-) rotate the 'Truncated Cone' shape along the z-axis by pressing the 'z' (decrease the angle) and the 'Z' (increase the angle) keys"<<endl<<endl;
	cout.flush();
}

/// This function draws the <i>'Truncated Cone'</i> shape in the OpenGL window of interest by using the preferences, chosen by the user.
void draw()
{
	/* Now, we draw the 'Truncated Cone' shape in the OpenGL window of interest by using the preferences, chosen by the user. */
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
	
	/* Now, we draw the lateral part by using the 'glDrawElements' statement! */
	for(unsigned int h=0;h<height_slices_num;h++)
	{
		glVertexPointer(3,GL_FLOAT,0,sides[h]);
		glDrawElements(GL_TRIANGLE_STRIP,2*(radial_slices_num+1),GL_UNSIGNED_INT,ind_side);
	}
	
	/* Now, we draw the bottom and the top basis by using the 'glDrawElements' statement! */
	glVertexPointer(3,GL_FLOAT,0,bottom_basis);
	glDrawElements(GL_TRIANGLE_FAN,radial_slices_num+2,GL_UNSIGNED_INT,ind_basis);
	glVertexPointer(3,GL_FLOAT,0,top_basis);
	glDrawElements(GL_TRIANGLE_FAN,radial_slices_num+2,GL_UNSIGNED_INT,ind_basis);
	
	/* Finally, the scene is complete! */
	glFlush();
	cout<<"\tApproximated and drawn the 'Truncated Cone' shape (through several 'glDrawElements()' statements) by using "<<radial_slices_num<<" radial slices and "<<height_slices_num<<" horizontal slices, rotation angle around the x-axis: "<<Xangle<<", rotation ";
	cout<<"angle around the y-axis: "<<Yangle<<", rotation angle around the z-axis: "<<Zangle<<endl;
	cout.flush();
}

/// This function computes in advance all vertices of the <i>'Truncated Cone'</i> shape to be drawn in the OpenGL scene of interest.
void computePoints()
{
	float delta_radial,delta_vert;
	
	/* First, we compute several variables for computing the vertices in the lateral part of the 'Truncated Cone' shape. Then, we prepare the arrays for storing the vertices in the lateral part of the 'Truncated Cone' shape. */
	delta_radial=(2.0*PI)/(radial_slices_num);
	delta_vert=3.0/height_slices_num;
	if(ind_side!=NULL) delete ind_side;
	ind_side=NULL;
	ind_side=new uint[2*(radial_slices_num+1)];
	for(unsigned int h=0;h<2*(radial_slices_num+1);h++) ind_side[h]=h;
	sides=new GLfloat* [height_slices_num];
	for(unsigned int h=0;h<height_slices_num;h++) 
	{
		/* Now, we create all points of interest. */
		float hh=h*delta_vert;
		float radius_hh=2.0+(3.0-hh)*sqrt(2.0)*cos(PI/4.0);
		float hhp=(h+1)*delta_vert;
		float radius_hhp=2.0+(3.0-hhp)*sqrt(2.0)*cos(PI/4.0);
		sides[h]=new GLfloat[6*(radial_slices_num+1)];
		for(unsigned int k=0;k<=radial_slices_num;k++)
		{
			sides[h][6*k+0]=radius_hhp*cos(k*delta_radial);
			sides[h][6*k+1]=hhp;
			sides[h][6*k+2]=radius_hhp*sin(k*delta_radial);
			sides[h][6*k+3]=radius_hh*cos(k*delta_radial);
			sides[h][6*k+4]=hh;
			sides[h][6*k+5]=radius_hh*sin(k*delta_radial);
		}
	}

	/* Now, we compute the vertices for the bottom basis of the 'Truncated Cone' shape! */
	if(ind_basis!=NULL) delete ind_basis;
	ind_basis=NULL;
	ind_basis=new uint[radial_slices_num+2];
	for(int k=0;k<radial_slices_num+2;k++) ind_basis[k]=k;
	if(bottom_basis!=NULL) delete bottom_basis;
	bottom_basis=NULL;
	bottom_basis=new GLfloat[3*(radial_slices_num+2)];
	bottom_basis[0]=0.0;
	bottom_basis[1]=0.0;
	bottom_basis[2]=0.0;
	for(unsigned int k=0;k<=radial_slices_num;k++)
	{
		bottom_basis[3*k+3]=5.0*cos(k*delta_radial);
		bottom_basis[3*k+4]=0.0;
		bottom_basis[3*k+5]=5.0*sin(k*delta_radial);
	}
	
	/* Finally, we compute the vertices for the top basis of the 'Truncated Cone' shape! */
	if(top_basis!=NULL) delete top_basis;
	top_basis=NULL;
	top_basis=NULL;
	top_basis=new GLfloat[3*(radial_slices_num+2)];
	top_basis[0]=0.0;
	top_basis[1]=3.0;
	top_basis[2]=0.0;
	for(unsigned int k=0;k<=radial_slices_num;k++)
	{
		top_basis[3*k+3]=2.0*cos(k*delta_radial);
		top_basis[3*k+4]=3.0;
		top_basis[3*k+5]=2.0*sin(k*delta_radial);
	}
}
