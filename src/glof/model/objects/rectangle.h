/*
 * rectangle.h
 *
 *  Created on: 20.05.2014
 *      Author: sieb
 */

#ifndef RECTANGLE_H_
#define RECTANGLE_H_


class GlofRectangle : public GlofObject {

public:

	GlofRectangle();
	virtual ~GlofRectangle();

	virtual void render();

private:

	GLdouble position[3];
	GLdouble rotation[3];
	GLdouble scale[3];


};


#endif /* RECTANGLE_H_ */
