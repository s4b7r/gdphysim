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
	// Check for previously assigned numerical values
	// to preserve the Variable's type
	if( type == Unspecified ) {
		type = NoValue;
	}

}

bool Variable::isCalculable() {

	//return type == Qualified || isQuantifiable();
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
	// Check for the Variable's name,
	// so it will not get marked as unspecified if there is one
	if( name[0] != 0 ) {
		type = NoValue;
	} else {
		type = Unspecified;
	}
	quality = "";

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
		**((int**)value) = *((int*)(this->value));

		break;
	case Double:
		*value = malloc(sizeof(double));
		**((double**)value) = *((double*)(this->value));

		break;
	default:
		break;
	}
	return type;

}

ResultCode Variable::reformFor(Variable* variable, Component** newSide,
		Component** otherSide) {

	return ImpossibleState;

}

ResultCode Variable::calculate() {

	return Successful;

}

ComponentType Variable::getType() {

	return tVariable;

}

bool kissms::Variable::hasChild(Component* child) {

	return false;

}

bool Variable::isVectorial() {

	return false;

}

char* Variable::getName() {

	return name;

}

std::string Variable::getQuality() {

	std::string tmp;

	//if( isQuantifiable() ) {
	//	std::ostringstream oss;
	//	oss << getQuantity();
	//	tmp = oss.str();
	//} else {
	if( type == Qualified ) {
		tmp = quality;
	} else {
		tmp = name;
	}
	//}

	return tmp;

}

void Variable::setQuality(std::string quality) {

	this->quality = quality;
	if( type <= NoValue ) {
		type = Qualified;
	}

}

void Variable::getVariables(std::vector<Variable*>* variables) {

	variables->push_back(this);

}

void Variable::replace(Component* search, Component* replace) {
}

Component* Variable::clone() {

	return this;

	/*Variable *cloned = new Variable();

	cloned->setName(this->getName());
	void **value = (void**)malloc(sizeof(void*));
	Variable::Type type = this->getValue(value);
	switch (type) {
	case Variable::Integer:
		cloned->setValue(**((int**)value));

		break;
	case Variable::Double:
		cloned->setValue(**((double**)value));

		break;
	default:
		break;
	}
	cloned->setQuality(this->getQuality());

	return cloned;*/

}

}


