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

	return ImpossibleState;

}

ResultCode Vector::calculate() {

	return ImpossibleState;

}

ComponentType Vector::getType() {

	return tVector;

}

bool Vector::hasChild(Component* child) {

	// This is not done in a single for-construct so that
	// the more complex hasChild()-call is executed if needed only
	for( int i = 0; i < 3; i++ ) {
		if( arguments[i] == child ) {
			return true;
		}
	}
	for( int i = 0; i < 3; i++ ) {
		if( arguments[i]->hasChild(child) ) {
			return true;
		}
	}
	return false;

}

bool Vector::isVectorial() {

	return true;

}

std::string Vector::getQuality() {

	std::string tmp = "ups";
	return tmp;
}

void Vector::getVariables(std::vector<Variable*>* variables) {

	// Not implemented

}

void Vector::replace(Component* search, Component* replace) {

	for( int i = 0; i < 3; i++ ) {
		if( arguments[i] == search ) {
			arguments[i] = replace;
		} else {
			arguments[i]->replace(search, replace);
		}
	}

}

Component* kissms::Vector::clone() {

	Vector *cloned = new Vector();
	for( int i = 0; i < 3; i++ ) {
		cloned->setArgument(i, this->getArgument(i)->clone());
	}
	return cloned;

}

}


