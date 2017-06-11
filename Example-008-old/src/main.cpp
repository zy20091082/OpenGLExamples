/*******************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 * 
 * Last update: June 2017
 *
 * This program is Free Software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.                                       
 *                                                                         
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License (http://www.gnu.org/licenses/gpl.txt) for more details.
 * 
 * main.cpp - the main function for the 'Example-008 (Old Mode)' Test.
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

/// This flag identifies what viewing configuration must be applied to the scene.
/**
 * It may assume these values:
 *
 * -) '0' for activating the 'Viewing Configuration #0'. Here, the 'large' quadrilateral is rendered before, but it is partially hidden by the 'small' quadrilateral.
 * -) '1' for activating the 'Viewing Configuration #1'. Here, the 'small' quadrilateral is rendered before, but it is completely hidden by the 'large' quadrilateral.
 */
int choice;

/// This boolean flag is useful for completing the textual interface.
bool eol=false;

/* Prototypes for all functions of interest! */
void draw();
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);

/// The main function for the <i>'Example-008 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-008' Test, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws the 'filled versions' for 2 quadrilaterals of different size and with a not empty intersection (partial overlap) in an OpenGL window."<<endl;
	cout<<"\tIn particular, the 'small' quadrilateral may be completely covered by the 'large' quadrilateral, depending on their rendering order. This latter corresponds to their color, which is defined as follows:"<<endl<<endl;
	cout<<"\t\t-) the quadrilateral in 'red' is rendered before in the scene;"<<endl;
	cout<<"\t\t-) the quadrilateral in 'blue' is rendered after in the scene."<<endl<<endl;
	cout<<"\tThe rendering order of these quadrilaterals corresponds to the following viewing configurations, that can be activated upon request by the user:"<<endl<<endl;
	cout<<"\t\t0. the 'large' quadrilateral (in 'red') is rendered before, and the 'small' quadrilateral (in 'blue') is rendered after in the 'Viewing Configuration #0'. In this case, both the quadrilaterals are visible."<<endl;
	cout<<"\t\t   The 'Viewing Configuration #0' is activated upon request by pressing the '0' key."<<endl<<endl;
	cout<<"\t\t1. The 'small' quadrilateral (in 'red') is rendered before, and the 'large' quadrilateral (in 'blue') is rendered after in the 'Viewing Configuration #1'. In this case, only the 'large' quadrilateral is visible."<<endl;
	cout<<"\t\t   The 'Viewing Configuration #1' is activated upon request by pressing the '1' key."<<endl<<endl;
	cout<<"\tLikewise, the window of interest can be closed by pressing any among the 'Q', the 'q', and the 'Esc' keys."<<endl<<endl;
	cout.flush();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(480,480);
	glutCreateWindow("The 'Example-008' Test, based on the (Old Mode) OpenGL");
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

/// This function draws the <i>'filled versions'</i> of 2 quadrilaterals in the OpenGL window of interest by using the viewing configuration, chosen by the user.
void draw()
{
	/* We draw the 'filled versions' of 2 quadrilaterals in the OpenGL window of interest by using the viewing configuration, chosen by the user. */
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	if(choice==0)
	{
		/* We must draw the 'filled version' of the 'large' quadrilateral, first. */
		glBegin(GL_POLYGON);
		glVertex3f(20,20,0);
		glVertex3f(80,20,0);
		glVertex3f(80,80,0);
		glVertex3f(20,80,0);
		glEnd();
	}
	else
	{
		/* We must draw the 'filled version' of the 'small' quadrilateral, first. */
		glBegin(GL_POLYGON);
		glVertex3f(40,40,0);
		glVertex3f(60,40,0);
		glVertex3f(60,60,0);
		glVertex3f(40,60,0);
		glEnd();
	}
	
	/* Now, we draw the 'filled version' of the second quadrilateral! */
	glColor3f(0.0,0.0,1.0);
	if(choice==0)
	{
		/* We must draw the 'filled version' of the 'small' quadrilateral. */
		glBegin(GL_POLYGON);
		glVertex3f(40,40,0);
		glVertex3f(60,40,0);
		glVertex3f(60,60,0);
		glVertex3f(40,60,0);
		glEnd();
	}
	else
	{
		/* We must draw the 'filled version' of the 'large' quadrilateral. */
		glBegin(GL_POLYGON);
		glVertex3f(20,20,0);
		glVertex3f(80,20,0);
		glVertex3f(80,80,0);
		glVertex3f(20,80,0);
		glEnd();
	}
	
	/* If we arrive here, all is finished! */
	glFlush();
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	choice=0;
	glClearColor(1.0, 1.0, 1.0, 0.0);
	eol=false;
	cout<<"\tAt the beginning, the 'Viewing Configuration #"<<choice<<"' is applied to the scene."<<endl<<endl;
	cout.flush();
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '0' - '1' keys. */
	switch (key)
	{
		case 'q':
	
		/* The key is 'q', thus we can exit from this program. */
		if(eol) cout<<endl;
		cout<<"\tThis program is closing correctly ... "<<endl<<endl;
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
		if(eol) cout<<endl;
		cout<<"\tThis program is closing correctly ... "<<endl<<endl;
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
		if(eol) cout<<endl;
		cout<<"\tThis program is closing correctly ... "<<endl<<endl;
		cout << "\tPress the RETURN key to finish ... ";
		cin.get();
		#ifndef _MSC_VER
			cout << endl;
			cout.flush();
		#endif
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case '0':
		
		/* The key is '0', thus we apply the 'Viewing Configuration #0' to the scene. */
		choice=0;
		cout<<"\tThe 'Viewing Configuration #"<<choice<<"' is currently applied to the scene."<<endl;
		cout.flush();
		eol=true;
		glutPostRedisplay();
		break;
		
		case '1':
		
		/* The key is '1', thus we apply the 'Viewing Configuration #1' to the scene. */
		choice=1;
		cout<<"\tThe 'Viewing Configuration #"<<choice<<"' is currently applied to the scene."<<endl;
		cout.flush();
		eol=true;
		glutPostRedisplay();
		break;
		
		default:

    	/* Other keys are not important for us! */
    	break;
	}
}
