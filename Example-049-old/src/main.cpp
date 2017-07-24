/****************************************************************************************************************************************************************************************************************
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
 * main.cpp - the main function for the 'Example-049 (Old Mode)' Test.
 ****************************************************************************************************************************************************************************************************************/
 
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

/// The rotation angle <i>'Rx'</i> for rotating the <i>'Truncated Cone'</i> shape along the x-axis.
/**
 * This value indicates the angle 'Rx' for rotating the 'Truncated Cone' shape along the x-axis '[1,0,0]'. This rotation angle is increased by pressing the 'X' key, and
 * decreased by pressing the 'x' key.
 */
float Xangle=0.0;

/// The rotation angle <i>'Ry'</i> for rotating the <i>'Truncated Cone'</i> shape along the y-axis.
/**
 * This value indicates the angle 'Ry' for rotating the 'Truncated Cone' shape along the y-axis '[0,1,0]'. This rotation angle is increased by pressing the 'Y' key, and
 * decreased by pressing the 'y' key.
 */
float Yangle=0.0;

/// The rotation angle <i>'Rz'</i> for rotating the <i>'Truncated Cone'</i> shape along the z-axis.
/**
 * This value indicates the angle 'Rz' for rotating the 'Truncated Cone' shape along the z-axis '[0,0,1]'. This rotation angle is increased by pressing the 'Z' key, and
 * decreased by pressing the 'z' key.
 */
float Zangle=0.0;

/// The number <i>'h'</i> of the horizontal slices across the <i>'y'</i> axis, approximating the <i>'Truncated Cone'</i> shape.
/**
 * By construction, the <i>'Truncated Cone'</i> shape is approximated by a number 'h' of planes, parallel to the plane containing its basis, across the 'y' axis. This
 * value contains the number 'h' of horizontal slices, and it is initially set to 'h=3', which is the minimum number of horizonal planes, parallel to the basis of the
 * 'Truncated Cone' shape. It is increased and decreased by pressing, respectively, the 'H' and the 'h' keys.
 */
unsigned int height_slices_num=3;

/// The number <i>'r'</i> of the radial sectors in the basis of the <i>'Truncated Cone'</i> shape.
/**
 * By construction, the basis of the 'Truncated Cone' shape is approximated by a number 'r' of radial sectors, such that each point is connected to its apex. This value 
 * contains the number 'r' of radial sectors, and it is initially set to 'r=3', which is the minimum number of radial sectors in the basis of the 'Truncated Cone'
 * shape. It is increased and decreased by pressing, respectively, the 'R' and the 'r' keys.
 */
unsigned int radial_slices_num=3;

/* Prototypes for all functions of interest! */
void initialize();
void manageKeys(unsigned char key, int x, int y);
void draw();
void resize(int w,int h);

/// The main function for the <i>'Example-049 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-049' Test, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws the 'Truncated Cone' shape in an OpenGL window. Intuitively, this shape is a portion of any 'Cone' shape. This latter is a 3D geometric shape, that tapers smoothly from a 'basis' (not necessarily circular) to a point '(xv,yv,zv)', called the"<<endl;
	cout<<"\t'apex' of the 'Cone' shape. In other words, any 'Cone' shape is formed by a set of line segments, connecting its 'apex' to all points in the 'basis', such that its support plane does not contain the 'apex'. The boundary, formed by these lines, is called"<<endl;
	cout<<"\tthe 'lateral surface' of the 'Cone' shape. The 'axis' of the 'Cone' shape is the straight line, passing through its 'apex', about which 'Cone' shape may have a circular symmetry. Here, we limit our attention to a 'Right Circular Cone' shape, such that"<<endl;
	cout<<"\tits basis is circular, and its 'axis' passes through the 'basis' center at right angles to its support plane."<<endl<<endl;
	cout<<"\tIn this test, we consider the 'Truncated Cone' shape as any given 'Right Circular Cone' shape, cut off by a plane, and not including its 'apex'. For the sake of the simplicity, the 'axis' of the 'Cone' shape is the 'y'-axis, the support plane for the"<<endl;
	cout<<"\tcircular basis is the 'xz' plane, and the truncation plane is parallel to the 'xz' plane. The intersection between the truncation plane and the cone results into another circle, parallel to the first basis in the 'xz' plane. Broadly speaking, the"<<endl;
	cout<<"\t'Truncated Cone' shape may be considered as a prism with '2' circular basis of different radii."<<endl<<endl;
	cout<<"\tThe 'lateral surface' of the 'Truncated Cone' shape is approximated by a triangle grid, formed by 'r' radial sectors, and by 'h' horizontal slices around the 'y'-axis. In addition, each of '2' basis of the 'Truncated Cone' shape is approximated by a"<<endl;
	cout<<"\ttriangle fan, imposed by the 'r' radial sectors. By construction, it is possible to merge these grids into a unique triangle grid. Specifically, the 'wireframe versions' of the triangles in this triangle grid (in 'blue') are rendered by using the"<<endl;
	cout<<"\tperspective projection."<<endl<<endl;
	cout<<"\tIn this test, the user cannot modify the position of the truncation plane, the position, and the radii of '2' basis in the 'Truncated Cone' shape of interest, since they are fixed in advance. Instead, the user can modify the numbers 'r' and"<<endl;
	cout<<"\t'h' of the radial sectors and the horizontal slices, respectively, as well as rotate the scene along the coordinate axes. In particular the user can:"<<endl<<endl;
	cout<<"\t\t-) increase the number 'r' of the radial sectors by pressing the 'R' key;"<<endl;
	cout<<"\t\t-) decrease the number 'r' of the radial sectors by pressing the 'r' key;"<<endl;
	cout<<"\t\t-) increase the number 'h' of the horizontal slices by pressing the 'H' key;"<<endl;
	cout<<"\t\t-) decrease the number 'h' of the horizontal slices by pressing the 'h' key;"<<endl;
	cout<<"\t\t-) increase the rotation angle 'Rx' along the 'x'-axis by pressing the 'X' key;"<<endl;
	cout<<"\t\t-) decrease the rotation angle 'Rx' along the 'x'-axis by pressing the 'x' key;"<<endl;
	cout<<"\t\t-) increase the rotation angle 'Ry' along the 'y'-axis by pressing the 'Y' key;"<<endl;
	cout<<"\t\t-) decrease the rotation angle 'Ry' along the 'y'-axis by pressing the 'y' key;"<<endl;
	cout<<"\t\t-) increase the rotation angle 'Rz' along the 'z'-axis by pressing the 'Z' key;"<<endl;
	cout<<"\t\t-) decrease the rotation angle 'Rz' along the 'z'-axis by pressing the 'z' key."<<endl<<endl;
	cout<<"\tLikewise, the window of interest can be closed by pressing any among the 'Q', the 'q', and the 'Esc' keys."<<endl<<endl;
	cout.flush();	
	
	/* If we arrive here, we can draw the 'Truncated Cone' shape of interest by using the rendering settings, chosen by the user. */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-049' Test, based on the (Old Mode) OpenGL");
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
   	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	Xangle=0.0;
	Yangle=0.0;
	Zangle=0.0;
	height_slices_num=3;
	radial_slices_num=3;
	cout<<"\tAt the beginning, the 'wireframe version' of the 'Truncated Cone' shape is drawn by exploiting 'h="<<height_slices_num<<"' horizontal slices and 'r="<<radial_slices_num<<"' radial sectors (thus, the minimum numbers 'r' and 'h' as possible), as well as rotation angles 'Rx=";
	cout<<Xangle<<"', "<<"'Ry="<<Yangle<<"', and 'Rz="<<Zangle<<"'."<<endl<<endl;
	cout.flush();	
}

/// This function is the keyboard input processing routine for the OpenGL window of interest (ASCII keys).
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'r' - 'R' - 'h' - 'H' - 'x' - 'X' - 'y' - 'Y' - 'z' - 'Z' - 'Esc' - keys */
	switch (key)
	{
		case 'x':
		
			/* The key is 'x', thus we decrease the rotation angle 'Rx' for rotating the 'wireframe version' of the 'Truncated Cone' shape along the X-axis. */
			Xangle -= 5.0;
			if(Xangle < 0.0) Xangle += 360.0;
	        glutPostRedisplay();
	        break;
		
		case 'X':
		
			/* The key is 'X', thus we increase the rotation angle 'Rx' for rotating the 'wireframe version' of the 'Truncated Cone' shape along the X-axis. */
	        Xangle += 5.0;
			if (Xangle > 360.0) Xangle -= 360.0;
	        glutPostRedisplay();
	        break;
		
		case 'y':
		
			/* The key is 'y', thus we decrease the rotation angle 'Ry' for rotating the 'wireframe version' of the 'Truncated Cone' shape along the Y-axis. */
			Yangle -= 5.0;
			if(Yangle < 0.0) Yangle += 360.0;
	        glutPostRedisplay();
	        break;
		
		case 'Y':
		
			/* The key is 'Y', thus we increase the rotation angle 'Ry' for rotating the 'wireframe version' of the 'Truncated Cone' shape along the Y-axis. */
	        Yangle += 5.0;
			if (Yangle > 360.0) Yangle -= 360.0;
	        glutPostRedisplay();
	        break;
		
		case 'z':
        
	        /* The key is 'z', thus we decrease the rotation angle 'Rz' for rotating the 'wireframe version' of the 'Truncated Cone' shape along the z-axis. */
			Zangle -= 5.0;
			if(Zangle < 0.0) Zangle += 360.0;
	        glutPostRedisplay();
	        break;
        
		case 'Z':
		
			/* The key is 'Z', thus we increase the rotation angle 'Rz' for rotating the 'wireframe version' of the 'Truncated Cone' shape along the z-axis. */
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
		
		case 'h':
		
			/* The key is 'h', thus we reduce the number of the horizontal slices in the 'wireframe version' of the 'Truncated Cone' shape. */
			if(height_slices_num>3) height_slices_num=height_slices_num-1;
			else cout<<"\tThe minimum number 'h=3' of the horizontal slices in the 'wireframe version' of the 'Truncated Cone' shape is reached, and it is not possible to decrease again this number."<<endl;
			cout.flush();
			glutPostRedisplay();
			break;
		
		case 'r':
		
			/* The key is 'r', thus we reduce the number of the radial sectors in the 'wireframe version' of the 'Truncated Cone' shape. */
			if(radial_slices_num>3) radial_slices_num=radial_slices_num-1;
			else cout<<"\tThe minimum number 'h=3' of the radial sectors in the 'wireframe version' of the 'Truncated Cone' shape is reached, and it is not possible to decrease again this number."<<endl;
			cout.flush();
			glutPostRedisplay();
			break;
		
		case 'H':
		
			/* The key is 'H', thus we increase the number of the horizontal slices in the 'wireframe version' of the 'Truncated Cone' shape. */
			height_slices_num=height_slices_num+1;
			glutPostRedisplay();
			break;
			
		case 'R':
		
			/* The key is 'R', thus we increase the number of the radial sectors in the 'wireframe version' of the 'Truncated Cone' shape. */
			radial_slices_num=radial_slices_num+1;
			glutPostRedisplay();
			break;
		
		default:
		
			/* Other keys are not important for us */
			break;
	}
}

/// This function draws the <i>'Truncated Cone'</i> shape in the OpenGL window of interest by using the preferences, chosen by the user.
void draw()
{
	float delta_radial,delta_vert;

	/* Now, we draw the 'Truncated Cone' shape in the OpenGL window of interest by using the preferences, chosen by the user. */
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
   	glTranslatef(0.0, 0.0, -10.0);
   	glRotatef(Zangle, 0.0, 0.0, 1.0);
   	glRotatef(Yangle, 0.0, 1.0, 0.0);
  	glRotatef(Xangle, 1.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glColor3f(0,0,1);
	glLineWidth(1);
	glPointSize(5);
	delta_radial=(2.0*PI)/(radial_slices_num);
	delta_vert=3.0/height_slices_num;
	for(unsigned int h=0;h<height_slices_num;h++)
	{
		float hh=h*delta_vert;
		float radius_hh=2.0+(3.0-hh)*sqrt(2.0)*cos(PI/4.0);
		float hhp=(h+1)*delta_vert;
		float radius_hhp=2.0+(3.0-hhp)*sqrt(2.0)*cos(PI/4.0);
	
		/* Now, we complete the current horizontal slice (a triangle strip). */
		glBegin(GL_TRIANGLE_STRIP);
		for(unsigned int k=0;k<=radial_slices_num;k++)
		{
			glVertex3f(radius_hhp*cos(k*delta_radial),hhp,radius_hhp*sin(k*delta_radial));
			glVertex3f(radius_hh*cos(k*delta_radial),hh,radius_hh*sin(k*delta_radial));
		}
		
		/* Now, we finalize the current horizontal slice (a triangle strip). */
		glEnd();
	}
	
	/* If we arrive here, we draw the bottom and the top triangle fans! */
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0,0,0);
	for(unsigned int k=0;k<=radial_slices_num;k++) glVertex3f(5.0*cos(k*delta_radial),0,5.0*sin(k*delta_radial));
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0,3,0);
	for(unsigned int k=0;k<=radial_slices_num;k++) glVertex3f(2.0*cos(k*delta_radial),3,2.0*sin(k*delta_radial));
	glEnd();
	
	/* Finally, the scene is complete! */
	glFlush();
	cout<<"\tThe 'wireframe version' of the 'Truncated Cone' shape is currently drawn by exploiting 'h="<<height_slices_num<<"' horizontal slices and 'r="<<radial_slices_num<<"' radial sectors, as well as rotation angles 'Rx=";
	cout<<Xangle<<"', "<<"'Ry="<<Yangle<<"', and 'Rz="<<Zangle<<"'."<<endl;
	cout.flush();
}
