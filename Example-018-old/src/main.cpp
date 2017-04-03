/*******************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 * 
 * Last update: April 2017
 *
 * This program is Free Software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.                                       
 *                                                                         
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License (http://www.gnu.org/licenses/gpl.txt) for more details.
 * 
 * main.cpp - the main function for the 'Example-018 (Old Mode)' example.
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

/// The counter index for cycling the vertices order for all possible versions of the convex polygons (in <i>'red'</i>).
int iconvex;

/// The counter index for cycling the vertices order for all possible versions of the concave polygons (in <i>'blue'</i>).
int inconvex;

/// This boolean flag is useful for completing the textual interface.
bool eol=false;

/// The 3D coordinates of the points in the convex polygons (in <i>'red'</i>).
float convex_points[][3]={
			{ 20.0,20.0,0.0},
			{ 50,20,0 },
			{ 80,50,0 },
			{ 80,80,0 },
			{ 20,80,0 }
	};

/// The 3D coordinates of the points in the concave polygons (in <i>'blue'</i>).
float not_convex_points[][3]={
			{20,120,0},
			{80,120,0},
			{40,140,0},
			{20,180,0}
};

/* Prototypes for all functions of interest! */
void draw();
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);

/// The main function for the <i>'Example-018 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-018' Example, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws the 'filled' and the 'wireframe versions' of several convex (in 'red') and concave (in 'blue') polygons, and allows the user to cycle the vertices order in the polygons of interest by pressing the '+' key."<<endl;
	cout<<"\tWhile performing these operations, there may be 'strange' situations, expecially when cycling the vertices in the 'filled versions' of the concave polygons (in 'blue')."<<endl<<endl;
	cout<<"\tIt is possible to end this program by pressing one among the 'Q' - 'q' - 'Esc' keys."<<endl<<endl;
	cout.flush();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(600,600);
	glutCreateWindow("The 'Example-018' Example, based on the (Old Mode) OpenGL");
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
   	glOrtho(0,200,0,200,-1,1);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function draws the <i>'filled'</i> and the <i>'wireframe versions'</i> of several convex (in <i>'red'</i>) and concave (in <i>'blue'</i>) polygons in the OpenGL window of interest.
void draw()
{
	int pp,jj;

	/* We draw the 'filled' and the 'wireframe versions' of several convex (in 'red') and concave (in 'blue') polygons in the OpenGL window of interest. First, we draw the 'filled version' of the convex polygon #0 (in 'red'). */
	pp = (iconvex%5);
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(10.0);
	glLineWidth(2.0);
	glColor3f(1.0,0.0,0.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_POLYGON);
   	for(int k=0;k<5;k++) 
   	{ 
   		jj=(k+pp)%5;
   		glVertex3f(convex_points[jj][0],convex_points[jj][1],convex_points[jj][2]);
   	}
   	
   	/* We draw the 'wireframe version' of the convex polygon #0 (in 'red'). */
   	glEnd();
   	glColor3f(1.0,0.0,0.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glBegin(GL_POLYGON);
	for(int k=0;k<5;k++) 
   	{ 
   		jj=(k+pp)%5;
   		glVertex3f(convex_points[jj][0]+100,convex_points[jj][1],convex_points[jj][2]);
   	}
   	
   	/* We draw the 'filled version' of the concave polygon #1 (in 'blue'). */
	glEnd();
	glColor3f(0.0,0.0,1.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_POLYGON);
	for(int k=0;k<4;k++) 
   	{ 
   		jj=(k+pp)%4;
   		glVertex3f(not_convex_points[jj][0],not_convex_points[jj][1],not_convex_points[jj][2]);
   	}
	
	/* We draw the 'wireframe version' of the concave polygon #1 (in 'blue'). */
	glEnd();
	glColor3f(0.0,0.0,1.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	pp=(inconvex%4);
	glBegin(GL_POLYGON);
	for(int k=0;k<4;k++) 
   	{ 
   		jj=(k+pp)%4;
   		glVertex3f(not_convex_points[jj][0]+100,not_convex_points[jj][1],not_convex_points[jj][2]);
   	}
	
	/* If we arrive here, all is ok! */
	glEnd();
	glFlush();
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	iconvex=0;
	inconvex=0;
	eol=false;
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '+' keys. */
	switch (key)
	{
		case 'q':
	
		/* The key is 'q', thus we can exit from this program. */
		if(eol) cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case 'Q':
	
		/* The key is 'Q', thus we can exit from this program. */
		if(eol) cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case 27:
	
		/* The key is 'Esc', thus we can exit from this program. */
		if(eol) cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case '+':
		
		/* The key is '+', thus we must cycle the order of the vertices for all polygons of interest. */
		iconvex=iconvex+1;
		inconvex=inconvex+1;
		eol=true;
		cout<<"\tThe vertices for both the 'filled' and the 'wireframe versions' of several convex and concave polygons are cycled in advance."<<endl;
		glutPostRedisplay();		
		break;

		default:

    	/* Other keys are not important for us! */
    	break;
	}
}
