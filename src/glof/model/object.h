/*
 * object.h
 *
 *  Created on: 31.03.2014
 *      Author: sieb
 */

#ifndef OBJECT_H_
#define OBJECT_H_


class GlofObject {

public:

	GlofObject();
	virtual ~GlofObject();

	virtual void render() = 0;

};



#endif /* OBJECT_H_ */
