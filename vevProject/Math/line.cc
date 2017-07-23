#include <cassert>
#include <cstdio>
#include "line.h"
#include "tools.h"

Line::Line() : m_O(Vector3::ZERO), m_d(Vector3::UNIT_Y) {}
Line::Line(const Vector3 & o, const Vector3 & d) : m_O(o), m_d(d) {}
Line::Line(const Line & line) : m_O(line.m_O), m_d(line.m_d) {}

Line & Line::operator=(const Line & line) {
	if (&line != this) {
		m_O = line.m_O;
		m_d = line.m_d;
	}
	return *this;
}

// Hacer que una linea pase a traves del pto A y B. Comprobar que los ptos no estan muy cerca.
void Line::setFromAtoB(const Vector3 & A, const Vector3 & B) {
    /* if(!((B-A).isZero())){
        m_d = (B - A);
        m_d.normalize();
        m_O = A;
    }*/
    Vector3 d = B - A; // from A to B
    float mod = d.normalize();
    assert(mod > Constants::distance_epsilon);
    m_O = A;
    m_d = d;

}

// Dado un numero hallar su punto mediante la formula p(u)=o+u*d
Vector3 Line::at(float u) const {
	Vector3 res = Vector3(0.0f, 0.0f,  0.0f);
    res = m_O + (u * m_d);

    return res;
}

// Calcular el parametro u0 de un pto de la linea que sea el mas cercano a P mediante la siguiente formula
// u0 = D*(P-O) / D*D , where * == dot product
float Line::paramDistance(const Vector3 & P) const {
	/*
    float denom = m_d.dot(m_d);

    //Si D * D es 0 entonces no seguimos porque es division entre 0, usar distance_epsilon de tools
    if (distance_is_zero(denom)) return 0.0f;
    else return m_d.dot(P - m_O)/denom;
    */
    float res = 0.0f;
    float dd = m_d.dot(m_d);
    assert(dd > Constants::distance_epsilon * Constants::distance_epsilon);
    res = m_d.dot(P - m_O) / dd;
    return res;

}

// Calcular la distancia minima 'dist' de la linea a P
//
// dist = mod(P - (O + uD))
// Where u = ParamDistance(P)
float Line::distance(const Vector3 & P) const {
	/*
    float res = 0.0f;
    Vector3 aux = m_O + (paramDistance(P)*m_d);
    aux = P - aux;
    res = aux.length();//Length calcula el modulo del vector
	return res;
    */
    float res = 0.0f;
    float u0 = paramDistance(P);
    Vector3 W = P - (m_O + u0 * m_d);
    res = W.length();
    return res;
}

void Line::print() const {
	printf("O:");
	m_O.print();
	printf(" d:");
	m_d.print();
	printf("\n");
}
