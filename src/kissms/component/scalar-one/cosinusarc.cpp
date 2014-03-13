/*
 * cosinusarc.cpp
 *
 *  Created on: 10.02.2014
 *      Author: sieb
 */

#include "kissms/kissms.h"

namespace kissms {

CosinusArc::CosinusArc() {
}

CosinusArc::~CosinusArc() {
}

ResultCode CosinusArc::reformFor(Variable* variable,
		Component** newSide, Component** otherSide) {

	*newSide = argument;
	*otherSide = new Cosinus();
	return Successful;

}

ResultCode CosinusArc::calculate() {

	ResultCode rc = Successful;
	rc = argument->calculate();
	quantity = acos(argument->getQuantity());
	return rc;

}

ComponentType CosinusArc::getType() {

	return tCosinusArc;

}

std::string CosinusArc::getQuality() {

	std::string tmp;
	std::ostringstream oss;

	if( isQuantifiable() ) {
		oss << getQuantity();
	} else {
		oss << "arccos(" << argument->getQuality() << ")";
	}
	tmp = oss.str();
	return tmp;

}

}


