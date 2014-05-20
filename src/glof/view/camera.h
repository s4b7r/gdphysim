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

	GLdouble getAspect() const;
	void setAspect(GLdouble aspect);

	GLdouble getFovy() const;
	void setFovy(GLdouble fovy);

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
