/*
 * variable.cpp
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#include <kissms/kissms.h>

namespace kissms {

Variable::Variable() {

	type = Unspecified;

}

Variable::~Variable() {
}

void Variable::setName(char* value) {
}

bool Variable::isCalculable() {

	return false;

}

bool Variable::isQuantifiable() {

	return false;

}

}


