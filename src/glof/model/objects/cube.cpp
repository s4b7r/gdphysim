/*
 * cube.cpp
 *
 *  Created on: 20.05.2014
 *      Author: sieb
 */

GlofCube::GlofCube() {

	x = 0;
	y = 0;
	z = 0;
	rotX = 0;
	rotY = 0;
	rotZ = 0;
	scale = 1;

}

GlofCube::~GlofCube() {
}

void GlofCube::render() {

	// Todo Implement GlofCube::Render()

}

GLdouble GlofCube::getPositionX() {
	return x;
}

GLdouble GlofCube::getPositionY() {
	return y;
}

GLdouble GlofCube::getPositionZ() {
	return z;
}

void GlofCube::setPosition(GLdouble x, GLdouble y, GLdouble z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

GLdouble GlofCube::getRotationX() {
	return rotX;
}

GLdouble GlofCube::getRotationY() {
	return rotY;
}

GLdouble GlofCube::getRotationZ() {
	return rotZ;
}

void GlofCube::setRotation(GLdouble rotX, GLdouble rotY, GLdouble rotZ) {
	this->rotX = rotX;
	this->rotY = rotY;
	this->rotZ = rotZ;
}
