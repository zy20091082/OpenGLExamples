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
 * main.cpp - the main function for the 'Example-036 (Old Mode)' Test.
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

/// This flag indicates what projection we must exploit while drawing the scene.
/**
 * This flag assumes the following values:
 *
 * 0: it indicates to use the viewing perspective box (frustum) '[-5,5]' x '[-5,5]' x '[0,100]'
 * 1: it indicates to use the viewing perspective box (frustum) '[-5,5]' x '[-5,5]' x '[5,120]'
 * 2: it indicates to use the viewing perspective box (frustum) '[-5,5]' x '[-5,5]' x '[10,100]'
 * 3: it indicates to use the viewing perspective box (frustum) '[-5,5]' x '[-5,5]' x '[2.5,100]'
 * 4: it indicates to use the viewing perspective box (frustum) '[-10,10]' x '[-10,10]' x '[5,100]'
 * 5: it indicates to use the viewing perspective box (frustum) '[-1,1]' x '[-3,3]' x '[5,100]'
 *
 * The user can choose what project must be used by pressing cyclically the ' ' (space) key.
 */
int projection=0;

/* Prototypes for all functions of interest! */
void draw();
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);

/// The main function for the <i>'Example-036 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-036' Test, based on the (Old Mode) OpenGL."<<endl;
	
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-036' Test, based on the (Old Mode) OpenGL");
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
	projection=0;
	cout<<"\tAt the beginning, the 'Helix' curve of interest is drawn by using the ";
	if(projection==0) cout<<"viewing perspective box (frustum) '[-5,5]' x '[-5,5]' x '[0,100]' (thus, the 'viewing configuration #0').";
	else if(projection==1) cout<<"viewing perspective box (frustum) '[-5,5]' x '[-5,5]' x '[5,120]' (thus, the 'viewing configuration #1').";
	else if(projection==2) cout<<"viewing perspective box (frustum) '[-5,5]' x '[-5,5]' x '[10,100]' (thus, the 'viewing configuration #2').";
	else if(projection==3) cout<<"viewing perspective box (frustum) '[-5,5]' x '[-5,5]' x '[2.5,100]' (thus, the 'viewing configuration #3').";
	else if(projection==4) cout<<"viewing perspective box (frustum) '[-10,10]' x '[-10,10]' x '[5,100]' (thus, the 'viewing configuration #4').";
	else if(projection==5) cout<<"viewing perspective box (frustum) '[-1,1]' x '[-3,3]' x '[5,100]' (thus, the 'viewing configuration #5').";
	cout<<endl;
	cout.flush();
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '+' - '-' - ' ' keys. */
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
		
		case ' ':
		
		/* The key is ' ', thus we change the projection of interest! */
		projection=(projection+1)%6;
		resize(500,500);
		glutInitWindowSize(500,500);
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
   	if(projection==0) glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
   	else if(projection==1) glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 120.0);
   	else if(projection==2) glFrustum(-5.0, 5.0, -5.0, 5.0, 10.0, 100.0);
   	else if(projection==3) glFrustum(-5.0, 5.0, -5.0, 5.0, 2.5, 100.0);
   	else if(projection==4) glFrustum(-10.0, 10.0, -10.0, 10.0, 5.0, 100.0);
   	else if(projection==5) glFrustum(-1,1,-3,3,5,100);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function draws the polyline (in <i>'red'</i>), approximating the <i>'Helix'</i> curve of interest, in the main OpenGL window.
void draw()
{
	/* We draw the polyline (in 'red'), approximating the 'Helix' curve of interest, in the main OpenGL window. */
	glClear(GL_COLOR_BUFFER_BIT);
   	glColor3f(1.0, 0.0, 0.0);
   	glLineWidth(2);
   	glBegin(GL_LINE_STRIP);
   	for(double t = -10 * PI; t <= 10 * PI; t += PI/20.0) { glVertex3f(20.0 * cos(t), 20.0 * sin(t), t - 60.0); }
   	glEnd();
   	glFlush();
	cout<<"\tThe 'Helix' curve of interest is currently drawn by using the ";
	if(projection==0) cout<<"viewing perspective box (frustum) '[-5,5]' x '[-5,5]' x '[0,100]' (thus, the 'viewing configuration #0').";
	else if(projection==1) cout<<"viewing perspective box (frustum) '[-5,5]' x '[-5,5]' x '[5,120]' (thus, the 'viewing configuration #1').";
	else if(projection==2) cout<<"viewing perspective box (frustum) '[-5,5]' x '[-5,5]' x '[10,100]' (thus, the 'viewing configuration #2').";
	else if(projection==3) cout<<"viewing perspective box (frustum) '[-5,5]' x '[-5,5]' x '[2.5,100]' (thus, the 'viewing configuration #3').";
	else if(projection==4) cout<<"viewing perspective box (frustum) '[-10,10]' x '[-10,10]' x '[5,100]' (thus, the 'viewing configuration #4').";
	else if(projection==5) cout<<"viewing perspective box (frustum) '[-1,1]' x '[-3,3]' x '[5,100]' (thus, the 'viewing configuration #5').";
	cout<<endl;
	cout.flush();
}
