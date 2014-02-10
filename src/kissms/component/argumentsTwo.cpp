/*
 * argumentsTwo.cpp
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#include "kissms/kissms.h"

namespace kissms {

ArgumentsTwo::ArgumentsTwo() {

	argumentLeft = 0;
	argumentRight = 0;

}

ArgumentsTwo::~ArgumentsTwo() {

	free(argumentLeft);
	free(argumentRight);

}

void ArgumentsTwo::setLeft(Component* argument) {

	argumentLeft = argument;

}

void ArgumentsTwo::setRight(Component* argument) {

	argumentRight = argument;

}

void ArgumentsTwo::setArguments(Component* left, Component* right) {

	setLeft(left);
	setRight(right);

}

bool ArgumentsTwo::isCalculable() {

	return argumentLeft->isCalculable() && argumentRight->isCalculable();

}

bool ArgumentsTwo::isQuantifiable() {

	return argumentLeft->isQuantifiable() && argumentRight->isQuantifiable();

}

bool ArgumentsTwo::isOnLeft(Component* component) {

	if( argumentLeft == component ) {
		return true;
	} else if( argumentLeft->hasChild(component) ) {
		return true;
	}
	return false;

}

bool ArgumentsTwo::isOnRight(Component* component) {

	if( argumentRight == component ) {
		return true;
	} else if( argumentRight->hasChild(component) ) {
		return true;
	}
	return false;

}

ComponentType ArgumentsTwo::getType() {

	return tArgumentsTwo;

}

bool ArgumentsTwo::hasChild(Component* child) {

	if( argumentLeft == child || argumentRight == child ) {
		return true;
	} else if( argumentLeft->hasChild(child) || argumentRight->hasChild(child) ) {
		return true;
	}
	return false;

}

}


