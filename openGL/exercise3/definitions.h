#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#ifdef __linux__

#include <GL/gl.h>

#elif __APPLE__
#include <OpenGL/gl.h>
#endif

/** DEFINITIONS **/

#define KG_WINDOW_TITLE                     "Transformaciones geometricas"
#define KG_WINDOW_WIDTH                     600
#define KG_WINDOW_HEIGHT                    400
#define KG_WINDOW_X                         50
#define KG_WINDOW_Y                         50

#define KG_MSSG_SELECT_FILE                 "Escribe el path del objeto:"
#define KG_MSSG_FILENOTFOUND                "Ese fichero no existe!"
#define KG_MSSG_INVALIDFILE                 "Ha habido algún tipo de error con el fichero..."
#define KG_MSSG_EMPTYFILE                   "El fichero está vacío."
#define KG_MSSG_FILEREAD                    "Lectura del fichero finalizada."

#define KG_STEP_MOVE                        5.0f
#define KG_STEP_ROTATE                      10.0f
#define KG_STEP_ZOOM                        0.75
#define KG_STEP_CAMERA_ANGLE                5.0f

#define KG_ORTHO_X_MIN_INIT                -5
#define KG_ORTHO_X_MAX_INIT                 5
#define KG_ORTHO_Y_MIN_INIT                -5
#define KG_ORTHO_Y_MAX_INIT                 5
#define KG_ORTHO_Z_MIN_INIT                -100
#define KG_ORTHO_Z_MAX_INIT                 10000

#define KG_COL_BACK_R                       0.30f
#define KG_COL_BACK_G                       0.30f
#define KG_COL_BACK_B                       0.30f
#define KG_COL_BACK_A                       1.00f

#define KG_COL_SELECTED_R                   1.00f
#define KG_COL_SELECTED_G                   0.75f
#define KG_COL_SELECTED_B                   0.00f

#define KG_COL_NONSELECTED_R                1.00f
#define KG_COL_NONSELECTED_G                1.00f
#define KG_COL_NONSELECTED_B                1.00f

#define KG_COL_X_AXIS_R                     1.0f
#define KG_COL_X_AXIS_G                     0.0f
#define KG_COL_X_AXIS_B                     0.0f

#define KG_COL_Y_AXIS_R                     0.0f
#define KG_COL_Y_AXIS_G                     1.0f
#define KG_COL_Y_AXIS_B                     0.0f

#define KG_COL_Z_AXIS_R                     0.0f
#define KG_COL_Z_AXIS_G                     0.0f
#define KG_COL_Z_AXIS_B                     1.0f

#define KG_MAX_DOUBLE                       10E25

/** STRUCTURES **/

/****************************
 * Structure to store the   *
 * coordinates of 3D points *
 ****************************/
typedef struct {
    GLdouble x, y, z;
} point3;

/*****************************
 * Structure to store the    *
 * coordinates of 3D vectors *
 *****************************/
typedef struct {
    GLdouble x, y, z;
} vector3;

/****************************
 * Structure to store the   *
 * colors in RGB mode       *
 ****************************/
typedef struct {
    GLfloat r, g, b;
} color3;

/****************************
 * Structure to store       *
 * objects' vertices        *
 ****************************/
typedef struct {
    point3 coord;                       /* coordinates,x, y, z */
    GLint num_faces;                    /* number of faces that share this vertex */
} vertex;

/****************************
 * Structure to store       *
 * objects' faces or        *
 * polygons                 *
 ****************************/
typedef struct {
    GLint num_vertices;                 /* number of vertices in the face */
    GLint *vertex_table;                /* table with the index of each vertex */
} face;


/****************************
 * Structure to store a     *
 * pile of 3D objects       *
 ****************************/
struct object3d {
    GLint num_vertices;                 /* number of vertices in the object*/
    vertex *vertex_table;               /* table of vertices */
    GLint num_faces;                    /* number of faces in the object */
    face *face_table;                   /* table of faces */
    point3 min;                         /* coordinates' lower bounds */
    point3 max;                         /* coordinates' bigger bounds */
    struct object3d *next;              /* next element in the pile of objects */
    struct camera *camara;
    struct typeNode *pila;              /* pila de transformaciones */
    float mat_rot_cam[16];
};

struct camera {
    int pertenece_a_objeto;                             /* cámara de objeto(1) o no (0)*/

    int modo;                                           /* Proyección paralela o en perspectiva */
    GLdouble left, right, bottom, top, nearVal, farVal; /* Parametros necesarios para glFrustum */
    float miCamara[16];                                 /* Referencia a nuestra cámara */
    float m[16];                                        /* Matriz devuelta por lookAt */

    struct camera *next;
    struct camera *prev;
};

struct typeNode {
    float m[16];

    struct typeNode *next;
    struct typeNode *prev;
};

typedef struct object3d object3d;
typedef struct typeNode typeNode;
typedef struct camera camera;

#endif // DEFINITIONS_H
