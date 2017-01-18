#include <stdio.h>
#include "display.h"
#include "io.h"
#include "definitions.h"

#ifdef __linux__
    #include <GL/glut.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
#elif __APPLE__
    #include <GLUT/glut.h>
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#endif

/** GLOBAL VARIABLES **/

GLdouble _window_ratio;                     /*Control of window's proportions */
GLdouble _ortho_x_min, _ortho_x_max;         /*Variables for the control of the orthographic projection*/
GLdouble _ortho_y_min, _ortho_y_max;        /*Variables for the control of the orthographic projection*/
GLdouble _ortho_z_min, _ortho_z_max;         /*Variables for the control of the orthographic projection*/

object3d *_first_object = 0;                /*List of objects*/
object3d *_selected_object = 0;            /*Object currently selected*/

camera *camara;
camera *first_camara;

/** GENERAL INITIALIZATION **/
void initialization() {

    /*Initialization of all the variables with the default values*/
    _ortho_x_min = KG_ORTHO_X_MIN_INIT;
    _ortho_x_max = KG_ORTHO_X_MAX_INIT;
    _ortho_y_min = KG_ORTHO_Y_MIN_INIT;
    _ortho_y_max = KG_ORTHO_Y_MAX_INIT;
    _ortho_z_min = KG_ORTHO_Z_MIN_INIT;
    _ortho_z_max = KG_ORTHO_Z_MAX_INIT;

    _window_ratio = (GLdouble) KG_WINDOW_WIDTH / (GLdouble) KG_WINDOW_HEIGHT;

    /*Definition of the background color*/
    glClearColor(KG_COL_BACK_R, KG_COL_BACK_G, KG_COL_BACK_B, KG_COL_BACK_A);

    /*Definition of the method to draw the objects*/
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //Inicializamos la cámara:

    first_camara = (camera *) malloc(sizeof(camera));
    camara = (camera *) malloc(sizeof(camera));

    first_camara->pertenece_a_objeto = 0;

    first_camara->left = -0.1;
    first_camara->right = 0.1;
    first_camara->bottom = -0.1;
    first_camara->top = 0.1;
    first_camara->nearVal = 0.1;
    first_camara->farVal = 20000;

    first_camara->modo = 1;

    first_camara->miCamara[0] = 5;
    first_camara->miCamara[1] = 5;
    first_camara->miCamara[2] = 5;
    first_camara->miCamara[3] = 1;
    first_camara->miCamara[4] = 0;
    first_camara->miCamara[5] = 0;
    first_camara->miCamara[6] = 0;
    first_camara->miCamara[7] = 1;
    first_camara->miCamara[8] = 0;
    first_camara->miCamara[9] = 1;
    first_camara->miCamara[10] = 0;
    first_camara->miCamara[11] = 0;
    first_camara->miCamara[12] = 0;
    first_camara->miCamara[13] = 0;
    first_camara->miCamara[14] = 0;
    first_camara->miCamara[15] = 1;

    first_camara->next = NULL;
    first_camara->prev = NULL;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(first_camara->miCamara[0], first_camara->miCamara[1], first_camara->miCamara[2],
              first_camara->miCamara[4], first_camara->miCamara[5], first_camara->miCamara[6],
              first_camara->miCamara[8], first_camara->miCamara[9], first_camara->miCamara[10]);

    glGetFloatv(GL_MODELVIEW_MATRIX, first_camara->m);

    camara = first_camara;
}

/** MAIN FUNCTION **/
int main(int argc, char **argv) {

    /*First of all, print the help information*/
    print_help();

    /* glut initializations */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(KG_WINDOW_WIDTH, KG_WINDOW_HEIGHT);
    glutInitWindowPosition(KG_WINDOW_X, KG_WINDOW_Y);
    glutCreateWindow(KG_WINDOW_TITLE);

    /* set the callback functions */
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(SpecialKeys);

    /* this initialization has to be AFTER the creation of the window */
    initialization();

    /* start the main loop */
    glutMainLoop();
    return 0;
}
