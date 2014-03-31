/*
 * camera.cpp
 *
 *  Created on: 31.03.2014
 *      Author: sieb
 */

#include "glof/glof.h"

GlofCamera::GlofCamera() {

	// Need to implement?

}

GlofCamera::~GlofCamera() {

	// Need to implement?

}

void GlofCamera::bindWindow(int windowId) {

	windowBinds.push_back(windowId);

}

void GlofCamera::removeBind(int windowId) {

	// Remove window id from binds field
	std::vector<int>::iterator itWId;
	itWId = windowBinds.begin();
	while( itWId != windowBinds.end() ) {
		if( *itWId == windowId ) {
			windowBinds.erase(itWId);
			itWId = windowBinds.end();
		} else {
			itWId++;
		}
	}

}

void GlofCamera::render() {

	// Implement!

}
