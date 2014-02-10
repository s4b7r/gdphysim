/*
 * negation.cpp
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#include "kissms/kissms.h"

namespace kissms {

Negation::Negation() {
}

Negation::~Negation() {
}

ResultCode Negation::reformFor(Variable* variable, Component** newSide,
		Component** otherSide) {

	*newSide = argument;
	*otherSide = new Negation();
	return Successful;

}

ResultCode Negation::calculate() {

	argument->calculate();
	quantity = argument->getQuantity() * -1.0;
	return Successful;

}

ComponentType Negation::getType() {

	return tNegation;

}

}


