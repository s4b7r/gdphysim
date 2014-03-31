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

private:

	GLdouble x;
	GLdouble y;
	GLdouble z;

};



#endif /* CAMERA_H_ */
