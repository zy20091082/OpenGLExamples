/*******************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 * 
 * Last update: September 2017
 *
 * main.cpp - the main function for the 'Example-031 (Old Mode)' Test.
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

/// The number <i>'n'</i> of the samples in all approximations of interest for the <i>'Circular Annulus'</i> shape.
/**
 * This global variable contains the number 'n>4' of the samples in all approximations of interest for the 'Circular Annulus' shape. Here, the value of 'n>4' is the
 * number 'n>4' of the vertices in '2' triangle fans of interest (including the 'reference vertex'), that approximate the 'Variant #0' and the 'Variant #1' of the
 * 'Circular Annulus' shape. Moreover, recall that 'm=n-1' is the number of the vertices pairs in the triangle strip, approximating the 'Variant #3' of the 'Circular
 * Annulus' shape. By construction, it is not possible to have 'n<5', thus to have 'm<4'. The number 'n>4' of the samples (i.e., the content of this global variable)
 * can be increased and decreased upon request by pressing, respectively, the '+' and the '-' keys.
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

/// The custom settings for choosing the rendering order of the triangle fans in the <i>'Variant #0'</i> of the <i>'Circular Annulus'</i> shape.
/**
 * The value of this global variable indicates what rendering order of the triangle fans in the 'Variant #0' of the 'Circular Annulus' shape must be exploited. Recall
 * that the 'Variant #0' of interest is formed by '2' triangle fans with 'n>4' vertices (including the 'reference vertex'), that describe, respectively, the 'inner'
 * disk (in 'blue') and the 'outer' disk (in 'red') at different z-depth. Here, the rendering scene is modified by the rendering order of these disks, specified by the
 * value of this global variable as follows:
 *
 * 	-)  the value '0' enables the 'Configuration #0', where the 'inner' disk (in 'blue') is rendered after the 'outer' disk (in 'red'). Here, both the disks are visible.
 *	-)  The value '1' enables the 'Configuration #1', where the 'inner' disk (in 'blue') is rendered before the 'outer' disk (in 'red'). Here, only the 'outer' disk is
 * 		visible, and hides the other disk.
 *
 * The user can modify the rendering order of the disks (thus the resulting scene) by pressing cyclically the 'o' key.
 */
int odmode=0;

/* Prototypes for all functions of interest! */
void initialize();
void manageKeys(unsigned char key, int x, int y);
void draw();
void resize(int w,int h);
void drawDisc(float R,float X,float Y,float Z);
void drawString(void *font,string s);

/// The main function for the <i>'Example-31 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a new window! */
	cout<<endl<<"\tThis is the 'Example-031' Test, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws '3' variants of the 'Circular Annulus' shape with 'inner' radius 'rI', 'outer' radius 'rE', and center '(xc,yc)' in an OpenGL window. The ";
	cout<<"'Circular Annulus' shape is defined as follows:"<<endl<<endl;
	cout<<"\t| rI * cos(t) | <= | x(t) - xc | <= | rE * cos(t) |, | rI * sin(t) | <= | y(t) - yc | <= | rE * sin(t) |"<<endl<<endl;
	cout<<"\tfor every 't' in '[-pi,pi]', and for any 'rI>0' and 'rE>0', such that 'rI<rE'."<<endl<<endl;
	cout<<"\tIn other words, it is formed by all points in the circular crown, bounded by 2 (concentric) 'Circle' shapes (disks) of the same center '(xc,yc)' and of ";
	cout<<"radius 'rI' and 'rE', respectively. The disk of radius 'rE' is the 'outer' disk,"<<endl;
	cout<<"\tand the disk of radius 'rI' is the 'inner' disk."<<endl<<endl;
	cout<<"\tSpecifically, this test draws the following variants of the 'Circular Annulus' shape:"<<endl<<endl;
	cout<<"\t\t0. the 'Variant #0' of the 'Circular Annulus' shape exploits '2' triangle fans, formed by 'n>4' vertices (including their 'reference vertices'). By ";
	cout<<"construction, it is not possible to have 'n<5'. Broadly speaking, '2' triangle"<<endl;
	cout<<"\t\t   fans describe, respectively, the 'inner' disk (in 'blue') and the 'outer' disk (in 'red') at different z-depth. These disks are described by the ";
	cout<<"'Circle' shape, and are drawn by using the orthographic projection, such"<<endl;
	cout<<"\t\t   that their 'reference vertices' are projected on the same point. Here, the user can choose to modify the rendering order of the 'inner' and the ";
	cout<<"'outer' disks by obtaining the following configurations:"<<endl<<endl;
	cout<<"\t\t\t-) the 'Configuration #0', where the 'inner' disk is rendered after the 'outer' disk. Here, both the disks are visible."<<endl;
	cout<<"\t\t\t-) The 'Configuration #1', where the 'inner' disk is rendered before the 'outer' disk. Here, only the 'outer' disk is visible, and hides the other ";
	cout<<"disk."<<endl<<endl;
	cout<<"\t\tIt is clear that only the 'Configuration #0' seems to coincide with the 'Circular Annulus' shape. In any case, any of these configurations for the ";
	cout<<"'Variant #0' is not a 'real' approximation of the 'Circular Annulus' shape."<<endl<<endl;
	cout<<"\t\t1. The 'Variant #1' of the 'Circular Annulus' shape is defined in the same spirit of the 'Variant #0', but the z-buffer (depth test) technique is ";
	cout<<"exploited here for rendering '2' disks of interest. Also in this case, each of"<<endl;
	cout<<"\t\t   them is approximated by '2' triangle fans with 'n>4' vertices, including their 'reference vertices', and it is not possible to have 'n<5'. Thus, the ";
	cout<<"resulting scene does not depend on the rendering order of '2' disks, and"<<endl;
	cout<<"\t\t   is only 'the same as' the 'Configuration #0' for the 'Variant #0' of the 'Circular Annulus' shape."<<endl<<endl;
	cout<<"\t\t2. The 'Variant #2' of the 'Circular Annulus' shape is defined by only one triangle strip, formed by 'm=n-1' pairs of the corresponding vertices (thus ";
	cout<<"'2*n-2' vertices) in the 'inner' and the 'outer' circles, respectively."<<endl;
	cout<<"\t\t   These curves approximate the boundary of the 'Circular Annulus' shape. Broadly speaking, we consider the orthographic projections of all 'n>4' ";
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
	cout<<"\t\t-) choose to exploit any of '2' rendering orders for the triangles fans of interest (disks) in the 'Variant #0' of the 'Circular Annulus' shape by ";
	cout<<"pressing cyclically the 'o' key;"<<endl<<endl;
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
	glutCreateWindow("The 'Example-031' Test, based on the (Old Mode) OpenGL");
	glutReshapeFunc(resize);
	glutKeyboardFunc(manageKeys);
	glutDisplayFunc(draw);
	glewExperimental = GL_TRUE;
   	glewInit();
   	initialize(); 
	glutMainLoop();
	return EXIT_SUCCESS;
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
	/* Now, we draw a triangle fan with radius 'R' and center '(X,Y,Z)'. Here, we consider 'n>4' vertices, including the 'reference vertex'. */
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

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	num_samples=5;
	mode=GL_FILL;
	odmode=0;
	cout<<"\tAt the beginning, all variants of the 'Circular Annulus' shape are approximated by the ";
	if(mode==GL_FILL) cout<<"'filled versions' ";
	else cout<<"'wireframe versions' ";
	cout<<"of '2' triangle fans, each with the minimum number 'n="<<num_samples<<"' of vertices (including their 'reference vertices'), and of a triangle"<<endl; 
	cout<<"\tstrip with the minimum number 'm="<<(num_samples-1)<<"' of vertices pairs (thus with '"<<2*(num_samples-1)<<"' vertices). The 'Configuration ";
	cout<<"#"<<odmode<<"' for the 'Variant #0' of the 'Circular Annulus' shape is initially considered."<<endl<<endl;
	cout.flush();
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '+' - '-' - ' ' - 'o' (space) keys. */
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
		
			/* The key is '+', thus we increase the number 'n>4' of the vertices in '2' triangle fans of interest (including the 'reference vertex'), that approximate
			 * the 'Variant #0' and the 'Variant #1' of the 'Circular Annulus' shape. Moreover, recall that 'm=n-1' is the number of the vertices pairs in the triangle
			 * strip, approximating the 'Variant #3' of the 'Circular Annulus' shape. By construction, it is not possible to have 'n<5', thus to have 'm<4'. */
			num_samples=num_samples+1;
			glutPostRedisplay();
			break;

		case '-':
		
			/* The key is '-', thus we decrease the number 'n>4' of the vertices (if possible) in '2' triangle fans of interest (including the 'reference vertex'), that
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

		case 'o':

			/* The key is 'o', thus we change the rendering order for '2' triangle fans of interest in the 'Variant #0' of the 'Circular Annulus' shape. There are
			 * '2' possible configurations:
			 *
			 * 	-) the 'Configuration #0', where the 'inner' disk (in 'blue') is rendered after the 'outer' disk (in 'red'). Here, both the disks are visible.
			 *	-) The 'Configuration #1', where the 'inner' disk (in 'blue') is rendered before the 'outer' disk (in 'red'). Here, only the 'outer' disk is visible,
			 *	   and hides the other disk.
		 	 *
			 * It is clear that only the 'Configuration #0' seems to coincide with the 'Circular Annulus' shape. In any case, any of these configurations for the
		 	 * 'Variant #0' is not a 'real' approximation of the 'Circular Annulus' shape.
			 */
			odmode=( (odmode+1)%2);
			glutPostRedisplay();
			break;

		default:

	    	/* Other keys are not important for us! */
    		break;
	}
}

/// This function draws <i>'3'</i> different approximations of the <i>'Circular Annulus'</i> shape in the OpenGL window of interest by using the rendering settings, chosen by the user.
void draw()
{
	float d=(2*PI)/(num_samples-1);

	/* Now, we draw the 'Variant #0' of the 'Circular Annulus' shape by using '2' triangle fans, formed by 'n>4' vertices (including their 'reference vertices'). Broadly
	 * speaking, they describe '2' disks (described by the 'Circle' shape) at different depth, that are drawn by using the orthographic projection, and such that their
	 * 'reference vertices' are projected on the same point. By construction, it is not possible to have 'n<5'. The value of 'n>4' can be increased and decreased upon
	 * request by pressing, respectively, the '+' and the '-' keys.
	 * 
	 * Here, the user can choose to modify (by pressing cyclically the 'o' key) the rendering order of the 'inner' disk (in 'blue') and the 'outer' disk (in 'red'),
	 * obtaining the following configurations:
	 *
 	 * 	-) the 'Configuration #0', where the 'inner' disk is rendered after the 'outer' disk. Here, both the disks are visible.
	 * 	-) The 'Configuration #1', where the 'inner' disk is rendered before the 'outer' disk. Here, only the 'outer' disk is visible, and hides the other disk.
	 *
 	 * It is clear that only the 'Configuration #0' seems to coincide with the 'Circular Annulus' shape. In any case, any of these configurations for the 'Variant #0'
	 * is not a 'real' approximation of the 'Circular Annulus' shape.
 	 */
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT,mode);
	if(odmode==0)
	{
		/* The 'Configuration #0' is exploited, where the inner' disk (in 'blue') is rendered after the 'outer' disk (in 'red'). Here, both the disks are visible. */
		glColor3f(1,0,0);
		drawDisc(20,25,75,0);
		glColor3f(0,0,1);
		drawDisc(10,25,75,0);
	}
	else
	{
		/* The 'Configuration #1' is exploited, where the 'inner' disk (in 'blue') is rendered before the 'outer' disk (in 'red'). Here, only the 'outer' disk is
		 * visible, and hides the other disk. */
		glColor3f(0,0,1);
		drawDisc(10,25,75,0);
		glColor3f(1,0,0);
		drawDisc(20,25,75,0);
	}
	
	/* Now, we draw the 'Variant #1' of the 'Circular Annulus' shape. This variant is defined in the same spirit of the 'Variant #0', but the z-buffer (depth test)
	 * technique is exploited here for rendering '2' disks of interest (formed by 'n>4' vertices, including their 'reference vertices'). Thus, the resulting scene does
	 * not depend on the rendering order of '2' disks, and is only 'the same as' the 'Configuration #0' of the 'Variant #0' for the 'Circular Annulus' shape. By 
	 * construction, it is not possible to have 'n<5'. The value of 'n>4' can be increased and decreased upon request by pressing, respectively, the '+' and the '-'
	 * keys. */
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
	 * construction, it is not possible to have 'n<5', thus to have 'm<4'. The value of 'n>4' (thus also the value of 'm=n-1') can be increased and decreased upon
	 * request by pressing, respectively, the '+' and the '-' keys. */
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
	cout<<"' vertices"<<endl<<"\tpairs (thus with '"<<2*(num_samples-1)<<"' vertices). The 'Configuration #"<<odmode<<"' for the 'Variant #0' of the 'Circular Annulus'";
	cout<<" shape is currently considered."<<endl;
	cout.flush();
}

