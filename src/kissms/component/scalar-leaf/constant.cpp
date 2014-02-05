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
	value = 0;

}

Constant::~Constant() {

	resetValue();

}

void Constant::setValue(char* value) {

	resetValue();
	this->value = (char*) malloc(sizeof(char) * 10);
	strcpy((char*) this->value, value);
	type = String;

}

void Constant::setValue(int value) {

	resetValue();
	this->value = (int*) malloc(sizeof(int));
	this->*value = value;
	type = Integer;

}

void Constant::setValue(double value) {

	resetValue();
	this->value = (double*) malloc(sizeof(double));
	this->*value = value;
	type = Double;

}

bool Constant::isCalculable() {

	if( type != Unspecified ) {
		return true;
	}
	return false;

}

bool Constant::isQuantifiable() {

	switch ( type ) {
	case Integer:
	case Double:
		return true;

		break;
	default:
		return false;

		break;
	}

	return false;

}

void Constant::resetValue() {

	switch ( type ) {
	case String:
	case Integer:
	case Double:
		free(value);

		break;
	default:
		break;
	}
	type = Unspecified;

}

}
