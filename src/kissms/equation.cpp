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

	// Repeatedly try to solve the Equation for the given Variable,
	// until the Variable is explicitly represented.
	// Abort if solving process fails.
	while( !isExplicitly(variable) && solveResult == Successful ) {
		solveResult = solveFor(variable, isOnLeft(variable));
	}

	return solveResult;

}

ResultCode Equation::calculateFor(Variable* variable) {

	ResultCode rc;
	Component *calcComp;
	Variable *explicitVariable;

	// First the Equation has to be solved
	rc = solveFor(variable);
	if( rc != Successful ) {
		return rc;
	}
	// Set the placeholder regarding the Equation's side which the Variable belongs to
	if( isOnLeft(variable) ) {
		calcComp = argumentRight;
		explicitVariable = (Variable*) argumentLeft;
	} else if( isOnRight(variable) ) {
		calcComp = argumentLeft;
		explicitVariable = (Variable*) argumentRight;
	} else {
		printf("Debug: Equation - Variable neither on left nor on right\n");
		return ImpossibleState;
	}
	if( !calcComp->isCalculable() ) {
		return NotCalculable;
	}
	rc = calcComp->calculate();
	if( rc == Successful ) {
		// TODO What is with non-quantifiable Components?
		// If everything is okay, set the Variable's numerical value
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

	/**
	 * The Equation's argument on the Variable's side. This Component
	 * will have to reform itself.
	 */
	Component **reformComponent;
	/**
	 * The Equation's argument not on the Variable's side.
	 */
	Component **otherSide;
	/**
	 * The Component which will replace the Component on the Variable's side.
	 */
	Component **newSide = (Component**) malloc(sizeof(Component*));
	/**
	 * The Component which will encapsulate the Component not on the Variable's side.
	 */
	Component **newOtherSide = (Component**) malloc(sizeof(Component*));
	ResultCode reformResult;

	// Set the placeholder regarding the Equation's side which the Variable belongs to
	if( variableOnLeft ) {
		reformComponent = &argumentLeft;
		otherSide = &argumentRight;
	} else {
		reformComponent = &argumentRight;
		otherSide = &argumentLeft;
	}

	// Call the Component's reform-method
	reformResult = (*reformComponent)->reformFor(variable, newSide, newOtherSide);

	// Further processing on success only
	if( reformResult == Successful ) {
		free(*reformComponent);
		// Replace Variable's side
		*reformComponent = *newSide;
		// Fill the encapsulating Component with the other side's old Component
		ComponentType ct = (*newOtherSide)->getType();
		switch (ct) {
		case tCosinus:
		case tNegation:
		case tReciprocal:
		case tSinus:
		case tSinusArc:
		case tCosinusArc:
			(*(ArgumentsOne**)newOtherSide)->setArgument(*otherSide);

			break;
		case tAddition:
		case tMultiplication:
			(*(ArgumentsTwo**)newOtherSide)->setLeft(*otherSide);

			break;
		default:
			return ImpossibleState;
			break;
		}
		// Replace other side
		*otherSide = *newOtherSide;

		return Successful;
	}
	return reformResult;

}

ResultCode Equation::reformFor(Variable* variable, Component** newSide,
		Component** otherSide) {

	return ImpossibleState;

}

ResultCode Equation::getScalarEquations(Equation* equations[]) {

	// TODO Equation::getScalarEquations
	return NotYetImplemented;

}

}


