#include <cstdio>
#include <cassert>
#include "node.h"
#include "nodeManager.h"
#include "intersect.h"
#include "bboxGL.h"
#include "renderState.h"

using std::string;
using std::list;
using std::map;

// Recipe 1: iterate through children:
//
//    for(list<Node *>::iterator it = m_children.begin(), end = m_children.end();
//        it != end; ++it) {
//        Node *theChild = *it;
//        theChild->print(); // or any other thing
//    }

// Recipe 2: iterate through children inside a const method
//
//    for(list<Node *>::const_iterator it = m_children.begin(), end = m_children.end();
//        it != end; ++it) {
//        Node *theChild = *it;
//        theChild->print(); // or any other thing
//    }

Node::Node(const string &name) :
	m_name(name),
	m_parent(0),
	m_gObject(0),
	m_light(0),
	m_shader(0),
	m_placement(new Trfm3D),
	m_placementWC(new Trfm3D),
	m_containerWC(new BBox1),
    m_checkCollision(true),
	m_isCulled(false),
	m_drawBBox(false) {}

Node::~Node() {
	delete m_placement;
	delete m_placementWC;
	delete m_containerWC;
}

static string name_clone(const string & base) {

	static char MG_SC_BUFF[2048];
	Node *aux;

	int i;
	for(i = 1; i < 1000; i++) {
		sprintf(MG_SC_BUFF, "%s#%d", base.c_str(), i);
		string newname(MG_SC_BUFF);
		aux = NodeManager::instance()->find(newname);
		if(!aux) return newname;
	}
	fprintf(stderr, "[E] Node: too many clones of %s\n.", base.c_str());
	exit(1);
	return string();
}

Node* Node::cloneParent(Node *theParent) {

	string newName = name_clone(m_name);
	Node *newNode = NodeManager::instance()->create(newName);
	newNode->m_gObject = m_gObject;
	newNode->m_light = m_light;
	newNode->m_shader = m_shader;
	newNode->m_placement->clone(m_placement);
	newNode->m_parent = theParent;
	for(list<Node *>::iterator it = m_children.begin(), end = m_children.end();
		it != end; ++it) {
		Node *theChild = *it;
		newNode->m_children.push_back(theChild->cloneParent(this));
	}
	return newNode;
}


Node *Node::clone() {
	return cloneParent(0);
}

///////////////////////////////////
// transformations

void Node::attachGobject(GObject *gobj ) {
	if (!gobj) {
		fprintf(stderr, "[E] attachGobject: no gObject for node %s\n", m_name.c_str());
		exit(1);
	}
	if (m_children.size()) {
		fprintf(stderr, "EW] Node::attachGobject: can not attach a gObject to node (%s), which already has children.\n", m_name.c_str());
		exit(1);
	}
	m_gObject = gobj;
	propagateBBRoot();
}

GObject *Node::detachGobject() {
	GObject *res = m_gObject;
	m_gObject = 0;
	return res;
}

GObject *Node::getGobject() {
	return m_gObject;
}

void Node::attachLight(Light *theLight) {
	if (!theLight) {
		fprintf(stderr, "[E] attachLight: no light for node %s\n", m_name.c_str());
		exit(1);
	}
	m_light = theLight;
}

Light * Node::detachLight() {
	Light *res = m_light;
	m_light = 0;
	return res;
}

void Node::attachShader(ShaderProgram *theShader) {
	if (!theShader) {
		fprintf(stderr, "[E] attachShader: empty shader for node %s\n", m_name.c_str());
		exit(1);
	}
	m_shader = theShader;
}

ShaderProgram *Node::detachShader() {
	ShaderProgram *theShader = m_shader;
	m_shader = 0;
	return theShader;
}

ShaderProgram *Node::getShader() {
	return m_shader;
}
///////////////////////////////////
// transformations

void Node::initTrfm() {
	Trfm3D I;
	m_placement->swap(I);
	// Update Geometric state
	updateGS();
}

void Node::setTrfm(const Trfm3D * M) {
	if (!M) {
		fprintf(stderr, "[E] setTrfm: no trfm for node %s\n", m_name.c_str());
		exit(1);
	}
	m_placement->clone(M);
	// Update Geometric state
	updateGS();
}

void Node::addTrfm(const Trfm3D * M) {
	if (!M) {
		fprintf(stderr, "[E] addTrfm: no trfm for node %s\n", m_name.c_str());
		exit(1);
	}
	m_placement->add(M);
	// Update Geometric state
	updateGS();
}

void Node::translate(const Vector3 & P) {
	static Trfm3D localT;
	localT.setTrans(P);
	addTrfm(&localT);
};

void Node::rotateX(float angle ) {
	static Trfm3D localT;
	localT.setRotX(angle);
	addTrfm(&localT);
};

void Node::rotateY(float angle ) {
	static Trfm3D localT;
	localT.setRotY(angle);
	addTrfm(&localT);
};

void Node::rotateZ(float angle ) {
	static Trfm3D localT;
	localT.setRotZ(angle);
	addTrfm(&localT);
};

void Node::scale(float factor ) {
	static Trfm3D localT;
	localT.setScale(factor);
	addTrfm(&localT);
};

///////////////////////////////////
// tree operations

Node *Node::parent() {
	if (!m_parent) return this;
	return m_parent;
}

/**
 * nextSibling: Get next sibling of node. Return first sibling if last child.
 *
 */

Node *Node::nextSibling() {
	Node *p = m_parent;
	if(!p) return this;
	list<Node *>::iterator end = p->m_children.end();
	list<Node *>::iterator it = p->m_children.begin();
	while(it != end && *it != this) ++it;
	assert(it != end);
	++it;
	if (it == end) return *(p->m_children.begin());
	return *it;
}

/**
 * firstChild: Get first child of node. Return itself if leaf node.
 *
 * @param theNode A pointer to the node
 */

Node *Node::firstChild() {
	if (!m_children.size()) return this;
	return *(m_children.begin());
}

// Cycle through children of a Node. Return children[ i % lenght(children) ]

Node * Node::cycleChild(size_t idx) {

	size_t m = idx % m_children.size();
	size_t i = 0;
	for(list<Node *>::iterator it = m_children.begin(), end = m_children.end();
		it != end; ++it) {
		if (i == m) return *it;
		i++;
	}
	return 0;
}

// Add a child to node
// Print a warning (and do nothing) if node already has an gObject.
void Node::addChild(Node *theChild) {
	if (theChild == 0) return;
	if (m_gObject) {
        fprintf(stderr, "[E] addChild: node %s already has a gObject\n", m_name.c_str());
        exit(1);
		// node has a gObject, so print warning
	} else {
        // node does not have gObject, so attach child
        m_children.push_back(theChild);
        theChild->m_parent = this;
        theChild->updateGS();
	}
}



void Node::detach() {

	Node *theParent;
	theParent = m_parent;
	if (theParent == 0) return; // already detached (or root node)
	m_parent = 0;
	theParent->m_children.remove(this);
	// Update bounding box of parent
	theParent->propagateBBRoot();
}

// Agrandamos cada caja contenedora de lo de dentro.
// Al final cada caja padre debe poder contener a todos sus elems hijos.

void Node::propagateBBRoot() {
    /*
    if (m_parent){
        updateBB();
        this->m_parent->propagateBBRoot();
    }
    */
    for (Node *oneNode = this; oneNode; oneNode = oneNode->m_parent)
        oneNode->updateBB();
}

// Dado un nodo, actualizamos su caja para que incluya a su objeto y a los objetos de sus hijos
// Se le llama desde propagateBBRoot
void Node::updateBB () {
    /*
    if (m_children.empty()){
        m_containerWC->transform(this->m_placementWC);
    }else{
        m_containerWC->init();
        for(list<Node *>::iterator it = m_children.begin(), end = m_children.end(); it != end; ++it) {
            Node *theChild = *it;
            m_containerWC->include(theChild->m_containerWC);
        }
    }
    */
    if (m_gObject) {
        m_containerWC->clone(m_gObject->getContainer());
        m_containerWC->transform(m_placementWC);
    } else {
        m_containerWC->init(); // set void
        // Increase container_WC with child's BBoxes
        for(list<Node *>::iterator it = m_children.begin(), end = m_children.end(); it != end; ++it) {
            Node *theChild = *it;
            m_containerWC->include(theChild->m_containerWC);
        }
    }

}

// Update WC (world coordinates matrix) of a node and
// its bounding box recursively updating all children.
//
// given a node:
//  - update the world transformation (m_placementWC) using the parent's WC transformation
//  - recursive call to update WC of the children
//  - update Bounding Box to world coordinates
//
// Precondition:
//
//  - m_placementWC of m_parent is up-to-date (or m_parent == 0)
void Node::updateWC() {
    /*
    if (!m_parent){
        this->m_placementWC->clone(this->m_placement);
    }else{
        this->m_placementWC->clone(this->parent()->m_placementWC);
        this->m_placementWC->add(this->m_placement);
    }
    for(list<Node *>::iterator it = m_children.begin(), end = m_children.end(); it != end; ++it) {
        Node *theChild = *it;
        theChild->updateWC();
    }
    updateBB();
    */
    if (m_parent == 0) {
        m_placementWC->clone(m_placement); // placement already in world coordinates.
    } else {
        // Compose placement with parent's placementWC
        m_placementWC->clone(m_parent->m_placementWC);
        m_placementWC->add(m_placement);
    }
    // update children transformations
    for(list<Node *>::iterator it = m_children.begin(), end = m_children.end();
        it != end; ++it) {
        Node *theChild = *it;
        theChild->updateWC();
    }
    // Now update Bounding Box to world coordinates
    updateBB();
}

//  Update geometric state of a node.
//
// given a node:
// - Update WC transformation of sub-tree starting at node (updateWC)
// - Propagate Bounding Box to root (propagateBBRoot)
void Node::updateGS() {
    /*
    updateWC();
    propagateBBRoot();
    */
    updateWC();
    if (m_parent)
        m_parent->propagateBBRoot();

}

void Node::setDrawBBox(bool b) { m_drawBBox = b; }
bool Node::getDrawBBox() const { return m_drawBBox; }

void Node::setCheckCollision(bool b) { m_checkCollision = b; }
bool Node::getCheckCollision() const { return m_checkCollision; }

// Dibujamos el grafo de escena, como estamos en global solo nos preocupan sus hijos
// En local mirariamos la transformacion de todos los nodos
// Las instrucciones de la diapo son:
//  1. Guardar en la pila la matriz de transformaciones
//  2. Realizar la transformacion
//  3. Dibujar el objeto geometrico
//  4. Dibujar los hijos
//  5. Desempilar la matriz de transformaciones
void Node::draw() {

    /*
    RenderState *rs = RenderState::instance();
    // Print BBoxes
    if(rs->getBBoxDraw() || m_drawBBox) BBoxGL::draw( m_containerWC );
    // En global solo hacemos las transformaciones en los nodos hoja
    if (m_children.empty()){
        rs->push(rs->modelview); //Guardamos la modelview en la pila
        rs->addTrfm(rs->modelview, m_placementWC);//Multiplicacion de la transformacion por el modelview de la pila
    }
    if (this->m_gObject) m_gObject->draw();
    if (m_children.empty()) rs->pop(rs->modelview);
    for(list<Node *>::iterator it = m_children.begin(), end = m_children.end(); it != end; ++it) {
        Node *theChild = *it;
        theChild->draw();
    }*/

    ShaderProgram *prev_shader = 0;
    RenderState *rs = RenderState::instance();

    if (m_isCulled) return;

    // Set shader (save previous)
    if (m_shader != 0) {
        prev_shader = rs->getShader();
        rs->setShader(m_shader);
    }

    // Print BBoxes
    if(rs->getBBoxDraw() || m_drawBBox)
        BBoxGL::draw( m_containerWC );

    // Draw geometry object
    if (m_gObject) {
        // the world transformation is already precalculated, so just put the
        // transformation in the openGL matrix
        //
        rs->push(RenderState::modelview);
        rs->addTrfm(RenderState::modelview, m_placementWC);
        // Set model matrix
        rs->loadTrfm(RenderState::model, m_placementWC);
        m_gObject->draw();
        rs->pop(RenderState::modelview);
    }

    // draw sub-nodes (recursive)
    for(list<Node *>::iterator it = m_children.begin(), end = m_children.end();
        it != end; ++it) {
        Node *theChild = *it;
        theChild->draw(); // Recursive call
    }
    if (prev_shader != 0) {
        // restore shader
        rs->setShader(prev_shader);
    }
}

// Set culled state of a node's children

void Node::setCulled(bool culled) {
	m_isCulled = culled;
	for(list<Node *>::iterator it = m_children.begin(), end = m_children.end();
		it != end; ++it) {
		Node *theChild = *it;
		theChild->setCulled(culled); // Recursive call
	}
}

// Dada una camara verificamos si los nodos del arbol se encuenta dentro o fuera del area visible.
// Si no esta dentro de ella, m_isCulled = 1, sino m_isCulled = 0
void Node::frustumCull(Camera *cam) {
	int cull = cam->checkFrustum(m_containerWC, 0);

	if(cull == 1) m_isCulled = 1;
	else if(cull == -1) m_isCulled = 0;
	else{
		if(m_gObject) m_isCulled = 0;
		for(list<Node *>::iterator it = m_children.begin(), end = m_children.end(); it != end; ++it) {
    	    Node *theChild = *it;
			theChild->frustumCull(cam);
    	}
	}
}

// @@ TODO: Check whether a BSphere (in world coordinates) intersects with a
// (sub)tree.
//
// Return a pointer to the Node which collides with the BSphere. 0
// if not collision.
//
// Note:
//    See Recipe 2 in for knowing how to iterate through children inside a const
//    method.

const Node *Node::checkCollision(const BSphere *bsph) const {
    if (!m_checkCollision) return 0;

    if(BSphereBBoxIntersect(bsph, this->m_containerWC) == IREJECT) return 0;
    //Si ha intersectado y es un objeto (nodo hoja) entonces devolvemos el nodo
    if(m_gObject) return this;

    for(list<Node *>::const_iterator it = m_children.begin(), end = m_children.end(); it != end; ++it) {
        Node *theChild = *it;
        if(theChild->checkCollision(bsph)) return theChild;
    }

	return 0; /* No collision */
}
