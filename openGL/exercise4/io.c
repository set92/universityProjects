#include "definitions.h"
#include "load_obj.h"
#include "stack2.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

#ifdef __linux__

#include <GL/glut.h>

#elif _WIN32 || _WIN64
#include "GL\freeglut.h"
#elif __APPLE__
#include <GLUT/glut.h>
#include "io.h"
#endif

extern object3d *_first_object;
extern object3d *_selected_object;
extern camera *first_camara;
extern camera *camara;
extern light *arrayLuces[8];
extern int flat_or_smooth;
extern int foco_debug;

int estado = 0; //0-> nada seleccionado
int cont = 0;
int mov = 0; //0-> no se mueve,  1-> transformaciones objeto, 2-> transformaciones camara, 3-> transformaciones luz
int modo_c = 0; // 0-> vuelo, 1-> analisis
int glob_loc = 0; //0-> local, 1-> global
int obj_cam = 0; //0-> el objeto no es la cámara, 1-> el objeto es la cámara
int transf_luz = 0; //0-> Transformaciones locales, 1-> Transformaciones globales
int i, num; //Para iterar el vector.

extern light *luzSeleccionada; //inicialmente la luz seleccionada es el sol.
extern material *mat[4];
extern GLdouble _ortho_x_min, _ortho_x_max;
extern GLdouble _ortho_y_min, _ortho_y_max;
extern GLdouble _ortho_z_min, _ortho_z_max;

/**
 * @brief This function just prints information about the use
 * of the keys
 */
void print_help() {
    printf("Practica 2 GC :Gráficos por computador\n");
    printf("Transformaciones geométricas\n\n");

    printf("Creado por: Cristina Mayor y Sergio Tobal  \n");
    printf("Fecha: Octubre, 2016 \n");
    printf("\n\n");
    printf("Resumen de funciones \n");
    printf("<?>\t\t Lanza esta ayuda. \n");
    printf("<ESC>\t\t Salir del programa. \n");
    printf("<F>\t\t Cargar objeto.\n");
    printf("<TAB>\t\t Moverse entre los objetos cargados en escena.\n");
    printf("<SUPR>\t\t Borrar el objeto seleccionado.\n");
    printf("<CTRL + ->\t Acercar zoom.\n");
    printf("<CTRL + +>\t Alejar zoom.\n");
    printf("<M,m>\t\t Activar traslación.\n");
    printf("<B,b>\t\t Activar rotación.\n");
    printf("<T,t>\t\t Activar escalado.\n");
    printf("<G,g>\t\t Activar transformaciones globales.\n");
    printf("<L,l>\t\t Activar transformaciones locales.\n");
    printf("<U,u>\t\t Deshacer.\n");
    printf("<R,r>\t\t Rehacer.\n");
    printf("<UP>\t\t Trasladar +Y; Escalar + Y; Rotar +X.\n");
    printf("<DOWN>\t\t Trasladar -Y; Escalar - Y; Rotar -X.\n");
    printf("<RIGHT>\t\t Trasladar +X; Escalar + X; Rotar +Y.\n");
    printf("<LEFT>\t\t Trasladar -X; Escalar - X; Rotar -Y.\n");
    printf("<AVPAG>\t\t Trasladar +Z; Escalar + Z; Rotar +Z.\n");
    printf("<REPAG>\t\t Trasladar -Z; Escalar - Z; Rotar -Z.\n");
    printf("<+>\t\t Escalar + en todos los ejes del objeto.\n");
    printf("<->\t\t Escalar -  en todos los ejes del objeto.\n");
    printf("\n\n");
}

void insertarCamara(struct camera *cam) {
    struct camera *aux = first_camara;
    while ((aux != NULL) && (aux->next != NULL)) {
        aux = aux->next;
    }
    aux->next = cam;
    cam->prev = aux;
}

void actualizarCamara() {
    _selected_object->camara->miCamara[0] = _selected_object->pila->m[12];
    _selected_object->camara->miCamara[1] = _selected_object->pila->m[13];
    _selected_object->camara->miCamara[2] = _selected_object->pila->m[14];

    _selected_object->camara->miCamara[4] = _selected_object->pila->m[12] + _selected_object->pila->m[8];
    _selected_object->camara->miCamara[5] = _selected_object->pila->m[13] + _selected_object->pila->m[9];
    _selected_object->camara->miCamara[6] = _selected_object->pila->m[14] + _selected_object->pila->m[10];

    _selected_object->camara->miCamara[8] = _selected_object->pila->m[4];
    _selected_object->camara->miCamara[9] = _selected_object->pila->m[5];
    _selected_object->camara->miCamara[10] = _selected_object->pila->m[6];

}

void inicializarCamara() {
    _selected_object->camara->pertenece_a_objeto = 1;

    _selected_object->camara->left = -0.1;
    _selected_object->camara->right = 0.1;
    _selected_object->camara->bottom = -0.1;
    _selected_object->camara->top = 0.1;
    _selected_object->camara->nearVal = 0.1;
    _selected_object->camara->farVal = 20000;

    _selected_object->camara->modo = 1;

    _selected_object->camara->miCamara[0] = _selected_object->pila->m[12];
    _selected_object->camara->miCamara[1] = _selected_object->pila->m[13];
    _selected_object->camara->miCamara[2] = _selected_object->pila->m[14];
    _selected_object->camara->miCamara[3] = 1;

    _selected_object->camara->miCamara[4] = _selected_object->pila->m[12] + _selected_object->pila->m[8];
    _selected_object->camara->miCamara[5] = _selected_object->pila->m[13] + _selected_object->pila->m[9];
    _selected_object->camara->miCamara[6] = _selected_object->pila->m[14] + _selected_object->pila->m[10];
    _selected_object->camara->miCamara[7] = 1;

    _selected_object->camara->miCamara[8] = _selected_object->pila->m[4];
    _selected_object->camara->miCamara[9] = _selected_object->pila->m[5];
    _selected_object->camara->miCamara[10] = _selected_object->pila->m[6];
    _selected_object->camara->miCamara[11] = 0;

    _selected_object->camara->miCamara[12] = 0;
    _selected_object->camara->miCamara[13] = 0;
    _selected_object->camara->miCamara[14] = 0;
    _selected_object->camara->miCamara[15] = 1;

    _selected_object->camara->prev = NULL;
    _selected_object->camara->next = NULL;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glGetFloatv(GL_MODELVIEW_MATRIX, _selected_object->mat_rot_cam);
}

void calcularNormales(object3d *optr) {
    int ind1, ind2, ind3, i, j;
    double x1, y1, z1, x2, y2, z2;

    for (i = 0; i < optr->num_vertices; i++) {//poner a 0 el vector normal del vertice 0 0 0
        optr->vertex_table->normal.x = 0;
        optr->vertex_table->normal.y = 0;
        optr->vertex_table->normal.z = 0;

    }

    for (i = 0; i < optr->num_faces; i++) {
        ind1 = optr->face_table[i].vertex_table[0];
        ind2 = optr->face_table[i].vertex_table[1];
        ind3 = optr->face_table[i].vertex_table[2];

        x1 = optr->vertex_table[ind2].coord.x - optr->vertex_table[ind1].coord.x;
        y1 = optr->vertex_table[ind2].coord.y - optr->vertex_table[ind1].coord.y;
        z1 = optr->vertex_table[ind2].coord.z - optr->vertex_table[ind1].coord.z;

        x2 = optr->vertex_table[ind3].coord.x - optr->vertex_table[ind1].coord.x;
        y2 = optr->vertex_table[ind3].coord.y - optr->vertex_table[ind1].coord.y;
        z2 = optr->vertex_table[ind3].coord.z - optr->vertex_table[ind1].coord.z;

        optr->face_table[i].normal.x = (y1 * z2) - (z1 * y2);
        optr->face_table[i].normal.y = (z1 * x2) - (x1 * z2);
        optr->face_table[i].normal.z = (x1 * y2) - (y1 * x2);

        for (j = 0; j < optr->face_table[i].num_vertices; j++) {
            ind1 = optr->face_table[i].vertex_table[j];

            optr->vertex_table[ind1].normal.x += optr->face_table[i].normal.x;
            optr->vertex_table[ind1].normal.y += optr->face_table[i].normal.y;
            optr->vertex_table[ind1].normal.z += optr->face_table[i].normal.z;

            //calcular vector normal del poligono mediante productor vectorial
        }
    }
	/* For evitado por GL_NORMALIZE
    for (i = 0; i < optr->num_vertices; i++) {

    }
    */

}

void actualizarFoco() {
    if (_selected_object) {
        arrayLuces[2]->info->positionLight[0] = _selected_object->pila->m[12];
        arrayLuces[2]->info->positionLight[1] = _selected_object->pila->m[13];
        arrayLuces[2]->info->positionLight[2] = _selected_object->pila->m[14];
        arrayLuces[2]->info->positionLight[3] = 1.0;

        arrayLuces[2]->info->spotDirection[0] = _selected_object->pila->m[8];
        arrayLuces[2]->info->spotDirection[1] = _selected_object->pila->m[9];
        arrayLuces[2]->info->spotDirection[2] = _selected_object->pila->m[10];
    }
}

void copiarContenidoArray(GLfloat matrizOrigen[4], GLfloat matrizDestino[4]) {
    matrizDestino[0] = matrizOrigen[0];
    matrizDestino[1] = matrizOrigen[1];
    matrizDestino[2] = matrizOrigen[2];
    matrizDestino[3] = matrizOrigen[3];
}

void opcionSuprimir(object3d *auxiliar_object) {
    /*Erasing an object depends on whether it is the first one or not*/
    if (_first_object != 0)
        if (obj_cam == 1) {
            if (_selected_object->camara->next == NULL) {
                _selected_object->camara->prev->next = NULL;
                camara = first_camara;
            } else {
                _selected_object->camara->prev->next = _selected_object->camara->next;
                _selected_object->camara->next->prev = _selected_object->camara->prev;
                camara = _selected_object->camara->next;
            }
        }

    if (_selected_object == _first_object) {
        /*To remove the first object we just set the first as the current's next*/
        _first_object = _first_object->next;
        /*Once updated the pointer to the first object it is save to free the memory*/
        free(_selected_object);
        /*Finally, set the selected to the new first one*/
        _selected_object = _first_object;
    } else {
        /*In this case we need to get the previous element to the one we want to erase*/
        auxiliar_object = _first_object;
        while (auxiliar_object->next != _selected_object) {
            auxiliar_object = auxiliar_object->next;
        }

        /*Now we bypass the element to erase*/
        auxiliar_object->next = _selected_object->next;
        /*free the memory*/
        free(_selected_object);
        /*and update the selection*/
        _selected_object = auxiliar_object;
    }
    actualizarFoco();
}


void seleccionarMaterial(int num) {
    if (_selected_object) {
        copiarContenidoArray(mat[num - 1]->matAmb, _selected_object->material->matAmb);
        copiarContenidoArray(mat[num - 1]->matDiff, _selected_object->material->matDiff);
        copiarContenidoArray(mat[num - 1]->matSpec, _selected_object->material->matSpec);
        _selected_object->material->matShininess = mat[num - 1]->matShininess;
    } else {
        printf("No se ha seleccionado ningun objeto\n");
    }
}

void onOffIluminacion() {
    if (glIsEnabled(GL_LIGHTING)) {
        printf("Lightning desactivado\n");
        glDisable(GL_LIGHTING);
    } else {
        printf("Lightning activado\n");
        glEnable(GL_LIGHTING);
    }
}

/**
 * @brief Callback function to control the basic keys
 * @param key Key that has been pressed
 * @param x X coordinate of the mouse pointer when the key was pressed
 * @param y Y coordinate of the mouse pointer when the key was pressed
 */
void keyboard(unsigned char key, int x, int y) {
    char *fname = malloc(sizeof(char) * 128); /* Note that scanf adds a null character at the end of the vector*/
    int read = 0;
    object3d *auxiliar_object = 0;
    GLdouble wd, he, midx, midy;
    float a, b, c;
    int type;
    switch (key) {
        case 'f':
        case 'F':
            /*Ask for file*/
            printf("%s", KG_MSSG_SELECT_FILE);
            scanf("%s", fname);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            printf("0\n");
/*
			#ifdef __linux__
	            if (cont == 0) {
	                fname = "objektuak/abioia.obj";
	                cont = 1;
	            } else fname = "objektuak/logoehu_ona.obj";
			#elif _WIN32 || _WIN64
        		if (cont == 0) {
                    fname = "C:/Users/setto/Documents/Visual Studio 2015/Projects/ConsoleApplication1/ConsoleApplication1/objektuak/abioia.obj";
                    cont = 1;
                }
                else fname = "C:/Users/setto/Documents/Visual Studio 2015/Projects/ConsoleApplication1/ConsoleApplication1/objektuak/logoehu_ona.obj";
			#elif __APPLE__
                fname = "objektuak/abioia.obj";
                //fname = "/Users/cristina/Dropbox/ProyectosGC/exercise3/objektuak/abioia.obj";
			#endif
*/
            /*Allocate memory for the structure and read the file*/
            printf("1\n");
            auxiliar_object = (object3d *) malloc(sizeof(object3d));
            read = read_wavefront(fname, auxiliar_object);
            switch (read) {
                /*Errors in the reading*/
                case 1:
                    printf("%s: %s\n", fname, KG_MSSG_FILENOTFOUND);
                    break;
                case 2:
                    printf("%s: %s\n", fname, KG_MSSG_INVALIDFILE);
                    break;
                case 3:
                    printf("%s: %s\n", fname, KG_MSSG_EMPTYFILE);
                    break;
                    /*Read OK*/
                case 0:
                    calcularNormales(auxiliar_object);

                    /*Insert the new object in the list*/
                    auxiliar_object->next = _first_object;
                    _first_object = auxiliar_object;
                    _selected_object = _first_object;

                    _selected_object->pila = (typeNode *) malloc(sizeof(typeNode));

                    glGetFloatv(GL_MODELVIEW_MATRIX, _selected_object->pila->m);
                    _selected_object->pila->next = NULL;
                    _selected_object->pila->prev = NULL;

                    _selected_object->camara = (camera *) malloc(sizeof(camera));
                    inicializarCamara();
                    insertarCamara(_selected_object->camara);
                    printf("%s\n", KG_MSSG_FILEREAD);

                    actualizarFoco();

                    //Asignamos un material base al objeto
                    _selected_object->material = (material *) malloc(sizeof(material));
                    GLfloat matBaseAmb[4] = {0.2, 0.2, 0.2, 1.0};
                    GLfloat matBaseDiff[4] = {0.8, 0.8, 0.8, 1.0};
                    GLfloat matBaseSpec[4] = {0.0, 0.0, 0.0, 1.0};
                    copiarContenidoArray(matBaseAmb, _selected_object->material->matAmb);
                    copiarContenidoArray(matBaseDiff, _selected_object->material->matDiff);
                    copiarContenidoArray(matBaseSpec, _selected_object->material->matSpec);
                    _selected_object->material->matShininess = 0.0;
                    break;
            }
            break;

        case 9: /* <TAB> */
            if (_first_object != 0) {
                _selected_object = _selected_object->next;
                /*The selection is circular, if we move out of the list we go back to the first element*/
                if (_selected_object == 0) _selected_object = _first_object;
                if (obj_cam == 1) {
                    camara = _selected_object->camara;
                    actualizarCamara();
                }
                if (modo_c == 1) {
                    camara->miCamara[4] = _selected_object->pila->m[12];
                    camara->miCamara[5] = _selected_object->pila->m[13];
                    camara->miCamara[6] = _selected_object->pila->m[14];
                }

                actualizarFoco();
            }
            break;

        case 127: /* <SUPR> */
            opcionSuprimir(auxiliar_object);
            break;


        case '-':
            glMatrixMode(GL_MODELVIEW);
            if (glutGetModifiers() == GLUT_ACTIVE_CTRL) {
                /*Increase the projection plane; compute the new dimensions*/
                wd = (_ortho_x_max - _ortho_x_min) / KG_STEP_ZOOM;
                he = (_ortho_y_max - _ortho_y_min) / KG_STEP_ZOOM;
                /*In order to avoid moving the center of the plane, we get its coordinates*/
                midx = (_ortho_x_max + _ortho_x_min) / 2;
                midy = (_ortho_y_max + _ortho_y_min) / 2;
                /*The the new limits are set, keeping the center of the plane*/
                _ortho_x_max = midx + wd / 2;
                _ortho_x_min = midx - wd / 2;
                _ortho_y_max = midy + he / 2;
                _ortho_y_min = midy - he / 2;

            } else {
                if (mov == 1) {
                    struct typeNode *matriz = (typeNode *) malloc(sizeof(typeNode));
                    glLoadMatrixf(_selected_object->pila->m);
                    glScalef(0.5f, 0.5f, 0.5f);
                    glGetFloatv(GL_MODELVIEW_MATRIX, matriz->m);
                    insertFirst(matriz);
                    glPopMatrix();
                } else if (mov == 2) {
                    camara->left /= 0.5;
                    camara->right /= 0.5;
                    camara->top /= 0.5;
                    camara->bottom /= 0.5;
                    camara->nearVal *= 0.5;
                } else if (mov == 3) {
                    if (luzSeleccionada->info->tipo == 2) { //Es un foco
                        if ((luzSeleccionada->info->spotCutoff - 5) > 0)//Comprobar que nunca sea un valor negativo.
                            luzSeleccionada->info->spotCutoff -= 5;
                    }
                }
            }
            break;

        case '+':
            glMatrixMode(GL_MODELVIEW);
            if (glutGetModifiers() == GLUT_ACTIVE_CTRL) {/*Increase the projection plane; compute the new dimensions*/
                wd = (_ortho_x_max - _ortho_x_min) * KG_STEP_ZOOM;
                he = (_ortho_y_max - _ortho_y_min) * KG_STEP_ZOOM;
                /*In order to avoid moving the center of the plane, we get its coordinates*/
                midx = (_ortho_x_max + _ortho_x_min) / 2;
                midy = (_ortho_y_max + _ortho_y_min) / 2;
                /*The the new limits are set, keeping the center of the plane*/
                _ortho_x_max = midx + wd / 2;
                _ortho_x_min = midx - wd / 2;
                _ortho_y_max = midy + he / 2;
                _ortho_y_min = midy - he / 2;

            } else {
                if (mov == 1) {
                    struct typeNode *matriz = (typeNode *) malloc(sizeof(typeNode));
                    glLoadMatrixf(_selected_object->pila->m);
                    glScalef(2.0f, 2.0f, 2.0f);
                    glGetFloatv(GL_MODELVIEW_MATRIX, matriz->m);
                    insertFirst(matriz);
                    glPopMatrix();
                } else if (mov == 2) {
                    camara->left *= 0.5;
                    camara->right *= 0.5;
                    camara->top *= 0.5;
                    camara->bottom *= 0.5;
                    camara->nearVal /= 0.5;
                } else if (mov == 3) {
                    if (luzSeleccionada->info->tipo == 2) { //Es un foco
                        if ((luzSeleccionada->info->spotCutoff + 5 ) <= 90) {
                            luzSeleccionada->info->spotCutoff += 5;
                        }
                    }
                }

            }
            break;
           

        case 'W':
        case 'w':
            printf("Selecciona tu material de entre los siguiente\n Pulsa 1 para bronce\n Pulsa 2 para rubi\n Pulsa 3 para oro\n Pulsa 4 para esmeralda\n");
            scanf("%d", &num);

            if (num <= 4 || num >= 1) {
                seleccionarMaterial(num);
            } else {
                printf("El valor introducido es incorrecto\n");
            }
            break;
        case 'P':
        case 'p':
            if (camara->modo == 1) camara->modo = 0;
            else camara->modo = 1;
            break;

        case 'M':
        case 'm':
            printf("Traslación activada\n");
            estado = 1;
            break;

        case 'B':
        case 'b':
            printf("Rotación activada\n");
            estado = 2;
            break;

        case 'T':
        case 't':
            if (mov == 1) printf("Escalado activado\n");
            else if (mov == 2) printf("Volumen activado.\n");
            estado = 3;
            break;

        case 'G':
        case 'g'://Transformaciones globales en el objeto / camara modo análisis
            if (mov == 1) {
                printf("Transformaciones globales del objeto.\n");
                glob_loc = 1;
            } else if (mov == 2) {
                printf("Cámara en modo análisis.\n");
                camara->miCamara[4] = _selected_object->pila->m[12];
                camara->miCamara[5] = _selected_object->pila->m[13];
                camara->miCamara[6] = _selected_object->pila->m[14];
                modo_c = 1;
            } else if (mov == 3) {
                printf("Transformaciones globales de la luz\n");
                transf_luz = 1;
            }
            break;

        case 'L':
        case 'l': //Transformaciones locales en el objeto / camara modo vuelo
            if (mov == 1) {
                printf("Transformaciones locales del objeto.\n");
                glob_loc = 0;
            } else if (mov == 2) {
                printf("Cámara en modo vuelo.\n");
                modo_c = 0;
            } else if (mov == 3) {
                printf("Transformaciones locales de la luz\n");
                transf_luz = 0;
            }
            break;


        case 'O':
        case 'o'://Aplicar transformaciones al objeto seleccionado
            printf("Aplicamos transformaciones al objeto.\n");
            mov = 1;
            break;

        case 'K':
        case 'k'://Aplicar transformaciones a la cámara actual
            printf("Aplicamos transformaciones a la cámara.\n");
            mov = 2;
            break;

        case 'A':
        case 'a'://Aplicar transformaciones a la luz selecionada
            printf("Luz activada.\n");
            mov = 3;
            break;

        case 'C': //Objeto seleccionado es cámara
            printf("Punto de vista desde el objeto seleccionado.\n");
            obj_cam = 1;
            actualizarCamara();
            camara = _selected_object->camara;
            break;

        case 'c': // Cambiar de cámara, en caso de que haya más
            printf("Pasamos a la siguiente cámara.\n");
            if (camara->next != NULL) {
                camara = camara->next;
            } else {
                camara = first_camara;
            }
            if (camara->pertenece_a_objeto == 0) {
                obj_cam = 0;
            } else {
                obj_cam = 1;
            }
            break;

        case 'i':
        case 'I':
            printf("Crear nueva cámara\n");
            struct camera *nueva = (camera *) malloc(sizeof(camera));
            float xUser, yUser, zUser;
            printf("Introduce la coordenada x de la posición de la cámara\n");
            scanf("%f", &xUser);
            printf("Introduce la coordenada y de la posición de la cámara\n");
            scanf("%f", &yUser);
            printf("Introduce la coordenada z de la posición de la cámara\n");
            scanf("%f", &zUser);
            nueva->miCamara[0] = xUser;
            nueva->miCamara[1] = yUser;
            nueva->miCamara[2] = zUser;
            nueva->miCamara[3] = 1;

            printf("Introduce la coordenada x del punto al que mira la cámara\n");
            scanf("%f", &xUser);
            printf("Introduce la coordenada y del punto al que mira la cámara\n");
            scanf("%f", &yUser);
            printf("Introduce la coordenada z del punto al que mira la cámara\n");
            scanf("%f", &zUser);
            nueva->miCamara[4] = xUser;
            nueva->miCamara[5] = yUser;
            nueva->miCamara[6] = zUser;
            nueva->miCamara[7] = 1;

            printf("Introduce la coordenada x de la verticalidad de la cámara\n");
            scanf("%f", &xUser);
            printf("Introduce la coordenada y de la verticalidad de la cámara\n");
            scanf("%f", &yUser);
            printf("Introduce la coordenada z de la verticalidad de la cámara\n");
            scanf("%f", &zUser);
            nueva->miCamara[8] = xUser;
            nueva->miCamara[9] = yUser;
            nueva->miCamara[10] = zUser;
            nueva->miCamara[11] = 0;

            nueva->miCamara[12] = 0;
            nueva->miCamara[13] = 0;
            nueva->miCamara[14] = 0;
            nueva->miCamara[15] = 0;

            nueva->pertenece_a_objeto = 0;
            nueva->next = NULL;
            nueva->prev = NULL;

            nueva->left = -0.1;
            nueva->right = 0.1;
            nueva->bottom = -0.1;
            nueva->top = 0.1;
            nueva->nearVal = 0.1;
            nueva->farVal = 20000;

            nueva->modo = 1;

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            gluLookAt(nueva->miCamara[0], nueva->miCamara[1], nueva->miCamara[2],
                      nueva->miCamara[4], nueva->miCamara[5], nueva->miCamara[6],
                      nueva->miCamara[8], nueva->miCamara[9], nueva->miCamara[10]);

            glGetFloatv(GL_MODELVIEW_MATRIX, nueva->m);

            insertarCamara(nueva);

            camara = nueva;

            printf("Cámara creada!\n");
            break;

        case '0':
            printf("%d\n", luzSeleccionada->info->numero);
            if (luzSeleccionada->estado == 0){
                printf("Para poder cambiar el tipo de luz antes debes crearla.\n");
            }
            else{
                if (luzSeleccionada->info->numero == GL_LIGHT0 || luzSeleccionada->info->numero == GL_LIGHT1 ||
                luzSeleccionada->info->numero == GL_LIGHT2) {
                printf("Estas luces no se pueden modificar\n");
                } else {
                    printf("Has decidido cambiar el tipo de luz.\n");
                    printf("Por favor, introduce 0 para cambiar a una luz tipo sol, 1 para una luz tipo bombilla y 2 para una luz tipo foco:\n");
                    scanf("%d", &type);
                    switch (type) {
                        case 0:
                            printf("Has elegido un Sol\n");
                            luzSeleccionada->info->tipo = 0;
                            luzSeleccionada->info->positionLight[3] = 0.0;
                            break;
                        case 1:
                            printf("Has elegido una Bombilla\n");
                            luzSeleccionada->info->tipo = 2;
                            luzSeleccionada->info->positionLight[3] = 1.0;
                            break;
                        case 2:
                            printf("Has elegido un Foco\n");
                            luzSeleccionada->info->tipo = 3;
                            luzSeleccionada->info->positionLight[3] = 1.0;
                            printf("Intoduce el valor del cutoff: \n");
                            scanf("%f", &a);
                            luzSeleccionada->info->spotCutoff = a;

                            printf("Intoduce el valor del exponente: \n");
                            scanf("%f", &a);
                            luzSeleccionada->info->spotExponent = a;
                            printf("Introduce los valores de dirección (3 valores float), separados por espacios: \n");
                            scanf("%f %f %f", &a, &b, &c);
                            luzSeleccionada->info->spotDirection[0] = a;
                            luzSeleccionada->info->spotDirection[1] = b;
                            luzSeleccionada->info->spotDirection[2] = c;
                            break;
                        default:
                            printf("Esa no es una opción válida\n");
                            break;
                    }
                }
            }
            

            break;


        case '1':
            luzSeleccionada = arrayLuces[0];
            printf("Luz seleccionada 0\n");
            break;

        case '2':
            luzSeleccionada = arrayLuces[1];
            printf("Luz seleccionada 1\n");
            break;

        case '3':
            luzSeleccionada = arrayLuces[2];
            printf("Luz seleccionada 2\n");
            break;

        case '4':
            luzSeleccionada = arrayLuces[3];
            printf("Luz seleccionada 3\n");
            break;

        case '5':
            luzSeleccionada = arrayLuces[4];
            printf("Luz seleccionada 4\n");
            break;

        case '6':
            luzSeleccionada = arrayLuces[5];
            printf("Luz seleccionada 5\n");
            break;

        case '7':
            luzSeleccionada = arrayLuces[6];
            printf("Luz seleccionada 6\n");
            break;

        case '8':
            luzSeleccionada = arrayLuces[7];
            printf("Luz seleccionada 7\n");
            break;

        case '?':
            print_help();
            break;

        case 'U':
        case 'u'://caso ctrl z
            //Código de deshacer las transformaciones
            if (_selected_object) {
                deleteFirst();
            }
            if (obj_cam == 1) actualizarCamara();
            actualizarFoco();

            break;

        case 'R'://caso ctrl y
        case 'r':
            if (_selected_object) {
                deleteMiddle();
            }
            if (obj_cam == 1) actualizarCamara();
            actualizarFoco();
            break;

        case 27: /* <ESC> */
            exit(0);
            break;

        default:
            /*In the default case we just print the code of the key. This is usefull to define new cases*/
            printf("%d %c\n", key, key);
    }


    /*In case we have do any modification affecting the displaying of the object, we redraw them*/
    glutPostRedisplay();
}


int existeLuzEncendida() {

    for (i = 0; i <= 7; i++) {
        if (arrayLuces[i]->estado == 2)
            return 1;
    }
    return 0;
}

void disableLights() {
    for (i = 0; i <= 7; i++) {
        if (arrayLuces[i]->estado == 2) {
            arrayLuces[i]->estado = 1;
            glDisable(GL_LIGHT0 + i); //Desactivar la luz que esté activada.
        }
    }
}

void enableLights() {
    for (i = 0; i <= 7; i++) {
        if (arrayLuces[i]->estado == 1) {
            arrayLuces[i]->estado = 2;
            glEnable(GL_LIGHT0 + i); //Activar la luz que esté activada.
        }
    }
}

void rotarFoco(int index1, int index2, int valorMultipl, int valorMultipl2, float angle) {
    float aux1, aux2;
    aux1 = luzSeleccionada->info->spotDirection[index1];
    aux2 = luzSeleccionada->info->spotDirection[index2];
    luzSeleccionada->info->spotDirection[index1] = aux1 * cos(angle) + valorMultipl * aux2 * sin(angle);
    luzSeleccionada->info->spotDirection[index2] = valorMultipl2 * aux1 * sin(angle) + aux2 * cos(angle);
}

void rotarLuz(int index1, int index2, int valorMultipl, int valorMultipl2, float angle) {
    float aux1, aux2;
    aux1 = luzSeleccionada->info->positionLight[index1];
    aux2 = luzSeleccionada->info->positionLight[index2];
    luzSeleccionada->info->positionLight[index1] = aux1 * cos(angle) + valorMultipl * aux2 * sin(angle);
    luzSeleccionada->info->positionLight[index2] = valorMultipl2 * aux1 * sin(angle) + aux2 * cos(angle);
}

void nuevaLuz(int ind) {
    int respuesta;
    int type = -1, salir = 0;
    float x, y, z, a;

    printf("Esta luz aun no está creada, ¿desea crear una luz?[1 - si/0 - no]\n");
    scanf("%i", &respuesta);

    if (respuesta == 1) {
        arrayLuces[ind]->estado = 2;

        while (salir == 0) {
            printf("Por favor, introduce 0 para crear una luz tipo sol, 1 para una luz tipo bombilla y 2 para una luz tipo foco:\n");
            scanf(" %d", &type);

            if (type == 0 || type == 1 || type == 2) {

                salir = 1;
                arrayLuces[ind]->info = (lightInfo *) malloc(sizeof(lightInfo));

                arrayLuces[ind]->info->tipo = type;
                arrayLuces[ind]->info->numero = GL_LIGHT0 + ind;
                printf("Introduce los valores de difusión (4 valores float), separados por espacios.\n");
                scanf("%f %f %f %f", &x, &y, &z, &a);
                arrayLuces[ind]->info->diffuseLight[0] = x;
                arrayLuces[ind]->info->diffuseLight[1] = y;
                arrayLuces[ind]->info->diffuseLight[2] = z;
                arrayLuces[ind]->info->diffuseLight[3] = a;
                printf("Introduce los valores de ambiente (4 valores float), separados por espacios.\n");
                scanf("%f %f %f %f", &x, &y, &z, &a);
                arrayLuces[ind]->info->ambientLight[0] = x;
                arrayLuces[ind]->info->ambientLight[1] = y;
                arrayLuces[ind]->info->ambientLight[2] = z;
                arrayLuces[ind]->info->ambientLight[3] = a;
                printf("Introduce los valores de especular (4 valores float), separados por espacios.\n");
                scanf("%f %f %f %f", &x, &y, &z, &a);
                arrayLuces[ind]->info->specularLight[0] = x;
                arrayLuces[ind]->info->specularLight[1] = y;
                arrayLuces[ind]->info->specularLight[2] = z;
                arrayLuces[ind]->info->specularLight[3] = a;
                printf("Introduce los valores de posición (4 valores float), separados por espacios.\n");
                scanf("%f %f %f %f", &x, &y, &z, &a);
                arrayLuces[ind]->info->positionLight[0] = x;
                arrayLuces[ind]->info->positionLight[1] = y;
                arrayLuces[ind]->info->positionLight[2] = z;
                arrayLuces[ind]->info->positionLight[3] = a;
                printf("Introduce los valores de atenuación constante, lineal y cuadratica (3 valores float), separados por espacios.\n");
                scanf("%f %f %f", &x, &y, &z);
                arrayLuces[ind]->info->spotAttenuation[0] = x;
                arrayLuces[ind]->info->spotAttenuation[1] = y;
                arrayLuces[ind]->info->spotAttenuation[2] = z;

                if (type == 2) {//Foco
                    printf("Intoduce el valor del cutoff: \n");
                    scanf("%f", &x);
                    arrayLuces[ind]->info->spotCutoff = x;

                    printf("Intoduce el valor del exponente: \n");
                    scanf("%f", &x);
                    arrayLuces[ind]->info->spotExponent = x;
                    printf("Introduce los valores de dirección (3 valores float), separados por espacios: \n");
                    scanf("%f %f %f", &x, &y, &z);
                    arrayLuces[ind]->info->spotDirection[0] = x;
                    arrayLuces[ind]->info->spotDirection[1] = y;
                    arrayLuces[ind]->info->spotDirection[2] = z;
                }
            } else {
                printf("Introduce algo válido.\n");
                salir = 0;
            }
        }
    } else printf("Puede realizar cualquier otra acción.\n");
}

void cambiarEstadoLuz(int luz) {
    if (arrayLuces[luz]->estado == 2) {
        printf("Luz %d desactivada\n", luz);
        glDisable(GL_LIGHT0 + luz);
        arrayLuces[luz]->estado = 1;
    } else if (arrayLuces[luz]->estado == 1) {
        printf("Luz %d activada\n", luz);
        glEnable(GL_LIGHT0 + luz);
        arrayLuces[luz]->estado = 2;
    } else if (arrayLuces[luz]->estado == 0) {
        nuevaLuz(luz);
    }
}


void SpecialKeys(int key, int x, int y) {
    float angle = 0.25f;
    if (_selected_object) {
        float aux[4] = {0, 0, 0, 0};
        switch (mov) {
            case 1: //Transformaciones al objeto
                printf("Transformaciones al objeto.\n");
                struct typeNode *matriz = (typeNode *) malloc(sizeof(typeNode));
                glMatrixMode(GL_MODELVIEW);
                if (glob_loc == 0) glLoadMatrixf(_selected_object->pila->m);
                else glLoadIdentity();

                switch (estado) {
                    case 1:
                        switch (key) {
                            case GLUT_KEY_UP:
                                glTranslatef(0.0f, 1.0f, 0.0f);
                                break;
                            case GLUT_KEY_DOWN:
                                glTranslatef(0.0f, -1.0f, 0.0f);
                                break;
                            case GLUT_KEY_RIGHT:
                                glTranslatef(1.0f, 0.0f, 0.0f);
                                break;
                            case GLUT_KEY_LEFT:
                                glTranslatef(-1.0f, 0.0f, 0.0f);
                                break;
                            case GLUT_KEY_PAGE_UP:
                                glTranslatef(0.0f, 0.0f, 1.0f);
                                break;
                            case GLUT_KEY_PAGE_DOWN:
                                glTranslatef(0.0f, 0.0f, -1.0f);
                                break;
                        }

                        break;
                    case 2:
                        switch (key) {
                            case GLUT_KEY_UP:
                                glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
                                break;
                            case GLUT_KEY_DOWN:
                                glRotatef(15.0f, -1.0f, 0.0f, 0.0f);
                                break;
                            case GLUT_KEY_RIGHT:
                                glRotatef(15.0f, 0.0f, 1.0f, 0.0f);
                                break;
                            case GLUT_KEY_LEFT:
                                glRotatef(15.0f, 0.0f, -1.0f, 0.0f);
                                break;
                            case GLUT_KEY_PAGE_UP:
                                glRotatef(15.0f, 0.0f, 0.0f, 1.0f);
                                break;
                            case GLUT_KEY_PAGE_DOWN:
                                glRotatef(15.0f, 0.0f, 0.0f, -1.0f);
                                break;
                        }

                        break;
                    case 3:
                        switch (key) {
                            case GLUT_KEY_UP:
                                glScalef(1.0f, 1.5f, 1.0f);
                                break;
                            case GLUT_KEY_DOWN:
                                glScalef(1.0f, 0.75f, 1.0f);
                                break;
                            case GLUT_KEY_RIGHT:
                                glScalef(1.5f, 1.0f, 1.0f);
                                break;
                            case GLUT_KEY_LEFT:
                                glScalef(0.75f, 1.0f, 1.0f);
                                break;
                            case GLUT_KEY_PAGE_UP:
                                glScalef(1.0f, 1.0f, 1.5f);
                                break;
                            case GLUT_KEY_PAGE_DOWN:
                                glScalef(1.0f, 1.0f, 0.75f);
                                break;
                        }
                        break;
                    default:
                        printf("No hay ninguna transformación seleccionada\n");
                        break;

                }
                if (glob_loc == 1) glMultMatrixf(_selected_object->pila->m);
                glGetFloatv(GL_MODELVIEW_MATRIX, matriz->m);
                insertFirst(matriz);
                if (obj_cam == 1) {
                    printf("La camara es del objeto\n");
                    actualizarCamara();
                }
                if (modo_c == 1) {
                    camara->miCamara[4] = _selected_object->pila->m[12];
                    camara->miCamara[5] = _selected_object->pila->m[13];
                    camara->miCamara[6] = _selected_object->pila->m[14];

                }
                actualizarFoco();
                break;

            case 2://Cámara
                printf("Transformaciones a la cámara\n");
                if (obj_cam == 0) {
                    glMatrixMode(GL_MODELVIEW);
                    glLoadIdentity();

                    if (modo_c == 0) {//Cámara en modo vuelo.
                        printf("modo vuelo\n");
                        glTranslatef(camara->miCamara[0], camara->miCamara[1], camara->miCamara[2]);
                        switch (estado) {
                            case 1: //Traslación
                                switch (key) {
                                    case GLUT_KEY_UP:
                                        glTranslatef(camara->m[1], camara->m[5], camara->m[9]);
                                        break;
                                    case GLUT_KEY_DOWN:
                                        glTranslatef(-camara->m[1], -camara->m[5], -camara->m[9]);
                                        break;
                                    case GLUT_KEY_RIGHT:
                                        glTranslatef(camara->m[0], camara->m[4], camara->m[8]);
                                        break;
                                    case GLUT_KEY_LEFT:
                                        glTranslatef(-camara->m[0], -camara->m[4], -camara->m[8]);
                                        break;
                                    case GLUT_KEY_PAGE_UP:
                                        glTranslatef(-camara->m[2], -camara->m[6], -camara->m[10]);
                                        break;
                                    case GLUT_KEY_PAGE_DOWN:
                                        glTranslatef(camara->m[2], camara->m[6], camara->m[10]);
                                        break;
                                }
                                break;
                            case 2: //Rotación
                                switch (key) {
                                    case GLUT_KEY_UP:
                                        glRotatef(15, camara->m[0], camara->m[4], camara->m[8]);
                                        break;
                                    case GLUT_KEY_DOWN:
                                        glRotatef(-15, camara->m[0], camara->m[4], camara->m[8]);
                                        break;
                                    case GLUT_KEY_RIGHT:
                                        glRotatef(-15, camara->m[1], camara->m[5], camara->m[9]);
                                        break;
                                    case GLUT_KEY_LEFT:
                                        glRotatef(15, camara->m[1], camara->m[5], camara->m[9]);
                                        break;
                                    case GLUT_KEY_PAGE_UP:
                                        glRotatef(15, camara->m[2], camara->m[6], camara->m[10]);
                                        break;
                                    case GLUT_KEY_PAGE_DOWN:
                                        glRotatef(-15, camara->m[2], camara->m[6], camara->m[10]);
                                        break;
                                }
                                break;
                            case 3: //Volumen
                                switch (key) {
                                    case GLUT_KEY_UP:
                                        camara->top += 0.1;
                                        camara->bottom -= 0.1;
                                        break;
                                    case GLUT_KEY_DOWN:
                                        if (camara->top > 0.11) {
                                            camara->top -= 0.1;
                                            camara->bottom += 0.1;
                                        }
                                        break;
                                    case GLUT_KEY_RIGHT:
                                        camara->right += 0.1;
                                        camara->left -= 0.1;
                                        break;
                                    case GLUT_KEY_LEFT:
                                        if (camara->right > 0.11) {
                                            camara->right -= 0.1;
                                            camara->left += 0.1;
                                        }
                                        break;
                                    case GLUT_KEY_PAGE_UP:
                                        camara->nearVal += 0.1;
                                        camara->farVal += 0.1;
                                        break;
                                    case GLUT_KEY_PAGE_DOWN:
                                        if (camara->nearVal > 0.11) {
                                            camara->nearVal -= 0.1;
                                            camara->farVal -= 0.1;
                                        }
                                        break;
                                }
                                break;
                            default:
                                printf("No hay nada seleccionado.\n");
                                break;
                        }
                        glTranslatef(-camara->miCamara[0], -camara->miCamara[1], -camara->miCamara[2]);
                    } else if (modo_c == 1) { //Cámara en modo análisis
                        printf("modo análisis\n");
                        aux[0] = camara->miCamara[4];
                        aux[1] = camara->miCamara[5];
                        aux[2] = camara->miCamara[6];
                        aux[3] = camara->miCamara[7];

                        glTranslatef(camara->miCamara[4], camara->miCamara[5], camara->miCamara[6]);
                        switch (estado) {
                            case 1: //Traslación
                                switch (key) {
                                    case GLUT_KEY_PAGE_UP:
                                        glTranslatef(-camara->m[2], -camara->m[6], -camara->m[10]);
                                        break;
                                    case GLUT_KEY_PAGE_DOWN:
                                        glTranslatef(camara->m[2], camara->m[6], camara->m[10]);
                                        break;
                                }
                                break;
                            case 2: //Rotación
                                switch (key) {
                                    case GLUT_KEY_UP:
                                        glRotatef(-15, camara->m[0], camara->m[4], camara->m[8]);
                                        break;
                                    case GLUT_KEY_DOWN:
                                        glRotatef(15, camara->m[0], camara->m[4], camara->m[8]);
                                        break;
                                    case GLUT_KEY_RIGHT:
                                        glRotatef(15, camara->m[1], camara->m[5], camara->m[9]);
                                        break;
                                    case GLUT_KEY_LEFT:
                                        glRotatef(-15, camara->m[1], camara->m[5], camara->m[9]);
                                        break;
                                    case GLUT_KEY_PAGE_UP:
                                        glRotatef(-15, camara->m[2], camara->m[6], camara->m[10]);
                                        break;
                                    case GLUT_KEY_PAGE_DOWN:
                                        glRotatef(15, camara->m[2], camara->m[6], camara->m[10]);
                                        break;
                                }
                                break;
                            case 3: //Volumen
                                switch (key) {
                                    case GLUT_KEY_UP:
                                        camara->top += 0.1;
                                        camara->bottom -= 0.1;
                                        break;
                                    case GLUT_KEY_DOWN:
                                        if (camara->top > 0.11) {
                                            camara->top -= 0.1;
                                            camara->bottom += 0.1;
                                        }
                                        break;
                                    case GLUT_KEY_RIGHT:
                                        camara->right += 0.1;
                                        camara->left -= 0.1;
                                        break;
                                    case GLUT_KEY_LEFT:
                                        if (camara->right > 0.11) {
                                            camara->right -= 0.1;
                                            camara->left += 0.1;
                                        }
                                        break;
                                    case GLUT_KEY_PAGE_UP:
                                        camara->nearVal += 0.1;
                                        camara->farVal += 0.1;
                                        break;
                                    case GLUT_KEY_PAGE_DOWN:
                                        if (camara->nearVal > 0.11) {
                                            camara->nearVal -= 0.1;
                                            camara->farVal -= 0.1;
                                        }
                                        break;
                                }
                                break;
                            default:
                                printf("No hay nada seleccionado.\n");
                                break;
                        }
                        glTranslatef(-camara->miCamara[4], -camara->miCamara[5], -camara->miCamara[6]);
                    }

                    glMultMatrixf(camara->miCamara);
                    glGetFloatv(GL_MODELVIEW_MATRIX, camara->miCamara);
                    if (modo_c == 1) {
                        camara->miCamara[4] = aux[0];
                        camara->miCamara[5] = aux[1];
                        camara->miCamara[6] = aux[2];
                        camara->miCamara[7] = aux[3];
                    }
                } else {
                    if (estado == 2) {
                        glLoadMatrixf(_selected_object->mat_rot_cam);
                        switch (key) {
                            case GLUT_KEY_UP:
                                glRotatef(-15, _selected_object->mat_rot_cam[0], _selected_object->mat_rot_cam[4],
                                          _selected_object->mat_rot_cam[8]);
                                break;
                            case GLUT_KEY_DOWN:
                                glRotatef(15, _selected_object->mat_rot_cam[0], _selected_object->mat_rot_cam[4],
                                          _selected_object->mat_rot_cam[8]);
                                break;
                            case GLUT_KEY_RIGHT:
                                glRotatef(15, _selected_object->mat_rot_cam[1], _selected_object->mat_rot_cam[5],
                                          _selected_object->mat_rot_cam[9]);
                                break;
                            case GLUT_KEY_LEFT:
                                glRotatef(-15, _selected_object->mat_rot_cam[1], _selected_object->mat_rot_cam[5],
                                          _selected_object->mat_rot_cam[9]);
                                break;
                            case GLUT_KEY_PAGE_UP:
                                glRotatef(-15, _selected_object->mat_rot_cam[2], _selected_object->mat_rot_cam[6],
                                          _selected_object->mat_rot_cam[10]);
                                break;
                            case GLUT_KEY_PAGE_DOWN:
                                glRotatef(15, _selected_object->mat_rot_cam[2], _selected_object->mat_rot_cam[6],
                                          _selected_object->mat_rot_cam[10]);
                                break;
                        }
                        glGetFloatv(GL_MODELVIEW_MATRIX, _selected_object->mat_rot_cam);
                    } else
                        printf("La única opción que puedes ejecutar es rotar la cámara.\n");
                }

                break;


            case 3:
                printf("luz\n");
                if ((luzSeleccionada->estado == 2) && glIsEnabled(GL_LIGHTING)) { //comprobar que la luz esté encendida
                    switch (estado) {
                        case 1: //Traslación
                            printf("traslación de la luz\n");
                            if (luzSeleccionada->info->numero == GL_LIGHT2){// Asi bloquemamos el foco asociado al objet
                                printf("Ese foco no se puede mover.\n");
                            }
                            else{
                                if (luzSeleccionada->info->tipo == 0) { //comprobar que la luz es un sol
                                    printf("Este tipo de luz no tiene traslaciones.\n");
                                } else {
                                    switch (key) {
                                        case GLUT_KEY_UP:
                                            luzSeleccionada->info->positionLight[1] += 1;
                                        break;
                                        case GLUT_KEY_DOWN:
                                            luzSeleccionada->info->positionLight[1] -= 1;
                                        break;
                                        case GLUT_KEY_RIGHT:
                                         printf("%i\n", luzSeleccionada->info->tipo );
                                            luzSeleccionada->info->positionLight[0] += 1;
                                        break;
                                        case GLUT_KEY_LEFT: 
                                            luzSeleccionada->info->positionLight[0] -= 1;
                                        break;
                                        case GLUT_KEY_PAGE_UP: 
                                            luzSeleccionada->info->positionLight[2] += 1;
                                        break;
                                        case GLUT_KEY_PAGE_DOWN: 
                                            luzSeleccionada->info->positionLight[2] -= 1;
                                        break;
                                    }
                                }
                            }                            
                            break;
                        case 2: //Rotación
                            switch (luzSeleccionada->info->tipo) {
                                case 0://sol
                                case 1: //bombilla
                                    switch (key) { /*vamos a suponer que el usuario siempre quiere hacer la rotación en global ya que en
                                                        local no tendría sentido.*/
                                        case GLUT_KEY_UP:
                                            rotarLuz(2, 0, -1, 1, angle);
                                            break;
                                        case GLUT_KEY_DOWN:
                                            rotarLuz(2, 0, 1, -1, angle);
                                            break;
                                        case GLUT_KEY_LEFT:
                                            rotarLuz(0, 1, -1, 1, angle);
                                            break;
                                        case GLUT_KEY_RIGHT:
                                            rotarLuz(0, 1, 1, -1, angle);
                                            break;
                                        case GLUT_KEY_PAGE_DOWN:
                                            rotarLuz(1, 2, -1, 1, angle);
                                            break;
                                        case GLUT_KEY_PAGE_UP:
                                            rotarLuz(1, 2, 1, -1, angle);
                                            break;
                                    }
                                    break;
                                case 2: //foco
                                    if (luzSeleccionada->info->numero == GL_LIGHT2)
                                        break; // Asi bloquemamos el foco asociado al objeto
                                    if (transf_luz ==
                                        0) { //transformaciones locales (solo afecta a la dirección del foco, la posición no cambia)
                                        //TODO poner que se bloquee el foco 3 que es el relacionado al objeto?

                                        angle = 0.15;
                                        switch (key) {
                                            case GLUT_KEY_UP:
                                                rotarFoco(1, 2, -1, 1, angle);
                                                break;
                                            case GLUT_KEY_DOWN:
                                                rotarFoco(1, 2, 1, -1, angle);
                                                break;
                                            case GLUT_KEY_RIGHT:
                                                rotarFoco(2, 0, -1, 1, angle);
                                                break;
                                            case GLUT_KEY_LEFT:
                                                rotarFoco(2, 0, 1, -1, angle);
                                                break;
                                            case GLUT_KEY_PAGE_UP:
                                                rotarFoco(0, 1, -1, 1, angle);
                                                break;
                                            case GLUT_KEY_PAGE_DOWN:
                                                rotarFoco(0, 1, 1, -1, angle);
                                                break;
                                        }


                                    } else { //Transf globales (Rotar posición y dirección)
                                        switch (key) {
                                            case GLUT_KEY_UP:
                                                rotarLuz(1, 2, -1, 1, angle);
                                                rotarFoco(1, 2, -1, 1, angle);
                                                break;
                                            case GLUT_KEY_DOWN:
                                                rotarLuz(1, 2, 1, -1, angle);
                                                rotarFoco(1, 2, 1, -1, angle);
                                                break;
                                            case GLUT_KEY_LEFT:
                                                rotarLuz(2, 0, -1, 1, angle);
                                                rotarFoco(2, 0, -1, 1, angle);
                                                break;
                                            case GLUT_KEY_RIGHT:
                                                rotarLuz(2, 0, 1, -1, angle);
                                                rotarFoco(2, 0, 1, -1, angle);
                                                break;
                                            case GLUT_KEY_PAGE_DOWN:
                                                rotarLuz(0, 1, -1, 1, angle);
                                                rotarFoco(0, 1, -1, 1, angle);
                                                break;
                                            case GLUT_KEY_PAGE_UP:
                                                rotarLuz(0, 1, 1, -1, angle);
                                                rotarFoco(0, 1, 1, -1, angle);
                                                break;
                                        }

                                    }
                                    break;
                            }
                            break;
                        case 3: //Volumen, en cualquiera de los casos, la función de este va a ser la de ampliar spotCutoff
                            switch (key) {
                                if (luzSeleccionada->info->tipo == 2) {
                                    case GLUT_KEY_UP:
                                    case GLUT_KEY_RIGHT:
                                    case GLUT_KEY_PAGE_UP:
	                                    if ((luzSeleccionada->info->spotCutoff + 5) <= 90 )
	                                        luzSeleccionada->info->spotCutoff += 5;
                                    break;
                                    case GLUT_KEY_DOWN:
                                    case GLUT_KEY_LEFT:
                                    case GLUT_KEY_PAGE_DOWN:
                                    	if ((luzSeleccionada->info->spotCutoff - 5) > 0)
                                        	luzSeleccionada->info->spotCutoff -= 5;
                                    break;
                                }
                            }
                            break;
                        default:
                            printf("No hay nada seleccionado.\n");
                            break;
                    }
                } else { //La luz está apagada
                    printf("La luz que desea transformar está apagada. Enciéndala para poder hacer transformaciones sobre ella.\n");
                }

                break;
            default:
                printf("No hay nada seleccionado para transformar.\n");
                break;

        }
        switch (key) {
            printf("Entro en el key\n");
            case GLUT_KEY_F1:
                cambiarEstadoLuz(0);
                break;
            case GLUT_KEY_F2:
                cambiarEstadoLuz(1);
                break;
            case GLUT_KEY_F3:
                cambiarEstadoLuz(2);
                break;
            case GLUT_KEY_F4:
                cambiarEstadoLuz(3);
                break;
            case GLUT_KEY_F5:
                cambiarEstadoLuz(4);
                break;
            case GLUT_KEY_F6:
                cambiarEstadoLuz(5);
                break;
            case GLUT_KEY_F7:
                cambiarEstadoLuz(6);
                break;
            case GLUT_KEY_F8:
                cambiarEstadoLuz(7);
                break;
            case GLUT_KEY_F9:
                onOffIluminacion();
                break;
            case GLUT_KEY_F10:
                if (existeLuzEncendida() == 1) { //Hay alguna luz encendida
                    printf("f10 quitar luces\n");
                    disableLights();
                } else {
                    printf("f10 poner luces\n");
                    enableLights();
                }
                break;
            case GLUT_KEY_F11:
                foco_debug = !foco_debug;
                break;
            case GLUT_KEY_F12:
                flat_or_smooth = !flat_or_smooth;
                break;
        }
        //actualizarFoco();
        glutPostRedisplay();
    }
}