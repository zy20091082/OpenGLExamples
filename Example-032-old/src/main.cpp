/*******************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 * 
 * Last update: September 2017
 *
 * main.cpp - the main function for the 'Example-032 (Old Mode)' Test.
 *******************************************************************************************************************************************************/

/* First, we must understand which platform we are using. */
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <string>
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

/// The number <i>'n'</i> of the vertices for every triangle fan in the <i>'Bullseye'</i> shape of interest.
/**
 * The value of this global variable is the number 'n>4' of the vertices for every triangle fan (including the 'reference vertex'), which approximates any of the
 * 'Circle' shapes in the 'Bullseye' shape of interest. The value of 'n>4', initially set to 'n=5', can be increased and decreased by pressing the '+' and the '-' keys,
 * respectively. By construction, it is not possible to have 'n<5'.
 */
unsigned int num_samples=5;

/// The custom settings for rendering the triangles of interest in the triangle fans to be drawn.
/**
 * The value of this global variable indicates the rendering type of the triangles in the triangle fans to be drawn by following these conventions:
 *
 * 	-) the 'GL_LINE' value, used for rendering the 'wireframe versions' for all triangles in the triangle fans of interest;
 * 	-) the 'GL_FILL' value, used for rendering the 'filled versions' for all triangles in the triangle fans of interest.
 *
 *  It is possible to cycle between these rendering types for all triangles of interest by pressing the ' ' (space) key.
 */
GLenum mode=GL_FILL;

/* Prototypes for all functions of interest! */
void initialize();
void manageKeys(unsigned char key, int x, int y);
void draw();
void resize(int w,int h);
void drawDisc(float R,float X,float Y,float Z);

/// The main function for the <i>'Example-032 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a new window! */
	cout<<endl<<"\tThis is the 'Example-032' Test, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws a specific variant of the 'Bullseye' shape in an OpenGL window. A generic 'Bullseye' shape is defined by several concentric 'Circle' shapes ";
	cout<<"(disks) of different colors, same center '(xc,yc)', and radii of different length."<<endl;
	cout<<"\tRecall that the 'Circle' shape with radius 'R>0' and center '(xc,yc)' consists of all points, that are at distance at most 'R' from the center '(xc,yc)', ";
	cout<<"and is defined as follows:"<<endl<<endl;
	cout<<"\t| x(t) - xc | <= R * cos(t), | y(t) - yc | <= R * sin(t)"<<endl<<endl<<"\tfor any given 'R>0', and for every 't' in '[-pi,pi]'. In the remainder of this ";
	cout<<"test, we consider the 'Circle' shapes as centered at the origin '(0.0,0.0)'."<<endl<<endl;
	cout<<"\tIn other words, any 'Bullseye' shape is the union of all circular crowns, bounded by the 'Circle' curves, that are the boundary for the pairs of its ";
	cout<<"consecutive disks, if sorted with respect to the length of their radius. The"<<endl;
	cout<<"\t'Bullseye' shape often represents the targets in the shooting and the archery competitions."<<endl<<endl;
	cout<<"\tIn this test, we restrict our attention to a specific approximation of the 'Bullseye' shape, formed by '5' concentric disks. In any case, the ";
	cout<<"approximation of interest is not 'real', since it is the result of considering only the"<<endl;
	cout<<"\tapproximations of the 'Circle' shapes, placed at different z-depth. In this context, the scene is drawn by using the orthographic projection, such that ";
	cout<<"the center of every 'Circle' shape is projected on the same point. Each 'Circle'"<<endl;
	cout<<"\tshape of interest is approximated by a triangle fan of 'n>4' vertices (including the 'reference vertex'). All 'Circle' shapes are drawn in different ";
	cout<<"colors by using the z-buffer (depth test) technique. Thus, the result is a 'false'"<<endl;
	cout<<"\tapproximation of the 'Bullseye' shape, and is always the same, despite the rendering order of the 'Circle' shapes."<<endl<<endl;
	cout<<"\tHere, the user cannot modify the radius, the number, and the colors for the 'Circle' shapes of interest, since they are fixed in advance. Instead, the ";
	cout<<"user can:"<<endl<<endl;
	cout<<"\t\t-) choose to render either the 'wireframe' or the 'filled versions' for all triangles in the triangle fans of interest by pressing cyclically the ";
	cout<<"' ' (space) key;"<<endl;
	cout<<"\t\t-) increase the number 'n' of all vertices in every triangle fan of interest (including the 'reference vertex') by pressing the '+' key. By ";
	cout<<"construction, it is not possible to have 'n<5'."<<endl;
	cout<<"\t\t-) Decrease the number 'n' of all vertices in every triangle fan of interest (including the 'reference vertex') by pressing the '-' key. By ";
	cout<<"construction, it is not possible to have 'n<5'."<<endl<<endl;
	cout<<"\tLikewise, the window of interest can be closed by pressing any among the 'Q', the 'q', and the 'Esc' keys."<<endl<<endl;
	cout<<"\t----------------------------------------------------------------------------------------------------------------------------------------------------------";
	cout<<"------------------------------------------------------------------------------"<<endl<<endl;
	cout.flush();

	/* If we arrive here, then we can draw the approximation of the 'Bullseye' shape in the scene. */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE|GLUT_DEPTH);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-032' Test, based on the (Old Mode) OpenGL");
	glutReshapeFunc(resize);
	glutKeyboardFunc(manageKeys);
	glutDisplayFunc(draw);
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
   	glOrtho(-100,100,-100,100,-100,10);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function draws a triangle fan, which approximates a given <i>'Circle'</i> shape.
/**
 * Here, the 'Circle' shape of interest has radius 'R', and center '(X,Y)'. It is also planar, and its supporting plane has equation 'z=Z'.
 */
void drawDisc(float R,float X,float Y,float Z)
{
	/* Now, we draw a triangle fan with radius 'R' and center '(X,Y,Z)'. */
	float d=(2*PI)/(num_samples-1);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(X,Y,Z);
	for(int i=0;i<num_samples;i++)
	{
		float t=i*d;
		glVertex3f(X+R*cos(t),Y+R*sin(t),Z);
	}
	
	/* If we arrive here, then all is ok. */
	glEnd();
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '+' - '-' - ' ' (space) keys. */
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
		
		case '+':
		
			/* The key is '+', thus we increase the number 'n>4' of the vertices in every triangle fan (including its 'reference vertex'), which approximates any of '5'
			 * 'Circle' shapes in the 'Bullseye' shape of interest. By construction, it is not possible to have 'n<5'.
			 */
			num_samples=num_samples+1;
			glutPostRedisplay();
			break;
		
		case '-':
		
			/* The key is '-', thus we decrease (if possible) the number 'n>4' of the vertices in every triangle fan (including its 'reference vertex'), which 
		 	 * approximates any of '5' 'Circle' shapes in the 'Bullseye' shape of interest. By construction, it is not possible to have 'n<5'.
			 */
			if(num_samples>5) num_samples=num_samples-1;
			else
			{
				cout<<"\tThe minimum number 'n=5' of the vertices for every triangle fan of interest is reached, and it is not possible to decrease again this number.";
				cout<<endl;
				cout.flush();
			}

			/* If we arrive here, then this case is finished! */
			glutPostRedisplay();
			break;
		
		case ' ':
		
			/* The key is ' ' (space), thus we change the rendering mode for all triangles in the triangle fans of interest! */
			if(mode==GL_FILL) mode=GL_LINE;
			else mode=GL_FILL;
			glutPostRedisplay();
			break;

		default:

			/* Other keys are not important for us! */
			break;
	}			
}

/// This function draws the approximation of the <i>'Bullseye'</i> shape in the OpenGL window of interest by using the rendering settings, chosen by the user.
void draw()
{
	/* Here, the approximation of interest for the 'Bullseye' shape is not 'real', since it is the result of drawing the approximations of '5' 'Circle' shapes, placed at
	 * different z-depth. In this context, the scene is drawn by using the orthographic projection, such that all centers of the 'Circle' shapes are projected on the
	 * same point. Every 'Circle' shape of interest is approximated by a triangle fan of 'n' vertices (including its 'reference vertex'), and is drawn by using the 
	 * z-buffer (depth test) technique. Thus, the result will be a 'false' version of the 'Bullseye' shape, and will be always the same, despite the rendering order for
	 * the 'Circle' shapes of interest. */
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT,mode);
	glEnable(GL_DEPTH_TEST);
	glColor3f(0,0,0);
	drawDisc(95,0,0,10);
	glColor3f(1,1,0.5);
	drawDisc(20,0,0,80);
	glColor3f(0,0,1);
	drawDisc(60,0,0,40);
	glColor3f(0,1,0);
	drawDisc(80,0,0,20);
	glColor3f(1,0,0);
	drawDisc(40,0,0,60);
	glDisable(GL_DEPTH_TEST);
	glFlush();
	
	/* If we arrive here, then all is ok! */
	cout<<"\tThe 'Bullseye' shape is currently approximated by the ";
	if(mode==GL_FILL) cout<<"'filled versions' ";
	else cout<<"'wireframe versions' ";
	cout<<"of the triangles in every triangle fan with 'n="<<num_samples<<"' vertices (including the 'reference vertex'), which approximates any of its 'Circle' ";
	cout<<"shapes."<<endl;
	cout.flush();
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	num_samples=5;
	mode=GL_FILL;
	cout<<"\tAt the beginning, the 'Bullseye' shape is approximated by the ";
	if(mode==GL_FILL) cout<<"'filled versions' ";
	else cout<<"'wireframe versions' ";
	cout<<"of the triangles in every triangle fan with 'n="<<num_samples<<"' vertices (including the 'reference vertex', thus with the minimum number 'n' as possible),";
	cout<<" which "<<endl<<"\tapproximates any of its 'Circle' shapes."<<endl<<endl;
	cout.flush();
}

