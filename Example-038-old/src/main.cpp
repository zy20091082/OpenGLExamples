/*******************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 * 
 * Last update: May 2017
 *
 * This program is Free Software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.                                       
 *                                                                         
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License (http://www.gnu.org/licenses/gpl.txt) for more details.
 * 
 * main.cpp - the main function for the 'Example-038 (Old Mode)' Test.
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

/// The coordinates and the angles for the intersection points between the <i>'Circular Annulus'</i> shapes, forming the <i>'Eight'</i> shape of interest.
/**
 * By construction, the 'Circular Annulus' shapes, forming the 'Eight' shape of interest, have 2 intersection points '(xp1,yp1)' and '(xp2,yp2)', such that 'yp1=yp2' and 'xp2=-xp1', along the frontiers of their 'external' disks. These points are 
 * also determined by 2 elevation angles 'teta1' and 'teta2', such that 'teta2=pi/2+teta1'.
 */
float xp1,yp1,xp2,yp2,teta1,teta2;

/// The number of the samples in all approximations of interest for the <i>'Eight'</i> shape.
/**
 * This value, initially set to '5', is the number of the samples in all approximations of interest for the 'Eight' shape. Specifically, its meaning depends on the 
 *
 * -) it may be the number 'n' of the vertices (initially 'n=4') in the triangle fans, approximating the disks in the 'Eight' shape (i.e., in the variant #0 of the 'Eight' shape).
 * -) It may be the number 'k' of the vertices pairs (initially 'k=5') in the quad strips, approximating the 'Eight' shape (i.e., in the variant #1 of the 'Eight' shape).
 *
 * This value is interactively modified by pressing the '+' and the '-' keys.
 */
unsigned int num_samples=5;

/// This flag indicates what tessellation of the <i>'Eight'</i> shape must be drawn.
/**
 * The value of this flag may be one of the following values:
 *
 * -) 0: 	used for indicating the use of the variant #0 for the 'Eight' shape, formed by the union of 2 'Circular Annulus' shapes, partially overlapped. 
 * -) 1:	used for indicating the use of the variant #1 for the 'Eight' shape, formed by 2 quad strips.
 *
 * It is possible to cycle between these 2 tessellations by pressing the ' ' (space) key.
 */
int tessellation=0;

/// The setting for rendering all polygons in the triangle fans or in the quad strips, used for approximating all variants of interest of the <i>'Eight'</i> shape.
/**
 * The value of this flag may be one of the following values:
 *
 * -) the 'GL_LINE' value, used for rendering the 'wireframe versions' for all polygons in the triangle fans or in the quad strips of interest;
 * -) the 'GL_FILL' value, used for rendering the 'filled versions' for all polygons in the triangle fans or in the quad strips of interest.
 *
 * It is possible to cycle between these 2 renderings by pressing the 'w' key.
 */
GLenum mode=GL_FILL;

/* Prototypes for all functions of interest! */
void initialize();
void manageKeys(unsigned char key, int x, int y);
void draw();
void resize(int w,int h);
void drawDisc(float R,float X,float Y,float Z);

/// The main function for the <i>'Example-038 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-038' Test, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws 2 variants of the 'Eight' shape in an OpenGL window by using the rendering settings, chosen interactively by the user. Broadly speaking, the 'Eight' shape represents the '8' number. Intuitively, this shape can be seen as the union"<<endl;
	cout<<"\tof 2 'Circular Annulus' shapes, partially overlapped. Recall that any 'Circular Annulus' shape with 'internal' radius 'rI', 'external' radius 'rE', and center '(xc,yc)' is defined as follows:"<<endl<<endl;
	cout<<"\t| rI * cos(t) | <= | x(t) - xc | <= | rE * cos(t) |, | rI * sin(t) | <= | y(t) - yc | <= | rE * sin(t) |"<<endl<<endl;
	cout<<"\tfor every 't' in '[-pi,pi]', and for any 'rI>0' and 'rE>0', such that 'rI<rE'."<<endl<<endl<<"\tIn other words, any 'Circular Annulus' shape is formed by all points in the circular crown, bounded by 2 (concentric) 'Circle' shapes (disks) of"<<endl;
	cout<<"\tthe same center '(xc,yc)' and of radius 'rI' and 'rE', respectively. The disk of radius 'rE' is the 'external' disk, and the disk of radius 'rI' is the 'internal' disk."<<endl<<endl;
	cout<<"\tFor the sake of simplicity, the 'Circular Annulus' shape in the superior portion of the 'Eight' shape is indicated as the 'superior circular crown', while the 'Circular Annulus' shape in the inferior portion of the 'Eight' shape is indicated"<<endl;
	cout<<"\tas the 'inferior circular crown'."<<endl<<endl<<"\tSpecifically, this test draws the following variants of the 'Eight' shape:"<<endl<<endl;
	cout<<"\t\t0. the variant #0 is not 'real', since it is the result of drawing the approximations of 2 complete 'Circular Annulus' shapes, placed at different z-depths. Note that every 'Circular Annulus' shape is recursively rendered by drawing its"<<endl;
	cout<<"\t\t   'external' (in 'red') and 'internal' (in 'white') disks. The scene is drawn by using the orthographic projection, such that the centers for the 'Circle' shapes of interest are projected on the same point. Here, the z-buffer (depth test)"<<endl;
	cout<<"\t\t   technique is exploited. Thus, the result will be always the same, despite the rendering order of the 'Circle' shapes. Thus, they only seem to approximate the 'Circular Annulus' shape, and thus also the 'Eight' shape. In particular, there"<<endl;
	cout<<"\t\t   exists a portion of the 'Eight' shape, which is shared by the 'inferior' and by the 'superior circular crown'. All 'Circle' shapes of interest are approximated by a triangle fan of 'n' vertices."<<endl<<endl;
	cout<<"\t\t1. The variant #1 is a 'real' approximation of the 'Eight' shape, and is defined with respect to its horizontal symmetry. Here, the 'Eight' shape is decomposed into the 'superior' and the 'inferior' patches, that correspond (broadly) to its"<<endl;
	cout<<"\t\t   'superior' and 'inferior circular crowns' (but not completely). Every patch is recursively formed by 2 pieces. The first piece is the portion of the corresponding circular crown, which does not contain the intersection with other circular"<<endl;
	cout<<"\t\t   crown. In other words, it is a sector of the corresponding circular crown, and is approximated by a quad strip. This latter is defined on 'k' pairs of the corresponding vertices in the 'Circle' curves, that bound both the 'internal' and "<<endl;
	cout<<"\t\t   'external' disks of the corresponding circular crown. Other piece of the patch is a variant of the circular sector in the corresponding circular crown, which is bounded by the frontier of the 'internal' disk and by the horizontal symmetry"<<endl;
	cout<<"\t\t   axis. Also this piece is approximated by a quad strip, which is defined on 'k/4' pairs of the corresponding vertices in the horizontal symmetry axis and in the frontier of the 'internal' disk. For the sake of the simplicity, 2 vertices"<<endl;
	cout<<"\t\t   pairs are duplicated here, since they already belong to the first piece of the patch."<<endl<<endl;
	cout<<"\t\t   It is clear that both quad strips, approximating these pieces, can be merged into a unique quad strip (in 'red'), approximating each patch of the 'Eight' shape. This means that the variant #1 of the 'Eight' shape is formed by 2 quad strips"<<endl; 
	cout<<"\t\t   (both in 'red')."<<endl<<endl;
	cout<<"\tHere, the user cannot modify the radii and the centers for all disks in 2 variants of the 'Eight' shape, since they are fixed in advance. Instead, the user can:"<<endl<<endl;
	cout<<"\t\t-) increase the number 'n' of all vertices in the triangle fans, or the number 'k' of all vertices pairs in the quad strips of interest by pressing the '+' key;"<<endl;
	cout<<"\t\t-) decrease the number 'n' of all vertices in the triangle fans, or the number 'k' of all vertices pairs in the quad strips of interest by pressing the '-' key;"<<endl;
	cout<<"\t\t-) choose to render a specific variant of the 'Eight' shape by pressing cyclically the ' ' (space) key. The custom settings for rendering the polygons in the corresponding tessellation are set independently."<<endl;
	cout<<"\t\t-) Choose to render the 'wireframe' or the 'filled versions' of all triangles in the triangle fans or in the quad strips of interest by pressing cyclically the 'w' key. The variant of the 'Eight' shape to be drawn is chosen independently.";
	cout<<endl<<endl;
	cout<<"\tLikewise, the window of interest can be closed by pressing any among the 'Q', the 'q', and the 'Esc' keys."<<endl<<endl;
	cout.flush();
	
	/* If we arrive here, we can draw the 'Eight' shape of interest by using the rendering settings, chosen by the user. */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE|GLUT_DEPTH);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(450,765);
	glutCreateWindow("The 'Example-038' Test, based on the (Old Mode) OpenGL");
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
   	glOrtho(-60,60,-80,110,-10,0);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	num_samples=5;
	tessellation=0;
	mode=GL_FILL;
	yp1=15.0;
	yp2=15.0;
	xp1=sqrt(1275);
	xp2=-sqrt(1275);
	teta1=acos(xp1/50);
	teta2=-teta1;
	teta2=PI/2-teta2;
	cout<<"\tAt the beginning, ";
	if(mode==GL_FILL) cout<<"the 'filled versions' of all ";
	if(mode==GL_LINE) cout<<"the 'wireframe versions' of all ";
	if(tessellation==0) cout<<"triangles, belonging to the triangle fans (formed by the minimum number 'n="<<(num_samples-1)<<"' as possible of the vertices) in the variant #0 of the 'Eight' shape, are drawn."<<endl<<endl;
	if(tessellation==1) cout<<"quadrilaterals, belonging to the quad strips (formed by the minimum number 'k="<<num_samples<<"' as possible of the vertices pairs) in the variant #1 of the 'Eight' shape, are drawn."<<endl<<endl;
	cout.flush();
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '+' - '-' - 'w' - ' ' (space) keys. */
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
		
		case 'w':
		
		/* The key is 'w', thus we change the rendering mode to be used! */
		if(mode==GL_FILL) mode=GL_LINE;
		else mode=GL_FILL;
		glutPostRedisplay();
		break;
		
		case '+':
		
		/* The key is '+', thus we increase the number 'n' of the vertices in the triangle fans, or the number 'k' of the vertices pairs in the quad strips of interest! */
		num_samples=num_samples+1;
		glutPostRedisplay();
		break;
		
		case '-':
		
		/* The key is '-', thus we decrease (if it is possible) the number 'n' of the vertices in the triangle fans, or the number 'k' of the vertices pairs in the quad strips of interest! */
		if(num_samples>5) num_samples=num_samples-1;
		else
		{
			cout<<"\tThe minimum number ";
			if(tessellation==0) cout<<"'n=4' of the vertices in the triangle fans of interest ";
			else cout<<"'k=5' of the vertices pairs in the quad strips of interest ";
			cout<<"is reached, and it is not possible to decrease again this number."<<endl;
		}
		
		glutPostRedisplay();
		break;
		
		case ' ':
		
		/* The key is ' ' (space), thus we change the tessellation of the 'Eight' shape to be drawn! */
		tessellation=(tessellation+1)%2;
		glutPostRedisplay();
		break;
		
		default:

    	/* Other keys are not important for us! */
    	break;
	}
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

/// This function draws the tessellation of interest for the <i>'Eight'</i> shape in the main OpenGL window by using the rendering settings, choosen by the user.
void draw()
{
	unsigned int aaa;

	/* We draw the tessellation of interest for the 'Eight' shape in the main OpenGL window by using the rendering settings, choosen by the user. */
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK,mode);
	glColor3f(1,0,0);
	if(tessellation==0)
	{
		/* We draw four disks by using the depth test (z-buffer). */
		glEnable(GL_DEPTH_TEST);
		drawDisc(50,0,-20,5);
		drawDisc(50,0,50,3);
		glColor3f(1,1,1);
		drawDisc(20,0,-20,10);
		drawDisc(20,0,50,10);
		glDisable(GL_DEPTH_TEST);
		aaa=num_samples-1;
	}
	else
	{
		float e1=-teta1;
		float e2=PI+teta1;
		float d=fabs(e1-e2)/(num_samples-1);
		unsigned int num=(num_samples-1)/4;
		float dl=2*fabs(xp1)/(num);
		float d1=fabs(PI-2*teta1)/(num);
		aaa=num_samples+num-1;
		
		/* We draw the superior part of the 'Eight' shape. First, we draw the central portion. */
		glBegin(GL_QUAD_STRIP);
		glColor3f(1,0,0);
		for(unsigned int k=0;k<=num;k++)
		{
			glVertex3f(-xp1+k*dl,15,1);
			glVertex3f(20*cos(e2+k*d1),50+20*sin(e2+k*d1),1);
		}
		
		/* Then, we draw the remaining portion! */
		for(unsigned int k=0;k<num_samples;k++)
		{
			glVertex3f(50*cos(e1+k*d),50+50*sin(e1+k*d),1);
			glVertex3f(20*cos(e1+k*d),50+20*sin(e1+k*d),1);
		}
		
		/* Now, we draw the inferior part of the 'Eight' shape. First, we draw the central portion. */
		glEnd();
		glBegin(GL_QUAD_STRIP);
		for(unsigned int k=0;k<=num;k++)
		{
			glVertex3f(-xp1+k*dl,15,1);
			glVertex3f(20*cos(e2+k*d1),-20-20*sin(e2+k*d1),1);
		}
		
		/* Now, we draw the remaining portion! */
		for(unsigned int k=0;k<num_samples;k++)
		{
			glVertex3f(50*cos(e1+k*d),-20-50*sin(e1+k*d),1);
			glVertex3f(20*cos(e1+k*d),-20-20*sin(e1+k*d),1);
		}
		
		/* Now, the scene is complete. */
		glEnd();
	}
	
	/* If we arrive here, all is ok! */
	glFlush();
	if(mode==GL_FILL) cout<<"\tThe 'filled versions' of all ";
	if(mode==GL_LINE) cout<<"\tThe 'wireframe versions' of all ";
	if(tessellation==0) cout<<"triangles, belonging to the triangle fans (all formed by 'n="<<aaa<<"' vertices) in the variant #0 of the 'Eight' shape, are currently drawn."<<endl;
	if(tessellation==1) cout<<"quadrilaterals, belonging to the quad strips (all formed by 'k="<<aaa<<"' vertices pairs) in the variant #1 of the 'Eight' shape, are currently drawn."<<endl;
	cout.flush();
}
