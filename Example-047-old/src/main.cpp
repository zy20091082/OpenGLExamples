/*********************************************************************************************************************************************************************
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
 * main.cpp - the main function for the 'Example-047 (Old Mode)' Test.
 *********************************************************************************************************************************************************************/
 
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

/// The number <i>'p'</i> of the <i>'slices'</i> around the Z-axis, approximating the <i>'Ellipsoid'</i> shape.
/**
 * By construction, each hemisphere of the 'Ellipsoid' shape is approximated by a number 'p' of 'slices' around the 'z' axis (similar to the longitudinal lines). This
 * value contains the number 'p' of longitudinal lines, and it is initially set to 'p=3', which is the minimum number of longitudinal lines in each hemisphere of the
 * Ellipsoid' shape. It is increased and decreased by pressing, respectively, the 'P' and the 'p' keys.
 */
unsigned int long_slices_num=3;

/// The number <i>'q'</i> of the <i>'stacks'</i> around the Z-axis, approximating the <i>'Ellipsoid'</i> shape.
/**
 * By construction, each hemisphere of the 'Ellipsoid' shape is approximated by a number 'q' of 'stacks' around the 'z' axis (similar to the latitudinal lines). This 
 * value contains the number 'q' of latitudinal lines, and it is initially set to 'q=3', which is the minimum number of latitudinal lines in each hemisphere of the 
 * Ellipsoid' shape. It is increased and decreased by pressing, respectively, the 'Q' and the 'q' keys.
 */
unsigned int lat_slices_num=3;

/// The length <i>'a'</i> of the <i>'principal axis'</i> in the <i>'Ellipsoid'</i> shape, parallel to the <i>'x'</i>-axis.
/**
 * This value is the length 'a' of the 'principal axis' in the 'Ellipsoid' shape, parallel to the 'x'-axis, and it cannot be modified by the user. Here, 'a=2'.
 */
float radiusX=2.0;

/// The length <i>'b'</i> of the <i>'principal axis'</i> in the <i>'Ellipsoid'</i> shape, parallel to the <i>'y'</i>-axis.
/**
 * This value is the length 'b' of the 'principal axis' in the 'Ellipsoid' shape, parallel to the 'y'-axis, and it cannot be modified by the user. Here, 'b=3'.
 */
float radiusY=3.0;

/// The length <i>'c'</i> of the <i>'principal axis'</i> in the <i>'Ellipsoid'</i> shape, parallel to the <i>'z'</i>-axis.
/**
 * This value is the length 'c' of the 'principal axis' in the 'Ellipsoid' shape, parallel to the 'z'-axis, and it cannot be modified by the user. Here, 'c=5'.
 */
float radiusZ=5.0;

/// The rotation angle <i>'Rx'</i> for rotating the <i>Ellipsoid'</i> shape along the x-axis.
/**
 * This value indicates the angle 'Rx' for rotating the Ellipsoid' shape along the x-axis '[1,0,0]'. This rotation angle is increased by pressing the 'X' key, and
 * decreased by pressing the 'x' key.
 */
float Xangle=0.0;

/// The rotation angle <i>'Ry'</i> for rotating the <i>Ellipsoid'</i> shape along the y-axis.
/**
 * This value indicates the angle 'Ry' for rotating the Ellipsoid' shape along the y-axis '[0,1,0]'. This rotation angle is increased by pressing the 'Y' key, and
 * decreased by pressing the 'y' key.
 */
float Yangle=0.0;

/// The rotation angle <i>'Rz'</i> for rotating the <i>Ellipsoid'</i> shape along the z-axis.
/**
 * This value indicates the angle 'Rz' for rotating the Ellipsoid' shape along the z-axis '[0,0,1]'. This rotation angle is increased by pressing the 'Z' key, and
 * decreased by pressing the 'z' key.
 */
float Zangle=0.0;

/// The custom settings for rendering the quadrilaterals of interest in the quad grids, approximating the <i>Ellipsoid'</i> shape.
/**
 * The value of this flag may be one of the following values:
 *
 * -) the 'GL_LINE' value, used for rendering the 'wireframe versions' for the quadrilaterals of interest;
 * -) the 'GL_FILL' value, used for rendering the 'filled versions' for the quadrilaterals of interest.
 *
 * The user can choose what rendering mode must be used by pressing interactively the 'm' key.
 */
GLenum mode=GL_LINE;

/* Prototypes for all functions of interest! */
void initialize();
void manageKeys(unsigned char key, int x, int y);
void draw();
void resize(int w,int h);

/// The main function for the <i>'Example-047 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-047' Test, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws the 'Ellipsoid' shape in an OpenGL window. Intuitively, the 'Ellipsoid' shape is a surface, which may be obtained from the 'Sphere' shape by ";
	cout<<"deforming it through an affine transformation. Recall that the 'Sphere' shape"<<endl;
	cout<<"\tdescribes a perfectly round geometrical object in the 3D space, that is the surface of a completely round ball. Like the 'Circle' shape, which ";
	cout<<"geometrically is an object in the 2D space, the 'Sphere' shape is defined mathematically"<<endl;
	cout<<"\tas the set of 3D points, that are at the same distance 'R' from a given point '(xc,yc,zc)'. The distance 'R' is the 'radius' of the 'Sphere' shape, and ";
	cout<<"the point '(xc,yc,zc)' is its 'center'."<<endl<<endl;
	cout<<"\tHere, we consider the 'Ellipsoid' shape as a variant of the 'Sphere' shape of the 'center' '(xc,yc,zc)', and such that its symmetry axes are scaled ";
	cout<<"independently in order to have lengths 'a', 'b'', and 'c' (not necessarily the"<<endl;
	cout<<"\tsame). For the sake of the simplicity, the 'Ellipsoid' shape is the union of '2' symmetric hemi-ellipsoids with the same 'center' '(xc,yc,zc)' for any ";
	cout<<"'a,b,c>0', any 'r' in '[ 0, pi/2 ]', and any 's' in '[ 0, 2*pi ]'. The points of"<<endl;
	cout<<"\tthe first hemi-ellipsoid are expressed as follows:"<<endl<<endl;
	cout<<"\tx(r,s) = xc + a * cos(r) * cos(s), y(r,s) = yc + b * sin(r), z(r,s) = zc + c * cos(r) * sin(s)"<<endl<<endl<<"\tInstead, the points of the second ";
	cout<<"hemi-ellipsoid are expressed as follows:"<<endl<<endl;
	cout<<"\tx(r,s) = xc + a * cos(r) * cos(s), y(r,s) = yc - b * sin(r), z(r,s) = zc + c * cos(r) * sin(s)"<<endl<<endl;
	cout<<"\tHere, the hemi-ellipsoids of the 'Ellipsoid' shape (in 'blue' and in 'red', respectively) are both approximated by a quad grid, formed by 'p' 'slices' ";
	cout<<" around the Z-axis (similar to the longitudinal lines) and by 'q' 'stacks' along "<<endl;
	cout<<"\tthe Z-axis (similar to the latitudinal lines). Specifically, the 'filled' and the 'wireframe versions' of the elements in the quad grids are rendered by";
	cout<<" using the perspective projection."<<endl<<endl;
	cout<<"\tIn this test, the user cannot modify the lengths 'a', 'b'', and 'c', as well as the 'center' '(xc,yc,zc)', since they are fixed in advance. Instead, the ";
	cout<<"user can modify the numbers 'p' and 'q' of the longitudinal and the latitudinal"<<endl;
	cout<<"\tslices, respectively, as well as rotate the scene along the coordinate axes. In particular, the user can:"<<endl<<endl;
	cout<<"\t\t-) increase the number 'p' of the longitudinal slices by pressing the 'P' key;"<<endl;
	cout<<"\t\t-) decrease the number 'p' of the longitudinal slices by pressing the 'p' key;"<<endl;
	cout<<"\t\t-) increase the number 'q' of the latitudinal slices by pressing the 'Q' key;"<<endl;
	cout<<"\t\t-) decrease the number 'q' of the latitudinal slices by pressing the 'q' key;"<<endl;
	cout<<"\t\t-) increase the rotation angle 'Rx' along the 'x'-axis by pressing the 'X' key;"<<endl;
	cout<<"\t\t-) decrease the rotation angle 'Rx' along the 'x'-axis by pressing the 'x' key;"<<endl;
	cout<<"\t\t-) increase the rotation angle 'Ry' along the 'y'-axis by pressing the 'Y' key;"<<endl;
	cout<<"\t\t-) decrease the rotation angle 'Ry' along the 'y'-axis by pressing the 'y' key;"<<endl;
	cout<<"\t\t-) increase the rotation angle 'Rz' along the 'z'-axis by pressing the 'Z' key;"<<endl;
	cout<<"\t\t-) decrease the rotation angle 'Rz' along the 'z'-axis by pressing the 'z' key;"<<endl;
	cout<<"\t\t-) render either the 'wireframe' or the 'filled version' of the 'Ellipsoid' shape by pressing cyclically the 'm' key."<<endl<<endl<<"\tLikewise, the ";
	cout<<"window of interest can be closed by pressing the 'Esc' key."<<endl<<endl;
	cout<<"\tVERY IMPORTANT:"<<endl;
	cout<<"\tNote that the z-buffer technique and the normals are not exploited in this test, thus the rendering for the 'filled versions' of the elements in the quad";
	cout<<" grids may contain any error. This aspect goes beyond the scope of this test."<<endl<<endl;
	cout.flush();

	/* If we arrive here, we can draw the 'Ellipsoid' shape of interest by using the rendering settings, chosen by the user. */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-047' Test, based on the (Old Mode) OpenGL");
	glutReshapeFunc(resize);
	glutKeyboardFunc(manageKeys);
	glutDisplayFunc(draw);
	glewExperimental = GL_TRUE;
   	glewInit();
   	initialize(); 
	glutMainLoop();
	return EXIT_SUCCESS;
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	long_slices_num=3;
	lat_slices_num=3;
	radiusX=2.0;
	radiusY=3.0;
	radiusZ=5.0;
	mode=GL_LINE;
	Xangle=0.0;
	Yangle=0.0;
	Zangle=0.0;
	cout<<"\tAt the beginning, the ";
	if(mode==GL_LINE) cout<<"'wireframe version' ";
	else cout<<"'filled version' ";
	cout<<"of the 'Ellipsoid' shape is drawn by exploiting 'q="<<lat_slices_num<<"' latitudinal slices and 'p="<<long_slices_num<<"' longitudinal slices (thus, the ";
	cout<<"minimum numbers 'p' and 'q' as possible), as well as rotation angles"<<endl;
	cout<<"\t'Rx="<<Xangle<<"', "<<"'Ry="<<Yangle<<"', and 'Rz="<<Zangle<<"'."<<endl<<endl;
	cout.flush();
}

/// This function is the keyboard input processing routine for the OpenGL window of interest (ASCII keys).
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'p' - 'P' - 'x' - 'X' - 'y' - 'Y' - 'z' - 'Z' - 'Esc' - 'm' keys */
	switch (key)
	{
		case 'q':
	
			/* The key is 'q', thus we reduce the number 'q' of the latitudinal slices in the 'wireframe version' of the 'Ellipsoid' shape. */
			if(lat_slices_num>3) lat_slices_num=lat_slices_num-1;
			else
			{
				cout<<"\tThe minimum number 'q=3' of the latitudinal slices in the 'wireframe version' of the 'Ellipsoid' shape is reached, and it is not possible to";
				cout<<" decrease again this number."<<endl;
				cout.flush();
			}

			/* If we arrive here, then this case is finished! */
			glutPostRedisplay();
			break;
		
		case 'Q':
	
			/* The key is 'Q', thus we increase the number 'q' of the latitudinal slices in the 'wireframe version' of the 'Ellipsoid' shape. */
			lat_slices_num=lat_slices_num+1;
			glutPostRedisplay();
			break;

		case 'p':
	
			/* The key is 'p', thus we reduce the number 'p' of the longitudinal slices in the 'wireframe version' of the 'Ellipsoid' shape. */
			if(long_slices_num>3) long_slices_num=long_slices_num-1;
			else
			{
				cout<<"\tThe minimum number 'p=3' of the longitudinal slices in the 'wireframe version' of the 'Ellipsoid' shape is reached, and it is not possible to";
				cout<<" decrease again this number."<<endl;
				cout.flush();
			}

			/* If we arrive here, then this case is finished! */
			glutPostRedisplay();
			break;
		
		case 'P':
	
			/* The key is 'P', thus we increase the number 'p' of the longitudinal slices in the 'wireframe version' of the 'Ellipsoid' shape. */
			long_slices_num=long_slices_num+1;
			glutPostRedisplay();
			break;
		
		case 'x':
		
			/* The key is 'x', thus we decrease the rotation angle 'Rx' for rotating the 'wireframe version' of the 'Ellipsoid' shape along the X-axis. */
			Xangle -= 5.0;
			if(Xangle < 0.0) Xangle += 360.0;
	        glutPostRedisplay();
	        break;
		
		case 'X':
		
			/* The key is 'X', thus we increase the rotation angle 'Rx' for rotating the 'wireframe version' of the 'Ellipsoid' shape along the X-axis. */
	        Xangle += 5.0;
			if (Xangle > 360.0) Xangle -= 360.0;
	        glutPostRedisplay();
	        break;
		
		case 'y':
		
			/* The key is 'y', thus we decrease the rotation angle 'Ry' for rotating the 'wireframe version' of the 'Ellipsoid' shape along the Y-axis. */
			Yangle -= 5.0;
			if(Yangle < 0.0) Yangle += 360.0;
	        glutPostRedisplay();
	        break;
		
		case 'Y':
		
			/* The key is 'Y', thus we increase the rotation angle 'Ry' for rotating the 'wireframe version' of the 'Ellipsoid' shape along the Y-axis. */
	        Yangle += 5.0;
			if (Yangle > 360.0) Yangle -= 360.0;
	        glutPostRedisplay();
	        break;
		
		case 'z':
        
	        /* The key is 'z', thus we decrease the rotation angle 'Rz' for rotating the 'wireframe version' of the 'Ellipsoid' shape along the z-axis. */
			Zangle -= 5.0;
			if(Zangle < 0.0) Zangle += 360.0;
	        glutPostRedisplay();
	        break;
        
		case 'Z':
		
			/* The key is 'Z', thus we increase the rotation angle 'Rz' for rotating the 'wireframe version' of the 'Ellipsoid' shape along the z-axis. */
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
		
		case 'm':
		
			/* We change the rendering mode for the quadrilaterals in the 'Ellipsoid' shape of interest. */
			if(mode==GL_FILL) mode=GL_LINE;
			else if(mode==GL_LINE) mode=GL_FILL;
			glutPostRedisplay();
			break;

		default:
		
			/* Other keys are not important for us */
			break;
	}		
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

/// This function draws the <i>'Ellipsoid'</i> shape in the OpenGL window of interest by using the preferences, chosen by the user.
void draw()
{
	float delta_p,delta_q;

	/* Now, we draw the 'Ellipsoid' shape in the OpenGL window of interest by using the preferences, chosen by the user. */
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
   	glTranslatef(0.0, 0.0, -10.0);
   	glRotatef(Zangle, 0.0, 0.0, 1.0);
   	glRotatef(Yangle, 0.0, 1.0, 0.0);
  	glRotatef(Xangle, 1.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK,mode);
	glColor3f(0,0,1);
	glLineWidth(1);
	glPointSize(5);
	delta_p=(2.0*PI)/(long_slices_num);
	delta_q=PI/(2.0*lat_slices_num);
	for(unsigned int j=0;j<lat_slices_num;j++)
	{
		float psij=(float)j*delta_q,ppsi_j=(float)(j+1)*delta_q;
		
		/* Now, we consider the current latitudinal slice of the superior hemisphere of the 'Ellipsoid' shape as a quad strip to be drawn. */
		glColor3f(0,0,1);
		glBegin(GL_QUAD_STRIP);
		for(unsigned int i=0;i<=long_slices_num;i++)
		{
			float tetha_i=(float)i*delta_p;
			glVertex3f(radiusX*cos(ppsi_j)*cos(tetha_i),radiusY*sin(ppsi_j),radiusZ*cos(ppsi_j)*sin(tetha_i));
			glVertex3f(radiusX*cos(psij)*cos(tetha_i),radiusY*sin(psij),radiusZ*cos(psij)*sin(tetha_i));
		}
		
		/* Now, we consider the current latitudinal slice of the inferior hemisphere of the 'Ellipsoid' shape as a quad strip to be drawn. */
		glEnd();
		glColor3f(1,0,0);
		glBegin(GL_QUAD_STRIP);
		for(unsigned int i=0;i<=long_slices_num;i++)
		{
			float tetha_i=(float)i*delta_p;
			glVertex3f(radiusX*cos(ppsi_j)*cos(tetha_i),-radiusY*sin(ppsi_j),radiusZ*cos(ppsi_j)*sin(tetha_i));
			glVertex3f(radiusX*cos(psij)*cos(tetha_i),-radiusY*sin(psij),radiusZ*cos(psij)*sin(tetha_i));
		}
		
		/* Finally, we finalize the current latitudinal slice in the inferior hemisphere of the 'Ellipsoid' shape (a quad strip). */
		glEnd();
	}
	
	/* If we arrive here, we have finished! */
	glFlush();
	if(mode==GL_LINE) cout<<"\tThe 'wireframe version' ";
	else cout<<"\tThe 'filled version' ";
	cout<<"of the 'Ellipsoid' shape is currently drawn by exploiting 'q="<<lat_slices_num<<"' latitudinal slices and 'p="<<long_slices_num<<"' longitudinal slices, as";
	cout<<" well as rotation angles 'Rx="<<Xangle<<"', "<<"'Ry="<<Yangle<<"', and 'Rz="<<Zangle<<"'."<<endl;
	cout.flush();
}

