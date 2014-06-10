/*
 * rectangle.cpp
 *
 *  Created on: 20.05.2014
 *      Author: sieb
 */

GlofRectangle::GlofRectangle() {

	position[0] = 0;
	position[1] = 0;
	position[2] = 0;
	rotation[0] = 0;
	rotation[1] = 0;
	rotation[2] = 0;


}

GlofRectangle::~GlofRectangle() {
}

void GlofRectangle::render() {

	glPushMatrix();

	glScaled(scaleX, scaleY, 1);

	glBegin(GL_QUADS);



	glEnd();

	glPopMatrix();

}

