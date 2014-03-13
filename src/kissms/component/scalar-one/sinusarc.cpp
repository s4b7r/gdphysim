/*
 * sinusarc.cpp
 *
 *  Created on: 10.02.2014
 *      Author: sieb
 */

#include "kissms/kissms.h"

namespace kissms {

SinusArc::SinusArc() {
}

SinusArc::~SinusArc() {
}

ResultCode SinusArc::reformFor(Variable* variable, Component** newSide,
		Component** otherSide) {

	*newSide = argument;
	*otherSide = new Sinus();
	return Successful;

}

ResultCode SinusArc::calculate() {

	ResultCode rc = Successful;
	rc = argument->calculate();
	quantity = asin(argument->getQuantity());
	return rc;

}

ComponentType SinusArc::getType() {

	return tSinusArc;

}

std::string SinusArc::getQuality() {

	std::string tmp;
	std::ostringstream oss;

	if( isQuantifiable() ) {
		oss << getQuantity();
	} else {
		oss << "arcsin(" << argument->getQuality() << ")";
	}
	tmp = oss.str();
	return tmp;

}

}


