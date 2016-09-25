#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

struct Vertex {
    float x,y,u,v;
};

struct Vertex v1, v2, v3;

//Quedara la y mas baja en v1.y, y la mas alta en v3.y
static void sortByY() {
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
        v3 = vAux;    }
}


static float elMasTxiki(float a, float b){
    if (a<b) return a;
    else return b;
}

static float elMasGrande(float a, float b){
    if (a<b) return b;
    else return a;
}

static char color(int x, int y){
    if((x % 2) == 0){
        if (( y % 2 ) == 0){
            return 'n';
        }
        else{
            return 'b';
        }
    }else{
        if((y % 2) == 0){
            return 'b';
        }
        else{
            return 'n';
        }
    }
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

    float inX, outX, x, line, slope1, slope2, slopeUY, slope2UY, inUV, outUV, u, v;
    char a;


    inX = v1.x;
    outX = v1.x;
    slope1 = ((v3.x-v1.x)/(v3.y-v1.y));
    slope2 = ((v2.x-v1.x)/(v2.y-v1.y));
    if (v1.y == v2.y){
        inX = v1.x;
        outX = v2.x;
    }


    inUV = v1.u;
    outUV = v3.u;
    slopeUY = ((v3.u-v1.u)/(v3.x-v1.x));
    slope2UY = ((v2.v-v1.v)/(v2.x-v1.x));


    u = inUV;
    v = outUV;
    for (line = v1.y; line < v2.y; line++, inX += slope1, outX += slope2) {
        printf("%f, %f\n",u,v);
        u += slopeUY;
        v += slope2UY;
        for (x = elMasTxiki(inX,outX); x < elMasGrande(inX,outX); x++) {

            a = color(u/0.125, v/0.125);
            if (a=='n') glColor3f(0.0f, 0.0f, 0.0f);
            if (a=='b') glColor3f(1.0f, 1.0f, 1.0f);
            glBegin(GL_POINTS);
            glVertex2f(x, line);
            glEnd();
        }
    }

    slope2=((v3.x-v2.x)/(v3.y-v2.y));
    slope2UY = ((v3.v-v2.v)/(v3.x-v2.x));

    for (line = v2.y; line < v3.y; line++, inX += slope1, outX += slope2) {
        u += slopeUY;
        v += slope2UY;
        printf("%f, %f, %f, %f\n",u,v,slopeUY,slope2UY);
        for (x = elMasTxiki(inX,outX); x < elMasGrande(inX,outX); x++ ) {
            //u += slopeUY;
            a = color(u/0.125, v/0.125);
            if (a=='n') glColor3f(0.0f, 0.0f, 0.0f);
            if (a=='b') glColor3f(1.0f, 1.0f, 1.0f);
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
    v1.x=0.0f, v1.y=0.0f, v2.x=0.0f, v2.y=500.0f, v3.x=500.0f, v3.y=0.0f;
    v1.u=0, v2.u=0;v3.u=1;
    v1.v=0; v2.v=1;v3.u=1;

    glutDisplayFunc(draw);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(SpecialKeys);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutMainLoop();
    return 0;
}
