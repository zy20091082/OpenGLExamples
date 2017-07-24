/**********************************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 * 
 * Last update: July 2017
 *
 * This program is Free Software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.                                       
 *                                                                         
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License (http://www.gnu.org/licenses/gpl.txt) for more details.
 * 
 * main.cpp - the main function for the 'Example-059 (Old Mode)' Test.
 **********************************************************************************************************************************************************************/
 
/* First, we must understand which platform we are using. */
#include <cstdlib>
#include <iostream>
#include <cmath>
#define PI 3.14159265358979324
#ifndef uint
	typedef unsigned int uint;
#endif
using namespace std;
#ifdef __APPLE__

	/* We are using a MacOSX platform (Macintosh). */
	#include "GL/glew.h"
	#include "GLUT/glut.h"
	#include "OpenGL/gl.h"

#else

	/* We are not using a MacOSX platform. Thus, we have a generic Unix-like platform, like the GNU/Linux, or a Microsoft Windows platform. */
	#include "GL/glew.h"
	#include "GL/glut.h"
	#include "GL/gl.h"

#endif

/// The rotation angle <i>'Rx'</i> for rotating the <i>'Truncated Cone'</i> shape along the x-axis.
/**
 * This value indicates the angle 'Rx' for rotating the 'Truncated Cone' shape along the x-axis '[1,0,0]'. This rotation angle is increased by pressing the 'X' key,
 * and decreased by pressing the 'x' key.
 */
float Xangle=0.0;

/// The rotation angle <i>'Ry'</i> for rotating the <i>'Truncated Cone'</i> shape along the y-axis.
/**
 * This value indicates the angle 'Ry' for rotating the 'Truncated Cone' shape along the y-axis '[0,1,0]'. This rotation angle is increased by pressing the 'Y' key,
 * and decreased by pressing the 'y' key.
 */
float Yangle=0.0;

/// The rotation angle <i>'Rz'</i> for rotating the <i>'Truncated Cone'</i> shape along the z-axis.
/**
 * This value indicates the angle 'Rz' for rotating the 'Truncated Cone' shape along the z-axis '[0,0,1]'. This rotation angle is increased by pressing the 'Z' key, 
 * and decreased by pressing the 'z' key.
 */
float Zangle=0.0;

/// The number <i>'h'</i> of the horizontal slices across the <i>'y'</i> axis, approximating the <i>'Truncated Cone'</i> shape.
/**
 * By construction, the <i>'Truncated Cone'</i> shape is approximated by a number 'h' of planes, parallel to the plane containing its basis, across the 'y' axis. This 
 * value contains the number 'h' of horizontal slices, and it is initially set to 'h=3', which is the minimum number of horizonal planes, parallel to the basis of the
 * 'Truncated Cone' shape. It is increased and decreased by pressing, respectively, the 'H' and the 'h' keys.
 */
uint height_slices_num=3;

/// The number <i>'r'</i> of the radial sectors in the basis of the <i>'Truncated Cone'</i> shape.
/**
 * By construction, the basis of the 'Truncated Cone' shape is approximated by a number 'r' of radial sectors, such that each point is connected to its apex. This value 
 * contains the number 'r' of radial sectors, and it is initially set to 'r=3', which is the minimum number of radial sectors in the basis of the 'Truncated Cone' shape.
 * It is increased and decreased by pressing, respectively, the 'R' and the 'r' keys.
 */
uint radial_slices_num=3;

/// The Euclidean 3D coordinates for all vertices, belonging to the inferior basis of the <i>'Truncated Cone'</i> shape.
/**
 * This array contains the Euclidean 3D coordinates (i.e., 3 floating-point values) for all vertices, belonging to the inferior basis of the 'Truncated Cone' shape. By
 * construction, the inferior basis lays on the coordinate plane 'xz' (with 'y=0'), and is approximated by a number 'r' of radial sectors. For the sake of the 
 * simplicity, the inferior basis is approximated by a triangle fan of center (0,0,0), defined on 'r' radial sectors. Thus, this array contains the Euclidean 3D
 * coordinates for all 'r+2' vertices of interest, including the Euclidean 3D coordinates for the center, and a copy of the Euclidean 3D coordinates of the first vertex
 * in the triangle fan, necessary for completing its definition. In other words, this array contains '3*(r+2)' locations. This array is directly used by the
 * 'glDrawArrays()' function without using another degree of indirection.
 *
 * The content of this array (including the content of other auxiliary data structures) is recomputed by the 'computePoints()' function, when the values 'r' and 'h' are
 * modified by the user. Instead, their content is deallocated by the 'clearPoints()' function.
 */
GLfloat *bottom_basis=NULL;

/// The Euclidean 3D coordinates for all vertices, belonging to the superior basis of the <i>'Truncated Cone'</i> shape.
/**
 * This array contains the Euclidean 3D coordinates (i.e., 3 floating-point values) for all vertices, belonging to the superior basis of the 'Truncated Cone' shape. By
 * construction, the superior basis lays on the plane of equation 'y=3'), and is approximated by a number 'r' of radial sectors. For the sake of the simplicity, the top
 * basis is approximated by a triangle fan of center (0,3,0), defined on 'r' radial sectors. Thus, this array contains the Euclidean 3D coordinates for all 'r+2'
 * vertices of interest, including the Euclidean 3D coordinates for the center, and a copy of the Euclidean 3D coordinates of the first vertex in the triangle fan,
 * necessary for completing its definition. In other words, this array contains '3*(r+2)' locations. This array is directly used by the 'glDrawArrays()' function 
 * without using another degree of indirection.
 *
 * The content of this array (including the content of other auxiliary data structures) is recomputed by the 'computePoints()' function, when the values 'r' and 'h' are
 * modified by the user. Instead, their content is deallocated by the 'clearPoints()' function.
 */
GLfloat *top_basis=NULL;

/// The Euclidean 3D coordinates for all vertices, belonging to the 'lateral surface' of the <i>'Truncated Cone'</i> shape.
/**
 * This matrix contains the Euclidean 3D coordinates (i.e., 3 floating-point values) for all vertices, belonging to the 'lateral surface' of the 'Truncated Cone' shape.
 * By construction, the 'lateral surface' is approximated by a grid, formed by 'r' radial sectors, and by 'h' horizontal slices around the 'y'-axis. Each row of this 
 * matrix corresponds to any horizontal slice, which is approximated by a quad strip. Thus, this matrix has 'h' rows. Furthermore, it is needed to enumerate '2*(r+1)'
 * points (and their for completing correctly a quad strip. Thus, each row of this matrix contains '6*(r+1)' floating-points

 * The content of this matrix (including the content of other auxiliary data structures) is recomputed by the 'computePoints()' function, when the values 'r' and 'h' are
 * modified by the user. Instead, their content is deallocated by the 'clearPoints()' function.
 */
GLfloat **sides=NULL;

uint *ind_side=NULL;

/* Prototypes for all functions of interest! */
void initialize();
void manageKeys(unsigned char key, int x, int y);
void draw();
void resize(int w,int h);
void computePoints();
void clearPoints();

/// The main function for the <i>'Example-059 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-059' Test, based on the (Old Mode) OpenGL."<<endl;


	/* If we arrive here, we can draw the 'Truncated Cone' shape of interest by using the rendering settings, chosen by the user. */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-059' Test, based on the (Old Mode) OpenGL");
	glutReshapeFunc(resize);
	glutKeyboardFunc(manageKeys);
	glutDisplayFunc(draw);
	glewExperimental = GL_TRUE;
   	glewInit();
   	initialize(); 
	glutMainLoop();
	return EXIT_SUCCESS;
}

void clearPoints()
{
	/* Now, we deallocate all auxiliary arrays! */
	if(bottom_basis!=NULL) delete bottom_basis;
	bottom_basis=NULL;
	if(top_basis!=NULL) delete top_basis;
	top_basis=NULL;
	if(ind_side!=NULL) delete ind_side;
	ind_side=NULL;
	if(sides!=NULL) delete sides;
	sides=NULL;
}

void computePoints()
{
	float delta_radial,delta_vert;

	/* First, we deallocates the existing auxiliary arrays! */
	clearPoints();
	delta_radial=(2.0*PI)/(radial_slices_num);
	delta_vert=3.0/height_slices_num;
	
	/* Now, we compute the Euclidean 3D coordinates for all vertices in the inferior basis of the 'Truncated Cone' shape! */
	bottom_basis=new GLfloat[3*(radial_slices_num+2)];
	bottom_basis[0]=0.0;
	bottom_basis[1]=0.0;
	bottom_basis[2]=0.0;
	for(uint k=0;k<=radial_slices_num;k++)
	{
		bottom_basis[3*k+3]=5.0*cos(k*delta_radial);
		bottom_basis[3*k+4]=0.0;
		bottom_basis[3*k+5]=5.0*sin(k*delta_radial);
	}

	/* Now, we compute the Euclidean 3D coordinates for all vertices in the superior basis of the 'Truncated Cone' shape! */
	top_basis=new GLfloat[3*(radial_slices_num+2)];
	top_basis[0]=0.0;
	top_basis[1]=3.0;
	top_basis[2]=0.0;
	for(uint k=0;k<=radial_slices_num;k++)
	{
		top_basis[3*k+3]=2.0*cos(k*delta_radial);
		top_basis[3*k+4]=3.0;
		top_basis[3*k+5]=2.0*sin(k*delta_radial);
	}

	/* Now, we compute the Euclidean 3D coordinates for all vertices in the lateral side of the 'Truncated Cone' shape! */
	ind_side=new uint[2*(radial_slices_num+1)];
	for(uint h=0;h<2*(radial_slices_num+1);h++) ind_side[h]=h;
	sides=new GLfloat* [height_slices_num];
	for(uint h=0;h<height_slices_num;h++) 
	{
		/* Now, we compute the Euclidean 3D coordinates for all vertices of interest! */
		float hh=h*delta_vert;
		float radius_hh=2.0+(3.0-hh)*sqrt(2.0)*cos(PI/4.0);
		float hhp=(h+1)*delta_vert;
		float radius_hhp=2.0+(3.0-hhp)*sqrt(2.0)*cos(PI/4.0);
		sides[h]=new GLfloat[6*(radial_slices_num+1)];
		for(uint k=0;k<=radial_slices_num;k++)
		{
			sides[h][6*k+0]=radius_hhp*cos(k*delta_radial);
			sides[h][6*k+1]=hhp;
			sides[h][6*k+2]=radius_hhp*sin(k*delta_radial);
			sides[h][6*k+3]=radius_hh*cos(k*delta_radial);
			sides[h][6*k+4]=hh;
			sides[h][6*k+5]=radius_hh*sin(k*delta_radial);
		}
	}
}

/// This function updates the viewport for the scene when it is resized. */
void resize(int w, int h)
{
	/* We update only the projection matrix! */
	glViewport(0, 0, w, h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	Xangle=0.0;
	Yangle=0.0;
	Zangle=0.0;
	height_slices_num=3;
	radial_slices_num=3;
	bottom_basis=NULL;
	top_basis=NULL;
	ind_side=NULL;
	sides=NULL;
	computePoints();
	glEnableClientState(GL_VERTEX_ARRAY);
	cout<<"\tAt the beginning, the 'wireframe version' of the 'Truncated Cone' shape is drawn by exploiting 'h="<<height_slices_num<<"' horizontal slices and ";
	cout<<"'r="<<radial_slices_num<<"' radial sectors (thus, the minimum numbers 'r' and 'h' as possible), as well as rotation angles 'Rx=";
	cout<<Xangle<<"', "<<"'Ry="<<Yangle<<"', and 'Rz="<<Zangle<<"'."<<endl<<endl;
	cout.flush();	
}

/// This function is the keyboard input processing routine for the OpenGL window of interest (ASCII keys).
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'r' - 'R' - 'h' - 'H' - 'x' - 'X' - 'y' - 'Y' - 'z' - 'Z' - 'Esc' - keys */
	switch (key)
	{
		case 'x':
		
			/* The key is 'x', thus we decrease the rotation angle 'Rx' for rotating the 'wireframe version' of the 'Truncated Cone' shape along the X-axis. */
			Xangle -= 5.0;
			if(Xangle < 0.0) Xangle += 360.0;
	        glutPostRedisplay();
	        break;
		
		case 'X':
		
			/* The key is 'X', thus we increase the rotation angle 'Rx' for rotating the 'wireframe version' of the 'Truncated Cone' shape along the X-axis. */
	        Xangle += 5.0;
			if (Xangle > 360.0) Xangle -= 360.0;
	        glutPostRedisplay();
	        break;
		
		case 'y':
		
			/* The key is 'y', thus we decrease the rotation angle 'Ry' for rotating the 'wireframe version' of the 'Truncated Cone' shape along the Y-axis. */
			Yangle -= 5.0;
			if(Yangle < 0.0) Yangle += 360.0;
	        glutPostRedisplay();
	        break;
		
		case 'Y':
		
			/* The key is 'Y', thus we increase the rotation angle 'Ry' for rotating the 'wireframe version' of the 'Truncated Cone' shape along the Y-axis. */
	        Yangle += 5.0;
			if (Yangle > 360.0) Yangle -= 360.0;
	        glutPostRedisplay();
	        break;
		
		case 'z':
        
	        /* The key is 'z', thus we decrease the rotation angle 'Rz' for rotating the 'wireframe version' of the 'Truncated Cone' shape along the z-axis. */
			Zangle -= 5.0;
			if(Zangle < 0.0) Zangle += 360.0;
	        glutPostRedisplay();
	        break;
        
		case 'Z':
		
			/* The key is 'Z', thus we increase the rotation angle 'Rz' for rotating the 'wireframe version' of the 'Truncated Cone' shape along the z-axis. */
	        Zangle += 5.0;
			if (Zangle > 360.0) Zangle -= 360.0;
	        glutPostRedisplay();
	        break;
		
		case 27:
	
			/* The key is 'Esc', thus we can exit from this program. */
			clearPoints();
			cout<<endl<<"\tThis program is closing correctly ... "<<endl<<endl;
			cout << "\tPress the RETURN key to finish ... ";
			cin.get();
			#ifndef _MSC_VER
				cout << endl;
				cout.flush();
			#endif
			cout.flush();
			exit(EXIT_SUCCESS);
			break;
			
		case 'q':
	
			/* The key is 'q', thus we can exit from this program. */
			clearPoints();
			cout<<endl<<"\tThis program is closing correctly ... "<<endl<<endl;
			cout << "\tPress the RETURN key to finish ... ";
			cin.get();
			#ifndef _MSC_VER
				cout << endl;
				cout.flush();
			#endif
			cout.flush();
			exit(EXIT_SUCCESS);
			break;
			
		case 'Q':
	
			/* The key is 'Q', thus we can exit from this program. */
			clearPoints();
			cout<<endl<<"\tThis program is closing correctly ... "<<endl<<endl;
			cout << "\tPress the RETURN key to finish ... ";
			cin.get();
			#ifndef _MSC_VER
				cout << endl;
				cout.flush();
			#endif
			cout.flush();
			exit(EXIT_SUCCESS);
			break;
		
		case 'h':
		
			/* The key is 'h', thus we reduce the number of the horizontal slices in the 'wireframe version' of the 'Truncated Cone' shape. */
			if(height_slices_num>3) { height_slices_num=height_slices_num-1; computePoints(); }
			else { cout<<"\tThe minimum number 'h=3' of the horizontal slices in the 'wireframe version' of the 'Truncated Cone' shape is reached, and it is not possible to decrease again this number."<<endl; cout.flush(); }
			glutPostRedisplay();
			break;
		
		case 'r':
		
			/* The key is 'r', thus we reduce the number of the radial sectors in the 'wireframe version' of the 'Truncated Cone' shape. */
			if(radial_slices_num>3) { radial_slices_num=radial_slices_num-1; computePoints(); }
			else { cout<<"\tThe minimum number 'h=3' of the radial sectors in the 'wireframe version' of the 'Truncated Cone' shape is reached, and it is not possible to decrease again this number."<<endl; cout.flush(); }
			glutPostRedisplay();
			break;
		
		case 'H':
		
			/* The key is 'H', thus we increase the number of the horizontal slices in the 'wireframe version' of the 'Truncated Cone' shape. */
			height_slices_num=height_slices_num+1;
			computePoints();
			glutPostRedisplay();
			break;
			
		case 'R':
		
			/* The key is 'R', thus we increase the number of the radial sectors in the 'wireframe version' of the 'Truncated Cone' shape. */
			radial_slices_num=radial_slices_num+1;
			computePoints();
			glutPostRedisplay();
			break;
		
		default:
		
			/* Other keys are not important for us */
			break;
	}
}

/// This function draws the <i>'Truncated Cone'</i> shape in the OpenGL window of interest by using the preferences, chosen by the user.
void draw()
{
	float delta_radial,delta_vert;

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

	/* Now, we draw the lateral side of the 'Truncated Cone' shape! */
	for(uint h=0;h<height_slices_num;h++)
	{
		glVertexPointer(3,GL_FLOAT,0,sides[h]);
		glDrawElements(GL_QUAD_STRIP,2*(radial_slices_num+1),GL_UNSIGNED_INT,ind_side);
	}

	/* Now, we draw the inferior and the superior basis for the 'Truncated Cone' shape! */
	glVertexPointer(3,GL_FLOAT,0,bottom_basis);
	glDrawArrays(GL_TRIANGLE_FAN,0,(uint)(radial_slices_num+2));
	glVertexPointer(3,GL_FLOAT,0,top_basis);
	glDrawArrays(GL_TRIANGLE_FAN,0,(uint)(radial_slices_num+2));
	
	/* Finally, the scene is complete! */
	glFlush();
	cout<<"\tThe 'wireframe version' of the 'Truncated Cone' shape is currently drawn by exploiting 'h="<<height_slices_num<<"' horizontal slices and ";
	cout<<"'r="<<radial_slices_num<<"' radial sectors, as well as rotation angles 'Rx=";
	cout<<Xangle<<"', "<<"'Ry="<<Yangle<<"', and 'Rz="<<Zangle<<"'."<<endl;
	cout.flush();	
}

