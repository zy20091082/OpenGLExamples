/*********************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 *
 * Last update: January 2018
 *
 * main.cpp - the main function for the 'Example-002 (Old Mode)' Test.
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

/* Forward prototypes for all functions of interest! */
void draw(void);
void initialize(void);
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);

/// The main function for the <i>'Example-002 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
    /* First, we export out an introductory message for this test on the standard output stream (cout)! */
    cout<<endl<<"\tThis is the 'Example-002' Test, based on the (Old Mode) OpenGL."<<endl;
    cout<<"\tIt is similar to the classic 'Hello World' program for testing the correctness of the building infrastructure."<<endl;
    cout<<"\tBroadly speaking, it draws the 'filled version' of a quadrilateral (in 'red') in an OpenGL window, and provides a very basic interaction mechanism with ";
    cout<<"the user."<<endl<<endl<<"\tHere, the window of interest can be closed by pressing any among the 'Q', the 'q', and the 'Esc' keys."<<endl<<endl;
    cout<<"\t----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl<<endl;
    cout.flush();
    
    /* If we arrive here, then we can draw the desired scene! */
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
    glutInitWindowPosition(50,25);
    glutInitWindowSize(480,480);
    glutCreateWindow("The 'Example-002' Test, based on the (Old Mode) OpenGL");
    glutDisplayFunc(draw);
    glutReshapeFunc(resize);
    glutKeyboardFunc(manageKeys);
    glewExperimental = GL_TRUE;
    glewInit();
    initialize();
    glutMainLoop();
    return EXIT_SUCCESS;
}

/// This function initializes the scene in the OpenGL window of interest.
void initialize() { glClearColor(1.0, 1.0, 1.0, 0.0); }

/// This function updates the viewport for the scene when it is resized. */
void resize(int w, int h)
{
    /* We update the projection and the modeling matrices! */
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/// This function draws the <i>'filled version'</i> of a quadrilateral (in <i>'red'</i>) in the OpenGL window of interest.
void draw()
{
    /* We draw the 'filled version' of a quadrilateral (in 'red') in the OpenGL window of interest! */
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(30.0, 20.0, 0.0);
    glVertex3f(80.0, 20.0, 0.0);
    glVertex3f(80.0, 80.0, 0.0);
    glVertex3f(20.0, 80.0, 0.0);
    glEnd();
    glFlush();
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
    /* We are interested only in the 'q' - 'Q' - 'Esc' keys. */
    switch(key)
    {
        case 'q':
        
            /* The user presses the 'q' key, thus we can exit from this program! */
            cout<<"\tThis program is closing correctly ... "<<endl<<endl;
            cout << "\tPress the RETURN key to finish ... ";
            cin.get();
            #ifndef _MSC_VER
                cout << endl;
                cout.flush();
            #endif
            exit(EXIT_SUCCESS);
            break;
            
        case 'Q':
            
            /* The user presses the 'Q' key, thus we can exit from this program! */
            cout<<"\tThis program is closing correctly ... "<<endl<<endl;
            cout << "\tPress the RETURN key to finish ... ";
            cin.get();
            #ifndef _MSC_VER
                cout << endl;
                cout.flush();
            #endif
            exit(EXIT_SUCCESS);
            break;

        case 27:
            
            /* The user presses the 'Esc' key, thus we can exit from this program! */
            cout<<"\tThis program is closing correctly ... "<<endl<<endl;
            cout << "\tPress the RETURN key to finish ... ";
            cin.get();
            #ifndef _MSC_VER
                cout << endl;
                cout.flush();
            #endif
            exit(EXIT_SUCCESS);
            break;
            
        default:
            
            /* Other keys are not important for us! */
            break;
    }
}

