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

	// Initialise OpenGL
	glShadeModel(GL_SMOOTH);

	// Create Model
	model = new GlofModel();

	return 0;

}

int Glof::newWindow(char* name) {

	// Create new GLUT window
	struct GlofWindow newWindow;
	newWindow.id = glutCreateWindow(name);
	// Add new window to windows field
	windows.push_back(newWindow);
	// Return window id
	return newWindow.id;

}

int Glof::newSubwindow(int pId, int pX, int pY, int w, int h) {

	// Create new GLUT subwindow
	int id = glutCreateSubWindow(pId, pX, pY, w, h);
	// Add to parent's subwindows field
	std::vector<GlofWindow>::iterator itW;
	itW = windows.begin();
	while( itW != windows.end() ) {
		if( itW->id == pId ) {
			itW->subwindows.push_back(id);
			itW = windows.end();
		}
		itW++;
	}
	// Return subwindow id
	return id;

}

void Glof::deleteWindow(int id) {

	// Remove window from windows field
	std::vector<GlofWindow>::iterator itW;
	itW = windows.begin();
	while( itW != windows.end() ) {
		if( itW->id == id ) {
			windows.erase(itW);
			itW = windows.end();
		}
		itW++;
	}
	// Destroy GLUT window
	glutDestroyWindow(id);

}

Glof::~Glof() {

	delete model;

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



