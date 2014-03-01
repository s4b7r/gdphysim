/*
 * equationsystem.cpp
 *
 *  Created on: 25.02.2014
 *      Author: sieb
 */

#include "kissms/kissms.h"

namespace kissms {

Equationsystem::Equationsystem() {
}

Equationsystem::~Equationsystem() {
}

void Equationsystem::addEquation(Equation* equation) {

	if( !containsEquation(equation) ) {
		equations.push_back(equation);
	}

}

void Equationsystem::removeEquation(Equation* equation) {

	std::vector<Equation*>::iterator it = equations.begin();
	bool found = false;

	while( !found && it != equations.end() ) {
		if( *it == equation ) {
			equations.erase(it);
			found = true;
		}
		it++;
	}

}

bool Equationsystem::containsEquation(Equation* equation) {

	std::vector<Equation*>::iterator it = equations.begin();

	while( it != equations.end() ) {
		if( *it == equation ) {
			return true;
		}
		it++;
	}
	return false;

}

ResultCode Equationsystem::solveFor(Variable* variable) {

	// TODO Implement Equationsystem::solveFor(Variable*)
	return NotYetImplemented;

	std::vector<Equation*>::iterator eqIt;
	int minVarCount;
	Equation *solveEquation = 0;

	// Find Equation containing the given Variable with the least other Variables
	eqIt = equations.begin();
	while( eqIt != equations.end() ) {
		if( (*eqIt)->hasChild(variable) ) {
			std::vector<Variable*> eqVariables;
			(*eqIt)->getVariables(&eqVariables);
			if( minVarCount > eqVariables.size() || solveEquation == 0 ) {
				minVarCount = eqVariables.size();
				solveEquation = (*eqIt);
			}
		}
	}

	// Solve Equation for given Variable and get the required other Variables
	solveEquation->solveFor(variable);
	std::vector<Variable*> pendingVariables;
	if( solveEquation->getLeft() == variable ) {
		solveEquation->getRight()->getVariables(&pendingVariables);
	} else {
		solveEquation->getLeft()->getVariables(&pendingVariables);
	}

	// Create Equationsystem with unused Equations
	Equationsystem equationsLeft;
	eqIt = equations.begin();
	while( eqIt != equations.end() ) {
		if( *eqIt != solveEquation ) {
			equationsLeft.addEquation(*eqIt);
		}
	}
	equationsLeft.setPendingVariables(pendingVariables);
	equationsLeft.solvePending();

	return NotYetImplemented;

}

ResultCode Equationsystem::calculateFor(Variable* variable) {

	// TODO Implement Equationsystem::calculateFor(Variable*)
	return NotYetImplemented;

}

void Equationsystem::setPendingVariables(
		std::vector<Variable*> pendingVariables) {

	this->pendingVariables = pendingVariables;

}

ResultCode Equationsystem::solvePending() {

	// TODO Implement Equationsystem::solvePending()
	return NotYetImplemented;

}

}


