/*
 * component.cpp
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#include "kissms/kissms.h"

namespace kissms {

Component::Component() {

	quantity = NAN;
	debugId = -1;

}

Component::~Component() {
}

double Component::getQuantity() {

	return quantity;

}

ComponentType Component::getType() {

	return tUnspecified;
	
}

void Component::setDebugId(int dbgId) {

	debugId = dbgId;

}

int Component::getDebugId() {

	return debugId;

}

}


