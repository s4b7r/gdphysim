/*
 * sinus.cpp
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#include "kissms/kissms.h"

namespace kissms {

Sinus::Sinus() {
}

Sinus::~Sinus() {
}

ResultCode Sinus::reformFor(Variable* variable, Component** newSide,
		Component** otherSide) {

	*newSide = argument;
	*otherSide = new SinusArc();
	return Successful;

}

ResultCode Sinus::calculate() {

	argument->calculate();
	quantity = sin(argument->getQuantity());
	return Successful;

}

ComponentType Sinus::getType() {

	return tSinus;

}

std::string Sinus::getQuality() {

	std::string tmp;
	std::ostringstream oss;

	if( isQuantifiable() ) {
		oss << getQuantity();
	} else {
		oss << "sin(" << argument->getQuality() << ")";
	}
	tmp = oss.str();
	return tmp;

}

}


