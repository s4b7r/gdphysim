/*
 * viewport.h
 *
 *  Created on: 31.03.2014
 *      Author: sieb
 */

#ifndef VIEWPORT_H_
#define VIEWPORT_H_


class GlofViewport {

public:

	GlofViewport();
	virtual ~GlofViewport();

private:

	GlofCamera *camera;

};


#endif /* VIEWPORT_H_ */
