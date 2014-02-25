/*
 * addition.cpp
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#include "kissms/kissms.h"

namespace kissms {

Addition::Addition() {
}

Addition::~Addition() {
}

ResultCode Addition::reformFor(Variable* variable, Component** newSide,
		Component** otherSide) {

	*otherSide = new Addition();
	Negation *nega = new Negation();
	if( isOnLeft((Component*)variable) ) {
		*newSide = argumentLeft;
		nega->setArgument(argumentRight);
	} else if( isOnRight((Component*)variable) ) {
		*newSide = argumentRight;
		nega->setArgument(argumentLeft);
	} else {
		return ImpossibleState;
	}
	(*(Addition**)otherSide)->setRight(nega);

	return Successful;

}

ResultCode Addition::calculate() {

	if( !isCalculable() ) {
		return NotCalculable;
	}
	if( isQuantifiable() ) {
		argumentLeft->calculate();
		argumentRight->calculate();
		quantity = argumentLeft->getQuantity() + argumentRight->getQuantity();
		return Successful;
	} else {
		return NotYetImplemented;
	}

	return ImpossibleState;

}

ComponentType Addition::getType() {

	return tAddition;

}

char* Addition::getQuality() {

	char *tmp = (char*)malloc(sizeof(char)*10);
	if( isQuantifiable() ) {
		sprintf(tmp, "%8f", getQuantity());
	} else {
		sprintf(tmp, "%s + %s", argumentLeft->getQuality(), argumentRight->getQuality());
	}
	return tmp;

}

}


