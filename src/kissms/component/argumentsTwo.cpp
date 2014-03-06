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

	if( argumentLeft == component ||
			argumentLeft->hasChild(component) ) {
		return true;
	}
	return false;

}

bool ArgumentsTwo::isOnRight(Component* component) {

	if( argumentRight == component ||
			argumentRight->hasChild(component) ) {
		return true;
	}
	return false;

}

ComponentType ArgumentsTwo::getType() {

	return tArgumentsTwo;

}

bool ArgumentsTwo::hasChild(Component* child) {

	if( argumentLeft == child || argumentRight == child ||
			argumentLeft->hasChild(child) || argumentRight->hasChild(child) ) {
		return true;
	}
	return false;

}

bool ArgumentsTwo::isVectorial() {

	return argumentLeft->isVectorial() || argumentRight->isVectorial();

}

Component* ArgumentsTwo::getLeft() {

	return argumentLeft;

}

Component* ArgumentsTwo::getRight() {

	return argumentRight;

}

void ArgumentsTwo::getVariables(std::vector<Variable*>* variables) {

	argumentLeft->getVariables(variables);
	argumentRight->getVariables(variables);

}

void ArgumentsTwo::replace(Component* search, Component* replace) {

	if( argumentLeft == search ) {
		argumentLeft = replace;
	} else {
		argumentLeft->replace(search, replace);
	}
	if( argumentRight == search ) {
		argumentRight = replace;
	} else {
		argumentRight->replace(search, replace);
	}

}

void ArgumentsTwo::clone(Component* source, Component* destination) {

	Component::clone(source, destination);
	((ArgumentsTwo*)destination)->setLeft(((ArgumentsTwo*)source)->getLeft());
	((ArgumentsTwo*)destination)->setRight(((ArgumentsTwo*)source)->getRight());

}

Component* ArgumentsTwo::clone() {

	Component *cloned = 0;
	switch (this->getType()) {
	case tAddition:
		cloned = new Addition();

		break;
	case tMultiplication:
		cloned = new Multiplication();

		break;
	case tVectorproduct:
		cloned = new Vectorproduct();

		break;
	case tEquation:
		cloned = new Equation();

	default:
		break;
	}
	clone(this, cloned);
	return cloned;

}

}


