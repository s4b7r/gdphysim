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
		Component** otherSide, Component** placeholder) {

	Addition *addi = new Addition();
	Negation *nega = new Negation();
	Constant *cons = new Constant();
	if( isOnLeft(variable) ) {
		*newSide = argumentLeft;
		nega->setArgument(argumentRight);
	} else if( isOnRight(variable) ) {
		*newSide = argumentRight;
		nega->setArgument(argumentLeft);
	} else {
		return ImpossibleState;
	}
	addi->setRight(nega);
	addi->setLeft(cons);
	*otherSide = addi;
	*placeholder = cons;

	return Successful;

}

ResultCode Addition::calculate() {



}

}


