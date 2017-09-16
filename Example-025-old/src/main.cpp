/*******************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 * 
 * Last update: September 2017
 *
 * main.cpp - the main function for the 'Example-025 (Old Mode)' Test.
 *******************************************************************************************************************************************************/

/* First, we must understand which platform we are using. */
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <string>
#include <climits>
#include <limits>
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

/// The coefficients of the equation, describing the <i>'Parabola'</i> curve of interest.
/**
 * The 'Parabola' curve of interest is described by the following equation:
 * 
 * a x^2 + b x + c = 0
 *
 * where 'a' is not null (clearly). These global variables contain the '3' floating-point values for the parameters 'a', 'b', and 'c' of interest. The values of these
 * global variables are provided interactively by the user.
 */
float a,b,c;

/// The number <i>'n'</i> of the vertices to be used for defining the (open) polyline, approximating the <i>'Parabola'</i> curve of interest.
/**
 * The value of this global variable is the number 'n>2' of the vertices to be used for defining the (open) polyline, approximating the portion of interest for the
 * 'Parabola' curve of interest. The 'Parabola' curve of interest is described by the following equation:
 *
 * a x^2 + b x + c = 0
 *
 * where 'a' is not null (clearly). For the sake of the efficiency, only a portion of the 'Parabola' curve is drawn, centered with respect its vertex '(xv,yv)'. Here,
 * the x-range of the 'Parabola' curve is '[ xv - R, xv + R ]' for any given semi-length 'R>0', provided interactively by the user. This implies that the 'Parabola'
 * curve is approximated by a (open) polyline with 'n>2' vertices and 'm=n-1' edges. The value of 'n>2', initially set to 'n=3', can be increased and decreased by
 * pressing the '+' and the '-' keys, respectively. By construction, it is not possible to have 'n<3'.
 */
unsigned int num_samples=3;

/// The coordinates <i>'(xv,yv)'</i> for the vertex to be used for defining and drawing the (open) polyline, approximating the <i>'Parabola'</i> curve of interest.
/**
 * The 'Parabola' curve of interest is described by the following equation:
 *
 * a x^2 + b x + c = 0
 *
 * where 'a' is not null (clearly). Here, the coordinates '(xv,yv)' for the vertex of the 'Parabola' curve are determined by its coefficients 'a', 'b', and 'c', as
 * follows:
 * 
 * xv = -b / ( 2 * a ), yv = a * xv ^ 2 + b * xv + c
 *
 * These global variables contain, respectively, the coordinates 'xv' and 'yv' as '2' floating-point values. The values of these global variables are automatically 
 * computed once the user insert the values for the parameters 'a', 'b', and 'c' (mentioned above).
 */
float xv,yv;

/// The x- and the y-ranges for the scene, where the (open) polyline, approximating the <i>'Parabola'</i> curve of interest, must be drawn.
/**
 * The 'Parabola' curve of interest is described by the following equation: 
 *
 * a x^2 + b x + c = 0
 *
 * where 'a' is not null (clearly). For the sake of the efficiency, only a portion of the 'Parabola' curve is drawn, centered with respect its vertex '(xv,yv)'. Here,
 * the x-range of the 'Parabola' curve is '[ xv - R, xv + R ]' for any given semi-length 'R>0', provided interactively by the user. Instead, the y-range depends on the
 * specific 'Parabola' curve of interest, thus on its parameters 'a', 'b', and 'c', also on the semi-length 'R'.
 * 
 * These global variables contain the minimum and the maximum values for the x- and the y-ranges, and are useful for fixing the orthographic projection, used for 
 * drawing the scene. Specifically, they are floating-point values, and are automatically computed once the user insert the values for the parameters 'a', 'b', and
 * 'c' (mentioned above), and thus once also the corresponding vertex is computed.
 */
float xmin,xmax,ymin,ymax;

/// The semi-length <i>'R'</i> for the x-range of the scene, where the (open) polyline, approximating the <i>'Parabola'</i> curve of interest, must be drawn.
/**
 * The 'Parabola' curve of interest is described by the following equation: 
 *
 * a x^2 + b x + c = 0
 *
 * where 'a' is not null (clearly). For the sake of the efficiency, only a portion of the 'Parabola' curve is drawn, centered with respect its vertex '(xv,yv)', such
 * that:
 * 
 * xv = -b / ( 2 * a ), yv = a * xv ^ 2 + b * xv + c
 *
 * Here, the x-range of the 'Parabola' curve is '[ xv - R, xv + R ]' for any given semi-length 'R>0'. Instead, the y-range depends on the specific 'Parabola' curve of
 * interest, thus on its parameters 'a', 'b', and 'c', also on the semi-length 'R'.
 *
 * The value of this global variable is the semi-length 'R', which is a not null and positive floating-point value, provided interactively by the user.
 */
float R;

/* Prototypes for all functions of interest! */
void draw();
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);
float evaluateParabola(float x);
void exportEquation();
void pause();

/// The main function for the <i>'Example-025 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
	float vmin,vmax,h;

	/* We initialize everything, and create a very basic window! */
	cout<<endl<<"\tThis is the 'Example-025' Test, based on the (Old Mode) OpenGL."<<endl;
	cout<<"\tIt draws a (open) polyline (in 'red'), formed by an arbitrary number 'n>2' of the vertices (and thus by 'm=n-1' edges), in an OpenGL window. The (open) ";
	cout<<"polyline of interest approximates the 'Parabola' curve, defined as follows:"<<endl<<endl;
	cout<<"\tx(t) = t, y(t) = a * t ^ 2 + b * t + c"<<endl<<endl<<"\tfor any 't', 'b', and 'c', and any not null 'a'. The parameters 'a', 'b', and 'c' determine the ";
	cout<<"properties of the 'Parabola' curve. In particular, its vertex '(xv,yv)' is defined as follows:"<<endl<<endl;
	cout<<"\txv = -b / (2 * a), yv = a * xv ^ 2 + b * xv + c"<<endl<<endl;
	cout<<"\tFor the sake of the simplicity, the 'Parabola' curve is drawn for every 't' in the x-range '[ xv-R , xv+R ]', with any given 'R>0'. The corresponding ";
	cout<<"y-range depends on the 'Parabola' curve of interest."<<endl<<endl;
	cout<<"\tHere, the scene is centered with respect to the vertex '(xv,yv)' and the corresponding symmetry axis (in 'blue')."<<endl<<endl;
	cout<<"\tThis test also provides a very basic interaction mechanism with the user, which must provide interactively the parameter 'a' (as a not null floating-point";
	cout<<" value), the parameters 'b' and 'c' (as '2' floating-point values), as well"<<endl;
	cout<<"\tas the semi-length 'R' (as a not null and positive floating-point value). In this context, the user can also:"<<endl<<endl;
	cout<<"\t\t-) increase the number 'n' of the vertices (thus also the number 'm=n-1' of the edges) in the (open) polyline of interest by pressing the '+' key. By";
	cout<<" construction, it is not possible to have 'n<3' and 'm<2'."<<endl;
	cout<<"\t\t-) Decrease the number 'n' of the vertices (thus also the number 'm=n-1' of the edges) in the (open) polyline of interest by pressing the '-' key. By";
	cout<<" construction, it is not possible to have 'n<3' and 'm<2'."<<endl<<endl;
	cout<<"\tLikewise, the window of interest can be closed by pressing any among the 'Q', the 'q', and the 'Esc' keys."<<endl<<endl;
	cout<<"\t----------------------------------------------------------------------------------------------------------------------------------------------------------";
	cout<<"------------------------------------------------------------------------------"<<endl<<endl;
	cout.flush();

	/* If we arrive here, then the user must insert the coefficients 'a' - 'b' - 'c' for the equation 'a * x^2 + b*x + c = 0' of the 'Parabola' curve. */
	cout<<"\tPlease, insert all coefficients '(a,b,c)' for the equation 'a * x ^ 2 + b * x + c = 0' (thus, 3 floating-point values, separated by spaces, such that ";
	cout<<"'a' is not null), describing the 'Parabola' curve of interest: ";
	cin>>a>>b>>c;
	if( (!cin) || (a==0) )
	{
		cin.clear();
		cout<<endl<<"\tPLEASE, INSERT VALID COEFFICIENTS '(a,b,c)' FOR THE EQUATION 'a * x ^ 2 + b * x + c = 0' (THUS, 3 FLOATING-POINT VALUES, SEPARATED BY SPACES, ";
		cout<<"SUCH THAT 'a' IS NOT NULL), DESCRIBING THE 'PARABOLA' CURVE OF INTEREST."<<endl<<endl;
		cout<<"\tTHIS PROGRAM IS CLOSING ... "<<endl<<endl;
		pause();
		return EXIT_FAILURE;
	}

	/* If we arrive here, then we can compute the vertex '(xv,yv)' for the custom 'Parabola' curve of interest. */
	xv=-b/(2.0*a);
	yv=evaluateParabola(xv);
	cout<<endl<<"\tIn this case, the 'Parabola' curve of interest has equation ";
	exportEquation();
	cout<<", and vertex '(xv,yv)' = ("<<xv<<","<<yv<<")."<<endl<<endl;

	/* Finally, the user must insert the semi-length 'R' for the x-range '[ xv-R ; xv+R ]', where the 'Parabola' curve must be drawn. */
	cout<<"\tPlease, insert the semi-length 'R' (thus, a positive and not null floating-point value), used for determining the x-range [";
	if(xv==0) cout<<"-R,+R]";
	else cout<<xv<<"-R,"<<xv<<"+R]";
	cout<<", where the 'Parabola' curve is drawn: ";
	cin>>R;
	if( (!cin) || (R<=0) )
	{
		cin.clear();
		cout<<endl<<"\tPLEASE, INSERT A VALID VALUE (THUS, A POSITIVE AND NOT NULL FLOATING-POINT VALUE) FOR THE SEMI-LENGTH 'R' OF INTEREST."<<endl<<endl;
		cout<<"\tTHIS PROGRAM IS CLOSING ..."<<endl<<endl;
		pause();
		return EXIT_FAILURE;
	}

	/* Now, we complete everything! */
	xmin=xv-R;
	xmax=xv+R;
	cout<<endl<<"\tAs mentioned above, the 'Parabola' curve of interest has equation ";
	exportEquation();
	cout<<", and vertex '(xv,yv)' = ("<<xv<<","<<yv<<")."<<endl;
	cout<<"\tThe x-range for the 'Parabola' of interest is ["<<xmin<<","<<xmax<<"]."<<endl;
	vmin=evaluateParabola(xmin);
	vmax=evaluateParabola(xmax);
	ymin=min((float)min(vmin,vmax),yv);
	ymax=max((float)max(vmin,vmax),yv);
	cout<<"\tThe y-range for the 'Parabola' curve of interest is ["<<ymin<<","<<ymax<<"]."<<endl<<endl;
	h=fabs(ymin-ymax);
	cout<<"\t----------------------------------------------------------------------------------------------------------------------------------------------------------";
	cout<<"------------------------------------------------------------------------------"<<endl<<endl;
	cout.flush();

	/* If we arrive here, then we can draw the (open) polyline, approximating the 'Parabola' curve of interest. */
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	if(h==2*R) glutInitWindowSize(500,500);
	else if(2*R>h) { glutInitWindowSize(1000,1000*h/(2*R)); }
	else { glutInitWindowSize(1000*2*R/h,1000); }
	glutCreateWindow("The 'Example-025' Test, based on the (Old Mode) OpenGL");
	glutDisplayFunc(draw);
	glutReshapeFunc(resize);
	glutKeyboardFunc(manageKeys);
	glewExperimental = GL_TRUE;
   	glewInit();
   	initialize(); 
	glutMainLoop();
	return EXIT_SUCCESS;
}

/// This function evaluates the y-value for equation, describing the <i>'Parabola'</i> curve of interest, at a given x-coordinate.
/**
 * The 'Parabola' curve of interest is described by the following equation:
 *
 * a x^2 + b x + c = 0
 *
 * where 'a' is not null (clearly). This function returns the y-value of the 'Parabola' curve for any given any floating-point 'x' value.
 */
float evaluateParabola(float x) { return (a*x*x+b*x+c); }

/// This function exports the human-readable version of the equation for the <i>'Parabola'</i> curve of interest on the standard output stream.
/**
 * The 'Parabola' curve of interest is described by the following equation:
 *
 * a x^2 + b x + c = 0
 *
 * where 'a' is not null (clearly). The human-readable version of this equation, exported by this function, depends on the actual values of the parameters 'a', 'b', and
 * 'c'.
 */
void exportEquation()
{
	/* Now, we check the 'a' value in the equation 'ax^2+bx+c=0'. */
	cout<<"'";
	if(a>0)
	{
		if(fabs(a)!=1.0) cout<<fabs(a);
		cout<<" * x^2 ";
	}
	else if(a<0)
	{
		cout<<"-";
		if(fabs(a)!=1.0) cout<<fabs(a);
		cout<<" * x^2 ";
	}	
	
	/* Now, we check the 'b' value in the equation 'ax^2+bx+c=0'. */
	if(b>0)
	{
		if(fabs(b)!=1.0) cout<<"+ "<<fabs(b)<<" * x ";
		else cout<<"+ x ";
	}
	else if(b<0)
	{
		if(fabs(b)!=1.0) cout<<"- "<<fabs(b)<<" * x ";
		else cout<<"- x ";
	}

	/* Finally, we check the 'c' value in the equation 'ax^2+bx+c=0'. */
	if(c>0) { cout<<"+ "<<fabs(c)<<" "; }
	else if(c<0) { cout<<"- "<<fabs(c)<<" "; }
	cout<<"= 0'";
}

/// This function simulates a pause while this test runs.
void pause()
{
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cin.clear();
	cout << "\tPress the RETURN key to finish ... ";
	cout.flush();
	cin.get();
	#ifndef _MSC_VER
		cout << endl;
		cout.flush();
	#endif
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
	/* We are interested only in the 'q' - 'Q' - 'Esc' - '+' - '-' keys. */
	switch (key)
	{
		case 'q':
	
			/* The key is 'q', thus we can exit from this program. */
			cout<<endl<<"\tThis program is closing correctly ... "<<endl<<endl;
			pause();
			exit(EXIT_SUCCESS);
			break;
		
		case 'Q':
	
			/* The key is 'Q', thus we can exit from this program. */
			cout<<endl<<"\tThis program is closing correctly ... "<<endl<<endl;
			pause();
			exit(EXIT_SUCCESS);
			break;
		
		case 27:
	
			/* The key is 'Esc', thus we can exit from this program. */
			cout<<endl<<"\tThis program is closing correctly ... "<<endl<<endl;
			pause();
			exit(EXIT_SUCCESS);
			break;
		
		case '+':
		
			/* The key is '+', thus we increase the number 'n>2' of the vertices in the (open) polyline of interest. By construction, it is not possible to have 'n<3'.
			 */
			num_samples=num_samples+1;
			glutPostRedisplay();
			break;
		
		case '-':
		
			/* The key is '-', thus we decrease the number 'n>2' of the vertices (if possible) in the (open) polyline of interest. By construction, it is not possible to
			 * have 'n<3'. */
			if(num_samples>3) num_samples=num_samples-1;
			else
			{
				/* Here, we have already 'n=3', and it is not possible to decrease again the value of 'n'. */
				cout<<"\tThe minimum number 'n=3' of the vertices in the (open) polyline of interest is reached, and it is not possible to decrease ";
				cout<<"again this number."<<endl;
				cout.flush();
			}

			/* If we arrive here, then this case is finished! */
			glutPostRedisplay();
			break;

		default:

    		/* Other keys are not important for us! */
    		break;
	}
}

/// This function updates the viewport for the scene when it is resized. */
void resize(int w, int h)
{
	float x0,x1,y0,y1;

	/* First, we set properly the x-range. */
	x0=xmin-0.1*fabs(xmin);
	x1=xmax+0.1*fabs(xmax);
	y0=ymin-0.1*fabs(ymin);
	y1=ymax+0.1*fabs(ymax);
	if(xmin==0)
	{
		x1=xmax+0.1*fabs(xmax);
		x0=-0.1*fabs(xmax);
	}
	else if(xmax==0)
	{
		x0=xmin-0.1*fabs(xmin);
		x1=0.1*fabs(xmin);
	}
	
	/* Now, we set properly the y-range. */
	if(ymin==0)
	{
		y1=ymax+0.1*fabs(ymax);
		y0=-0.1*fabs(ymax);
	}
	else if(ymax==0)
	{
		y0=ymin-0.1*fabs(ymin);
		y1=0.1*fabs(ymin);
	}
	
	/* We update the projection and the modeling matrices! */
	glViewport(0, 0, w, h);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glOrtho(x0,x1,y0,y1,-1,1);
   	glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
}

/// This function initializes the OpenGL window of interest.
void initialize() 
{
	/* We initialize the OpenGL window of interest! */
	glClearColor(1.0, 1.0, 1.0, 0.0);
	num_samples=3;
	cout<<"\tAt the beginning, the (open) polyline, approximating the portion of interest for the 'Parabola' curve, is formed by 'n="<<num_samples<<"' vertices and ";
	cout<<"'m=n-1="<<(num_samples-1)<<"' edges (thus by the minimum number 'n' as possible)."<<endl<<endl;
	cout.flush();
}

/// This function draws the (open) polyline (in <i>'red'</i>), approximating the <i>'Parabola'</i> curve of interest, in the main OpenGL window.
void draw()
{
	/* We draw the (open) polyline (in 'red'), approximating the 'Parabola' curve of interest, in the main OpenGL window. */
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glLineWidth(1);
	glBegin(GL_LINE_STRIP);
	float d=(2*R)/(num_samples-1);
	unsigned int m=num_samples/2;
	if( num_samples % 2!=0)
	{
		for(unsigned int k=0;k<num_samples;k++)
		{
			float x=xmin+k*d;
			if(k==m) glVertex3f(x,yv,0);
			else glVertex3f(x,evaluateParabola(x),0);
		}
	}
	else
	{
		for(unsigned int k=0;k<num_samples;k++)
		{
			float x=xmin+k*d;
			if( (k==m) || (k==(m-1)) ) glVertex3f(x,yv,0);
			else glVertex3f(x,evaluateParabola(x),0);
		}
	}

	/* If we arrive here, then all is ok, and we can draw the vertex '(xv,yv)' of the 'Parabola' curve of interest, and the corresponding symmetry axis (in 'blue'). */
	glEnd();
	glColor3f(0.0,0.0,1.0);
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex3f(xv,yv,0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(xv,ymin,0);
	glVertex3f(xv,ymax,0);
	glEnd();	
	glFlush();
	cout<<"\tThe portion of interest for the 'Parabola' curve is currently approximated by a (open) polyline with 'n="<<num_samples<<"' vertices and 'm=n-1=";
	cout<<(num_samples-1)<<"' edges."<<endl;
	cout.flush();
}

