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
		printf("\nc\n");
		calcComp = argumentRight;
		explicitVariable = (Variable*) argumentLeft;
	} else if( isOnRight(variable) ) {
		calcComp = argumentLeft;
		explicitVariable = (Variable*) argumentRight;
	} else {
		return ImpossibleState;
	}
	printf("type of calcComp: %d\n", calcComp->getType());
	if( !calcComp->isCalculable() ) {
		printf("\na\n");
		return NotCalculable;
	}
	printf("\nb\n");
	rc = calcComp->calculate();
	if( rc == Successful ) {
		explicitVariable->setValue(calcComp->getQuantity());
	}

	return rc;

}

bool Equation::contains(Variable* variable) {

	return isOnLeft(variable) || isOnRight(variable);

}

bool Equation::isExplicitly(Variable* variable) {

	if( argumentLeft == (Component*)variable || argumentRight == (Component*)variable ) {
		return true;
	}
	return false;

}

ResultCode Equation::calculate() {

	printf("eq::calc");
	return NotYetImplemented;

}

ComponentType Equation::getType() {

	return tEquation;

}

ResultCode Equation::solveFor(Variable* variable, bool variableOnLeft) {

	printf("varonleft:%d\n",variableOnLeft);

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
		(*(ArgumentsTwo**)newOtherSide)->setLeft(*otherSide);
		// TODO Think about memory leaks
		// Is the placeholder referenced anywhere else?
		*otherSide = *newOtherSide;

		return Successful;
	}
	return reformResult;

}

ResultCode Equation::reformFor(Variable* variable, Component** newSide,
		Component** otherSide, Component** placeholder) {

	printf("eq::ref");
	return NotYetImplemented;

}

}


