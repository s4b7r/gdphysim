/*
 * glof.cpp
 *
 *  Created on: 31.03.2014
 *      Author: sieb
 */

#include "glof/glof.h"

Glof* Glof::myPointer = 0;

void Glof::deleteGlof() {

	delete myPointer;
	myPointer = 0;

}

int Glof::init(int* argcp, char** argv) {

	// GLFO should not be initialised twice
	if( isInit ) {
		return 1;
	}
	isInit = true;

	// Initialise GLUT
	glutInit(argcp, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	// Create Model
	model = new GlofModel();

	return 0;

}

Glof::~Glof() {

	// Delete GlofModel
	delete model;

	// Delete all GlofWindows
	while( !windows.empty() ) {
		delete windows.back();
		windows.pop_back();
	}

}

Glof* Glof::getGlof() {

	if( myPointer != 0 ) {
		// If GLOF already exists, return it
		return myPointer;
	} else {
		// If GLOF does not exist, create and return
		myPointer = new Glof();
		return myPointer;
	}

}

GlofModel* Glof::getModel() {

	return model;

}

Glof::Glof() {

	isInit = false;
	model = 0;

}

GlofWindow* Glof::newWindow() {

	// Create new Window
	GlofWindow *newWindow = new GlofWindow();
	// Push on windows vector
	windows.push_back(newWindow);
	// Return
	return newWindow;


}

void Glof::deleteWindow(GlofWindow* window) {

	// Remove from windows vector
	std::vector<GlofWindow*>::iterator itW;
	itW = windows.begin();
	while( itW != windows.end() ) {
		if( *itW == window ) {
			windows.erase(itW);
			itW = windows.end();
		} else {
			itW++;
		}
	}
	// Clear memory
	delete window;

}
