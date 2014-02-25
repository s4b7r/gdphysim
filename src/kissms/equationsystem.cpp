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

	Equation *mainEquation = 0;
	std::vector<Equation*>::iterator it = equations.begin();
	bool found = false;
	ResultCode rc = 0;

	while( !found && it != equations.end() ) {
		if( (*it)->hasChild(variable) ) {
			mainEquation = *it;
			found = true;
		}
		it++;
	}
	if( !found ) {
		return GeneralFailure;
	}
	rc = mainEquation->solveFor(variable);
	if( rc != Successful ) {
		return rc;
	}
	Component *mainEqsValueside = 0;
	if( mainEquation->getLeft() == variable ) {
		mainEqsValueside = mainEquation->getRight();
	} else {
		mainEqsValueside = mainEquation->getLeft();
	}
	if( mainEqsValueside->isCalculable() ) {
		return Successful;
	}
	std::vector<Variable*> varsToResolve;
	mainEqsValueside->getVariables(&varsToResolve);
	std::vector<Equation*> equationsLeft;
	it = equations.begin();
	while( it != equations.end() ) {
		if( *it != mainEquation ) {
			equationsLeft.push_back(*it);
		}
		it++;
	}
	if( equationsLeft.size() < varsToResolve.size() ) {
		return GeneralFailure;
	}

	// TODO Resolve Variables on the other side

}

ResultCode Equationsystem::calculateFor(Variable* variable) {

	ResultCode rc = solveFor(variable);
	if( rc != Successful ) {
		return rc;
	}
	// TODO Calculate the Equationsystem

}

}
