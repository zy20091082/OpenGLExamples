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
 * main.cpp - the main function for the 'Example-056 (Old Mode)' Test.
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

/// The custom settings for rendering the triangle and the desidered polygons in the quad strip of interest.
/**
 * The value of this flag may be one of the following values:
 * 
 * -) the '0' value, used for rendering the 'filled versions' of the triangle and the desired polygons in the quad strip of interest to be drawn, approximating the
 * 	  'Square Annulus' shape;
 * -) the '1' value, used for rendering the 'wireframe versions' of the triangle and the desired polygons in the quad strip of interest to be drawn, approximating the
 * 	  'Square Annulus' shape;
 * -) the '2' value, used for rendering only the vertices of the triangle and the desired polygons in the quad strip of interest to be drawn, approximating the
 * 	  'Square Annulus' shape;
 * 
 * The user can choose what rendering has to be exploited by pressing cyclically the ' ' (space) key.
 */
int mode=0;

/// The Euclidean 3D coordinates for all points in the quad strip of interest, approximating the <i>'Square Annulus'</i> shape.
/**
 * The Euclidean 3D coordinates for all points in the quad strip of interest, approximating the 'Square Annulus' shape, are stored as consecutive 3 floating-point values.
 * In particular, the Euclidean 3D coordinates, related to the point of index (j % 8), for any j, are stored in locations '3*j' - '3*j+1' - '3*j+2' within this array.
 * Instead, the colors for all points of interest are stored in the 'colors' array by using a similar approach.
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

/// The colors components for all points in the quad strip of interest, approximating the <i>'Square Annulus'</i> shape.
/**
 * The colors components for all points in the quad strip of interest, approximating the 'Square Annulus' shape, are stored as consecutive 3 floating-point values. In
 * particular, the color components, related to the point of index (j % 8), for any j, are stored in locations '3*j' - '3*j+1' - '3*j+2' within this array. Instead, the
 * Euclidean 3D coordinates for all points of interest are stored in the 'vertices' array by using a similar approach.
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

/// The number <i>'n'</i> for the subset of points to be considered in the quad strip of interest, approximating the <i>'Square Annulus'</i> shape.
/**
 * This value is the number 'n' of indices to be considered in the quad strip of interest, approximating the 'Square Annulus' shape. This value belongs to the range
 * '[4,n-1]' in order to access the 'vertices' and the 'colors' arrays in order to limit the quadrilaterals number to be drawn. Specifically, every index 'j' in the
 * range '[0,n-1]' is generated, and is used for accessing the locations '3*j', '3*j+1', and '3*j+2' in the 'vertices' and the 'colors' arrays. The user can increase
 * the number 'n' of interest (cyclically up to 10) by pressing the '+' key, and can decrease it bypressing the '-' key.
 *
 * In order to implement correctly the 'vertex array' technique in this test, we consider only 'n' locations in the array 'inds' (see later).
 */
int num=4;

/// The indices for the locations to be considered in the arrays, necessary for implementing the <i>'vertex array'</i> technique.
/**
 * This array contains the indices for the locations to be considered in the quad strip of interest, approximating the 'Square Annulus' shape. Broadly speaking, they are
 * useful for drawing the desired portion of the 'Square Annulus' shape by using the 'vertex array' technique in this test. Specifically, the indices of interest are
 * used for accessing the locations of interest in the 'vertices' and the 'colors' arrays.
 *
 * In other words, we consider only 'n' locations of this array in order to implement correctly the 'vertex array' technique in this test.
 */
static unsigned int inds[10] = { 0,1,2,3,4,5,6,7,0,1 };

/// The interwined array, containing the Euclidean <i>'3D'</i> coordinates and the colors components for drawing the unique triangle in the scene
/**
 * This (interwined) array contains the Euclidean 3D coordinates and the colors components (i.e., floating-point values) for drawing the unique triangle in the scene by
 * using the 'vertex array' technique. By construction, the Euclidean 3D components for the vertex of index (j % 3), for any j, are stored in the locations of indices
 * '3*j', '3*j+1', and '3*j+2'. Instead, the corresponding color components are stored in the locations of indices '3*j+3', '3*j+4', and '3*j+5'.
 * 
 * Here, all locations of this array are always considered.
 */
static float trg[]= {
	40, 40, 0, 0, 1, 1,
	60, 40, 0, 1, 0, 0,
	60, 60, 0, 0, 1, 0 };

/* Prototypes for all functions of interest! */
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);
void draw();

/// The main function for the <i>'Example-056 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-056' Test, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws several portions of a custom shape, formed by a single triangle and the 'Square Annulus' shape (not connected together), in an OpenGL window. ";
	cout<<"This latter is bounded by '2' "<<endl;
	cout<<"\t(concentric) axis-parallel rectangles of different size in the same spirit of a circular crown. It is often known as the 'rectangular' crown. Its large ";
	cout<<"rectangle is called the 'external'"<<endl;
	cout<<"\trectangle, and other rectangle is called the 'internal' rectangle. Thus, it requires '8' vertices with their optional attributes (colors)."<<endl<<endl;
	cout<<"\tHere, the 'Square Annulus' shape of interest is approximated by an unique quad strip, formed by '4' quadrilaterals, without adding any 'Steiner' ";
	cout<<"point. By construction, it is necessary"<<endl;
	cout<<"\tto enumerate a sequence of '10' points with their independent colors ('2' points and their colors are needed to be duplicated)."<<endl<<endl;
	cout<<"\tFor the sake of the efficiency, we exploit the 'vertex array' technique, provided directly by the OpenGL, for modeling both the triangle and the quad ";
	cout<<"strip of interest. This technique is "<<endl;
	cout<<"\tused to group together several drawing instructions into only one instruction for rendering (a subset of) the vertices and some of their state ";
	cout<<"parameters. Here, we limit our attention to"<<endl;
	cout<<"\tthe Euclidean '3D' coordinates and the colors for all '8' vertices in the 'Square Annulus' shape of interest, as well as for '3' vertices in the ";
	cout<<"triangle."<<endl<<endl;
	cout<<"\tHere, we exploit '2' different types of the 'vertex array' technique. When modeling the triangle, we exploit an array of '18' locations, containing the ";
	cout<<"interleaving of the Euclidean '3D'"<<endl;
	cout<<"\tcoordinates and the colors components for every vertex. In this case, the 'glDrawArrays()' function is exploited for drawing directly the content of ";
	cout<<"this array without using another"<<endl;
	cout<<"\tindirection level Instead, when modeling the quad strip of interest, '2' arrays are defined, containing, respectively, the Euclidean '3D' coordinates ";
	cout<<"and the colors components for all '8'"<<endl;
	cout<<"\tvertices (with no redundancy). This information is stored as '8' consecutive tuples of '3' floating-point values in every array, respectively. The ";
	cout<<"locations, containing the Euclidean '3D'"<<endl;
	cout<<"\tcoordinates and the color components for the point of index 'j % 8' (for any 'j'), are stored in positions '3 * j', '3 * j + 1', and '3 * j + 2'. ";
	cout<<"Hence, it is sufficient to access the "<<endl;
	cout<<"\tlocations, related to vertices of indices '0,...,7,0,1', in '2' arrays, mentioned above, in order to draw the quad strip of interes by using the ";
	cout<<"'glDrawElement()' function. This is done"<<endl;
	cout<<"\tby a single instruction, and requires the list of indices to the vertices to be considered, as mentioned above."<<endl<<endl;
	cout<<"\tIn order to show the actual validity of this approach, it is possible to limit our attention only on a specific portion of the 'Square Annulus' shape, ";
	cout<<"defined by using only 'n' points,"<<endl;
	cout<<"\tsuch that 'n' is in the range '[3,10]'. This means that only a subset of all quadrilaterals in the quad strip of interest are drawn. Broadly speaking, ";
	cout<<"every index 'j' in '[0,n-1]' is "<<endl;
	cout<<"\tgenerated in order to access the locations, corresponding to the point of index 'j % 8', in the arrays of interest. These indices 'j' are passed as ";
	cout<<"argument to the unique invocation of the"<<endl;
	cout<<"\t'glDrawElement()' function in the code, which automatically takes into the account their corresponding state parameters. Instead, the array, necessary ";
	cout<<"for modeling the triangle, is always"<<endl;
	cout<<"\tconsidered interely by the 'glDrawArrays()' function."<<endl<<endl;
	cout<<"\tIn this test, it is not possible to modify the size and the position for the 'external' and the 'internal' rectangles of the 'Square Annulus' shape. ";
	cout<<"Instead, the user can:"<<endl<<endl;
	cout<<"\t\t-) increase the maximum number 'n' of points to be considered by pressing the '+' key;"<<endl;
	cout<<"\t\t-) decrease the maximum number 'n' of points to be considered by pressing the '-' key;"<<endl<<endl;
	cout<<"\tand can press cyclically the ' ' (space) key for choosing to render:"<<endl<<endl;
	cout<<"\t\t-) only the points for the triangle and the desired polygons in the quad strip of interest;"<<endl;
	cout<<"\t\t-) the 'wireframe versions' for the triangle and the desired polygons in the quad strip of interest;"<<endl;
	cout<<"\t\t-) the 'filled versions' for the triangle and the desired polygons in the quad strip of interest."<<endl<<endl;
	cout<<"\tLikewise, the window of interest can be closed by pressing any among the 'Q', the 'q', and the 'Esc' keys."<<endl<<endl;
	cout.flush();

	/* If we arrive here, we can draw the 'Square Annulus' and the 'Triangle' shapes of interest by using the rendering settings, chosen by the user. */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-056' Test, based on the (Old Mode) OpenGL");
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
		
			/* We update the rendering mode for the triangle and the the subset of polygons to be drawn in the quad strip, approximating the 'Square Annulus' shape. */
			mode=(mode+1)%3;
			glutPostRedisplay();
			break;
		
		case '+':
		
			/* We increase the number of the vertices to be considered in the quad strip, approximating the 'Square Annulus' shape. */
			if(num<10) num=num+2;
			else if(num==10) num=4;
			glutPostRedisplay();
			break;
		
		case '-':
		
			/* We decrease the number of the vertices to be considered in the quad strip, approximating the 'Square Annulus' shape. */
			if(num>4) num=num-2;
			else cout<<"\tThe minimum number 'n=4' of the vertices to be considered in the quad strip of interest is reached, and it is not possible to decrease again this number."<<endl;
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
	glClearColor(0.0, 0.0, 0.0, 0.0);
	mode=0;
	num=4;
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	cout<<"\tAt the beginning, the 'filled versions' of the triangle and the polygons in the quad strip of interest, defined by using only 'n=4' vertices (the minimum number 'n' as possible), are drawn."<<endl<<endl;
	cout.flush();
}

/// This function draws the triangle and the portion of interest for the quad strip, approximating the <i>'Square Annulus'</i> shape, in the main OpenGL window by using the rendering preferences, chosen by the user.
void draw()
{
	/* We draw the triangle and the portion of interest for the quad strip, approximating the 'Square Annulus' shape, in the main OpenGL window by using the rendering
 	 * preferences, chosen by the user. */
	glClear(GL_COLOR_BUFFER_BIT);
	if(mode==0) glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	if(mode==1) glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	if(mode==2) glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
	glPointSize(8);
	glLineWidth(2);

	/* Now, we draw the desired portion of the quad strip, approximating the 'Square Annulus' shape! */
	glVertexPointer(3,GL_FLOAT,0,vertices);
	glColorPointer(3,GL_FLOAT,0,colors);
	glDrawElements(GL_QUAD_STRIP,num,GL_UNSIGNED_INT,inds);

	/* Now, we draw the unique triangle in the scene! */
	glVertexPointer(3,GL_FLOAT,6*sizeof(float),&trg[0]);
	glColorPointer(3,GL_FLOAT,6*sizeof(float),&trg[3]);
	glDrawArrays(GL_TRIANGLES,0,3);

	/* If we arrive here, then the scene is complete! */
	glFlush();
	if(mode==0) cout<<"\tThe 'filled versions' of ";
	if(mode==1) cout<<"\tThe 'wireframe versions' of ";
	if(mode==2) cout<<"\tOnly the points of ";
	cout<<"the triangle and the polygons in the quad strip of interest, defined by using only 'n="<<num<<"' vertices, are currently drawn."<<endl;
	cout.flush();
}

