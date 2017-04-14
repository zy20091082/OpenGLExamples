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

	/* We are not using a MacOSX platform. Thus, we have a generic Unix-like platform, like the GNU/Linux, or a Microsoft Windows platform. */
	#include "GL/glew.h"
	#include "GL/glut.h"
	#include "GL/gl.h"

#endif

/// The center coordinates <i>'(xc,yc)'</i> to be used for defining and drawing the quadstrip, approximating the <i>'Circular Annulus'</i> shape of interest.
/**
 * Clearly, the center for the 'Circular Annulus' shape of interest is formed by 2 floating-point values, provided interactively by the user.
 */
float xc,yc;

/// The radius <i>'rE'</i> of the external circle to be used for defining and drawing the quadstrip, approximating the <i>'Circular Annulus'</i> shape of interest.
/**
 * The radius 'rE' is also called the 'external radius' for the 'Circular Annulus' shape of interest. Clearly, it must be a positive and not null floating-point value, provided interactively by the user.
 */
float rE;

/// The radius <i>'rI'</i> of the internal circle to be used for defining and drawing the quadstrip, approximating the <i>'Circular Annulus'</i> shape of interest.
/**
 * The radius 'rI' is also called the 'internal radius' for the 'Circular Annulus' shape of interest. Clearly, it must be a positive and not null floating-point value, provided interactively by the user.
 */
float rI;

/// The number of all quadrilaterals in the quadstrip, approximating the <i>'Circular Annulus'</i> shape of interest.
/**
 * It is initially set to '3', which is the minimum number 'n' of all quadrilaterals. It is interactively modified by pressing the '+' and the '-' keys.
 */
unsigned int num_quads=3;

/// The setting for rendering all quadrilaterals in the quadstrip, used for approximating the <i>'Circular Annulus'</i> shape of interest.
/**
 * The value of this flag may be one of the following values:
 *
 * -) the 'p' char value, used for choosing to render only the vertices for all quadrilaterals in the quadstrip, used for approximating the 'Circular Annulus' shape of interest;
 * -) the 'l' char value, used for choosing to render the 'wireframe versions' for all quadrilaterals in the quadstrip, used for approximating the 'Circular Annulus' shape of interest;
 * -) the 'f' char value, used for choosing to render the 'filled versions' for all quadrilaterals in the quadstrip, used for approximating the 'Circular Annulus' shape of interest.
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
	cout<<"\tIt draws all quadrilaterals (in 'red') in a quadstrip (formed by an arbitrary number 'n' of quadrilaterals), approximating the 'Circular Annulus' shape with internal radius 'rI', external radius 'rE', and center '(xc,yc)'."<<endl;
	cout<<"\tNote that the 'Circular Annulus' shape is defined as follows:"<<endl<<endl;
	cout<<"\t| rI * cos(t) | <= | x(t) - xc | <= | rE * cos(t) |, | rI * sin(t) | <= | y(t) - yc | <= | rE * sin(t) |"<<endl<<endl;
	cout<<"\tfor every 't' in '[-pi,pi]', and for any 'rI'>0 and 'rE>0', such that 'rI<rE'."<<endl<<endl;
	cout<<"\tIn other words, it is formed by all points, belonging to the intersection of two concentric 'Circle' shapes of center '(xc,yc)' and of radius 'rI' and 'rE', respectively."<<endl<<endl;
	cout<<"\tThe external radius 'rE' and the internal radius 'rI', as well as the center coodinates '(xc,yc)' of the 'Circular Annulus' shape, are specified interactively by the user, which can also:"<<endl<<endl;
	cout<<"\t\t-) decide to render only the vertices for all quadrilaterals in the quadstrip of interest by pressing the 'p' key;"<<endl;
	cout<<"\t\t-) decide to render the 'wireframe versions' for all quadrilaterals in the quadstrip of interest by pressing the 'l' key;"<<endl;
	cout<<"\t\t-) decide to render the 'filled versions' for all quadrilaterals in the quadstrip of interest by pressing the 'f' key;"<<endl;
	cout<<"\t\t-) increase the number 'n' of all quadrilaterals in the quadstrip of interest by pressing the '+' key;"<<endl;
	cout<<"\t\t-) decrease the number 'n' of all quadrilaterals in the quadstrip of interest by pressing the '-' key."<<endl<<endl;
	cout<<"\tIt is possible to end this program by pressing one among the 'Q' - 'q' - 'Esc' keys."<<endl<<endl;
	cout<<"\tPlease, insert the internal radius 'rI' (thus, a positive and not null floating-point value) for the 'Circular Annulus' shape of interest: ";
	cin>>rI;
	if( (!cin) || (rI<=0) )
	{
		cout<<endl<<"\tPLEASE, INSERT A VALID VALUE (THUS, A POSITIVE AND NOT NULL FLOATING-POINT VALUE) FOR THE INTERNAL RADIUS 'rI' OF INTEREST."<<endl<<endl<<"\tTHIS PROGRAM IS CLOSING ..."<<endl<<endl;
		cout.flush();
		return EXIT_FAILURE;
	}
	
	/* Now, we read the external radius 'rE' for the 'Circular Annulus' shape of interest. */
	cout<<"\tPlease, insert the external radius 'rE' (thus, a positive and not null floating-point value, such that 'rE'>"<<rI<<") for the 'Circular Annulus' shape of interest: ";
	cin>>rE;
	if( (!cin) || (rE<=0) || (rE<=rI) )
	{
		cout<<endl<<"\tPLEASE, INSERT A VALID VALUE (THUS, A POSITIVE AND NOT NULL FLOATING-POINT VALUE, SUCH THAT 'rE'>"<<rI<<") FOR THE EXTERNAL RADIUS 'rE' OF INTEREST."<<endl<<endl<<"\tTHIS PROGRAM IS CLOSING ..."<<endl<<endl;
		cout.flush();
		return EXIT_FAILURE;
	}
	
	/* Now, we read the center coordinates '(xc,yc)' for the 'Circular Annulus' shape of interest. */
	cout<<"\tPlease, insert the center coordinates '(xc,yc)' for the 'Circular Annulus' shape of interest (thus, 2 floating-point values, separated by a space): ";
	cout.flush();
	cin>>xc>>yc;
	if(!cin)
	{
		cout<<endl<<"\tPLEASE, INSERT THE CENTER COORDINATES '(xc,yc)' FOR THE 'CIRCULAR ANNULUS' SHAPE OF INTEREST (THUS, 2 FLOATING-POINT VALUES, SEPARATED BY A SPACE)."<<endl<<endl<<"\tTHIS PROGRAM IS CLOSING ..."<<endl<<endl;
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

/// This function updates the viewport for the scene when it is resized. */
void resize(int w, int h)
{
	/* We update the projections and the modeling matrices! */
	glViewport(0, 0, w, h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glOrtho(xc-1.1*rE,xc+1.1*rE,yc-1.1*rE,yc+1.1*rE,-1,1);
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
		
		/* The key is '+', thus we increase the number of all quadrilaterals in the quadstrip of interest. */
		num_quads=num_quads+1;
		glutPostRedisplay();
		break;
		
		case '-':
		
		/* The key is '-', thus we decrease the number of all quadrilaterals (if possible) in the quadstrip of interest. */
		if(num_quads>3) num_quads=num_quads-1;
		else cout<<"\tThe minimum number 'n'=3 of all quadrilaterals in the quadstrip of interest is reached, and it is not possible to decrease again this number."<<endl;
		cout.flush();
		glutPostRedisplay();
		break;
		
		case 'l':

		/* The key is 'l', thus we choose to render only the 'wireframe versions' of all quadrilaterals in the quadstrip, used for approximating the 'Circular Annulus' shape of interest. */
		choice='l';
		glutPostRedisplay();
		break;
		
		case 'f':
		
		/* The key is 'f', thus we choose to render only the 'filled versions' of all quadrilaterals in the quadstrip, used for approximating the 'Circular Annulus' shape of interest. */
		choice='f';
		glutPostRedisplay();
		break;
		
		case 'p':
		
		/* The key is 'p', thus we choose to render only the vertices of all quadrilaterals in the quadstrip, used for approximating the 'Circular Annulus' shape of interest. */
		choice='p';
		glutPostRedisplay();
		break;

		default:

    	/* Other keys are not important for us */
    	break;
	}
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	num_quads=3;
	choice='l';
	cout<<"\tAt the beginning, the 'wireframe versions' of 'n'="<<num_quads<<" quadrilaterals (thus, the minimum number 'n' of quadrilaterals as possible) in the quadstrip, approximating the 'Circular Annulus' shape of center '("<<xc<<","<<yc<<")',";
	cout<<" internal radius 'rI'="<<rI<<", and external radius 'rE'="<<rE<<", are rendered."<<endl<<endl;
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
		glVertex3f(xc+rI*cos(t),yc+rI*sin(t),0);
		glVertex3f(xc+rE*cos(t),yc+rE*sin(t),0);
		t=t+(2*PI/num_quads);
	}
	
	/* If we arrive here, all is ok */
	glEnd();
	glFlush();
	glFlush();
	if(choice=='l') 
	{ 
		/* We draw the 'wireframe versions' (in 'red') for all quadrilaterals in the quadstrip of interest! */
		cout<<"\tThe 'wireframe versions' of 'n'="<<num_quads<<" quadrilaterals in the quadstrip of interest, are rendered."<<endl; 
		cout.flush();
	}
    else if(choice=='f') 
    {
    	/* We draw the 'filled versions' (in 'red') for all quadrilaterals in the quadstrip of interest! */
    	cout<<"\tThe 'filled versions' of 'n'="<<num_quads<<" quadrilaterals in the quadstrip of interest, are rendered."<<endl; 
		cout.flush();
    }
    else if(choice=='p') 
    { 
    	/* We draw only the vertices (in 'red') for all quadrilaterals in the quadstrip of interest! */
    	cout<<"\tOnly the vertices of 'n'="<<num_quads<<" quadrilaterals in the quadstrip of interest, are rendered."<<endl;
		cout.flush();
    }
}
