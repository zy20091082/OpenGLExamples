/*******************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 * 
 * Last update: September 2017
 * 
 * main.cpp - the main function for the 'Example-010 (Old Mode)' Test.
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

/// This flag identifies what graphic primitive must be exploited for rendering the cloud of several 3D points in the scene.
/**
 * The value of this global variable indicates what graphic primitive must be exploited in the scene by following these conventions:
 *
 * 	-) the 'GL_POINTS' value, used for rendering several independent 3D points (key '0');
 * 	-) the 'GL_LINES' value, used for rendering several independent lines (key '1');
 * 	-) the 'GL_LINE_STRIP' value, used for rendering an open line strip (key '2');
 * 	-) the 'GL_LINE_LOOP' value, used for rendering a closed line strip (key '3');
 * 	-) the 'GL_TRIANGLES' value, used for rendering several triangles (key '4');
 * 	-) the 'GL_POLYGON' value, used for rendering a unique polygon (key '5').
 *
 * The user can choose what graphic primitive must be exploited by pressing, respectively, the '0' ... '5' keys.
 */
int rendering;

/* Prototypes for all functions of interest! */
void draw();
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);

/// The main function for the <i>'Example-010 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-010' Test, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws several graphic primitives in an OpenGL window, starting from a cloud of 3D points."<<endl;
	cout<<"\tThis test also provides a very basic interaction mechanism with the user, which can choose what graphic primitive must be exploited, as follows:";
	cout<<endl<<endl;
	cout << "\t\t0. the 'GL_POINTS' primitive is chosen by pressing the '0' key for drawing several independent 3D points;" << endl;
	cout << "\t\t1. the 'GL_LINES' primitive is chosen by pressing the '1' key for drawing several independent lines;" << endl;
	cout << "\t\t2. the 'GL_LINE_STRIP' primitive is chosen by pressing the '2' key for drawing an open line strip;" << endl;
	cout << "\t\t3. the 'GL_LINE_LOOP' primitive is chosen by pressing the '3' key for drawing a closed line loop;" << endl;
	cout << "\t\t4. the 'GL_TRIANGLES' primitive is chosen by pressing the '4' key for drawing several independent triangles;" << endl;
	cout << "\t\t5. the 'GL_POLYGON' primitive is chosen by pressing the '5' key for drawing only one polygon."<<endl<<endl;
	cout<<"\tLikewise, the window of interest can be closed by pressing any among the 'Q', the 'q', and the 'Esc' keys."<<endl<<endl;
	cout<<"\t----------------------------------------------------------------------------------------------------------------------------------------------------------";
	cout<<"------------------------------------------------------------------------------"<<endl<<endl;
	cout.flush();

	/* If we arrive here, then we draw the initial scene! */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(480,480);
	glutCreateWindow("The 'Example-010' Test, based on the (Old Mode) OpenGL");
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
   	glOrtho(0,130,0,120,-1,1);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(1.0, 1.0, 1.0, 0.0); 
	rendering=GL_POINTS;
	cout<<"\tAt the beginning, the 'GL_POINTS' primitive is used for drawing several independents 3D points in the scene."<<endl<<endl;
	cout.flush();
}

/// This function draws the cloud of several 3D points in the OpenGL window of interest by using the graphic primitive, chosen by the user.
void draw()
{
	/* We draw the cloud of several 3D points in the OpenGL window of interest by using the graphic primitive, chosen by the user. */
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(10.0);
	glLineWidth(2.0);
	glColor3f(1,0,0);
	glBegin(rendering);
	glVertex3f(20,80,0);
	glVertex3f(20,50,0);
	glVertex3f(50,20,0);
	glVertex3f(80,20,0);
	glVertex3f(110,50,0);
	glVertex3f(110,80,0);
	glVertex3f(80,100,0);
	glVertex3f(50,100,0);
	glEnd();
	glFlush();
	switch(rendering)
	{
		case GL_POINTS:

			/* The 'GL_POINTS' primitive is currently used for drawing several independent 3D points in the scene. */
			cout<<"\tThe 'GL_POINTS' primitive is currently used for drawing several independents 3D points in the scene."<<endl;
			cout.flush();
			break;
		
		case GL_LINES:
		
			/* The 'GL_LINES' primitive is currently used for drawing several independent lines in the scene. */
			cout<<"\tThe 'GL_LINES' primitive is currently used for drawing several independent lines in the scene."<<endl;
			cout.flush();
			break;
		
		case GL_LINE_STRIP:

			/* The 'GL_LINE_STRIP' primitive is currently used for drawing an open line strip in the scene. */
			cout<<"\tThe 'GL_LINE_STRIP' primitive is currently used for drawing an open line strip in the scene."<<endl;
			cout.flush();
			break;

		case GL_LINE_LOOP:

			/* The 'GL_LINE_LOOP' primitive is currently used for drawing a closed line loop in the scene. */
			cout<<"\tThe 'GL_LINE_LOOP' primitive is currently used for drawing a closed line loop in the scene."<<endl;
			cout.flush();
			break;
		
		case GL_TRIANGLES:

			/* The 'GL_TRIANGLES' primitive is currently used for drawing several independent triangles in the scene. */
			cout<<"\tThe 'GL_TRIANGLES' primitive is currently used for drawing several independent triangles in the scene."<<endl;
			cout.flush();
			break;
		
		case GL_POLYGON:

			/* The 'GL_POLYGON' primitive is currently used for drawing only one polygon in the scene. */
			cout<<"\tThe 'GL_POLYGON' primitive is currently used for drawing only one polygon in the scene."<<endl;
			cout.flush();
			break;

		default:

			/* Something is wrong here. We do nothing! */
			break;
	}
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '0' - '1' - '2' - '3' - '4' - '5' keys. */
	switch (key)
	{
		case 'q':
	
			/* The key is 'q', thus we can exit from this program. */
			cout<<endl<<"\tThis program is closing correctly ... "<<endl<<endl;
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
			cout<<endl<<"\tThis program is closing correctly ... "<<endl<<endl;
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
			cout<<endl<<"\tThis program is closing correctly ... "<<endl<<endl;
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
		
			/* The key is '0', thus the 'GL_POINTS' primitive is currently used for drawing several independent 3D points in the scene. */
			rendering=GL_POINTS;
			glutPostRedisplay();
			break;

		case '1':
		
			/* The key is '1', thus the 'GL_LINES' primitive is currently used for drawing several independent lines in the scene. */
			rendering=GL_LINES;
			glutPostRedisplay();
			break;
		
		case '2':
		
			/* The key is '2', thus the 'GL_LINE_STRIP' primitive is currently used for drawing an open line strip in the scene. */
			rendering=GL_LINE_STRIP;
			glutPostRedisplay();
			break;
		
		case '3':
		
			/* The key is '3', thus the 'GL_LINE_LOOP' primitive is currently used for drawing a closed line loop in the scene. */
			rendering=GL_LINE_LOOP;
			glutPostRedisplay();
			break;
		
		case '4':
		
			/* The key is '4', thus the 'GL_TRIANGLES' primitive is currently used for drawing several triangles in the scene. */
			rendering=GL_TRIANGLES;
			glutPostRedisplay();
			break;

		case '5':
		
			/* The key is '5', thus the 'GL_POLYGON' primitive is currently used for drawing only one polygon in the scene. */
			rendering=GL_POLYGON;
			glutPostRedisplay();
			break;
		
		default:

			/* Other keys are not important for us! */
			break;
	}
}

