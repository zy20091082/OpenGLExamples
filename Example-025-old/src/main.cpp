/*******************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 * 
 * Last update: January 2017
 *
 * This program is Free Software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.                                       
 *                                                                         
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License (http://www.gnu.org/licenses/gpl.txt) for more details.
 * 
 * main.cpp - the main function for the 'Example-025 (Old Mode)' example
 *******************************************************************************************************************************************************/

/* First, we must understand which platform we are using. */
#if defined(_MSC_VER)

	/* We are using the Microsoft Visual Studio, thus we must fix the bug, regarding the 'min()' and the 'max()' template functions. */
	#define NOMINMAX
	#include <algorithm>
	using namespace std;

#endif
#include <cstdlib>
#include <iostream>
#include <cmath>
using namespace std;

#ifdef __APPLE__

	/* We are using a MacOSX platform (Macintosh) */
	#include "GL/glew.h"
	#include "GLUT/glut.h"
	#include "OpenGL/gl.h"

#else

	/* We are not using a MacOSX platform. Thus, we have a generic Unix-like platform, like the GNU Linux, or a Microsoft Windows platform. */
	#include "GL/glew.h"
	#include "GL/glut.h"
	#include "GL/gl.h"

#endif

/// The number of the samples, used for drawing the parabola of interest.
unsigned int num_samples;

/// The coefficients for the parabola of interest
float a,b,c;

/// The coordinates for the vertex of the parabola of interest.
float xv,yv;

/// The semi-length for the interval of interest.
float radius;

/// The x- and the y-ranges for the scene of interest.
float xmin,xmax,ymin,ymax;

/* Prototypes for all functions of interest! */
void draw();
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);
float evaluateParabola(float x);

/// The main function for the <i>'Example-025 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	float vmin,vmax,h;

	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-025' Example, based on the (Old Mode) OpenGL"<<endl<<endl;
	cout.flush();
	cout<<"\tPlease, insert all coefficients for the parabola of interest in the form 'a x^2 + b x + c = 0' (separated by spaces): ";
	cin>>a>>b>>c;
	if( (!cin) || (a==0) )
	{
		cout<<"\tPLEASE, INSERT VALID COEFFICIENTS FOR THE PARABOLA OF INTEREST IN THE FORM 'a x^2 + b x + c = 0' (SEPARATED BY SPACES)"<<endl<<endl;
		cout.flush();
		return EXIT_FAILURE;
	}
	
	/* If we arrive here, we can compute the vertex (xv,yv) for the parabola of interest. */
	xv=-b/(2.0*a);
	yv=evaluateParabola(xv);
	cout<<endl<<"\tVertex for the parabola of interest '(xv,yv)' = "<<xv<<" "<<yv<<endl<<endl;
	cout.flush();
	
	/* Now, we read the semi-length 'R' for the interval [-R,R] of interest, used for rendering the parabola of interest. */
	cout<<"\tPlease, insert the semi-length 'R', used for deciding the x-range [";
	if(xv==0) cout<<"-R,+R]";
	else cout<<xv<<"-R,"<<xv<<"+R]";
	cout<<" for the parabola of interest: ";
	cin>>radius;
	if( (!cin) || (radius<=0) )
	{
		cout<<"\tPLEASE, INSERT A VALID VALUE FOR THE SEMI-LENGTH 'R' OF THE INTERVAL [-R,R] (POSITIVE AND NOT NULL), USED FOR DECIDING THE X-RANGE FOR THE PARABOLA OF INTEREST"<<endl<<endl;
		cout.flush();
		return EXIT_FAILURE;
	}

	/* Now, we complete everything! */
	xmin=xv-radius;
	xmax=xv+radius;
	cout<<endl<<"\tThe x-range for the parabola of interest: ["<<xmin<<","<<xmax<<"]"<<endl<<endl;
	vmin=evaluateParabola(xmin);
	vmax=evaluateParabola(xmax);
	ymin=min((float)min(vmin,vmax),yv);
	ymax=max((float)max(vmin,vmax),yv);
	cout<<"\tThe y-range for the parabola of interest: ["<<ymin<<","<<ymax<<"]"<<endl<<endl;
	h=fabs(ymin-ymax);
	
	/* If we arrive here, we can draw our parabola! */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	if(h==2*radius) glutInitWindowSize(500,500);
	else if(2*radius>h) { glutInitWindowSize(1000,1000*h/(2*radius)); }
	else { glutInitWindowSize(1000*2*radius/h,1000); }
	glutCreateWindow("The 'Example-025' Example, based on the (Old Mode) OpenGL");
	glutDisplayFunc(draw);
	glutReshapeFunc(resize);
	glutKeyboardFunc(manageKeys);
	glewExperimental = GL_TRUE;
   	glewInit();
   	initialize(); 
	glutMainLoop();
	return EXIT_SUCCESS;
}

/// This function evaluates the parabola at a certain point.
float evaluateParabola(float x) { return (a*x*x+b*x+c); }

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	num_samples=3;
	cout<<"\tWe draw a parabola of equation ("<<a<<","<<b<<","<<c<<") * (x^2,x,1) = 0, in the x-range ["<<xv-radius<<","<<xv+radius<<"], and with vertex ("<<xv<<","<<yv<<")"<<endl<<endl;
	cout.flush();
}

/// This function updates the viewport for the scene when it is resized. */
void resize(int w, int h)
{
	float x0,x1,y0,y1;

	/* First, we set properly the x-range. */
	x0=xmin-0.1*fabs(xmin);
	x1=xmax+0.1*fabs(xmax);
	y0=ymin-0.1*fabs(ymin);
	y1=ymax+0.1*fabs(ymax);
	if(xmin==0)
	{
		x1=xmax+0.1*fabs(xmax);
		x0=-0.1*fabs(xmax);
	}
	else if(xmax==0)
	{
		x0=xmin-0.1*fabs(xmin);
		x1=0.1*fabs(xmin);
	}
	
	/* Now, we set properly the y-range. */
	if(ymin==0)
	{
		y1=ymax+0.1*fabs(ymax);
		y0=-0.1*fabs(ymax);
	}
	else if(ymax==0)
	{
		y0=ymin-0.1*fabs(ymin);
		y1=0.1*fabs(ymin);
	}
	
	/* We update the projections and the modeling matrices! */
	glViewport(0, 0, w, h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glOrtho(x0,x1,y0,y1,-1,1);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '+' - '-' keys */
	switch (key)
	{
		case 'q':
	
		/* The key is 'q' */
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case 'Q':
	
		/* The key is 'Q' */
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case 27:
	
		/* The key is 'Esc' */
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case '+':
		
		/* The key is '+', thus we increase the number of the samples! */
		num_samples=num_samples+1;
		glutPostRedisplay();
		break;
		
		case '-':
		
		/* The key is '-', thus we decrease the number of the samples! */
		if(num_samples>3) num_samples=num_samples-1;
		else cout<<"\tThe minimum number 3 of samples is reached"<<endl;
		cout.flush();
		glutPostRedisplay();
		break;
	
		default:

    	/* Other keys are not important for us */
    	break;
	}
}

/// This function draws the parabola in the OpenGL window of interest by using the current settings.
void draw()
{
	float d,x;

	/* We draw the the parabola in the OpenGL window of interest by using the current settings. */
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINE_STRIP);
	d=(2*radius)/(num_samples-1);
	for(unsigned int k=0;k<num_samples;k++)
	{
		x=xmin+k*d;
		glVertex3f(x,evaluateParabola(x),0);
	}
	
	/* If we arrive here, all is ok */
	glEnd();
	glFlush();
	cout<<"\tApproximated and drawn the parabola of interest (polyline) with "<<num_samples<<" samples"<<endl;
	cout.flush();
}
