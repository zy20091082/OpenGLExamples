/********************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 * 
 * Last update: September 2017
 * 
 * main.cpp - the main function for the 'Example-045 (Old Mode)' Test.
 ********************************************************************************************************************************************************/

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

/// The number <i>'p'</i> of the <i>'slices'</i> around the Z-axis, approximating the <i>'Hemisphere'</i> shape.
/**
 * By construction, the 'Hemisphere' shape is approximated by a number 'p' of 'slices' around the 'z' axis (similar to the longitudinal lines). This global variable
 * contains the number 'p' of longitudinal lines, and it is initially set to 'p=3', which is the minimum number 'p' of longitudinal lines in the 'Hemisphere' shape. The
 * value of 'p' is increased and decreased by pressing, respectively, the 'P' and the 'p' keys. By construction, it is not possible to have 'p<3' (as mentioned above).
 */
unsigned int long_slices_num=3;

/// The number <i>'q'</i> of the <i>'stacks'</i> around the Z-axis, approximating the <i>'Hemisphere'</i> shape.
/**
 * By construction, the 'Hemisphere' shape is approximated by a number 'q' of 'stacks' around the 'z' axis (similar to the latitudinal lines). This global variable 
 * contains the number 'q' of latitudinal lines, and it is initially set to 'q=3', which is the minimum number 'q' of latitudinal lines in the 'Hemisphere' shape. The
 * value of 'q' is increased and decreased by pressing, respectively, the 'Q' and the 'q' keys. By construction, it is not possible to have 'q<3' (as mentioned above).
 */
unsigned int lat_slices_num=3;

/// The radius <i>'R'</i> of the <i>'Hemisphere'</i> shape.
/**
 * This global variable contains the value of the radius 'R' for the 'Hemisphere' shape, and it cannot be modified by the user. It is fixed in advance as 'R'=5, and it
 * is the distance among the points of the 'Hemisphere' shape and its center '(0,0,0)'.
 */
float radius=5.0;

/// The rotation angle <i>'Rx'</i> for rotating the <i>'Hemisphere'</i> shape along the x-axis.
/**
 * This global variable contains the value of the angle 'Rx' for rotating the 'Hemisphere' shape along the x-axis '[1,0,0]'. The rotation angle 'Rx' is increased by
 * pressing the 'X' key, and decreased by pressing the 'x' key. The value of the angle 'Rx' (i.e, the value of this global variable) is automatically limited within the
 * range '[0,360]'.
 */
float Xangle=0.0;

/// The rotation angle <i>'Ry'</i> for rotating the <i>'Hemisphere'</i> shape along the y-axis.
/**
 * This global variable contains the value of the angle 'Ry' for rotating the 'Hemisphere' shape along the y-axis '[0,1,0]'. The rotation angle 'Ry' is increased by
 * pressing the 'Y' key, and decreased by pressing the 'y' key. The value of the angle 'Ry' (i.e, the value of this global variable) is automatically limited within the
 * range '[0,360]'.
 */
float Yangle=0.0;

/// The rotation angle <i>'Rz'</i> for rotating the <i>'Hemisphere'</i> shape along the z-axis.
/**
 * This global variable contains the value of the angle 'Rz' for rotating the 'Hemisphere' shape along the z-axis '[0,0,1]'. The rotation angle 'Rz' is increased by
 * pressing the 'Z' key, and decreased by pressing the 'z' key. The value of the angle 'Rz' (i.e, the value of this global variable) is automatically limited within the
 * range '[0,360]'.
 */
float Zangle=0.0;

/* Prototypes for all functions of interest! */
void initialize();
void manageKeys(unsigned char key, int x, int y);
void draw();
void resize(int w,int h);

/// The main function for the <i>'Example-045 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-045' Test, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws the 'Hemisphere' shape in an OpenGL window. Intuitively, the 'Hemisphere' shape is basically any of '2' hemispheres in the 'Sphere' shape. This ";
	cout<<"latter describes a perfectly round geometrical object in the 3D space, that is"<<endl;
	cout<<"\tthe surface of a completely round ball. Like the 'Circle' shape, which geometrically is an object in the 2D space, the 'Sphere' shape is defined ";
	cout<<"mathematically as the set of 3D points, that are at the same distance 'R' from a given"<<endl;
	cout<<"\tpoint '(xc,yc,zc)'. The distance 'R' is the 'radius' of the 'Sphere' shape, and the point '(xc,yc,zc)' is its 'center'."<<endl<<endl;
	cout<<"\tFor the sake of the simplicity, we consider the 'Hemisphere' shape as the superior hemisphere in the 'Sphere' shape of 'radius' 'R' and 'center' ";
	cout<<"'(xc,yc,zc)', such that its points are expressed as follows:"<<endl<<endl;
	cout<<"\tx(r,s) = xc + R * cos(r) * cos(s), y(r,s) = yc + R * sin(r), z(r,s) = zc + R * cos(r) * sin(s)"<<endl<<endl<<"\tfor any 'R>0', for any 'r' in '[ 0, pi/2 ";
	cout<<"]', and for any 's' in '[ 0, 2*pi ]'."<<endl<<endl;
	cout<<"\tHere, the 'Hemisphere' shape is approximated by a quad grid, consisting of 'p' 'slices' around the Z-axis (similar to the longitudinal lines) and of";
	cout<<" 'q' 'stacks' along the Z-axis (similar to the latitudinal lines). By construction,"<<endl;
	cout<<"\t'p>=3' and 'q>=3'. Specifically, the 'wireframe versions' of all quadrilaterals in the quad grid of interest (in 'blue') are rendered by using the ";
	cout<<"perspective projection."<<endl<<endl;
	cout<<"\tIn this test, the user cannot modify the 'radius' 'R', and the 'center' '(xc,yc,zc)' of the 'Hemisphere' shape, since they are fixed in advance. Instead,";
	cout<<" the user can modify the numbers 'p' and 'q' of the longitudinal and the"<<endl;
	cout<<"\tlatitudinal slices, respectively, as well as rotate the scene along the coordinate axes. In particular, the user can:"<<endl<<endl;
	cout<<"\t\t-) increase the number 'p' of the longitudinal slices by pressing the 'P' key;"<<endl;
	cout<<"\t\t-) decrease the number 'p' of the longitudinal slices by pressing the 'p' key. By construction, it is not possible to have 'p<3'."<<endl;
	cout<<"\t\t-) Increase the number 'q' of the latitudinal slices by pressing the 'Q' key;"<<endl;
	cout<<"\t\t-) decrease the number 'q' of the latitudinal slices by pressing the 'q' key. By construction, it is not possible to have 'q<3'."<<endl;
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
	cout.flush();

	/* If we arrive here, then we can draw the 'Hemisphere' shape of interest by using the rendering settings, chosen by the user. */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-045' Test, based on the (Old Mode) OpenGL");
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
	cout<<"\tAt the beginning, the 'wireframe version' of the 'Hemisphere' shape is drawn by exploiting 'q="<<lat_slices_num<<"' latitudinal slices and 'p=";
	cout<<long_slices_num<<"' longitudinal slices (thus, the minimum numbers 'p' and 'q' as possible), as well as rotation angles"<<endl;
	cout<<"\t'Rx="<<Xangle<<"', "<<"'Ry="<<Yangle<<"', and 'Rz="<<Zangle<<"'."<<endl<<endl;
	cout.flush();
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'p' - 'P' - 'x' - 'X' - 'y' - 'Y' - 'z' - 'Z' - 'Esc' - keys */
	switch (key)
	{
		case 'Q':
	
			/* The key is 'Q', thus we increase the number 'q' of the latitudinal slices in the quad strip, approximating the 'wireframe version' of the 'Hemisphere'
			 * shape. By construction, it is not possible to have 'q<3'. */
			lat_slices_num=lat_slices_num+1;
			glutPostRedisplay();
			break;

		case 'q':
	
			/* The key is 'q', thus we reduce the number 'q' of the latitudinal slices in the quad strip, approximating the 'wireframe version' of the 'Hemisphere'
			 * shape. By construction, it is not possible to have 'q<3'. */
			if(lat_slices_num>3) lat_slices_num=lat_slices_num-1;
			else 
			{
				cout<<"\tThe minimum number 'q=3' of the latitudinal slices in the 'wireframe version' of the 'Hemisphere' shape is reached, and it is not possible to";
				cout<<" decrease again this number."<<endl;
				cout.flush();
			}

			/* If we arrive here, then this case is finished! */
			glutPostRedisplay();
			break;

		case 'P':
	
			/* The key is 'P', thus we increase the number 'p' of the longitudinal slices in the quad strip, approximating the 'wireframe version' of the 'Hemisphere'
			 * shape. By construction, it is not possible to have 'p<3'. */
			long_slices_num=long_slices_num+1;
			glutPostRedisplay();
			break;

		case 'p':
	
			/* The key is 'p', thus we reduce the number 'p' of the longitudinal slices in the quad strip, approximating the 'wireframe version' of the 'Hemisphere'
			 * shape. By construction, it is not possible to have 'p<3'. */
			if(long_slices_num>3) long_slices_num=long_slices_num-1;
			else
			{
				cout<<"\tThe minimum number 'p=3' of the longitudinal slices in the 'wireframe version' of the 'Hemisphere' shape is reached, and it is not possible to";
				cout<<" decrease again this number."<<endl;
				cout.flush();
			}

			/* If we arrive here, then this case is finished! */
			glutPostRedisplay();
			break;
		
		case 'x':
		
			/* The key is 'x', thus we decrease the rotation angle 'Rx' for rotating the quad strip, approximating the 'wireframe version' of the 'Hemisphere' shape,
			 * along the X-axis. Here, the value of 'Rx' is automatically limited within the '[0,360]' range. */
			Xangle -= 5.0;
			if(Xangle < 0.0) Xangle += 360.0;
			glutPostRedisplay();
			break;

		case 'X':
		
			/* The key is 'X', thus we increase the rotation angle 'Rx' for rotating the quad strip, approximating the 'wireframe version' of the 'Hemisphere' shape,
			 * along the X-axis. Here, the value of 'Rx' is automatically limited within the '[0,360]' range. */
	        Xangle += 5.0;
			if (Xangle > 360.0) Xangle -= 360.0;
	        glutPostRedisplay();
	        break;
		
		case 'y':
		
			/* The key is 'y', thus we decrease the rotation angle 'Ry' for rotating the quad strip, approximating the 'wireframe version' of the 'Hemisphere' shape,
			 * along the Y-axis. Here, the value of 'Ry' is automatically limited within the '[0,360]' range. */
			Yangle -= 5.0;
			if(Yangle < 0.0) Yangle += 360.0;
			glutPostRedisplay();
			break;

		case 'Y':
		
			/* The key is 'Y', thus we increase the rotation angle 'Ry' for rotating the quad strip, approximating the 'wireframe version' of the 'Hemisphere' shape,
			 * along the Y-axis. Here, the value of 'Ry' is automatically limited within the '[0,360]' range. */
			Yangle += 5.0;
			if (Yangle > 360.0) Yangle -= 360.0;
			glutPostRedisplay();
			break;

		case 'z':
        
	        /* The key is 'z', thus we decrease the rotation angle 'Rz' for rotating the quad strip, approximating the 'wireframe version' of the 'Hemisphere' shape,
			 * along the Z-axis. Here, the value of 'Rz' is automatically limited within the '[0,360]' range. */
			Zangle -= 5.0;
			if(Zangle < 0.0) Zangle += 360.0;
			glutPostRedisplay();
	        break;
		
		case 'Z':
		
			/* The key is 'Z', thus we increase the rotation angle 'Rz' for rotating the quad strip, approximating the 'wireframe version' of the 'Hemisphere' shape,
			 * along the Z-axis. Here, the value of 'Rz' is automatically limited within the '[0,360]' range. */
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

/// This function draws the <i>'Hemisphere'</i> shape in the OpenGL window of interest by using the preferences, chosen by the user.
void draw()
{
	float delta_p,delta_q;

	/* Now, we draw the 'Hemisphere' shape in the OpenGL window of interest by using the preferences, chosen by the user. */
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
	delta_q=PI/(2.0*lat_slices_num);
	for(unsigned int j=0;j<lat_slices_num;j++)
	{
		/* Now, we consider the current latitudinal slice of the 'Hemisphere' shape as a quad strip to be drawn. */
		float psij=(float)j*delta_q,ppsi_j=(float)(j+1)*delta_q;
		glBegin(GL_QUAD_STRIP);
		for(unsigned int i=0;i<=long_slices_num;i++)
		{
			float tetha_i=(float)i*delta_p;
			glVertex3f(radius*cos(ppsi_j)*cos(tetha_i),radius*sin(ppsi_j),radius*cos(ppsi_j)*sin(tetha_i));
			glVertex3f(radius*cos(psij)*cos(tetha_i),radius*sin(psij),radius*cos(psij)*sin(tetha_i));
		}
		
		/* Now, we finalize the current latitudinal slice of the 'Hemisphere' shape (thus a quad strip). */
		glEnd();
	}

	/* If we arrive here, then we have finished! */
	glFlush();
	cout<<"\tThe 'wireframe version' of the 'Hemisphere' shape is currently drawn by exploiting 'q="<<lat_slices_num<<"' latitudinal slices and 'p="<<long_slices_num;
	cout<<"' longitudinal slices, as well as rotation angles 'Rx="<<Xangle<<"', "<<"'Ry="<<Yangle<<"', and 'Rz="<<Zangle<<"'."<<endl;
	cout.flush();
}

