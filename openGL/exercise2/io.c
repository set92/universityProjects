#include "definitions.h"
#include "load_obj.h"
#include "stack2.h"
#include <GL/glut.h>
#include <stdio.h>

extern object3d * _first_object;
extern object3d * _selected_object;

int estado = 0; //0-> nada seleccionado

extern GLdouble _ortho_x_min,_ortho_x_max;
extern GLdouble _ortho_y_min,_ortho_y_max;
extern GLdouble _ortho_z_min,_ortho_z_max;

/**
 * @brief This function just prints information about the use
 * of the keys
 */
void print_help(){
    printf("KbG Irakasgaiaren Praktika. Programa honek 3D objektuak \n");
    printf("aldatzen eta bistaratzen ditu.  \n\n");

    printf("Egilea: Borja Calvo (borja.calvo@ehu.es) \n");
    printf("Data: Irailak, 2014 \n");
    printf("\n\n");
    printf("FUNTZIO NAGUSIAK \n");
    printf("<?>\t\t Laguntza hau bistaratu \n");
    printf("<ESC>\t\t Programatik irten \n");
    printf("<F>\t\t Objektua bat kargatu\n");
    printf("<TAB>\t\t Kargaturiko objektuen artean bat hautatu\n");
    printf("<DEL>\t\t Hautatutako objektua ezabatu\n");
    printf("<CTRL + ->\t Bistaratze-eremua handitu\n");
    printf("<CTRL + +>\t Bistaratze-eremua txikitu\n");
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
    typeNode *matriz = 0;
    GLdouble wd,he,midx,midy;

    switch (key) {
        case 'f':
        case 'F':
            /*Ask for file*/
            printf("%s", KG_MSSG_SELECT_FILE);
            //scanf("%s", fname);
            //fname = "objektuak/logoehu_ona.obj";
            fname = "/home/set92/Documents/Github/proyectosUniversidad/openGL/exercise2/objektuak/logoehu_ona.obj";
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
                    /* insertar la identidad en la pila */

                    matriz = (typeNode *) malloc(sizeof (typeNode));
                    glGetFloatv(GL_MODELVIEW_MATRIX, matriz->m);
                    insertFirst(matriz);

                    printf("%s\n",KG_MSSG_FILEREAD);
                    break;
            }
            break;

        case 9: /* <TAB> */
            _selected_object = _selected_object->next;
            /*The selection is circular, thus if we move out of the list we go back to the first element*/
            if (_selected_object == 0) _selected_object = _first_object;
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
            break;

        case '+':
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
            break;

        case 'M':
        case 'm'://Activar traslacion
            estado = 1;
            break;

        case 'B':
        case 'b'://Activar rotación
            estado = 2;
            break;

        case 'T':
        case 't'://Activar escalado
            estado = 3;
            break;

        case 'G':
        case 'g'://Activar transformaciones en el sistema de referencia del mundo
            //Transformaciones globales
            estado = 4;
            break;

        case 'L':
        case 'l'://Activar transformaciones en el sistema de referencia local del
            //objeto (objeto 3D, ccámara o luces) )
            estado = 5;
            break;

        case 'O':
        case 'o'://Aplicar transformaciones al objeto seleccionado
            break;

        case 'K':
        case 'k'://Aplicar transformaciones a la cámara actual
            break;

        case 'A':
        case 'a'://Aplicar transformaciones a la luz selecionada
            break;

        case '?':
            print_help();
            break;

        case 'z':
        case 'Z':
            if (glutGetModifiers() == GLUT_ACTIVE_CTRL){
                //Código de deshacer las transformaciones
            }
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
    switch (key) {
        case GLUT_KEY_UP:
            switch(estado){
                case 0:
                    printf("No hay ninguna transformación seleccionada\n");
                    break;
                case 1:
                    printf("Está seleccionada la traslación\n");
                    //traslación +Y
                    break;
                case 2:
                    printf("está seleccionada la rotación\n");
                    //rotación +Y
                    break;
                case 3:
                    printf("está seleccionado el escalado\n");
                    //Escalado +X
                    //glScale(2,0,0);
                    break;
                case 4:
                    break;
                case 5:
                    break;
            }
            break;

        case GLUT_KEY_DOWN:
            switch(estado){
                case 0:
                    printf("No hay ninguna transformación seleccionada\n");
                    break;
                case 1:
                    printf("Está seleccionada la traslación\n");
                    //traslación -Y
                    break;
                case 2:
                    printf("está seleccionada la rotación\n");
                    //rotación -Y
                    break;
                case 3:
                    printf("está seleccionado el escalado\n");
                    //escalado -X
                    //glScale(0.5,0,0)
                    break;
                case 4:
                    break;
                case 5:
                    break;
            }
            break;

        case GLUT_KEY_RIGHT:
            switch(estado){
                case 0:
                    printf("No hay ninguna transformación seleccionada\n");
                    break;
                case 1:
                    printf("Está seleccionada la traslación\n");
                    //Traslación +X
                    break;
                case 2:
                    printf("está seleccionada la rotación\n");
                    //rotación +X
                    break;
                case 3:
                    printf("está seleccionado el escalado\n");
                    //escalado +Y
                    //glScale(0,2,0)
                    break;
                case 4:
                    break;
                case 5:
                    break;
            }
            break;

        case GLUT_KEY_LEFT:
            switch(estado){
                case 0:
                    printf("No hay ninguna transformación seleccionada\n");
                    break;
                case 1:
                    printf("Está seleccionada la traslación\n");
                    //traslación -X
                    break;
                case 2:
                    printf("está seleccionada la rotación\n");
                    //rotación -X
                    break;
                case 3:
                    printf("está seleccionado el escalado\n");
                    //escalado -Y
                    //glScale(0,0.5,0);
                    break;
                case 4:
                    break;
                case 5:
                    break;
            }
            break;

        default:
            printf("El codigo ASCII de la tecla pulsada es %d\n", key );
    }
    glutPostRedisplay();
}