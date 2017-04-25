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
 * main.cpp - the main function for the 'Example-031 (Old Mode)' example.
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
 * Each variant of the 'Circular Annulus' shape is accompanied by an informative label about what they represent. Each label is rendered by using this font.
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
 * It is possible to cycle between these 2 renderings by pressing the ' ' key.
 */
GLenum mode=GL_FILL;

/// The setting for choosing the rendering order of the triangle fans in the variant #0 of the <i>'Circular Annulus'</i> shape.
/**
 * In the variant #0 of the 'Circular Annulus' shape, 2 triangle fans, respectively in 'red' (the 'external disk') and 'blue' (the 'internal disk') at different z-depths are rendered without using the z-depth test. 
 * Thus, their rendering order is fundamental for drawing the scene. There are 2 possible cases:
 *
 * -) 'Configuration #0' (this flag is 0), where the 'external disk' is rendered before the 'internal disk'. In this case, all disks are visible.
 * -) 'Configuration #1' (this flag is 1), where the 'internal disk' is rendered before the 'external disk'. In this case, only the 'external disk' is visible.
 *
 * It is possible to cycle between these 2 rendering by pressing the 'o' key.
 */
int odmode=0;

/* Prototypes for all functions of interest! */
void initialize();
void manageKeys(unsigned char key, int x, int y);
void draw();
void resize(int w,int h);
void drawDisc(float R,float X,float Y,float Z);
void drawString(void *font,string s);

/// The main function for the <i>'Example-31 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a new window! */
	cout<<endl<<"\tThis is the 'Example-031' Example, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws 3 variants of the 'Circular Annulus' shape with internal radius 'rI', external radius 'rE', and center '(xc,yc)'. The 'Circular Annulus' shape is defined as follows:"<<endl<<endl;
	cout<<"\t| rI * cos(t) | <= | x(t) - xc | <= | rE * cos(t) |, | rI * sin(t) | <= | y(t) - yc | <= | rE * sin(t) |"<<endl<<endl;
	cout<<"\tfor every 't' in '[-pi,pi]', and for any 'rI'>0 and 'rE>0', such that 'rI<rE'."<<endl<<endl;
	cout<<"\tIn other words, it is formed by all points, belonging to the intersection of 2 concentric 'Circle' shapes (disks) of center '(xc,yc)' and of radius 'rI' and 'rE', respectively."<<endl<<endl;
	cout<<"\tSpecifically, this test draws the following variants of the 'Circular Annulus' shape:"<<endl<<endl;
	cout<<"\t\t-) the variant #0 is not 'real', since it is the result of drawing the approximations of 2 'Circle' shapes of radius 'rI' (in 'blue') and 'rE' (in 'red'), respectively, placed at different z-depths. The scene is drawn"<<endl;
	cout<<"\t\t   by using the orthographic projection, such that their centers are projected on the same point. In this context, the rendering order of the 'Circle' shapes is not fixed, and is modified upon request by the user. Hence,"<<endl;
	cout<<"\t\t   2 different configurations [ 'Configuration #0 ] [ 'Configuration #1' ] are possible, depending on which 'Circle' shape is rendered before. This means that the result is 'the same as' the 'Circular Annulus' shape only"<<endl;
	cout<<"\t\t   if the 'Circle' shape in 'red' is drawn before than the 'Circle' shape in 'blue' [ Configuration #0 ]. Both the 'Circle' shapes are approximated by a triangle fan of 'n' vertices (including the center)."<<endl<<endl;
	cout<<"\t\t-) The variant #1 is basically the same as the variant #0, but the approximations of 2 'Circle' shapes (always at different z-depths) are drawn by using the z-buffer (depth test) technique. Thus, the result"<<endl;
	cout<<"\t\t   will be always the same, despite the rendering order of the 'Circle' shapes. Also in this case, both the 'Circle' shapes are approximated by a triangle fan of 'n' vertices (including the center)."<<endl<<endl;
	cout<<"\t\t-) The variant #2 is a real approximation of the 'Circular Annulus' shape through a triangle strip (in 'red'), defined over 'n' pairs of the corresponding vertices (including the center) between the approximations"<<endl;
	cout<<"\t\t   of the external and of the internal 'Circle' curves, respectively. These curves approximate the boundary of the 'Circular Annulus' shape."<<endl<<endl;
	cout<<"\tEach variant is accompanied by an explicative label. Thus, this test also shows how writing and rendering some text."<<endl<<endl;
	cout<<"\tHere, the user cannot modify the radius and the center for 3 variants of the 'Circular Annulus' shape, since they are fixed in advance. Instead, the user can:"<<endl<<endl;
	cout<<"\t\t-) increase the number 'n' of all vertices in the triangle fans and of the vertices pairs in the triangle strip of interest by pressing the '+' key;"<<endl;
	cout<<"\t\t-) decrease the number 'n' of all vertices in the triangle fans and of the vertices pairs in the triangle strip of interest by pressing the '-' key;"<<endl;
	cout<<"\t\t-) choose the rendering order of the 'Circle' shapes in the variant #0 of the 'Circular Annulus' shape by pressing cyclically the 'o' key;"<<endl;
	cout<<"\t\t-) choose to render the 'wireframe' or the 'filled versions' for all triangles in the triangle fans and in the triangle strip of interest by pressing cyclically the ' ' (space) key."<<endl<<endl;
	cout<<"\tIt is possible to end this program by pressing one among the 'Q' - 'q' - 'Esc' keys."<<endl<<endl;
	cout.flush();
	
	/* If we arrive here, we can draw all variants of the 'Circular Annulus' shape in the scene. */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE|GLUT_DEPTH);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-031' Example, based on the (Old Mode) OpenGL");
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

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	num_samples=5;
	mode=GL_FILL;
	odmode=0;
	cout<<"\tAt the beginning, the variants of the 'Circular Annulus' shape are currently approximated by the ";
	if(mode==GL_FILL) cout<<"'filled versions' ";
	else cout<<"'wireframe versions' ";
	cout<<"of all triangles in 2 triangle fans with 'n'="<<num_samples<<" vertices and in a triangle strip with 'n'="<<num_samples<<" pairs of vertices"<<endl;
	cout<<"\t(thus with the minimum number 'n' of vertices and vertices pairs as possible). The 'Configuration #"<<odmode<<"' for the variant #0 of the 'Circular Annulus' shape is initially considered."<<endl<<endl;
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '+' - '-' - ' ' - 'o' keys. */
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
		else cout<<"\tThe minimum number 'n'=5 of vertices in 2 triangle fans and of vertices pairs in the triangle strip of interest is reached, and it is not possible to decrease again this number."<<endl;
		cout.flush();
		glutPostRedisplay();
		break;
		
		case ' ':
		
		/* The key is ' ', thus we change the rendering mode! */
		if(mode==GL_FILL) mode=GL_LINE;
		else mode=GL_FILL;
		glutPostRedisplay();
		break;
		
		case 'o':
		
		/* The key is 'o', thus we change the rendering order for the triangle fans of interest in the variant #0 of the 'Circular Annulus' shape. */
		odmode=( (odmode+1)%2);
		glutPostRedisplay();

		default:

    	/* Other keys are not important for us! */
    	break;
	}
}

/// This function draws 3 different approximations of the <i>'Circular Annulus'</i> shape in the OpenGL window of interest by using the rendering settings, chosen by the user.
void draw()
{
	float d=(2*PI)/(num_samples-1);
	
	/* Now, we draw the variant #0 of the 'Circular Annulus' shape by using 2 triangle fans (approximating by the 'Circle' shape). Broadly speaking, they describe 2 disk at different depths, that are drawn by using the orthographic projection,
	 * such that their centers are projected on the same point. Here, the result depends on the rendering order of the 'Circle' shapes, which can be modified upon request by the user. Hence, the result is not necessarily 'the same as' the 'Circular Annulus' 
	 * shape. */
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT,mode);
	if(odmode==0)
	{
		/* The 'Configuration #0' is chosen. */
		glColor3f(1,0,0);
		drawDisc(20,25,75,0);
		glColor3f(0,0,1);
		drawDisc(10,25,75,0);
	}
	else
	{
		/* The 'Configuration #1' is chosen. */
		glColor3f(0,0,1);
		drawDisc(10,25,75,0);
		glColor3f(1,0,0);
		drawDisc(20,25,75,0);
	}

	/* Now, we draw the variant #1 of the 'Circular Annulus' shape. This variant is basically 'the same as' the variant #0, but the z-buffer technique is exploited. Thus, the result does not depend on their rendering order, and is 'the same as'
	 * the 'Circular Annulus' shape. */
	glEnable(GL_DEPTH_TEST);
	glColor3f(1,0,0);
	drawDisc(20,75,75,0);
	glColor3f(0,0,1);
	drawDisc(10,75,75,0.5);
	glDisable(GL_DEPTH_TEST);
	
	/* Finally, we draw the variant #2 of the 'Circular Annulus' shape by using only triangle strip. Here, we consider 'n' pairs of the corresponding vertices in the approximations of the internal and the external 'Circle' curves. These curves 
	 * approximate the boundary of the 'Circular Annulus' shape. */
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
	cout<<"of several triangles in 2 triangle fans [ 'Configuration #"<<odmode<<"' ] and in a triangle strip with 'n'="<<num_samples<<" vertices and 'n'="<<num_samples<<" vertices pairs, respectively."<<endl;
	cout.flush();
}
