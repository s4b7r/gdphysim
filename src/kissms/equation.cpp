/*
 * equation.cpp
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#include "kissms/kissms.h"

namespace kissms {

Equation::Equation() {
}

Equation::~Equation() {
}

ResultCode Equation::solveFor(Variable* variable) {

	ResultCode solveResult = Successful;

	while( !isExplicitly(variable) && solveResult == Successful ) {
		solveResult = solveFor(variable, isOnLeft(variable));
	}

	return solveResult;

}

ResultCode Equation::calculateFor(Variable* variable) {

	ResultCode rc;
	Component *calcComp;

	rc = solveFor(variable);
	if( rc != Successful ) {
		return rc;
	}
	if( isOnLeft(variable) ) {
		calcComp = argumentRight;
	} else if( isOnRight(variable) ) {
		calcComp = argumentLeft;
	} else {
		return ImpossibleState;
	}
	if( !calcComp->isCalculable() ) {
		return NotCalculable;
	}
	rc = calcComp->calculate();

	return rc;

}

bool Equation::contains(Variable* variable) {

	return isOnLeft(variable) || isOnRight(variable);

}

bool Equation::isExplicitly(Variable* variable) {

	if( argumentLeft == (Component*)variable || argumentRight == (Component*)variable ) {
		return true;
	} else {
		return false;
	}

}

void Equation::calculate() {
}

ResultCode Equation::solveFor(Variable* variable, bool variableOnLeft) {

	Component **reformComponent;
	Component **otherSide;
	Component **newSide = (Component**) malloc(sizeof(Component*));
	Component **newOtherSide = (Component**) malloc(sizeof(Component*));
	Component **placeholder = (Component**) malloc(sizeof(Component*));
	ResultCode reformResult;

	if( variableOnLeft ) {
		reformComponent = &argumentLeft;
		otherSide = &argumentRight;
	} else {
		reformComponent = &argumentRight;
		otherSide = &argumentLeft;
	}

	reformResult = (*reformComponent)->reformFor(variable, newSide, newOtherSide, placeholder);

	if( reformResult == Successful ) {
		*reformComponent = *newSide;
		// TODO Think about memory leaks
		// Is the old Component referenced anywhere else?
		*placeholder = *otherSide;
		// TODO Think about memory leaks
		// Is the placeholder referenced anywhere else?
		*otherSide = *newOtherSide;

		return Successful;
	}
	return reformResult;

}

ResultCode Equation::reformFor(Variable* variable, Component** newSide,
		Component** otherSide, Component** placeholder) {

	return NotYetImplemented;

}

bool Equation::isCalculable() {

	return false;

}

bool Equation::isQuantifiable() {

	return false;

}

}


