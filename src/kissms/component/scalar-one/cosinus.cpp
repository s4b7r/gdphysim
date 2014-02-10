/*
 * cosinus.cpp
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#include "kissms/kissms.h"

namespace kissms {

Cosinus::Cosinus() {
}

Cosinus::~Cosinus() {
}

ResultCode Cosinus::reformFor(Variable* variable, Component** newSide,
		Component** otherSide) {

	*newSide = argument;
	*otherSide = new CosinusArc();
	return Successful;

}

ResultCode Cosinus::calculate() {

	argument->calculate();
	quantity = cos(argument->getQuantity());
	return Successful;

}

ComponentType Cosinus::getType() {

	return tCosinus;

}

}


