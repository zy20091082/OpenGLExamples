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
 * main.cpp - the main function for the 'Example-051 (Old Mode)' Test.
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

/// The custom settings for rendering all triangles in the triangle strip of interest, approximating the <i>'Square Annulus'</i> shape.
/**
 * The value of this flag may be one of the following values:
 * 
 * -) the '0' value, used for rendering the 'filled versions' of all triangles in the triangle strip of interest to be drawn, approximating the 'Square Annulus' shape;
 * -) the '1' value, used for rendering the 'wireframe versions' of all triangles in the triangle strip of interest to be drawn, approximating the 'Square Annulus'
 * shape;
 * -) the '2' value, used for rendering only the vertices of all triangles in the triangle strip of interest to be drawn, approximating the 'Square Annulus' shape.
 * 
 * The user can choose what rendering has to be exploited by pressing cyclically the ' ' (space) key.
 */
int mode=0;

/* Prototypes for all functions of interest! */
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);
void draw();

/// The main function for the <i>'Example-051 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-051' Test, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws several versions of the 'Square Annulus' shape in an OpenGL window. This shape is bounded by 2 (concentric) axis-parallel rectangles of different size in the same spirit of a circular ";
	cout<<"crown. It is often known as the 'rectangular' crown. Its"<<endl; 
	cout<<"\tlarge rectangle is called the 'external' rectangle, and other rectangle is called the 'internal' rectangle. Thus, it requires 8 vertices with their optional attributes (colors)."<<endl<<endl;
	cout<<"\tHere, the 'Square Annulus' shape of interest is approximated by an unique triangle strip, formed by '8' triangles, without adding any 'Steiner' point. By construction, it is necessary to enumerate ";
	cout<<"a sequence of '10' points with their independent colors"<<endl; 
	cout<<"\t('2' points and their colors are needed to be duplicated). This is done explicitly. This technique works perfectly, but it is not easy to be customized for a different number of vertices, or for a ";
	cout<<"different colors palette."<<endl<<endl;
	cout<<"\tIn this test, it is not possible to modify the size and the position for the 'external' and the 'internal' rectangles of the 'Square Annulus' shape. Instead, the user can decide interactively to ";
	cout<<"render:"<<endl<<endl;
	cout<<"\t\t-) only the points in the triangle strip of interest, approximating the 'Square Annulus' shape;"<<endl;
	cout<<"\t\t-) the 'wireframe versions' of all triangles in the triangle strip of interest, approximating the 'Square Annulus' shape;"<<endl;
	cout<<"\t\t-) the 'filled versions' of all triangles in the triangle strip of interest, approximating the 'Square Annulus' shape;"<<endl<<endl;
	cout<<"\tby pressing cyclically the ' ' (space) key."<<endl<<endl<<"\tLikewise, the window of interest can be closed by pressing any among the 'Q', the 'q', and the 'Esc' keys."<<endl<<endl;
	cout.flush();

	/* If we arrive here, we can draw the 'Square Annulus' shape of interest by using the rendering settings, chosen by the user. */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-051' Test, based on the (Old Mode) OpenGL");
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

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(0.0, 0.0, 0.0, 0.0);
	mode=0;
	cout<<"\tAt the beginning, the 'filled versions' for all triangles in the triangle strip of interest, approximating the 'Square Annulus' shape, are rendered in the scene."<<endl<<endl;
	cout.flush();
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - ' ' (space) keys. */
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
		
		/* We update the rendering mode for all triangles in the triangle strip, approximating the 'Square Annulus' shape. */
		mode=(mode+1)%3;
		glutPostRedisplay();
		break;

		default:

    	/* Other keys are not important for us */
    	break;
	}
}

/// This function draws all triangles in a triangle strip, approximating the <i>'Square Annulus'</i> shape, in the OpenGL window of interest by using the rendering preferences, chosen by the user.
void draw()
{
	/* We draw all triangles in a triangle strip, approximating the 'Square Annulus' shape, in the OpenGL window of interest by using the rendering preferences, chosen by the user. */
	glClear(GL_COLOR_BUFFER_BIT);
	if(mode==0) glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	if(mode==1) glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	if(mode==2) glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
	glPointSize(8);
	glLineWidth(2);
	glBegin(GL_TRIANGLE_STRIP);
	
	/* We draw Point #0 with coordinates (30,30,0) and color (1,1,1). */
	glColor3f(1,1,1);
	glVertex3f(30,30,0);
	
	/* We draw Point #1 with coordinates (10,10,0) and color (1,0,0). */
	glColor3f(1,0,0);
	glVertex3f(10,10,0);
	
	/* We draw Point #2 with coordinates (70,30,0) and color (0,1,0). */
	glColor3f(0,1,0);
	glVertex3f(70,30,0);
	
	/* We draw Point #3 with coordinates (90,10,0) and color (0,0,1). */
	glColor3f(0,0,1);
	glVertex3f(90,10,0);
	
	/* We draw Point #4 with coordinates (70,70,0) and color (1,1,0). */
	glColor3f(1,1,0);
	glVertex3f(70,70,0);
	
	/* We draw Point #5 with coordinates (90,90,0) and color (1,0,1). */
	glColor3f(1,0,1);
	glVertex3f(90,90,0);
	
	/* We draw Point #6 with coordinates (30,70,0) and color (0,1,1). */
	glColor3f(0,1,1);
	glVertex3f(30,70,0);
	
	/* We draw Point #7 with coordinates (10,90,0) and color (1,0,0). */
	glColor3f(1,0,0);
	glVertex3f(10,90,0);
	
	/* We draw Point #0 (again) with coordinates (30,30,0) and color (1,1,1). */
	glColor3f(1,1,1);
	glVertex3f(30,30,0);
	
	/* We draw Point #1 (again) with coordinates (10,10,0) and color (1,0,0). */
	glColor3f(1,0,0);
	glVertex3f(10,10,0);
	
	glEnd();
	glFlush();
	if(mode==2) cout<<"\tOnly the vertices of all triangles in the triangle strip of interest, approximating the 'Square Annulus' shape, are currently rendered in the scene."<<endl;
	if(mode==1) cout<<"\tThe 'wireframe versions' of all triangles in the triangle strip of interest, approximating the 'Square Annulus' shape, are currently rendered in the scene."<<endl;
	if(mode==0) cout<<"\tThe 'filled versions' of all triangles in the triangle strip of interest, approximating the 'Square Annulus' shape, are currently rendered in the scene."<<endl;
}
