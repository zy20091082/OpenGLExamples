/*********************************************************************************************************************************************************
 * David Canino (canino.david@gmail.com)
 *
 * Main website (GitHub): http://github.com/davidcanino/OpenGLExamples
 *
 * Last update: January 2018
 *
 * main.cpp - the main function for the 'Example-003 (Old Mode)' Test.
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
 * -) the 'left_value' global variable indicates the minimum value of the range along the 'x'-axis;
 * -) the 'right_value' global variable indicates the maximum value of the range along the 'x'-axis;
 * -) the 'bottom_value' global variable indicates the minimum value of the range along the 'y'-axis;
 * -) the 'top_value' global variable indicates the maximum value of the range along the 'y'-axis;
 * -) the '-far_value' global variable indicates the minimum value of the range along the 'z'-axis;
 * -) the '-near_value' global variable indicates the maximum value of the range along the 'z'-axis.
 */
GLfloat left_value, right_value, bottom_value, top_value, near_value, far_value;

// The orthographic projection to be applied for rendering the scene.
/*
 * The value of this global variable indicates what orthographic viewing box must be applied to the scene by following these conventions:
 *
 * -) 0: it corresponds to the orthographic viewing box '[0,100]' x '[0,100]' x '[-1,1]' (the 'View #0'), activated by pressing the '0' key;
 * -) 1: it corresponds to the orthographic viewing box '[-100,100]' x '[-100,100]' x '[-1,1]' (the 'View #1'), activated by pressing the '1' key;
 * -) 2: it corresponds to the orthographic viewing box '[20,80]' x '[20,80]' x '[-1,1]' (the 'View #2'), activated by pressing the '2' key;
 * -) 3: it corresponds to the orthographic viewing box '[0,100]' x '[0,100]' x '[-2,5]' (the 'View #3'), activated by pressing the '3' key;
 * -) 4: it corresponds to the orthographic viewing box '[0,200]' x '[0,200]' x '[-1,1]' (the 'View #4'), activated by pressing the '4' key;
 * -) 5: it corresponds to the orthographic viewing box '[120,200]' x '[90,200]' x '[-1,3]' (the 'View #5'), activated by pressing the '5' key.
 */
int scene=0;

/* Forward prototypes for all functions of interest! */
void draw(void);
void initialize(void);
void resize(int w,int h);
void manageKeys(unsigned char key, int x, int y);

// The main function for the <i>'Example-003 (Old Mode)'</i> Test.
int main(int argc,char **argv)
{
    /* First, we export out an introductory message for this test on the standard output stream (cout)! */
    cout<<endl<<"\tThis is the 'Example-003' Test, based on the (Old Mode) OpenGL."<<endl;
    cout<<"\tIt draws the 'filled version' of the quadrilateral (in 'red') with vertices '(30,20,0)' - '(80,20,0)' - '(80,80,0)' - '(20,80,0)' in an OpenGL window, ";
    cout<<"and provides a basic interaction mechanism with the user. In fact, the user can"<<endl;
    cout<<"\tapply (upon request) the following orthographic projections to the scene:"<<endl<<endl;
    cout<<"\t\t0. the orthographic viewing box '[0,100]' x '[0,100]' x '[-1,1]' (the 'View #0') is activated by pressing the '0' key. This is the ";
    cout<<"standard orthographic viewing box of the scene, and the quadrilateral is completely rendered"<<endl;
    cout<<"\t\t   in the middle of the scene."<<endl<<endl;
    cout<<"\t\t1. The orthographic viewing box '[-100,100]' x '[-100,100]' x '[-1,1]' (the 'View #1') is activated by pressing the '1' key. The ";
    cout<<"reduced and scaled quadrilateral is completely rendered in the top right corner of the scene."<<endl<<endl;
    cout<<"\t\t2. The orthographic viewing box '[20,80]' x '[20,80]' x '[-1,1]' (the 'View #2') is activated by pressing the '2' key. This ";
    cout<<"orthographic viewing box does not cover entirely the ortographic projection of the quadrilateral,"<<endl;
    cout<<"\t\t   which is partially rendered in the middle of the scene."<<endl<<endl;
    cout<<"\t\t3. The orthographic viewing box '[0,100]' x '[0,100]' x '[-2,5]' (the 'View #3') is activated by pressing the '3' key. The ";
    cout<<"quadrilateral is completely rendered in the middle of the scene as like as when the 'View #0' is"<<endl;
    cout<<"\t\t   exploited, even if this ortographic viewing box is different."<<endl<<endl;
    cout<<"\t\t4. The orthographic viewing box '[0,200]' x '[0,200]' x '[-1,1]' (the 'View #4') is activated by pressing the '4' key. The reduced and ";
    cout<<"scaled quadrilateral is completely rendered in the bottom left corner of the scene."<<endl<<endl;
    cout<<"\t\t5. The orthographic viewing box '[120,200]' x '[90,200]' x '[-1,3]' (the 'View #5') is activated by pressing the '5' key. This ";
    cout<<"orthographic viewing box does not intersect the orthographic projection of the quadrilateral,"<<endl;
    cout<<"\t\t   which is not rendered at all."<<endl<<endl;
    cout<<"\tLikewise, the window of interest can be closed by pressing any among the 'Q', the 'q', and the 'Esc' keys."<<endl<<endl;
    cout<<"\t----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl<<endl;
    cout.flush();
    
    /* If we arrive here, then we can draw the desired scene in the OpenGL windows of interest! Specifically, we can draw the polygon of interest by using the rendering settings, requested by the user. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
    glutInitWindowPosition(50, 25);
    glutInitWindowSize(480, 480);
    glutCreateWindow("The 'Example-003' Test, based on the (Old Mode) OpenGL");
    glutDisplayFunc(draw);
    glutReshapeFunc(resize);
    glutKeyboardFunc(manageKeys);
    glewExperimental = GL_TRUE;
    glewInit();
    initialize();
    glutMainLoop();
    return EXIT_SUCCESS;
}

// This function initializes the scene in the OpenGL window of interest.
void initialize()
{
    /* We initialize all global and local variables for drawing the scene in the OpenGL window of interest! */
    left_value = 0.0;
    right_value = 100.0;
    bottom_value = 0.0;
    top_value = 100.0;
    near_value = -1.0;
    far_value = 1.0;
    glClearColor(1.0, 1.0, 1.0, 0.0);
    scene=0;
    cout<<"\tAt the beginning, the 'View #0', corresponding to the orthographic viewing box '[0,100]' x '[0,100]' x '[-1,1]', is applied to the scene.";
    cout<<endl<<endl;
    cout.flush();
}

// This function updates the viewport for the scene when it is resized. */
void resize(int w, int h)
{
    /* We update the projection and the modeling matrices! */
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(left_value, right_value, bottom_value, top_value, near_value, far_value);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/// This function is the keyboard input processing routine for the OpenGL window of interest.
void manageKeys(unsigned char key, int x, int y)
{
    /* We are interested only in the 'q' - 'Q' - 'Esc' - '0' - '1' - '2' - '3' - '4' - '5' keys. */
    switch (key)
    {
        case 'q':
            
            /* The user presses the 'q' key, thus we can exit from this program! */
            cout<<endl<<"\t----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl<<endl;
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
            cout<<endl<<"\t----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl<<endl;
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
            cout<<endl<<"\t----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl<<endl;
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
            
        case '0':
            
            /* The user presses the '0' key, thus we exploit the orthographic viewing box '[0,100]' x '[0,100]' x '[-1,1]' (thus, the 'View #0'). */
            scene=0;
            left_value = 0.0;
            right_value = 100.0;
            bottom_value = 0.0;
            top_value = 100.0;
            near_value = -1.0;
            far_value = 1.0;
            glutPostRedisplay();
            break;
        
        case '1':
            
            /* The user presses the '1' key, thus we exploit the orthographic viewing box '[-100,100]' x '[-100,100]' x '[-1,1]' (thus, the 'View #1'). */
            scene=1;
            left_value = -100.0;
            right_value = 100.0;
            bottom_value = -100.0;
            top_value = 100.0;
            near_value = -1.0;
            far_value = 1.0;
            glutPostRedisplay();
            break;
            
        case '2':
            
            /* The user presses the '2' key, thus we exploit the orthographic viewing box '[20,80]' x '[20,80]' x '[-1,1]' (thus, the 'View #2'). */
            scene=2;
            left_value = 20;
            right_value = 80;
            bottom_value = 20;
            top_value = 80;
            near_value = -1.0;
            far_value = 1.0;
            glutPostRedisplay();
            break;
            
        case '3':
            
            /* The user presses the '3' key, thus we exploit the orthographic viewing box '[0,100]' x '[0,100]' x '[-2,5]' (thus, the 'View #3'). */
            scene=3;
            left_value = 0;
            right_value = 100;
            bottom_value = 0;
            top_value = 100;
            near_value = -2.0;
            far_value = 5.0;
            glutPostRedisplay();
            break;
        
        case '4':
            
            /* The user presses the '4' key, thus we exploit the orthographic viewing box '[0,200]' x '[0,200]' x '[-1,1]' (thus, the 'View #4'). */
            scene=4;
            left_value = 0;
            right_value = 200;
            bottom_value = 0;
            top_value = 200;
            near_value = -1.0;
            far_value = 1.0;
            glutPostRedisplay();
            break;
        
        case '5':
            
            /* The user presses the '5' key, thus we exploit the orthographic viewing box '[120,200]' x '[90,200]' x '[-1,3]' (thus, the 'View #5'). */
            scene=5;
            left_value = 120;
            right_value = 200;
            bottom_value = 90;
            top_value = 200;
            near_value = -1.0;
            far_value = 3.0;
            glutPostRedisplay();
            break;
        
        default:

            /* Other keys are not important for us! */
            break;
    }
}

// This function draws the <i>'filled version'</i> of a quadrilateral (in <i>'red'</i>) in the OpenGL window of interest by using the orthographic projection, chosen by the user.
void draw()
{
    /* We draw the 'filled version' of a quadrilateral (in 'red') in the OpenGL window of interest by using the orthographic projection, chosen by the user. */
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(left_value, right_value, bottom_value, top_value, near_value, far_value);
    glBegin(GL_POLYGON);
    glVertex3f(30.0, 20.0, 0.0);
    glVertex3f(80.0, 20.0, 0.0);
    glVertex3f(80.0, 80.0, 0.0);
    glVertex3f(20.0, 80.0, 0.0);
    glEnd();
    glFlush();
    switch(scene)
    {
        case 0:
            
            /* The 'View #0' is currently applied to the scene. */
            cout<<"\tThe 'View #0', corresponding to the orthographic viewing box '[0,100]' x '[0,100]' x '[-1,1]', is currently applied to the scene."<<endl;
            cout.flush();
            break;
            
        case 1:
            
            /* The 'View #1' is currently applied to the scene. */
            cout<<"\tThe 'View #1', corresponding to the orthographic viewing box '[-100,100]' x '[-100,100]' x '[-1,1]', is currently applied to the scene."<<endl;
            cout.flush();
            break;
            
        case 2:
            
            /* The 'View #2' is currently applied to the scene. */
            cout<<"\tThe 'View #2', corresponding to the orthographic viewing box '[20,80]' x '[20,80]' x '[-1,1]', is currently applied to the scene."<<endl;
            cout.flush();
            break;
            
        case 3:
            
            /* The 'View #3' is currently applied to the scene. */
            cout<<"\tThe 'View #3', corresponding to the orthographic viewing box '[0,100]' x '[0,100]' x '[-2,5]', is currently applied to the scene."<<endl;
            cout.flush();
            break;
            
        case 4:
            
            /* The 'View #4' is currently applied to the scene. */
            cout<<"\tThe 'View #4', corresponding to the orthographic viewing box '[0,200]' x '[0,200]' x '[-1,1]', is currently applied to the scene."<<endl;
            cout.flush();
            break;
            
        case 5:
            
            /* The 'View #5' is currently applied to the scene. */
            cout<<"\tThe 'View #5', corresponding to the orthographic viewing box '[120,200]' x '[90,200]' x '[-1,3]', is currently applied to the scene."<<endl;
            cout.flush();
            break;
            
        default:
            
            /* Something is wrong here. We do nothing! */
            break;
    }
}

