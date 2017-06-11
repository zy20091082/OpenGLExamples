/*******************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 * 
 * Last update: June 2017
 *
 * This program is Free Software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.                                       
 *                                                                         
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License (http://www.gnu.org/licenses/gpl.txt) for more details.
 * 
 * main.cpp - the main function for the 'Example-044 (Old Mode)' Test.
 *******************************************************************************************************************************************************/

/* First, we must understand which platform we are using. */
#include <cstdlib>
#include <iostream>
#include <cmath>
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

/// The number <i>'n'</i> of the samples in all versions of interest for the <i>'Moon'</i> shape.
/**
 * It is initially set to 'n=5', which is the minimum number of the samples in all versions of interest. It is interactively modified by pressing the '+' and the '-' keys.
 */
int num_samples=5;

/// The setting for rendering all quadrilaterals in the quad strips, used for approximating all versions of interest of the <i>'Moon'</i> shape.
/**
 * The value of this flag may be one of the following values:
 *
 * -) the 'GL_LINE' value, used for rendering the 'wireframe versions' for all quadrilaterals in the quad strips of interest;
 * -) the 'GL_FILL' value, used for rendering the 'filled versions' for all quadrilaterals in the quad strips of interest.
 *
 * It is possible to cycle between these 2 renderings by pressing the 'r' (space) key.
 */
GLenum mode=GL_FILL;

/// The font for drawing the informative labels of interest.
/**
 * Each version of the 'Moon' shape is accompanied by an informative label about what they represent. Each label is rendered by using this font.
 */
static long font = (long)GLUT_BITMAP_8_BY_13;

/* Prototypes for all functions of interest! */
void initialize();
void manageKeys(unsigned char key, int x, int y);
void draw();
void resize(int w,int h);
void drawString(void *font,string s,GLfloat x,GLfloat y);

/// The main function for the <i>'Example-044 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a new window! */
	cout<<endl<<"\tThis is the 'Example-044' Example, based on the (Old Mode) OpenGL"<<endl;
	cout<<"\tIt draws 3 versions of the 'Moon' shape in an OpenGL window. Intuitively, the 'Moon' shape represents any lunar phase, namely the shape of any illuminated (sunlit) portion of the 'Moon' as seen by an observer on 'Earth'. In this case, "<<endl;
	cout<<"\twe limit our attention to the 'Waning Crescent', the 'Last Quarter', and the 'Waning Gibbous' lunar phases as they are seen in the northern hemisphere of the 'Earth'."<<endl<<endl;
	cout<<"\tEach lunar phase is bounded by 2 profiles, that are subdivided into 'n-1' horizontal stripes (in 'red') by using 'n' points. Every horizontal strip consists of a quadrilateral, which is defined by 2 pairs of adjacent vertices, belonging"<<endl;
	cout<<"\tto the profiles in the variant of the 'Moon' shape to be drawn. Thus, this latter is approximated by a quad strip, defined on 'n' pairs of corresponding vertices."<<endl<<endl;
	cout<<"\tEach variant of the 'Moon' shape is accompanied by an explicative label. Thus, this test also shows how writing and rendering some text in an OpenGL window."<<endl<<endl;
	cout<<"\tHere, the user cannot modify the position and the profiles for '3' versions of the 'Moon' shape, since they are fixed in advance. Instead, the user can:"<<endl<<endl;
	cout<<"\t\t-) increase the number 'n' of all vertices in the quad strips of interest by pressing the '+' key;"<<endl;
	cout<<"\t\t-) decrease the number 'n' of all vertices in the quad strips of interest by pressing the '-' key;"<<endl;
	cout<<"\t\t-) choose to render the 'wireframe' or the 'filled versions' for all quadrilaterals in the quad strips of interest by pressing cyclically the 'r' (space) key."<<endl<<endl;
	cout<<"\tLikewise, the window of interest can be closed by pressing any among the 'Q', the 'q', and the 'Esc' keys."<<endl<<endl;
	cout.flush();
	
	/* If we arrive here, we can draw 3 versions of the 'Moon' shape of interest by using the rendering settings, chosen by the user. */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(560,350);
	glutCreateWindow("The 'Example-044' Test, based on the (Old Mode) OpenGL");
	glutReshapeFunc(resize);
	glutKeyboardFunc(manageKeys);
	glutDisplayFunc(draw);
	glewExperimental = GL_TRUE;
   	glewInit();
   	initialize(); 
	glutMainLoop();
	return EXIT_SUCCESS;
}

/// This function draws a string (label) in the OpenGL scene of interest.
void drawString(void *font,string s,GLfloat x,GLfloat y)
{
	glRasterPos2f(x,y);
	for(string::iterator c=s.begin();c!=s.end();c++) glutBitmapCharacter(font, *c); 
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	num_samples=5;
	mode=GL_FILL;
	cout<<"\tAt the beginning, the versions of the 'Moon' shape to be drawn are approximated by the ";
	if(mode==GL_FILL) cout<<"'filled versions' ";
	else cout<<"'wireframe versions' ";
	cout<<"of all quadrilaterals in the quad strips, defined by 'n="<<num_samples<<"' vertices pairs (thus by the minimum number 'n' as possible of the vertices pairs)."<<endl<<endl;
	cout.flush();
}

/// This function updates the viewport for the scene when it is resized. */
void resize(int w, int h)
{
	/* We update the projection and the modeling matrices! */
	glViewport(0, 0, w, h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	gluOrtho2D(-180.0,150.0,-80.0,70.0);
	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '+' - '-' - 'r' keys. */
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
		
		/* The key is '+', thus we increase the number 'n' of the vertices pairs in the quad strips of interest! */
		num_samples=num_samples+1;
		glutPostRedisplay();
		break;
		
		case '-':
		
		/* The key is '-', thus we decrease the number 'n' of the vertices pairs in the quad strips of interest! */
		if(num_samples>5) num_samples=num_samples-1;
		else cout<<"\tThe minimum number 'n=5' of the vertices pairs in the quad strips of interest is reached, and it is not possible to decrease again this number."<<endl;
		cout.flush();
		glutPostRedisplay();
		break;
		
		case 'r':
		
		/* The key is 'r', thus we change the rendering mode! */
		if(mode==GL_FILL) mode=GL_LINE;
		else mode=GL_FILL;
		glutPostRedisplay();
		break;

		default:

    	/* Other keys are not important for us! */
    	break;
	}
}

/// This function draws 3 different versions of the <i>'Moon'</i> shape in the OpenGL window of interest by using the rendering settings, chosen by the user.
void draw()
{
	float d=PI/(num_samples);
	float d1=120.0/(num_samples);

	/* Now, we draw 3 different versions of the 'Moon' shape in the OpenGL window of interest by using the rendering settings, chosen by the user. */
	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK,mode);
	glColor3f(1,0,0);
	glLineWidth(1);
	
	/* Now, we draw the Version #0, describing the 'Waning crescent' lunar phase. */
	glBegin(GL_QUAD_STRIP);
	for(unsigned int k=0;k<=num_samples;k++)
	{
		glVertex2f(-110+60*cos(PI/2+k*d),60*sin(PI/2+k*d));
		glVertex2f(-110+30*cos(PI/2+k*d),60*sin(PI/2+k*d));
	}
	
	/* Now, we draw the Version #1, describing the 'Last Quarter' lunar phase. */
	glEnd();
	glBegin(GL_QUAD_STRIP);
	for(unsigned int k=0;k<=num_samples;k++)
	{
		glVertex2f(60*cos(PI/2+k*d),60*sin(PI/2+k*d));
		glVertex2f(0,60-k*d1);
	}
	
	/* Now, we draw the Version #2, describing the 'Waning Gibbous' lunar phase. */
	glEnd();
	glBegin(GL_QUAD_STRIP);
	for(unsigned int k=0;k<=num_samples;k++)
	{
		glVertex2f(110+60*cos(PI/2+k*d),60*sin(PI/2+k*d));
		glVertex2f(110-30*cos(PI/2+k*d),60*sin(PI/2+k*d));
	}
	
	/* If we arrive here, we can write the labels, and the scene will be complete! */
	glEnd();
	glColor3f(0,0,0);
	drawString((void*)font,"Waning Crescent",-170.0,-70.0);
	drawString((void*)font,"Last Quarter",-60.0,-70.0);
	drawString((void*)font,"Waning Gibbous",60.0,-70.0);
	glFlush();
	cout<<"\tThe versions of the 'Moon' shape to be drawn are currently approximated by the ";
	if(mode==GL_FILL) cout<<"'filled versions' ";
	else cout<<"'wireframe versions' ";
	cout<<"of all quadrilaterals in the quad strips, defined by 'n="<<num_samples<<"' vertices pairs."<<endl;
	cout.flush();
}
