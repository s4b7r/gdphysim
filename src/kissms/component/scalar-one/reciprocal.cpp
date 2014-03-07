/*
 * reciprocal.cpp
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#include "kissms/kissms.h"

namespace kissms {

Reciprocal::Reciprocal() {
}

Reciprocal::~Reciprocal() {
}

ResultCode Reciprocal::reformFor(Variable* variable,
		Component** newSide, Component** otherSide) {

	*newSide = argument;
	*otherSide = new Reciprocal();
	return Successful;

}

ResultCode Reciprocal::calculate() {

	argument->calculate();
	quantity = 1.0 / argument->getQuantity();
	return Successful;

}

ComponentType Reciprocal::getType() {

	return tReciprocal;

}

std::string Reciprocal::getQuality() {

	std::string tmp;
	std::ostringstream oss;

	//if( isQuantifiable() ) {
	//	oss << getQuantity();
	//} else {
		oss << "1/(" << argument->getQuality() << ")";
	//}
	tmp = oss.str();
	return tmp;

}

}


