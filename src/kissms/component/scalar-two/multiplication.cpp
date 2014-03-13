/*
 * multiplication.cpp
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#include "kissms/kissms.h"

namespace kissms {

Multiplication::Multiplication() {
}

Multiplication::~Multiplication() {
}

ResultCode Multiplication::reformFor(Variable* variable,
		Component** newSide, Component** otherSide) {

	*otherSide = new Multiplication();
	Reciprocal *reci = new Reciprocal();
	if( isOnLeft((Component*)variable) ) {
		*newSide = argumentLeft;
		reci->setArgument(argumentRight);
	} else if( isOnRight((Component*)variable) ) {
		*newSide = argumentRight;
		reci->setArgument(argumentLeft);
	} else {
		return ImpossibleState;
	}
	(*(Multiplication**)otherSide)->setRight(reci);

	return Successful;

}

ResultCode Multiplication::calculate() {

	ResultCode rc = Successful;
	if( !isCalculable() ) {
		return NotCalculable;
	}
	if( isQuantifiable() ) {
		rc = argumentLeft->calculate();
		if( rc != Successful ) {
			return rc;
		}
		rc = argumentRight->calculate();
		if( rc != Successful ) {
			return rc;
		}
		quantity = argumentLeft->getQuantity() * argumentRight->getQuantity();
		return rc;
	} else {
		DP("NotYetImplemented:: Multiplication::calculate()");
		return NotYetImplemented;
	}

	return ImpossibleState;

}

ComponentType Multiplication::getType() {

	return tMultiplication;

}

std::string Multiplication::getQuality() {

	std::string tmp;
	std::ostringstream oss;

	//if( isQuantifiable() ) {
	//	oss << getQuantity();
	//} else {
	Component *argLeft = argumentLeft;
	Component *argRight = argumentRight;
	std::string argLQual = argLeft->getQuality();
	std::string argRQual = argRight->getQuality();
	oss << "(" << argumentLeft->getQuality() << ")*(" << argumentRight->getQuality() << ")";
	//}
	tmp = oss.str();
	return tmp;

}

}


