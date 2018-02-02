/*********************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 *
 * Last update: January 2018
 *
 * main.cpp - the main function for the 'Example-005 (Old Mode)' Test.
 *********************************************************************************************************************************************************/

/* First, we must understand which platform we are using. */
#include <cstdlib>
#include <iostream>
using namespace std;
#include "GL/glew.h"
#ifdef __APPLE__

    /* We are using any MacOSX platform (Macintosh). */
    #include "GLUT/glut.h"
    #include "OpenGL/gl.h"

#else

    /* We are not using a MacOSX platform. For instance, we have either any generic Unix-like platform (e.g., any GNU/Linux distribution), or any Microsoft Windows platform. */
    #include "GL/glut.h"
    #include "GL/gl.h"

#endif

/// The value of the <i>'x'</i> coordinate for the triangle of interest.
/**
 * The triangle of interest in this scene has vertices '(x,20,0)' - '(80,20,0)' - '(80,80,0)', for any 'x' coordinate along the x-axis. The value of this floating-point value is the value of the 'x' coordinate along the x-axis. It is initially set to 'x=20.0', and can
 * be modified by pressing the '+' (increased by 1.0), the '-' (decreased by 1.0), and the '=' (resetted to 'x=20.0') keys.
 */
GLfloat xcoord=20;

/// This boolean flag is useful for completing the textual interface.
/**
 * Specifically, the value of this boolean flag indicates whether the user has requested to modify the value of the 'x' coordinate for the triangle of interest, thus if it is necessary to add an EOL in order to complete the textual interface.
 */
bool eol=false;

/* Forward prototypes for all functions of interest! */
void draw();
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);

/// The main function for the <i>'Example-005 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
    /* First, we export out an introductory message for this test on the standard output stream (cout)! */
    cout<<endl<<"\tThis is the 'Example-005' Test, based on the (Old Mode) OpenGL."<<endl;
    cout<<"\tIt draws the 'filled version' of a polygon (in 'red') in an OpenGL window, and provides a basic interaction mechanism with the user."<<endl;
    cout<<"\tThe polygon of interest is the intersection of the following elements:"<<endl<<endl;
    cout<<"\t\t-) the ortographic viewing box '[0,100]' x '[0,100]' x '[-1,1]';"<<endl;
    cout<<"\t\t-) the triangle with vertices '(x,20,0)' - '(80,20,0)' - '(80,80,0)', for any 'x' coordinate along the x-axis."<<endl<<endl;
    cout<<"\tIn this context the orthographic viewing box is not modified. Instead, the 'x' coordinate of the triangle, initially set to 'x=20.0', can be moved by the user along";
    cout<<" the x-axis."<<endl<<"\tSpecifically, the user can:"<<endl<<endl;
    cout<<"\t\t-) increase the 'x' coordinate by '1.0' for the triangle of interest by pressing the '+' key;"<<endl;
    cout<<"\t\t-) decrease the 'x' coordinate by '1.0' for the triangle of interest by pressing the '-' key;"<<endl;
    cout<<"\t\t-) reset the 'x' coordinate for the triangle of interest to its initial value 'x=20.0' by pressing the '=' key."<<endl<<endl;
    cout<<"\tHere, the window of interest can be closed by pressing any among the 'Q', the 'q', and the 'Esc' keys."<<endl<<endl;
    cout<<"\t----------------------------------------------------------------------------------------------------------------------------------------------------------";
    cout<<"------------------------------------------------------------------------------"<<endl<<endl;
    cout.flush();
    
    /* If we arrive here, then we draw the initial version of the scene by setting 'x=20.0' for the triangle of interest! */
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(480,480);
    glutCreateWindow("The 'Example-005' Test, based on the (Old Mode) OpenGL");
    glutDisplayFunc(draw);
    glutReshapeFunc(resize);
    glutKeyboardFunc(manageKeys);
    glewExperimental = GL_TRUE;
    glewInit();
    initialize();
    glutMainLoop();
    return EXIT_SUCCESS;
}

/// This function draws the <i>'filled version'</i> of the polygon (in <i>'red'</i>), which is the intersection between a triangle and the ortographic viewing box, in the OpenGL window of interest.
void draw()
{
    /* We draw the 'filled version' of the polygon (in 'red'), which is the intersection between the following components, in the OpenGL window of interest:
     *
     * -) the ortographic viewing box '[0,100]' x '[0,100]' x '[-1,1]';
     * -) the triangle with vertices '(x,20,0)' - '(80,20,0)' - '(80,80,0)', for any 'x' coordinate along the x-axis.
     */
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(xcoord,20,0);
    glVertex3f(80,20,0);
    glVertex3f(80,80,0);
    glEnd();
    glFlush();
}

/// This function initializes the scene in the OpenGL window of interest.
void initialize()
{
    /* We initialize all global and local variables for drawing the scene in the OpenGL window of interest! */
    xcoord=20.0;
    eol=false;
    glClearColor(1.0, 1.0, 1.0, 0.0);
    cout<<"\tAt the beginning, the 'x' coordinate for the triangle of interest is set to 'x="<<xcoord<<"' in the scene."<<endl<<endl;
    cout.flush();
}

/// This function updates the viewport for the scene when it is resized. */
void resize(int w, int h)
{
    /* We update the projection and the modeling matrices! */
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,100,0,100,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
    /* We are interested only in the 'q' - 'Q' - 'Esc' - '+' - '-' - "=" keys. */
    switch (key)
    {
        case 'q':
            
            /* The user presses the 'q' key, thus we can exit from this program! */
            if(eol) cout<<endl;
            cout<<"\t----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl<<endl;
            cout<<"\tThis program is closing correctly ... "<<endl<<endl;
            cout<<"\tPress the RETURN key to finish ... ";
            cout.flush();
            cin.get();
            #ifndef _MSC_VER
                cout << endl;
                cout.flush();
            #endif
            exit(EXIT_SUCCESS);
            break;
            
        case 'Q':
            
            /* The user presses the 'Q' key, thus we can exit from this program! */
            if(eol) cout<<endl;
            cout<<"\t----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl<<endl;
            cout<<"\tThis program is closing correctly ... "<<endl<<endl;
            cout<<"\tPress the RETURN key to finish ... ";
            cout.flush();
            cin.get();
            #ifndef _MSC_VER
                cout << endl;
                cout.flush();
            #endif
            exit(EXIT_SUCCESS);
            break;
            
        case 27:
            
            /* The user presses the 'Esc' key, thus we can exit from this program! */
            if(eol) cout<<endl;
            cout<<"\t----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl<<endl;
            cout<<"\tThis program is closing correctly ... "<<endl<<endl;
            cout<<"\tPress the RETURN key to finish ... ";
            cout.flush();
            cin.get();
            #ifndef _MSC_VER
                cout << endl;
                cout.flush();
            #endif
            exit(EXIT_SUCCESS);
            break;
        
        case '+':
            
            /* The user presses the '+ key, thus we increase the 'x' coordinate by '1.0' for the triangle of interest. */
            xcoord=xcoord+(GLfloat)1.0;
            cout<<"\tThe 'x' coordinate for the triangle of interest is currently increased to 'x="<<xcoord<<"' in the scene."<<endl;
            cout.flush();
            eol=true;
            glutPostRedisplay();
            break;
            
        case '-':
            
            /* The user presses the '-' key, thus we decrease the 'x' coordinate by '1.0' for the triangle of interest. */
            xcoord=xcoord-(GLfloat)1.0;
            cout<<"\tThe 'x' coordinate for the triangle of interest is currently decreased to 'x="<<xcoord<<"' in the scene."<<endl;
            cout.flush();
            eol=true;
            glutPostRedisplay();
            break;
     
        case '=':
            
            /* The user presses the '-' key, thus we reinitialize the 'x' coordinate to 'x=20.0' for the triangle of interest. */
            xcoord=20.0;
            eol=true;
            cout<<"\tThe 'x' coordinate for the triangle of interest is currently set to its default value 'x="<<xcoord<<"' in the scene."<<endl;
            cout.flush();
            glutPostRedisplay();
            break;
            
        default:
            
            /* Other keys are not important for us! */
            break;
    }
}
