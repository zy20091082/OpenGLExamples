
#ifdef __APPLE__

#else

	#include "GL/glew.h"
	#include "GL/glut.h"
	#include "GL/gl.h"
#endif

void draw(void)
{
	/* We set a black background for the new window! */
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

int main(int argc,char **argv)
{
	/* We initialize everything, and create a very basic window! */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(50,25);
	glutInitWindowSize(480,480);
	glutCreateWindow("First example 'Example-001 (Old Mode)'");
	glutDisplayFunc(draw);
	glutMainLoop();
	return EXIT_SUCCESS;
}

