/*
 * model.cpp
 *
 *  Created on: 31.03.2014
 *      Author: sieb
 */

#include "glof/glof.h"

GlofModel::GlofModel() {
}

GlofModel::~GlofModel() {

	while( !objects.empty() ) {
		delete objects.back();
		objects.pop_back();
	}

}

void GlofModel::render() {
}
