/*******************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 * 
 * Last update: February 2017
 *
 * This program is Free Software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.                                       
 *                                                                         
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License (http://www.gnu.org/licenses/gpl.txt) for more details.
 * 
 * main.cpp - the main function for the 'Example-063 (Old Mode)' example
 *******************************************************************************************************************************************************/

/* First, we must understand which platform we are using. */
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;
#ifndef uint
	typedef unsigned int uint;
#endif
#ifdef __APPLE__

	/* We are using a MacOSX platform (Macintosh) */
	#include "GL/glew.h"
	#include "GLUT/glut.h"
	#include "OpenGL/gl.h"

#else

	/* We are not using a MacOSX platform. Thus, we have a generic Unix-like platform, like the GNU Linux, or a Microsoft Windows platform. */
	#include "GL/glew.h"
	#include "GL/glut.h"
	#include "GL/gl.h"

#endif

/// The rendering mode for the scene of interest (filled triangles, if mode=0 | wireframe triangles, if mode=1 | triangles points, if mode=2).
int mode=0;

/// This constant value identifies the location of a generic buffer, specialized for storing the vertex data for the <i>'Square Annulus'</i> shape of interest.
#define VERTICES 0

/// This constant value identifies the location of a generic buffer, specialized for storing ...
#define INDICES 1

/// This plain array contains the Euclidean coordinates of the vertices for the <i>'Square Annulus'</i> shape of interest by using the <i>'Vertex Buffer Object (VBO)'</i> technique.
static GLfloat vertices[] = {
	30,30,0,
	10,10,0,
	70,30,0,
	90,10,0,
	70,70,0,
	90,90,0,
	30,70,0,
	10,90,0
};

/// This plain arrays contains the colors of the vertices for the <i>'Square Annulus'</i> shape of interest by using the <i>'Vertex Buffer Object (VBO)'</i> technique.
static GLfloat colors[] = {
	1,1,1,
	1,0,0,
	0,1,0,
	0,0,1,
	1,1,0,
	1,0,1,
	0,1,1,
	1,0,0
};

/// This plain array indicates the indices for the locations of interest for drawing the <i>'Square Annulus'</i> shape by using the <i>'Vertex Buffer Object (VBO)'</i> technique.
static uint inds[10] = { 0,1,2,3,4,5,6,7,0,1 };

/// This plain array contains the indices for the buffers to be exploited.
static uint buffer[2];

/* Prototypes for all functions of interest! */
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key,int x,int y);
void draw();
void animate(int v);

/// The main function for the <i>'Example-063 (Old Mode)'</i> example.
int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("The 'Example-063' Example, based on the (Old Mode) OpenGL");
	glutDisplayFunc(draw);
	glutReshapeFunc(resize);
	glutKeyboardFunc(manageKeys);
	glewExperimental = GL_TRUE;
   	glewInit();
   	initialize(); 
	glutMainLoop();
	return EXIT_SUCCESS;
}

/// This function updates the viewport for the scene when it is resized. */
void resize(int w,int h)
{
	/* We update the projections and the modeling matrices! */
	glViewport(0,0,w,h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glOrtho(0,100,0,100,-1,1);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key,int x,int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' keys */
	switch (key)
	{
		case 'q':
	
		/* The key is 'q' */
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case 'Q':
	
		/* The key is 'Q' */
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case 27:
	
		/* The key is 'Esc' */
		cout<<endl;
		cout.flush();
		exit(EXIT_SUCCESS);
		break;
		
		case ' ':
		
		/* We update the rendering mode. */
		mode=(mode+1)%3;
		glutPostRedisplay();
		break;

		default:

    	/* Other keys are not important for us */
    	break;
	}
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	cout<<endl<<"\tThis is the 'Example-063' Example, based on the (Old Mode) OpenGL"<<endl<<endl;
	cout<<"\tDrawing the 'Square Annulus' shape, approximated by one triangle strip, by using the 'Vertex Buffer Object (VBO)' technique."<<endl;
	cout<<"\tThe vertices colors change randomly, and it is possible to modify the triangles rendering mode by pressing the ' ' key."<<endl;
	mode=0;
	glClearColor(0.0,0.0,0.0,0.0);

	/* Here, we generate two VBO buffers and save their indices in the 'buffer' array. In this case, each buffer is implemented by a 'vertex array', thus it is mandatory to enable 
	 * the 'vertex arrays' for coordinates and colors.
	 *
	 * Then, we must associate and describe each VBO buffer as the corresponding 'vertex array'. Here:
	 *
	 * -) the 'buffer[VERTICES]' location contains the vertices coordinates and the colors (the vertex data)
	 * -) the 'buffer[INDICES]' location contains the indices for accessing correctly the 'vertex array' 
	 *
	 * We bind the 'buffer[VERTICES]' as a vertex-array, then we initialize its content. Specifically, it is formed by two parts:
	 *
	 * -) the vertex coordinates (see the 'vertices' array)
	 * -) the vertex colors (see the 'colors' array)
	 *
	 * These parts must copied separately in the VBO.
	 */
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glGenBuffers(2,buffer);
	glBindBuffer(GL_ARRAY_BUFFER,buffer[VERTICES]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices)+sizeof(colors),NULL,GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(vertices),vertices);
	glBufferSubData(GL_ARRAY_BUFFER,sizeof(vertices),sizeof(colors),colors);

	/* Nwo, we perform the same operations for the indices to be considered. Here, the VBO buffer is directly initialized. */	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffer[INDICES]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(inds),inds,GL_STATIC_DRAW);
	
	/* Now, we enable and define the vertex-array. Note that it is automatically described in terms of the VBO buffer. */
	glVertexPointer(3,GL_FLOAT,0,0);
	glColorPointer(3,GL_FLOAT,0,(GLvoid*)(sizeof(vertices)));
	
	/* Finally, we activate a very basic animation. */
	glutTimerFunc(5,animate,1);
}

/// This function enables a very basic animation when drawing the <i>'Square Annulus'</i> shape by using the <i>'Vertex Buffer Object (VBO)'</i> technique.
void animate(int v)
{
	glutPostRedisplay();
	glutTimerFunc(500,animate,1);
}

/// This function draws the <i>'Square Annulus'</i> shape of interest in the OpenGL window of interest.
void draw()
{
	float *vbo_data;

	/* We must draw the triangle strip, forming the 'Square Annulus' shape of interest, by using the 'Vertex Buffer Object (VBO)' technique. First, we retrieve the VBO in order to change randomly the vertices colors. 
	 * This is necessary only for the animation purposes. */
	glClear(GL_COLOR_BUFFER_BIT);
	vbo_data=(float*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	srand(time(NULL));
	for(int i=0;i<sizeof(colors)/sizeof(float);i++) vbo_data[sizeof(vertices)/sizeof(float)+i]=(float)rand()/(float)RAND_MAX;
	glUnmapBuffer(GL_ARRAY_BUFFER);
	
	/* Now, we invoke the 'vertex array' as usual. The VBO is automatically exploited. */
	if(mode==0) glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	if(mode==1) glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	if(mode==2) glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
	glPointSize(8);
	glLineWidth(2);
	glDrawElements(GL_TRIANGLE_STRIP,10,GL_UNSIGNED_INT,0);
	glutSwapBuffers();
}
