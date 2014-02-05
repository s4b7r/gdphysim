/*
 * constant.cpp
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#include <kissms/kissms.h>

namespace kissms {

Constant::Constant() {

	type = Unspecified;

}

Constant::~Constant() {
}

void Constant::setValue(char* value) {
}

void Constant::setValue(int value) {
}

void Constant::setValue(double value) {
}

bool Constant::isCalculable() {

	return true;

}

bool Constant::isQuantifiable() {

	if( type == Integer || type == Double ) {
		return true;
	} else {
		return false;
	}

}

}

