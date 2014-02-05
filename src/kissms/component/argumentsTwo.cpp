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

	argumentLeft = left;
	argumentRight = right;

}

bool ArgumentsTwo::isCalculable() {

	return argumentLeft->isCalculable() && argumentRight->isCalculable();

}

bool ArgumentsTwo::isQuantifiable() {

	return argumentLeft->isQuantifiable() && argumentRight->isQuantifiable();

}

}


