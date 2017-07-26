/*******************************************************************************************************************************************************
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
 * main.cpp - the main function for the 'Example-061 (Old Mode)' Test.
 *******************************************************************************************************************************************************/

/* First, we must understand which platform we are using. */
#include <cstdlib>
#include <iostream>
#include <cmath>
#define PI 3.14159265358979324
#ifndef uint
	typedef unsigned int uint;
#endif
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
float Xangle=10.0;

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
uint num_samples=3;

/// The Euclidean 3D coordinates for the vertices in all triangle strips, approximating the <i>'Playground Slide'</i> shape.
/**
 * By construction, the 'Playground Slide' shape is defined by extruding a parabolic profile, formed by 'n' samples, and adding several basis for enclosing a void. This
 * operation results into the union of 4 major pieces, all approximated by a triangle strip:
 *
 * -) 	the extrusion of 2 parabolic profiles, requiring '2*n' points for being described by a triangle strip. It is also possible to merge this surface with the
 *	  	frontward and the backward sides of the solid. These latter require other 4 points for being describing as 2 triangle strips. The union of these triangle strips
 * 		forms the triangle strip #0.
 * -) 	'2' lateral surfaces, bounded by the parabolic profiles, and by the 'xz' coordinate plane. Each of them require '2*n' points for being described as 2 triangle 
 * 	  	strips. These are the triangle strips #1 and #2. 
 * -) 	the bottom basis of the solid, laying on the 'xz' coordinate plane. This surfaces requires '2*n' points for being described as a triangle strip. This is the
 *		triangle strip #3.
 *
 * Specifically, this array contains the Euclidean 3D coordinates (thus 3 floating-point values) for all points, necessary for modeling these triangle strips. Hence,
 * this array contains '3*(2*n+4)+3*(2*n)+3*(2*n)+3*(2*n)' floating-point values. This array is indirectly used by the 'glMultiDrawElements()' function by using the
 * degree of indirection, provided by the 'inds' and the 'cnt' arrays (see later).
 *
 * The content of this array (including the content of other auxiliary data structures) is recomputed by the 'computePoints()' function, when the value 'n' is modified
 * by the user. Instead, their content is deallocated by the 'destroyPoints()' function.
 */
GLfloat *vertices=NULL;

/// The indices for accessing correctly the Euclidean 3D coordinates for all vertices in the triangle strips, approximating the <i>'Playground Slide'</i> shape.
/**
 * By construction, the 'Playground Slide' shape is defined by extruding a parabolic profile, formed by 'n' samples, and adding several basis for enclosing a void. This
 * operation results into the union of 4 major pieces, all approximated by a triangle strip:
 *
 * -) 	the extrusion of 2 parabolic profiles, requiring '2*n' points for being described by a triangle strip. It is also possible to merge this surface with the
 *	  	frontward and the backward sides of the solid. These latter require other 4 points for being describing as 2 triangle strips. The union of these triangle strips
 * 		forms the triangle strip #0.
 * -) 	'2' lateral surfaces, bounded by the parabolic profiles, and by the 'xz' coordinate plane. Each of them require '2*n' points for being described as 2 triangle 
 * 	  	strips. These are the triangle strips #1 and #2. 
 * -) 	the bottom basis of the solid, laying on the 'xz' coordinate plane. This surfaces requires '2*n' points for being described as a triangle strip. This is the
 *		triangle strip #3.
 * 
 * Each row of this matrix contains the indices to the locations in the 'vertices' array, that are necessary for modeling a given triangle strip. Thus, this matrix has
 * 4 rows. Specifically:
 *
 * -)	the row #0 corresponds to the triangle strip #0, and contains '2*n+4' indices to the corresponding locations;
 * -) 	the rows #1 and #2 correspond to '2' lateral surfaces of the 'Playground Slide', and each of them contains '2*n' indices;
 * -)	the row #3 corresponds to the bottom basis of the solid, and contains '2*n' indices. 
 *
 * Broadly speaking, this matrix provides the degree of indirection, together with the 'cnt' array, for making accessible to the 'glMultiDrawElements()' function all
 * locations of interest in the 'vertices' array.
 *
 * The content of this matrix (including the content of other auxiliary data structures) is recomputed by the 'computePoints()' function, when the value 'n' is modified
 * by the user. Instead, their content is deallocated by the 'destroyPoints()' function.
 */
uint **inds=NULL;

/// The vertices numbers in the triangle strips, approximating the <i>'Playground Slide'</i> shape.
/**
 * By construction, the 'Playground Slide' shape is defined by extruding a parabolic profile, formed by 'n' samples, and adding several basis for enclosing a void. This
 * operation results into the union of 4 major pieces, all approximated by a triangle strip:
 *
 * -) 	the extrusion of 2 parabolic profiles, requiring '2*n' points for being described by a triangle strip. It is also possible to merge this surface with the
 *	  	frontward and the backward sides of the solid. These latter require other 4 points for being describing as 2 triangle strips. The union of these triangle strips
 * 		forms the triangle strip #0.
 * -) 	'2' lateral surfaces, bounded by the parabolic profiles, and by the 'xz' coordinate plane. Each of them require '2*n' points for being described as 2 triangle 
 * 	  	strips. These are the triangle strips #1 and #2. 
 * -) 	the bottom basis of the solid, laying on the 'xz' coordinate plane. This surfaces requires '2*n' points for being described as a triangle strip. This is the
 *		triangle strip #3.
 * 
 * Each component of this array corresponds to a row of the 'inds' matrix. This latter contains the indices to the locations in the 'vertices' array, that are necessary
 * for modeling a given triangle strip. Thus, this array has 4 components (the same as the rows number in the 'inds' matrix). Specifically:
 *
 * -)	the row #0 of the 'inds' matrix corresponds to the triangle strip #0, and contains '2*n+4' indices to the corresponding locations. Thus, the component #0 of this
 *		array contains the value '2*n+4'.
 * -) 	The rows #1 and #2 of the 'inds' matrix correspond to '2' lateral surfaces of the 'Playground Slide', and each of them contains '2*n' indices. Thus, both the 
 *		components #1 and #2 of this array contain the value '2*n'.
 * -)	The row #3 corresponds to the bottom basis of the solid, and contains '2*n' indices. Thus, the component #3 of this array contains the value '2*n'.
 *
 * Broadly speaking, this array provides the degree of indirection, together with the 'inds' matrix, for making accessible to the 'glMultiDrawElements()' function all
 * locations of interest in the 'vertices' array.
 *
 * The content of this array (including the content of other auxiliary data structures) is recomputed by the 'computePoints()' function, when the value 'n' is modified
 * by the user. Instead, their content is deallocated by the 'destroyPoints()' function.
 */
int *cnt=NULL;

/* Prototypes for all functions of interest! */
void initialize();
void manageKeys(unsigned char key, int x, int y);
void draw();
void resize(int w,int h);
float evaluateSlide(float v);
void computePoints();
void destroyPoints();

/// The main function for the <i>'Example-061 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-061' Test, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws the 'Playground Slide' shape in an OpenGL window. Intuitively, this shape describes the classic playground slides, that can be found in parks, ";
	cout<<"schools, playgrounds, and backyards. A "<<endl;
	cout<<"\tslide may be flat or (more often) half cylindrical, in order to prevent falls. Slides are usually constructed of plastic or metal, and they have a smooth ";
	cout<<"surface, which is either straight or "<<endl;
	cout<<"\twavy. The user, typically a child, climbs to the top of the slide via a ladder or stairs, sits down on the top of the slide, and slides down the ";
	cout<<"chute."<<endl<<endl;
	cout<<"\tIn this case, we try to model this physical object by considering a parabolic profile to be extruded. A parabolic profile is a portion of the 'Parabola' ";
	cout<<"curve, defined as follows:"<<endl<<endl;
	cout<<"\tx(t) = t, y(t) = a * t ^ 2 + b * t + c"<<endl<<endl;
	cout<<"\tfor any not null 'a', and for every 't'. The parameters 'a', 'b', and 'c' determine the properties of the 'Parabola' curve."<<endl<<endl;
	cout<<"\tHere, we limit our attention to every 't' in a given range in order to obtain a parabolic profile, which is extruded along the 'z'-axis in order to ";
	cout<<"obtain the slide of interest (specifically "<<endl;
	cout<<"\ta curvilinear '2D' shape). In order to obtain a '3D' solid, we also consider '2' lateral surfaces, bounded by the parabolic profiles and by the 'xz' ";
	cout<<"coordinate plane, as well as '2' "<<endl;
	cout<<"\tquadrilaterals, that are the frontward and the backward sides of the solid, plus another quadrilateral, which is the bottom basis in the 'xz' coordinate ";
	cout<<"plane. Broadly speaking, the"<<endl<<"\t'Playground Slide'shape is the '2D' shape, bounding this '3D' solid."<<endl<<endl;
	cout<<"\tThe parabolic profile of interest is approximated by a polyline with 'n' vertices and edges. This implies that each lateral side as well as the bottom ";
	cout<<"basis of the 'Playgrond Slide' shape"<<endl;
	cout<<"\tcan be approximated by '3 independent triangle strips. Instead, the frontward and the backward sides of the 'Playground Slide' shape are simply ";
	cout<<"quadrilaterals, that can be triangulated. By"<<endl;
	cout<<"\tconstruction, these latter, together with the triangle strip, approximating the extrusion of the parabolic profile, can be merged into only one triangle";
	cout<<" strip. Specifically, the"<<endl;
	cout<<"\t'wireframe versions' of the triangles in these '4' triangle grids (in 'green') are rendered by using the perspective projection."<<endl<<endl;
	cout<<"\tFor the sake of the efficiency, we exploit the 'vertex array' technique, provided directly by the OpenGL, for modeling '4' triangle strips of interest. ";
	cout<<"This technique is used to group together"<<endl;
	cout<<"\tseveral drawing instructions into only one instruction for rendering (a subset of) the vertices and some of their state parameters. Here, we limit our ";
	cout<<"attention to the Euclidean '3D'"<<endl;
	cout<<"\tcoordinates (thus, '3' floating-point values) for every point in '4' triangle strips of interest. These floating-point values are stored in a unique ";
	cout<<"array, such that its content is recomputed"<<endl;
	cout<<"\twhen modifying the number 'n' of the samples in the parabolic profile. In this case, the 'glMultiDrawElements()' function is exploited for drawing ";
	cout<<"directly the content of this array (in only"<<endl;
	cout<<"\tone step) by using another indirection level."<<endl<<endl;
	cout<<"\tIn this test, the user cannot modify the parameters of the parabolic profile to be extruded (like the parabola equation and the position), as well as ";
	cout<<"the extrusion parameters for the"<<endl;
	cout<<"\t'Playground Slide' shape of interest, since they are fixed in advance. Instead, the user can modify the number 'n' of the samples in the parabolic ";
	cout<<"profile, as well as rotate the scene along"<<endl;
	cout<<"\tthe coordinate axes. In particular the user can:"<<endl<<endl;
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
	glutCreateWindow("The 'Example-061' Test, based on the (Old Mode) OpenGL");
	glutReshapeFunc(resize);
	glutKeyboardFunc(manageKeys);
	glutDisplayFunc(draw);
	glewExperimental = GL_TRUE;
   	glewInit();
   	initialize(); 
	glutMainLoop();
	return EXIT_SUCCESS;
}

/// This function evaluates the parabolic profile for the <i>'Playground Slide'</i> shape at a given point.
float evaluateSlide(float v) { return ( 0.03875*pow(v,2)-1.225*v+10.0); }

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
	glClearColor(0.0, 0.0, 0.0, 0.0);
	Xangle=10.0;
	Yangle=0.0;
	Zangle=0.0;
	num_samples=3;
	vertices=NULL;
	inds=NULL;
	cnt=NULL;
	computePoints();
	glEnableClientState(GL_VERTEX_ARRAY);
	cout<<"\tAt the beginning, the 'wireframe version' of the 'Playground Slide' shape is drawn by exploiting 'n="<<num_samples<<"' samples in its parabolic profile, ";
	cout<<"as well as rotation angles 'Rx="<<Xangle<<"', "<<"'Ry="<<Yangle<<"', and 'Rz="<<Zangle<<"'."<<endl<<endl;
	cout.flush();
}

/// This function allocates and initializes the content of all auxiliary data structures, used for drawing the <i>'Playground Slide'</i> shape.
/**
 * Specifically, this function allocates and initializes the content of the following auxiliary data structures:
 *
 * -)	the 'vertices' array, containing the Euclidean 3D coordinates for the vertices in all triangle strips of interest;
 * -)	the 'inds' matrix, containing the locations indices in the 'vertices' array, that correspond to the vertices for all triangle strips of interest;
 * -)	the 'cnt' array, containing the vertices numbers in the triangle strips of interest (with respect to the 'vertices' array).
 *
 * The content of these auxiliary data structures is deallocated by the 'destroyPoints()' function, when the value 'n' is modified by the user.
 */
void computePoints()
{
	float dv=40.0/(num_samples-1);
	uint ind=0;

	/* First, we deallocate the existing points. Then, we allocate all auxiliary arrays, and other variables. */
	destroyPoints();
	inds=new uint*[4];
	for(uint k=0;k<4;k++) inds[k]=NULL;
	cnt=new int[4];
	for(uint k=0;k<4;k++) cnt[k]=(int)0;
	vertices=new GLfloat[3*(2*num_samples+4)+3*(2*num_samples)+3*(2*num_samples)+3*(2*num_samples)];
	
	/* Now, we add the data for the triangle strip #0, containing 'n+4' actual vertices. */
	cnt[0]=2*num_samples+4;
	inds[0]=new uint[2*num_samples+4];
	ind=0;
	inds[0][ind]=ind;
	vertices[3*ind]=5;
	vertices[3*ind+1]=0;
	vertices[3*ind+2]=-20;
	ind=ind+1;
	inds[0][ind]=ind;
	vertices[3*ind]=-5;
	vertices[3*ind+1]=0;
	vertices[3*ind+2]=-20;
	for(unsigned int k=0;k<num_samples;k++)
	{
		float v=-20.0+k*dv;
		float p=evaluateSlide(v);
		
		/* Now, we analyze the samples of the parabola! */
		ind=ind+1;
		inds[0][ind]=ind;
		vertices[3*ind]=5;
		vertices[3*ind+1]=p;
		vertices[3*ind+2]=v;
		ind=ind+1;
		inds[0][ind]=ind;
		vertices[3*ind]=-5;
		vertices[3*ind+1]=p;
		vertices[3*ind+2]=v;
	}

	/* If we arrive here, we complete 2 vertical basis (front and back). */
	ind=ind+1;
	inds[0][ind]=ind;
	vertices[3*ind]=5;
	vertices[3*ind+1]=0;
	vertices[3*ind+2]=20;
	ind=ind+1;
	inds[0][ind]=ind;
	vertices[3*ind]=-5;
	vertices[3*ind+1]=0;
	vertices[3*ind+2]=20;

	/* Now, we compute the points for the triangle strip #1, which contains 'n' actual vertices. */
	cnt[1]=2*num_samples;
	inds[1]=new uint[2*num_samples];
	for(unsigned int k=0;k<num_samples;k++)
	{
		float v=-20.0+k*dv;
		float p=evaluateSlide(v);
		
		/* Now, we add 2 vertices of this slide! */
		ind=ind+1;
		inds[1][2*k]=ind;
		vertices[3*ind]=5;
		vertices[3*ind+1]=p;
		vertices[3*ind+2]=v;
		ind=ind+1;
		inds[1][2*k+1]=ind;
		vertices[3*ind]=5;
		vertices[3*ind+1]=0;
		vertices[3*ind+2]=v;
	}
	
	/* Now, we compute the points for the triangle strip #2, which contains 'n' actual vertices. */
	cnt[2]=2*num_samples;
	inds[2]=new uint[2*num_samples];
	for(unsigned int k=0;k<num_samples;k++)
	{
		float v=-20.0+k*dv;
		float p=evaluateSlide(v);
		
		/* Now, we add 2 vertices of this slide! */
		ind=ind+1;
		inds[2][2*k]=ind;
		vertices[3*ind]=-5;
		vertices[3*ind+1]=p;
		vertices[3*ind+2]=v;
		ind=ind+1;
		inds[2][2*k+1]=ind;
		vertices[3*ind]=-5;
		vertices[3*ind+1]=0;
		vertices[3*ind+2]=v;
	}

	/* Now, we compute the points for the (last) triangle strip #3, which contains 'n' actual vertices. */
	cnt[3]=2*num_samples;
	inds[3]=new uint[2*num_samples];
	for(unsigned int k=0;k<num_samples;k++)
	{
		float v=-20.0+k*dv;
		ind=ind+1;
		inds[3][2*k]=ind;
		vertices[3*ind]=5;
		vertices[3*ind+1]=0;
		vertices[3*ind+2]=v;
		ind=ind+1;
		inds[3][2*k+1]=ind;
		vertices[3*ind]=-5;
		vertices[3*ind+1]=0;
		vertices[3*ind+2]=v;
	}
}

/// This function deallocates all auxiliary data structures, used for drawing the <i>'Playground Slide'</i> shape.
/**
 * Specifically, this function deallocates the following auxiliary data structures:
 *
 * -)	the 'vertices' array, containing the Euclidean 3D coordinates for the vertices in all triangle strips of interest;
 * -)	the 'inds' matrix, containing the locations indices in the 'vertices' array, that correspond to the vertices for all triangle strips of interest;
 * -)	the 'cnt' array, containing the vertices numbers in the triangle strips of interest (with respect to the 'vertices' array).
 *
 * The content of these auxiliary data structures is recomputed by the 'computePoints()' function, when the value 'n' is modified by the user.
 */
void destroyPoints()
{
	/* First, we destroy the 'vertices' and the 'cnt' arrays. Finally, we destroy the 'inds' matrix. */
	if(vertices!=NULL) delete vertices;
	vertices=NULL;
	if(cnt!=NULL) delete cnt;
	cnt=NULL;
	if(inds!=NULL)
	{
		for(unsigned int j=0;j<4;j++) if(inds[j]!=NULL) { delete inds[j]; inds[j]=NULL; } 
		delete inds;
		inds=NULL;
	}
}

/// This function draws the <i>'Playground Slide'</i> shape in the OpenGL window of interest by using the preferences, chosen by the user.
void draw()
{
	/* Now, we draw the Playground Slide' shape in the OpenGL window of interest by using the preferences, chosen by the user. */
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
   	glTranslatef(0.0, 0.0, -28.0);
   	glRotatef(Zangle, 0.0, 0.0, 1.0);
   	glRotatef(Yangle, 0.0, 1.0, 0.0);
  	glRotatef(Xangle, 1.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glColor3f(0,1,0);
	glLineWidth(1);
	glVertexPointer(3,GL_FLOAT,0,vertices);
	glMultiDrawElements(GL_TRIANGLE_STRIP,cnt,GL_UNSIGNED_INT,(const void**)inds,4);
	glFlush();
	cout<<"\tThe current 'wireframe version' of the 'Playground Slide' shape is drawn by exploiting 'n="<<num_samples<<"' samples in its parabolic profile, as well ";
	cout<<"as rotation angles 'Rx="<<Xangle<<"', "<<"'Ry="<<Yangle<<"', and 'Rz="<<Zangle<<"'."<<endl;
	cout.flush();
}

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
			destroyPoints();
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
			destroyPoints();
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
			destroyPoints();
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
			computePoints();
			glutPostRedisplay();
			break;
		
		case '-':
			
			/* The key is '-', thus we reduce the number of the samples in the parabolic profile in the 'Playground Slide' shape. */
			if(num_samples>3) { num_samples=num_samples-1; computePoints(); }
			else { cout<<"\tThe minimum number 'n=3' of the samples in the parabolic profile of the 'Playground Slide' shape is reached, and it is not possible to decrease again this number."<<endl; }
			glutPostRedisplay();
			break;

		default:
		
			/* Other keys are not important for us */
			break;
	}
}

