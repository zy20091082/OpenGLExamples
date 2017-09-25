/*******************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 * 
 * Last update: September 2017
 *
 * main.cpp - the main function for the 'Example-022 (Old Mode)' Test.
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

/// The radius <i>'R'</i> to be used for defining and drawing the version of the <i>'Circle'</i> shape to be considered.
/**
 * The value of this global variable is the length of the radius 'R>0' to be used for defining and drawing the version of the 'Circle' shape to be considered. Clearly,
 * the radius for the desired version of the 'Circle' shape consists of a positive and not null floating-point value, that is provided interactively by the user.
 */
float radius;

/// The center coordinates <i>'(xc,yc)'</i> to be used for defining and drawing the desired version of the <i>'Circle'</i> shape.
/**
 * The values of these global variables contain, respectively, the center coordinates '(xc,yc)' for the desired version of the 'Circle' shape. Clearly, the center 
 * coordinates for the desired version of the 'Circle' shape consist of '2' floating-point values, that are provided interactively by the user.
 */
float xc,yc;

/// The desired version of the <i>'Circle'</i> shape to be defined and drawn in this test.
/**
 * The value of this global variable identifies what version of the 'Circle' shape must be defined and drawn in this test by following these conventions:
 *
 * 	-) 'l': 	we choose to approximate only the boundary for the 'Circle' shape of interest by using a (closed) polyline (in 'red') with an arbitrary number 'n>2' of
 * 				the vertices and the edges. We call this (closed) polyline as the 'Version #0' of the 'Circle' shape, which is activated by pressing the 'l' key.
 *
 * 	-) 'f':		we choose to approximate the 'Circle' shape of interest by using a triangle fan of an arbitrary number 'n>2' of the triangles (in 'dark gray'). These
 *				triangles are incident at the 'reference vertex' (in 'red'), which coincides with the center '(xc,yc)' of the 'Circle' shape. We call this triangle fan 
 *				as the 'Version #1' of the 'Circle' shape, which is activated by pressing the 'f' key.
 *
 * 	-) 'p':		we choose to approximate the 'Circle' shape of interest by using only one polygon (in 'red') with an arbitrary number 'n>2' of the vertices and the
 * 				edges. We call this polygon as the 'Version #2' of the 'Circle' shape, which is activated by pressing the 'p' key.
 */
char choice;

/// The number <i>'n'</i> of the samples to be used for defining and drawing the desired version of the <i>'Circle'</i> shape.
/**
 * The value of this global variable contains the number 'n>2' of the samples to be used for defining and drawing the desired version of the 'Circle' shape. Its meaning
 * depends on which specific version of the 'Circle' shape. Specifically:
 *
 * 	-) 	when representing the 'Version #0' of the 'Circle' shape, we choose to approximate only the boundary for the 'Circle' shape of interest by using a (closed)
 * 		polyline (in 'red') with an arbitrary number 'n>2' of the vertices and the edges.
 *
 *	-) 	When representing the 'Version #1' of the 'Circle' shape, we choose to approximate the 'Circle' shape of interest by using a triangle fan of an arbitrary number
 * 		'n>2' of the triangles (in 'dark gray'). These triangles are incident at the 'reference vertex' (in 'red'), which coincides with the center '(xc,yc)' of the
 * 		'Circle' shape.
 *
 * The value of 'n>2', initially set to 'n=3', can be increased and decreased by pressing the '+' and the '-' keys, respectively. By construction, it is not possible to
 * have 'n<3'.
 */
unsigned int num_samples=3;

/* Prototypes for all functions of interest! */
void draw();
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);
void pause();

/// The main function for the <i>'Example-022 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-022' Test, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws '3' different versions of the 'Circle' shape with radius 'R>0' and center coordinates '(xc,yc)' in an OpenGL window. Intuitively, the 'Circle'";
	cout<<" shape contains all points at distance at most 'R>0' from the center '(xc,yc)',"<<endl<<"\tand is defined as follows:"<<endl<<endl;
	cout<<"\t| x(t) - xc | <= R * cos(t), | y(t) - yc | <= R * sin(t)"<<endl<<endl<<"\tfor any 'R>0', and for every 't' in '[-pi,pi]'."<<endl<<endl;
	cout<<"\tSpecifically, the user can choose upon request any among the following versions of the 'Circle' shape:"<<endl<<endl;
	cout<<"\t\t0) the 'Version #0' of the 'Circle' shape describes only the boundary for the 'Circle' shape of interest by using a (closed) polyline (in 'red') with ";
	cout<<"an arbitrary number 'n>2' of the vertices and the edges."<<endl;
	cout<<"\t\t1) The 'Version #1' of the 'Circle' shape describes the shape by using a triangle fan with an arbitrary number 'n>2' of triangles (in 'dark gray')";
	cout<<" and with 'm=n+1' vertices (including the 'reference vertex', in 'red')."<<endl;
	cout<<"\t\t2) The 'Version #2' of the 'Circle' shape describes the shape by using only one polygon (in 'red') with an arbitrary number 'n>2' of the vertices";
	cout<<" and the edges."<<endl<<endl;
	cout<<"\tThe center of the scene, drawn by this test, coincides with the center '(xc,yc)' of the 'Circle' shape (in 'blue')."<<endl<<endl;
	cout<<"\tThis test also provides a very basic interaction mechanism with the user, which must provide interactively the radius 'R>0' (as a positive and not null ";
	cout<<"floating-point value) and the center coordinates '(xc,yc)' (as a pair of '2'"<<endl;
	cout<<"\tfloating-point values). In this context, the user can also:"<<endl<<endl;
	cout<<"\t\t-) choose to draw the 'Version #0' of the 'Circle' shape by pressing the 'l' key;"<<endl;
	cout<<"\t\t-) choose to draw the 'Version #1' of the 'Circle' shape by pressing the 'f' key;"<<endl;
	cout<<"\t\t-) choose to draw the 'Version #2' of the 'Circle' shape by pressing the 'p' key;"<<endl;
	cout<<"\t\t-) increase the number 'n' of the samples in the desired version of the 'Circle' shape by pressing the '+' key. By construction, it is not possible to ";
	cout<<"have 'n<3'."<<endl;
	cout<<"\t\t-) Decrease the number 'n' of the samples in the desired version of the 'Circle' shape by pressing the '+' key. By construction, it is not possible to ";
	cout<<"have 'n<3'."<<endl<<endl;
	cout<<"\tLikewise, the window of interest can be closed by pressing any among the 'Q', the 'q', and the 'Esc' keys."<<endl<<endl;
	cout<<"\t----------------------------------------------------------------------------------------------------------------------------------------------------------";
	cout<<"------------------------------------------------------------------------------"<<endl<<endl;
	cout.flush();

	/* If we arrive here, then we can read the radius 'R>0' for the desired version of the 'Circle' shape. */
	cout<<"\tPlease, insert the radius 'R>0' (thus, a positive and not null floating-point value) for the desired version of the 'Circle' shape: ";
	cin>>radius;
	if( (!cin) || (radius<=0) )
	{
		cin.clear();
		cout<<endl<<"\tPLEASE, INSERT A VALID VALUE (THUS, A POSITIVE AND NOT NULL FLOATING-POINT VALUE) FOR THE RADIUS 'R>0' OF INTEREST."<<endl<<endl;
		cout<<"\tTHIS PROGRAM IS CLOSING ..."<<endl<<endl;
		pause();
		return EXIT_FAILURE;
	}

	/* Now, we read the center coordinates '(xc,yc)' for the version of the desired 'Circle' shape. */
	cout<<"\tPlease, insert the center coordinates '(xc,yc)' for the desired version of the 'Circle' shape (thus, '2' floating-point values, separated by a space): ";
	cout.flush();
	cin>>xc>>yc;
	if(!cin)
	{
		cin.clear();
		cout<<endl<<"\tPLEASE, INSERT THE CENTER COORDINATES '(xc,yc)' FOR THE DESIRED VERSION OF THE 'CIRCLE' SHAPE (THUS, '2' FLOATING-POINT VALUES, SEPARATED BY A";
		cout<<" SPACE)."<<endl<<endl<<"\tTHIS PROGRAM IS CLOSING ..."<<endl<<endl;
		pause();
		return EXIT_FAILURE;
	}

	/* If we arrive here, then we can draw the desired version of the 'Circle' shape, chosen by the user. */
	cout<<endl;
	cout<<"\t----------------------------------------------------------------------------------------------------------------------------------------------------------";
	cout<<"------------------------------------------------------------------------------"<<endl<<endl;
	cout.flush();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-022' Test, based on the (Old Mode) OpenGL");
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

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	num_samples=3;
	choice='l';
	cout<<"\tAt the beginning, the boundary of the 'Circle' shape with center '("<<xc<<","<<yc<<")' and radius 'R="<<radius<<"' ('Version #0') is approximated ";
	cout<<"by a (closed) polyline with 'n="<<num_samples<<"' vertices and 'n="<<num_samples<<"' edges (thus by the minimum number 'n' as possible)."<<endl<<endl;
	cout.flush();
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

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '+' - '-' - 'l' - 'f' - 'p' keys. */
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
		
			/* The key is '+', thus we increase the number 'n>2' of the samples in the desired version of the 'Circle' shape (chosen by the user). By construction, it
			 * is not possible to have 'n<3'. */
			num_samples=num_samples+1;
			glutPostRedisplay();
			break;

		case '-':
		
			/* The key is '-', thus we decrease the number 'n>2' of the samples (if possible) in the desired version of the 'Circle' shape (chosen by the user). By
			 * construction, it is not possible to have 'n<3'. */
			if(num_samples>3) num_samples=num_samples-1;
			else
			{
				cout<<"\tThe minimum number 'n=3' of the ";
				if(choice=='l') cout<<"vertices and the edges in the (closed) polyline, approximating the boundary of the 'Circle' shape (the 'Version #0'), ";
				if(choice=='p') cout<<"vertices and the edges in the 'filled version' of the polygon, approximating the 'Circle' shape (the 'Version #2'), ";
				if(choice=='f') cout<<"'filled versions' for all triangles in the triangle fan, approximating the 'Circle' shape (the 'Version #1'), ";
				cout<<"is reached, and it is not possible to decrease again this number."<<endl;
				cout.flush();
			}

			/* If we arrive here, then this case is finished! */
			glutPostRedisplay();
			break;

		case 'l':
		
			/* The key is 'l', thus we choose to approximate only the boundary for the 'Circle' shape of interest by using a (closed) polyline (in 'red') with an
			 * arbitrary number 'n>2' of the vertices and the edges (the 'Version #0'). */
			choice='l';
			glutPostRedisplay();
			break;

		case 'f':
		
			/* The key is 'f', thus we choose to approximate the 'Circle' shape of interest by using the 'filled versions' of an arbitrary number 'n>2' of the triangles
			 * (in 'dark gray') in a triangle fan with the center '(xc,yc)' of the 'Circle' shape as the reference vertex (the 'Version #1'). Here, the triangle fan has
			 * 'm=n+1' vertices (including the 'reference vertex', in 'red'). It is clear that 'm>3. */
			choice='f';
			glutPostRedisplay();
			break;

		case 'p':
		
			/* The key is 'p', thus we choose to approximate the 'Circle' shape of interest by using the 'filled version' of only one polygon (in 'red') with an
			 * arbitrary number 'n>2' of the vertices and the edges (the 'Version #2'). */
			choice='p';
			glutPostRedisplay();
			break;

		default:

    		/* Other keys are not important for us! */
    		break;
	}
}

/// This function draws the desired version of the <i>'Circle'</i> shape in the OpenGL window of interest by using the current rendering settings (chosen by the user).
void draw()
{
	float t=0;

	/* We draw the desired version of the 'Circle' shape in the OpenGL window of interest by using the current rendering settings (chosen by the user). */
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(5);
	glLineWidth(2);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	if(choice=='l')
	{
		/* We must approximate the boundary of the 'Circle' shape by using a (closed) polyline (in 'red') with 'n>2' vertices and 'n>2' edges. We indicate this (closed)
		 * polyline as the 'Version #0' of the 'Circle' shape. */
		glColor3f(1.0,0.0,0.0);
		glLineWidth(2);
		glBegin(GL_LINE_LOOP);
		for(unsigned int i=0;i<=num_samples;i++)
		{
			glVertex3f(xc+radius*cos(t),yc+radius*sin(t),0);
			t=t+(2*PI/num_samples);
		}
	}
	else if(choice=='f')
	{
		/* We must approximate the 'Circle' shape by using the 'filled versions' of 'n>2' triangles in a triangle fan, such that its 'reference vertex' is the center
		 * '(xc,yc)'. Here, all triangles are shown in 'dark gray', and the 'reference vertex' is depicted in 'red' in order to be highlighted. We indicate this shape
		 * as the 'Version #1' of the 'Circle' shape.
		 */
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_TRIANGLE_FAN);
		glVertex3f(xc,yc,0);
		glColor3f(0.5,0.5,0.5);
		for(unsigned int i=0;i<=num_samples;i++)
		{
			glVertex3f(xc+radius*cos(t),yc+radius*sin(t),0);
			t=t+(2*PI/num_samples);
		}
	}
	else if(choice=='p')
	{
		/* We must approximate the 'Circle' shape by using the 'filled version' of only one polygon (in 'red') with 'n>2' vertices and 'n>2' edges. We indicate this
		 * polygon as the 'Version #2' of the 'Circle' shape.
		 */
		glColor3f(1.0,0.0,0.0);
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		glBegin(GL_POLYGON);
		for(unsigned int i=0;i<=num_samples;i++)
		{
			glVertex3f(xc+radius*cos(t),yc+radius*sin(t),0);
			t=t+(2*PI/num_samples);
		}
	}
	
	/* If we arrive here, then all is ok, and we can draw the center '(xc,yc)' for desired version of the 'Circle' shape (in 'blue'). */
	glEnd();
	glColor3f(0.0,0.0,1.0);
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex3f(xc,yc,0);
	glEnd();
	glFlush();
	if(choice=='l')
	{
		cout<<"\tThe 'Version #0' for the 'Circle' shape of interest is currently approximated by a (closed) polyline with 'n="<<num_samples<<"' vertices and 'n=";
		cout<<num_samples<<"' edges."<<endl;
		cout.flush();
	}
	else if(choice=='f')
	{
		cout<<"\tThe 'Version #1' for the 'Circle' shape of interest is currently approximated by a triangle fan with 'n="<<num_samples<<"' triangles and 'm=n+1=";
		cout<<(num_samples+1)<<"' vertices (including the 'reference vertex')."<<endl;
		cout.flush();
	}
	else if(choice=='p')
	{
		cout<<"\tThe 'Version #2' for the 'Circle' shape of interest is currently approximated by only one polygon with 'n="<<num_samples<<"' vertices and 'n=";
		cout<<num_samples<<"' edges."<<endl;
		cout.flush();
	}
}

