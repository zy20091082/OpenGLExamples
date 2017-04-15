/*******************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 * 
 * Last update: April 2017
 *
 * This program is Free Software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.                                       
 *                                                                         
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License (http://www.gnu.org/licenses/gpl.txt) for more details.
 * 
 * main.cpp - the main function for the 'Example-030 (Old Mode)' example.
 *******************************************************************************************************************************************************/

/* First, we must understand which platform we are using. */
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <string>
#define PI 3.14159265358979324
using namespace std;
#ifdef __APPLE__

	/* We are using a MacOSX platform (Macintosh) */
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
 * Each variant of the 'Circular Annulus' shape is accompanied by an informative label about what they represent. This label is rendered by using this font.
 */
static long font = (long)GLUT_BITMAP_8_BY_13;

/// The number of the samples in all approximations of interest of the <i>'Circular Annulus'</i> shape.
/**
 * It is initially set to '5', which is the minimum number of the samples in all approximations of interest. It is interactively modified by pressing the '+' and the '-' keys.
 * Its meaning is different for every variant:
 *
 * -) in the variants #0 and #1, it is the number of vertices (including the center) for constructing the triangle fan of interest.
 * -) In the variant #2, it is the number of pairs, formed by the corresponding vertices in the external and the internal 'Circle' curves. These latter provides the boundary of the 'Circular Annulus' shape.
 */
unsigned int num_samples=5;

/// The setting for rendering all triangles in the triangle fans and in the triangle strip, used for approximating all variants of interest of the <i>'Circular Annulus'</i> shape.
/**
 * The value of this flag may be one of the following values:
 *
 * -) the 'GL_LINE' value, used for rendering the 'wireframe versions' for all triangles in the triangle fans and in the triangle strip of interest;
 * -) the 'GL_FILL' value, used for rendering the 'filled versions' for all triangles in the triangle fans and in the triangle strip of interest.
 *
 * It is possible to cycle between these two renderings by pressing the ' ' key.
 */
GLenum mode=GL_FILL;

/* Prototypes for all functions of interest! */
void initialize();
void manageKeys(unsigned char key, int x, int y);
void draw();
void resize(int w,int h);
void drawDisc(float R,float X,float Y,float Z);
void drawString(void *font,string s);

/// The main function for the <i>'Example-030 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a new window! */
	cout<<endl<<"\tThis is the 'Example-030' Example, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws 3 variants of the 'Circular Annulus' shape with internal radius 'rI', external radius 'rE', and center '(xc,yc)'. The 'Circular Annulus' shape is defined as follows:"<<endl<<endl;
	cout<<"\t| rI * cos(t) | <= | x(t) - xc | <= | rE * cos(t) |, | rI * sin(t) | <= | y(t) - yc | <= | rE * sin(t) |"<<endl<<endl;
	cout<<"\tfor every 't' in '[-pi,pi]', and for any 'rI'>0 and 'rE>0', such that 'rI<rE'.";
	cout<<"\tfor every 't' in '[-pi,pi]', and for any 'rI'>0 and 'rE>0', such that 'rI<rE'."<<endl<<endl;
	cout<<"\tIn other words, it is formed by all points, belonging to the intersection of two concentric 'Circle' shapes of center '(xc,yc)' and of radius 'rI' and 'rE', respectively."<<endl<<endl;
	cout<<"\tSpecifically, this test draws the following variants of the 'Circular Annulus' shape:"<<endl<<endl;
	cout<<"\t\t-) the first variant is not 'real', since it is the result of drawing the approximations of 2 collinear 'Circle' shapes of radius 'rI' (in 'blue') and 'rE' (in 'red'), respectively, at different z-depths."<<endl;
	cout<<"\t\t   The 'Circle' shape in 'red' is rendered before than the 'Circle' shape in 'blue'. The scene is drawn by using the orthographic projection, thus they seem to approximate the 'Circular Annulus' shape."<<endl;
	cout<<"\t\t   Both the 'Circle' shapes are approximated by a triangle fan of 'n' vertices (including the center)."<<endl<<endl;
	cout<<"\t\t-) The second variant is basically the same as the first variant, but the approximations of 2 'Circle' shapes (always at different z-depths) are drawn by using the z-buffer (depth test) technique. Thus, the "<<endl;
	cout<<"\t\t   result will be always the same, despite the rendering order of the 'Circle' shapes. Also in this case, both the 'Circle' shapes are approximated by a triangle fan of 'n' vertices (including the center)."<<endl<<endl;
	cout<<"\t\t-) The third variant is a real approximation of the 'Circular Annulus' shape through a triangle strip (in 'red'), defined over 'n' pairs of the corresponding vertices (including the center) between the"<<endl;
	cout<<"\t\t   approximations of the external and of the internal 'Circle' curves. These curves approximate the boundary of the 'Circular Annulus' shape."<<endl<<endl;
	cout<<"\tEach variant is accompanied by an explicative label. Thus, this test also shows how writing and rendering some text."<<endl<<endl;
	cout<<"\tHere, the user cannot modify the radius and the center for 3 variants of the 'Circular Annulus' shape, since they are fixed in advance. Instead, the user can:"<<endl<<endl;
	cout<<"\t\t-) increase the number 'n' of all vertices in the triangle fans and in the triangle strip of interest by pressing the '+' key;"<<endl;
	cout<<"\t\t-) decrease the number 'n' of all vertices in the triangle fans and in the triangle strip of interest by pressing the '-' key;"<<endl;
	cout<<"\t\t-) choose to render the 'wireframe' or the 'filled versions' for all triangles in the triangle fans and in the triangle strip of interest by pressing cyclically the ' ' (space) key."<<endl<<endl;
	cout<<"\tIt is possible to end this program by pressing one among the 'Q' - 'q' - 'Esc' keys."<<endl<<endl;
	cout.flush();
	
	/* If we arrive here, we can draw all variants of the 'Circular Annulus' shape in the scene. */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE|GLUT_DEPTH);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-030' Example, based on the (Old Mode) OpenGL");
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
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '+' - '-' - ' ' keys. */
	switch (key)
	{
		case 'q':
	
		/* The key is 'q', thus we can exit from this program. */
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case 'Q':
	
		/* The key is 'Q', thus we can exit from this program. */
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case 27:
	
		/* The key is 'Esc', thus we can exit from this program. */
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case '+':
		
		/* The key is '+', thus we increase the number of the vertices in 2 triangle fans and in the triangle strip of interest! */
		num_samples=num_samples+1;
		glutPostRedisplay();
		break;
		
		case '-':
		
		/* The key is '-', thus we decrease the number of the vertices (if possible) in 2 triangle fans and in the triangle strip of interest! */
		if(num_samples>5) num_samples=num_samples-1;
		else cout<<"\tThe minimum number 'n'=5 of vertices in 2 triangle fans and in the triangle strip of interest is reached, and it is not possible to decrease again this number."<<endl;
		cout.flush();
		glutPostRedisplay();
		break;
		
		case ' ':
		
		/* The key is ' ', thus we change the rendering mode! */
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
	/* Now, we draw a triangle fan with radius 'R' and center '(X,Y,Z)'. */
	float d=(2*PI)/(num_samples-1);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(X,Y,Z);
	for(int i=0;i<num_samples;i++)
	{
		float t=i*d;
		glVertex3f(X+R*cos(t),Y+R*sin(t),Z);
	}
	
	/* If we arrive here, all is ok. */
	glEnd();
}

/// This function draws 3 different approximations of the <i>'Circular Annulus'</i> shape in the OpenGL window of interest by using the rendering settings, chosen by the user.
void draw()
{
	float d=(2*PI)/(num_samples-1);

	/* Now, we draw the first (false) variant of the 'Circular Annulus' shape by using two overlapping disks (described by the 'Circle' shape). The external disk in 'red' is rendered before than the internal disk in 'blue'. These disks are collinear, but at 
	 * different depths. In any case, the result is the 'Circular Annulus' shape, since the orthographic projection is exploited. If we change the rendering order of the disks, then the result will be different. */
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT,mode);
	glColor3f(1,0,0);
	drawDisc(20,25,75,0);
	glColor3f(0,0,1);
	drawDisc(10,25,75,0);
	
	/* Now, we draw the second (false) variant of the 'Circular Annulus' shape. This variant is basically the same as the first variant, but the z-buffer technique is exploited, thus the result does not depend on their rendering order. */
	glEnable(GL_DEPTH_TEST);
	glColor3f(1,0,0);
	drawDisc(20,75,75,0);
	glColor3f(0,0,1);
	drawDisc(10,75,75,0.5);
	glDisable(GL_DEPTH_TEST);
	
	/* Now, we draw the third (true) variant of the 'Circular Annulus' shape by using only triangle strip. Here, we consider 'n' pairs of the corresponding vertices in the approximations of the internal and the external 'Circle' curves. These curves approximate 
	 * the boundary of the 'Circular Annulus' shape. */
	glColor3f(1,0,0);
	glBegin(GL_TRIANGLE_STRIP);
	for(int i=0;i<num_samples;i++)
	{
		float t=i*d;
		glVertex3f(50+10*cos(t),25+10*sin(t),0);
		glVertex3f(50+20*cos(t),25+20*sin(t),0);
	}
	
	/* If we arrive here, we draw the informative labels for all variants of interest. */
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
   	
   	/* If we arrive here, all is ok! */
	glFlush();
	cout<<"\tAll variants of the 'Circular Annulus' shape are approximated by the ";
	if(mode==GL_FILL) cout<<"'filled versions' ";
	else cout<<"'wireframe versions' ";
	cout<<"of several triangles in 2 triangle fans and a triangle strip with 'n'="<<num_samples<<" vertices."<<endl;
	cout.flush();
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	num_samples=5;
	mode=GL_FILL;
	cout<<"\tAt the beginning, the variants of the 'Circular Annulus' shape are currently approximated by the ";
	if(mode==GL_FILL) cout<<"'filled versions' ";
	else cout<<"'wireframe versions' ";
	cout<<"of all triangles in 2 triangle fans and a triangle strip with 'n'="<<num_samples<<" vertices (thus with the minimum"<<endl;
	cout<<"\tnumber 'n' of vertices as possible)."<<endl<<endl;
}

