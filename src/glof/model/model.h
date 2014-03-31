/*
 * model.h
 *
 *  Created on: 31.03.2014
 *      Author: sieb
 */

#ifndef MODEL_H_
#define MODEL_H_


namespace glof {

class Model {

public:

	Model();
	virtual ~Model();

	void render();

private:

	std::vector<Object> objects;

};

}


#endif /* MODEL_H_ */
