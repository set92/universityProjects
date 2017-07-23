#include "tools.h"
#include "avatar.h"
#include "scene.h"

Avatar::Avatar(const std::string &name, Camera * cam, float radius) :
	m_name(name), m_cam(cam), m_walk(false) {
	Vector3 P = cam->getPosition();
	m_bsph = new BSphere(P, radius);
}

Avatar::~Avatar() {
	delete m_bsph;
}

bool Avatar::walkOrFly(bool walkOrFly) {
	bool walk = m_walk;
	m_walk = walkOrFly;
	return walk;
}

// TODO:
//
// AdvanceAvatar: see if avatar can advance 'step' units.

bool Avatar::advance(float step) {

    Vector3 aux;
    if (m_walk){
		aux = {m_bsph->getPosition().x() + step*m_cam->getDirection().x(),
					   m_bsph->getPosition().y(),
					   m_bsph->getPosition().z() + step*m_cam->getDirection().z()};
		m_bsph->setPosition(aux);
	}else{
		aux = {m_bsph->getPosition().x() + step*m_cam->getDirection().x(),
					   m_bsph->getPosition().y() + step*m_cam->getDirection().y(),
					   m_bsph->getPosition().z() + step*m_cam->getDirection().z()};
		m_bsph->setPosition(aux);
	}

	Node *rootNode = Scene::instance()->rootNode(); // root node of scene

    //Si hay colision movemos la esfera a la posicion de la camara
	if (rootNode->checkCollision(m_bsph) != NULL){
		aux = {m_cam->getPosition().x(),m_cam->getPosition().y(),m_cam->getPosition().z()};
		m_bsph->setPosition(aux);
		return 0;
	}else{
        //Si no hay colision nos movemos normal
		if (m_walk)
			m_cam->walk(step);
		else
			m_cam->fly(step);
		return true;
	}

}

void Avatar::leftRight(float angle) {
	if (m_walk)
		m_cam->viewYWorld(angle);
	else
		m_cam->yaw(angle);
}

void Avatar::upDown(float angle) {
	m_cam->pitch(angle);
}

void Avatar::print() const { }
