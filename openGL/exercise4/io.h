#ifndef IO_H
#define IO_H
#include "definitions.h"

void print_help();
void insertarCamara(struct camera *cam);
void actualizarCamara();
void inicializarCamara();
void calcularNormales(object3d *optr);
void actualizarFoco();
void copiarContenidoArray(GLfloat matrizOrigen[4], GLfloat matrizDestino[4]);
void opcionSuprimir(object3d *auxiliar_object);
void keyboard(unsigned char key, int x, int y);
int existeLuzEncendida();
void disableLights();
void enableLights();
void rotarFoco(int index1, int index2, int valorMultipl, int valorMultipl2, float angle);
void rotarLuz(int index1, int index2, int valorMultipl, int valorMultipl2, float angle);
void nuevaLuz(int ind);
void cambiarEstadoLuz(int luz);
void seleccionarMaterial(int num);
void onOffIluminacion();
void SpecialKeys(int key, int x, int y);

#endif // IO_H
