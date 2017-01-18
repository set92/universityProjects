#include <stdio.h>
#include "display.h"
#include "io.h"
#include "definitions.h"

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

/** GLOBAL VARIABLES **/

GLdouble _window_ratio;                     /*Control of window's proportions */
GLdouble _ortho_x_min, _ortho_x_max;         /*Variables for the control of the orthographic projection*/
GLdouble _ortho_y_min, _ortho_y_max;        /*Variables for the control of the orthographic projection*/
GLdouble _ortho_z_min, _ortho_z_max;         /*Variables for the control of the orthographic projection*/

object3d *_first_object = 0;                /*List of objects*/
object3d *_selected_object = 0;            /*Object currently selected*/

camera *camara;
camera *first_camara;

light *arrayLuces[8];
light *luzSeleccionada;

material *mat[3];

int flat_or_smooth = 0; // 0-> flat, 1->smooth
extern int foco_debug;

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
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);

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

void initializationLights() {
    
    glEnable(GL_LIGHTING); //enable the lighting

    glEnable(GL_LIGHT0); // Por si acabo no esta on la 0, la encendemos.
    
    glEnable(GL_NORMALIZE);

    arrayLuces[0] = (light *) malloc(sizeof(light));
    arrayLuces[0]->estado = 2;
    arrayLuces[0]->info = (lightInfo *) malloc(sizeof(lightInfo));

    arrayLuces[0]->info->tipo = 0;
    arrayLuces[0]->info->numero = GL_LIGHT0;

    arrayLuces[0]->info->diffuseLight[0] = 0.6;
    arrayLuces[0]->info->diffuseLight[1] = 0.6;
    arrayLuces[0]->info->diffuseLight[2] = 0.6;
    arrayLuces[0]->info->diffuseLight[3] = 1.0;

    arrayLuces[0]->info->ambientLight[0] = 0.8;
    arrayLuces[0]->info->ambientLight[1] = 0.8;
    arrayLuces[0]->info->ambientLight[2] = 0.8;
    arrayLuces[0]->info->ambientLight[3] = 1.0;

    arrayLuces[0]->info->specularLight[0] = 0.5;
    arrayLuces[0]->info->specularLight[1] = 0.5;
    arrayLuces[0]->info->specularLight[2] = 0.5;
    arrayLuces[0]->info->specularLight[3] = 1.0;

    arrayLuces[0]->info->positionLight[0] = 0.0001;
    arrayLuces[0]->info->positionLight[1] = 1.0001;
    arrayLuces[0]->info->positionLight[2] = 0.0001;
    arrayLuces[0]->info->positionLight[3] = 0.0;

    arrayLuces[0]->info->spotAttenuation[0] = 1.0;
    arrayLuces[0]->info->spotAttenuation[1] = 0.0;
    arrayLuces[0]->info->spotAttenuation[2] = 0.0;

    arrayLuces[1] = (light *) malloc(sizeof(light));
    arrayLuces[1]->estado = 1;
    arrayLuces[1]->info = (lightInfo *) malloc(sizeof(lightInfo));

    arrayLuces[1]->info->tipo = 1;
    arrayLuces[1]->info->numero = GL_LIGHT1;

    arrayLuces[1]->info->diffuseLight[0] = 0.6;
    arrayLuces[1]->info->diffuseLight[1] = 0.6;
    arrayLuces[1]->info->diffuseLight[2] = 0.6;
    arrayLuces[1]->info->diffuseLight[3] = 1.0;

    arrayLuces[1]->info->ambientLight[0] = 0.4;
    arrayLuces[1]->info->ambientLight[1] = 0.4;
    arrayLuces[1]->info->ambientLight[2] = 0.4;
    arrayLuces[1]->info->ambientLight[3] = 1.0;

    arrayLuces[1]->info->specularLight[0] = 0.2;
    arrayLuces[1]->info->specularLight[1] = 0.2;
    arrayLuces[1]->info->specularLight[2] = 0.2;
    arrayLuces[1]->info->specularLight[3] = 1.0;

    arrayLuces[1]->info->positionLight[0] = 1.0;
    arrayLuces[1]->info->positionLight[1] = 20.0;
    arrayLuces[1]->info->positionLight[2] = 1.0;
    arrayLuces[1]->info->positionLight[3] = 1.0;

    arrayLuces[1]->info->spotAttenuation[0] = 1.0;
    arrayLuces[1]->info->spotAttenuation[1] = 0.0;
    arrayLuces[1]->info->spotAttenuation[2] = 0.0;

    arrayLuces[2] = (light *) malloc(sizeof(light));
    arrayLuces[2]->estado = 1;
    arrayLuces[2]->info = (lightInfo *) malloc(sizeof(lightInfo));

    arrayLuces[2]->info->tipo = 2;
    arrayLuces[2]->info->numero = GL_LIGHT2;

    arrayLuces[2]->info->diffuseLight[0] = 0.5;
    arrayLuces[2]->info->diffuseLight[1] = 0.5;
    arrayLuces[2]->info->diffuseLight[2] = 0.5;
    arrayLuces[2]->info->diffuseLight[3] = 1.0;

    arrayLuces[2]->info->ambientLight[0] = 0.5;
    arrayLuces[2]->info->ambientLight[1] = 0.5;
    arrayLuces[2]->info->ambientLight[2] = 0.5;
    arrayLuces[2]->info->ambientLight[3] = 1.0;

    arrayLuces[2]->info->specularLight[0] = 0.5;
    arrayLuces[2]->info->specularLight[1] = 0.5;
    arrayLuces[2]->info->specularLight[2] = 0.5;
    arrayLuces[2]->info->specularLight[3] = 1.0;

    arrayLuces[2]->info->positionLight[0] = 0.0;
    arrayLuces[2]->info->positionLight[1] = 30.0;
    arrayLuces[2]->info->positionLight[2] = 0.0;
    arrayLuces[2]->info->positionLight[3] = 1.0;

    arrayLuces[2]->info->spotCutoff = 20.0;

    arrayLuces[2]->info->spotExponent = 1.0;

    arrayLuces[2]->info->spotDirection[0] = 0.0;
    arrayLuces[2]->info->spotDirection[1] = -1.0;
    arrayLuces[2]->info->spotDirection[2] = 0.0;

    arrayLuces[2]->info->spotAttenuation[0] = 1.0;
    arrayLuces[2]->info->spotAttenuation[1] = 0.0;
    arrayLuces[2]->info->spotAttenuation[2] = 0.0;

    for (int i = 3; i <= 7; i++){
        arrayLuces[i] = (light *) malloc(sizeof(light));
        arrayLuces[i]->estado = 0;
    }

    luzSeleccionada = arrayLuces[0];

}

void asignarValores(GLfloat matriz[4], float red, float green, float blue, float alpha){
    matriz[0] = red;
    matriz[1] = green;
    matriz[2] = blue;
    matriz[3] = alpha;
}

void crearMateriales(){
    for (int i = 0; i <= 3; i++) {
        mat[i] = (material *) malloc(sizeof(material));
    }
    
    //bronce
    asignarValores(mat[0]->matAmb, 0.21, 0.12, 0.05, 1.0);
    asignarValores(mat[0]->matDiff, 0.71, 0.42, 0.18, 1.0);
    asignarValores(mat[0]->matSpec, 0.39, 0.27, 0.16, 1.0);
    mat[0]->matShininess = 0.2;

    //rubi
    asignarValores(mat[1]->matAmb, 0.1745, 0.1175, 0.1175, 1.0);
    asignarValores(mat[1]->matDiff, 0.61424, 0.04136, 0.04136, 1.0);
    asignarValores(mat[1]->matSpec, 0.727811, 0.626959, 0.626959, 1.0);
    mat[1]->matShininess = 0.6;

    //gold
    asignarValores(mat[2]->matAmb, 0.24725, 0.1995, 0.0745, 1.0);
    asignarValores(mat[2]->matDiff, 0.75164, 0.60648, 0.22648, 1.0);
    asignarValores(mat[2]->matSpec, 0.628281, 0.555802, 0.366065, 1.0);
    mat[2]->matShininess = 0.4;

    //emerald
    asignarValores(mat[3]->matAmb, 0.0215, 0.1745, 0.0215, 1.0);
    asignarValores(mat[3]->matDiff, 0.07568, 0.61424, 0.07568, 1.0);
    asignarValores(mat[3]->matSpec, 0.633, 0.727811, 0.633, 1.0);
    mat[3]->matShininess = 0.6;
}

void rightClickMenu(int value) {
    switch(value){
        case 0: exit(0); break; //salir
        case 1: print_help(); break; //ayuda
		case 2: onOffIluminacion(); break; //des/activar iluminacion
        case 3: foco_debug = !foco_debug; break; //Activar o desactivar modo debug del foco
		case 7: opcionSuprimir(_selected_object); break; // Eliminar objeto

		case 11: break;
		case 12: break;
		case 13: break;

		case 21: seleccionarMaterial(1); break; //Materiales
		case 22: seleccionarMaterial(2); break;
		case 23: seleccionarMaterial(3); break;
		case 24: seleccionarMaterial(4); break;

		case 31: cambiarEstadoLuz(0); break; //Materiales
		case 32: cambiarEstadoLuz(1); break;
		case 33: cambiarEstadoLuz(2); break;
		case 34: cambiarEstadoLuz(3); break;
		case 35: cambiarEstadoLuz(4); break; //Materiales
		case 36: cambiarEstadoLuz(5); break;
		case 37: cambiarEstadoLuz(6); break;
		case 38: cambiarEstadoLuz(7); break;
		
    }
	glutPostRedisplay();
}

void initMenu(){
    static int menu_id, submenu_objetos, submenu_material, submenu_iluminacion, submenu_luces;

	//submenus
	submenu_material = glutCreateMenu(rightClickMenu);
	glutAddMenuEntry("Bronce", 21);
	glutAddMenuEntry("Rubi", 22);
	glutAddMenuEntry("Oro", 23);
	glutAddMenuEntry("Esmeralda", 24);
	//submenu objetos
    submenu_objetos = glutCreateMenu(rightClickMenu);
    glutAddSubMenu("Cambiar material", submenu_material);
	glutAddMenuEntry("Borrar Objeto", 7);
	//glutAddMenuEntry("Rotar", 11);
	//glutAddMenuEntry("Trasladar", 12);
	//glutAddMenuEntry("Escalar", 13);

	submenu_iluminacion = glutCreateMenu(rightClickMenu);
	glutAddMenuEntry("Des/activar iluminacion", 2);
    glutAddMenuEntry("Modo debug foco", 3);
	glutAddSubMenu("Des/activar Luces", submenu_luces);
	glutAddMenuEntry("Luz 1", 31);
	glutAddMenuEntry("Luz 2", 32);
	glutAddMenuEntry("Luz 3", 33);
	glutAddMenuEntry("Luz 4", 34);
	glutAddMenuEntry("Luz 5", 35);
	glutAddMenuEntry("Luz 6", 36);
	glutAddMenuEntry("Luz 7", 37);
	glutAddMenuEntry("Luz 8", 38);

	//menu principal
    menu_id = glutCreateMenu(rightClickMenu);

    glutAddMenuEntry("Mostrar ayuda", 1);
    glutAddSubMenu("Objetos", submenu_objetos);
	glutAddSubMenu("Iluminacion", submenu_iluminacion);

    glutAddMenuEntry("Quit", 0);     
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/** MAIN FUNCTION **/
int main(int argc, char **argv) {

    /*First of all, print the help information*/
    print_help();

    /* glut initializations */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
    //glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(KG_WINDOW_WIDTH, KG_WINDOW_HEIGHT);
    glutInitWindowPosition(KG_WINDOW_X, KG_WINDOW_Y);
    glutCreateWindow(KG_WINDOW_TITLE);
    
    glEnable(GL_DEPTH_TEST); // Activar z-buffer

    //Definimos una luz global que afecte a todos los objetos, no necesario salvo que queramos 2 luces distintas
    GLfloat global_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    //Decimos que la luz que incida sobre nuestros poligonos sera suave, mas calculos pero mas bonita
    if (flat_or_smooth) glShadeModel(GL_SMOOTH);
    else glShadeModel(GL_FLAT);

    /* set the callback functions */
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(SpecialKeys);

    /* this initialization has to be AFTER the creation of the window */
    initMenu();
    initialization();
    initializationLights();
    crearMateriales();
    
    /* start the main loop */
    glutMainLoop();
    return 0;
}
