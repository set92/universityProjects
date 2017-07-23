//
// Created by set92 on 8/05/17.
//

#ifndef VEVPROJECT_PROJECTIVETEXTURE_H
#define VEVPROJECT_PROJECTIVETEXTURE_H

#include <stdio.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <Shading/texture.h>
#include <Camera/camera.h>


typedef struct{
    Texture *tex; //Variable textura
    Camera *cam;
    //Trfm3D *trfmTodo;
}ProjectiveTexture;

//Crea una textura proyectiva
ProjectiveTexture  *CreateProjectiveTexture(char *name,
                                            Vector3 m_E,
                                            Vector3 m_At,
                                            Vector3 m_Up,
                                            float fovy, float aspect, float near, float far);
//Destruye una textura proyectiva
void DestroyProjectiveTexture(ProjectiveTexture **thisPT);
void OpenGLTrfmTexture(ProjectiveTexture *thisPT, float *glmatrix);
void BindGLProjectiveTexture(ProjectiveTexture *thisPT);
void PlaceSceneProjectiveTexture(ProjectiveTexture *thisPT);
void printProjectiveTexture(ProjectiveTexture *thisPT);


#endif //VEVPROJECT_PROJECTIVETEXTURE_H
