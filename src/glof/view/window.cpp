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
	strcpy(name, "Title");
	parent = 0;
	camera = 0;

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
	// Bind GLUT callbacks
	glutDisplayFunc(render);
	// OpenGL settings
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	return 0;

}

int GlofWindow::getId() {

	return glutId;

}

void GlofWindow::render() {

	// If I have no subwindows, I render myself
	if( windows.empty() ) {
		// Clear GL color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Clear GL model and projection matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		// Call camera's render function
		camera->render();
	} else { // If I have subwindows, I render them
		std::vector<GlofWindow*>::iterator subwindowIterator;
		subwindowIterator = windows.begin();
		while( subwindowIterator != windows.end() ) {
			(*subwindowIterator)->render();
			subwindowIterator++;
		}
	}
	// Swap buffers
	glutSwapBuffers();

}
