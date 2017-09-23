/*******************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 * 
 * Last update: September 2017
 *
 * main.cpp - the main function for the 'Example-020 (Old Mode)' Test.
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

/* Prototypes for all functions of interest! */
void draw();
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);

/// The main function for the <i>'Example-020 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-020' Test, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws '2' versions of the 'Double Square Annulus' shape in an OpenGL window. This shape is bounded by an 'outer' axis-parallel rectangle, and by '2'";
	cout<<" 'inner' axis-parallel rectangles, entirely contained in the 'outer' rectangle."<<endl;
	cout<<"\tBroadly speaking, any 'Double Square Annulus' shape is the union of '2' 'Square Annulus' shapes, connected along one side of their 'outer' ";
	cout<<"rectangles. Recall that any 'Square Annulus' shape is contained between '2' (concentric)"<<endl;
	cout<<"\taxis-parallel rectangles of different size."<<endl<<endl;
	cout<<"\tHere, the 'Double Square Annulus' shape of interest is approximated by only one triangle strip (in 'red'), where a bunch of 'Steiner' points are added in ";
	cout<<"order to make this possible. Specifically, this test draws the 'filled' and"<<endl;
	cout<<"\tthe 'wireframe versions' of all triangles in the triangle strip, just mentioned."<<endl<<endl;
	cout<<"\tThis test also provides a very basic interaction mechanism with the user. Here, the window of interest can be closed by pressing any among the 'Q', the ";
	cout<<"'q', and the 'Esc' keys."<<endl<<endl;
	cout<<"\t----------------------------------------------------------------------------------------------------------------------------------------------------------";
	cout<<"------------------------------------------------------------------------------"<<endl<<endl;

	/* If we arrive here, then we draw the 'wireframe' and the 'filled' versions for the triangle strip of interest. */
	cout.flush();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(450,480);
	glutCreateWindow("The 'Example-020' Test, based on the (Old Mode) OpenGL");
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
   	glOrtho(0,200,0,300,-1,1);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function initializes the OpenGL window of interest.
void initialize() { glClearColor(1.0, 1.0, 1.0, 0.0); }

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' keys. */
	switch (key)
	{
		case 'q':
	
			/* The key is 'q', thus we can exit from this program. */
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

		default:

			/* Other keys are not important for us! */
			break;
	}
}

/// This function draws the <i>'filled'</i> and the <i>'wireframe versions'</i> of the triangle strip (in <i>'red'</i>), which approximates the <i>'Double Square Annulus'</i> shape, in the OpenGL window of interest.
void draw()
{
	/* We draw the 'filled' and the 'wireframe versions' of the triangle strip (in 'red'), which approximates the 'Double Square Annulus' shape, in the OpenGL window 
	 * of interest. First, we draw the 'wireframe version' for the triangle strip of interest (in 'red'). */
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(95,10,0);
	glVertex3f(80,30,0);
	glVertex3f(10,10,0);
	glVertex3f(30,30,0);
	glVertex3f(10,140,0);
	glVertex3f(30,110,0);
	glVertex3f(50,140,0);
	glVertex3f(80,110,0);
	glVertex3f(95,140,0);
	glVertex3f(110,110,0);
	glVertex3f(140,140,0);
	glVertex3f(140,110,0);
	glVertex3f(180,140,0);
	glVertex3f(160,110,0);
	glVertex3f(180,10,0);
	glVertex3f(160,30,0);
	glVertex3f(95,10,0);
	glVertex3f(110,30,0);
	glVertex3f(80,30,0);
	glVertex3f(110,110,0);
	glVertex3f(80,110,0);
	glEnd();
	
	/* Now, we draw the 'filled version' for the triangle strip of interest (in 'red'). */
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(95,160,0);
	glVertex3f(80,180,0);
	glVertex3f(10,160,0);
	glVertex3f(30,180,0);
	glVertex3f(10,290,0);
	glVertex3f(30,260,0);
	glVertex3f(50,290,0);
	glVertex3f(80,260,0);
	glVertex3f(95,290,0);
	glVertex3f(110,260,0);
	glVertex3f(140,290,0);
	glVertex3f(140,260,0);
	glVertex3f(180,290,0);
	glVertex3f(160,260,0);
	glVertex3f(180,160,0);
	glVertex3f(160,180,0);
	glVertex3f(95,160,0);
	glVertex3f(110,180,0);
	glVertex3f(80,180,0);
	glVertex3f(110,260,0);
	glVertex3f(80,260,0);
	glEnd();
	glFlush();
}

