/*
 * window.cpp
 *
 *  Created on: 31.03.2014
 *      Author: sieb
 */

#include "glof/glof.h"

GlofWindow::GlofWindow() {

	glutId = 0;
	isInit = false;
	x = 0;
	y = 0;
	w = 0;
	h = 0;
	name = (char*)malloc(sizeof(char) * 6);
	strcat(name, "Title");
	parent = 0;

}


GlofWindow::~GlofWindow() {

	// Delete name array
	delete name;

	// Delete all GlofWindows
	while( !windows.empty() ) {
		delete windows.back();
		windows.pop_back();
	}

}

void GlofWindow::setName(char* name) {

	if( !isInit ) {
		// Delete old char array
		delete name;
		// Allocate new one
		this->name = (char*)malloc(sizeof(char) * sizeof(name));
		// Copy string
		strcpy(this->name, name);
	}

}

void GlofWindow::setPosition(int x, int y) {

	if( !isInit ) {
		this->x = x;
		this->y = y;
	}

}

void GlofWindow::setSize(int w, int h) {

	if( !isInit ) {
		this->w = w;
		this->h = h;
	}

}

GlofWindow* GlofWindow::newSubwindow() {

	if( !isInit || parent ) {
		return 0;
	}

	// Create new Window
	GlofWindow *newWindow = new GlofWindow();
	// Set subwindow's parent
	newWindow->setParent(this);
	// Push on windows vector
	windows.push_back(newWindow);
	// Return
	return newWindow;

}

void GlofWindow::setParent(GlofWindow* parent) {

	this->parent = parent;

}

int GlofWindow::init() {

	// Should not be initialized twice
	if( isInit ) {
		return 1;
	}
	isInit = true;

	// Set initial values
	glutInitWindowPosition(x, y);
	glutInitWindowSize(w, h);
	// Create window
	if( !parent ) {
		glutId = glutCreateWindow(name);
	} else {
		glutId = glutCreateSubWindow(parent->getId(), x, y, w, h);
	}
	// Bind glut callbacks
	glutDisplayFunc(render);

	return 0;

}

int GlofWindow::getId() {

	return glutId;

}

void GlofWindow::render() {

	// Implement!

}
