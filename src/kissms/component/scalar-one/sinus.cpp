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

char* Sinus::getQuality() {

	char *tmp = (char*)malloc(sizeof(char)*10);
	if( isQuantifiable() ) {
		sprintf(tmp, "%8f", getQuantity());
	} else {
		sprintf(tmp, "sin(%s)", argument->getQuality());
	}
	return tmp;

}

}


