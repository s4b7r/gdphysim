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

	//DP("Constant " << this->getQuality() << " is calculable: ");
	if( type != Unspecified ) {
		//DP(".. yes");
		return true;
	}
	//DP(".. no");
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

Constant::Type Constant::getValue(void* value) {

	switch ( type ) {
	case String:
		value = malloc(sizeof(char) * 10);
		strcpy((char*) value, (char*) this->value);

		break;
	case Integer:
		value = malloc(sizeof(int));
		*(int*)value = *((int*)(this->value));

		break;
	case Double:
		value = malloc(sizeof(double));
		*(double*)value = *((double*)(this->value));

		break;
	default:
		break;
	}
	return type;

}

ResultCode Constant::reformFor(Variable* variable, Component** newSide,
		Component** otherSide) {

	return ImpossibleState;

}

ResultCode Constant::calculate() {

	return Successful;

}

ComponentType Constant::getType() {

	return tConstant;

}

bool Constant::hasChild(Component* child) {

	return false;

}

bool Constant::isVectorial() {

	return false;

}

std::string Constant::getQuality() {

	std::string tmp;

	if( isQuantifiable() ) {
		std::ostringstream oss;
		oss << getQuantity();
		tmp = oss.str();
	} else {
		tmp = (char*)value;
	}

	return tmp;

}

void Constant::getVariables(std::vector<Variable*>* variables) {

	// This method is intentionally left blank
	// There are no Variables in a Constant

}

void Constant::replace(Component* search, Component* replace) {

	// This method is intentionally left blank
	// There are no Components in a Constant

}

Component* Constant::clone() {

	// TODO Constant::clone()

}

}


