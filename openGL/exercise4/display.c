#include "definitions.h"
#include "io.h"
#include <stdio.h>
#ifdef __linux__
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#elif _WIN32 || _WIN64
	#include "GL\freeglut.h"
#elif __APPLE__
	#include <GLUT/glut.h>
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#endif

/** EXTERNAL VARIABLES **/

extern GLdouble _window_ratio;
extern GLdouble _ortho_x_min, _ortho_x_max;
extern GLdouble _ortho_y_min, _ortho_y_max;
extern GLdouble _ortho_z_min, _ortho_z_max;

extern int obj_cam;

extern object3d *_first_object;
extern object3d *_selected_object;
extern camera *camara;
extern light *arrayLuces[8];
extern light *luzSeleccionada;
extern int flat_or_smooth;

int foco_debug = 0;
int i, j, x = 0,y = 0,z = 0;


/**
 * @brief Function to draw the axes
 */
void draw_axes() {
    /*Draw X axis*/
    glColor3f(KG_COL_X_AXIS_R, KG_COL_X_AXIS_G, KG_COL_X_AXIS_B);
    glBegin(GL_LINES);
    glVertex3d(KG_MAX_DOUBLE, 0, 0);
    glVertex3d(-1 * KG_MAX_DOUBLE, 0, 0);
    glEnd();
    /*Draw Y axis*/
    glColor3f(KG_COL_Y_AXIS_R, KG_COL_Y_AXIS_G, KG_COL_Y_AXIS_B);
    glBegin(GL_LINES);
    glVertex3d(0, KG_MAX_DOUBLE, 0);
    glVertex3d(0, -1 * KG_MAX_DOUBLE, 0);
    glEnd();
    /*Draw Z axis*/
    glColor3f(KG_COL_Z_AXIS_R, KG_COL_Z_AXIS_G, KG_COL_Z_AXIS_B);
    glBegin(GL_LINES);
    glVertex3d(0, 0, KG_MAX_DOUBLE);
    glVertex3d(0, 0, -1 * KG_MAX_DOUBLE);
    glEnd();
}


/**
 * @brief Callback reshape function. We just store the new proportions of the window
 * @param width New width of the window
 * @param height New height of the window
 */
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    /*  Take care, the width and height are integer numbers, but the ratio is a GLdouble so, in order to avoid
     *  rounding the ratio to integer values we need to cast width and height before computing the ratio */
    _window_ratio = (GLdouble) width / (GLdouble) height;
}

void establecerLuces() {
   // glLoadIdentity();
    int i = 0;
    for (i = 0; i < 8; i++){
        if (arrayLuces[i]->estado == 2) {
            glLightfv(arrayLuces[i]->info->numero, GL_AMBIENT, arrayLuces[i]->info->ambientLight);
            glLightfv(arrayLuces[i]->info->numero, GL_DIFFUSE, arrayLuces[i]->info->diffuseLight);
            glLightfv(arrayLuces[i]->info->numero, GL_SPECULAR, arrayLuces[i]->info->specularLight);
            glLightfv(arrayLuces[i]->info->numero, GL_POSITION, arrayLuces[i]->info->positionLight);
            glLightf(arrayLuces[i]->info->numero, GL_CONSTANT_ATTENUATION, arrayLuces[i]->info->spotAttenuation[0]);
            glLightf(arrayLuces[i]->info->numero, GL_LINEAR_ATTENUATION, arrayLuces[i]->info->spotAttenuation[1]);
            glLightf(arrayLuces[i]->info->numero, GL_QUADRATIC_ATTENUATION, arrayLuces[i]->info->spotAttenuation[2]);
            if (arrayLuces[i]->info->tipo == 2){
                glLightf(arrayLuces[i]->info->numero, GL_SPOT_CUTOFF, arrayLuces[i]->info->spotCutoff);
                glLightfv(arrayLuces[i]->info->numero, GL_SPOT_DIRECTION, arrayLuces[i]->info->spotDirection);
                glLightf(arrayLuces[i]->info->numero, GL_SPOT_EXPONENT, arrayLuces[i]->info->spotExponent);


            }
        }
    }
}

/**
 * @brief Callback display function
 */
void display(void) {
    GLint v_index, v, f;
    object3d *aux_obj = _first_object;

    /* Clear the screen */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Define the projection */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (camara->modo == 0) {
        glOrtho(camara->left * 100, camara->right * 100, camara->bottom * 100, camara->top * 100, camara->nearVal,
                camara->farVal);
    } else {
        glFrustum(camara->left, camara->right, camara->bottom, camara->top, camara->nearVal, camara->farVal);
    }

    /* Now we start drawing the object */
    glMatrixMode(GL_MODELVIEW);
    if (obj_cam == 0) {
        glLoadIdentity();
    } else {
        glLoadMatrixf(_selected_object->mat_rot_cam);
    }
    gluLookAt(camara->miCamara[0], camara->miCamara[1], camara->miCamara[2],
              camara->miCamara[4], camara->miCamara[5], camara->miCamara[6],
              camara->miCamara[8], camara->miCamara[9], camara->miCamara[10]);

    glGetFloatv(GL_MODELVIEW_MATRIX, camara->m);

    establecerLuces();
    
    if (flat_or_smooth) glShadeModel(GL_SMOOTH);
    else glShadeModel(GL_FLAT);

    /*First, we draw the axes*/
    draw_axes();

    /*Now each of the objects in the list*/
    while (aux_obj != 0) {
        glPushMatrix();
        /* Select the color, depending on whether the current object is the selected one or not */
        if (aux_obj == _selected_object) {
            if (!existeLuzEncendida()) glColor3f(KG_COL_SELECTED_R, KG_COL_SELECTED_G, KG_COL_SELECTED_B);
        } else {
            if (!existeLuzEncendida()) glColor3f(KG_COL_NONSELECTED_R, KG_COL_NONSELECTED_G, KG_COL_NONSELECTED_B);
        }

        if (aux_obj->material->matAmb != NULL) {
            glMaterialfv(GL_FRONT, GL_AMBIENT, aux_obj->material->matAmb);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, aux_obj->material->matDiff);
            glMaterialfv(GL_FRONT, GL_SPECULAR, aux_obj->material->matSpec);
            glMaterialf(GL_FRONT, GL_SHININESS, aux_obj->material->matShininess);            
        }

        /* Draw the object; for each face create a new polygon with the corresponding vertices */
        //glLoadIdentity();
        if (foco_debug && luzSeleccionada->info->tipo == 2){
            glBegin(GL_LINES);
                glVertex3fv(luzSeleccionada->info->positionLight);  
                glVertex3f(luzSeleccionada->info->positionLight[0] + 40 * luzSeleccionada->info->spotDirection[0],
                    luzSeleccionada->info->positionLight[1] + 40 * luzSeleccionada->info->spotDirection[1],
                    luzSeleccionada->info->positionLight[2] + 40 * luzSeleccionada->info->spotDirection[2]);
            glEnd();
        }

        glMultMatrixf(aux_obj->pila->m);

        for (f = 0; f < aux_obj->num_faces; f++) {
            glBegin(GL_POLYGON);
            
            if (!flat_or_smooth) glNormal3f(aux_obj->face_table[f].normal.x, aux_obj->face_table[f].normal.y, aux_obj->face_table[f].normal.z);

            for (v = 0; v < aux_obj->face_table[f].num_vertices; v++) {
                v_index = aux_obj->face_table[f].vertex_table[v];

                if (flat_or_smooth) glNormal3f(aux_obj->vertex_table[v_index].normal.x, aux_obj->vertex_table[v_index].normal.y, aux_obj->vertex_table[v_index].normal.z);

                glVertex3d(aux_obj->vertex_table[v_index].coord.x,
                           aux_obj->vertex_table[v_index].coord.y,
                           aux_obj->vertex_table[v_index].coord.z);
            }
            glEnd();
        }
        aux_obj = aux_obj->next;
        glPopMatrix();
    }

    if (foco_debug ) {
        glTranslatef(luzSeleccionada->info->positionLight[0],luzSeleccionada->info->positionLight[1],luzSeleccionada->info->positionLight[2]);
        glutSolidSphere(.25f,5,5);
    }
    glLineWidth(2.5);
    
    /*Do the actual drawing*/
    glFlush();
}
