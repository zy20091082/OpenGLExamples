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
 * main.cpp - the main function for the 'Example-042 (Old Mode)' Test.
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

/// The setting for rendering all triangles in the triangle fans, used for approximating the <i>'Cone'</i> shape.
/**
 * The value of this flag may be one of the following values:
 *
 * -) the 'GL_LINE' value, used for rendering the 'wireframe versions' of all triangles in the triangle fans of interest;
 * -) the 'GL_FILL' value, used for rendering the 'filled versions' of all triangles in the triangle fans of interest.
 *
 * It is possible to cycle between these 2 renderings by pressing the 'r' key.
 */
GLenum mode=GL_FILL;

/// The number of the samples in all approximations of interest for the <i>'Cone'</i> shape.
/**
 * This value, initially set to '5', is the number of the samples in all approximations of interest for the 'Cone' shape. Broadly speaking, it is the number of vertices
 * in the triangle fans of interest. It is interactively modified by pressing the '+' and the '-' keys.
 */
unsigned int num_samples=5;

/// This flag indicates what projection we must exploit while drawing the scene.
/**
 * This flag assumes the following values:
 *
 * 0: it indicates to use the viewing orthographic box.
 * 1: it indicates to use the viewing perspective box.
 *
 * The user can choose what projection must be used by pressing cyclically the ' ' (space) key.
 */
int projection=0;

/// This flag indicates what view of the <i>'Cone'</i> shape must be rendered in the scene.
/**
 * This flag assumes the following values:
 *
 * 0: it indicates to render the 'View #0' of the 'Cone' shape along the canonical plane 'xz';
 * 1: it indicates to render the 'View #1' of the 'Cone' shape along the canonical plane 'xz' (upturned version of the 'View #0').
 * 2: it indicates to render the 'View #2' of the 'Cone' shape along the canonical plane 'yz';
 * 3: it indicates to render the 'View #3' of the 'Cone' shape along the canonical plane 'yz' (upturned version of the 'View #2').
 * 4: it indicates to render the 'View #4' of the 'Cone' shape along the canonical plane 'xy';
 * 5: it indicates to render the 'View #5' of the 'Cone' shape along the canonical plane 'xy' (upturned version of the 'View #4').
 *
 * The user can choose what view must be rendered by pressing cyclically the 'c' key.
 */
int configuration=0;

/* Prototypes for all functions of interest! */
void initialize();
void manageKeys(unsigned char key, int x, int y);
void draw();
void resize(int w,int h);

/// The main function for the <i>'Example-042 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-042' Test, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws several views of the 'Cone' shape in an OpenGL window by using the rendering settings, chosen interactively by the user. Broadly speaking, the ";
	cout<<"'Cone' shape tapers smoothly from a flat base (frequently, though not"<<endl;
	cout<<"\tnecessarily, described by a 'Circle' shape) to a given point, called the 'apex' or the 'vertex'. In other words, the 'Cone' shape is formed by a ";
	cout<<"collection of lines, connecting the 'apex' to all of the points on a base,"<<endl;
	cout<<"\twhich does not contain the 'apex'. The 'axis' of the 'Cone' shape is the line, passing through the 'apex', about which the 'Cone' shape has a circular ";
	cout<<"symmetry."<<endl<<endl;
	cout<<"\tHere, we limit our attention to a 'Cone', where the basis is described by a 'Circle' shape of radius 'R=35', and the point '(0,70,0)' as the 'apex' of the";
	cout<<" 'Cone' shape. The 'Cone' shape of interest is open, thus we consider"<<endl;
	cout<<"\tonly the boundary of the 'Circle' shape, described by the 'Circle' curve."<<endl<<endl;
	cout<<"\tIn this case, the 'Cone' shape of interest is described by a triangle fan (in 'red') with 'n' vertices. Thanks to its symmetry properties, it is ";
	cout<<"interesting to analyze (upon request) 6 views of the 'Cone' shape, in particular:"<<endl<<endl;
	cout<<"\t\t-) a view along the canonical plane 'xz' and its upturned version (indicated as the 'View #0' and the 'View #1');"<<endl;
	cout<<"\t\t-) a view along the canonical plane 'yz' and its upturned version (indicated as the 'View #2' and the 'View #3');"<<endl;
	cout<<"\t\t-) a view along the canonical plane 'xy' and its upturned version (indicated as the 'View #4' and the 'View #5');"<<endl<<endl;
	cout<<"\tin order to give a more complete overview of its properties."<<endl<<endl;
	cout<<"\tMeanwhile, it is also possible to apply (upon request) any between the orthographic and the perspective projection, since some portions of the shape may ";
	cout<<"overlap and not be visible in a specific view. Finally, it also possible"<<endl;
	cout<<"\tto render (upon request) the 'wireframe' and the 'filled versions' of all triangles in the current approximation of the 'Cone' shape. These aspects are ";
	cout<<"orthogonal, and can be combined together in several ways."<<endl<<endl;
	cout<<"\tHere, the user cannot modify the radius 'R=35' and the center for the basis of the 'Cone' shape, since they are fixed in advance. Instead, the user can:";
	cout<<endl<<endl;
	cout<<"\t\t-) choose to render a specific view of the 'Cone' shape by pressing cyclically the 'c' key;"<<endl;
	cout<<"\t\t-) choose to apply the orthographic or the perspective projection to the current view of the 'Cone' shape by pressing cyclically the ' ' (space) key;";
	cout<<endl;
	cout<<"\t\t-) choose to render the 'wireframe' or the 'filled versions' of all triangles in the current approximation of the 'Cone' shape by pressing cyclically ";
	cout<<"the 'r' key;"<<endl;
	cout<<"\t\t-) increase the number 'n' of all vertices in the triangle fans of interest by pressing the '+' key;"<<endl;
	cout<<"\t\t-) decrease the number 'n' of all vertices in the triangle fans of interest by pressing the '-' key."<<endl<<endl;
	cout<<"\tLikewise, the window of interest can be closed by pressing any among the 'Q', the 'q', and the 'Esc' keys."<<endl<<endl;
	cout.flush();
	
	/* If we arrive here, we can draw the 'Cone' shape of interest by using the rendering settings, chosen by the user. */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(600,600);
	glutCreateWindow("The 'Example-042' Test, based on the (Old Mode) OpenGL");
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
	num_samples=5;
	mode=GL_FILL;
	projection=0;
	configuration=0;
	cout<<"\tAt the beginning, ";
	if(mode==GL_FILL) cout<<"the 'filled versions' of all ";
	if(mode==GL_LINE) cout<<"the 'wireframe versions' of all ";
	cout<<"triangles in the triangle fans (formed by the minimum number 'n="<<num_samples<<"' as possible of the vertices) in the 'View #"<<configuration<<"' are ";
	cout<<"drawn by using the ";
	if(projection==0) cout<<"orthographic projection."<<endl<<endl;
	else cout<<"perspective projection."<<endl<<endl;
	cout.flush();
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '+' - '-' - ' ' (space) -'r' - 'c' keys */
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
		
		case '+':
		
		/* The key is '+', thus we increase the number 'n' of the vertices in the triangle fans of interest! */
		num_samples=num_samples+1;
		glutPostRedisplay();
		break;
		
		case '-':
		
		/* The key is '-', thus we decrease (if it is possible) the number 'n' of the vertices in the triangle fans of interest! */
		if(num_samples>5) num_samples=num_samples-1;
		else cout<<"\tThe minimum number 'n=5' of the vertices in the triangle fans of interest is reached, and it is not possible to decrease again this number."<<endl;
		glutPostRedisplay();
		break;
		
		case ' ':
		
		/* The key is ' ' (space), thus we change the projection (perspective or orthographic). */
		projection=(projection+1)%2;
		resize(600,600);
		glutInitWindowSize(600,600);
		glutPostRedisplay();
		break;
		
		case 'r':
		
		/* The key is 'r', thus we change the rendering mode to be used! */
		if(mode==GL_FILL) mode=GL_LINE;
		else mode=GL_FILL;
		glutPostRedisplay();
		break;
		
		case 'c':
		
		/* The key is 'c', thus we change the placement of the 'Cone' shape in the scene (6 possible configurations). */
		configuration=(configuration+1)%6;
		resize(600,600);
		glutInitWindowSize(600,600);
		glutPostRedisplay();
		break;
		
		default:

    	/* Other keys are not important for us! */
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
   	if(projection==1)
   	{
   		if(configuration<2) { gluPerspective(3,0.5,2,180); }
   		else if(configuration<4) { glFrustum(-10,10,-15,15,3,150); }
   		else { glFrustum(-15,15,-50,50,14,150); }
   	}
   	else if(configuration<2) { glOrtho(-45,45,-45,45,105,25); }
   	else if(configuration<4) { glOrtho(-10,80,-45,45,105,25); }
   	else { glOrtho(-45,45,-10,80,105,25); }
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}
   	
/// This function draws the <i>'Cone'</i> shape in the OpenGL window of interest by using the preferences, chosen by the user.
void draw()
{
	float d=(2*PI)/(num_samples-1);

	/* Now, we draw the 'Cone' shape of interest in the OpenGL window of interest by using the preferences, chosen by the user. */
	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK,mode);
	glColor3f(1,0,0);
	glLineWidth(1);
	glBegin(GL_TRIANGLE_FAN);
	if(configuration==0)
	{
		/* We draw the 'View #0' of the 'Cone' shape along the 'xz' plane. */
		glVertex3f(0,0,-25);
		for(int k=0;k<=num_samples;k++) { glVertex3f(35*cos(-PI+k*d),35*sin(-PI+k*d),-95); }
	}
	else if(configuration==1)
	{
		/* We draw the 'View #1' of the 'Cone' shape along the 'xz' plane (upturned version of the 'View #0'). */
		glVertex3f(0,0,-95);
		for(int k=0;k<=num_samples;k++) { glVertex3f(35*cos(-PI+k*d),35*sin(-PI+k*d),-25); }
	}
	else if(configuration==2)
	{
		/* We draw the 'View #2' of the 'Cone' shape along the 'yz' plane. */
		glVertex3f(70,0,-60);
		for(int k=0;k<=num_samples;k++) { glVertex3f(0,35*sin(-PI+k*d),35*cos(-PI+k*d)-60); }
	}
	else if(configuration==3)
	{
		/* We draw the 'View #3' of the 'Cone' shape along the 'xz' plane (upturned version of the 'View #2'). */
		glVertex3f(0,0,-60);
		for(int k=0;k<=num_samples;k++) { glVertex3f(70,35*sin(-PI+k*d),35*cos(-PI+k*d)-60); }
	}
	else if(configuration==4)
	{
		/* We draw the 'View #4' of the 'Cone' shape along the 'xy' plane. */
		glVertex3f(0,70.0,-60);
		for(int k=0;k<=num_samples;k++) { glVertex3f(35*cos(-PI+k*d),0,35*sin(-PI+k*d)-60); }
	}
	else if(configuration==5)
	{
		/* We draw the 'View #5' of the 'Cone' shape along the 'xy' plane (upturned version of the 'View #4'). */
		glVertex3f(0,0,-60);
		for(int k=0;k<=num_samples;k++) { glVertex3f(35*cos(-PI+k*d),70,35*sin(-PI+k*d)-60); }
	}
	
	/* If we arrive here, the scene is complete! */
	glEnd();
	glFlush();
	if(mode==GL_FILL) cout<<"\tThe 'filled versions' of all ";
	if(mode==GL_LINE) cout<<"\tThe 'wireframe versions' of all ";
	cout<<"triangles in the triangle fans (formed by 'n="<<num_samples<<"' vertices) in the 'View #"<<configuration<<"' are currently drawn by using the ";
	if(projection==0) cout<<"orthographic projection."<<endl;
	else cout<<"perspective projection."<<endl;
	cout.flush();
}

