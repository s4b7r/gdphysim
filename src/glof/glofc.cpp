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



