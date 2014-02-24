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

	printf("ArgumentsOne::isVectorial()\n");
	printf("This type: %d\n", getType());
	printf("Argument's type: %d\n", argument->getType());
	argument->isVectorial();
	printf("Done\n");
	return argument->isVectorial();

}

Component* ArgumentsOne::getArgument() {

	return argument;

}

}


