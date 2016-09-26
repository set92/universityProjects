#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    float x,y,u,v;
} Vertex;

Vertex v1, v2, v3;
Vertex *aptr, *bptr, *mptr; // punteros al alto, bajo y medio
Vertex *iptr, /*!< Puntero al punto de entrada de la linea a dibujar */
*dptr; /*!< Puntero al punto de salida de la linea a dibujar */
Vertex *selectptoptr; /*!< Puntero al vertice seleccionado por el usuario */

int msaa = 0;
/**
 * Ordena los vertices usando 3 puntos, al final quedara en v1.y el mas bajo y en v3.y el mas alto
 */
static void sortByY() {
    Vertex *auxptr;

    aptr = &v3;
    mptr = &v2;
    bptr = &v1;

    if (mptr->y > aptr->y) {
        auxptr = mptr;
        mptr = aptr;
        aptr = auxptr;
    }
    // aptr y mptr estan ordenados correctamente
    if (bptr->y > mptr->y) {
        auxptr = mptr;
        mptr = bptr;
        bptr = auxptr;
    }
    // el bptr es el más bajo fijo!
    if (mptr->y > aptr->y) {
        auxptr = aptr;
        aptr = mptr;
        mptr = auxptr;
    }
}
/**
 * Devuelve el color que le corresponde al pixel marcado por el pto (u,v)
 * @param u Coordenada de mapeado del eje horizontal
 * @param v Coordenada de mapeado del eje vertical
 * @return Numero correspondiente al color
 */
float color(float u, float v) {
    int x,y;
    x = u/0.125;
    y = v/0.125;

    if( (x % 2) == 0 ) {
        if ( ( y % 2 ) == 0 ) {
            return (0.0);
        } else {
            return (1.0);
        }
    }else {
        if( (y % 2) == 0 ) {
            return (1.0);
        } else {
            return (0.0);
        }
    }
}
/**
 * Dibuja desde un pto de entrada del triangulo a uno de salida
 * @param line Altura a la que se va a dibujar la linea
 */
void dibujarLineas(float line){
    float slopeUX, slopeVX, u, v, val;

    slopeUX = ((dptr->u-iptr->u)/(dptr->x-iptr->x));
    slopeVX = ((dptr->v-iptr->v)/(dptr->x-iptr->x));
    u = iptr->u;
    v = iptr->v;
    for (float x = iptr->x; x < dptr->x; x++) {
        u += slopeUX;
        v += slopeVX;

        val = color(u, v);
        glColor3f(val, val,val );
        glBegin(GL_POINTS);
        glVertex2f(x, line);
        glEnd();
    }
}
/**
 * Drawing the 3 vertex with different colors
 */
static void dibujarVertices(){
    glPointSize(10.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0f,0.0f,0.0f);
    glVertex2f(bptr->x,bptr->y);
    glColor3f(0.0f,1.0f,0.0f);
    glVertex2f(mptr->x,mptr->y);
    glColor3f(0.0f,0.0f,1.0f);
    glVertex2f(aptr->x,aptr->y);
    glEnd();
}

void reshape(int width, int height) {
    // we ignore the params and always resize the window to
    glutReshapeWindow(500, 500);
}

static void draw(void) {
    float slope1, slope2, slopeU1, slopeU2, slopeV1, slopeV2;
    float line;
    Vertex c1,c2;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 500.0, 0.0, 500.0,-250.0, 250.0);
    if (msaa) glEnable(GL_MULTISAMPLE_ARB);
    else glDisable(GL_MULTISAMPLE_ARB);
    dibujarVertices();

    glPointSize(1.0f);
    glColor3f(1.0f,1.0f,1.0f);

    c1.x = bptr->x; c1.u = bptr->u; c1.v = bptr->v;     c2.x = bptr->x; c2.u = bptr->u; c2.v = bptr->v;

    slope1 = ((aptr->x-bptr->x)/(aptr->y-bptr->y));     slope2 = ((mptr->x-bptr->x)/(mptr->y-bptr->y));
    slopeU1 = ((aptr->u-bptr->u)/(aptr->y-bptr->y));    slopeU2 = ((mptr->u-bptr->u)/(mptr->y-bptr->y));
    slopeV1 = ((aptr->v-bptr->v)/(aptr->y-bptr->y));    slopeV2 = ((mptr->v-bptr->v)/(mptr->y-bptr->y));

    if (bptr->y == mptr->y) {
        c1.x = bptr->x; c1.u = bptr->u; c1.v = bptr->v;
        c2.x = mptr->x; c2.u = mptr->u; c2.v = mptr->v;
    }

    // El pto de entrada(c1) sera donde la pendiente este mas baja
    if (slope1 < slope2) {
        iptr = &c1;
        dptr = &c2;
    } else {
        iptr = &c2;
        dptr = &c1;
    }

    // We draw the lower side of the triangle until the slope changes
    for (line = bptr->y; line < mptr->y; line++, c1.x += slope1, c2.x += slope2,
         c1.u += slopeU1, c2.u += slopeU2, c1.v+=slopeV1, c2.v+=slopeV2) {
        dibujarLineas(line);
    }

    // Cambiamos la slope2 que era la pendiente mas pequeña a la siguiente pendiente
    slope2 = ((aptr->x-mptr->x)/(aptr->y-mptr->y));
    slopeU2 = ((aptr->u-mptr->u)/(aptr->y-mptr->y));
    slopeV2 = ((aptr->v-mptr->v)/(aptr->y-mptr->y));

    // Draw the upper side of the triangle
    for (line = mptr->y; line < aptr->y; line++, c1.x += slope1, c2.x += slope2,
         c1.u += slopeU1, c2.u += slopeU2, c1.v+=slopeV1, c2.v+=slopeV2) {
        dibujarLineas(line);
    }

    glutSwapBuffers();
}

static void keyboard (unsigned char key, int x, int y) {

    switch(key)	{
        case 98: // b
            selectptoptr = bptr;
            break;
        case 110: // n
            selectptoptr = mptr;
            break;
        case 109: // m
            selectptoptr = aptr;
            break;
        case 108: // l
            msaa = !msaa;
            if(msaa == 1)printf("msaa activado\n");
            else printf("msaa desactivado\n");
            glutPostRedisplay();
            break;
        case 27:  // <ESC>
            exit(0);
            break;
        default:
            printf("%d %c\n", key, key );
    }
    sortByY();
    glutPostRedisplay();
}

void SpecialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            selectptoptr->x -= 20.0f;
            break;
        case GLUT_KEY_RIGHT:
            selectptoptr->x += 20.0f;
            break;
        case GLUT_KEY_UP:
            selectptoptr->y += 20.0f;
            break;
        case GLUT_KEY_DOWN:
            selectptoptr->y -= 20.0f;
            break;
        default:
            printf("El codigo ASCII de la tecla pulsada es %d\n", key );
    }
    sortByY();
    glutPostRedisplay();
}

bool puntoCoorrecto(Vertex v){
    if(v.x<0 || v.x>500 || v.y<0 || v.y>500 ||
            v.u>1 || v.u<0 || v.v<0 || v.v>1) return false;
    else return true;
}

bool validarCoordenadas(){
    bool pt1 = puntoCoorrecto(v1);
    bool pt2 = puntoCoorrecto(v2);
    bool pt3 = puntoCoorrecto(v3);
    if(pt1 && pt2 && pt3) return true;
    else{
        printf("Hay algún valor erróneo. Mete los datos de nuevo\n");
        return false;
    }
}

bool pedirCoordsUsuario(){
    printf("Mete v1.x: ");    scanf("%f", &v1.x);
    printf("Mete v1.y: ");    scanf("%f", &v1.y);
    printf("Mete v1.u: ");    scanf("%f", &v1.u);
    printf("Mete v1.v: ");    scanf("%f", &v1.v);

    printf("Mete v2.x: ");    scanf("%f", &v2.x);
    printf("Mete v2.y: ");    scanf("%f", &v2.y);
    printf("Mete v2.u: ");    scanf("%f", &v2.u);
    printf("Mete v2.v: ");    scanf("%f", &v2.v);

    printf("Mete v3.x: ");    scanf("%f", &v3.x);
    printf("Mete v3.y: ");    scanf("%f", &v3.y);
    printf("Mete v3.u: ");    scanf("%f", &v3.u);
    printf("Mete v3.v: ");    scanf("%f", &v3.v);

    return validarCoordenadas();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowPosition(50, 25);
    glutInitWindowSize(500,500);
    glutCreateWindow("OpenGL");
    //v1.x=0.0f, v1.y=0.0f, v2.x=0.0f, v2.y=0.0f, v3.x=0.0f, v3.y=0.0f;
    //v1.u=0, v2.u=0; v3.u=0;
    //v1.v=0; v2.v=0; v3.v=0;

    bool coord = pedirCoordsUsuario();
    while(coord == false) coord = pedirCoordsUsuario();

    sortByY();
    selectptoptr = bptr;

    glutDisplayFunc(draw);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(SpecialKeys);
    glutReshapeFunc(reshape);

    //glutReshapeWindow(400,400);
    //printf("%s\n",glGetString(GL_RENDERER));

    glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
    glutMainLoop();
    return 0;
}
