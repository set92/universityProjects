#ifndef IO_H
#define IO_H
#include "definitions.h"


void insertarCamara(struct camera *cam);
void actualizarCamara();
void inicializarCamara();
void keyboard(unsigned char key, int x, int y);
void print_help();
void SpecialKeys(int key, int x, int y);


#endif // IO_H
