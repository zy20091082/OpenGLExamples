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
 * main.cpp - the main function for the 'Example-053 (Old Mode)' Test.
 *******************************************************************************************************************************************************/

/* First, we must understand which platform we are using. */
#include <cstdlib>
#include <iostream>
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

/// The custom settings for rendering the desidered triangles in the triangle strip of interest, approximating the <i>'Square Annulus'</i> shape.
/**
 * The value of this flag may be one of the following values:
 * 
 * -) the '0' value, used for rendering the 'filled versions' of the desidered triangles in the triangle strip of interest to be drawn, approximating the 'Square
 * 	  Annulus' shape;
 * -) the '1' value, used for rendering the 'wireframe versions' of the desidered triangles in the triangle strip of interest to be drawn, approximating the 'Square 
 * 	  Annulus' shape;
 * -) the '2' value, used for rendering only the vertices of the desidered triangles in the triangle strip of interest to be drawn, approximating the 'Square Annulus' 
 *    shape.
 * 
 * The user can choose what rendering has to be exploited by pressing cyclically the ' ' (space) key.
 */
int mode=0;

/// The Euclidean 3D coordinates for all points in the triangle strip of interest, approximating the <i>'Square Annulus'</i> shape.
/**
 * The Euclidean 3D coordinates for all points in the triangle strip of interest are stored as consecutive 3 floating-point values. In particular, the Euclidean 3D
 * coordinates, related to the point of index (j % 8), for any j, are stored in locations '3*j' - '3*j+1' - '3*j+2' within this array. Instead, the colors for all points
 * of interest are stored in the 'colors' array by using a similar approach.
 *
 * The user can choose what points have to be considered by modifying the global variable 'num' (see later).
 */
static GLfloat vertices[] = {
	30,30,0,
	10,10,0,
	70,30,0,
	90,10,0,
	70,70,0,
	90,90,0,
	30,70,0,
	10,90,0
};

/// The colors for all points in the triangle strip of interest, approximating the <i>'Square Annulus'</i> shape.
/**
 * The colors for all points in the triangle strip of interest are stored as consecutive 3 floating-point values. In particular, the color components, related to the
 * point of index (j % 8), for any j, are stored in locations '3*j' - '3*j+1' - '3*j+2' within this array. Instead, the Euclidean 3D coordinates for all points of
 * interest are stored in the 'vertices' array by using a similar approach.
 *
 * The user can choose what points have to be considered by modifying the global variable 'num' (see later).
 */
static GLfloat colors[] = {
	1,1,1,
	1,0,0,
	0,1,0,
	0,0,1,
	1,1,0,
	1,0,1,
	0,1,1,
	1,0,0
};

/// The number <i>'n'</i> for the subset of points to be considered in the triangle strip of interest, approximating the <i>'Square Annulus'</i> shape.
/**
 * This value is the number 'n' of indices to be considered in the range '[3,n-1]' in order to access the 'vertices' and the 'colors' arrays in order to limit the
 * triangles number to be drawn. Specifically, every index 'j' in the range '[0,n-1]' is generated, and is used for accessing the locations '3*j', '3*j+1', and '3*j+2'
 * in the 'vertices' and the 'colors' arrays. The user can increase the number 'n' of interest (cyclically up to 10) by pressing the '+' key, and can decrease it by
 * pressing the '-' key.
 */
int num=3;

/* Prototypes for all functions of interest! */
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);
void draw();

/// The main function for the <i>'Example-053 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-053' Test, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws several portions of the 'Square Annulus' shape in an OpenGL window. This shape is bounded by '2' (concentric) axis-parallel rectangles of ";
	cout<<"different size in the same spirit of a"<<endl;
	cout<<"\tcircular crown. It is often known as the 'rectangular' crown. Its large rectangle is called the 'external' rectangle, and other rectangle is called ";
	cout<<"the 'internal' rectangle. Thus, it"<<endl;
	cout<<"\trequires '8' vertices with their optional attributes (colors)."<<endl<<endl;
	cout<<"\tHere, the 'Square Annulus' shape of interest is approximated by an unique triangle strip, formed by '8' triangles, without adding any 'Steiner' point. ";
	cout<<"By construction, it is necessary to"<<endl;
	cout<<"\tenumerate a sequence of '10' points with their independent colors ('2' points and their colors are needed to be duplicated)."<<endl<<endl;
	cout<<"\tFor the sake of the efficiency, we exploit the 'vertex array' technique, provided directly by the OpenGL. This technique is used to group together ";
	cout<<"several drawing instructions into"<<endl;
	cout<<"\tonly one instruction for rendering (a subset of) the vertices and some of their state parameters. Here, we limit our attention to the Euclidean '3D' ";
	cout<<"coordinates and the colors for all '8'"<<endl;
	cout<<"\tvertices in the 'Square Annulus' shape of interest. In particular, '2' arrays are defined, containing, respectively, the Euclidean '3D' coordinates and ";
	cout<<"the colors components for all '8' 
	cout<<"\tvertices (with no redundancy). This information is stored as '8' consecutive tuples of '3' floating-point values in every array, respectively. The ";
	cout<<"locations, containing the Euclidean '3D' "<<endl;
	cout<<"\tcoordinates and the colors components for the point of index 'j % 8' (for any 'j'), are stored in positions '3 * j', '3 * j + 1', and '3 * j + 2'. ";
	cout<<"Hence, it is sufficient to access the"<<endl;
	cout<<"\tlocations, related to vertices of indices '0,...,7,0,1', in '2' arrays, mentioned above, in order to draw the triangle strip of interest. In this test, ";
	cout<<"the 'glArrayElement()' function "<<endl;
	cout<<"\tis exploited for drawing a specific vertex with its state parameters (one vertex for each instruction)."<<endl<<endl;
	cout<<"\tIn order to show the actual validity of this approach, it is possible to limit our attention only on a specific portion of the 'Square Annulus' shape, ";
	cout<<"defined by using only 'n' points, "<<endl;
	cout<<"\tsuch that 'n' is in the range '[3,10]'. This means that only a subset of all triangles in the triangle strip of interest are drawn. Broadly speaking, ";
	cout<<"every index 'j' in '[0,n-1]' is "<<endl;
	cout<<"\tgenerated in order to access the locations, corresponding to the point of index 'j % 8', in the arrays of interest."<<endl<<endl;
	cout<<"\tIn this test, it is not possible to modify the size and the position for the 'external' and the 'internal' rectangles of the 'Square Annulus' shape. ";
	cout<<"Instead, the user can:"<<endl<<endl;
	cout<<"\t\t-) increase the maximum number 'n' of points to be considered by pressing the '+' key;"<<endl;
	cout<<"\t\t-) decrease the maximum number 'n' of points to be considered by pressing the '-' key;"<<endl<<endl;
	cout<<"\tand can press cyclically the ' ' (space) key for choosing to render:"<<endl<<endl;
	cout<<"\t\t-) only the points for the desired triangles in the triangle strip of interest;"<<endl;
	cout<<"\t\t-) the 'wireframe versions' for the desired triangles in the triangle strip of interest;"<<endl;
	cout<<"\t\t-) the 'filled versions' for the desired triangles in the triangle strip of interest."<<endl<<endl;
	cout<<"\tLikewise, the window of interest can be closed by pressing any among the 'Q', the 'q', and the 'Esc' keys."<<endl<<endl;
	cout.flush();

	/* If we arrive here, we can draw the 'Square Annulus' shape of interest by using the rendering settings, chosen by the user. */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-053' Test, based on the (Old Mode) OpenGL");
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
   	glOrtho(0,100,0,100,-1,1);
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
		
			/* We update the rendering mode for the subset of triangles to be drawn in the triangle strip, approximating the 'Square Annulus' shape. */
			mode=(mode+1)%3;
			glutPostRedisplay();
			break;
		
		case '+':
		
			/* We increase the number of the vertices to be considered in the triangle strip, approximating the 'Square Annulus' shape. */
			if(num<10) num=num+1;
			else if(num==10) num=3;
			glutPostRedisplay();
			break;
		
		case '-':
		
			/* We decrease the number of the vertices to be considered in the triangle strip, approximating the 'Square Annulus' shape. */
			if(num>3) num=num-1;
			else cout<<"\tThe minimum number 'n=3' of the vertices to be considered in the triangle strip of interest is reached, and it is not possible to decrease again this number."<<endl;
			glutPostRedisplay();
			break;

		default:

			/* Other keys are not important for us */
			break;
	}
}

/// This function draws the portion of interest for the triangle strip, approximating the <i>'Square Annulus'</i> shape, in the main OpenGL window by using the rendering preferences, chosen by the user.
void draw()
{
	/* We draw the portion of interest for the triangle strip, approximating the <i>'Square Annulus'</i> shape, in the main OpenGL window by using the rendering
	 * preferences, chosen by the user. */
	glClear(GL_COLOR_BUFFER_BIT);
	if(mode==0) glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	if(mode==1) glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	if(mode==2) glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
	glPointSize(8);
	glLineWidth(2);
	glBegin(GL_TRIANGLE_STRIP);
	for(int i=0;i<num;i++) { glArrayElement(i%8); }
	glEnd();
	glFlush();
	if(mode==0) cout<<"\tThe 'filled versions' of ";
	if(mode==1) cout<<"\tThe 'wireframe versions' of ";
	if(mode==2) cout<<"\tOnly the points of ";
	cout<<"the triangles in the triangle strip of interest, defined by using only 'n="<<num<<"' vertices, are currently drawn."<<endl;
	cout.flush();
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(0.0, 0.0, 0.0, 0.0);
	mode=0;
	num=3;
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,vertices);
	glColorPointer(3,GL_FLOAT,0,colors);
	cout<<"\tAt the beginning, the 'filled versions' of the triangles in the triangle strip of interest, defined by using only 'n=3' vertices (the minimum number 'n' as possible), are drawn."<<endl<<endl;
	cout.flush();
}

