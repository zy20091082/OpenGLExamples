/*******************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 * 
 * Last update: September 2017
 *
 * main.cpp - the main function for the 'Example-030 (Old Mode)' Test.
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

/// The font for drawing the informative labels of interest.
/**
 * Each variant of the 'Circular Annulus' shape is accompanied by an informative label about what they represent. Each label is rendered by using the font, which is 
 * stored in this static and global variable.
 */
static long font = (long)GLUT_BITMAP_8_BY_13;

/// The number of the samples in all approximations of interest for the <i>'Circular Annulus'</i> shape.
/**
 * This global variable contains the number 'n' of the samples in all approximations of interest for the 'Circular Annulus' shape. Here, the value of 'n' is the number
 * 'n' of the vertices in '2' triangle fans of interest (including the 'reference vertex'), that approximate the 'Variant #0' and the 'Variant #1' of the 'Circular
 * Annulus' shape. Moreover, recall that 'm=n-1' is the number of the vertices pairs in the triangle strip, approximating the 'Variant #3' of the 'Circular Annulus'
 * shape. By construction, it is not possible to have 'n<5', thus to have 'm<4'. The number 'n' of the samples (i.e., the content of this global variable) can be
 * increased and decreased upon request by pressing, respectively, the '+' and the '-' keys.
 */
unsigned int num_samples=5;

/// The custom settings for rendering the triangles of interest in the triangle fans and the triangle strip to be drawn.
/**
 * The value of this global variable indicates the rendering type of the triangles in the triangle fans and the triangle strip to be drawn by following these 
 * conventions:
 *
 * 	-) the 'GL_LINE' value, used for rendering the 'wireframe versions' for all triangles in '2' triangle fans and in the triangle strip of interest;
 * 	-) the 'GL_FILL' value, used for rendering the 'filled versions' for all triangles in '2' triangle fans and in the triangle strip of interest.
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
void drawString(void *font,string s);

/// The main function for the <i>'Example-030 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a new window! */
	cout<<endl<<"\tThis is the 'Example-030' Test, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws '3' variants of the 'Circular Annulus' shape with 'inner' radius 'rI', 'outer' radius 'rE', and center '(xc,yc)' in an OpenGL window. The ";
	cout<<"'Circular Annulus' shape is defined as follows:"<<endl<<endl;
	cout<<"\t| rI * cos(t) | <= | x(t) - xc | <= | rE * cos(t) |, | rI * sin(t) | <= | y(t) - yc | <= | rE * sin(t) |"<<endl<<endl;
	cout<<"\tfor every 't' in '[-pi,pi]', and for any 'rI>0' and 'rE>0', such that 'rI<rE'."<<endl<<endl;
	cout<<"\tIn other words, it is formed by all points in the circular crown, bounded by 2 (concentric) 'Circle' shapes (disks) of the same center '(xc,yc)' and of ";
	cout<<"radius 'rI' and 'rE', respectively. The disk of radius 'rE' is the 'outer' disk,"<<endl;
	cout<<"\tand the disk of radius 'rI' is the 'inner' disk."<<endl<<endl;
	cout<<"\tSpecifically, this test draws the following variants of the 'Circular Annulus' shape:"<<endl<<endl;
	cout<<"\t\t0. the 'Variant #0' of the 'Circular Annulus' shape exploits '2' triangle fans, formed by 'n' vertices (including their 'reference vertices'). By ";
	cout<<"construction, it is not possible to have 'n<5'. Broadly speaking, '2' triangle"<<endl;
	cout<<"\t\t   fans describe, respectively, the 'inner' disk (in 'blue' ) and the 'outer' disk (in 'red') at different z-depths. These disks are described by the ";
	cout<<"'Circle' shape, and are drawn by using the orthographic projection, such"<<endl;
	cout<<"\t\t   that their 'reference vertices' are projected on the same point. Here, the 'outer' disk is rendered before than the 'inner' disk, and it is not ";
	cout<<"possible to modify their rendering order. Thus, the 'Variant #0' seems to"<<endl;
	cout<<"\t\t   coincide with the 'Circular Annulus' shape without being a 'real' approximation of this shape."<<endl<<endl;
	cout<<"\t\t1. The 'Variant #1' of the 'Circular Annulus' shape is defined in the same spirit of the 'Variant #0', but the z-buffer (depth test) technique is ";
	cout<<"exploited here for rendering '2' disks of interest. Also in this case, each of"<<endl;
	cout<<"\t\t   them is approximated by '2' triangle fans with 'n' vertices, including their 'reference vertices', and it is not possible to have 'n<5'. Thus, the ";
	cout<<"resulting scene does not depend on the rendering order of '2' disks, and"<<endl;
	cout<<"\t\t   is 'the same as' the 'Variant #0' of the 'Circular Annulus' shape."<<endl<<endl;
	cout<<"\t\t2. The 'Variant #2' of the 'Circular Annulus' shape is defined by only one triangle strip, formed by 'm=n-1' pairs of the corresponding vertices (thus ";
	cout<<"'2*n-2' vertices) in the 'inner' and the 'outer' circles, respectively."<<endl;
	cout<<"\t\t   These curves approximate the boundary of the 'Circular Annulus' shape. Broadly speaking, we consider the orthographic projections of all 'n' ";
	cout<<"vertices in the 'Variant #0' (or also in the 'Variant #1') of the 'Circular"<<endl;
	cout<<"\t\t   Annulus' shape, excepting their 'reference vertices'. By construction, it is not possible to have 'n<5', thus to have 'm<4'. In any case, note ";
	cout<<"that the triangle strip of interest is planar, and is a 'real' approximation"<<endl;
	cout<<"\t\t   of the 'Circular Annulus' shape."<<endl<<endl;
	cout<<"\tEach variant of the 'Circular Annulus' shape is accompanied by an explicative label. Thus, this test also shows how writing and rendering some text in ";
	cout<<"an OpenGL window."<<endl<<endl;
	cout<<"\tHere, the user cannot modify the position, the radii, and the centers for '3' variants of the 'Circular Annulus' shape, since they are fixed in advance. ";
	cout<<"Instead, the user can:"<<endl<<endl;
	cout<<"\t\t-) choose to render either the 'wireframe' or the 'filled versions' for all triangles of interest by pressing cyclically the ' ' (space) key;"<<endl;
	cout<<endl;
	cout<<"\t\t-) increase the number 'n' of the vertices in the triangle fans (including their 'reference vertices'), thus also the number 'm=n-1' of the vertices ";
	cout<<"pairs in the triangle strip, by pressing the '+' key. By construction, it"<<endl;
	cout<<"\t\t   is not possible to have 'n<5', thus to have 'm<4'."<<endl<<endl;
	cout<<"\t\t-) Decrease the number 'n' of the vertices in the triangle fans (including their 'reference vertices'), thus also the number 'm=n-1' of the vertices ";
	cout<<"pairs in the triangle strip, by pressing the '-' key. By construction, it"<<endl;
	cout<<"\t\t   is not possible to have 'n<5', thus to have 'm<4'."<<endl<<endl;
	cout<<"\tLikewise, the window of interest can be closed by pressing any among the 'Q', the 'q', and the 'Esc' keys."<<endl;
	cout<<"\t----------------------------------------------------------------------------------------------------------------------------------------------------------";
	cout<<"------------------------------------------------------------------------------"<<endl<<endl;
	cout.flush();

	/* If we arrive here, then we can draw all variants of the 'Circular Annulus' shape in the scene. */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE|GLUT_DEPTH);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-030' Test, based on the (Old Mode) OpenGL");
	glutReshapeFunc(resize);
	glutKeyboardFunc(manageKeys);
	glutDisplayFunc(draw);
	glewExperimental = GL_TRUE;
   	glewInit();
   	initialize(); 
	glutMainLoop();
	return EXIT_SUCCESS;
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
		
			/* The key is '+', thus we increase the number 'n' of the vertices in '2' triangle fans of interest (including the 'reference vertex'), that approximate the
			 * 'Variant #0' and the 'Variant #1' of the 'Circular Annulus' shape. Moreover, recall that 'm=n-1' is the number of the vertices pairs in the triangle
			 * strip, approximating the 'Variant #3' of the 'Circular Annulus' shape. By construction, it is not possible to have 'n<5', thus to have 'm<4'. */
			num_samples=num_samples+1;
			glutPostRedisplay();
			break;

		case '-':
		
			/* The key is '-', thus we decrease the number 'n' of the vertices (if possible) in '2' triangle fans of interest (including the 'reference vertex'), that
			 * approximate the 'Variant #0' and the 'Variant #1' of the 'Circular Annulus' shape. Moreover, recall that 'm=n-1' is the number of the vertices pairs in
			 * the triangle strip, approximating the 'Variant #3' of the 'Circular Annulus' shape. By construction, it is not possible to have 'n<5', thus to have
		 	 * 'm<4'. */
			if(num_samples>5) num_samples=num_samples-1;
			else
			{
				cout<<"\tThe minimum number 'n=5' of the vertices in '2' triangle fans of interest (including the 'reference vertex'), as well as the minimum number";
				cout<<"'m=4' of vertices pairs in the triangle strip of interest are reached, and it is not possible"<<endl;
				cout<<"\tto decrease again these numbers."<<endl;
				cout.flush();
			}

			/* If we arrive here, then this case is finished! */
			glutPostRedisplay();
			break;

		case ' ':
		
			/* The key is ' ' (space), thus we change the rendering mode for all triangles in '2' triangle fans and in the triangle strip of interest. */
			if(mode==GL_FILL) mode=GL_LINE;
			else mode=GL_FILL;
			glutPostRedisplay();
			break;

		default:

	    	/* Other keys are not important for us! */
    		break;
	}
}

/// This function draws a bitmap character string in the scene.
void drawString(void *font,string s) { for(string::iterator c=s.begin();c!=s.end();c++) glutBitmapCharacter(font, *c); }

/// This function updates the viewport for the scene when it is resized. */
void resize(int w, int h)
{
	/* We update the projection and the modeling matrices! */
	glViewport(0, 0, w, h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glOrtho(0,100,0,100,-1,1);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function draws a triangle fan, approximating a given <i>'Circle'</i> shape.
void drawDisc(float R,float X,float Y,float Z)
{
	/* Now, we draw a triangle fan with radius 'R' and center '(X,Y,Z)'. Here, we consider 'n' vertices, including the 'reference vertex'. */
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

/// This function draws '3' different approximations of the <i>'Circular Annulus'</i> shape in the OpenGL window of interest by using the rendering settings, chosen by the user.
void draw()
{
	float d=(2*PI)/(num_samples-1);

	/* Now, we draw the 'Variant #0' of the 'Circular Annulus' shape by using '2' triangle fans, formed by 'n' vertices (including their 'reference vertices'). Broadly
	 * speaking, they describe '2' disks (described by the 'Circle' shape) at different depths, that are drawn by using the orthographic projection, and such that their
	 * 'reference vertices' are projected on the same point. The 'outer' disk in 'red' is rendered before than the 'inner' disk in 'blue', and is not possible to modify
	 * their rendering order. Thus, the resulting scene seems to coincide with the 'Circular Annulus' shape, and is 'the same as' the 'Variant #1' of the 'Circular
	 * Annulus' shape. By construction, it is not possible to have 'n<5', thus to have 'm<4'. The value of 'n' (thus also the value of 'm') can be increased and
	 * decreased upon request by pressing, respectively, the '+' and the '-' keys. */
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT,mode);
	glColor3f(1,0,0);
	drawDisc(20,25,75,0);
	glColor3f(0,0,1);
	drawDisc(10,25,75,0);
	
	/* Now, we draw the 'Variant #1' of the 'Circular Annulus' shape. This variant is defined in the same spirit of the 'Variant #0', but the z-buffer (depth test)
	 * technique is exploited here for rendering '2' disks of interest (formed by 'n' vertices, including their 'reference vertices'). Thus, the resulting scene does
	 * not depend on the rendering order of '2' disks, and is 'the same as' the 'Variant #0' of the 'Circular Annulus' shape. By construction, it is not possible to
	 * have 'n<5', thus to have 'm<4'. The value of 'n' (thus also the value of 'm') can be increased and decreased upon request by pressing, respectively, the '+' and
	 * the '-' keys. */
	glEnable(GL_DEPTH_TEST);
	glColor3f(1,0,0);
	drawDisc(20,75,75,0);
	glColor3f(0,0,1);
	drawDisc(10,75,75,0.5);
	glDisable(GL_DEPTH_TEST);
	
	/* Now, we draw the 'Variant #2' of the 'Circular Annulus' shape by using only one triangle strip. Here, we consider 'm=n-1' pairs of the corresponding vertices
	 * (thus '2*n-2' vertices) in the 'inner' and the 'outer' circles, respectively. These curves approximate the boundary of the 'Circular Annulus' shape. Broadly
	 * speaking, we consider the orthographic projections of all vertices in the 'Variant #0' (or also in the 'Variant #1') of the 'Circular Annulus' shape, excepting
	 * their 'reference vertices'. In any case, note that the triangle strip of interest is planar, and is a 'real' approximation of the 'Circular Annulus' shape. By
	 * construction, it is not possible to have 'n<5', thus to have 'm<4'. The value of 'n' (thus also the value of 'n') can be increased and decreased upon request by
	 * pressing, respectively, the '+' and the '-' keys. */
	glColor3f(1,0,0);
	glBegin(GL_TRIANGLE_STRIP);
	for(int i=0;i<num_samples;i++)
	{
		float t=i*d;
		glVertex3f(50+10*cos(t),25+10*sin(t),0);
		glVertex3f(50+20*cos(t),25+20*sin(t),0);
	}

	/* If we arrive here, then we draw the informative labels for all variants of interest. */
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
    glRasterPos3f(5.0, 51.0, 0.0);
    drawString((void*)font,"Overlapping disks without");
    glRasterPos3f(8.0, 48.0, 0.0);
    drawString((void*)font,"the depth test buffer");
   	glRasterPos3f(55.0, 51.0, 0.0);
   	drawString((void*)font,"Overlapping disks with the");
   	glRasterPos3f(65.0,48.0,0.0);
   	drawString((void*)font,"depth test buffer");
   	glRasterPos3f(7,1,0);
   	drawString((void*)font,"A 'Circular Annulus' shape with only one triangle strip");

	/* If we arrive here, then all is ok! */
	glFlush();
	cout<<"\tAll variants of the 'Circular Annulus' shape are currently approximated by the ";
	if(mode==GL_FILL) cout<<"'filled versions' ";
	else cout<<"'wireframe versions' ";
	cout<<"of '2' triangle fans, each with 'n="<<num_samples<<"' vertices (including their 'reference vertices'), and of a triangle strip with 'm="<<(num_samples-1);
	cout<<"' vertices"<<endl<<"\tpairs (thus with '"<<2*(num_samples-1)<<"' vertices)."<<endl;
	cout.flush();
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	num_samples=5;
	mode=GL_FILL;
	cout<<"\tAt the beginning, all variants of the 'Circular Annulus' shape are approximated by the ";
	if(mode==GL_FILL) cout<<"'filled versions' ";
	else cout<<"'wireframe versions' ";
	cout<<"of '2' triangle fans, each with the minimum number 'n="<<num_samples<<"' of vertices (including their 'reference vertices'), and of a triangle"<<endl; 
	cout<<"\tstrip with the minimum number 'm="<<(num_samples-1)<<"' of vertices pairs (thus with '"<<2*(num_samples-1)<<"' vertices)."<<endl<<endl;
	cout.flush();
}

