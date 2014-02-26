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

	argument->calculate();
	quantity = acos(argument->getQuantity());
	return Successful;

}

ComponentType CosinusArc::getType() {

	return tCosinusArc;

}

}


