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

	ResultCode rc = Successful;
	rc = argument->calculate();
	quantity = argument->getQuantity() * -1.0;
	return rc;

}

ComponentType Negation::getType() {

	return tNegation;

}

std::string Negation::getQuality() {

	std::string tmp;
	std::ostringstream oss;

	//if( isQuantifiable() ) {
	//	oss << getQuantity();
	//} else {
		oss << "-(" << argument->getQuality() << ")";
	//}
	tmp = oss.str();
	return tmp;

}

}


