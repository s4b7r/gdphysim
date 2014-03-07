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
#include "stdlib.h"

using std::vector;

class Physiccore : public TSingleton<Physiccore>{
private:
	vector<Solid*> elements;
	vector<int*> anchorPositions;

	void setAnchorsPosition();

public:
	template<class T>
	void addElement(T *element){
		elements.push_back(element);
		setAnchorsPosition();
	}
//	vector<Solid*> getElements(){return elements;}
	void deleteHoveredElements(int x, int y);
	void linkHoveredAnchors(int x, int y);
	vector<int*> getAnchorsPosition();
	void draftElements();
	void computeInteractiveForces();
	void groundHoveredAnchors(int x, int y);
};

#endif /* PHYSICCORE_H_ */