/*
 * constant.cpp
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#include "kissms/kissms.h"

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
	*((int*)(this->value)) = value;
	type = Integer;
	quantity = value;

}

void Constant::setValue(double value) {

	resetValue();
	this->value = (double*) malloc(sizeof(double));
	*((double*)(this->value)) = value;
	type = Double;
	quantity = value;

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
	quantity = NAN;

}

Constant::Type Constant::getValue(void** value) {

	switch ( type ) {
	case String:
		*value = malloc(sizeof(char) * 10);
		strcpy((char*) *value, (char*) this->value);

		break;
	case Integer:
		*value = malloc(sizeof(int));
		**(int**)value = *((int*)(this->value));

		break;
	case Double:
		*value = malloc(sizeof(double));
		**(double**)value = *((double*)(this->value));

		break;
	default:
		break;
	}
	return type;

}

ResultCode Constant::reformFor(Variable* variable, Component** newSide,
		Component** otherSide, Component** placeholder) {

	return NotYetImplemented;

}

ResultCode Constant::calculate() {

	return NotYetImplemented;

}

}


