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
 * main.cpp - the main function for the 'Example-024 (Old Mode)' example.
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

	/* We are not using a MacOSX platform. Thus, we have a generic Unix-like platform, like the GNU Linux, or a Microsoft Windows platform. */
	#include "GL/glew.h"
	#include "GL/glut.h"
	#include "GL/gl.h"

#endif

/// The center coordinates <i>'(xc,yc)'</i> for the <i>'Circular Annulus'</i> shape of interest.
float xc,yc;

/// The radius <i>'rE'</i> of the external circle for the <i>'Circular Annulus'</i> shape of interest.
/**
 * The radius 'rE' is also called the <i>'external radius'</i> for the 'Circular Annulus' shape of interest.
 */
float radiusE;

/// The radius <i>'rI'</i> of the internal circle for the <i>'Circular Annulus'</i> shape of interest.
/**
 * The radius 'rI' is also called the <i>'internal radius'</i> for the 'Circular Annulus' shape of interest.
 */
float radiusI;

/// The number of the quadrilaterals in the quadstrip, used for approximating the <i>'Circular Annulus'</i> shape of interest.
unsigned int num_quads=3;

/// The setting for rendering the quadstrip, used for approximating the <i>'Circular Annulus'</i> shape of interest.
/**
 * It may be one of the following values:
 *
 * -) the 'p' char value, used for choosing to render only the points of the quadrilaterals in the quadstrip of interest (press the 'p' key);
 * -) the 'l' char value, used for choosing to render only the edges of the quadrilaterals ('wireframe version') in the quadstrip of interest (press the 'l' key);
 * -) the 'f' char value, used for choosing to render completely the quadrilaterals ('filled version') in the quadstrip of interest (press the 'f' key).
 */
char choice;

/* Prototypes for all functions of interest! */
void draw();
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);

/// The main function for the <i>'Example-024 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-024' Example, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws several versions (in 'red') of a quadstrip (formed by an arbitrary number of quadrilaterals), approximating the 'Circular Annulus' shape with internal radius 'rI', external radius 'rE', and center '(xc,yc)'."<<endl;
	cout<<"\tThe external radius 'rE' and the internal radius 'rI', as well as the center coodinates '(xc,yc)' of the 'Circular Annulus' shape, are specified by the user, which can also:"<<endl<<endl;
	cout<<"\t\t-) decide to render only the points for the quadrilaterals in the quadstrip of interest by pressing the 'p' key;"<<endl;
	cout<<"\t\t-) decide to render only the edges for the quadrilaterals ('wireframe version') in the quadstrip of interest by pressing the 'l' key;"<<endl;
	cout<<"\t\t-) decide to render completely the quadrilaterals ('filled version') in the quadstrip of interest by pressing the 'f' key;"<<endl;
	cout<<"\t\t-) increase the number of the quadrilaterals in the quadstrip of interest by pressing the '+' key;"<<endl;
	cout<<"\t\t-) decrease the number of the quadrilaterals in the quadstrip of interest by pressing the '-' key."<<endl<<endl;
	cout<<"\tIt is possible to end this program by pressing one among the 'Q' - 'q' - 'Esc' keys."<<endl<<endl;
	cout.flush();
	cout<<"\tPlease, insert the internal radius 'rI' (positive and not null) for the 'Circular Annulus' shape of interest: ";
	cin>>radiusI;
	if( (!cin) || (radiusI<=0) )
	{
		cout<<endl<<"\tPLEASE, INSERT A VALID VALUE (POSITIVE AND NOT NULL) FOR THE INTERNAL RADIUS 'rI' OF INTEREST."<<endl<<endl<<"\tTHIS PROGRAM IS CLOSING ..."<<endl<<endl;
		cout.flush();
		return EXIT_FAILURE;
	}
	
	/* Now, we read the external radius 'rE' for the 'Circular Annulus' shape of interest. */
	cout<<"\tPlease, insert the external radius 'rE' (positive, not null, and larger than the internal radius 'rI'="<<radiusI<<") for the 'Circular Annulus' shape of interest: ";
	cin>>radiusE;
	if( (!cin) || (radiusE<=0) || (radiusE<=radiusI) )
	{
		cout<<endl<<"\tPLEASE, INSERT A VALID VALUE (POSITIVE, NOT NULL, AND LARGER THAN THE INTERNAL RADIUS 'rI'="<<radiusI<<") FOR THE EXTERNAL RADIUS 'rE' OF INTEREST."<<endl<<endl<<"\tTHIS PROGRAM IS CLOSING ..."<<endl<<endl;
		cout.flush();
		return EXIT_FAILURE;
	}
	
	/* Finally, we read the center coordinates '(xc,yc)' for the 'Circular Annulus' shape of interest. */
	cout<<"\tPlease, insert the center coordinates '(xc,yc)' for the 'Circular Annulus' shape of interest (separated by a space): ";
	cout.flush();
	cin>>xc>>yc;
	if(!cin)
	{
		cout<<endl<<"\tPLEASE, INSERT THE CENTER COORDINATES '(xc,yc)' FOR THE 'CIRCULAR ANNULUS' SHAPE OF INTEREST (SEPARATED BY A SPACE)."<<endl<<endl<<"\tTHIS PROGRAM IS CLOSING ..."<<endl<<endl;
		cout.flush();
		return EXIT_FAILURE;
	}
	
	/* If we arrive here, we can draw the quadstrip, approximating the 'Circular Annulus' shape, by exploiting the rendering settings, chosen by the user. */
	cout<<endl;
	cout.flush();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-024' Example, based on the (Old Mode) OpenGL");
	glutDisplayFunc(draw);
	glutReshapeFunc(resize);
	glutKeyboardFunc(manageKeys);
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
	num_quads=3;
	choice='l';
	cout<<"\tInitially, only the edges of the "<<num_quads<<" quadrilaterals (the minimum number as possible) in the quadstrip, approximating the 'Circular Annulus' shape of center ("<<xc<<","<<yc<<"), internal radius "<<radiusI<<", and external radius ";
	cout<<radiusE<<", are rendered."<<endl<<endl;
	cout.flush();
}

/// This function draws the specific quadstrip (in <i>'red'</i>), approximating the <i>'Cicular Annulus'</i> shape of interest, in the OpenGL window of interest by using the current rendering settings (chosen by the user).
void draw()
{
	float t;
	
	/* We draw the quadstrip (in 'red'), describing the circular annulus, in the OpenGL window of interest. */
	t=0;
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(5);
	glLineWidth(3);
	glColor3f(1.0,0.0,0.0);
	if(choice=='l') glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	if(choice=='f') glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	if(choice=='p') glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
	glBegin(GL_QUAD_STRIP);
	for(unsigned int i=0;i<=num_quads;i++)
	{
		glVertex3f(xc+radiusI*cos(t),yc+radiusI*sin(t),0);
		glVertex3f(xc+radiusE*cos(t),yc+radiusE*sin(t),0);
		t=t+(2*PI/num_quads);
	}
	
	/* If we arrive here, all is ok */
	glEnd();
	glFlush();
	glFlush();
	if(choice=='l') 
	{ 
		/* We draw the 'wireframe version' (in 'red') for all quadrilaterals in the quadstrip of interest! */
		cout<<"\tThe 'wireframe version' of the "<<num_quads<<" quadrilaterals in the quadstrip, approximating the 'Circular Annulus' shape of interest, is rendered."<<endl; 
		cout.flush();
	}
    else if(choice=='f') 
    {
    	/* We draw the 'filled version' (in 'red') for all quadrilaterals in the quadstrip of interest! */
    	cout<<"\tThe 'filled version' of the "<<num_quads<<" quadrilaterals in the quadstrip, approximating the 'Circular Annulus' shape of interest, is rendered."<<endl; 
		cout.flush();
    }
    else if(choice=='p') 
    { 
    	/* We draw only the points (in 'red') for all quadrilaterals in the quadstrip of interest! */
    	cout<<"\tOnly the points of the "<<num_quads<<" quadrilaterals in the quadstrip, approximating the 'Circular Annulus' shape of interest, are rendered."<<endl;
		cout.flush();
    }
}

/// This function updates the viewport for the scene when it is resized. */
void resize(int w, int h)
{
	/* We update the projections and the modeling matrices! */
	glViewport(0, 0, w, h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glOrtho(xc-1.1*radiusE,xc+1.1*radiusE,yc-1.1*radiusE,yc+1.1*radiusE,-1,1);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '+' - '-' - 'l' - 'f' - 'p' keys. */
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
		
		/* The key is '+', thus we increase the number of the quadrilaterals in the quadstrip, used for approximating the 'Circular Annulus' shape of interest. */
		num_quads=num_quads+1;
		glutPostRedisplay();
		break;
		
		case '-':
		
		/* The key is '-', thus we decrease the number of the quadrilaterals (if possible) in the quadstrip, used for approximating the 'Circular Annulus' shape of interest. */
		if(num_quads>3) num_quads=num_quads-1;
		else cout<<"\tThe minimum number 3 of quadrilaterals is reached, and it is not possible to decrease again this number."<<endl;
		cout.flush();
		glutPostRedisplay();
		break;
		
		case 'l':

		/* The key is 'l', thus we choose to render only the edges of the quadrilaterals ('wireframe version') in the quadstrip, used for approximating the 'Circular Annulus' shape of interest. */
		choice='l';
		glutPostRedisplay();
		break;
		
		case 'f':
		
		/* The key is 'f', thus we choose to render completely the quadrilaterals ('filled version') in the quadstrip, used for approximating the 'Circular Annulus' shape of interest. */
		choice='f';
		glutPostRedisplay();
		break;
		
		case 'p':
		
		/* The key is 'p', thus we choose to render only the vertices of the quadrilaterals in the quadstrip, used for approximating the 'Circular Annulus' shape of interest. */
		choice='p';
		glutPostRedisplay();
		break;

		default:

    	/* Other keys are not important for us */
    	break;
	}
}
