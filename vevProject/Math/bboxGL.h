// -*-C++-*-

#pragma once

#include "bbox.h"

class BBoxGL {
public:
	/**
	 * Draw a BBox into openGL
	 *
	 * @param thisBBox pointer to BBox
	 */
	static void draw( BBox1 * thisBBox);
private:
	static void init_opengl_vbo(BBox1 *thisBBox);
};
