/*
 * camera.h
 *
 *  Created on: 31.03.2014
 *      Author: sieb
 */

#ifndef CAMERA_H_
#define CAMERA_H_

class GlofCamera {

public:

	GlofCamera();
	virtual ~GlofCamera();

	void render();

	GLdouble getAspect();
	void setAspect(GLdouble aspect);

	GLdouble getFovy();
	void setFovy(GLdouble fovy);

	GLdouble getPositionX();
	GLdouble getPositionY();
	GLdouble getPositionZ();
	void setPosition(GLdouble x, GLdouble y, GLdouble z);

private:

	GLdouble fovy;
	GLdouble aspect;
	GLdouble zNear;
	GLdouble zFar;

	GLdouble x;
	GLdouble y;
	GLdouble z;

};



#endif /* CAMERA_H_ */
