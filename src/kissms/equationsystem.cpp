/*
 * equationsystem.cpp
 *
 *  Created on: 25.02.2014
 *      Author: sieb
 */

#include "kissms/kissms.h"

namespace kissms {

Equationsystem::Equationsystem() {

	pendingVariables = new std::vector<Variable*>();
	traceVariables = new std::vector<struct trace>();

}

Equationsystem::~Equationsystem() {
}

void Equationsystem::addEquation(Equation* equation) {

	if( !containsEquation(equation) ) {
		equations.push_back(equation);
	}

}

void Equationsystem::removeEquation(Equation* equation) {

	std::vector<Equation*>::iterator it = equations.begin();
	bool found = false;

	while( !found && it != equations.end() ) {
		if( *it == equation ) {
			equations.erase(it);
			found = true;
		}
		it++;
	}

}

bool Equationsystem::containsEquation(Equation* equation) {

	std::vector<Equation*>::iterator it = equations.begin();

	while( it != equations.end() ) {
		if( *it == equation ) {
			return true;
		}
		it++;
	}
	return false;

}

ResultCode Equationsystem::solveFor(Variable* variable) {

	std::vector<Equation*>::iterator eqIt;
	unsigned int minVarCount;
	Equation *solveEquation = 0;
	ResultCode rc;

	DP("Eqsys with " << equations.size() << " Eqs left");

	// Find Equation containing the given Variable with the least other Variables
	eqIt = equations.begin();
	while( eqIt != equations.end() ) {
		if( (*eqIt)->hasChild(variable) ) {
			std::vector<Variable*> eqVariables;
			(*eqIt)->getVariables(&eqVariables);
			if( minVarCount > eqVariables.size() || solveEquation == 0 ) {
				minVarCount = eqVariables.size();
				solveEquation = (*eqIt);
			}
		}
		eqIt++;
	}

	// Solve Equation for given Variable
	solveEquation->solveFor(variable);

	// Save Variable to check for circular dependencies
	struct trace newTrace;
	newTrace.variable = variable;
	newTrace.equation = solveEquation;
	traceVariables->push_back(newTrace);

	// Get the Equation's other side
	Component *valueComponent;
	if( solveEquation->getLeft() == variable ) {
		valueComponent = solveEquation->getRight();
	} else {
		valueComponent = solveEquation->getLeft();
	}

	// Get dependencies (Variables which have to be solved to solve this one)
	std::vector<Variable*> otherVariables;
	std::vector<Variable*>::iterator varIt;
	valueComponent->getVariables(&otherVariables);
	varIt = otherVariables.begin();
	while( varIt != otherVariables.end() ) {
		if( !(*varIt)->isCalculable() ) {
			pendingVariables->push_back(*varIt);

			// Check for circular dependencies
			std::vector<struct trace>::iterator traceIt;
			traceIt = traceVariables->begin();
			while( traceIt != traceVariables->end() ) {
				if( *varIt == (*traceIt).variable ) {
					// Circular dependency detected
					DP("Circular dependency detected");
					// TODO Handle circular dependencies
					return GeneralFailure;








				}
				traceIt++;
			}
		}
		varIt++;
	}

	// Solve and calculate
	if( pendingVariables->size() != 0 ) {
		// There are other Variables which have to be solved

		// Create Equationsystem with unused Equations
		Equationsystem equationsLeft;
		eqIt = equations.begin();
		while( eqIt != equations.end() ) {
			if( *eqIt != solveEquation ) {
				equationsLeft.addEquation(*eqIt);
			}
			eqIt++;
		}
		equationsLeft.setPendingVariables(pendingVariables);
		equationsLeft.setTraceVariables(traceVariables);

		// Solve next pending Variable
		rc = equationsLeft.solvePending();

		if( rc != Successful ) {
			return rc;
		}
	}

	// Calculate
	rc = valueComponent->calculate();
	if( rc != Successful ) {
		return rc;
	}
	// If everything is okay, set the Variable's numerical value
	variable->setValue(valueComponent->getQuantity());
	// And it's quality
	variable->setQuality(valueComponent->getQuality());

	return rc;

}

ResultCode Equationsystem::calculateFor(Variable* variable) {

	return solveFor(variable);

}

void Equationsystem::setPendingVariables(
		std::vector<Variable*> *pendingVariables) {

	free(this->pendingVariables);
	this->pendingVariables = pendingVariables;

}

ResultCode Equationsystem::solvePending() {

	Variable *solveVariable;
	ResultCode rc;

	solveVariable = pendingVariables->back();
	pendingVariables->pop_back();
	rc = solveFor(solveVariable);

	return rc;

}

void Equationsystem::setTraceVariables(std::vector<struct trace>* traceVariables) {

	free(this->traceVariables);
	this->traceVariables = traceVariables;

}

}


