// -*-C++-*-

#pragma once

/**
 * @brief A geometry object is a list of meshes and a Bounding volume
 *
 * Geometry objects don't understand about local transformations etc. They only
 * store topological info.
 *
 * Note: geometry objects own the triangleMeshes they contain.
 *
 */

#include <list>
#include <string>
#include "bbox.h"
#include "trfm3D.h"
#include "triangleMesh.h"

class GObject {

public:

	const std::string & getName() const;

	// Draw the geometry object using current modelview matrix

	void draw();

	// Draw opaque meshes of the geometry object using current modelview matrix

	void drawOpaque();

	// Draw transparent meshes of the geometry object using current modelview matrix

	void drawTransparent();

	const BBox1 *getContainer(); //!< Get bounding box of GObject

	// needs to know which materials are available

	void add(TriangleMesh *oneMesh );

	// apply a trfm to all meshes
	void applyTrfm(const Trfm3D * trfm);

	// Set gObject to be faceted.
	void setFaceted();

	// Set gObject to be smooth.
	void setSmooth();

	void setTexture(Texture *tex); //!< Set texture to all meshes inside this gObject

	int  numTriangles() const; //!< Number of triangles in the GObject

	void print() const;

	friend class GObjectManager;

private:

	void updateContainer(); //!< recalculate bounding box

	/**
	 * Create a geometry object given a wavefront file
	 *
	 * @param DirName The directory where the obj is
	 * @param FileName The file name
	 *
	 * @return the new created geometry object
	 */
	static GObject *createFromWavefront(const std::string &DirName, const std::string & FileName );

	GObject(const std::string & name);
	~GObject();

	GObject(const GObject & o);
	GObject & operator=(const GObject & o);

	std::string m_name;
	std::list<TriangleMesh *> m_meshes;
	std::list<TriangleMesh *> m_meshes_transp;
	BBox1 m_container;
};
