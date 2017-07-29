/*******************************************************************************************************************************************************
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
 * main.cpp - the main function for the 'Example-060 (Old Mode)' Test.
 *******************************************************************************************************************************************************/

/* First, we must understand which platform we are using. */
#include <cstdlib>
#include <iostream>
#include <cmath>
#define PI 3.14159265358979324
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

/// The custom settings for rendering the triangles in the triangle fan of interest.
/**
 * -) the '0' value, used for rendering the 'filled versions' of the triangles in the triangle fan to be drawn, approximating the 'Ellipse' shape;
 * -) the '1' value, used for rendering the 'wireframe versions' of the triangles in the triangle fan to be drawn, approximating the 'Ellipse' shape;
 * -) the '2' value, used for rendering only the points of the triangles in the triangle fan to be drawn, approximating the 'Ellipse' shape;
 *
 * The user can choose what rendering has to be exploited by pressing cyclically the ' ' (space) key.
 */
int mode=0;

/// The number <i>'n'</i> of the vertices, including the center, for modeling the triangle fan of interest.
/**
 * This variable contains the number 'n' of the vertices, including the center '(xc,yc)', for modeling the triangle fan, approximating the 'Ellipse' shape. The user can
 * increase the number 'n' of the samples by pressing the '+' key, and decrease 'n' by pressing the '-' key. 
 * 
 * The Euclidean 3D coordinates of these points are stored in the 'pnts' array, which is recomputed by the 'computeEllipseVertices()' function, every time the value 'n'
 * is modified.
 */
int num=5;

/// The Euclidean 3D coordinates for all points in the triangle fan of interest, approximating the <i>'Ellipse'</i> shape.
/**
 * The Euclidean 3D coordinates for all 'n' points in the triangle fan of interest, approximating the 'Ellipse' shape, are stored as consecutive 3 floating-point values.
 * By construction, this array contains '3*(n+1)' locations. In particular, the Euclidean 3D coordinates, related to the point of index (j % 8), for any j, are stored
 * in locations '3*j' - '3*j+1' - '3*j+2' within this array. Each point has the same color 'white', which is not consider in the vertex array structure.
 */
float *pnts=NULL;

/* Prototypes for all functions of interest! */
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);
void draw();
void computeEllipseVertices();
void deallocateEllipseVertices();

/// The main function for the <i>'Example-060 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-060' Test, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws several variants of the 'Ellipse' shape with semi-axis 'Rx' and 'Ry' (respectively along the x- and the y-axis), as well as center '(xc,yc)', ";
	cout<<"in an OpenGL window. The 'Ellipse' shape is formed by an arbitrary number"<<endl;
	cout<<"\t'n-1' of the samples, and is defined as follows:"<<endl<<endl;
	cout<<"\t| x(t) - xc | <= Rx * cos(t), | y(t) - yc | <= Ry * sin(t)"<<endl<<endl;
	cout<<"\tfor any 'Rx>0', 'Ry>0', and for every 't' in '[-pi,pi]'."<<endl<<endl;
	cout<<"\tHere, the 'Ellipse' shape is approximated by 'n-1' triangles in a triangle fan. All triangles (in 'white') are incident at the center '(xc,yc)'. Thus, ";
	cout<<"the 'Ellipse' shape is approximated by 'n' vertices, including the center"<<endl<<"\t'(xc,yc)'."<<endl<<endl;
	cout<<"\tFor the sake of the efficiency, we exploit the 'vertex array' technique, provided directly by the OpenGL, for modeling the triangle fan of interest. ";
	cout<<"This technique is used to group together several drawing instructions into"<<endl;
	cout<<"\tonly one instruction for rendering (a subset of) the vertices and some of their state parameters. Here, we limit our attention to the Euclidean '3D' ";
	cout<<"coordinates for 'n' vertices in the triangle fan of interest. Specifically,"<<endl;
	cout<<"\twe exploit an array of '3*(n+1)' locations, containing the Euclidean '3D' coordinates (thus, '3' floating-values) for each vertex, including the center ";
	cout<<"'(xc,yc)', and a copy of the first vertex of the sequence for completing"<<endl;
	cout<<"\tand closing the triangle fan of interest. In this case, the 'glDrawArrays()' function is exploited for drawing directly the content of this array without ";
	cout<<"using another indirection level. Note that the content of this array is "<<endl;
	cout<<"\trecomputed when modifying the number 'n' of the samples in the triangle fan."<<endl<<endl;
	cout<<"\tIn this test, it is not possible to modify the radii 'Rx' and 'Ry', as well as the center '(xc,yc)' for the 'Ellipse' shape, since they are fixed in ";
	cout<<"advance. Instead, the user can:"<<endl<<endl;
	cout<<"\t\t-) increase the number 'n' of the samples in the triangle fan by pressing the '+' key;"<<endl;
	cout<<"\t\t-) decrease the number 'n' of the samples in the triangle fan by pressing the '-' key;"<<endl<<endl;
	cout<<"\tand can press cyclically the ' ' (space) key for choosing to render:"<<endl<<endl;
	cout<<"\t\t-) only the points for all triangles in the triangle fan of interest;"<<endl;
	cout<<"\t\t-) the 'wireframe versions' for all triangles in the triangle fan of interest;"<<endl;
	cout<<"\t\t-) the 'filled versions' for all triangles in the triangle fan of interest."<<endl<<endl;
	cout<<"\tLikewise, the window of interest can be closed by pressing any among the 'Q', the 'q', and the 'Esc' keys."<<endl<<endl;
	cout.flush();

	/* If we arrive here, we can draw the 'Ellipse' shape of interest by using the rendering settings, chosen by the user. */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,700);
	glutCreateWindow("The 'Example-060' Test, based on the (Old Mode) OpenGL");
	glutDisplayFunc(draw);
	glutReshapeFunc(resize);
	glutKeyboardFunc(manageKeys);
	glewExperimental = GL_TRUE;
   	glewInit();
   	initialize();
	glutMainLoop();
	return EXIT_SUCCESS;
}

/// This function updates the viewport for the scene when it is resized. */
void resize(int w, int h)
{
	/* We update the projection and the modeling matrices! */
	glViewport(0, 0, w, h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glOrtho(-35,35,-60,60,-1,1);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function deallocates the array, containing the Euclidean 3D coordinates for the points in the triangle fan, approximating the <i>'Ellipse'</i> shape.
/**
 * This function deallocates the 'pnts' array, containing the Euclidean 3D coordinates for the points in the triangle fan, approximating the 'Ellipse' shape. The content
 * of this array is allocated and recomputed (upon request) by the 'computeEllipseVertices()' function.
 */
void deallocateEllipseVertices()
{
	if(pnts!=NULL) delete pnts;
	pnts=NULL;
}

/// This function computes the content of the array, containing the Euclidean 3D coordinates for the points in the triangle fan, approximating the <i>'Ellipse'</i> shape.
/**
 * This function computes the content of the 'pnts' array, containing the Euclidean 3D coordinates for the points in the triangle fan, approximating the 'Ellipse' shape.
 * The content of this array is deallocated by the 'deallocateEllipseVertices()' function.
 */
void computeEllipseVertices()
{
	float delta=(2*PI)/(num-1),xk;

	/* First, we deallocate the content of the old 'pnts' array. */
	deallocateEllipseVertices();
	pnts=new float[3*(num+1)];
	pnts[0]=0.0;
	pnts[1]=0.0;
	pnts[2]=0.0;
	for(int k=0;k<num;k++)
	{
		xk=-PI+k*delta;
		pnts[ 3*(k+1) ]=30.0*cos(xk);
		pnts[ 3*(k+1)+1 ]=55.0*sin(xk);
		pnts[ 3*(k+1)+2 ]=0.0;
	}
	
	/* Now, we enable the 'vertex array' for the 'pnts' array. */
	glVertexPointer(3,GL_FLOAT,0,pnts);
}

/// This function draws the triangles in the triangle fan, approximating the <i>'Ellipse'</i> shape, in the main OpenGL window by using the rendering preferences, chosen by the user.
void draw()
{
	/* We draw the triangles in the triangle fan, approximating the 'Ellipse' shape, in the main OpenGL window by using the rendering preferences, chosen by the user. */
	glClear(GL_COLOR_BUFFER_BIT);
	if(mode==0) glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	if(mode==1) glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	if(mode==2) glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
	glPointSize(8);
	glLineWidth(2);
	glColor3f(1,1,1);
	glDrawArrays(GL_TRIANGLE_FAN,0,num+1);
	glFlush();
	if(mode==0) cout<<"\tThe 'filled versions' ";
	if(mode==1) cout<<"\tThe 'wireframe versions' ";
	if(mode==2) cout<<"\tOnly the points ";
	cout<<"of the triangles in the triangle fan, defined by using 'n="<<num<<"' vertices, are currently drawn."<<endl;
	cout.flush();
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(0.0, 0.0, 0.0, 0.0);
	mode=0;
	num=5;
	pnts=NULL;
	glEnableClientState(GL_VERTEX_ARRAY);
	computeEllipseVertices();
	cout<<"\tAt the beginning, the 'filled versions' of the triangles in the triangle fan, defined by using 'n=5' vertices (the minimum number 'n' as possible), are ";
	cout<<"drawn."<<endl<<endl;
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
			deallocateEllipseVertices();
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
			deallocateEllipseVertices();
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
		
		case 27:
	
			/* The key is 'Esc', thus we can exit from this program. */
			deallocateEllipseVertices();
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
		
		case ' ':
		
			/* We update the rendering mode for the triangles in the triangle fan, approximating the 'Ellipse' shape. */
			mode=(mode+1)%3;
			glutPostRedisplay();
			break;
		
		case '+':
		
			/* We increase the number of the vertices to be considered in the triangle fan, approximating the 'Ellipse' shape. */
			num=num+1;
			computeEllipseVertices();
			glutPostRedisplay();
			break;
		
		case '-':
		
			/* We decrease the number of the vertices to be considered in the triangle fan, approximating the 'Ellipse' shape. */
			if(num>5)
			{
				num=num-1;
				computeEllipseVertices(); 
			}
			else
			{
				cout<<"\tThe minimum number 'n=5' of the vertices to be considered in the triangle fan of interest is reached, and it is not possible to decrease ";
				cout<<"again this number."<<endl;
				cout.flush();
			}

			/* If we arrive here, this case is finished! */
			glutPostRedisplay();
			break;

		default:

			/* Other keys are not important for us */
			break;
	}
}

