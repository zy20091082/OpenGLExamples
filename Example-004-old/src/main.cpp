/*********************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com).
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 *
 * Last update: March 2018.
 *
 * main.cpp - the main function for the 'Example-004 (Old Mode)' Test.
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

// These variables define the orthographic view of interest to be applied in the scene.
/*
 * -) the value of the 'left_value' global variable indicates the minimum value of the range along the 'x'-axis;
 * -) the value of the 'right_value' global variable indicates the maximum value of the range along the 'x'-axis;
 * -) the value of the 'bottom_value' global variable indicates the minimum value of the range along the 'y'-axis;
 * -) the value of the 'top_value' global variable indicates the maximum value of the range along the 'y'-axis;
 * -) the negated value of the 'far_value' global variable indicates the minimum value of the range along the 'z'-axis;
 * -) the negated value of the 'near_value' global variable indicates the maximum value of the range along the 'z'-axis.
 */
GLfloat left_value, right_value, bottom_value, top_value, near_value, far_value;

// The orthographic projection to be applied for rendering the scene.
/**
 * The value of this global variable indicates what orthographic viewing box must be applied to the scene by following these conventions:
 *
 * -) 0: it corresponds to the ortographic viewing box '[0,100]' x '[0,100]' x '[-1,1]' (the 'View #0'), activated by pressing the <0> key;
 * -) 1: it corresponds to the ortographic viewing box '[0,200]' x '[0,200]' x '[-1,1]' (the 'View #1'), activated by pressing the <1> key.
 */
int scene=0;

/* Forward prototypes for all functions of interest! */
void draw();
void initialize();
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);

/// The main function for the <i>'Example-004 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
    /* First, we export out an introductory message for this test on the standard output stream (cout)! */
    cout<<endl<<"\tThis is the 'Example-004' Test, based on the (Old Mode) OpenGL."<<endl;
    cout<<"\tIt draws the 'filled versions' of the following quadrilaterals in an OpenGL window:"<<endl<<endl;
    cout<<"\t\t0. the 'Quadrilateral #0' (in 'red') with vertices '(20,20,0)' - '(80,20,0)' - '(80,80,0)' - '(20,80,0)';"<<endl;
    cout<<"\t\t1. the 'Quadrilateral #1' (in 'green') with vertices '(120,120,0)' - '(180,120,0)' - '(180,180,0)' - '(120,180,0)';"<<endl<<endl;
    cout<<"\tby using the following orthographic projections (activated upon request by the user):"<<endl<<endl;
    cout<<"\t\t0. the ortographic viewing box '[0,100]' x '[0,100]' x '[-1,1]' (the 'View #0') is activated by pressing the <0> key. In this case, ";
    cout<<"only the 'Quadrilateral #0' is shown."<<endl;
    cout<<"\t\t1. The ortographic viewing box '[0,200]' x '[0,200]' x '[-1,1]' (the 'View #1') is activated by pressing the <1> key. In this case, ";
    cout<<"both the 'Quadrilateral #0' and the 'Quadrilateral #1' are shown."<<endl<<endl;
    cout<<"\tHere, the window of interest can be closed by pressing any among the <Q>, the <q>, and the <Esc> keys."<<endl<<endl;
    cout<<"\t----------------------------------------------------------------------------------------------------------------------------------------------------------";
    cout<<"------------------------------------------------------------------------------"<<endl<<endl;
    cout.flush();
    
    /* If we arrive here, then we can draw '2' quadrilaterals of interest by using the orthographic viewing box, requested by the user. */
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(480,480);
    glutCreateWindow("The 'Example-004' Test, based on the (Old Mode) OpenGL");
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
void resize(int w, int h)
{
    /* We update the projection and the modeling matrices! */
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(left_value,right_value,bottom_value,top_value,near_value,far_value);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/// This function initializes the scene in the OpenGL window of interest.
void initialize()
{
    /* We initialize all global and local variables for drawing the scene in the OpenGL window of interest! */
    left_value = 0.0;
    right_value = 100.0;
    bottom_value = 0.0;
    top_value = 100.0;
    near_value = -1.0;
    far_value = 1.0;
    scene=0;
    glClearColor(1.0, 1.0, 1.0, 0.0);
    cout<<"\tAt the beginning, the 'View #0', corresponding to the orthographic viewing box '[0,100]' x '[0,100]' x '[-1,1]', is applied to the scene.";
    cout<<endl<<endl;
    cout.flush();
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
    /* We are interested only in the <q> - <Q> - <Esc> - <0> - <1> keys. */
    switch (key)
    {
        case 'q':
            
            /* The user presses the <q> key, thus we can exit from this program! */
            cout<<endl<<"\t----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl<<endl;
            cout<<"\tThis program is closing correctly ... "<<endl<<endl;
            cout<<"\tPress the <RETURN> key to finish ... ";
            cout.flush();
            cin.get();
            #ifndef _MSC_VER
                cout << endl;
                cout.flush();
            #endif
            exit(EXIT_SUCCESS);
            break;
            
        case 'Q':
            
            /* The user presses the <Q> key, thus we can exit from this program! */
            cout<<endl<<"\t----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl<<endl;
            cout<<"\tThis program is closing correctly ... "<<endl<<endl;
            cout<<"\tPress the <RETURN> key to finish ... ";
            cout.flush();
            cin.get();
            #ifndef _MSC_VER
                cout << endl;
                cout.flush();
            #endif
            exit(EXIT_SUCCESS);
            break;
            
        case 27:
            
            /* The user presses the <Esc> key, thus we can exit from this program! */
            cout<<endl<<"\t----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl<<endl;
            cout<<"\tThis program is closing correctly ... "<<endl<<endl;
            cout<<"\tPress the <RETURN> key to finish ... ";
            cout.flush();
            cin.get();
            #ifndef _MSC_VER
                cout << endl;
                cout.flush();
            #endif
            exit(EXIT_SUCCESS);
            break;
            
        case '0':
            
            /* The user presses the <0> key, thus we exploit the orthographic viewing box '[0,100]' x '[0,100]' x '[-1,1]' (thus, the 'View #0'). */
            scene=0;
            left_value=0.0;
            right_value=100.0;
            bottom_value=0.0;
            top_value=100.0;
            near_value=-1.0;
            far_value=1.0;
            glutPostRedisplay();
            break;

        case '1':
            
            /* The user presses the <1> key, thus we exploit the orthographic viewing box '[0,200]' x '[0,200]' x '[-1,1]' (thus, the 'View #1'). */
            scene=1;
            left_value=0.0;
            right_value=200.0;
            bottom_value=0;
            top_value=200.0;
            near_value=-1;
            far_value=1.0;
            glutPostRedisplay();
            break;
            
        default:
            
            /* Other keys are not important for us! */
            break;
    }
}

/// This function draws the <i>'filled versions'</i> of <i>'2'</i> quadrilaterals (respectively, in <i>'red'</i> and in <i>'green'</i>) in the OpenGL window of interest by using the orthographic projection, chosen by the user.
void draw()
{
    /* We draw the 'filled versions' of '2' quadrilaterals (respectively, in 'red' and in 'green') in the OpenGL window of interest by using the orthographic projection, chosen by the user. */
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(left_value,right_value,bottom_value,top_value,near_value,far_value);
    glBegin(GL_POLYGON);
    glVertex3f(20.0, 20.0, 0.0);
    glVertex3f(80.0, 20.0, 0.0);
    glVertex3f(80.0, 80.0, 0.0);
    glVertex3f(20.0, 80.0, 0.0);
    glEnd();
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(120.0, 120.0, 0.0);
    glVertex3f(180.0, 120.0, 0.0);
    glVertex3f(180.0, 180.0, 0.0);
    glVertex3f(120.0, 180.0, 0.0);
    glEnd();
    glFlush();
    if(scene==0)
    {
        /* The 'View #0' is currently applied to the scene! */
        cout<<"\tThe 'View #0', corresponding to the orthographic viewing box '[0,100]' x '[0,100]' x '[-1,1]', is currently applied to the scene."<<endl;
        cout.flush();
    }
    else if(scene==1)
    {
        /* The 'View #1' is currently applied to the scene! */
        cout<<"\tThe 'View #1', corresponding to the orthographic viewing box '[0,200]' x '[0,200]' x '[-1,1]', is currently applied to the scene."<<endl;
        cout.flush();
    }
}

