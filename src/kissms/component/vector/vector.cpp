/*
 * vector.cpp
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#include "kissms/kissms.h"

namespace kissms {

Vector::Vector() {
}

Vector::~Vector() {
}

void Vector::setArgument(int index, Component* value) {

	arguments[index] = value;

}

Component* Vector::getArgument(int index) {

	return arguments[index];

}

bool Vector::isCalculable() {

	return false;

}

bool Vector::isQuantifiable() {

	return false;

}

ResultCode Vector::reformFor(Variable* variable, Component** newSide,
		Component** otherSide) {

	// TODO Vector::reformFor
	return NotYetImplemented;

}

ResultCode Vector::calculate() {

	// TODO Vector::calculate
	return NotYetImplemented;

}

ComponentType Vector::getType() {

	return tVector;

}

bool Vector::hasChild(Component* child) {

	// TODO Vector::hasChild
	return false;

}

}


