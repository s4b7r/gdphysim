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

	argument->calculate();
	quantity = asin(argument->getQuantity());
	return Successful;

}

ComponentType SinusArc::getType() {

	return tSinusArc;

}

char* SinusArc::getQuality() {

	char *tmp = (char*)malloc(sizeof(char)*10);
	if( isQuantifiable() ) {
		sprintf(tmp, "%8f", getQuantity());
	} else {
		sprintf(tmp, "arcsin(%s)", argument->getQuality());
	}
	return tmp;

}

}


