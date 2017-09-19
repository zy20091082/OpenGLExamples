/*******************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 * 
 * Last update: September 2017
 *
 * main.cpp - the main function for the 'Example-029 (Old Mode)' Test.
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

/// The number <i>'n'</i> of the vertices (and also of the edges) to be used for defining the (closed) polyline, approximating the <i>'Lissajous-like'</i> curve of interest.
/**
 * The value of this global variable is the number 'n>6' of the vertices (and also of the edges) to be used for defining the (closed) polyline, approximating the
 * 'Lissajous-like' curve of interest (in 'red'). The value of 'n>6', initially set to 'n=7', can be increased and decreased by pressing the '+' and the '-' keys,
 * respectively. By construction, it is not possible to have 'n<7'.
 */
unsigned int num_samples=7;

/// The coefficients to be used for defining the (closed) polyline, approximating the <i>'Lissajous-like'</i> curve of interest.
/**
 * The values of these global variables contain, respectively, the coefficients 'Kx', 'Ky', 'Rx', and 'Ry', that are used for defining the (closed) polyline, 
 * approximating the 'Lissajous-like' curve of interest (in 'red'). This latter is defined as follows:
 *
 * x(t) = Rx * cos( Kx * t ), y(t) = Ry * sin( Ky * t )
 *
 * for any 't' in '[0,2*pi]', and for any 'Kx>0', 'Ky>0', 'Rx>0', and 'Ry>0'. For the sake of the simplicity, these coefficients are described by positive and not null
 * integer values, provided interactively by the user. Their values imposes certain properties for the 'Lissajous-like' curve of interest.
 */
int Kx,Ky,Rx,Ry;

/* Prototypes for all functions of interest! */
void draw();
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);
void pause();

/// The main function for the <i>'Example-029 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-029' Test, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws a (closed) polyline (in 'red'), which is formed by an arbitrary number 'n>6' of the vertices (and thus also of the edges), in an OpenGL window.";
	cout<<" The (closed) polyline of interest approximates the 'Lissajous-like' curve with"<<endl;
	cout<<"\tcoefficients 'Rx>0', 'Kx>0', 'Ry>0', and 'Ky>0'. The 'Lissajous-like' curve is defined as follows:"<<endl<<endl;
	cout<<"\tx(t) = Rx * cos( Kx * t ), y(t) = Ry * sin( Ky * t )"<<endl<<endl;
	cout<<"\tfor every 't' in '[0,2*pi]', and for any 'Kx>0', 'Ky>0', 'Rx>0', and 'Ry>0'. For the sake of the simplicity, its coefficients are described by positive";
	cout<<" and not null integer values, provided interactively by the user. Their values"<<endl;
	cout<<"\timpose certain properties for the 'Lissajous-like' curve of interest. For instance, if 'Rx=Ry' and 'Kx=Ky', then the resulting 'Lissajous-like' curve ";
	cout<<"coincides with the 'Circle' curve."<<endl<<endl;
	cout<<"\tFor the sake of the clarity, the scene, drawn by this test, includes also the coordinate axes (in 'blue')."<<endl<<endl;
	cout<<"\tThis test also provides a very basic interaction mechanism with the user, which must provide interactively all coefficients of the 'Lissajous-like' curve";
	cout<<" (as mentioned above). In this context, the user can also:"<<endl<<endl;
	cout<<"\t\t-) increase the number 'n' of the vertices and the edges in the (closed) polyline of interest by pressing the '+' key. By construction, it is not ";
	cout<<"possible to have 'n<7'."<<endl;
	cout<<"\t\t-) Decrease the number 'n' of the vertices and the edges in the (closed) polyline of interest by pressing the '-' key. By construction, it is not ";
	cout<<"possible to have 'n<7'."<<endl<<endl;
	cout<<"\tLikewise, the window of interest can be closed by pressing any among the 'Q', the 'q', and the 'Esc' keys."<<endl<<endl;
	cout<<"\t----------------------------------------------------------------------------------------------------------------------------------------------------------";
	cout<<"------------------------------------------------------------------------------"<<endl<<endl;
	cout.flush();

	/* If we arrive here, then we can read the coefficient 'Rx>0' for the 'Lissajous-like' curve of interest. */
	cout<<"\tPlease, insert the coefficient 'Rx>0' (thus, a positive and not null 'integer' value) for the 'Lissajous-like' curve of interest: ";
	cin>>Rx;
	if( (!cin) || (Rx<=0) )
	{
		cin.clear();
		cout<<endl<<"\tPLEASE, INSERT A VALID VALUE (THUS, A POSITIVE AND NOT NULL 'INTEGER' VALUE) FOR THE COEFFICIENT 'Rx>0' OF INTEREST."<<endl<<endl;
		cout<<"\tTHIS PROGRAM IS CLOSING ..."<<endl<<endl;
		pause();
		return EXIT_FAILURE;
	}

	/* If we arrive here, then we can read the coefficient 'Kx>0' for the 'Lissajous-like' curve of interest. */
	cout<<"\tPlease, insert the coefficient 'Kx>0' (thus, a positive and not null 'integer' value) for the 'Lissajous-like' curve of interest: ";
	cin>>Kx;
	if( (!cin) || (Kx<=0) )
	{
		cin.clear();
		cout<<endl<<"\tPLEASE, INSERT A VALID VALUE (THUS, A POSITIVE AND NOT NULL 'INTEGER' VALUE) FOR THE COEFFICIENT 'Kx>0' OF INTEREST."<<endl<<endl;
		cout<<"\tTHIS PROGRAM IS CLOSING ..."<<endl<<endl;
		pause();
		return EXIT_FAILURE;
	}
	
	/* If we arrive here, then we can read the coefficient 'Ry>0' for the 'Lissajous-like' curve of interest. */
	cout<<"\tPlease, insert the coefficient 'Ry>0' (thus, a positive and not null 'integer' value) for the 'Lissajous-like' curve of interest: ";
	cin>>Ry;
	if( (!cin) || (Ry<=0) )
	{
		cin.clear();
		cout<<endl<<"\tPLEASE, INSERT A VALID VALUE (THUS, A POSITIVE AND NOT NULL 'INTEGER' VALUE) FOR THE COEFFICIENT 'Ry>0' OF INTEREST."<<endl<<endl;
		cout<<"\tTHIS PROGRAM IS CLOSING ..."<<endl<<endl;
		pause();
		return EXIT_FAILURE;
	}

	/* If we arrive here, then we can read the coefficient 'Ky>0' for the 'Lissajous-like' curve of interest. */
	cout<<"\tPlease, insert the coefficient 'Ky>0' (thus, a positive and not null 'integer' value) for the 'Lissajous-like' curve of interest: ";
	cin>>Ky;
	if( (!cin) || (Ky<=0) )
	{
		cin.clear();
		cout<<endl<<"\tPLEASE, INSERT A VALID VALUE (THUS, A POSITIVE AND NOT NULL 'INTEGER' VALUE) FOR THE COEFFICIENT 'Ky>0' OF INTEREST."<<endl<<endl;
		cout<<"\tTHIS PROGRAM IS CLOSING ..."<<endl<<endl;
		pause();
		return EXIT_FAILURE;
	}

	/* Here, we summarize the equation for the 'Lissajous-like' curve of interest. */
	cout<<endl<<"\tThe 'Lissajous-like' curve of interest has the following equation:"<<endl<<endl;
	cout<<"\tx(t) = "<<Rx<<" * cos( "<<Kx<<" * t ), y(t) = "<<Ry<<" * sin( "<<Ky<<" * t )"<<endl<<endl;
	cout<<"\tfor any 't' in '[0,2*pi]'."<<endl;
	cout.flush();

	/* If we arrive here, then we can draw the (closed) polyline, approximating the 'Lissajous-like' curve! */
	cout<<endl;
	cout<<"\t----------------------------------------------------------------------------------------------------------------------------------------------------------";
	cout<<"------------------------------------------------------------------------------"<<endl<<endl;
	cout.flush();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	if(Rx==Ry) glutInitWindowSize(500,500);
	else if(Rx>Ry) { glutInitWindowSize(1000,1000*Ry/Rx); }
	else { glutInitWindowSize(1000*Rx/Ry,1000); }
	glutCreateWindow("The 'Example-029' Test, based on the (Old Mode) OpenGL");
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
   	glOrtho(-1.1*Rx,1.1*Rx,-1.1*Ry,1.1*Ry,-1,1);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function draws the (closed) polyline (in <i>'red'</i>), approximating the <i>'Lissajous-like'</i> curve of interest, in the main OpenGL window.
void draw()
{
	/* We draw the (closed) polyline (in 'red'), approximating the 'Lissajous-like' curve of interest, in the main OpenGL window. For the sake of the clarity, we
	 * also draw the coordinate axes (in 'blue'). */
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,0.0,1.0);
	glLineWidth(1);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-1.1*Rx,0.0,0.0);
	glVertex3f(0.0,0.0,0.0);
	glVertex3f(1.1*Rx,0.0,0.0);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.0,-1.1*Ry,0.0);
	glVertex3f(0.0,0.0,0.0);
	glVertex3f(0.0,1.1*Ry,0.0);
	glEnd();

	/* Now, we draw the (closed) polyline of interest (in 'red'). */
	glColor3f(1.0,0.0,0.0);
	glLineWidth(2);
	float d=(2*PI)/(num_samples-1);
	float t=0.0;
	glBegin(GL_LINE_LOOP);
	for(int k=0;k<=num_samples;k++)
	{
		t=k*d;
		glVertex3f(Rx*cos(Kx*t),Ry*sin(Ky*t),0);
	}

	/* If we arrive here, then all is ok! */
	glEnd();
	glFlush();
	cout<<"\tThe 'Lissajous-like' curve of interest is currently approximated by a (closed) polyline with 'n="<<num_samples<<"' vertices and 'n="<<num_samples<<"' ";
	cout<<"edges."<<endl;
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
		
			/* The key is '+', thus we increase the number 'n>6' of the vertices and the edges in the (closed) polyline of interest. By construction, it is not possible
			 * to have 'n<7'. */
			num_samples=num_samples+1;
			glutPostRedisplay();
			break;
		
		case '-':
		
			/* The key is '-', thus we decrease the number 'n>6' of the vertices and the edges (if possible) in the (closed) polyline of interest. By construction, it is
			 * not possible to have 'n<7'. */
			if(num_samples>7) num_samples=num_samples-1;
			else
			{
				/* Here, we have already 'n=7', and it is not possible to decrease again the value of 'n'. */
				cout<<"\tThe minimum number 'n=7' of the vertices and the edges in the (closed) polyline of interest is reached, and it is not possible to decrease ";
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

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	num_samples=7;
	cout<<"\tAt the beginning, the (closed) polyline, approximating the 'Lissajous-like' curve with coefficients 'Rx="<<Rx<<"', 'Ry="<<Ry<<"', 'Kx="<<Kx<<"', ";
	cout<<"and 'Ky="<<Ky<<"', is formed by 'n="<<num_samples<<"' vertices and 'n="<<num_samples<<"' edges (thus by the minimum number 'n' as possible)."<<endl<<endl;
	cout.flush();
}

