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

	Addition *addi = new Addition();
	Negation *nega = new Negation();
	printf("isOnLeft: %d", isOnLeft((Component*)variable));
	if( isOnLeft((Component*)variable) ) {
		*newSide = argumentLeft;
		nega->setArgument(argumentRight);
	} else if( isOnRight((Component*)variable) ) {
		*newSide = argumentRight;
		nega->setArgument(argumentLeft);
	} else {
		return ImpossibleState;
	}
	addi->setRight(nega);
	*otherSide = addi;

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

}


