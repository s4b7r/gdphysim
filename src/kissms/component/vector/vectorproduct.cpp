/*
 * vectorproduct.cpp
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#include "kissms/kissms.h"

namespace kissms {

Vectorproduct::Vectorproduct() {
}

Vectorproduct::~Vectorproduct() {
}

ResultCode Vectorproduct::reformFor(Variable* variable,
		Component** newSide, Component** otherSide) {

	return ImpossibleState;

}

ResultCode Vectorproduct::calculate() {

	return ImpossibleState;

}

Vector* Vectorproduct::getVector() {

	// TODO Vectorproduct::getVector
	return 0;

}

}


