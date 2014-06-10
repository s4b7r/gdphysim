/*
 * cube.h
 *
 *  Created on: 20.05.2014
 *      Author: sieb
 */

#ifndef CUBE_H_
#define CUBE_H_

class GlofCube : public GlofObject {

public:

	GlofCube();
	virtual ~GlofCube();

	virtual void render();

	GLdouble getPositionX();
	GLdouble getPositionY();
	GLdouble getPositionZ();
	void setPosition(GLdouble x, GLdouble y, GLdouble z);

	GLdouble getRotationX();
	GLdouble getRotationY();
	GLdouble getRotationZ();
	void setRotation(GLdouble rotX, GLdouble rotY, GLdouble rotZ);

private:

	GLdouble x;
	GLdouble y;
	GLdouble z;

	GLdouble rotX;
	GLdouble rotY;
	GLdouble rotZ;

	GLdouble scale;

};


#endif /* CUBE_H_ */
