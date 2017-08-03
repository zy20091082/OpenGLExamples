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
 * main.cpp - the main function for the 'Example-037 (Old Mode)' Test.
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

/// This flag indicates the rendering settings for drawing the polygons in the tesselation of interest for the <i>'A'</i> shape.
/**
 * It assumes the following values:
 *
 * -) 0:	used for rendering only the points of all triangles and quadrilaterals in the tessellation of interest.
 * -) 1:	used for rendering the 'wireframe versions' of all triangles and quadrilaterals in the tessellation of interest.
 * -) 2:	used for rendering the 'filled versions' of all triangles and quadrilaterals in the tessellation of interest.
 *
 * The tessellation of interest is chosen independently.
 */
int mode=2;

/// This flag indicates what tessellation of the <i>'A'</i> shape must be exploited.
/**
 * It assumes the following values:
 *
 * -) 0: 	used for indicating the use of the 'Tessellation #0', consisting of a pure triangulation with 11 triangles. A different color is assigned to each triangle.
 * -) 1: 	used for indicating the use of the 'Tessellation #1', consisting of a quad-dominant mesh with 5 quadrilaterals and 1 triangle. A different color is assigned
 * 			to the triangle and to each quadrilateral.
 * -) 2: 	used for indicating the use of the 'Tessellation #2', consisting of the same triangulation in the 'Tessellation #0'. In this case, it is expressed by 1
 * 			triangle strip (in 'yellow'), and by 3 triangle fans. The reference vertices for the triangle fans are depicted, respectively, in 'red', in 'blue', and in
 * 			'green'. Instead, their triangles are depicted in 'grey'.
 *
 * The rendering settings for drawing the polygons of interest are set independently.
 */
int tessellation=0;

/* Prototypes for all functions of interest! */
void draw();
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);

/// The main function for the <i>'Example-037 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-037' Test, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws several versions of the 'A' shape in an OpenGL window by using the rendering settings, chosen interactively by the user. Broadly speaking, the ";
	cout<<"'A' shape represents the 'A' letter, which is in the first letter and the"<<endl;
	cout<<"\tfirst vowel in the ISO basic Latin alphabet. Here, we consider the upper-case version of the 'A' letter, consisting of 2 slanting sides of a triangle, ";
	cout<<"crossed in the middle by a horizontal bar (as usual)."<<endl<<endl;
	cout<<"\tIn this test, we consider the following tessellations of the 'A' shape, defined without adding any 'Steiner' point:"<<endl<<endl;
	cout<<"\t\t0. the 'Tessellation #0' of the 'A' shape consists of a pure triangulation, formed by 11 triangles. A different color is assigned to each triangle.";
	cout<<endl;
	cout<<"\t\t1. The 'Tessellation #1' of the 'A' shape consists of a quad-dominant mesh, formed by 5 quadrilaterals, and by only 1 triangle. Also in this case, a ";
	cout<<"different color is assigned to the triangle and to each quadrilateral."<<endl;
	cout<<"\t\t2. The 'Tessellation #2' of the 'A' shape consists of the same triangulation in the 'Tessellation #0'. In this case, it is expressed by 1 triangle strip";
	cout<<" (in 'yellow'), and by 3 triangle fans. The reference vertices for"<<endl; 
	cout<<"\t\t   the triangle fans are depicted, respectively, in 'red', in 'blue', and in 'green'. Instead, their triangles are depicted in 'grey'."<<endl<<endl;
	cout<<"\tHere, the user cannot modify the vertices positions in the 'A' shape, since they are fixed in advance. Instead, the user can choose interactively to ";
	cout<<"exploit any among the tessellations of the 'A' shape (mentioned above) by"<<endl;
	cout<<"\tpressing cyclically the 't' key. Moreover, the user can decide interactively to render:"<<endl<<endl;
	cout<<"\t\t-) only the points in the tessellation of interest for the 'A' shape;"<<endl;
	cout<<"\t\t-) the 'wireframe versions' of all triangles and quadrilaterals in the tessellation of interest for the 'A' shape;"<<endl;
	cout<<"\t\t-) the 'filled versions' of all triangles and quadrilaterals in the tessellation of interest for the 'A' shape;"<<endl<<endl;
	cout<<"\tby pressing cyclically the ' ' (space) key. As mentioned above, the tessellation of interest for the 'A' shape to be drawn can be chosen  independently.";
	cout<<endl<<endl<<"\tLikewise, the window of interest can be closed by pressing any among the 'Q', the 'q', and the 'Esc' keys."<<endl<<endl;
	cout.flush();
	
	/* If we arrive here, then we can draw the 'A' shape of interest. */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-037' Test, based on the (Old Mode) OpenGL");
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
	tessellation=0;
	mode=2;
	cout<<"\tAt the beginning, ";
	if(mode==0) cout<<"only the points of all polygons ";
	else if(mode==1) cout<<"the 'wireframe versions' of all polygons ";
	else if(mode==2) cout<<"the 'filled versions' of all polygons ";
	cout<<"in the 'Tesselation #"<<tessellation<<"' of the 'A' shape are drawn."<<endl<<endl;
	cout.flush();
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - ' ' (space) - 't' keys. */
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
		
		/* The key is ' ' (space), thus we change the rendering mode of interest! */
		mode=(mode+1)%3;
		glutPostRedisplay();
		break;
		
		case 't':
		
		/* The key is 't', thus we change the tessellation of interest! */
		tessellation=(tessellation+1)%3;
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
	/* We update the projection and the modeling matrices! */
	glViewport(0, 0, w, h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	gluOrtho2D(-35,35,-5,65);
}

/// This function draws the tessellation of interest for the <i>'A'</i> shape in the main OpenGL window by using the rendering settings, choosen by the user.
void draw()
{
	/* We draw the tessellation of interest for the 'A' shape in the main OpenGL window by using the rendering settings, choosen by the user. */
	glClear(GL_COLOR_BUFFER_BIT);
	if(mode==0) { glPolygonMode(GL_FRONT_AND_BACK,GL_POINT); }
	else if(mode==1) { glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); }
	else if(mode==2) { glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); }
   	glLineWidth(3);
   	glPointSize(8);
	if(tessellation==0)
   	{
   		/* We draw the 'Tessellation #0', formed only by 11 triangles. */
   		glBegin(GL_TRIANGLES);
   	
	   	/* Drawing the triangle #0 (A-B-E) [blue] */
	   	glColor3f(0.0, 0.0, 1.0);
	   	glVertex2f(-15,0);
	   	glVertex2f(-25,0);
	   	glVertex2f(-10.5,15);
	   	
	   	/* Drawing the triangle #1 (B-E-H) [light gray] */
	   	glColor3f(0.8,0.8,0.8);
	   	glVertex2f(-25,0);
	   	glVertex2f(-10.5,15);
	   	glVertex2f(-7.5,25);
	   	
	   	/* Drawing the triangle #2 (I-H-B) [cyan] */
	   	glColor3f(0.0, 1.0, 1.0);
	   	glVertex2f(-7,60);
	   	glVertex2f(-7.5,25);
	   	glVertex2f(-25,0);
	   	
	   	/* Drawing the triangle #3 (H-E-F) [yellow] */
	   	glColor3f(1.0, 1.0, 0.0);
	   	glVertex2f(-7.5,25);
	   	glVertex2f(-10.5,15);
	   	glVertex2f(10.5,15);
	   	
	   	/* Drawing the triangle #4 (H-G-F) [magenta] */
	   	glColor3f(1.0, 0.0, 1.0);
	   	glVertex2f(-7.5,25);
	   	glVertex2f(7.5,25);
	   	glVertex2f(10.5,15);
	   	
	   	/* Drawing the triangle #5 (F-G-D) [gray] */
	   	glColor3f(0.5, 0.5, 0.5);
	   	glVertex2f(10.5,15);
	   	glVertex2f(7.5,25);
	   	glVertex2f(25,0);
	   	
	   	/* Drawing the triangle #6 (F-C-D) [red] */
	   	glColor3f(1.0, 0.0, 0.0);
	   	glVertex2f(10.5,15);
	   	glVertex2f(15,0);
	   	glVertex2f(25,0);
	   	
	   	/* Drawing the triangle #7 (L-G-D) [green] */
	   	glColor3f(0.0, 1.0, 0.0);
	   	glVertex2f(7,60);
	   	glVertex2f(7.5,25);
	   	glVertex2f(25,0);
	   	
	   	/* Drawing the triangle #8 (I-L-M) [brown] */
	   	glColor3f(0.60, 0.40, 0.12);
	   	glVertex2f(-7,60);
	   	glVertex2f(7,60);
	   	glVertex2f(0,50);
	   	
	   	/* Drawing the triangle #9 (I-M-H) [purple]. */
	   	glColor3f(0.98, 0.625, 0.12);
	   	glVertex2f(-7,60);
	   	glVertex2f(0,50);
	   	glVertex2f(-7.5,25);
	   	
	   	/* Drawing the triangle #10 (M-G-L). */
	   	glColor3f(0.5, 0.5, 0);
	   	glVertex2f(0,50);
	   	glVertex2f(7.5,25);
	   	glVertex2f(7,60);
	   	glEnd();
   	}
   	else if(tessellation==1)
   	{
   		/* We draw the 'Tessellation #1', formed only by 5 independent quadrilaterals and 1 triangle (a quad-dominant mesh). */
   		glLineWidth(3);
   		glPointSize(8);
   		glBegin(GL_QUADS);
   		
   		/* Drawing the quad #0 (E-F-G-H) [blue]. */
   		glColor3f(0.0, 0.0, 1.0);
   		glVertex2d(-10.5,15);
   		glVertex2d(10.5,15);
   		glVertex2d(7.5,25);
   		glVertex2d(-7.5,25);
   		
   		/* Drawing the quad #1 (F-G-D-C) [red]. */
   		glColor3f(1.0, 0.0, 0.0);
   		glVertex2d(10.5,15);
   		glVertex2d(7.5,25);
   		glVertex2d(25,0);
   		glVertex2d(15,0);
   		
   		/* Drawing the quad #2 (L-M-G-D) [green]. */
   		glColor3f(0.0, 1.0, 0.0);
   		glVertex2d(7,60);
   		glVertex2d(0,50);
   		glVertex2d(7.5,25);
   		glVertex2d(25,0);
   		
   		/* Drawing the quad #3 (H-E-A-B) [cyan]. */
   		glColor3f(0.0, 1.0, 1.0);
   		glVertex2d(-7.5,25);
   		glVertex2d(-10.5,15);
   		glVertex2d(-15,0);
   		glVertex2d(-25,0);
   		
   		/* Drawing the quad #4 (I-M-H-B) [yellow]. */
   		glColor3f(1.0, 1.0, 0.0);
   		glVertex2d(-7,60);
   		glVertex2d(0,50);
   		glVertex2d(-7.5,25);
   		glVertex2d(-25,0);
   		glEnd();
   		
   		/* Drawing the triangle #0 (I-L-M) [magenta]. */
   		glColor3f(1,0,1);
   		glBegin(GL_TRIANGLES);
   		glVertex2f(-7,60);
   		glVertex2f(7,60);
   		glVertex2f(0,50);
   		glEnd();
   	}
   	else
   	{
   		/* We draw the 'Tessellation #2', which is the same as the 'Tessellation #0' (with 11 independent triangles), but represented by 3 triangle fans and 1 triangle
		 * strip. */
   		glLineWidth(3);
   		glPointSize(8);
   		
   		/* Drawing the first triangle fan (in red) for the point B, containing the points A-E-H-I. */
   		glBegin(GL_TRIANGLE_FAN);
   		glColor3f(1.0,0.0,0.0);
   		glVertex2f(-25,0);
   		glColor3f(0.8,0.8,0.8);
   		glVertex2f(-15,0);
   		glVertex2f(-10.5,15);
   		glVertex2f(-7.5,25);
   		glVertex2f(-7,60);
   		glEnd();
   		
   		/* Drawing the second triangle fan (in blue) for the point D, containing the points C-F-G-L. */
   		glBegin(GL_TRIANGLE_FAN);
   		glColor3f(0.0,0.0,1.0);
   		glVertex2f(25,0);
   		glColor3f(0.8,0.8,0.8);
   		glVertex2f(15,0);
   		glVertex2f(10.5,15);
   		glVertex2f(7.5,25);
   		glVertex2f(7,60);
   		glEnd();
   		
   		/* Drawing the third triangle fan (in green) for the point M, containing the points H-I-L-G. */
   		glBegin(GL_TRIANGLE_FAN);
   		glColor3f(0.0,1.0,0.0);
   		glVertex2f(0,50);
   		glColor3f(0.8,0.8,0.8);
   		glVertex2f(-7.5,25);
   		glVertex2f(-7,60);
   		glVertex2f(7,60);
   		glVertex2f(7.5,25);
   		glEnd();
   		
   		/* Drawing the triangle strip (in yellow), including the points H-E-F-G */
   		glBegin(GL_TRIANGLE_STRIP);
   		glColor3f(0.8,0.8,0.8);
   		glVertex2f(-10.5,15);
   		glColor3f(1,1,0);
   		glVertex2f(-7.5,25);
   		glVertex2f(10.5,15);
   		glColor3f(0.8,0.8,0.8);
   		glVertex2f(7.5,25);
   		glEnd();
   	}
   	
   	/* If we arrive here, then we have finished! */
   	glFlush();
   	if(mode==0) cout<<"\tOnly the points of all polygons ";
	else if(mode==1) cout<<"\tThe 'wireframe versions' of all polygons ";
	else if(mode==2) cout<<"\tThe 'filled versions' of all polygons ";
	cout<<"in the 'Tesselation #"<<tessellation<<"' of the 'A' shape are currently drawn."<<endl;
	cout.flush();
}

