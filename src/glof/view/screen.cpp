/*
 * screen.cpp
 *
 *  Created on: 31.03.2014
 *      Author: sieb
 */

#include "glof/glof.h"

GlofScreen::GlofScreen() {
}

GlofScreen::~GlofScreen() {

	while( !viewports.empty() ) {
		delete viewports.back();
		viewports.pop_back();
	}

}

GlofViewport* GlofScreen::newViewport() {

	viewports.push_back(new GlofViewport);
	return viewports.back();

}
