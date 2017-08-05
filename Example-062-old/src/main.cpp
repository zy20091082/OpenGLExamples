/*******************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 * 
 * Last update: August 2017
 *
 * This program is Free Software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.                                       
 *                                                                         
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License (http://www.gnu.org/licenses/gpl.txt) for more details.
 * 
 * main.cpp - the main function for the 'Example-062 (Old Mode)' Test.
 *******************************************************************************************************************************************************/

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

/// The custom settings for rendering the quadrilaterals in the quad strips of interest.
/**
 * -) the '0' value, used for rendering the 'filled versions' of the quadrilaterals in the quad strips to be drawn, approximating the 'Bullseye' shape;
 * -) the '1' value, used for rendering the 'wireframe versions' of the quadrilaterals in the quad strips to be drawn, approximating the 'Bullseye' shape;
 * -) the '2' value, used for rendering only the points of the quadrilaterals in the quad strips to be drawn, approximating the 'Bullseye' shape;
 *
 * The user can choose what rendering has to be exploited by pressing cyclically the ' ' (space) key.
 */
int mode=0;

/// The Euclidean 3D coordinates and the color components for all points in the quad strips, approximating the <i>'Bullseye'</i> shape.
/**
 * This array contains the Euclidean 3D coordinates (3 floating-point values) and the color components (3 floating-point values) for all points in the quad strips,
 * approximating the 'Bullseye' shape. Specifically, we approximate the 'Bullseye' shape by using 3 'Circular Annulus' shapes, such that each of them is approximated by
 * a quad strip, defined on 'n' pairs of corresponding points. These latter belong, respectively, to the 'internal' and the 'external circumference' of the 'Circular
 * Annulus' shape. By construction, the first pair of points is duplicated for closing correctly the quad strip. This implies that each quad strip is described by a  
 * sequence of '2*(n+1)' points. Hence, each quad strip occupies '6*2*(n+1) = 12*(n+1)' locations in this array. It is clear that storing all 3 quad strips, needed for
 * modeling correctly the 'Bullseye' shape requires '36*(n+1)' locations, and each location of this array stores a floating-point value.
 *
 * The content of this array, including the content of other auxiliary data structures (see later), is recomputed by the 'computePoints()' function, when the number 'n'
 * is modified by the user. Instead, the content of these auxiliary data structures is deallocated by the 'destroyPoints()' function.
 */
GLfloat *quads=NULL;

/// The number of the points for each quad strip, approximating the <i>'Bullseye'</i> shape.
/**
 * This array contains the number of the points for each quad strip, approximating the 'Bullseye' shape. Specifically, we approximate the 'Bullseye' shape by using 3
 * 'Circular Annulus' shapes, such that each of them is approximated by a quad strip, defined on 'n' pairs of corresponding points. These latter belong, respectively, 
 * to the 'internal' and the 'external circumference' of the 'Circular Annulus' shape. By construction, the first pair of points is duplicated for closing correctly the
 * quad strip. This implies that each quad strip is described by a sequence of '2*(n+1)' points. Hence, this array has always 3 locations, and each location is equal to
 * '2*(n+1)'.
 *
 * The content of this array, including the content of other auxiliary data structures (see later), is recomputed by the 'computePoints()' function, when the number 'n'
 * is modified by the user. Instead, the content of these auxiliary data structures is deallocated by the 'destroyPoints()' function. 
 */
int *cnt=NULL;

/// The indices to the points to be considered for the quad strips, approximating the <i>'Bullseye'</i> shape.
/**
 * This matrix provides another degree of indirection for accessing correctly the locations in the 'vertex array' structure (provided by the 'quads' array), when
 * modeling the quad strips of interest. These latter approximate the 'Bullseye' shape. Specifically, we approximate the 'Bullseye' shape by using 3 'Circular Annulus'
 * shapes, such that each of them is approximated by a quad strip, defined on 'n' pairs of corresponding points. These latter belong, respectively, to the 'internal'
 * and the 'external circumference' of the 'Circular Annulus' shape. By construction, the first pair of points is duplicated for closing correctly the quad strip. This
 * implies that each quad strip is described by a sequence of '2*(n+1)' points. As a consequence, this matrix has '3' rows (one for each quad strip), and each row
 * contains the '2*(n+1)' indices to the locations of the 'quads' array, describing the points of the corresponding quad strip.
 *
 * The content of this matrix, including the content of other auxiliary data structures (see later), is recomputed by the 'computePoints()' function, when the number
 * 'n' is modified by the user. Instead, the content of these auxiliary data structures is deallocated by the 'destroyPoints()' function. 
 */
uint** inds=NULL;

/// The number <i>'n'</i> of the samples, needed for approximating the <i>'Bullseye'</i> shape.
/**
 * This value contains the number 'n' of the samples, needed for approximating the 'Bullseye' shape. Specifically, we approximate the 'Bullseye' shape by using 3
 * 'Circular Annulus' shapes, such that each of them is approximated by a quad strip, defined on 'n' pairs of corresponding points. These latter belong, respectively, 
 * to the 'internal' and the 'external circumference' of the 'Circular Annulus' shape. In other words, the value 'n' is the number of the circular sectors to be 
 * considered in each quad strip of interest.
 * 
 * The number 'n' for the sectors of interest can be increased and decreased by pressing, respectively, the '+' and '-' key.
 */
uint num_samples=3;

/* Prototypes for all functions of interest! */
void initialize();
void manageKeys(unsigned char key, int x, int y);
void draw();
void resize(int w,int h);
void computePoints();
void destroyPoints();

/// The main function for the <i>'Example-062 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-062' Test, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws several variants of the 'Bullseye' shape, often representing the targets in the shooting and the archery competitions, in an OpenGL window. A ";
	cout<<"generic 'Bullseye' shape is defined by several concentric 'Circle' shapes"<<endl;
	cout<<"\t(disks) of different colors, same center '(xc,yc)', and radii of different lengths. Recall that the 'Circle' shape with radius 'R' and center '(xc,yc)' ";
	cout<<"is defined as follows:"<<endl<<endl;
	cout<<"\t| x(t) - xc | <= R * cos(t), | y(t) - yc | <= R * sin(t)"<<endl<<endl;
	cout<<"\tfor any 'R>0', and for every 't' in '[-pi,pi]'."<<endl<<endl;
	cout<<"\tIn other words, any 'Bullseye' shape is the union of all circular crowns, bounded by the 'Circle' curves, that are the boundary for the pairs of the ";
	cout<<"consecutive disks in the 'Bullseye' shape (also known as the 'Circular Annulus'"<<endl;
	cout<<"\tshapes), if sorted with respect to the lengths of their radii. Any 'Circular Annulus' shape is bounded by '2' circumferences of different radii. In this ";
	cout<<"context, the circumference with the smallest radius is indicated as the"<<endl;
	cout<<"\t'internal circumference', while the circumference with the biggest radius is indicated as the 'external circumference' of the 'Circular Annulus' shape.";
	cout<<endl<<endl;
	cout<<"\tHere, we restrict our attention to the approximation of the 'Bullseye' shape, formed by '3' (concentric) 'Circular Annulus' shapes of different colors. ";
	cout<<"Each of them is approximated by a quad strip, defined over 'n' circular"<<endl;
	cout<<"\tsectors. In this case, it is necessary to enumerate a pairs of vertices for each sector. More specifically, one vertex lays on the 'internal ";
	cout<<"circumference', while the other vertex lays on the 'external circumference'. Since the"<<endl;
	cout<<"\tfirst pair of vertices must be duplicated for closing correctly the quad strip, it is necessary to enumerate '2*(n+1)' vertices for each quad strip.";
	cout<<endl<<endl;
	cout<<"\tFor the sake of the efficiency, we exploit the 'vertex array' technique, provided directly by the OpenGL, for modeling '3' quad strips of interest. This ";
	cout<<"technique is used to group together several drawing instructions into only"<<endl;
	cout<<"\tone instruction for rendering (a subset of) the vertices and some of their state parameters. Here, we limit our attention to the Euclidean '3D' ";
	cout<<"coordinates and the color components (thus '6' floating-point values) for every"<<endl;
	cout<<"\tpoint in '3' quad strips of interest. These floating-point values are stored in a unique array, formed by '36 * (n+1)' locations. The content of this ";
	cout<<"array is recomputed when modifying the number 'n' of the sectors in the quad"<<endl;
	cout<<"\tstrips. In this case, the 'glMultiDrawElements()' function is exploited for drawing directly the content of this array (in only one step) by using another";
	cout<<" indirection level."<<endl<<endl;
	cout<<"\tIn this test, it is not possible to modify the radii and the colors of the 'Circular Annulus' shapes, as well as the center '(xc,yc)' for the 'Bullseye' ";
	cout<<"shape, since they are fixed in advance. Instead, the user can:"<<endl<<endl;
	cout<<"\t\t-) increase the number 'n' of the sectors in the quad strips of interest by pressing the '+' key;"<<endl;
	cout<<"\t\t-) decrease the number 'n' of the sectors in the quad strips of interest by pressing the '-' key;"<<endl<<endl;
	cout<<"\tand can press cyclically the ' ' (space) key for choosing to render:"<<endl<<endl;
	cout<<"\t\t-) only the points for all quadrilaterals in the quad strips of interest;"<<endl;
	cout<<"\t\t-) the 'wireframe versions' for all quadrilaterals in the quad strips of interest;"<<endl;
	cout<<"\t\t-) the 'filled versions' for all quadrilaterals in the quad strips of interest."<<endl<<endl;
	cout<<"\tLikewise, the window of interest can be closed by pressing any among the 'Q', the 'q', and the 'Esc' keys."<<endl<<endl;
	cout.flush();
	
	/* If we arrive here, then we can draw the 'Bullseye' shape of interest by using the rendering settings, chosen by the user. */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-062' Test, based on the (Old Mode) OpenGL");
	glutReshapeFunc(resize);
	glutKeyboardFunc(manageKeys);
	glutDisplayFunc(draw);
	glewExperimental = GL_TRUE;
   	glewInit();
   	initialize(); 
	glutMainLoop();
	return EXIT_SUCCESS;
}

/// This function deallocates all auxiliary data structures in this test.
/**
 * This function deallocates all auxiliary data structures, used in this test, for modeling correctly the 'Bullseye' shape through the 'vertex array' technique. This
 * operation is needed when the number 'n' of the sectors is modified. In the case, it is necessary to recompute correctly the content of all auxiliary data structures
 * by using the 'computePoints()' member function.
 */
void destroyPoints()
{
	/* Now, we destroy all auxiliary data structures for modeling correctly the 'Bullseye' shape through the 'vertex array' technique. */
	if(quads!=NULL) delete quads;
	quads=NULL;
	if(cnt!=NULL) delete cnt;
	cnt=NULL;
	if(inds!=NULL)
	{
		for(uint k=0;k<3;k++) if(inds[k]!=NULL) { delete inds[k]; inds[k]=NULL; }
		delete inds;
		inds=NULL;
	}
}

/// This function allocates and computes all auxiliary data structures in this test.
/**
 * This function allocates and computes all auxiliary data structures, used in this test, for modeling correctly the 'Bullseye' shape through the 'vertex array'
 * technique. This operation is needed when the number 'n' of the sectors is modified. The content of these auxiliary data structures is deallocated by the
 * 'destroyPoints()' function.
 */
void computePoints()
{
	float delta=(2*PI)/(num_samples);
	uint v;

	/* Now, we allocate and compute all auxiliary data structures for drawing the quad strips of interest in the 'Bullseye' shape (see the above description). Here:
	 *
 	 * -) we have 3 'Circular Annulus' shapes, approximated by 3 quad strips (thus, the 'inds' matrix and the 'cnt' array have 3 locations).
	 * -) Each 'Circular Annulus' is approximated by a quad strip, defined by 'n' pairs of points (as mentioned above). Since the first pair of points must be duplicated
	 *    in order to close correctly the quad strip, we need '2*(n+1)' points for modeing each quad strip. Thus, each row of the 'inds' matrix is an array of '2*(n+1)'
 	 * 	  locations, and each location of the 'cnt' array contains the '2*(n+1)' value.
	 * -) Here, we limit our attention to the Euclidean 3D coordinates and the color components. For each point, we need 3 floating-values for storing its Euclidean 3D
	 * 	  coordinates, and 3 floating-point values for storing its color components (thus 6 floating-point values for each point). This means that the 'quads' array
	 * 	  (i.e, the 'vertex array' structure in this test) have '36*(n+1)' locations.
	 */
	inds=new uint*[3];
	for(uint k=0;k<3;k++) { inds[k]=new uint[2*(num_samples+1)]; }
	cnt=new int[3];
	for(uint k=0;k<3;k++) { cnt[k]=2*(num_samples+1); }
	quads=new GLfloat[36*(num_samples+1)];
	
	/* Here, we model 3 'Circle Annulus' shapes, approximating the 'Bullseye' shape. Broadly speakig, we add 'n+1' pairs of points for each 'Circular Annulus' shape.
	 * We start from the 'Circular Annulus #0', shown in 'green'. Its 'internal radius' is 5, and its 'external radius' is 10. */
	for(uint k=0;k<=num_samples;k++)
	{
		/* We model the state parameters for the point #0 in the new pair, laying on the 'internal circumference' of the 'Circular Annulus #0'. The global index of this
		 * point is 'v=2*k', its Euclidean coordinates are stored in locations of indices '6*v', '6*v+1', and '6*v+2' in the 'quads' array, while its color components
		 * are stored in the locations of indices '6*v+3', '6*v+4', and '6*v+5', always in the 'quads' array. */
		v=2*k;		
		inds[0][2*k]=v;
		quads[6*v]=5*cos(k*delta);
		quads[6*v+1]=5*sin(k*delta);
		quads[6*v+2]=0;
		quads[6*v+3]=0.0;
		quads[6*v+4]=1.0;
		quads[6*v+5]=0.0;
		
		/* We model the state parameters for the point #1 in the new pair, laying on the 'external circumference' of the 'Circular Annulus #0'. The global index of this
		 * point is 'v=2*k+1', its Euclidean coordinates are stored in locations of indices '6*v', '6*v+1', and '6*v+2' in the 'quads' array, while its color components
		 * are stored in the locations of indices '6*v+3', '6*v+4', and '6*v+5', always in the 'quads' array. */
		v=v+1;
		inds[0][2*k+1]=v;
		quads[6*v]=10*cos(k*delta);
		quads[6*v+1]=10*sin(k*delta);
		quads[6*v+2]=0;
		quads[6*v+3]=0.0;
		quads[6*v+4]=1.0;
		quads[6*v+5]=0.0;
	}

	/* We continue on the 'Circular Annulus #1', shown in 'white'. Its 'internal radius' is 10, and its 'external radius' is 15. */
	for(uint k=0;k<=num_samples;k++)
	{
		/* We model the state parameters for the point #0 in the new pair, laying on the 'internal circumference' of the 'Circular Annulus #1'. The global index of this
		 * point is 'v=2*k+2*(n+1)', its Euclidean coordinates are stored in locations of indices '6*v', '6*v+1', and '6*v+2' in the 'quads' array, while its color
		 * components are stored in the locations of indices '6*v+3', '6*v+4', and '6*v+5', always in the 'quads' array. */
		v=(2*k+2*(num_samples+1));
		inds[1][2*k]=v;
		quads[6*v]=10*cos(k*delta);
		quads[6*v+1]=10*sin(k*delta);
		quads[6*v+2]=0;
		quads[6*v+3]=1.0;
		quads[6*v+4]=1.0;
		quads[6*v+5]=1.0;

		/* We model the state parameters for the point #1 in the new pair, laying on the 'external circumference' of the 'Circular Annulus #1'. The global index of this
		 * point is 'v=2*k+2*(n+1)+1', its Euclidean coordinates are stored in locations of indices '6*v', '6*v+1', and '6*v+2' in the 'quads' array, while its color
		 * components are stored in the locations of indices '6*v+3', '6*v+4', and '6*v+5', always in the 'quads' array. */
		v=v+1;
		inds[1][2*k+1]=v;
		quads[6*v]=15*cos(k*delta);
		quads[6*v+1]=15*sin(k*delta);
		quads[6*v+2]=0;
		quads[6*v+3]=1.0;
		quads[6*v+4]=1.0;
		quads[6*v+5]=1.0;
	}

	/* We continue on the 'Circular Annulus #2', shown in 'red'. Its 'internal radius' is 15, and its 'external radius' is 20. */
	for(uint k=0;k<=num_samples;k++)
	{
		/* We model the state parameters for the point #0 in the new pair, laying on the 'internal circumference' of the 'Circular Annulus #2'. The global index of this
		 * point is 'v=2*k+4*(n+1)', its Euclidean coordinates are stored in locations of indices '6*v', '6*v+1', and '6*v+2' in the 'quads' array, while its color
		 * components are stored in the locations of indices '6*v+3', '6*v+4', and '6*v+5' in the 'quads' array. */
		v=(2*k+4*(num_samples+1));
		inds[2][2*k]=v;
		quads[6*v]=15*cos(k*delta);
		quads[6*v+1]=15*sin(k*delta);
		quads[6*v+2]=0;
		quads[6*v+3]=1.0;
		quads[6*v+4]=0.0;
		quads[6*v+5]=0.0;

		/* We model the state parameters for the point #1 in the new pair, laying on the 'external circumference' of the 'Circular Annulus #2'. The global index of this
		 * point is 'v=2*k+4*(n+1)+1', its Euclidean coordinates are stored in locations of indices '6*v', '6*v+1', and '6*v+2' in the 'quads' array, while its color
		 * components are stored in the locations of indices '6*v+3', '6*v+4', and '6*v+5' in the 'quads' array. */
		v=v+1;
		inds[2][2*k+1]=v;
		quads[6*v]=20*cos(k*delta);
		quads[6*v+1]=20*sin(k*delta);
		quads[6*v+2]=0;
		quads[6*v+3]=1.0;
		quads[6*v+4]=0.0;
		quads[6*v+5]=0.0;
	}

	/* If we arrive here, then we enable the 'vertex array' over the 'quads' array. */
	glVertexPointer(3,GL_FLOAT,6*sizeof(float),&quads[0]);
	glColorPointer(3,GL_FLOAT,6*sizeof(float),&quads[3]);
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(0.0, 0.0, 0.0, 0.0);
	mode=0;
	cnt=NULL;
	inds=NULL;
	quads=NULL;
	num_samples=3;
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	computePoints();
	cout<<"\tAt the beginning, the 'filled versions' of the quadrilaterals in the quad strips, defined by using 'n=3' sectors (the minimum number 'n' as possible), ";
	cout<<"are drawn."<<endl<<endl;
	cout.flush();
}

/// This function updates the viewport for the scene when it is resized. */
void resize(int w, int h)
{
	/* We update the projection and the modeling matrices! */
	glViewport(0, 0, w, h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glOrtho(-30,30,-30,30,-1,1);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '+' - '-' - ' ' (space) keys. */
	switch (key)
	{
		case 'q':
	
			/* The key is 'q', thus we can exit from this program. */
			destroyPoints();
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
			destroyPoints();
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
			destroyPoints();
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
		
			/* We update the rendering mode for the quadrilaterals in the quad strips, approximating the 'Bullseye' shape. */
			mode=(mode+1)%3;
			glutPostRedisplay();
			break;
		
		case '+':
		
			/* We increase the number 'n' of the sectors for the quad strips, approximating the 'Bullseye' shape. */
			destroyPoints();
			num_samples=num_samples+1;
			computePoints();
			glutPostRedisplay();
			break;
		
		case '-':
		
			/* We decrease the number 'n' of the sectors for the quadrilaterals for the quad strips, approximating 'Bullseye' shape. */
			if(num_samples>3)
			{
				destroyPoints();
				num_samples=num_samples-1;
				computePoints(); 
			}
			else
			{
				cout<<"\tThe minimum number 'n=5' of the sectors to be considered in the quad strips of interest is reached, and it is not possible to decrease again ";
				cout<<"this number."<<endl;
				cout.flush();
			}

			/* If we arrive here, then this case is finished! */
			glutPostRedisplay();
			break;

		default:

			/* Other keys are not important for us */
			break;
	}
}

/// This function draws the quadrilaterals in the quad strips, approximating the <i>'Bullseye'</i> shape, in the main OpenGL window by using the rendering preferences, chosen by the user.
void draw()
{
	/* We draw the quadrilaterals in the quad strips, approximating the 'Bullseye' shape, in the main OpenGL window by using the rendering preferences, chosen by the
	 * user. */
	glClear(GL_COLOR_BUFFER_BIT);
	if(mode==0) glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	if(mode==1) glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	if(mode==2) glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
	glPointSize(5);
	glLineWidth(2);
	glMultiDrawElements(GL_QUAD_STRIP,cnt,GL_UNSIGNED_INT,(const void**)inds,3);
	glFlush();
	if(mode==0) cout<<"\tThe 'filled versions' ";
	if(mode==1) cout<<"\tThe 'wireframe versions' ";
	if(mode==2) cout<<"\tOnly the points ";
	cout<<"of the quadrilaterals in the quad strips of interest, defined by using 'n="<<num_samples<<"' sectors, are currently drawn."<<endl;
	cout.flush();
}

