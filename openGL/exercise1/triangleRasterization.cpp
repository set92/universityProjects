#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>


static float LOCAL_Red = 0.0f;

struct Vertex {
    float x,y;
} v1, v2, v3, vAux;

static void sortByY()
{
    if (v1.y > v2.y)
    {
        vAux = v1;
        v1 = v2;
        v2 = vAux;
    }
    if (v1.y > v3.y)
    {
        vAux = v1;
        v1 = v3;
        v3 = vAux;
    }
    if (v2.y > v3.y)
    {
        vAux = v2;
        v2 = v3;
        v3 = vAux;
    }
}

static void draw(void) {
    float line,x;
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 500.0, 0.0, 500.0,-250.0, 250.0);

    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_POINTS);
    v1.x=220.0f, v1.y=100.0f, v2.x=437.0f, v2.y=215.0f, v3.x=150.0f, v3.y=400.0f;
    sortByY();
    glColor3f(1.0f,0.0f,0.0f);
    glVertex3f(220.0f,100.0f,0.0f);
    glColor3f(0.0f,1.0f,0.0f);
    glVertex3f(437.0f,215.0f,0.0f);
    glColor3f(0.0f,0.0f,1.0f);
    glVertex3f(150.0f,400.0f,0.0f);
    glColor3f(1.0f,1.0f,1.0f);

    float in=v1.x, out=v1.x, slope1=((v2.x-v1.x)/(v2.y-v1.y)), slope2=((v3.x-v1.x)/(v3.y-v1.y));
    for (line = v1.y; line < v2.y; line++) {
        in += round(slope1);
        out += round(slope2);
        for (x = in; x < out; x++) {
            glBegin(GL_POINTS);
            glVertex2f(x,line);
            glEnd();
        }
    }

    slope2=((v3.x-v2.x)/(v3.y-v2.y));
    for (line = v2.y; line < v3.y; line++) {
        in += round(slope1);
        out += round(slope2);
        for (x = in; x < out; x++) {
            glBegin(GL_POINTS);
            glVertex2f(x,line);
            glEnd();
        }
    }
    glEnd();
    glFlush();
}

// This function will be called whenever the user pushes one key
static void keyboard (unsigned char key, int x, int y) {
    switch(key)	{
        case 'r':
            if ( LOCAL_Red > 0.01f ) LOCAL_Red -= 0.1f;
            printf ("red   : ");
            break;
        case 'R':
            if ( LOCAL_Red < 1.0f ) LOCAL_Red += 0.1f;
            printf ("red   : ");
            break;
        case 27:  // <ESC>
            exit( 0 );
            break;
        default:
            printf("%d %c\n", key, key );
    }

    printf ("(R = %f) (G = %f) (B = %f) \n", LOCAL_Red, LOCAL_Red, LOCAL_Red );
    // The screen must be drawn to show the new values
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    //Configure Window Position
    glutInitWindowPosition(50, 25);
    //Configure Window Size
    glutInitWindowSize(500,500);
    //Create Window
    glutCreateWindow("OpenGL");
    //Llamadas a las funciones responsables
    glutDisplayFunc(draw);
    glutKeyboardFunc(keyboard);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // Loop require by OpenGL
    glutMainLoop();
    return 0;
}