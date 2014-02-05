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

	if( isOnLeft(variable) ) {
		Addition *addi = new Addition();
		Negation *nega = new Negation();
		Constant *cons = new Constant();
		nega->setArgument(argumentRight);
		addi->setRight(nega);
		addi->setLeft(cons);
		*newSide = argumentLeft;
		*otherSide = addi;
		*placeholder = cons;
	}
	return NotYetImplemented;

}

ResultCode Addition::calculate() {



}

}


