#include "definitions.h"
#include "load_obj.h"
#include "stack2.h"
#include <stdio.h>

#ifdef __linux__
#include <GL/glut.h>
#elif __APPLE__
#include <GLUT/glut.h>
#endif

extern object3d * _first_object;
extern object3d * _selected_object;
extern camera *camara;


int estado = 0; //0-> nada seleccionado
int cont = 0;
int mov = 0; //0-> no se mueve,  1-> transformaciones objeto, 2-> transformaciones camara, 3-> transformaciones luz
int modo = 0; // 0-> local/vuelo, 1->global/analisis

extern GLdouble _ortho_x_min,_ortho_x_max;
extern GLdouble _ortho_y_min,_ortho_y_max;
extern GLdouble _ortho_z_min,_ortho_z_max;

/**
 * @brief This function just prints information about the use
 * of the keys
 */
void print_help(){
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

/**
 * @brief Callback function to control the basic keys
 * @param key Key that has been pressed
 * @param x X coordinate of the mouse pointer when the key was pressed
 * @param y Y coordinate of the mouse pointer when the key was pressed
 */
void keyboard(unsigned char key, int x, int y) {
    char* fname = malloc(sizeof (char)*128); /* Note that scanf adds a null character at the end of the vector*/
    int read = 0;
    object3d *auxiliar_object = 0;
    GLdouble wd,he,midx,midy;
    switch (key) {
        case 'f':
        case 'F':
            /*Ask for file*/
            printf("%s", KG_MSSG_SELECT_FILE);
            //scanf("%s", fname);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            #ifdef __linux__
                        if (cont==0){
                            fname = "objektuak/logoehu_ona.obj";
                            cont = 1;
                        }
                        else fname = "objektuak/abioia.obj";
            #elif __APPLE__
                    fname = "objektuak/abioia.obj";
                    //fname = "/Users/cristina/Dropbox/ProyectosGC/exercise2/objektuak/x_wing.obj";
            #endif
            /*Allocate memory for the structure and read the file*/
            auxiliar_object = (object3d *) malloc(sizeof (object3d));
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
                    /*Insert the new object in the list*/
                    auxiliar_object->next = _first_object;
                    _first_object = auxiliar_object;
                    _selected_object = _first_object;

                    _selected_object->pila = (typeNode *) malloc(sizeof (typeNode));
                    //_selected_object->pila = NULL;
                    /* insertar la identidad en la pila */

                    glGetFloatv(GL_MODELVIEW_MATRIX, _selected_object->pila->m);
                    //insertFirst(_selected_object->pila);
                    _selected_object->pila->next = NULL;
                    _selected_object->pila->prev = NULL;
                    printf("%s\n",KG_MSSG_FILEREAD);
                    break;
            }
            break;

        case 9: /* <TAB> */
            if (_first_object != 0){
                _selected_object = _selected_object->next;
                /*The selection is circular, if we move out of the list we go back to the first element*/
                if (_selected_object == 0) _selected_object = _first_object;
            }
            break;

        case 127: /* <SUPR> */

            /*Erasing an object depends on whether it is the first one or not*/
            if (_first_object != 0)

                if (_selected_object == _first_object)
                {
                    /*To remove the first object we just set the first as the current's next*/
                    _first_object = _first_object->next;
                    /*Once updated the pointer to the first object it is save to free the memory*/
                    free(_selected_object);
                    /*Finally, set the selected to the new first one*/
                    _selected_object = _first_object;
                } else {
                    /*In this case we need to get the previous element to the one we want to erase*/
                    auxiliar_object = _first_object;
                    while (auxiliar_object->next != _selected_object){
                        auxiliar_object = auxiliar_object->next;
                    }

                    /*Now we bypass the element to erase*/
                    auxiliar_object->next = _selected_object->next;
                    /*free the memory*/
                    free(_selected_object);
                    /*and update the selection*/
                    _selected_object = auxiliar_object;
                }
            break;


        case '-':
            glMatrixMode(GL_MODELVIEW);
            if (glutGetModifiers() == GLUT_ACTIVE_CTRL){
                /*Decrease the projection plane; compute the new dimensions*/
                wd=(_ortho_x_max-_ortho_x_min)/KG_STEP_ZOOM;
                he=(_ortho_y_max-_ortho_y_min)/KG_STEP_ZOOM;
                /*In order to avoid moving the center of the plane, we get its coordinates*/
                midx = (_ortho_x_max+_ortho_x_min)/2;
                midy = (_ortho_y_max+_ortho_y_min)/2;
                /*The the new limits are set, keeping the center of the plane*/
                _ortho_x_max = midx + wd/2;
                _ortho_x_min = midx - wd/2;
                _ortho_y_max = midy + he/2;
                _ortho_y_min = midy - he/2;
            }
            else{
                struct typeNode *matriz = (typeNode *) malloc(sizeof (typeNode));
                glLoadMatrixf(_selected_object->pila->m);
                glScalef(0.5f,0.5f,0.5f);
                glGetFloatv(GL_MODELVIEW_MATRIX, matriz->m);
                insertFirst(matriz);
                glPopMatrix();
            }
            break;

        case '+':
            glMatrixMode(GL_MODELVIEW);
            if (glutGetModifiers() == GLUT_ACTIVE_CTRL){
                /*Increase the projection plane; compute the new dimensions*/
                wd=(_ortho_x_max-_ortho_x_min)*KG_STEP_ZOOM;
                he=(_ortho_y_max-_ortho_y_min)*KG_STEP_ZOOM;
                /*In order to avoid moving the center of the plane, we get its coordinates*/
                midx = (_ortho_x_max+_ortho_x_min)/2;
                midy = (_ortho_y_max+_ortho_y_min)/2;
                /*The the new limits are set, keeping the center of the plane*/
                _ortho_x_max = midx + wd/2;
                _ortho_x_min = midx - wd/2;
                _ortho_y_max = midy + he/2;
                _ortho_y_min = midy - he/2;
            }
            else{
                struct typeNode *matriz = (typeNode *) malloc(sizeof (typeNode));
                glLoadMatrixf(_selected_object->pila->m);
                glScalef(2.0f,2.0f,2.0f);
                glGetFloatv(GL_MODELVIEW_MATRIX, matriz->m);
                insertFirst(matriz);
                glPopMatrix();
            }
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
            if(mov == 1) printf("Escalado activado\n");
            else if (mov ==2) printf("Volumen activado.\n");
            estado = 3;
            break;

        case 'G':
        case 'g'://Transformaciones globales en el objeto / camara modo análisis
            printf("%d\n", mov);
            if (mov == 1) printf("Transformaciones globales del objeto.\n");
            else if (mov ==2) printf("Cámara en modo análisis.\n");
            modo = 1;
            break;


        case 'L':
        case 'l': //Transformaciones locales en el objeto / camara modo vuelo
            if (mov == 1) printf("Transformaciones locales del objeto.\n");
            else if (mov ==2) printf("Cámara en modo vuelo.\n");
            modo = 0;
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
            //TODO
            break;

        case 'c': // Cambiar de cámara, en caso de que haya más
            printf("Pasamos a la siguiente cámara.\n");
            //TODO
            break;

        case '?':
            print_help();
            break;

        case 'U':
        case 'u'://caso ctrl z
            //Código de deshacer las transformaciones
            if (_selected_object) deleteFirst();
            break;

        case 'R'://caso ctrl y
        case 'r':
            if (_selected_object) deleteMiddle();
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

void SpecialKeys(int key, int x, int y) {
    printf("%d\n", mov);
    struct typeNode *matriz = (typeNode *) malloc(sizeof (typeNode));
    if(_selected_object){
        switch(mov){
            case 1: //Transformaciones al objeto
                printf("Transformaciones al objeto.\n");
                glMatrixMode(GL_MODELVIEW);
                if (modo == 0) glLoadMatrixf(_selected_object->pila->m);
                else glLoadIdentity();

                switch(estado){
                    case 1:
                        switch (key){
                            case GLUT_KEY_UP:glTranslatef(0.0f,1.0f,0.0f);break;
                            case GLUT_KEY_DOWN:glTranslatef(0.0f,-1.0f,0.0f);break;
                            case GLUT_KEY_RIGHT:glTranslatef(1.0f,0.0f,0.0f);break;
                            case GLUT_KEY_LEFT:glTranslatef(-1.0f,0.0f,0.0f);break;
                            case GLUT_KEY_PAGE_UP:glTranslatef(0.0f,0.0f,1.0f);break;
                            case GLUT_KEY_PAGE_DOWN:glTranslatef(0.0f,0.0f,-1.0f);break;
                        }

                        break;
                    case 2:
                        switch (key){
                            case GLUT_KEY_UP:glRotatef(15.0f,1.0f,0.0f,0.0f);break;
                            case GLUT_KEY_DOWN:glRotatef(15.0f,-1.0f,0.0f,0.0f);break;
                            case GLUT_KEY_RIGHT:glRotatef(15.0f,0.0f,1.0f,0.0f);break;
                            case GLUT_KEY_LEFT:glRotatef(15.0f,0.0f,-1.0f,0.0f);break;
                            case GLUT_KEY_PAGE_UP:glRotatef(15.0f,0.0f,0.0f,1.0f);break;
                            case GLUT_KEY_PAGE_DOWN:glRotatef(15.0f,0.0f,0.0f,-1.0f);break;
                        }

                        break;
                    case 3:
                        switch (key){
                            case GLUT_KEY_UP:glScalef(1.0f,1.5f,1.0f);break;
                            case GLUT_KEY_DOWN:glScalef(1.0f,0.75f,1.0f);break;
                            case GLUT_KEY_RIGHT:glScalef(1.5f,1.0f,1.0f);break;
                            case GLUT_KEY_LEFT:glScalef(0.75f,1.0f,1.0f);break;
                            case GLUT_KEY_PAGE_UP:glScalef(1.0f,1.0f,1.5f);break;
                            case GLUT_KEY_PAGE_DOWN:glScalef(1.0f,1.0f,0.75f);break;
                        }
                        break;
                    default:
                        printf("No hay ninguna transformación seleccionada\n");
                        break;

                }
                if (modo == 1) glMultMatrixf(_selected_object->pila->m);
                glGetFloatv(GL_MODELVIEW_MATRIX, matriz->m);
                insertFirst(matriz);
                break;

            case 2://Cámara
                printf("Transformaciones a la cámara en modo vuelo.\n");
                glMatrixMode(GL_MODELVIEW_MATRIX);
                glLoadIdentity();

                if (modo == 0) {//Cámara en modo vuelo.
                    glTranslatef(camara->miCamara[0], camara->miCamara[1], camara->miCamara[2]);
                    switch (estado){
                        case 1: //Traslación
                            switch (key){
                                case GLUT_KEY_UP:glTranslatef(camara->m[1], camara->m[5], camara->m[9]);break;
                                case GLUT_KEY_DOWN:glTranslatef(-camara->m[1], -camara->m[5], -camara->m[9]);break;
                                case GLUT_KEY_RIGHT:glTranslatef(camara->m[0], camara->m[4], camara->m[8]);break;
                                case GLUT_KEY_LEFT:glTranslatef(-camara->m[0], -camara->m[4], -camara->m[8]);break;
                                case GLUT_KEY_PAGE_UP:glTranslatef(camara->m[2], camara->m[6], camara->m[10]);break;
                                case GLUT_KEY_PAGE_DOWN:glTranslatef(-camara->m[2], -camara->m[6], -camara->m[10]);break;
                            }
                            break;
                        case 2: //Rotación
                            switch (key){
                                case GLUT_KEY_UP:glRotatef(15, camara->m[0], camara->m[4], camara->m[8]);break;
                                case GLUT_KEY_DOWN:glRotatef(-15, camara->m[0], camara->m[4], camara->m[8]);break;
                                case GLUT_KEY_RIGHT:glRotatef(-15, camara->m[1], camara->m[5], camara->m[9]);break;
                                case GLUT_KEY_LEFT:glRotatef(15, camara->m[1], camara->m[5], camara->m[9]);break;
                                case GLUT_KEY_PAGE_UP:glRotatef(15, camara->m[2], camara->m[6], camara->m[10]);break;
                                case GLUT_KEY_PAGE_DOWN:glRotatef(-15, camara->m[2], camara->m[6], camara->m[10]);break;
                            }
                            break;
                        case 3: //Volumen
                            switch (key){
                                case GLUT_KEY_UP:
                                    camara->top += 0.1;
                                    camara->bottom -= 0.1;
                                    break;
                                case GLUT_KEY_DOWN:
                                    if(camara->top > 0.11){
                                        camara->top -= 0.1;
                                        camara->bottom += 0.1;
                                    }
                                    break;
                                case GLUT_KEY_RIGHT:
                                    camara->right += 0.1;
                                    camara->left -= 0.1;
                                    break;
                                case GLUT_KEY_LEFT:
                                    if(camara->right > 0.11){
                                        camara->right -= 0.1;
                                        camara->left += 0.1;
                                    }
                                      break;
                                case GLUT_KEY_PAGE_UP:
                                    camara->nearVal += 0.1;
                                    camara->farVal += 0.1;
                                    break;
                                case GLUT_KEY_PAGE_DOWN:
                                    if (camara->nearVal > 0.11){
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
                }

                else if (modo == 1){ //Cámara en modo análisis
                    glTranslatef(camara->miCamara[4], camara->miCamara[5], camara->miCamara[6]);
                    switch (estado){
                        case 1: //Traslación
                            switch (key){
                                case GLUT_KEY_UP:glTranslatef(camara->m[1], camara->m[5], camara->m[9]);break;
                                case GLUT_KEY_DOWN:glTranslatef(-camara->m[1], -camara->m[5], -camara->m[9]);break;
                                case GLUT_KEY_RIGHT:glTranslatef(camara->m[0], camara->m[4], camara->m[8]);break;
                                case GLUT_KEY_LEFT:glTranslatef(-camara->m[0], -camara->m[4], -camara->m[8]);break;
                                case GLUT_KEY_PAGE_UP:glTranslatef(camara->m[2], camara->m[6], camara->m[10]);break;
                                case GLUT_KEY_PAGE_DOWN:glTranslatef(-camara->m[2], -camara->m[6], -camara->m[10]);break;
                            }
                            break;
                        case 2: //Rotación
                            switch (key){
                                case GLUT_KEY_UP:glRotatef(-15, camara->m[0], camara->m[4], camara->m[8]);break;
                                case GLUT_KEY_DOWN:glRotatef(15, camara->m[0], camara->m[4], camara->m[8]);break;
                                case GLUT_KEY_RIGHT:glRotatef(15, camara->m[1], camara->m[5], camara->m[9]);break;
                                case GLUT_KEY_LEFT:glRotatef(-15, camara->m[1], camara->m[5], camara->m[9]);break;
                                case GLUT_KEY_PAGE_UP:glRotatef(-15, camara->m[2], camara->m[6], camara->m[10]);break;
                                case GLUT_KEY_PAGE_DOWN:glRotatef(15, camara->m[2], camara->m[6], camara->m[10]);break;
                            }
                            break;
                        case 3: //Volumen
                            switch (key){
                                case GLUT_KEY_UP:
                                    camara->top += 0.1;
                                    camara->bottom -= 0.1;
                                    break;
                                case GLUT_KEY_DOWN:
                                    if(camara->top > 0.11){
                                        camara->top -= 0.1;
                                        camara->bottom += 0.1;
                                    }
                                    break;
                                case GLUT_KEY_RIGHT:
                                    camara->right += 0.1;
                                    camara->left -= 0.1;
                                    break;
                                case GLUT_KEY_LEFT:
                                    if(camara->right > 0.11){
                                        camara->right -= 0.1;
                                        camara->left += 0.1;
                                    }
                                      break;
                                case GLUT_KEY_PAGE_UP:
                                    camara->nearVal += 0.1;
                                    camara->farVal += 0.1;
                                    break;
                                case GLUT_KEY_PAGE_DOWN:
                                    if (camara->nearVal > 0.11){
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
                break;


            case 3:
                printf("luz\n");
                break;

            default:
                printf("No hay nada seleccionado para transformar.\n");
                break;

        }

        glutPostRedisplay();
    }
}