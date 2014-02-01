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

	return false;

}

bool Equation::isOnRight(Variable* variable) {

	return false;

}

bool Equation::isExplicitly(Variable* variable) {

	return false;

}

}
