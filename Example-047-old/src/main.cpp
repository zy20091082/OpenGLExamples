/****************************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 * 
 * Last update: September 2017
 *
 * main.cpp - the main function for the 'Example-047 (Old Mode)' Test.
 ****************************************************************************************************************************************************************/

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
 * By construction, the 'Ellipsoid' shape is approximated by a number 'p>2' of 'slices' around the 'z' axis (similar to the longitudinal lines). This global variable
 * contains the number 'p>2' of longitudinal lines, and it is initially set to 'p=3', which is the minimum number 'p>2' of longitudinal lines in the 'Ellipsoid' shape.
 * The value of 'p>2' is increased and decreased by pressing, respectively, the 'P' and the 'p' keys. By construction, it is not possible to have 'p<3' (as mentioned
 * above).
 */
unsigned int long_slices_num=3;

/// The number <i>'q'</i> of the <i>'stacks'</i> around the Z-axis, approximating the <i>'Ellipsoid'</i> shape.
/**
 * By construction, the 'Ellipsoid' shape is approximated by a number 'q>2' of 'stacks' around the 'z' axis (similar to the latitudinal lines). This global variable
 * contains the number 'q>2' of latitudinal lines, and it is initially set to 'q=3', which is the minimum number 'q>2' of latitudinal lines in the 'Ellipsoid' shape. The
 * value of 'q>2' is increased and decreased by pressing, respectively, the 'Q' and the 'q' keys. By construction, it is not possible to have 'q<3' (as mentioned above).
 */
unsigned int lat_slices_num=3;

/// The length <i>'a'</i> of the <i>'principal axis'</i>, parallel to the <i>'x'</i>-axis, for the <i>'Ellipsoid'</i> shape.
/**
 * This global variable contains the value of the length 'a' for the 'principal axis', parallel to the 'x'-axis, in the 'Ellipsoid' shape. Its value, fixed in advance as
 * 'a=2.0', cannot be modified by the user.
 */
float radiusX=2.0;

/// The length <i>'b'</i> of the <i>'principal axis'</i>, parallel to the <i>'y'</i>-axis, for the <i>'Ellipsoid'</i> shape.
/**
 * This global variable contains the value of the length 'b' for the 'principal axis', parallel to the 'y'-axis, in the 'Ellipsoid' shape. Its value, fixed in advance as
 * 'b=3.0', cannot be modified by the user.
 */
float radiusY=3.0;

/// The length <i>'c'</i> of the <i>'principal axis'</i>, parallel to the <i>'z'</i>-axis, for the <i>'Ellipsoid'</i> shape.
/**
 * This global variable contains the value of the length 'c' for the 'principal axis', parallel to the 'z'-axis, in the 'Ellipsoid' shape. Its value, fixed in advance as
 * 'c=5.0', cannot be modified by the user.
 */
float radiusZ=5.0;

/// The rotation angle <i>'Rx'</i> for rotating the <i>'Ellipsoid'</i> shape along the x-axis.
/**
 * This global variable contains the value of the angle 'Rx' for rotating the 'Ellipsoid' shape along the x-axis '[1,0,0]'. The rotation angle 'Rx' is increased by
 * pressing the 'X' key, and decreased by pressing the 'x' key. The value of the angle 'Rx' (i.e, the value of this global variable) is automatically limited within the
 * range '[0,360]'.
 */
float Xangle=0.0;

/// The rotation angle <i>'Ry'</i> for rotating the <i>'Ellipsoid'</i> shape along the y-axis.
/**
 * This global variable contains the value of the angle 'Ry' for rotating the 'Ellipsoid' shape along the y-axis '[0,1,0]'. The rotation angle 'Ry' is increased by
 * pressing the 'Y' key, and decreased by pressing the 'y' key. The value of the angle 'Ry' (i.e, the value of this global variable) is automatically limited within the
 * range '[0,360]'.
 */
float Yangle=0.0;

/// The rotation angle <i>'Rz'</i> for rotating the <i>'Ellipsoid'</i> shape along the z-axis.
/**
 * This global variable contains the value of the angle 'Rz' for rotating the 'Ellipsoid' shape along the z-axis '[0,0,1]'. The rotation angle 'Rz' is increased by
 * pressing the 'Z' key, and decreased by pressing the 'z' key. The value of the angle 'Rz' (i.e, the value of this global variable) is automatically limited within the
 * range '[0,360]'.
 */
float Zangle=0.0;

/// The custom settings for rendering the quadrilaterals of interest in the quad grids, approximating the <i>'Ellipsoid'</i> shape.
/**
 * The value of this global variable indicates the rendering type for the quadrilaterals of interest in the quad grids, approximating the 'Ellipsoid' shape, by 
 * following these conventions:
 *
 * 	-) the 'GL_LINE' value, used for rendering the 'wireframe versions' for the quadrilaterals of interest;
 * 	-) the 'GL_FILL' value, used for rendering the 'wireframe versions' for the quadrilaterals of interest.
 *
 * The user can choose between these rendering types by pressing cyclically the 'm' key.
 *
 * NOTE: the z-buffer technique and the normals are not exploited in this test, thus the rendering for the 'filled versions' of the quadrilaterals of interest may 		 
 * 		 contain several errors. This aspect goes beyond the scope of this test.
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
	cout<<"\tHere, the 'Ellipsoid' shape is a variant of the 'Sphere' shape of the 'center' '(xc,yc,zc)', such that its principal axes are scaled independently in ";
	cout<<"order to have lengths 'a', 'b'', and 'c' (not necessarily the same). For the"<<endl;
	cout<<"\tsake of the simplicity, the 'Ellipsoid' shape is the union of '2' symmetric hemi-ellipsoids with the same 'center' '(xc,yc,zc)' and for any 'a,b,c>0'. The";
 	cout<<" points of the first hemi-ellipsoid (known as the 'Hemi-Ellipsoid #0') are"<<endl;
	cout<<"\texpressed as follows:"<<endl<<endl;
	cout<<"\tx(r,s) = xc + a * cos(r) * cos(s), y(r,s) = yc + b * sin(r), z(r,s) = zc + c * cos(r) * sin(s)"<<endl<<endl<<"\tfor every 'r' in '[ 0, pi/2 ]', and every ";
	cout<<" 's' in '[ 0, 2*pi ]'. Instead, the points of the second hemi-ellipsoid (known as the 'Hemi-Ellipsoid #1') are expressed as follows:"<<endl<<endl;
	cout<<"\tx(r,s) = xc + a * cos(r) * cos(s), y(r,s) = yc - b * sin(r), z(r,s) = zc + c * cos(r) * sin(s)"<<endl<<endl;
	cout<<"\talways for every 'r' in '[ 0, pi/2 ]', and every 's' in '[ 0, 2*pi ]'."<<endl<<endl;
	cout<<"\tHere, each of '2' hemi-ellipsoids in the 'Ellipsoid' shape is approximated by a quad grid, formed by 'p>2' 'slices' around the Z-axis (similar to the ";
	cout<<"longitudinal lines) and by 'q>2' 'stacks' along the Z-axis (similar to the"<<endl;
	cout<<"\tlatitudinal lines). Specifically, the 'wireframe' and the 'filled' versions' of all quadrilaterals in the quad grids of interest (in 'blue' and in 'red', ";
	cout<<"respectively) are rendered upon request by using the perspective projection."<<endl<<endl;
	cout<<"\tIn this test, the user cannot modify the lengths 'a', 'b'', and 'c' for the principal axes, and the 'center' '(xc,yc,zc)' of the 'Ellipsoid' shape, since ";
	cout<<"they are fixed in advance. Instead, the user can modify the numbers 'p' and"<<endl;
	cout<<"\t'q' of the longitudinal and the latitudinal slices in each quad grid, respectively, as well as rotate the scene along the coordinate axes, and modify the";
	cout<<" rendering type for all quadrilaterals in the quad grids of interest. In"<<endl;
	cout<<"\tparticular, the user can:"<<endl<<endl;
	cout<<"\t\t-) choose to render either the 'wireframe' or the 'filled' versions' of all quadrilaterals in the quad grids of interest by pressing cyclically the ";
	cout<<"'m' key;"<<endl;
	cout<<"\t\t-) increase the number 'p' of the longitudinal slices by pressing the 'P' key. By construction, it is not possible to have 'p<3' in each quad grid.";
	cout<<endl;
	cout<<"\t\t-) Decrease the number 'p' of the longitudinal slices by pressing the 'p' key. By construction, it is not possible to have 'p<3' in each quad grid.";
	cout<<endl<<"\t\t-) Increase the number 'q' of the latitudinal slices by pressing the 'Q' key. By construction, it is not possible to have 'q<3' in each quad grid.";
	cout<<endl;
	cout<<"\t\t-) Decrease the number 'q' of the latitudinal slices by pressing the 'q' key. By construction, it is not possible to have 'q<3' in each quad grid.";
	cout<<endl;
	cout<<"\t\t-) Increase the rotation angle 'Rx' along the 'x'-axis by pressing the 'X' key. By construction, the value of 'Rx' is automatically limited within the";
	cout<<" '[0,360]' range."<<endl;
	cout<<"\t\t-) Decrease the rotation angle 'Rx' along the 'x'-axis by pressing the 'x' key. By construction, the value of 'Rx' is automatically limited within the";
	cout<<" '[0,360]' range."<<endl;
	cout<<"\t\t-) Increase the rotation angle 'Ry' along the 'y'-axis by pressing the 'Y' key. By construction, the value of 'Ry' is automatically limited within the";
	cout<<" '[0,360]' range."<<endl;
	cout<<"\t\t-) Decrease the rotation angle 'Ry' along the 'y'-axis by pressing the 'y' key. By construction, the value of 'Ry' is automatically limited within the";
	cout<<" '[0,360]' range."<<endl;
	cout<<"\t\t-) Increase the rotation angle 'Rz' along the 'z'-axis by pressing the 'Z' key. By construction, the value of 'Rz' is automatically limited within the";
	cout<<" '[0,360]' range."<<endl;
	cout<<"\t\t-) Decrease the rotation angle 'Rz' along the 'z'-axis by pressing the 'z' key. By construction, the value of 'Rz' is automatically limited within the";
	cout<<" '[0,360]' range."<<endl<<endl<<"\tLikewise, the window of interest can be closed by pressing the 'Esc' key."<<endl<<endl;
	cout<<"\t----------------------------------------------------------------------------------------------------------------------------------------------------------";
	cout<<"------------------------------------------------------------------------------"<<endl;
	cout<<"\tVERY IMPORTANT:"<<endl;
	cout<<"\tThe z-buffer technique and the normals are not exploited in this test, thus the rendering for the 'filled versions' of the quadrilaterals in the quad ";
	cout<<"grids of interest may contain several errors. This aspect goes beyond the scope of"<<endl;
	cout<<"\tthis test."<<endl;
	cout<<"\t----------------------------------------------------------------------------------------------------------------------------------------------------------";
	cout<<"------------------------------------------------------------------------------"<<endl<<endl;
	cout.flush();

	/* If we arrive here, then we can draw the 'Ellipsoid' shape of interest by using the rendering settings, chosen by the user. */
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

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'p' - 'P' - 'x' - 'X' - 'y' - 'Y' - 'z' - 'Z' - 'Esc' - 'm' keys */
	switch (key)
	{
		case 'Q':
	
			/* The key is 'Q', thus we increase the number 'q>2' of the latitudinal slices in the quad strip, approximating the 'wireframe version' of the 'Ellipsoid'
			 * shape. By construction, it is not possible to have 'q<3'. */
			lat_slices_num=lat_slices_num+1;
			glutPostRedisplay();
			break;

		case 'q':
	
			/* The key is 'q', thus we reduce the number 'q>2' of the latitudinal slices in the quad strip, approximating the 'wireframe version' of the 'Ellipsoid'
			 * shape. By construction, it is not possible to have 'q<3'. */
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

		case 'P':
	
			/* The key is 'P', thus we increase the number 'p>2' of the longitudinal slices in the quad strip, approximating the 'wireframe version' of the 'Ellipsoid'
			 * shape. By construction, it is not possible to have 'p<3'. */
			long_slices_num=long_slices_num+1;
			glutPostRedisplay();
			break;

		case 'p':
	
			/* The key is 'p', thus we reduce the number 'p>2' of the longitudinal slices in the quad strip, approximating the 'wireframe version' of the 'Ellipsoid'
			 * shape. By construction, it is not possible to have 'p<3'. */
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
		
		case 'x':
		
			/* The key is 'x', thus we decrease the rotation angle 'Rx' for rotating the quad strip, approximating the 'wireframe version' of the 'Ellipsoid' shape,
			 * along the X-axis. Here, the value of 'Rx' is automatically limited within the '[0,360]' range. */
			Xangle -= 5.0;
			if(Xangle < 0.0) Xangle += 360.0;
			glutPostRedisplay();
			break;

		case 'X':
		
			/* The key is 'X', thus we increase the rotation angle 'Rx' for rotating the quad strip, approximating the 'wireframe version' of the 'Ellipsoid' shape,
			 * along the X-axis. Here, the value of 'Rx' is automatically limited within the '[0,360]' range. */
	        Xangle += 5.0;
			if (Xangle > 360.0) Xangle -= 360.0;
	        glutPostRedisplay();
	        break;
		
		case 'y':
		
			/* The key is 'y', thus we decrease the rotation angle 'Ry' for rotating the quad strip, approximating the 'wireframe version' of the 'Ellipsoid' shape,
			 * along the Y-axis. Here, the value of 'Ry' is automatically limited within the '[0,360]' range. */
			Yangle -= 5.0;
			if(Yangle < 0.0) Yangle += 360.0;
			glutPostRedisplay();
			break;

		case 'Y':
		
			/* The key is 'Y', thus we increase the rotation angle 'Ry' for rotating the quad strip, approximating the 'wireframe version' of the 'Ellipsoid' shape,
			 * along the Y-axis. Here, the value of 'Ry' is automatically limited within the '[0,360]' range. */
			Yangle += 5.0;
			if (Yangle > 360.0) Yangle -= 360.0;
			glutPostRedisplay();
			break;

		case 'z':
        
	        /* The key is 'z', thus we decrease the rotation angle 'Rz' for rotating the quad strip, approximating the 'wireframe version' of the 'Ellipsoid' shape,
			 * along the Z-axis. Here, the value of 'Rz' is automatically limited within the '[0,360]' range. */
			Zangle -= 5.0;
			if(Zangle < 0.0) Zangle += 360.0;
			glutPostRedisplay();
	        break;
		
		case 'Z':
		
			/* The key is 'Z', thus we increase the rotation angle 'Rz' for rotating the quad strip, approximating the 'wireframe version' of the 'Ellipsoid' shape,
			 * along the Z-axis. Here, the value of 'Rz' is automatically limited within the '[0,360]' range. */
			Zangle += 5.0;
			if (Zangle > 360.0) Zangle -= 360.0;
			glutPostRedisplay();
			break;

		case 'm':
		
			/* We modify the rendering mode for the quadrilaterals in the 'Ellipsoid' shape of interest. */
			if(mode==GL_FILL) mode=GL_LINE;
			else if(mode==GL_LINE) mode=GL_FILL;
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
		
		/* Now, we consider the current latitudinal slice of the superior hemi-ellipsoid of the 'Ellipsoid' shape as a quad strip to be drawn. */
		glColor3f(0,0,1);
		glBegin(GL_QUAD_STRIP);
		for(unsigned int i=0;i<=long_slices_num;i++)
		{
			float tetha_i=(float)i*delta_p;
			glVertex3f(radiusX*cos(ppsi_j)*cos(tetha_i),radiusY*sin(ppsi_j),radiusZ*cos(ppsi_j)*sin(tetha_i));
			glVertex3f(radiusX*cos(psij)*cos(tetha_i),radiusY*sin(psij),radiusZ*cos(psij)*sin(tetha_i));
		}
		
		/* Now, we consider the current latitudinal slice of the inferior hemi-ellipsoid of the 'Ellipsoid' shape as a quad strip to be drawn. */
		glEnd();
		glColor3f(1,0,0);
		glBegin(GL_QUAD_STRIP);
		for(unsigned int i=0;i<=long_slices_num;i++)
		{
			float tetha_i=(float)i*delta_p;
			glVertex3f(radiusX*cos(ppsi_j)*cos(tetha_i),-radiusY*sin(ppsi_j),radiusZ*cos(ppsi_j)*sin(tetha_i));
			glVertex3f(radiusX*cos(psij)*cos(tetha_i),-radiusY*sin(psij),radiusZ*cos(psij)*sin(tetha_i));
		}
		
		/* Finally, we finalize the current latitudinal slice in the inferior hemi-ellipsoid of the 'Ellipsoid' shape (a quad strip). */
		glEnd();
	}
	
	/* If we arrive here, then we have finished! */
	glFlush();
	if(mode==GL_LINE) cout<<"\tThe 'wireframe version' ";
	else cout<<"\tThe 'filled version' ";
	cout<<"of the 'Ellipsoid' shape is currently drawn by exploiting 'q="<<lat_slices_num<<"' latitudinal slices and 'p="<<long_slices_num<<"' longitudinal slices, as";
	cout<<" well as rotation angles 'Rx="<<Xangle<<"', "<<"'Ry="<<Yangle<<"', and 'Rz="<<Zangle<<"'."<<endl;
	cout.flush();
}

