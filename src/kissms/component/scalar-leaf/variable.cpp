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
	name = (char*) malloc(sizeof(char) * 10);
	name[0] = 0;
	value = 0;

}

Variable::~Variable() {

	free(name);
	if( value != 0 ) {
		free(value);
	}

}

void Variable::setName(char* name) {

	strcpy(this->name, name);
	if( type == Unspecified ) {
		type = NoValue;
	}

}

bool Variable::isCalculable() {

	return false;

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
	this->*value = value;
	type = Integer;

}

void Variable::setValue(double value) {

	resetValue();
	this->value = (double*) malloc(sizeof(double));
	this->*value = value;
	type = Double;

}

}
