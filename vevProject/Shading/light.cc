#include <algorithm>
#include <cstdio>
#include "tools.h"
#include "light.h"
#include "trfm3D.h"
#include "renderState.h"

// forward declarations

Light::Light(type_t t) :
	m_type(t),
	m_switched(true),
	m_ambient(Vector3(0.2f, 0.2f, 0.2f)),
	m_diffuse(Vector3(0.8f, 0.8f, 0.8f)),
	m_specular(Vector3::ZERO),
	m_position(Vector3(0.0f, 5.0f, 0.0f)), // default is position
	m_spotDirection(Vector3(0.577, 0.577, 0.577)),
	m_positionEye(Vector3(0.0f, 5.0f, 0.0f)), // default is position
	m_spotDirectionEye(Vector3(0.577, 0.577, 0.577)),
	m_spotExponent(10.0f),
	m_spotCutOff(30.0f), // must be degrees
	m_att(Vector3(0.7f, 0.0f, 0.0f))
{}

Light::~Light() {}

void Light::swap(Light & rhs) {
	std::swap(m_type, rhs.m_type);
	std::swap(m_switched, rhs.m_switched);
	m_ambient.swap(rhs.m_ambient);
	m_diffuse.swap(rhs.m_diffuse);
	m_specular.swap(rhs.m_specular);
	m_position.swap(rhs.m_position);
	m_positionEye.swap(rhs.m_positionEye);
	m_spotDirection.swap(rhs.m_spotDirection);
	m_spotDirectionEye.swap(rhs.m_spotDirectionEye);
	std::swap(m_spotExponent, rhs.m_spotExponent);
	std::swap(m_spotCutOff, rhs.m_spotCutOff);
	m_att.swap(rhs.m_att);
}

Light::type_t Light::getType() const { return m_type; }

void Light::switchLight(bool status ) {	m_switched =status; }
bool Light::isOn() const { return m_switched; }

void Light::setPosition(const Vector3 & pos) {
	m_position = pos;
	m_positionEye = pos;
	if (m_type == directional) {
		// Normalize vector
		m_position.normalize();
		m_positionEye.normalize();
	}
}

Vector3 Light::getPositionEye() const { return m_positionEye; }
Vector3 Light::getPositionWorld() const { return m_position; }

/**
 * Get light position in Eye coordinates. Returns a pointer to a 4-float
 * vector, which represents a point in homogeneous coordinates. Last
 * coordinate (w) is 0.0 for directional lights, 1.0 for positional and
 * spotlights.
 */

const float *Light::getPositionEye_4fv() const {
	static float p[4]; // homogeneous
	p[0] = m_positionEye[0];
	p[1] = m_positionEye[1];
	p[2] = m_positionEye[2];
	p[3] = m_type == directional ? 0.0f : 1.0f;
	return &p[0];
}

/**
 * @@ TODO: Place the light into the scene. Store the result into positionEye and spotDirectionEye.
 *
 * hints:
 *        - multiply position with current modelView matrix
 */

void Light::placeScene() {
	RenderState *rs = RenderState::instance();
	Trfm3D *modelview;

	if( ! m_switched ) return;

	modelview = rs->top(RenderState::modelview);

	m_positionEye = m_position;

	//No tenemos en cuenta el tipo de luz invalid
	if(m_type == directional){
        m_positionEye = modelview->transformVector(m_position);
	}else{
		//Si no es posicional sera spotlight o direccional, que las 2 tienen una direccion representada por un vector
        if (m_type == spotlight) m_spotDirectionEye = modelview->transformVector(m_spotDirection);
        m_positionEye = modelview->transformPoint(m_position);
	}

}
/*
void Light::placeScene() {
    RenderState *rs = RenderState::instance();
    Trfm3D *modelview;
    if( ! m_switched ) return;
    modelview = rs->top(RenderState::modelview);
    m_positionEye = m_position;
    if(m_type == directional) modelview->transformVector(m_positionEye).normalize();
    else{
        if (m_type == spotlight) modelview->transformVector(m_spotDirectionEye); //m_spotDirectionEye = modelview->transformPoint(m_spotDirection);
        modelview->transformPoint(m_positionEye);
    }
}
*/

void Light::setSpotData(const Vector3 & direction,
						float cutOff, float exponent) {

	if (m_type != spotlight) {
		printf("[E] light is not spotlight!\n");
		exit(1);
	}
	m_spotDirection = direction;
	m_spotDirectionEye = direction;
	m_spotDirectionEye.normalize();
	m_spotCutOff = Constants::degree_to_rad * cutOff;
	m_spotExponent = exponent;

}

const Vector3 &Light::getSpotDirectionEye() const {
	static Vector3 nullDir(0.0f, 0.0f, 0.0f);
	if (m_type != spotlight) return nullDir;
	return m_spotDirectionEye;
}

const Vector3 &Light::getSpotDirectionWorld() const {
	static Vector3 nullDir(0.0f, 0.0f, 0.0f);
	if (m_type != spotlight) return nullDir;
	return m_spotDirection;
}

float Light::getSpotExponent() const {
	if (m_type != spotlight) return 0.0f;
	return m_spotExponent;
}

float Light::getSpotCutoff() const {
	if (m_type != spotlight) return 0.0f;
	return m_spotCutOff;
}

bool Light::isSpot() const {
	return m_type == spotlight;
}

void Light::setAmbient(const Vector3 &rgb) { m_ambient = rgb; }
void Light::setDiffuse(const Vector3 &rgb) { m_diffuse = rgb; }
void Light::setSpecular(const Vector3 &rgb) { m_specular = rgb; }
const Vector3 &Light::getAmbient() const { return m_ambient; }
const Vector3 &Light::getDiffuse() const { return m_diffuse; }
const Vector3 &Light::getSpecular() const { return m_specular; }

const Vector3 &Light::getAttenuationVector() const { return m_att; }
float Light::getConstantAttenuation() const { return m_att[0]; }
float Light::getLinearAttenuation() const { return m_att[1]; }
float Light::getQuadraticAttenuation() const { return m_att[2]; }

void Light::setConstantAttenuation(float c) {
	m_att[0] = c;
	m_att.normalizeL1(); // sum to one
}

void Light::setLinearAttenuation(float b) {
	m_att[1] = b;
	m_att.normalizeL1(); // sum to one
}

void Light::setQuadraticAttenuation(float a) {
	m_att[2] = a;
	m_att.normalizeL1(); // sum to one
}

void Light::print() {

	if( m_type == directional ) {
		printf("*** Directional Light");
	} else if( m_type == positional ) {
		printf("*** Positional Light");
	} else {
		printf("*** Spot Light");
	}

	if( m_switched )
		printf(" Switched ON\n" );
	else
		printf(" Switched OFF\n");

	printf(" Ambient %04.2f %04.2f %04.2f\n",
		   m_ambient[0], m_ambient[1],
		   m_ambient[2]);
	printf(" Diffuse %04.2f %04.2f %04.2f\n",
		   m_diffuse[0], m_diffuse[1],
		   m_diffuse[2]);
	printf(" Specular %04.2f %04.2f %04.2f\n",
		   m_specular[0], m_specular[1],
		   m_specular[2]);

	if( m_type == directional ) {
		printf(" Direction ");
	} else {
		printf(" Position ");
	}
	printf("%.2f %.2f %4.2f ; %04.2f\n",
		   m_position[0], m_position[1],
		   m_position[2], m_position[3] );

	if( m_type == directional ) {
		printf(" Transformed direction ");
	} else {
		printf(" Transformed position ");
	}
	printf("%.2f %.2f %4.2f ; %04.2f\n",
		   m_positionEye[0], m_positionEye[1],
		   m_positionEye[2], m_positionEye[3] );

	if( m_type == spotlight ) {
		printf(" Spot direction %04.2f %04.2f %04.2f (mod: %4.2f)\n",
			   m_spotDirection[0], m_spotDirection[1],
			   m_spotDirection[2], m_spotDirection.length());
		printf(" Transformed spot direction %04.2f %04.2f %04.2f\n",
			   m_spotDirectionEye[0], m_spotDirectionEye[1],
			   m_spotDirectionEye[2]);
		printf(" Exponent %6.1f Cut Off %4.1f\n",
			   m_spotExponent, m_spotCutOff );
	}
	printf(" Attenuation : Quad=%f Linear=%f Constant=%f\n",
		   m_att[2], m_att[1], m_att[0] );
}
