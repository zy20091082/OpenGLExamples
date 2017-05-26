/*******************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 * 
 * Last update: May 2017
 *
 * This program is Free Software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.                                       
 *                                                                         
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License (http://www.gnu.org/licenses/gpl.txt) for more details.
 * 
 * main.cpp - the main function for the 'Example-039 (Old Mode)' Test.
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

/// The setting for rendering all quadrilaterals in the quad strips, used for approximating the <i>'Ring'</i> shape.
/**
 * The value of this flag may be one of the following values:
 *
 * -) the 'GL_LINE' value, used for rendering the 'wireframe versions' of all quadrilaterals in the quad strips of interest;
 * -) the 'GL_FILL' value, used for rendering the 'filled versions' of all quadrilaterals in the quad strips of interest.
 *
 * It is possible to cycle between these 2 renderings by pressing the 'r' key.
 */
GLenum mode=GL_FILL;

/// The number of the samples in all approximations of interest for the <i>'Ring'</i> shape.
/**
 * This value, initially set to '5', is the number of the samples in all approximations of interest for the 'Ring' shape. Broadly speaking, it is the number of vertices pairs in the quad strips of interest. It is interactively modified by pressing the '+' 
 * and the '-' keys.
 */
unsigned int num_samples=5;

/// This flag indicates what projection we must exploit while drawing the scene.
/**
 * This flag assumes the following values:
 *
 * 0: it indicates to use the viewing orthographic box. This latter depends on which view of the 'Ring' shape we are rendering;
 * 1: it indicates to use the viewing perspective box (frustum) [-20,20,-20,20,4,180].
 *
 * The user can choose what projection must be used by pressing cyclically the ' ' (space) key.
 */
int projection=0;

/// This flag indicates what view of the <i>'Ring'</i> shape must be rendered in the scene.
/**
 * This flag assumes the following values:
 *
 * 0: it indicates to render the 'View #0' of the 'Ring' shape along the canonical plane 'xz';
 * 1: it indicates to render the 'View #1' of the 'Ring' shape along the canonical plane 'yz';
 * 2: it indicates to render the 'View #2' of the 'Ring' shape along the canonical plane 'xy'.
 *
 * The user can choose what view must be rendered by pressing cyclically the 'c' key.
 */
int configuration=0;

/* Prototypes for all functions of interest! */
void initialize();
void manageKeys(unsigned char key, int x, int y);
void draw();
void resize(int w,int h);

/// The main function for the <i>'Example-039 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-039' Test, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws several views of the 'Ring' shape in an OpenGL window by using the rendering settings, chosen interactively by the user. Broadly speaking, the 'Ring' shape is an open cylinder without considering its basis, described by 2 'Circle'"<<endl;
	cout<<"\tcurves. Recall that a 'cylinder' is the surface formed by the points at a fixed distance 'R' (known as the 'radius' of the cylinder) from a given straight line, called the 'axis' of the cylinder. A cylinder of radius 'R' and with the 'z'"<<endl;
	cout<<"\taxis as its axis may be defined as follows:"<<endl<<endl;
	cout<<"\tx(t)= R * cos(t), y(t) = R * sin(t), z(t) = z"<<endl<<endl<<"\tfor every 't' in '[-pi,pi]' and every 'z' in '[a,b]'. Here we limit our attention to 'R=35', and every 'z' in '[0,70]'."<<endl<<endl;
	cout<<"\tIn this case, the 'Ring' shape is approximated by a quad strip (in 'red'), formed by 'n' pairs of corresponding vertices in its 2 basis, i.e., in 2 'Circle' shapes. Thanks to its symmetry properties, it is interesting to analyze (upon"<<endl;
	cout<<"\trequest) 3 views of the 'Ring' shape along the canonical planes 'xz' (the 'View #0'), 'zy' (the 'View #1'), and 'xy' (the 'View #2'), in order to give a more complete overview of its properties. Meanwhile, it is also possible to apply"<<endl;
	cout<<"\t(upon request) any between the orthographic and the perspective projection, since some portions of the shape may overlap and not be visible in a specific view. Finally, it also possible to render (upon request) the 'wireframe' and the"<<endl;
	cout<<"\t'filled versions' of all quadrilaterals in the current approximation of the 'Ring' shape. These aspects are orthogonal, and can be combined together in several ways."<<endl<<endl;
	cout<<"\tHere, the user cannot modify the radius 'R'=35' and the centers for the basis of the 'Ring' shape, since they are fixed in advance. Instead, the user can:"<<endl<<endl;
	cout<<"\t\t-) choose to render a specific view of the 'Ring' shape by pressing cyclically the 'c' key;"<<endl;
	cout<<"\t\t-) choose to apply the orthographic or the perspective projection to the current view of the 'Ring' shape by pressing cyclically the ' ' (space) key;"<<endl;
	cout<<"\t\t-) choose to render the 'wireframe' or the 'filled versions' of all quadrilaterals in the current approximation of the 'Ring' shape by pressing cyclically the 'r' key;"<<endl;
	cout<<"\t\t-) increase the number 'n' of all vertices pairs in the quad strips of interest by pressing the '+' key;"<<endl;
	cout<<"\t\t-) decrease the number 'n' of all vertices pairs in the quad strips of interest by pressing the '-' key."<<endl<<endl;
	cout<<"\tLikewise, the window of interest can be closed by pressing any among the 'Q', the 'q', and the 'Esc' keys."<<endl<<endl;
	
	/* If we arrive here, we can draw the 'Ring' shape of interest by using the rendering settings, chosen by the user. */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(600,600);
	glutCreateWindow("The 'Example-039' Test, based on the (Old Mode) OpenGL");
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
	cout<<"quadrilaterals in the quad strips (formed by the minimum number 'n="<<num_samples<<"' as possible of the vertices pairs) in the 'View #"<<configuration<<"' are drawn by using the ";
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
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case 'Q':
	
		/* The key is 'Q', thus we can exit from this program. */
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case 27:
	
		/* The key is 'Esc', thus we can exit from this program. */
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case '+':
		
		/* The key is '+', thus we increase the number 'n' of the vertices pairs in the quad strips of interest! */
		num_samples=num_samples+1;
		glutPostRedisplay();
		break;
		
		case '-':
		
		/* The key is '-', thus we decrease (if it is possible) the number 'n' of the vertices pairs in the quad strips of interest! */
		if(num_samples>5) num_samples=num_samples-1;
		else cout<<"\tThe minimum number 'n=5' of the vertices pairs in the quad strips of interest is reached, and it is not possible to decrease again this number."<<endl;
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
		
		/* The key is 'c', thus we change the placement of the 'Ring' shape in the scene (3 possible configurations). */
		configuration=(configuration+1)%3;
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
   	if(projection==1) { glFrustum(-20,20,-20,20,4,180); }
   	else if(configuration==0) { glOrtho(-45,45,-10,80,105,25); }
   	else if(configuration==1) { glOrtho(-10,80,-45,45,105,25); }
   	else { glOrtho(-45,45,-45,45,105,25); }
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function draws the <i>'Ring'</i> shape in the OpenGL window of interest by using the preferences, chosen by the user.
void draw()
{
	float d=(2*PI)/(num_samples);

	/* Now, we draw the 'Ring' shape of interest in the OpenGL window of interest by using the preferences, chosen by the user. */
	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK,mode);
	glColor3f(1,0,0);
	glLineWidth(1);
	glBegin(GL_QUAD_STRIP);
	if(configuration==0)
	{
		/* We draw the 'View #0' of the 'Ring' shape along the 'xz' plane. */
		for(int k=0;k<=num_samples;k++) 
		{ 
			glVertex3f(35*cos(-PI+k*d),0,35*sin(-PI+k*d)-60); 
			glVertex3f(35*cos(-PI+k*d),70,35*sin(-PI+k*d)-60);
		}
	}
	else if(configuration==1)
	{
		/* We draw the 'View #1' of the 'Ring' shape along the 'zy' plane. */
		for(int k=0;k<=num_samples;k++)
		{
			glVertex3f(0,35*sin(-PI+k*d),35*cos(-PI+k*d)-60);
			glVertex3f(70,35*sin(-PI+k*d),35*cos(-PI+k*d)-60);
		}
	}
	else
	{
		/* We draw the 'View #2' of the 'Ring' shape along the 'xy' plane. */
		for(int k=0;k<=num_samples;k++)
		{
			glVertex3f(35*cos(-PI+k*d),35*sin(-PI+k*d),-95);
			glVertex3f(35*cos(-PI+k*d),35*sin(-PI+k*d),-25);
		}
	}
	
	/* If we arrive here, the scene is complete! */
	glEnd();
	glFlush();
	if(mode==GL_FILL) cout<<"\tThe 'filled versions' of all ";
	if(mode==GL_LINE) cout<<"\tThe 'wireframe versions' of all ";
	cout<<"quadrilaterals in the quad strips (formed by 'n="<<num_samples<<"' vertices pairs) in the 'View #"<<configuration<<"' are currently drawn by using the ";
	if(projection==0) cout<<"orthographic projection."<<endl;
	else cout<<"perspective projection."<<endl;
	cout.flush();
}
