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

}


