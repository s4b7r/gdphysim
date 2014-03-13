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

	ResultCode rc = Successful;
	rc = argument->calculate();
	quantity = cos(argument->getQuantity());
	return rc;

}

ComponentType Cosinus::getType() {

	return tCosinus;

}

std::string Cosinus::getQuality() {

	std::string tmp;
	std::ostringstream oss;

	//if( isQuantifiable() ) {
	//	oss << getQuantity();
	//} else {
		oss << "cos(" << argument->getQuality() << ")";
	//}
	tmp = oss.str();
	return tmp;

}

}

