/*******************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 * 
 * Last update: March 2017
 *
 * This program is Free Software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.                                       
 *                                                                         
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License (http://www.gnu.org/licenses/gpl.txt) for more details.
 * 
 * main.cpp - the main function for the 'Example-015 (Old Mode)' example.
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

	/* We are not using a MacOSX platform. Thus, we have a generic Unix-like platform, like the GNU Linux, or a Microsoft Windows platform. */
	#include "GL/glew.h"
	#include "GL/glut.h"
	#include "GL/gl.h"

#endif

/* Prototypes for all functions of interest! */
void draw();
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);
GLenum face,mode;

/// The main function for the <i>'Example-015 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-015' Example, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws a custom shape, approximated by a triangle fan (in 'turquoise gray', and with the reference vertex in 'red'), and it allows to modify its rendering as follows:"<<endl<<endl;
	cout<<"\t-) only the 'front' side of the triangles in the triangle fan of interest is rendered by pressing the 'f' and the 'F' keys;"<<endl;
	cout<<"\t-) only the 'back' side of the triangles in the triangle fan of interest is rendered by pressing the 'b' and the 'B' keys;"<<endl;
	cout<<"\t-) both the 'front' and the 'back' sides of the triangles in the triangle fan of interest are rendered by pressing the 't' and the 'T' keys;"<<endl;
	cout<<"\t-) only the vertices of the triangles in the triangle fan of interest are rendered by pressing the 'p' and the 'P' keys;"<<endl;
	cout<<"\t-) only the edges of the triangles in the triangle fan of interest are rendered (wireframe version) by pressing the 'l' and the 'L' keys;"<<endl;
	cout<<"\t-) the triangles in the triangle fan of interest are entirely rendered (filled version) by pressing the 'i' and the 'I' keys."<<endl<<endl;
	cout<<"\tIt is possible to end this program by pressing one among the 'Q' - 'q' - 'Esc' keys."<<endl<<endl;
	cout.flush();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(480,480);
	glutCreateWindow("The 'Example-015' Example, based on the (Old Mode) OpenGL");
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
	/* We update the projections and the modeling matrices! */
	glViewport(0, 0, w, h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glOrtho(0,140,0,120,-1,1);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function draws a custom shape, approximated by a triangle fan (in <i>'turquoise gray'</i>, and with the reference vertex in <i>'red'</i>), in the OpenGL window of interest by using the rendering preferences, chosen by the user.
void draw()
{
	/* We draw a custom shape, approximated by a triangle fan (in 'turquoise gray', and with the reference vertex in 'red'), in the OpenGL window of interest by using the rendering preferences, chosen by the user. */
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(10.0);
	glLineWidth(2.0);
	glColor3f(0.6,0.7,0.7);
	glPolygonMode(face,mode);
	glPolygonMode(face,mode);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0,0.0,0.0);
	glVertex3f(10.0, 10.0, 0.0);
	glColor3f(0.6,0.7,0.7);
	glVertex3f(35.0, 110.0, 0.0); 
	glVertex3f(75.0, 95.0, 0.0);
	glVertex3f(100.0, 50.0, 0.0);
	glVertex3f(110.0, 30.0, 0.0);
	glEnd();
	glFlush();
	glFlush();
	if(face==GL_FRONT)
	{
		/* We analyze only the 'front' side of the triangles in the triangle fan, approximating the custom shape of interest. */
		if(mode==GL_POINT) cout<<"\tOnly the points in the 'front' side of the triangles in the triangle fan, approximating the custom shape of interest, are rendered in the current scene."<<endl;
		if(mode==GL_LINE) cout<<"\tOnly the edges in the 'front' side of the triangles in the triangle fan, approximating the custom shape of interest, are rendered (wireframe version) in the current scene."<<endl;
		if(mode==GL_FILL) cout<<"\tOnly the 'front' side of the triangles in the triangle fan, approximating the custom shape of interest, is completely rendered (filled version) in the current scene."<<endl;
		cout.flush();
	}
	else if(face==GL_BACK)
	{
		/* We analyze only the 'back' side of the triangles in the triangle fan, approximating the custom shape of interest. */
		if(mode==GL_POINT) cout<<"\tOnly the points in the 'back' side of the triangles in the triangle fan, approximating the custom shape of interest, are rendered in the current scene."<<endl;
		if(mode==GL_LINE) cout<<"\tOnly the edges in the 'back' side of the triangles in the triangle fan, approximating the custom shape of interest, are rendered (wireframe version) in the current scene."<<endl;
		if(mode==GL_FILL) cout<<"\tOnly the 'back' side of the triangles in the triangle fan, approximating the custom shape of interest, is completely rendered (filled version) in the current scene."<<endl;
		cout.flush();
	}
	else
	{
		/* We analyze both the 'front' and the 'back' sides of the triangles in the triangle fan, approximating the custom shape of interest. */
		if(mode==GL_POINT) cout<<"\tOnly the points in both the 'front' and the 'back' sides of the triangles in the triangle fan, approximating the custom shape of interest, are rendered in the current scene."<<endl;
		if(mode==GL_LINE) cout<<"\tOnly the edges in both the 'front' and the 'back' sides of the triangles in the triangle fan, approximating the custom shape of interest, are rendered (wireframe version) in the current scene."<<endl;
		if(mode==GL_FILL) cout<<"\tBoth the 'front' and the 'back' sides of the triangles in the triangle fan, approximating the custom shape of interest, are completely rendered (filled version) in the current scene."<<endl;
		cout.flush();
	}
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	face=GL_FRONT_AND_BACK;
	mode=GL_FILL;
	cout<<"\tInitially, both the 'front' and the 'back' sides of the triangles in the triangle fan, approximating the custom shape of interest, are completely filled (filled version) in the current scene."<<endl<<endl;
	cout.flush();
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - 'f' - 'F' - 'b' - 'F' - 't' - 'T' - 'i' - 'I' - 'l' - 'L' - 'P' - 'p' keys. */
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
		
		case 'F':

		/* The key is 'F', thus we draw only the 'front' side of the triangles in the triangle fan, approximating the custom shape of interest. */
		face=GL_FRONT;
		glutPostRedisplay();
		break;
		
		case 'f':

		/* The key is 'f', thus we draw only the 'front' side of the triangles in the triangle fan, approximating the custom shape of interest. */
		face=GL_FRONT;
		glutPostRedisplay();
		break;
		
		case 'B':

		/* The key is 'B', thus we draw only the 'back' side of the triangles in the triangle fan, approximating the custom shape of interest. */
		face=GL_BACK;
		glutPostRedisplay();
		break;
		
		case 'b':

		/* The key is 'b', thus we draw only the 'back' side of the triangles in the triangle fan, approximating the custom shape of interest. */
		face=GL_BACK;
		glutPostRedisplay();
		break;
		
		case 'T':

		/* The key is 'T', thus we draw both the 'front' and the 'back' sides of the triangles in the triangle fan, approximating the custom shape of interest. */
		face=GL_FRONT_AND_BACK;
		glutPostRedisplay();
		break;
		
		case 't':

		/* The key is 't', thus we draw both the 'front' and the 'back' sides of the triangles in the triangle fan, approximating the custom shape of interest. */
		face=GL_FRONT_AND_BACK;
		glutPostRedisplay();
		break;
		
		case 'I':

		/* The key is 'I', thus we completely render the triangles in the triangle fan (filled version), approximating the custom shape of interest. */
		mode=GL_FILL;
		glutPostRedisplay();
		break;
		
		case 'i':

		/* The key is 'i', thus we completely render the triangles in the triangle fan (filled version), approximating the custom shape of interest. */
		mode=GL_FILL;
		glutPostRedisplay();
		break;
		
		case 'L':

		/* The key is 'L', thus we render only the edges of the triangles in the triangle fan (wireframe version), approximating the custom shape of interest. */
		mode=GL_LINE;
		glutPostRedisplay();
		break;
		
		case 'l':

		/* The key is 'l', thus we render only the edges of the triangles in the triangle fan (wireframe version), approximating the custom shape of interest. */
		mode=GL_LINE;
		glutPostRedisplay();
		break;
		
		case 'P':
		
		/* The key is 'P', thus we render only the points of the triangles in the triangle fan, approximating the custom shape of interest. */
		mode=GL_POINT;
		glutPostRedisplay();
		break;
		
		case 'p':
		
		/* The key is 'p', thus we render only the points of the triangles in the triangle fan, approximating the custom shape of interest. */
		mode=GL_POINT;
		glutPostRedisplay();
		break;
		
		default:

    	/* Other keys are not important for us! */
    	break;
	}
}
