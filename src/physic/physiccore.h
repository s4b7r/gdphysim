/*
 * physiccore.h
 *
 *  Created on: Mar 1, 2014
 *      Author: kevin
 */

#ifndef PHYSICCORE_H_
#define PHYSICCORE_H_
#define PHYSICCORE Physiccore::Get()

#include "kissms/kissms.h"
#include "gui/TSingleton.cpp"
#include "physic/solids/solid.h"

using kissms::Equation;
using kissms::Equationsystem;
using kissms::Variable;
using std::vector;

struct SystemEquations{
//	vector<Equation> forceEquations;
//	vector<Equation> torqueEquations;
	vector<Variable*> xVariables;
	vector<Variable*> yVariables;
};

class Physiccore : public TSingleton<Physiccore>{
private:
	vector<Solid*> elements;
	vector<int*> anchorPositions;
	vector<SystemEquations*> systemEquationsPerElement;
	Equationsystem equationSystem;

	void setAnchorsPosition();
	Variable** addInteractiveForceVarFromSolidToRodOfAnchor(Anchor a);
	int fillEquationSystem();

public:
	template<class T>
	void addElement(T *element){
		elements.push_back(element);
		elements.at(elements.size()-1)->setId(elements.size()-1);
		setAnchorsPosition();
	}
	void solve();
	//	vector<Solid*> getElements(){return elements;}
	void deleteHoveredElements(int x, int y);
	void linkHoveredAnchors(int x, int y);
	vector<int*> getAnchorsPosition();
	void draftElements();
	void groundHoveredAnchors(int x, int y);
};

#endif /* PHYSICCORE_H_ */
