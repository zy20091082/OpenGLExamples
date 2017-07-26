/********************************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 * 
 * Last update: July 2017
 *
 * This program is Free Software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.                                       
 *                                                                         
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License (http://www.gnu.org/licenses/gpl.txt) for more details.
 * 
 * main.cpp - the main function for the 'Example-050 (Old Mode)' Test.
 ********************************************************************************************************************************************************************/
 
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

/// The rotation angle <i>'Rx'</i> for rotating the <i>'Playground Slide'</i> shape along the x-axis.
/**
 * This value indicates the angle 'Rx' for rotating the 'Playground Slide' shape along the x-axis '[1,0,0]'. This rotation angle is increased by pressing the 'X' key,
 * and decreased by pressing the 'x' key.
 */
float Xangle=0.0;

/// The rotation angle <i>'Ry'</i> for rotating the <i>'Playground Slide'</i> shape along the y-axis.
/**
 * This value indicates the angle 'Ry' for rotating the 'Playground Slide' shape along the y-axis '[0,1,0]'. This rotation angle is increased by pressing the 'Y' key,
 * and decreased by pressing the 'y' key.
 */
float Yangle=0.0;

/// The rotation angle <i>'Rz'</i> for rotating the <i>'Playground Slide'</i> shape along the z-axis.
/**
 * This value indicates the angle 'Rz' for rotating the 'Playground Slide' shape along the z-axis '[0,0,1]'. This rotation angle is increased by pressing the 'Z' key,
 * and decreased by pressing the 'z' key.
 */
float Zangle=0.0;

/// The number <i>'n'</i> of the samples, approximating the parabolic profile to be extruded in order to form the <i>'Playground Slide'</i> shape of interest.
/**
 * By construction, the 'Playground Slide' shape is defined by extruding a parabolic profile. This value contains the number 'n' of the samples, approximating the 
 * parabolic profile of interest. It is increased and decreased by pressing, respectively, the '+' and the '-' keys.
 */
unsigned int num_samples=3;

/* Prototypes for all functions of interest! */
void initialize();
void manageKeys(unsigned char key, int x, int y);
void draw();
void resize(int w,int h);
float evaluateSlide(float v);

/// The main function for the <i>'Example-050 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-050' Test, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws the 'Playground Slide' shape in an OpenGL window. Intuitively, this shape describes the classic playground slides, that can be found in parks, schools, playgrounds, and backyards. ";
	cout<<"A slide may be flat, or (more often) half cylindrical, in order to"<<endl;
	cout<<"\tprevent falls. Slides are usually constructed of plastic or metal, and they have a smooth surface, which is either straight or wavy. The user, typically a child, climbs to the top of the ";
	cout<<"slide via a ladder or stairs, sits down on the top of the slide, and"<<endl;
	cout<<"\tslides down the chute."<<endl<<endl;
	cout<<"\tIn this case, we try to model this physical object by considering a parabolic profile to be extruded. A parabolic profile is a portion of the 'Parabola' curve, defined as follows:"<<endl<<endl;
	cout<<"\tx(t) = t, y(t) = a * t ^ 2 + b * t + c"<<endl<<endl<<"\tfor any not null 'a', and for every 't'. The parameters 'a', 'b', and 'c' determine the properties of the 'Parabola' curve."<<endl<<endl;
	cout<<"\tHere, we limit our attention to every 't' in a given range in order to obtain a parabolic profile, which is extruded along the 'z'-axis in order to obtain the slide of interest (specifically ";
	cout<<"a curvilinear '2D' shape). In order to obtain a '3D' solid, we"<<endl;
	cout<<"\talso consider '2' lateral surfaces, bounded by the parabolic profiles and by the 'xz' coordinate plane, as well as '2' quadrilaterals, that are the frontward and the backward sides of ";
	cout<<"the solid, plus another quadrilateral, which is the bottom basis in the"<<endl;
	cout<<"\tthe 'xz' coordinate plane. Broadly speaking, the 'Playground Slide' shape is the '2D' shape, bounding this '3D' solid."<<endl<<endl;
	cout<<"\tThe parabolic profile of interest is approximated by a polyline with 'n' vertices and edges. This implies that each lateral side as well as the bottom basis of the 'Playgrond Slide' shape ";
	cout<<"can be approximated by a quad strip. Instead, the frontward and the"<<endl;
	cout<<"\tbackward sides of the 'Playground Slide' shape are simply quadrilaterals. By construction, it is possible to merge these grids into a unique quad grid. Specifically, the 'wireframe ";
	cout<<"versions' of the quadrilaterals in this quad grid (in 'blue') are rendered"<<endl<<"\tby using the perspective projection."<<endl<<endl;
	cout<<"\tIn this test, the user cannot modify the parameters of the parabolic profile to be extruded (like the parabola equation and the position), as well as the extrusion parameters for the ";
	cout<<"'Playground Slide' shape of interest, since they are fixed in advance."<<endl;
	cout<<"\tInstead, the user can modify the number 'n' of the samples in the parabolic profile, as well as rotate the scene along the coordinate axes. In particular the user can:"<<endl<<endl;
	cout<<"\t\t-) increase the number 'n' of the samples by pressing the '+' key;"<<endl;
	cout<<"\t\t-) decrease the number 'n' of the samples by pressing the '-' key;"<<endl;
	cout<<"\t\t-) increase the rotation angle 'Rx' along the 'x'-axis by pressing the 'X' key;"<<endl;
	cout<<"\t\t-) decrease the rotation angle 'Rx' along the 'x'-axis by pressing the 'x' key;"<<endl;
	cout<<"\t\t-) increase the rotation angle 'Ry' along the 'y'-axis by pressing the 'Y' key;"<<endl;
	cout<<"\t\t-) decrease the rotation angle 'Ry' along the 'y'-axis by pressing the 'y' key;"<<endl;
	cout<<"\t\t-) increase the rotation angle 'Rz' along the 'z'-axis by pressing the 'Z' key;"<<endl;
	cout<<"\t\t-) decrease the rotation angle 'Rz' along the 'z'-axis by pressing the 'z' key."<<endl<<endl;
	cout<<"\tLikewise, the window of interest can be closed by pressing any among the 'Q', the 'q', and the 'Esc' keys."<<endl<<endl;
	cout.flush();
	
	/* If we arrive here, we can draw the 'Playground Slide' shape of interest by using the rendering settings, chosen by the user. */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-050' Test, based on the (Old Mode) OpenGL");
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
	/* We update only the projection matrix! */
	glViewport(0, 0, w, h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glFrustum(-5.0, 5.0, -10.0, 10.0, 4.0, 100.0);
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	Xangle=10.0;
	Yangle=0.0;
	Zangle=0.0;
	num_samples=3;
	cout<<"\tAt the beginning, the 'wireframe version' of the 'Playground Slide' shape is drawn by exploiting 'n="<<num_samples<<"' samples in its parabolic profile, as well as rotation angles 'Rx=";
	cout<<Xangle<<"', "<<"'Ry="<<Yangle<<"', and 'Rz="<<Zangle<<"'."<<endl<<endl;
	cout.flush();
}

/// This function evaluates the parabolic profile for the <i>'Playground Slide'</i> shape at a given point.
float evaluateSlide(float v) { return ( 0.03875*pow(v,2)-1.225*v+10.0); }

/// This function is the keyboard input processing routine for the OpenGL window of interest (ASCII keys).
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the '+' - '-' - 'x' - 'X' - 'y' - 'Y' - 'z' - 'Z' - 'Esc' - 'q' - 'Q' keys */
	switch (key)
	{
		case 'x':
		
			/* The key is 'x', thus we decrease the rotation angle 'Rx' for rotating the 'wireframe version' of the 'Playground Slide' shape along the X-axis. */
			Xangle -= 5.0;
			if(Xangle < 0.0) Xangle += 360.0;
	        glutPostRedisplay();
	        break;
		
		case 'X':
		
			/* The key is 'X', thus we increase the rotation angle 'Rx' for rotating the 'wireframe version' of the 'Playground Slide' shape along the X-axis. */
	        Xangle += 5.0;
			if (Xangle > 360.0) Xangle -= 360.0;
	        glutPostRedisplay();
	        break;
		
		case 'y':
		
			/* The key is 'y', thus we decrease the rotation angle 'Ry' for rotating the 'wireframe version' of the 'Playground Slide' shape along the Y-axis. */
			Yangle -= 5.0;
			if(Yangle < 0.0) Yangle += 360.0;
	        glutPostRedisplay();
	        break;
		
		case 'Y':
		
			/* The key is 'Y', thus we increase the rotation angle 'Ry' for rotating the 'wireframe version' of the 'Playground Slide' shape along the Y-axis. */
	        Yangle += 5.0;
			if (Yangle > 360.0) Yangle -= 360.0;
	        glutPostRedisplay();
	        break;
		
		case 'z':
        
	        /* The key is 'z', thus we decrease the rotation angle 'Rz' for rotating the 'wireframe version' of the 'Playground Slide' shape along the z-axis. */
			Zangle -= 5.0;
			if(Zangle < 0.0) Zangle += 360.0;
	        glutPostRedisplay();
	        break;
        
		case 'Z':
		
			/* The key is 'Z', thus we increase the rotation angle 'Rz' for rotating the 'wireframe version' of the 'Playground Slide' shape along the z-axis. */
	        Zangle += 5.0;
			if (Zangle > 360.0) Zangle -= 360.0;
	        glutPostRedisplay();
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
			
		case '+':
			
			/* The key is '+', thus we increase the number of the samples in the parabolic profile in the 'Playground Slide' shape. */
			num_samples=num_samples+1;
			glutPostRedisplay();
			break;
		
		case '-':
			
			/* The key is '-', thus we reduce the number of the samples in the parabolic profile in the 'Playground Slide' shape. */
			if(num_samples>3) num_samples=num_samples-1;
			else cout<<"\tThe minimum number 'n=3' of the samples in the parabolic profile of the 'Playground Slide' shape is reached, and it is not possible to decrease again this number."<<endl;
			glutPostRedisplay();
			break;

		default:
		
			/* Other keys are not important for us */
			break;
	}
}

/// This function draws the <i>'Playground Slide'</i> shape in the OpenGL window of interest by using the preferences, chosen by the user.
void draw()
{
	float dv=40.0/(num_samples-1);

	/* Now, we draw the 'Playground Slide' shape in the OpenGL window of interest by using the preferences, chosen by the user. */
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
   	glTranslatef(0.0, 0.0, -30.0);
   	glRotatef(Zangle, 0.0, 0.0, 1.0);
   	glRotatef(Yangle, 0.0, 1.0, 0.0);
  	glRotatef(Xangle, 1.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glColor3f(0,0,1);
	glLineWidth(1);
	glPointSize(5);
	glBegin(GL_QUAD_STRIP);
	glVertex3f(5,0,-20);
	glVertex3f(-5,0,-20);
	for(unsigned int k=0;k<num_samples;k++)
	{
		float v=-20.0+k*dv;
		float p=evaluateSlide(v);
		glVertex3f(5,p,v);
		glVertex3f(-5,p,v);
	}
	
	/* If we arrive here, we complete the two vertical basis (front and back) for the 'Playground Slide' shape. */
	glVertex3f(5,0,20);
	glVertex3f(-5,0,20);
	glEnd();
	
	/* If we arrive here, we draw the lateral side #0 of the 'Playground Slide' shape. */
	glBegin(GL_QUAD_STRIP);
	for(unsigned int k=0;k<num_samples;k++)
	{
		float v=-20.0+k*dv;
		float p=evaluateSlide(v);
		glVertex3f(5,p,v);
		glVertex3f(5,0,v);
	}
	
	/* If we arrive here, we draw the lateral side #1 of the 'Playground Slide' shape. */
	glEnd();
	glBegin(GL_QUAD_STRIP);
	for(unsigned int k=0;k<num_samples;k++)
	{
		float v=-20.0+k*dv;
		float p=evaluateSlide(v);
		glVertex3f(-5,p,v);
		glVertex3f(-5,0,v);
	}
	
	/* Now, we add the bottom basis of the 'Playground Slide' shape. */
	glEnd();
	glBegin(GL_QUAD_STRIP);
	for(unsigned int k=0;k<num_samples;k++)
	{
		float v=-20.0+k*dv;
		glVertex3f(5,0,v);
		glVertex3f(-5,0,v);
	}

	/* Finally, the scene is complete */
	glEnd();
	glFlush();
	cout<<"\tThe current 'wireframe version' of the 'Playground Slide' shape is drawn by exploiting 'n="<<num_samples<<"' samples in its parabolic profile, as well as rotation angles 'Rx=";
	cout<<Xangle<<"', "<<"'Ry="<<Yangle<<"', and 'Rz="<<Zangle<<"'."<<endl;
	cout.flush();
}
