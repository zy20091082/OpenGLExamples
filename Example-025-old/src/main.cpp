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
 * main.cpp - the main function for the 'Example-025 (Old Mode)' Test.
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

/// The coefficients of the equation, describing the <i>'Parabola'</i> curve of interest.
/**
 * The 'Parabola' curve of interest is described by the equation 'a x^2 + b x + c = 0 ', where 'a' is not null (clearly). They are described by 3 floating-point values.
 */
float a,b,c;

/// The number <i>'n'</i> of the vertices and the edges in the polyline, approximating the <i>'Parabola'</i> curve of interest.
/**
 * It is initially set to 'n=3', which is the minimum number 'n' of the vertices and the edges. It is interactively modified by pressing the '+' and the '-' keys.
 */
unsigned int num_samples=3;

/// The coordinates <i>'(xv,yv)'</i> for the vertex to be used for defining and drawing the polyline, approximating the <i>'Parabola'</i> curve of interest.
/**
 * Here, the coordinates '(xv,yv)' of the vertex are determined by the coefficients 'a', 'b', and 'c', as follows:
 * 
 * xv = -b / ( 2 * a ), yv = a * xv ^ 2 + b * xv + c
 */
float xv,yv;

/// The x- and the y-ranges for the scene, where the polyline, approximating the <i>'Parabola'</i> curve of interest, must be drawn.
/**
 * The values are useful for fixing the orthographic projection, used for drawing the scene. Here, the x-range of the 'Parabola' curve is '[ xv - R, xv + R ]' (by construction). Instead, the y-range depends on the specific 'Parabola' curve of interest.
 */
float xmin,xmax,ymin,ymax;

/// The radius <i>'R'</i> for the interval <i>['xv-R,xv+R']</i>, where the polyline, approximating the <i>'Parabola'</i> curve of interest, must be drawn.
/**
 * It must be a positive and not null floating-point value, provided interactively by the user. In this case, the 'Parabola' curve of interest is centered with respect to its vertex '(xv,yv)', and its x-range is '[ xv - R, xv + R ]' (by construction).
 */
float R;

/* Prototypes for all functions of interest! */
void draw();
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);
float evaluateParabola(float x);
void exportEquation();

/// The main function for the <i>'Example-025 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	float vmin,vmax,h;

	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-025' Test, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tdraws a polyline (in 'red'), formed by an arbitrary number 'n' of the vertices and the edges, in an OpenGL window. The polyline of interest approximates a portion of the 'Parabola' curve with vertex '(xv,yv)'. The portion of"<<endl;
	cout<<"\tinterest for the 'Parabola' curve is defined as follows:"<<endl<<endl;
	cout<<"\tx(t) = t, y(t) = a * t ^ 2 + b * t + c"<<endl<<endl<<"\tfor any not null 'a', and for every 't' in '[xv-R,xv+R]', with any 'R'>0."<<endl<<endl;
	cout<<"\tThe parameters 'a', 'b', and 'c' determine the properties of the 'Parabola' curve. In particular, its vertex '(xv,yv)' is defined as follows:"<<endl<<endl;
	cout<<"\txv = -b / (2 * a), yv = a * xv ^ 2 + b * xv + c"<<endl<<endl;
	cout<<"\tThis test also provides a very basic interaction mechanism with the user, which must provide the parameters 'a', 'b', and 'c', as well as the semi-length 'R' of the range '[xv-R,xv+R]'. The user can also:"<<endl<<endl;
	cout<<"\t\t-) increase the number 'n' of the vertices and the edges in the polyline of interest by pressing the '+' key;"<<endl;
	cout<<"\t\t-) decrease the number 'n' of the vertices and the edges in the polyline of interest by pressing the '-' key."<<endl<<endl;
	cout<<"\tLikewise, the window of interest can be closed by pressing any among the 'Q', the 'q', and the 'Esc' keys."<<endl<<endl;
	cout<<"\tPlease, insert all coefficients '(a,b,c)' for the equation 'a * x ^ 2 + b * x + c = 0' (thus, 3 floating-point values, separated by spaces, such that 'a' is not null), describing the 'Parabola' curve of interest: ";
	cin>>a>>b>>c;
	if( (!cin) || (a==0) )
	{
		cout<<endl<<"\tPLEASE, INSERT VALID COEFFICIENTS '(a,b,c)' FOR THE EQUATION 'a * x ^ 2 + b * x + c = 0' (THUS, 3 FLOATING-POINT VALUES, SEPARATED BY SPACES, SUCH THAT 'a' IS NOT NULL), DESCRIBING THE 'PARABOLA' CURVE OF INTEREST."<<endl<<endl;
		cout<<"\tTHIS PROGRAM IS CLOSING ... "<<endl<<endl;
		cout.flush();
		return EXIT_FAILURE;
	}
	
	/* If we arrive here, we can compute the vertex '(xv,yv)' for the custom 'Parabola' curve of interest. Then, we read the radius 'R' from the standard input stream. */
	xv=-b/(2.0*a);
	yv=evaluateParabola(xv);
	cout<<endl<<"\tIn this case, the 'Parabola' curve of interest has equation ";
	exportEquation();
	cout<<", and vertex '(xv,yv)' = ("<<xv<<","<<yv<<")."<<endl<<endl;
	cout<<"\tPlease, insert the radius 'R' (thus, a positive and not null floating-point value), used for determining the x-range [";
	if(xv==0) cout<<"-R,+R]";
	else cout<<xv<<"-R,"<<xv<<"+R]";
	cout<<", where the 'Parabola' curve is drawn: ";
	cin>>R;
	if( (!cin) || (R<=0) )
	{
		cout<<endl<<"\tPLEASE, INSERT A VALID VALUE (THUS, A POSITIVE AND NOT NULL FLOATING-POINT VALUE) FOR THE RADIUS 'R' OF INTEREST."<<endl<<endl<<"\tTHIS PROGRAM IS CLOSING ..."<<endl<<endl;
		cout.flush();
		return EXIT_FAILURE;
	}
	
	/* Now, we complete everything! */
	xmin=xv-R;
	xmax=xv+R;
	cout<<endl<<"\tAs mentioned above, the 'Parabola' curve of interest has equation ";
	exportEquation();
	cout<<", and vertex '(xv,yv)' = ("<<xv<<","<<yv<<")."<<endl;
	cout<<"\tThe x-range for the 'Parabola' of interest is ["<<xmin<<","<<xmax<<"]."<<endl;
	vmin=evaluateParabola(xmin);
	vmax=evaluateParabola(xmax);
	ymin=min((float)min(vmin,vmax),yv);
	ymax=max((float)max(vmin,vmax),yv);
	cout<<"\tThe y-range for the 'Parabola' curve of interest is ["<<ymin<<","<<ymax<<"]."<<endl<<endl;
	h=fabs(ymin-ymax);
	cout.flush();
	
	/* If we arrive here, we can draw the polyline, approximating the 'Parabola' curve of interest. */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	if(h==2*R) glutInitWindowSize(500,500);
	else if(2*R>h) { glutInitWindowSize(1000,1000*h/(2*R)); }
	else { glutInitWindowSize(1000*2*R/h,1000); }
	glutCreateWindow("The 'Example-025' Test, based on the (Old Mode) OpenGL");
	glutDisplayFunc(draw);
	glutReshapeFunc(resize);
	glutKeyboardFunc(manageKeys);
	glewExperimental = GL_TRUE;
   	glewInit();
   	initialize(); 
	glutMainLoop();
	return EXIT_SUCCESS;
}

/// This function evaluates the y-value for equation, describing the <i>'Parabola'</i> curve of interest, at a given x-coordinate.
/**
 * Here, the equation for the 'Parabola' curve of interest is 'a * x ^ 2 + b * x + c = 0', for any x (described by a floating-point value).
 */
float evaluateParabola(float x) { return (a*x*x+b*x+c); }

/// This function exports the human-readable version of the equation for the <i>'Parabola'</i> curve of interest on the standard output stream.
/**
 * Here, the equation for the 'Parabola' curve of interest is 'a * x ^ 2 + b * x + c = 0', for any x (described by a floating-point value).
 */
void exportEquation()
{
	/* Now, we check the 'a' value in the equation 'ax^2+bx+c=0'. */
	cout<<"'";
	if(a>0)
	{
		if(fabs(a)!=1.0) cout<<fabs(a);
		cout<<" * x^2 ";
	}
	else if(a<0)
	{
		cout<<"-";
		if(fabs(a)!=1.0) cout<<fabs(a);
		cout<<" * x^2 ";
	}	
	
	/* Now, we check the 'b' value in the equation 'ax^2+bx+c=0'. */
	if(b>0)
	{
		if(fabs(b)!=1.0) cout<<"+ "<<fabs(b)<<" * x ";
		else cout<<"+ x ";
	}
	else if(b<0)
	{
		if(fabs(b)!=1.0) cout<<"- "<<fabs(b)<<" * x ";
		else cout<<"- x ";
	}

	/* Finally, we check the 'c' value in the equation 'ax^2+bx+c=0'. */
	if(c>0) { cout<<"+ "<<fabs(c)<<" "; }
	else if(c<0) { cout<<"- "<<fabs(c)<<" "; }
	cout<<"= 0'";
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '+' - '-' keys. */
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
		
		/* The key is '+', thus we increase the number 'n' of the vertices and the edges in the polyline of interest! */
		num_samples=num_samples+1;
		glutPostRedisplay();
		break;
		
		case '-':
		
		/* The key is '-', thus we decrease the number 'n' of the vertices and the edges (if possible) in the polyline of interest. */
		if(num_samples>3) num_samples=num_samples-1;
		else cout<<"\tThe minimum number 'n=3' of the vertices and the edges in the polyline of interest is reached, and it is not possible to decrease again this number."<<endl;
		cout.flush();
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
	
	/* We update the projection and the modeling matrices! */
	glViewport(0, 0, w, h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glOrtho(x0,x1,y0,y1,-1,1);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	num_samples=3;
	cout<<"\tAt the beginning, the polyline, approximating the portion of interest for the 'Parabola' curve, is formed by 'n="<<num_samples<<"' vertices and edges (thus by the minimum number 'n' as possible of the vertices and the edges)."<<endl<<endl;
	cout.flush();
}

/// This function draws the polyline (in <i>'red'</i>), approximating the <i>'Parabola'</i> curve of interest, in the main OpenGL window.
void draw()
{
	float d,x;

	/* We draw the polyline (in 'red'), approximating the 'Parabola' curve of interest, in the main OpenGL window. */
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINE_STRIP);
	d=(2*R)/(num_samples-1);
	for(unsigned int k=0;k<num_samples;k++)
	{
		x=xmin+k*d;
		glVertex3f(x,evaluateParabola(x),0);
	}

	/* If we arrive here, all is ok */
	glEnd();
	glFlush();
	cout<<"\tThe portion of interest for the 'Parabola' curve is currently approximated by a polyline with 'n="<<num_samples<<"' vertices and 'n="<<num_samples<<"' edges."<<endl;
	cout.flush();
}
