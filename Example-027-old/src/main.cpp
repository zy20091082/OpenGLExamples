/*******************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 * 
 * Last update: September 2017
 *
 * main.cpp - the main function for the 'Example-027 (Old Mode)' Test.
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

/// The number <i>'n'</i> of the vertices to be used for defining the (open) polyline, approximating the <i>'Sine-like'</i> curve of interest.
/**
 * The value of this global variable is the number 'n>4' of the vertices to be used for defining the (open) polyline, approximating the portion of interest for the
 * 'Sine-like' curve of exponent 'k>0'. The 'Sine-like' curve of exponent 'k>0' is described by the following equation:
 *
 * x(t) = t, y(t) = sin^k (t)
 *
 * for each t in [-pi,pi], and for any 'k>0' (provided interactively by the user). This implies that the 'Sine-like' curve is approximated by a (open) polyline with
 * 'n>4' vertices and 'm=n-1' edges. The value of 'n>4', initially set to 'n=5', can be increased and decreased by pressing the '+' and the '-' keys, respectively. By
 * construction, it is not possible to have 'n<5'.
 */
unsigned int num_samples=5;

/// The exponent <i>'k'</i> to be used for defining the (open) polyline, approximating the <i>'Sine-like'</i> curve of interest.
/**
 * The value of this global variable is the exponent 'k>0' for defining the (open) polyline, approximating the portion of interest for the 'Sine-like' curve of exponent
 * 'k>0'. The 'Sine-like' curve of exponent 'k>0' is described by the following equation:
 *
 * x(t) = t, y(t) = sin^k (t)
 *
 * for each t in [-pi,pi], and for any 'k>0', provided interactively by the user. In other words, the value of this global variable is a positive and not null integer
 * value 'k>0'.
 */
int k=1;

/* Prototypes for all functions of interest! */
void draw();
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);
void pause();

/// The main function for the <i>'Example-027 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-027' Test, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws a (open) polyline (in 'red'), formed by an arbitrary number 'n>5' of the vertices (and thus by 'm=n-1' edges), in an OpenGL window. The (open) ";
	cout<<"polyline of interest approximates the 'Sine-like' curve in '[-pi,+pi]'. In"<<endl;
	cout<<"\tparticular, the 'Sine-like' curve is a generalization of the 'Sine' curve, and requires any given exponent 'k>0' for computing the sine function ";
	cout<<"to the 'k'-th. Specifically, the 'Sine-like' curve is defined as follows:"<<endl<<endl;
	cout<<"\tx(t) = t, y(t) = sin ^ k (t)"<<endl<<endl<<"\tfor any 'k>0', and for every 't' in '[-pi,pi]'."<<endl<<endl;
	cout<<"\tFor the sake of the clarity, the scene, drawn by this test, includes also the coordinate axes (in 'blue')."<<endl<<endl;
	cout<<"\tThis test also provides a very basic interaction mechanism with the user, which must provide interactively the exponent 'k>0' (as a not null and positive ";
	cout<<"integer value), and can also:"<<endl<<endl;
	cout<<"\t\t-) increase the number 'n' of the vertices (thus also the number 'm=n-1' of the edges) in the (open) polyline of interest by pressing the '+' key. By";
	cout<<" construction, it is not possible to have 'n<5' and 'm<4'."<<endl;
	cout<<"\t\t-) Decrease the number 'n' of the vertices (thus also the number 'm=n-1' of the edges) in the (open) polyline of interest by pressing the '-' key. By";
	cout<<" construction, it is not possible to have 'n<5' and 'm<4'."<<endl<<endl;
	cout<<"\tLikewise, the window of interest can be closed by pressing any among the 'Q', the 'q', and the 'Esc' keys."<<endl<<endl;
	cout.flush();

	/* If we arrive here, the user must insert the exponent 'k>0' for defining the 'Sine-like' curve of interest! */
	cout<<"\t----------------------------------------------------------------------------------------------------------------------------------------------------------";
	cout<<"------------------------------------------------------------------------------"<<endl<<endl;
	cout.flush();
	cout<<"\tPlease, insert the exponent 'k>0' (thus, a positive and not null 'integer' value) for defining the 'Sine-like' curve of interest: ";
	cin>>k;
	if( (!cin) || (k<=0) )
	{
		cin.clear();
		cout<<endl<<"\tPLEASE, INSERT A VALID VALUE (THUS, A POSITIVE AND NOT NULL 'INTEGER' VALUE) FOR THE EXPONENT 'k>0' OF INTEREST."<<endl<<endl;
		cout<<"\tTHIS PROGRAM IS CLOSING ..."<<endl<<endl;
		pause();
		return EXIT_FAILURE;
	}

	/* If we arrive here, then we can draw the (open) polyline, approximating the 'Sine-like' curve! */
	cout<<endl;
	cout<<"\tThe 'Sine-like' curve of interest has equation: "<<endl<<endl;
	cout<<"\tx(t) = t , y(t) = sin ^ "<<k<<" (t)"<<endl<<endl;
	cout<<"\tfor every 't' in '[-pi,pi]'."<<endl<<endl;
	cout<<"\t----------------------------------------------------------------------------------------------------------------------------------------------------------";
	cout<<"------------------------------------------------------------------------------"<<endl<<endl;
	cout.flush();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	if(k%2==0) glutInitWindowSize(600,600/(2*PI));
	else glutInitWindowSize(600,2*600/(2*PI));
	glutCreateWindow("The 'Example-027' Test, based on the (Old Mode) OpenGL");
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
		
			/* The key is '+', thus we increase the number 'n>4' of the vertices in the (open) polyline of interest. By construction, it is not possible to have 'n<5'.
			 */
			num_samples=num_samples+1;
			glutPostRedisplay();
			break;
		
		case '-':
		
			/* The key is '-', thus we decrease the number 'n>4' of the vertices (if possible) in the (open) polyline of interest. By construction, it is not possible to
			 * have 'n<5'. */
			if(num_samples>5) num_samples=num_samples-1;
			else
			{
				/* Here, we have already 'n=5', and it is not possible to decrease again the value of 'n'. */
				cout<<"\tThe minimum number 'n=5' of the vertices in the (open) polyline of interest is reached, and it is not possible to decrease ";
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

/// This function updates the viewport for the scene when it is resized. */
void resize(int w, int h)
{
	/* We update the projection and the modeling matrices! */
	glViewport(0, 0, w, h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	if(k%2==0) glOrtho(-PI-0.1,+PI+0.1,-0.1,1.1,-1,1);
   	else glOrtho(-PI-0.1,+PI+0.1,-1.1,1.1,-1,1);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	num_samples=5;
	cout<<"\tAt the beginning, the (open) polyline, approximating the 'Sine-like' curve with exponent 'k="<<k<<"', is formed by 'n="<<num_samples<<"' vertices and ";
	cout<<"'m=n-1="<<(num_samples-1)<<"' edges (thus by the minimum number 'n' as possible)."<<endl<<endl;
	cout.flush();
}

/// This function draws the (open) polyline (in <i>'red'</i>), approximating the <i>'Sine-like'</i> curve of interest, in the main OpenGL window.
void draw()
{
	float d,t;

	/* We draw the (open) polyline (in 'red'), approximating the 'Sine-like' curve of interest, in the main OpenGL window. For the sake of the clarity, we also the
	 * coordinates axes (in 'blue'). */
	d=(2*PI/(num_samples-1));
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f,0.0f,1.0f);
	glLineWidth(1);

	/* Now, we draw the x-axis (in 'blue'). */
	glBegin(GL_LINE_STRIP);
	glVertex3f(-PI,0.0f,0.0f);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(PI,0.0f,0.0f);
	glEnd();

	/* Now, we draw the y-axis (in 'blue'). */
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.0f,-1.0f,0.0f);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(0.0f,1.0f,0.0f);
	glEnd();

	/* If we arrive here, then we can draw the actual 'Sine-like' curve of exponent 'k>0'. */
	glColor3f(1.0,0.0,0.0);
	glLineWidth(2);
	glBegin(GL_LINE_STRIP);
	for(unsigned int i=0;i<num_samples;i++)
	{
		t=-PI+i*d;
		glVertex3f(t,pow(sin(t),k),0);
	}

	/* Finally, we are ok! */
	glEnd();
	glFlush();
	cout<<"\tThe (open) polyline, approximating the 'Sine-like' curve with exponent 'k="<<k<<"', is currently formed by 'n="<<num_samples<<"' vertices and 'm=n-1=";
	cout<<(num_samples-1)<<"' edges."<<endl;
	cout.flush();
}

