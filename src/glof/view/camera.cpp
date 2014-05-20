/*
 * camera.cpp
 *
 *  Created on: 31.03.2014
 *      Author: sieb
 */

#include "glof/glof.h"

GlofCamera::GlofCamera() {

	fovy = 0;
	aspect = 0;
	zNear = 0;
	zFar = 0;

	x = 0;
	y = 0;
	z = 0;

}

GlofCamera::~GlofCamera() {

	// Need to implement?

}

void GlofCamera::render() {

	// Set perspective in projection matrix
	glMatrixMode(GL_PROJECTION);
	gluPerspective(fovy, aspect, zNear, zFar);
	// Transform model matrix for camera's position and orientation
	glMatrixMode(GL_MODELVIEW);
	glTranslated(x, y, z);
	// Call model's render function
	Glof::getGlof()->getModel()->render();

}

GLdouble GlofCamera::getAspect() const {
	return aspect;
}

void GlofCamera::setAspect(GLdouble aspect) {
	this->aspect = aspect;
}

GLdouble GlofCamera::getFovy() const {
	return fovy;
}

void GlofCamera::setFovy(GLdouble fovy) {
	this->fovy = fovy;
}
