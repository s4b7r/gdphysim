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

	return NotYetImplemented;

}

ResultCode Equation::calculateFor(Variable* variable) {

	return NotYetImplemented;

}

bool Equation::contains(Variable* variable) {

	return false;

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

}
