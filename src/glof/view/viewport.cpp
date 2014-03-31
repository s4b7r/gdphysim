/*
 * viewport.cpp
 *
 *  Created on: 31.03.2014
 *      Author: sieb
 */

#include "glof/glof.h"

GlofViewport::GlofViewport() {

	camera = 0;

}

GlofViewport::~GlofViewport() {

	delete camera;

}
