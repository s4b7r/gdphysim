/*
 * variable.cpp
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#include "kissms/kissms.h"

namespace kissms {

Variable::Variable() {

	type = Unspecified;
	name = (char*) malloc(sizeof(char) * 10);
	name[0] = 0;
	value = 0;

}

Variable::~Variable() {

	resetValue();
	free(name);

}

void Variable::setName(char* name) {

	strcpy(this->name, name);
	if( type == Unspecified ) {
		type = NoValue;
	}

}

bool Variable::isCalculable() {

	return isQuantifiable();

}

void Variable::resetValue() {

	switch ( type ) {
	case Integer:
	case Double:
		free(value);

		break;
	default:
		break;
	}
	if( name[0] != 0 ) {
		type = NoValue;
	} else {
		type = Unspecified;
	}

}

bool Variable::isQuantifiable() {

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

void Variable::setValue(int value) {

	resetValue();
	this->value = (int*) malloc(sizeof(int));
	*((int*)(this->value)) = value;
	type = Integer;
	quantity = value;

}

void Variable::setValue(double value) {

	resetValue();
	this->value = (double*) malloc(sizeof(double));
	*((double*)(this->value)) = value;
	type = Double;
	quantity = value;

}

Variable::Type Variable::getValue(void** value) {

	switch ( type ) {
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

ResultCode Variable::reformFor(Variable* variable, Component** newSide,
		Component** otherSide, Component** placeholder) {

	return ImpossibleState;

}

ResultCode Variable::calculate() {

	printf("var::cacl");
	return NotYetImplemented;

}

ComponentType Variable::getType() {

	return tVariable;

}

}


