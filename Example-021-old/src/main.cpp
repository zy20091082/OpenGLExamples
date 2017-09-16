/*******************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 * 
 * Last update: September 2017
 *
 * main.cpp - the main function for the 'Example-021 (Old Mode)' Test.
 *******************************************************************************************************************************************************/

/* First, we must understand which platform we are using. */
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <string>
#include <climits>
#include <limits>
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

/// The radius <i>'R'</i> to be used for defining and drawing the (closed) polyline, approximating the <i>'Circle'</i> curve of interest.
/**
 * The value of this global variable is the length of the radius 'R' to be used for defining and drawing the (closed) polyline, approximating the 'Circle' curve of
 * interest. Clearly, the radius for the 'Circle' curve of interest consists of a positive and not null floating-point value, that is provided interactively by the user.
 */
float radius;

/// The center coordinates <i>'(xc,yc)'</i> to be used for defining and drawing the (closed) polyline, approximating the <i>'Circle'</i> curve of interest.
/**
 * The values of these global variables contain, respectively, the center coordinates '(xc,yc)' for the (closed) polyline, approximating the 'Circle' curve of interest.
 * Clearly, the center coordinates for the 'Circle' curve of interest consist of '2' floating-point values, that are provided interactively by the user.
 */
float xc,yc;

/// The number <i>'n'</i> of the vertices (and also of the edges) to be used for defining the (closed) polyline, approximating the <i>'Circle'</i> curve of interest.
/**
 * The value of this global variable is the number 'n>2' of the vertices (and also of the edges) to be used for defining the (closed) polyline, approximating the
 * 'Circle' curve of interest. The value of 'n>2', initially set to 'n=3', can be increased and decreased by pressing the '+' and the '-' keys, respectively. By
 * construction, it is not possible to have 'n<3'.
 */
unsigned int num_samples=3;

/* Prototypes for all functions of interest! */
void draw();
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);
void pause();

/// The main function for the <i>'Example-021 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-021' Test, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws a (closed) polyline (in 'red'), which is formed by an arbitrary number 'n>2' of the vertices (and thus also of the edges), in an OpenGL window.";
	cout<<" The (closed) polyline of interest approximates the 'Circle' curve of radius 'R'"<<endl;
	cout<<"\tand center coordinates '(xc,yc)'. The 'Circle' curve is defined as follows:"<<endl<<endl;
	cout<<"\tx(t) = xc + R * cos(t), y(t) = yc + R * sin(t)"<<endl<<endl<<"\tfor any 'R>0', and for every 't' in '[-pi,pi]'. Broadly speaking, the 'Circle' curve is ";
	cout<<"the boundary of the 'Circle' shape, containing all points at distance at most 'R' from the center '(xc,yc)'."<<endl<<endl;
	cout<<"\tThe center of the scene, drawn by this test, coincides with the center '(xc,yc)' of the 'Circle' shape/curve (in 'blue')."<<endl<<endl;
	cout<<"\tThis test also provides a very basic interaction mechanism with the user, which must provide interactively the radius 'R' (as a positive and not null ";
	cout<<"floating-point value) and the center coordinates '(xc,yc)' (as '2' floating-point"<<endl;
	cout<<"\tvalues). In this context, the user can also:"<<endl<<endl;
	cout<<"\t\t-) increase the number 'n' of the vertices and the edges in the (closed) polyline of interest by pressing the '+' key. By construction, it is not ";
	cout<<"possible to have 'n<3'."<<endl;
	cout<<"\t\t-) Decrease the number 'n' of the vertices and the edges in the (closed) polyline of interest by pressing the '-' key. By construction, it is not ";
	cout<<"possible to have 'n<3'."<<endl<<endl;
	cout<<"\tLikewise, the window of interest can be closed by pressing any among the 'Q', the 'q', and the 'Esc' keys."<<endl<<endl;
	cout<<"\t----------------------------------------------------------------------------------------------------------------------------------------------------------";
	cout<<"------------------------------------------------------------------------------"<<endl<<endl;
	cout.flush();

	/* If we arrive here, then we can read the radius 'R' for the 'Circle' curve of interest. */
	cout<<"\tPlease, insert the radius 'R' (thus, a positive and not null floating-point value) for the 'Circle' curve of interest: ";
	cin>>radius;
	if( (!cin) || (radius<=0) )
	{
		cin.clear();
		cout<<endl<<"\tPLEASE, INSERT A VALID VALUE (THUS, A POSITIVE AND NOT NULL FLOATING-POINT VALUE) FOR THE RADIUS 'R' OF INTEREST."<<endl<<endl;
		cout<<"\tTHIS PROGRAM IS CLOSING ..."<<endl<<endl;
		pause();
		return EXIT_FAILURE;
	}

	/* Now, we read the center coordinates '(xc,yc)' for the 'Circle' curve of interest. */
	cout<<"\tPlease, insert the center coordinates '(xc,yc)' for the 'Circle' curve of interest (thus, 2 floating-point values, separated by a space): ";
	cout.flush();
	cin>>xc>>yc;
	if(!cin)
	{
		cin.clear();
		cout<<endl<<"\tPLEASE, INSERT THE CENTER COORDINATES '(xc,yc)' FOR THE 'CIRCLE' CURVE OF INTEREST (THUS, 2 FLOATING-POINT VALUES, SEPARATED BY A SPACE).";
		cout<<endl<<endl<<"\tTHIS PROGRAM IS CLOSING ..."<<endl<<endl;
		pause();
		return EXIT_FAILURE;
	}
	
	/* If we arrive here, then we can draw the (closed) polyline, approximating the 'Circle' curve! */
	cout<<endl;
	cout<<"\t----------------------------------------------------------------------------------------------------------------------------------------------------------";
	cout<<"------------------------------------------------------------------------------"<<endl<<endl;
	cout.flush();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-021' Test, based on the (Old Mode) OpenGL");
	glutDisplayFunc(draw);
	glutReshapeFunc(resize);
	glutKeyboardFunc(manageKeys);
	glewExperimental = GL_TRUE;
   	glewInit();
   	initialize(); 
	glutMainLoop();
	return EXIT_SUCCESS;
}

/// This function simulates a pause while this test runs.
void pause()
{
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cin.clear();
	cout << "\tPress the RETURN key to finish ... ";
	cout.flush();
	cin.get();
	#ifndef _MSC_VER
		cout << endl;
		cout.flush();
	#endif
}

/// This function updates the viewport for the scene when it is resized. */
void resize(int w, int h)
{
	/* We update the projection and the modeling matrices! */
	glViewport(0, 0, w, h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glOrtho(xc-1.1*radius,xc+1.1*radius,yc-1.1*radius,yc+1.1*radius,-1,1);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	num_samples=3;
	cout<<"\tAt the beginning, the (closed) polyline, approximating the 'Circle' curve of center '("<<xc<<","<<yc<<")' and radius 'R="<<radius<<"', is formed by 'n=";
	cout<<num_samples<<"' vertices and 'n="<<num_samples<<"' edges (thus by the minimum number 'n' as possible)."<<endl<<endl;
	cout.flush();
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '+' - '-' keys. */
	switch (key)
	{
		case 'q':
	
			/* The key is 'q', thus we can exit from this program. */
			cout<<endl<<"\tThis program is closing correctly ... "<<endl<<endl;
			pause();
			exit(EXIT_SUCCESS);
			break;
		
		case 'Q':
	
			/* The key is 'Q', thus we can exit from this program. */
			cout<<endl<<"\tThis program is closing correctly ... "<<endl<<endl;
			pause();
			exit(EXIT_SUCCESS);
			break;
		
		case 27:
	
			/* The key is 'Esc', thus we can exit from this program. */
			cout<<endl<<"\tThis program is closing correctly ... "<<endl<<endl;
			pause();
			exit(EXIT_SUCCESS);
			break;
		
		case '+':
		
			/* The key is '+', thus we increase the number 'n>2' of the vertices and the edges in the (closed) polyline of interest. By construction, it is not possible
			 * to have 'n<3'. */
			num_samples=num_samples+1;
			glutPostRedisplay();
			break;
		
		case '-':
		
			/* The key is '-', thus we decrease the number 'n>2' of the vertices and the edges (if possible) in the (closed) polyline of interest. By construction, it is
			 * not possible to have 'n<3'. */
			if(num_samples>3) num_samples=num_samples-1;
			else
			{
				/* Here, we have already 'n=3', and it is not possible to decrease again the value of 'n'. */
				cout<<"\tThe minimum number 'n=3' of the vertices and the edges in the (closed) polyline of interest is reached, and it is not possible to decrease ";
				cout<<"again this number."<<endl;
				cout.flush();
			}

			/* If we arrive here, then this case is finished! */
			glutPostRedisplay();
			break;

		default:

    		/* Other keys are not important for us! */
    		break;
	}
}

/// This function draws the (closed) polyline (in <i>'red'</i>), approximating the <i>'Circle'</i> curve of interest, in the main OpenGL window.
void draw()
{
	float t;

	/* We draw the (closed) polyline (in 'red'), approximating the 'Circle' curve of interest, in the main OpenGL window. */
	t=0;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINE_LOOP);
	for(unsigned int i=0;i<=num_samples;i++)
	{
		glVertex3f(xc+radius*cos(t),yc+radius*sin(t),0);
		t=t+(2*PI/num_samples);
	}
	
	/* If we arrive here, then all is ok, and we can draw the center '(xc,yc)' of the 'Circle' curve of interest (in 'blue'). */
	glEnd();
	glColor3f(0.0,0.0,1.0);
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex3f(xc,yc,0);
	glEnd();
	glFlush();
	cout<<"\tThe 'Circle' curve of interest is currently approximated by a (closed) polyline with 'n="<<num_samples<<"' vertices and 'n="<<num_samples<<"' edges."<<endl;
	cout.flush();
}

