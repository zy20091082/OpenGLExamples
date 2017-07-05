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
 * main.cpp - the main function for the 'Example-046 (Old Mode)' Test.
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

/// The number <i>'p'</i> of the <i>'slices'</i> around the Z-axis, approximating the <i>'Dome'</i> shape.
/**
 * By construction, the 'Dome' shape is approximated by a number 'p' of 'slices' around the 'z' axis (similar to the longitudinal lines). This value contains the number 'p' of longitudinal lines, and it is initially set to 'p=3', which is the minimum number of longitudinal lines in the 'Dome'
 * shape. It is increased and decreased by pressing, respectively, the 'P' and the 'p' keys.
 */
unsigned int long_slices_num=3;

/// The number <i>'q'</i> of the <i>'stacks'</i> around the Z-axis, approximating the <i>'Dome'</i> shape.
/**
 * By construction, the 'Dome' shape is approximated by a number 'q' of 'stacks' around the 'z' axis (similar to the latitudinal lines). This value contains the number 'q' of latitudinal lines, and it is initially set to 'q=3', which is the minimum number of latitudinal lines in the 'Dome'
 * shape. It is increased and decreased by pressing, respectively, the 'Q' and the 'q' keys.
 */
unsigned int lat_slices_num=3;

/// The radius <i>'R'</i> of the <i>'Dome'</i> shape.
/**
 * This value is the radius 'R' of the 'Dome' shape, and it cannot be modified by the user. It is fixed in advance as 'R'=5, and it is the distance among the points of the 'Dome' shape and its center '(0,0,0)'.
 */
float radius=5.0;

/// The rotation angle <i>'Rx'</i> for rotating the <i>'Dome'</i> shape along the x-axis.
/**
 * This values indicates the angle 'Rx' for rotating the 'Dome' shape along the x-axis '[1,0,0]'. This rotation angle is increased by pressing the 'X' key, and decreased by pressing the 'x' key.
 */
float Xangle=0.0;

/// The rotation angle <i>'Ry'</i> for rotating the <i>'Dome'</i> shape along the y-axis.
/**
 * This values indicates the angle 'Ry' for rotating the 'Dome' shape along the y-axis '[0,1,0]'. This rotation angle is increased by pressing the 'Y' key, and decreased by pressing the 'y' key.
 */
float Yangle=0.0;

/// The rotation angle <i>'Rz'</i> for rotating the <i>'Dome'</i> shape along the z-axis.
/**
 * This values indicates the angle 'Rz' for rotating the 'Dome' shape along the z-axis '[0,0,1]'. This rotation angle is increased by pressing the 'Z' key, and decreased by pressing the 'z' key.
 */
float Zangle=0.0;

/* Prototypes for all functions of interest! */
void initialize();
void manageKeys(unsigned char key, int x, int y);
void draw();
void resize(int w,int h);

/// The main function for the <i>'Example-046 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-046' Test, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws the 'Dome' shape in an OpenGL window. Intuitively, the 'Dome' shape is a portion of any between '2' hemispheres of the 'Sphere' shape. Such hemisphere is known as the 'Hemisphere' shape. Broadly speaking, the 'Sphere' shape describes a"<<endl;
	cout<<"\tperfectly round geometrical object in the 3D space, that is the surface of a completely round ball. Like the 'Circle' shape, which geometrically is an object in the 2D space, the 'Sphere' shape is defined mathematically as the set of 3D"<<endl;
	cout<<"\tpoints, that are at the same distance 'R' from a given point '(xc,yc,zc)'. The distance 'R' is the 'radius' of the 'Sphere' shape, and the point '(xc,yc,zc)' is its 'center'."<<endl<<endl;
	cout<<"\tFor the sake of the simplicity, we consider the 'Dome' shape as a portion of the superior hemisphere in the 'Sphere' shape (thus of the 'Hemisphere' shape) of 'radius' 'R' and 'center' '(xc,yc)', such that its points are expressed as follows:"<<endl<<endl;
	cout<<"\tx(r,s) = xc + R * cos(r) * cos(s), y(r,s) = yc + R * sin(r), z(r,s) = zc + R * cos(r) * sin(s)"<<endl<<endl<<"\tfor any 'R>0', for any 'r' in '[ 0, pi/3 ]', and for any 's' in '[ 0, 2*pi ]'."<<endl<<endl;
	cout<<"\tHere, the 'Dome' shape is approximated by a quad grid, formed by 'p' 'slices' around the Z-axis (similar to the longitudinal lines) and by 'q' 'stacks' along the Z-axis (similar to the latitudinal lines). Specifically, the 'wireframe versions'"<<endl;
	cout<<"\tof the elements in the quad grid (in 'blue') are rendered by using the perspective projection."<<endl<<endl;
	cout<<"\tIn this test, the user cannot modify the 'radius' 'R', and the 'center' '(xc,yc,zc)', since they are fixed in advance. Instead, the user can modify the numbers 'p' and 'q' of the longitudinal and the latitudinal slices, respectively, as well as rotate"<<endl;
	cout<<"\tthe scene along the coordinate axes. In particular the user can:"<<endl<<endl;
	cout<<"\t\t-) increase the number 'p' of the longitudinal slices by pressing the 'P' key;"<<endl;
	cout<<"\t\t-) decrease the number 'p' of the longitudinal slices by pressing the 'p' key;"<<endl;
	cout<<"\t\t-) increase the number 'q' of the latitudinal slices by pressing the 'Q' key;"<<endl;
	cout<<"\t\t-) decrease the number 'q' of the latitudinal slices by pressing the 'q' key;"<<endl;
	cout<<"\t\t-) increase the rotation angle 'Rx' along the 'x'-axis by pressing the 'X' key;"<<endl;
	cout<<"\t\t-) decrease the rotation angle 'Rx' along the 'x'-axis by pressing the 'x' key;"<<endl;
	cout<<"\t\t-) increase the rotation angle 'Ry' along the 'y'-axis by pressing the 'Y' key;"<<endl;
	cout<<"\t\t-) decrease the rotation angle 'Ry' along the 'y'-axis by pressing the 'y' key;"<<endl;
	cout<<"\t\t-) increase the rotation angle 'Rz' along the 'z'-axis by pressing the 'Z' key;"<<endl;
	cout<<"\t\t-) decrease the rotation angle 'Rz' along the 'z'-axis by pressing the 'z' key."<<endl<<endl<<"\tLikewise, the window of interest can be closed by pressing the 'Esc' key."<<endl<<endl;
	cout.flush();

	/* If we arrive here, we can draw the 'Dome' shape of interest by using the rendering settings, chosen by the user. */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-046' Test, based on the (Old Mode) OpenGL");
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
	long_slices_num=3;
	lat_slices_num=3;
	radius=5.0;
	Xangle=0.0;
	Yangle=0.0;
	Zangle=0.0;
	cout<<"\tAt the beginning, the 'wireframe version' of the 'Dome' shape is drawn by exploiting 'q="<<lat_slices_num<<"' latitudinal slices and 'p="<<long_slices_num<<"' longitudinal slices (thus, the minimum numbers 'p' and 'q' as possible), as well as rotation angles 'Rx=";
	cout<<Xangle<<"', "<<"'Ry="<<Yangle<<"', and 'Rz="<<Zangle<<"'."<<endl<<endl;
	cout.flush();
}

/// This function is the keyboard input processing routine for the OpenGL window of interest (ASCII keys).
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'p' - 'P' - 'x' - 'X' - 'y' - 'Y' - 'z' - 'Z' - 'Esc' - keys */
	switch (key)
	{
		case 'q':
	
			/* The key is 'q', thus we reduce the number 'q' of the latitudinal slices in the 'wireframe version' of the 'Dome' shape. */
			if(lat_slices_num>3) lat_slices_num=lat_slices_num-1;
			else cout<<"\tThe minimum number 'q=3' of the latitudinal slices in the 'wireframe version' of the 'Dome' shape is reached, and it is not possible to decrease again this number."<<endl;
			cout.flush();
			glutPostRedisplay();
			break;
		
		case 'Q':
	
			/* The key is 'Q', thus we increase the number 'q' of the latitudinal slices in the 'wireframe version' of the 'Dome' shape. */
			lat_slices_num=lat_slices_num+1;
			glutPostRedisplay();
			break;

		case 'p':
	
			/* The key is 'p', thus we reduce the number 'p' of the longitudinal slices in the 'wireframe version' of the 'Dome' shape. */
			if(long_slices_num>3) long_slices_num=long_slices_num-1;
			else cout<<"\tThe minimum number 'p=3' of the longitudinal slices in the 'wireframe version' of the 'Dome' shape is reached, and it is not possible to decrease again this number."<<endl;
			cout.flush();
			glutPostRedisplay();
			break;
		
		case 'P':
	
			/* The key is 'P', thus we increase the number 'p' of the longitudinal slices in the 'wireframe version' of the 'Dome' shape. */
			long_slices_num=long_slices_num+1;
			glutPostRedisplay();
			break;
		
		case 'x':
		
			/* The key is 'x', thus we decrease the rotation angle 'Rx' for rotating the 'wireframe version' of the 'Dome' shape along the X-axis. */
			Xangle -= 5.0;
			if(Xangle < 0.0) Xangle += 360.0;
	        glutPostRedisplay();
	        break;
		
		case 'X':
		
			/* The key is 'X', thus we increase the rotation angle 'Rx' for rotating the 'wireframe version' of the 'Dome' shape along the X-axis. */
	        Xangle += 5.0;
			if (Xangle > 360.0) Xangle -= 360.0;
	        glutPostRedisplay();
	        break;
		
		case 'y':
		
			/* The key is 'y', thus we decrease the rotation angle 'Ry' for rotating the 'wireframe version' of the 'Dome' shape along the Y-axis. */
			Yangle -= 5.0;
			if(Yangle < 0.0) Yangle += 360.0;
	        glutPostRedisplay();
	        break;
		
		case 'Y':
		
			/* The key is 'Y', thus we increase the rotation angle 'Ry' for rotating the 'wireframe version' of the 'Dome' shape along the Y-axis. */
	        Yangle += 5.0;
			if (Yangle > 360.0) Yangle -= 360.0;
	        glutPostRedisplay();
	        break;
		
		case 'z':
        
	        /* The key is 'z', thus we decrease the rotation angle 'Rz' for rotating the 'wireframe version' of the 'Dome' shape along the z-axis. */
			Zangle -= 5.0;
			if(Zangle < 0.0) Zangle += 360.0;
	        glutPostRedisplay();
	        break;
        
		case 'Z':
		
			/* The key is 'Z', thus we increase the rotation angle 'Rz' for rotating the 'wireframe version' of the 'Dome' shape along the z-axis. */
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

		default:
		
			/* Other keys are not important for us */
			break;
	}		
}

/// This function draws the <i>'Dome'</i> shape in the OpenGL window of interest by using the preferences, chosen by the user.
void draw()
{
	float delta_p,delta_q;

	/* Now, we draw the 'Dome' shape in the OpenGL window of interest by using the preferences, chosen by the user. */
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
	delta_p=(2.0*PI)/(long_slices_num);
	delta_q=PI/(3.0*lat_slices_num);
	for(unsigned int j=0;j<lat_slices_num;j++)
	{
		/* Now, we consider the current latitudinal slice of the 'Dome' shape (a quad strip). */
		float psij=(float)j*delta_q,ppsi_j=(float)(j+1)*delta_q;
		glBegin(GL_QUAD_STRIP);
		for(unsigned int i=0;i<=long_slices_num;i++)
		{
			float tetha_i=(float)i*delta_p;
			glVertex3f(radius*cos(ppsi_j)*cos(tetha_i),radius*sin(ppsi_j),radius*cos(ppsi_j)*sin(tetha_i));
			glVertex3f(radius*cos(psij)*cos(tetha_i),radius*sin(psij),radius*cos(psij)*sin(tetha_i));
		}
		
		/* Now, we finalize the current latitudinal slice of the 'Dome' shape (a quad strip). */
		glEnd();
	}

	/* If we arrive here, we have finished! */
	glFlush();
	cout<<"\tThe 'wireframe version' of the 'Dome' shape is currently drawn by exploiting 'q="<<lat_slices_num<<"' latitudinal slices and 'p="<<long_slices_num<<"' longitudinal slices, as well as rotation angles 'Rx="<<Xangle<<"', "<<"'Ry="<<Yangle<<"', and 'Rz="<<Zangle<<"'."<<endl;
	cout.flush();
	cout.flush();
}
