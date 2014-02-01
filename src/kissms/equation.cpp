/*
 * equation.cpp
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#include <kissms/kissms.h>

namespace kissms {

Equation::Equation() {
}

Equation::~Equation() {
}

ResultCode Equation::solveFor(Variable* variable) {

	while( !isExplicitly(variable) ) {
		solveFor(variable, isOnLeft(variable));
	}

	//return Successful;
	return NotYetImplemented;

}

ResultCode Equation::calculateFor(Variable* variable) {

	return NotYetImplemented;

}

bool Equation::contains(Variable* variable) {

	return isOnLeft(variable) || isOnRight(variable);

}

bool Equation::isOnLeft(Variable* variable) {

	return isOnVector(variable, m_variablesLeft);

}

bool Equation::isOnRight(Variable* variable) {

	return isOnVector(variable, m_variablesRight);

}

bool Equation::isOnVector(Variable* variable, std::vector<Variable*> vector) {

	std::vector<Variable*>::iterator it = m_variablesRight.begin();

	while( it != m_variablesRight.end() ) {
		if( &*it == variable ) {
			return true;
		}
	}
	return false;

}

bool Equation::isExplicitly(Variable* variable) {

	if( m_argumentLeft == variable || m_argumentRight == variable ) {
		return true;
	} else {
		return false;
	}

}

ResultCode Equation::solveFor(Variable* variable, bool variableOnLeft) {

	Component **reformComponent;
	Component **otherSide;
	Component **newSide;
	Component **newOtherSide;
	Component **placeholder;
	ResultCode reformResult;

	if( variableOnLeft ) {
		reformComponent = &m_argumentLeft;
		otherSide = &m_argumentRight;
	} else {
		reformComponent = &m_argumentRight;
		otherSide = &m_argumentLeft;
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
	return GeneralFailure;

}

}

