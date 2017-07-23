#include <cstdio>
#include <cmath>
#include "camera.h"
#include "tools.h"
#include "intersect.h"

static Trfm3D LOCAL_Trfm;

Camera::Camera() :
	m_viewTrfm(new Trfm3D),
	m_projTrfm(new Trfm3D),
	m_E(Vector3::ZERO),
	m_At(0.0f, 0.0f, -1.0f),
	m_Up(0.0f, 1.0f, 0.0f),
	m_R(Vector3::UNIT_X),
	m_U(Vector3::UNIT_Y),
	m_D(Vector3::UNIT_Z) {
	for(int i = 0; i < MAX_CLIP_PLANES; ++i)
		m_fPlanes[i] = new Plane();
}

Camera::~Camera() {
	delete m_viewTrfm;
	delete m_projTrfm;
	for (int i=0; i<MAX_CLIP_PLANES; ++i)
		delete m_fPlanes[i];
}

PerspectiveCamera::PerspectiveCamera() :
	m_fovy(60.0f * Constants::degree_to_rad) {
	m_type = perspective;
	m_near = 0.1f;
	m_far = 1500.0f;
	m_aspectRatio = 1.0f;
	m_left = -0.034451;
	m_bottom = -0.026795;
	m_right = 0.034451;
	m_top = 0.026795;
	m_projTrfm->setFrustum(m_left, m_right,
						   m_bottom, m_top,
						   m_near, m_far);
}

PerspectiveCamera::~PerspectiveCamera() {}

void PerspectiveCamera::init(float fovy, float aspect,
							 float near, float far) {
	m_fovy = fovy;
	m_aspectRatio = aspect;
	m_near = near;
	m_far = far;
	updateProjection();
}

OrthographicCamera::OrthographicCamera() {
	m_type = orthographic;
	m_near = 0.1f;
	m_far = 1500.0f;
	m_left = -0.034451;
	m_bottom = -0.026795;
	m_right = 0.034451;
	m_top = 0.026795;
	m_projTrfm->setOrtho(m_left, m_right,
						 m_bottom, m_top,
						 m_near, m_far);
}

OrthographicCamera::~OrthographicCamera() {}

void OrthographicCamera::init(float left, float right,
							  float bottom, float top,
							  float near, float far) {
	m_left = left;
	m_right = right;
	m_bottom = bottom;
	m_top = top;
	m_near = near;
	m_far = far;
	updateProjection();
}

////////////////////////////////////////////////////////////7
// Projection stuff

void OrthographicCamera::onResize(int w, int h) {}
void PerspectiveCamera::onResize(int w, int h ) {
	if( h > 0 )
		m_aspectRatio = (float) w / (float) h;    // width/height
	else
		m_aspectRatio = 1.0f;
	updateProjection();
}

// zoom camera

void Camera::zoom(float angle) {}
void PerspectiveCamera::zoom(float angle) {
	m_fovy = angle;
	updateProjection();
}

float Camera::getZoom() const { return 0.0f; }
float PerspectiveCamera::getZoom() const { return m_fovy; }

void OrthographicCamera::updateProjection() {
	m_projTrfm->setOrtho(m_left, m_right,
						 m_bottom, m_top,
						 m_near, m_far);
	updateFrustumPlanes();
}

// @@ TODO:
// * Given (near, far, aspectRatio, fovy), calculate the values of
//   frustum (top, bottom, right, left).
// * Also, update projection matrix (projTrfm)

void PerspectiveCamera::updateProjection() {
	float top, bottom, left, right;

	top = m_near * tanf(m_fovy/2);
	bottom = -top;
	right = m_aspectRatio * top;
	left= -right;

	m_top = top;
	m_bottom = bottom;
	m_left = left;
	m_right = right;

	// Actualizar matriz de proyeccion
    m_projTrfm->setFrustum(m_left, m_right,
                           m_bottom, m_top,
                           m_near, m_far);

	// Leave next line as-is
	updateFrustumPlanes();
}



////////////////////////////////////////////////////////////7
// View transformation stuff

void Camera::setViewTrfm() {
	m_viewTrfm->setWorld2Local(m_E, m_R, m_U, m_D);
	updateFrustumPlanes();
}

// @@ TODO:
/**
 * Calculate (R, U, D) vectors of the camera frame given (E, At, Up)
 * E en las diapos es V
 *
 */
// Dicho de otra manera, es el Actualizar cambio de vista, hay que generar una matriz, valores de ella en diapo 43
void Camera::updateFrame () {

	Vector3 f;
	// vector de A a E
	f = (m_E - m_At);
	// vector unitario (normalizado) == dividir por su modulo
	f.normalize();

	m_Up.normalize();
	m_R = crossVectors(m_Up, f);
	m_U = crossVectors(f, m_R);
	m_D = f;

	// leave next line as-is
	setViewTrfm();
}

void  Camera::lookAt(const Vector3 & E,
					 const Vector3 & at,
					 const Vector3 & up) {
	m_E = E;
	m_At= at;
	m_Up = up;
	m_Up.normalize();
	Vector3 VA(at - E);
	if (VA.isZero()) {
		fprintf(stderr, "[W] while setting camera (%s): V & A are too near\n", m_name.size() ? m_name.c_str() : "noname" );
		m_At += Vector3(1.0f, 1.0f, 1.0f);
		VA += Vector3(1.0f, 1.0f, 1.0f);
	}
	VA.normalize();
	// Check if VA & up are colinear
	if( fabs( VA.dot(m_Up) ) > 1.0f - Constants::angle_epsilon ) {
		fprintf(stderr, "[W] while setting camera (%s): up is nearly parallel to VA\n", m_name.size() ? m_name.c_str() : "noname" );
		m_Up[0] += 1.0f;
		if(fabs( VA.dot(m_Up) ) > 1.0f - Constants::angle_epsilon ) // last check
			m_Up[1] += 1.0;
	}
	updateFrame();
}

////////////////////////////////////////////////////////////7
// get/set

const std::string & Camera::getName() const { return m_name; };
void Camera::setName(const std::string & n) { m_name = n; };

void Camera::setFar(float far) { m_far = far; updateProjection(); }
float Camera::getFar() const { return m_far; }
void Camera::setNear(float near) { m_near = near; updateProjection(); }
float Camera::getNear() const { return m_near; }
Vector3 Camera::getPosition() const { return m_E; }
Vector3 Camera::getDirection() const { return -1.0f * m_D; }

////////////////////////////////////////////////
// trfm transformations

const Trfm3D *Camera::viewTrfm() const { return m_viewTrfm;; }
const Trfm3D *Camera::projectionTrfm() const {return m_projTrfm; }
void Camera::viewTrfmGL(float *gmatrix) const { m_viewTrfm->getGLMatrix(gmatrix); }
void Camera::projectionTrfmGL(float *gmatrix) const  { m_projTrfm->getGLMatrix(gmatrix); }

////////////////////////////////////////////////
// Movement

// @@ TODO:
// Move the camera "step" units ahead. Fly mode.
//
// thisCamera         -> the camera
// step               -> number of units to fly (can be negative)

void Camera::fly(float step) {//3 lineas
	//Modificamos en el eje X, Y y Z
	m_E = m_E - step*m_D;
	m_At = m_At - step*m_D;

	setViewTrfm();
}

// @@ TODO:
// Move the camera "step" units ahead. Walk mode.
//
// thisCamera         -> the camera
// step               -> number of units to walk (can be negative)

void Camera::walk(float step) {//5 lineas

	//Modificamos solo en el eje X y el Z
	m_E.x() = m_E.x() - step*m_D.x();
	m_E.z() = m_E.z() - step*m_D.z();

	m_At.x() = m_At.x() - step*m_D.x();
	m_At.z() = m_At.z() - step*m_D.z();

	setViewTrfm();
}

void  Camera::panX(float step) {
	m_E += step * m_R;
	m_At += step * m_R;
	setViewTrfm();

}

void  Camera::panY(float step) {
	m_E += step * m_U;
	m_At += step * m_U;
	setViewTrfm();

}

void  Camera::pitch(float angle) {

	LOCAL_Trfm.setRotAxis(m_R, m_E, angle);
	m_At = LOCAL_Trfm.transformPoint(m_At);
	m_Up = LOCAL_Trfm.transformVector(m_Up);
	updateFrame();
}

void  Camera::yaw(float angle) {

	LOCAL_Trfm.setRotAxis(m_U, m_E, angle);
	m_At = LOCAL_Trfm.transformPoint(m_At);
	m_Up = LOCAL_Trfm.transformVector(m_Up);
	updateFrame();
}

void  Camera::roll(float angle) {

	LOCAL_Trfm.setRotAxis(m_D, m_E, -angle);
	m_At = LOCAL_Trfm.transformPoint(m_At);
	m_Up = LOCAL_Trfm.transformVector(m_Up);
	updateFrame();
}

// Rotate camera around world's Y axis

void Camera::viewYWorld(float angle) {
	LOCAL_Trfm.setRotAxis(Vector3::UNIT_Y, m_E, angle);
	m_At = LOCAL_Trfm.transformPoint(m_At);
	m_Up = LOCAL_Trfm.transformVector(m_Up);
	updateFrame();
}

void  Camera::arcOverUnder(float angle) {
	LOCAL_Trfm.setRotAxis(m_R, m_At, angle);
	m_E = LOCAL_Trfm.transformPoint(m_E);
	m_Up = LOCAL_Trfm.transformVector(m_Up);
	updateFrame();
}

void  Camera::arcLeftRight(float angle) {
	LOCAL_Trfm.setRotAxis(m_U, m_At, angle);
	m_E = LOCAL_Trfm.transformPoint(m_E);
	m_Up = LOCAL_Trfm.transformVector(m_Up);
	updateFrame();
}

// @@ TODO: Check frustum (look at camera.h for parameter descriptions and return
//          values)

/**
 *	Dado un bounding box, revisar si esta dentro del area visible o no.
 *
 * @param thisCamera the Camera.
 * @param theBBox the Bounding Box (in world coordinates).
 * @param planesBitM points to a bitmask where bit i is set if BBOX fully inside the i-th frustum plane.
 *
 * @return
 *     -1 BBOX fully inside
 *     0  BBOX intersects frustum
 *     +1 BBOX fully outside frustum
 */

int Camera::checkFrustum(const BBox1 *theBBox,
						 unsigned int *planesBitM) {
    int intersect = -1, result = 0;

    for (int i = 0; i < MAX_CLIP_PLANES; ++i) {
		result = BBoxPlaneIntersect(theBBox, m_fPlanes[i]);
		if(result == IREJECT) return 1;
		if(result == IINTERSECT) intersect = 0;
	}
	return intersect; // BBox is fully inside the frustum
}

/////////////////////////////////////////////////////////////////////////////////////
// Hemendik aurrera ez

void Camera::updateFrustumPlanes() {

	static GLfloat M[16];
	Plane *p;

	// V: view transformation
	// P: perspective transformation
	// T = P*V

	Trfm3D T(*m_projTrfm); // T = P;
	T.add(m_viewTrfm); // T = P*V
	T.getGLMatrix(M);

	// Extract the planes parameters

	// left plane
	p = m_fPlanes[0];

	p->m_n[0] = -M[3]  - M[0];  // -(m_41 + m_11)
	p->m_n[1] = -M[7]  - M[4];  // -(m_42 + m_12)
	p->m_n[2] = -M[11] - M[8];  // -(m_43 + m_13)
	p->m_d =     M[15] + M[12]; //  (m_44 + m_14), because d in plane is really (-d)
	p->m_isNorm = false;

	// right plane
	p = m_fPlanes[1];
	p->m_n[0] = -M[3]  + M[0];  // -(m_41 - m_11)
	p->m_n[1] = -M[7]  + M[4];  // -(m_42 - m_12)
	p->m_n[2] = -M[11] + M[8];  // -(m_43 - m_13)
	p->m_d =     M[15] - M[12]; //  (m_44 - m_14) because d in plane is really (-d)
	p->m_isNorm = false;

	// bottom plane
	p = m_fPlanes[2];
	p->m_n[0] = -M[3]  - M[1];  // -(m_41 + m_21)
	p->m_n[1] = -M[7]  - M[5];  // -(m_42 + m_22)
	p->m_n[2] = -M[11] - M[9];  // -(m_43 + m_23)
	p->m_d =     M[15] + M[13]; //  (m_44 + m_24) because d in plane is really (-d)
	p->m_isNorm = false;

	// top plane
	p = m_fPlanes[3];
	p->m_n[0] = -M[3]  + M[1];   // -(m_41 - m_21)
	p->m_n[1] = -M[7]  + M[5];   // -(m_42 - m_22)
	p->m_n[2] = -M[11] + M[9];   // -(m_43 - m_23)
	p->m_d =     M[15] - M[13];  //  (m_44 - m_24) because d in plane is really (-d)
	p->m_isNorm = false;

	// near plane
	p = m_fPlanes[4];
	p->m_n[0] = -M[3]  - M[2];  // -(m_41 + m_31)
	p->m_n[1] = -M[7]  - M[6];  // -(m_42 + m_32)
	p->m_n[2] = -M[11] - M[10]; // -(m_43 + m_33)
	p->m_d =     M[15] + M[14]; //  (m_44 + m_34) because d in plane is really (-d)
	p->m_isNorm = false;

	// far plane
	p = m_fPlanes[5];
	p->m_n[0] = -M[3]  + M[2];  // -(m_41 - m_31)
	p->m_n[1] = -M[7]  + M[6];  // -(m_42 - m_32)
	p->m_n[2] = -M[11] + M[10]; // -(m_43 - m_33)
	p->m_d =     M[15] - M[14]; //  (m_44 - m_34) because d in plane is really (-d)
	p->m_isNorm = false;
	// It is not neccesary to normalize the planes for frustum calculation
}

void Camera::print( ) {

	printf("View Point    : %.4f %.4f %.4f\n", m_E[0], m_E[1], m_E[1]);
	printf("Look At Point : %.4f %.4f %.4f\n", m_At[0], m_At[1], m_At[1]);
	printf("Up Vector     : %.4f %.4f %.4f\n", m_Up[0], m_Up[1], m_Up[2] );
	printf("Frame\n");
	printf("R : %.4f %.4f %.4f\n", m_R[0], m_R[1], m_R[2] );
	printf("U : %.4f %.4f %.4f\n", m_U[0], m_U[1], m_U[2] );
	printf("D : %.4f %.4f %.4f\n", m_D[0], m_D[1], m_D[2] );
	printf("View trfm:\n");
	m_viewTrfm->print();
}

void PerspectiveCamera::print( ) {
	printf("*** Perspective camera: %s\n", m_name.size() ? m_name.c_str() : "(noname)");
	Camera::print();
	printf("Fovy %.4f Near %.4f Far %.4f\n",  m_fovy * Constants::rad_to_degree,
		   m_near, m_far );
	printf("Ortho l,b,n min  %.4f %.4f %.4f\n", m_left, m_bottom, m_near);
	printf("      r,t,f max  %.4f %.4f %.4f\n", m_right, m_top, m_far);
	printf("Projection trfm:\n");
	m_projTrfm->print();
}

void OrthographicCamera::print( ) {
	printf("*** Orthographic camera: %s\n", m_name.size() ? m_name.c_str() : "(noname)");
	Camera::print();
	printf("Ortho l,b,n min  %.4f %.4f %.4f\n", m_left, m_bottom, m_near);
	printf("      r,t,f max  %.4f %.4f %.4f\n", m_right, m_top, m_far);
	printf("Projection trfm:\n");
	m_projTrfm->print();

}
