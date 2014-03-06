/*
 * argumentsOne.cpp
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#include "kissms/kissms.h"

namespace kissms {

ArgumentsOne::ArgumentsOne() {

	argument = 0;

}

ArgumentsOne::~ArgumentsOne() {

	free(argument);

}

void ArgumentsOne::setArgument(Component* argument) {

	this->argument = argument;

}

bool ArgumentsOne::isCalculable() {

	return argument->isCalculable();

}

bool ArgumentsOne::isQuantifiable() {

	return argument->isQuantifiable();

}

ComponentType ArgumentsOne::getType() {

	return tArgumentsOne;

}

bool kissms::ArgumentsOne::hasChild(Component* child) {

	if( argument == child ||
			argument->hasChild(child) ) {
		return true;
	}
	return false;

}

bool ArgumentsOne::isVectorial() {

	return argument->isVectorial();

}

Component* ArgumentsOne::getArgument() {

	return argument;

}

void ArgumentsOne::getVariables(std::vector<Variable*>* variables) {

	argument->getVariables(variables);

}

void ArgumentsOne::replace(Component* search, Component* replace) {

	if( argument == search ) {
		argument = replace;
	} else {
		argument->replace(search, replace);
	}

}

Component* ArgumentsOne::clone() {

	Component *cloned = 0;
	switch (this->getType()) {
	case tCosinus:
		cloned = new Cosinus();

		break;
	case tCosinusArc:
		cloned = new CosinusArc();

		break;
	case tNegation:
		cloned = new Negation();

		break;
	case tReciprocal:
		cloned = new Reciprocal;

		break;
	case tSinus:
		cloned = new Sinus();

		break;
	case tSinusArc:
		cloned = new SinusArc();

		break;
	default:
		break;
	}
	clone(this, cloned);
	return cloned;

}

void ArgumentsOne::clone(Component* source, Component* destination) {

	Component::clone(source, destination);
	((ArgumentsOne*)destination)->setArgument(((ArgumentsOne*)source)->getArgument());

}

}


