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

bool ArgumentsTwo::isOnLeft(Variable* variable) {

	return isOnVector(variable, variablesLeft);

}

bool ArgumentsTwo::isOnRight(Variable* variable) {

	return isOnVector(variable, variablesRight);

}

bool ArgumentsTwo::isOnVector(Variable* variable, std::vector<Variable*> vector) {

	std::vector<Variable*>::iterator it = variablesRight.begin();

	while( it != variablesRight.end() ) {
		if( *it == variable ) {
			return true;
		}
	}
	return false;

}

ComponentType kissms::ArgumentsTwo::getType() {

	return tArgumentsTwo;

}


}

