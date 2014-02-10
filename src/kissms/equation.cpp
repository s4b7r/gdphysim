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
	Variable *explicitVariable;

	rc = solveFor(variable);
	if( rc != Successful ) {
		return rc;
	}
	if( isOnLeft(variable) ) {
		calcComp = argumentRight;
		explicitVariable = (Variable*) argumentLeft;
	} else if( isOnRight(variable) ) {
		calcComp = argumentLeft;
		explicitVariable = (Variable*) argumentRight;
	} else {
		return ImpossibleState;
	}
	if( !calcComp->isCalculable() ) {
		return NotCalculable;
	}
	rc = calcComp->calculate();
	if( rc == Successful ) {
		explicitVariable->setValue(calcComp->getQuantity());
	}

	return rc;

}

bool Equation::isExplicitly(Variable* variable) {

	if( argumentLeft == (Component*)variable || argumentRight == (Component*)variable ) {
		return true;
	}
	return false;

}

ResultCode Equation::calculate() {

	return ImpossibleState;

}

ComponentType Equation::getType() {

	return tEquation;

}

ResultCode Equation::solveFor(Variable* variable, bool variableOnLeft) {

	Component **reformComponent;
	Component **otherSide;
	Component **newSide = (Component**) malloc(sizeof(Component*));
	Component **newOtherSide = (Component**) malloc(sizeof(Component*));
	ResultCode reformResult;

	if( variableOnLeft ) {
		reformComponent = &argumentLeft;
		otherSide = &argumentRight;
	} else {
		reformComponent = &argumentRight;
		otherSide = &argumentLeft;
	}

	reformResult = (*reformComponent)->reformFor(variable, newSide, newOtherSide);

	if( reformResult == Successful ) {
		free(reformComponent);
		*reformComponent = *newSide;
		(*(ArgumentsTwo**)newOtherSide)->setLeft(*otherSide);
		*otherSide = *newOtherSide;

		return Successful;
	}
	return reformResult;

}

ResultCode Equation::reformFor(Variable* variable, Component** newSide,
		Component** otherSide) {

	return ImpossibleState;

}

}


