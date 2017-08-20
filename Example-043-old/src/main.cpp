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
 * main.cpp - the main function for the 'Example-043 (Old Mode)' Test.
 *******************************************************************************************************************************************************/

/* First, we must understand which platform we are using. */
#include <cstdlib>
#include <iostream>
#include <cmath>
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

/// The coordinates for the center <i>'(xc,yc,zc)'</i> of the <i>'Sphere'</i> shape.
/**
 * These values are the coordinates for the center '(xc,yc,zc)' of the 'Sphere' shape. This latter can be:
 *
 * -) translated along any of '2' directions of the X-axis by pressing the 'left' and the 'right' (arrow) keys, respectively;
 * -) translated along any of '2' directions of the Y-axis by pressing the 'up' and the 'down' (arrow) keys, respectively.
 *
 * These values can be resetted by pressing the 'r' key, as well as the rotation angle (see later).
 */
float xc=0.0,yc=0.0;

/// The rotation angle for rotating the <i>'Sphere'</i> shape.
/**
 * This value indicates the angle for rotating the 'Sphere' shape along the custom axis '[1,1,1]' by pressing the ' ' key. This value can be resetted by pressing the 'r'
 * key, as well as the coordinates for the center '(xc,yc,zc)' of the 'Sphere' shape (see before).
 */
float Angle=0.0;

/* Prototypes for all functions of interest! */
void initialize();
void manageKeys(unsigned char key, int x, int y);
void manageSpecialKeys(int key,int x,int y);
void draw();
void resize(int w,int h);

/// The main function for the <i>'Example-043 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-043' Test, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws the 'Sphere' shape in an OpenGL window. Intuitively, the 'Sphere' shape describes a perfectly round geometrical object in the 3D space, that is ";
	cout<<"the surface of a completely round ball. Like the 'Circle' shape, which"<<endl;
	cout<<"\tgeometrically is an object in the 2D space, the 'Sphere' shape is defined mathematically as the set of 3D points, that are all at the same distance 'R' ";
	cout<<"from a given point '(xc,yc,zc)'. The distance 'R' is the 'radius' of the"<<endl;
	cout<<"\t'Sphere' shape, and the point '(xc,yc,zc)' is its 'center'."<<endl<<endl;
	cout<<"\tHere, the 'Sphere' shape is drawn by exploiting the 'glutWireSphere()' function, offered by the OpenGL Utility Toolkit (GLUT) package (or the FreeGLUT";
	cout<<" package). This function approximates the 'Sphere' shape through a quad grid,"<<endl;
	cout<<"\tformed by 'slices' around the Z-axis (similar to the longitudinal lines) and by 'stacks' along the Z-axis (similar to the latitudinal lines). ";
	cout<<"Specifically, the 'wireframe versions' of the quadrilaterals in the quad grid (in"<<endl;
	cout<<"\t'blue') are rendered by using the perspective projection."<<endl<<endl;
	cout<<"\tHere, the user cannot modify the radius 'R, the center '(xc,yc,zc)', and the numbers of the 'slices' and the 'stacks' in the approximation of interest for";
	cout<<"the 'Sphere' shape, since they are fixed in advance. Instead, the user"<<endl;
	cout<<"\tcan apply several transformations to the scene, in particular, the user can:"<<endl<<endl;
	cout<<"\t\t-) translate the center '(xc,yc,zc)' of the 'Sphere' shape along any of '2' directions of the X-axis by pressing the 'left' and the 'right' (arrow) ";
	cout<<"keys, respectively;"<<endl;
	cout<<"\t\t-) translate the center '(xc,yc,zc)' of the 'Sphere' shape along any of '2' directions of the Y-axis by pressing the 'up' and the 'down' (arrow) keys, ";
	cout<<"respectively;"<<endl;
	cout<<"\t\t-) rotate the 'Sphere' shape along the custom axis '[1,1,1]' by pressing the ' ' (space) key;"<<endl;
	cout<<"\t\t-) reset all transformations, applied to the 'Sphere' shape, by pressing the 'r' key."<<endl<<endl;
	cout<<"\tLikewise, the window of interest can be closed by pressing any among the 'Q', the 'q', and the 'Esc' keys."<<endl<<endl;
	cout.flush();
	
	/* If we arrive here, then we can draw the 'Sphere' shape of interest by using the rendering settings, chosen by the user. */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-043' Test, based on the (Old Mode) OpenGL");
	glutReshapeFunc(resize);
	glutKeyboardFunc(manageKeys);
	glutSpecialFunc(manageSpecialKeys);
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
	xc=0.0;
	yc=0.0;
	Angle=0.0;
	cout<<"\tAt the beginning, the 'Sphere' shape is drawn by exploiting the rotation angle "<<Angle<<", the translation value "<<xc<<" along the x-axis, and the ";
	cout<<"translation value "<<yc<<" along the y-axis."<<endl<<endl;
	cout.flush();
}

/// This function updates the viewport for the scene when it is resized. */
void resize(int w, int h)
{
	/* We update only the projection matrix! */
	glViewport(0, 0, w, h); 
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
}

/// This function is the keyboard input processing routine for the OpenGL window of interest (non-ASCII keys).
void manageSpecialKeys(int key, int x, int y)
{
	/* We are interested only in the 'up' - 'down' - 'left' - 'right' arrows. */
	switch(key)
	{
		case GLUT_KEY_UP:
		
			/* The special key is the 'up' arrow. Thus, we increase the 'yc' translation value (towards the positive y-values) and redraw the scene. */
			yc+=0.1;
			glutPostRedisplay();
			break;
			
		case GLUT_KEY_DOWN:
		
			/* The special key is the 'down' arrow. Thus, we decrease the 'yc' translation value (towards the negative y-values) and redraw the scene. */
			yc-=0.1;
			glutPostRedisplay();
			break;
			
		case GLUT_KEY_LEFT:
		
			/* The special key is the 'left' arrow. Thus, we decrease the 'xc' translation value (towards the negative x-values) and redraw the scene  */
			xc-=0.1;
			glutPostRedisplay();
			break;
			
		case GLUT_KEY_RIGHT:
		
			/* The special key is the 'right' arrow. Thus, we increase the 'xc' translation value (towards the positive x-values) and redraw the scene. */
			xc+=0.1;
			glutPostRedisplay();
			break;
		
		default:
		
			/* Other keys are not important for us */
			break;
	}
}

/// This function is the keyboard input processing routine for the OpenGL window of interest (ASCII keys).
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - ' ' (space) -'r' keys */
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
		
		case 'r':

			/* The key is 'r', thus we reset the rotation angle along the custom axis '[1,1,1]' and the translations of the center '(xc,yc,zc)' along the x- and the 
			 * y-axis. */
			xc=0;
			yc=0;
			Angle=0;
			glutPostRedisplay();
			break;
		
		case ' ':
		
			/* The key is ' ' (space), thus we increase the rotation angle along the custom axis '[1,1,1]'. */
			Angle+=10.0;
			glutPostRedisplay();
			break;
		
		default:
		
			/* Other keys are not important for us */
			break;
	}
}

/// This function draws the <i>'Sphere'</i> shape in the OpenGL window of interest by using the preferences, chosen by the user.
void draw()
{
	/* Now, we draw the 'Sphere' shape in the OpenGL window of interest by using the preferences, chosen by the user. */
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
   	glTranslatef(xc, yc, -5.0);
   	glRotatef(Angle, 1.0, 1.0, 1.0);
   	glColor3f(0,0,1);
   	glutWireSphere(1, 16, 10);
   	glutSwapBuffers();
   	cout<<"\tThe 'Sphere' shape is currently drawn by exploiting the rotation angle "<<Angle<<", the translation value "<<xc<<" along the x-axis, and the translation ";
	cout<<"value "<<yc<<" along the y-axis."<<endl;
	cout.flush();
}

