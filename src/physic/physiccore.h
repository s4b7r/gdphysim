/*
 * physiccore.h
 *
 *  Created on: Mar 1, 2014
 *      Author: kevin
 */

#ifndef PHYSICCORE_H_
#define PHYSICCORE_H_
#define PHYSICCORE Physiccore::Get()

#include <vector>
#include "gui/TSingleton.cpp"
#include "physic/solids/solid.h"

using std::vector;

class Physiccore : public TSingleton<Physiccore>{
private:
	vector<Solid> elements;
	vector<int*> anchorPositions;

	void setAnchorsPosition();

public:
	void addElement(Solid element);
	vector<Solid> getElements(){return elements;}
	vector<int*> getAnchorsPosition();
};

#endif /* PHYSICCORE_H_ */
