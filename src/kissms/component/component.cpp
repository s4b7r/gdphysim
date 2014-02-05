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

}

Component::~Component() {
}

double Component::getQuantity() {

	return quantity;

}

}

