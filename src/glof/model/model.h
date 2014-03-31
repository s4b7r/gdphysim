/*
 * model.h
 *
 *  Created on: 31.03.2014
 *      Author: sieb
 */

#ifndef MODEL_H_
#define MODEL_H_


class GlofModel {

public:

	GlofModel();
	virtual ~GlofModel();

	void render();

private:

	std::vector<GlofObject*> objects;

};



#endif /* MODEL_H_ */
