/*
 * model.cpp
 *
 *  Created on: 31.03.2014
 *      Author: sieb
 */

#include "glof/glof.h"

GlofModel::GlofModel() {

	// Need to implement?

}

GlofModel::~GlofModel() {

	while( !objects.empty() ) {
		delete objects.back();
		objects.pop_back();
	}

}

void GlofModel::render() {

	// Render all objects
	std::vector<GlofObject*>::iterator objectIterator;
	objectIterator = objects.begin();
	while( objectIterator != objects.end() ) {
		(*objectIterator)->render();
		objectIterator++;
	}

}
