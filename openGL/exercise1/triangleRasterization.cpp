#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

struct Vertex {
    float x,y;
};

struct Vertex v1, v2, v3;

/**
 * Ordena los vertices usando 3 puntos, al final quedara en v1.y el mas bajo y en v3.y el mas alto
 */
static void sortByY() {
    printf("%f,%f,%f,%f,%f,%f\n",v1.x,v1.y,v2.x,v2.y,v3.x,v3.y );
    struct Vertex vAux;
    if (v1.y > v2.y) {
        vAux = v1;
        v1 = v2;
        v2 = vAux;
    }
    if (v1.y > v3.y) {
        vAux = v1;
        v1 = v3;
        v3 = vAux;
    }
    if (v2.y > v3.y) {
        vAux = v2;
        v2 = v3;
        v3 = vAux;
    }
    printf("%f,%f,%f,%f,%f,%f\n",v1.x,v1.y,v2.x,v2.y,v3.x,v3.y );
}
static float elmastxiki(float a, float b){
    if (a < b) return a;
    else return b;
}

static float elmasgrande(float a, float b){
    if (a < b) return b;
    else return a;
}

static void draw(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 500.0, 0.0, 500.0,-250.0, 250.0);

    sortByY();

    glPointSize(10.0f);
    glBegin(GL_POINTS);
        glColor3f(1.0f,0.0f,0.0f);
        glVertex2f(v1.x,v1.y);
        glColor3f(0.0f,1.0f,0.0f);
        glVertex2f(v2.x,v2.y);
        glColor3f(0.0f,0.0f,1.0f);
        glVertex2f(v3.x,v3.y);
    glEnd();

    glPointSize(1.0f);
    glColor3f(1.0f,1.0f,1.0f);

    float in = v1.x, out = v1.x, x, line, slope1 = ((v3.x-v1.x)/(v3.y-v1.y)), slope2 = ((v2.x-v1.x)/(v2.y-v1.y));

    if (v1.y==v2.y){
        in=v1.x;
        out=v2.x;
    }
    for (line = v1.y; line < v2.y; line++, in += slope1, out += slope2) {
        for (x = elmastxiki(in, out); x < elmasgrande(in,out); x++) {
            glBegin(GL_POINTS);
                glVertex2f(x, line);
            glEnd();
        }
    }

    slope2=((v3.x-v2.x)/(v3.y-v2.y));

    for (;line < v3.y; line++, in += slope1, out += slope2) {
        for (x = elmastxiki(in, out); x < elmasgrande(in,out); x++ ) {
            glBegin(GL_POINTS);
                glVertex2f(x,line);
            glEnd();
        }
    }
    glFlush();
}

static void keyboard (unsigned char key, int x, int y) {
  	switch(key)	{
        case 112: // P
            v1.x += 20.0f;
            printf("%f\n", v1.x);
            break;
      	case 27:  // <ESC>
      		exit(0);
      		break;
      	default:
      		printf("%d %c\n", key, key );
  	}
  	glutPostRedisplay();
}

void SpecialKeys(int key, int x, int y) {
    switch (key) {
		case GLUT_KEY_LEFT:
            v1.x -= 20.0f;
            //printf("%f\n", v1.x);
            break;
		case GLUT_KEY_RIGHT:
            v1.x += 20.0f;
			break;
		case GLUT_KEY_UP:
            v1.y += 20.0f;
			break;
		case GLUT_KEY_DOWN:
            v1.y -= 20.0f;
			break;
	}
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(50, 25);
    glutInitWindowSize(500,500);
    glutCreateWindow("OpenGL");

    v1.x=220.0f, v1.y=100.0f, v2.x=437.0f, v2.y=100.0f, v3.x=150.0f, v3.y=400.0f;

    glutDisplayFunc(draw);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(SpecialKeys);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutMainLoop();
    return 0;
}
