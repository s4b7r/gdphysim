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

char* Reciprocal::getQuality() {

	char *tmp = (char*)malloc(sizeof(char)*10);
	if( isQuantifiable() ) {
		sprintf(tmp, "%8f", getQuantity());
	} else {
		sprintf(tmp, "1/(%s)", argument->getQuality());
	}
	return tmp;

}

}


