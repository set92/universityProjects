#include <cmath>
#include "intersect.h"
#include "tools.h"

// Comprobar si las 2 BBox colisionan entre si, devolver IINTERSECT si lo hacen, IREJECT en caso contrario
int  BBoxBBoxIntersect(const BBox1 *bba, const BBox1 *bbb ) {
    //En el momento que ves que no colisiona paras de mirar si colisiona, si colisiona miras el resto de ejes
    /*if ((bba->m_min.x() > bbb->m_max.x()) || (bbb->m_min.x() > bba->m_max.x()))
        return IREJECT;
    if ((bba->m_min.y() > bbb->m_max.y()) || (bbb->m_min.y() > bba->m_max.y()))
        return IREJECT;
    if ((bba->m_min.z() > bbb->m_max.z()) || (bbb->m_min.z() > bba->m_max.z()))
        return IREJECT;
    return IINTERSECT;
    */

    if (bba->m_min[0] > bbb->m_max[0] || bbb->m_min[0] > bba->m_max[0]) return IREJECT;
    if (bba->m_min[1] > bbb->m_max[1] || bbb->m_min[1] > bba->m_max[1]) return IREJECT;
    if (bba->m_min[2] > bbb->m_max[2] || bbb->m_min[2] > bba->m_max[2]) return IREJECT;

    return IINTERSECT;

}

// Interseccion de plano y caja. Los comentarios que le valen son del .h
int  BBoxPlaneIntersect (const BBox1 *theBBox, Plane *thePlane) {
    /*BBox1 *aux = new BBox1{{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f}};
    for (int i = 0; i < 3; ++i) {
        if (thePlane->m_n[i] >= 0){
            aux->m_min[i] = theBBox->m_min[i];
            aux->m_max[i] = theBBox->m_max[i];
        }else{
            aux->m_min[i] = theBBox->m_max[i];
            aux->m_max[i] = theBBox->m_min[i];
        }
    }

    if (thePlane->m_n.dot(aux->m_min) + thePlane->m_d > 0) return IREJECT;
    if (thePlane->m_n.dot(aux->m_max) + thePlane->m_d < 0) return -IREJECT;
    return IINTERSECT;
     */

    Vector3 Vmin;
    Vector3 Vmax;

    int min_side;
    int max_side;

    if (thePlane->m_n[0] >= 0.0) {
        Vmin[0] = theBBox->m_min[0];
        Vmax[0] = theBBox->m_max[0];
    } else {
        Vmin[0] = theBBox->m_max[0];
        Vmax[0] = theBBox->m_min[0];
    }

    if (thePlane->m_n[1] >= 0.0) {
        Vmin[1] = theBBox->m_min[1];
        Vmax[1] = theBBox->m_max[1];
    } else {
        Vmin[1] = theBBox->m_max[1];
        Vmax[1] = theBBox->m_min[1];
    }

    if (thePlane->m_n[2] >= 0.0) {
        Vmin[2] = theBBox->m_min[2];
        Vmax[2] = theBBox->m_max[2];
    } else {
        Vmin[2] = theBBox->m_max[2];
        Vmax[2] = theBBox->m_min[2];
    }

    min_side = thePlane->whichSide(Vmin);
    if (min_side > 0) return IREJECT;  // Vmin on possitive side: bbox outside
    max_side = thePlane->whichSide(Vmax);
    if (max_side < 0) return -IREJECT;  // Vmax on negative side: bbox inside
    return IINTERSECT; // Intersecting
}


// Colision entre 2 Esferas.
int BSphereBSphereIntersect(const BSphere *bsa, const BSphere *bsb ) {
    /*
    double distance = (bsb->getPosition() - bsa->getPosition()).lengthSquare();
    distance = pow(distance, 2);
    double radio = pow((bsa->getRadius() + bsb->getRadius()), 2);
	if (distance <= radio) return IINTERSECT;
	else return IREJECT;
    */

    Vector3 v;
    v = bsa->m_centre - bsb->m_centre;
    float ls = v.dot(v);
    float rs = bsa->m_radius + bsb->m_radius;
    if (ls > (rs * rs)) return IREJECT; // Disjoint
    return IINTERSECT; // Intersect
}

// Colision de esfera con plano
int BSpherePlaneIntersect(const BSphere *bs, Plane *pl) {
    /*
    switch (pl->whichSide(bs->getPosition())){
        case 0: return IINTERSECT;
        case -1: return -IREJECT;
        case 1: return IREJECT;
        default: return 2;// No deberia pasar, pero devolvemos un valor erroneo para no dar problemas de memoria
    }
    */
    float dist = pl->signedDistance(bs->m_centre);
    if (fabs(dist) < bs->m_radius)
        return IINTERSECT; // Intersect
    if (dist < 0)
        return -IREJECT; // BSphere inside plane
    return +IREJECT; // BSphere outside plane
}

//Colision entre caja y esfera
int BSphereBBoxIntersect(const BSphere *sphere, const BBox1 *box) {
    /*
    float d = 0, e;
    for (int i = 0; i < 3; ++i) {
        if ((e = sphere->getPosition()[i] - box->m_min[i]) < 0){
            if (e < -sphere->getRadius()) return IREJECT;
            d += pow(e, 2);
        }else{
            if ((e = sphere->getPosition()[i] - box->m_max[i]) > 0) {
                if (e > sphere->getRadius()) return IREJECT;
                d += pow(e, 2);
            }
        }
    }
    if (d > pow(sphere->getRadius(),2)){
        return IREJECT;
    }
    return IINTERSECT;
    */
    float d;
    float aux;
    float r;

    r = sphere->m_radius;
    d = 0;

    aux = sphere->m_centre[0] - box->m_min[0];
    if (aux < 0) {
        if (aux < -r) return IREJECT;
        d += aux*aux;
    } else {
        aux = sphere->m_centre[0] - box->m_max[0];
        if (aux > 0) {
            if (aux > r) return IREJECT;
            d += aux*aux;
        }
    }

    aux = (sphere->m_centre[1] - box->m_min[1]);
    if (aux < 0) {
        if (aux < -r) return IREJECT;
        d += aux*aux;
    } else {
        aux = sphere->m_centre[1] - box->m_max[1];
        if (aux > 0) {
            if (aux > r) return IREJECT;
            d += aux*aux;
        }
    }

    aux = sphere->m_centre[2] - box->m_min[2];
    if (aux < 0) {
        if (aux < -r) return IREJECT;
        d += aux*aux;
    } else {
        aux = sphere->m_centre[2] - box->m_max[2];
        if (aux > 0) {
            if (aux > r) return IREJECT;
            d += aux*aux;
        }
    }
    if (d > r * r) return IREJECT;
    return IINTERSECT;
}


int IntersectTriangleRay(const Vector3 & P0,
						 const Vector3 & P1,
						 const Vector3 & P2,
						 const Line *l,
						 Vector3 & uvw) {
	Vector3 e1(P1 - P0);
	Vector3 e2(P2 - P0);
	Vector3 p(crossVectors(l->m_d, e2));
	float a = e1.dot(p);
	if (fabs(a) < Constants::distance_epsilon) return IREJECT;
	float f = 1.0f / a;
	// s = l->o - P0
	Vector3 s(l->m_O - P0);
	float lu = f * s.dot(p);
	if (lu < 0.0 || lu > 1.0) return IREJECT;
	Vector3 q(crossVectors(s, e1));
	float lv = f * q.dot(l->m_d);
	if (lv < 0.0 || lv > 1.0) return IREJECT;
	uvw[0] = lu;
	uvw[1] = lv;
	uvw[2] = f * e2.dot(q);
	return IINTERSECT;
}

/* IREJECT 1 */
/* IINTERSECT 0 */

const char *intersect_string(int intersect) {

	static const char *iint = "IINTERSECT";
	static const char *prej = "IREJECT";
	static const char *mrej = "-IREJECT";
	static const char *error = "IERROR";

	const char *result = error;

	switch (intersect) {
	case IINTERSECT:
		result = iint;
		break;
	case +IREJECT:
		result = prej;
		break;
	case -IREJECT:
		result = mrej;
		break;
	}
	return result;
}
