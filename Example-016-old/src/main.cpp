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
 * main.cpp - the main function for the 'Example-016 (Old Mode)' Test.
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

/// The custom settings for choosing which side of all triangles in the triangle fans of interest must be rendered.
/**
 * The value of this flag may be one of the following values:
 * 
 * -) the 'GL_FRONT' value, used for rendering only the 'front' sides of all triangles in the triangle fans of interest (press the 'f' or the 'F' key);
 * -) the 'GL_BACK' value, used for rendering only the 'back' sides of all triangles in the triangle fans of interest (press the 'b' or the 'B' key);
 * -) the 'GL_FRONT_AND_BACK' value, used for rendering both the 'front' and the 'back' sides of all triangles in the triangle fans of interest (press the 't' or the 'T' key).
 *
 * The rendering type to be exploited is chosen separately by the user.
 */
GLenum face;

/// The custom settings for rendering the sides of interest for all triangles in the triangle fans of interest.
/**
 * The value of this flag may be one of the following values:
 *
 * -) the 'GL_POINT' value, used for rendering only the vertices for the sides of all triangles in the triangle fans of interest to be drawn (press the 'p' or the 'P' key);
 * -) the 'GL_LINE' value, used for rendering the 'wireframe versions' for the sides of all triangles in the triangle fans of interest to be drawn (press the 'l' or the 'L' key);
 * -) the 'GL_FILL' value, used for rendering the 'filled versions' for the sides of all triangles in the triangle fans of interest to be drawn (press the 'i' or the 'I' key).
 *
 * The choice for what sides of all triangles in the triangle fans of interest must be drawn is performed separately by the user.
 */
GLenum mode;

/* Prototypes for all functions of interest! */
void draw();
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);

/// The main function for the <i>'Example-016 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-016' Test, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws all triangles in 2 triangle fans, approximating the 'Square Annulus' shape'. The reference vertices of the triangle fans are depicted, respectively, in 'red' and in 'blue', while their triangles are depicted in 'turquoise gray'."<<endl;
	cout<<"\tThe settings for rendering all triangles in the triangle fans of interest can be modified interactively by the user as follows:"<<endl<<endl;
	cout<<"\t-) only the 'front' sides of all triangles in the triangle fans of interest are rendered by pressing the 'f' or the 'F' key. The corresponding rendering type is chosen by the user separately."<<endl;
	cout<<"\t-) Only the 'back' sides of all triangles in the triangle fans of interest are rendered by pressing the 'b' or the 'B' key. The corresponding rendering type is chosen by the user separately."<<endl;
	cout<<"\t-) Both the 'front' and the 'back' sides of all triangles in the triangle fans of interest are rendered by pressing the 't' or the 'T' key. The corresponding rendering type is chosen by the user separately."<<endl;
	cout<<"\t-) Only the vertices for the sides of all triangles in the triangle fans to be drawn are rendered by pressing the 'p' or the 'P' key. The user can choose separately what sides of all triangles must be drawn."<<endl;
	cout<<"\t-) The 'wireframe versions' for the sides of all triangles in the triangle fans to be drawn are rendered by pressing the 'l' or the 'L' key. The user can choose separately what sides of all triangles must be drawn."<<endl;
	cout<<"\t-) The 'filled versions' for the sides of all triangles in the triangle fans to be drawn are rendered by pressing the 'i' or the 'I' key. The user can choose separately what sides of all triangles must be drawn."<<endl<<endl;
	cout<<"\tIt is possible to end this program by pressing one among the 'Q' - 'q' - 'Esc' keys."<<endl<<endl;
	cout.flush();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(480,480);
	glutCreateWindow("The 'Example-016' Test, based on the (Old Mode) OpenGL");
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
   	glOrtho(0,140,0,120,-1,1);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	face=GL_FRONT_AND_BACK;
	mode=GL_FILL;
	cout<<"\tAt the beginning, the 'filled versions' for both the 'front' and the 'back' sides of all triangles in the triangle fans of interest are rendered in the current scene."<<endl<<endl;
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

		/* The key is 'F', thus we draw only the 'front' sides of all triangles in the triangle fans, approximating the 'Square Annulus' shape of interest, by using the rendering type, chosen by the user. */
		face=GL_FRONT;
		glutPostRedisplay();
		break;
		
		case 'f':

		/* The key is 'f', thus we draw only the 'front' sides of all triangles in the triangle fans, approximating the 'Square Annulus' shape of interest, by using the rendering type, chosen by the user. */
		face=GL_FRONT;
		glutPostRedisplay();
		break;
		
		case 'B':

		/* The key is 'B', thus we draw only the 'back' sides of all triangles in the triangle fans, approximating the 'Square Annulus' shape of interest, by using the rendering type, chosen by the user. */
		face=GL_BACK;
		glutPostRedisplay();
		break;
		
		case 'b':

		/* The key is 'b', thus we draw only the 'back' sides of all triangles in the triangle fans, approximating the 'Square Annulus' shape of interest, by using the rendering type, chosen by the user. */
		face=GL_BACK;
		glutPostRedisplay();
		break;
		
		case 'T':

		/* The key is 'T', thus we draw both the 'front' and the 'back' sides of all triangles in the triangle fans, approximating the 'Square Annulus' shape of interest, by using the rendering type, chosen by the user. */
		face=GL_FRONT_AND_BACK;
		glutPostRedisplay();
		break;
		
		case 't':

		/* The key is 't', thus we draw both the 'front' and the 'back' sides of all triangles in the triangle fans, approximating the 'Square Annulus' shape of interest, by using the rendering type, chosen by the user. */
		face=GL_FRONT_AND_BACK;
		glutPostRedisplay();
		break;
		
		case 'I':

		/* The key is 'I', thus we render the 'filled versions' for the sides to be drawn of all triangles in the triangle fans, approximating the 'Square Annulus' shape of interest. The user can choose separately what sides of all triangles must be drawn. */
		mode=GL_FILL;
		glutPostRedisplay();
		break;
		
		case 'i':

		/* The key is 'i', thus we render the 'filled versions' for the sides to be drawn of all triangles in the triangle fans, approximating the 'Square Annulus' shape of interest. The user can choose separately what sides of all triangles must be drawn. */
		mode=GL_FILL;
		glutPostRedisplay();
		break;
		
		case 'L':

		/* The key is 'L', thus we render the 'wireframe versions' for the sides to be drawn of all triangles in the triangle fans, approximating the 'Square Annulus' shape of interest. The user can choose separately what sides of all triangles must be drawn. */
		mode=GL_LINE;
		glutPostRedisplay();
		break;
		
		case 'l':

		/* The key is 'l', thus we render the 'wireframe versions' for the sides to be drawn of all triangles in the triangle fans, approximating the 'Square Annulus' shape of interest. The user can choose separately what sides of all triangles must be drawn. */
		mode=GL_LINE;
		glutPostRedisplay();
		break;
		
		case 'P':
		
		/* The key is 'P', thus we render only the vertices for the sides to be drawn of all triangles in the triangle fans, approximating the 'Square Annulus' shape of interest. The user can choose separately what sides of all triangles must be drawn. */
		mode=GL_POINT;
		glutPostRedisplay();
		break;
		
		case 'p':
		
		/* The key is 'p', thus we render only the vertices for the sides to be drawn of all triangles in the triangle fans, approximating the 'Square Annulus' shape of interest. The user can choose separately what sides of all triangles must be drawn. */
		mode=GL_POINT;
		glutPostRedisplay();
		break;
		
		default:

    	/* Other keys are not important for us! */
    	break;
	}
}

/// This function draws 2 triangle fans (in <i>'turquoise gray'</i>), approximating the <i>'Square Annulus'</i> shape, in the OpenGL window of interest by using the rendering preferences, chosen by the user.
void draw()
{
	/* We draw 2 triangle fans (in 'turquoise gray'), approximating the 'Square Annulus' shape, in the OpenGL window of interest by using the rendering preferences, chosen by the user. */
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(10.0);
	glLineWidth(2.0);
	glPolygonMode(face,mode);
	glPolygonMode(face,mode);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0,0.0,0.0);
	glVertex3f(40.0, 40.0, 0.0);
	glColor3f(0.6,0.7,0.7);
	glVertex3f(40.0, 80.0, 0.0);
	glVertex3f(20.0, 100.0, 0.0);
	glVertex3f(20.0, 20.0, 0.0);
	glVertex3f(120.0, 20.0, 0.0);
	glVertex3f(100.0, 40.0, 0.0);
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.0,0.0,1.0);
	glVertex3f(100.0, 80.0, 0.0);
	glColor3f(0.6,0.7,0.7);
	glVertex3f(40.0, 80.0, 0.0);
	glVertex3f(20.0, 100.0, 0.0);
	glVertex3f(120.0, 100.0, 0.0);
	glVertex3f(120.0, 20.0, 0.0);
	glVertex3f(100.0, 40.0, 0.0);
	glEnd();
	glFlush();
	glFlush();
	if(face==GL_FRONT)
	{
		/* We must draw only the 'front' sides of all triangles in the triangle fans of interest by using the rendering type, chosen by the user. */
		if(mode==GL_POINT) cout<<"\tOnly the vertices in the 'front' sides of all triangles in the triangle fans of interest are rendered in the current scene."<<endl;
		if(mode==GL_LINE) cout<<"\tThe 'wireframe versions' for the 'front' sides of all triangles in the triangle fans of interest are rendered in the current scene."<<endl;
		if(mode==GL_FILL) cout<<"\tThe 'filled versions' for the 'front' sides of all triangles in the triangle fans of interest are rendered in the current scene."<<endl;
	}
	else if(face==GL_BACK)
	{
		/* We must draw only the 'back' sides of all triangles in the triangle fans of interest by using the rendering type, chosen by the user. */
		if(mode==GL_POINT) cout<<"\tOnly the vertices in the 'back' sides of all triangles in the triangle fans of interest are rendered in the current scene."<<endl;
		if(mode==GL_LINE) cout<<"\tThe 'wireframe versions' for the 'back' sides of all triangles in the triangle fans of interest are rendered in the current scene."<<endl;
		if(mode==GL_FILL) cout<<"\tThe 'filled versions' for the 'back' sides of all triangles in the triangle fans of interest are rendered in the current scene."<<endl;
	}
	else
	{
		/* We must draw both the 'front' and the 'back' sides of all triangles in the triangle fans of interest by using the rendering type, chosen by the user. */
		if(mode==GL_POINT) cout<<"\tOnly the vertices in both the 'front' and the 'back' sides of all triangles in the triangle fans of interest are rendered in the current scene."<<endl;
		if(mode==GL_LINE) cout<<"\tThe 'wireframe versions' of both the 'front' and the 'back' sides for all triangles in the triangle fans of interest are rendered in the current scene."<<endl;
		if(mode==GL_FILL) cout<<"\tThe 'filled versions' of both the 'front' and the 'back' sides for all triangles in the triangle fans of interest are rendered in the current scene."<<endl;
	}
}
