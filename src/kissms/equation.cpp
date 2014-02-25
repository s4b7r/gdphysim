/*
 * equation.cpp
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#include "kissms/kissms.h"

namespace kissms {

Equation::Equation() {

	for( int i = 0; i < 3; i++ ) {
		scalarEquations[0] = 0;
	}

}

Equation::~Equation() {
}

ResultCode Equation::solveFor(Variable* variable) {

	ResultCode solveResult = Successful;

	if( isVectorial() ) {
		for( int i = 0; i < 3; i++ ) {
			scalarEquations[i] = new Equation();
		}
		getScalarEquations(scalarEquations);
		for( int i = 0; i < 3; i++ ) {
			if( scalarEquations[i]->hasChild(variable) ) {
				scalarEquations[i]->solveFor(variable);
			}
		}
	} else {
		// Repeatedly try to solve the Equation for the given Variable,
		// until the Variable is explicitly represented.
		// Abort if solving process fails.
		while( !isExplicitly(variable) && solveResult == Successful ) {
			solveResult = solveFor(variable, isOnLeft(variable));
		}
	}
	return solveResult;

}

ResultCode Equation::calculateFor(Variable* variable) {

	ResultCode rc;
	Component *calcComp;
	Variable *explicitVariable;

	// First the Equation has to be solved
	rc = solveFor(variable);
	if( rc != Successful ) {
		return rc;
	}
	if( isVectorial() ) {
		for( int i = 0; i < 3; i++ ) {
			if( scalarEquations[i]->hasChild(variable) ) {
				return scalarEquations[i]->calculateFor(variable);
			}
		}
		return NotCalculable;
	} else {
		// Set the placeholder regarding the Equation's side which the Variable belongs to
		if( isOnLeft(variable) ) {
			calcComp = argumentRight;
			explicitVariable = (Variable*) argumentLeft;
		} else if( isOnRight(variable) ) {
			calcComp = argumentLeft;
			explicitVariable = (Variable*) argumentRight;
		} else {
			return ImpossibleState;
		}
		if( !calcComp->isCalculable() ) {
			return NotCalculable;
		}
		rc = calcComp->calculate();
		if( rc == Successful ) {
			// If everything is okay, set the Variable's numerical value
			explicitVariable->setValue(calcComp->getQuantity());
		}
	}

	return rc;

}

bool Equation::isExplicitly(Variable* variable) {

	if( argumentLeft == (Component*)variable || argumentRight == (Component*)variable ) {
		return true;
	}
	return false;

}

ResultCode Equation::calculate() {

	return ImpossibleState;

}

ComponentType Equation::getType() {

	return tEquation;

}

ResultCode Equation::solveFor(Variable* variable, bool variableOnLeft) {

	/**
	 * The Equation's argument on the Variable's side. This Component
	 * will have to reform itself.
	 */
	Component **reformComponent;
	/**
	 * The Equation's argument not on the Variable's side.
	 */
	Component **otherSide;
	/**
	 * The Component which will replace the Component on the Variable's side.
	 */
	Component **newSide = (Component**) malloc(sizeof(Component*));
	/**
	 * The Component which will encapsulate the Component not on the Variable's side.
	 */
	Component **newOtherSide = (Component**) malloc(sizeof(Component*));
	ResultCode reformResult;

	// Set the placeholder regarding the Equation's side which the Variable belongs to
	if( variableOnLeft ) {
		reformComponent = &argumentLeft;
		otherSide = &argumentRight;
	} else {
		reformComponent = &argumentRight;
		otherSide = &argumentLeft;
	}

	// Call the Component's reform-method
	reformResult = (*reformComponent)->reformFor(variable, newSide, newOtherSide);

	// Further processing on success only
	if( reformResult == Successful ) {
		free(*reformComponent);
		// Replace Variable's side
		*reformComponent = *newSide;
		// Fill the encapsulating Component with the other side's old Component
		ComponentType ct = (*newOtherSide)->getType();
		switch (ct) {
		case tCosinus:
		case tNegation:
		case tReciprocal:
		case tSinus:
		case tSinusArc:
		case tCosinusArc:
			(*(ArgumentsOne**)newOtherSide)->setArgument(*otherSide);

			break;
		case tAddition:
		case tMultiplication:
			(*(ArgumentsTwo**)newOtherSide)->setLeft(*otherSide);

			break;
		default:
			return ImpossibleState;
			break;
		}
		// Replace other side
		*otherSide = *newOtherSide;

		return Successful;
	}
	return reformResult;

}

ResultCode Equation::reformFor(Variable* variable, Component** newSide,
		Component** otherSide) {

	return ImpossibleState;

}

ResultCode Equation::getScalarEquations(Equation* equations[]) {

	struct iteration it;
	Component *current;
	Component *parent[3];
	WhichLastArgument parentsArgument;

	std::stack<struct iteration> todo;

	struct iteration equationsLeft;
	struct iteration equationsRight;
	equationsLeft.current = argumentLeft;
	equationsRight.current = argumentRight;
	for( int i = 0; i < 3; i++ ) {
		equationsLeft.parent[i] = equations[i];
		equationsRight.parent[i] = equations[i];
	}
	equationsLeft.parentsArgument = Left;
	equationsRight.parentsArgument = Right;
	todo.push(equationsLeft);
	todo.push(equationsRight);

	while( !todo.empty() ) {
		it = todo.top();
		current = it.current;
		for( int i = 0; i < 3; i++ ) {
			parent[i] = it.parent[i];
		}
		parentsArgument = it.parentsArgument;
		todo.pop();
		switch( current->getType() ) {
		case tVector:
			for( int i = 0; i < 3; i++ ) {
				Component *argument = ((Vector*)current)->getArgument(i);
				switch (parentsArgument) {
				case Single:
					((ArgumentsOne*)parent[i])->setArgument(argument);

					break;
				case Left:
					((ArgumentsTwo*)parent[i])->setLeft(argument);

					break;
				case Right:
					((ArgumentsTwo*)parent[i])->setRight(argument);

					break;
				default:
					break;
				}
			}

			break;
		case tVectorproduct:
			Vector *result;
			result = ((Vectorproduct*)current)->getVector();
			it.current = result;
			struct iteration newIt;
			newIt.current = result;
			for( int i = 0; i < 3; i++ ) {
				newIt.parent[i] = parent[i];
			}
			newIt.parentsArgument = parentsArgument;
			todo.push(newIt);

			break;
		case tAddition:
		case tMultiplication:
		case tNegation:
		case tReciprocal:
		case tConstant:
		case tVariable:
			getScalarEquations(current, parent, parentsArgument, todo);

			break;
		default:
			break;
		}
	}

	return NotYetImplemented;

}

void Equation::getScalarEquations(Component* current,
		Component* parent[], WhichLastArgument parentsArgument,
		std::stack<struct iteration> todo) {

	struct iteration newItLeft;
	struct iteration newItRight;

	for( int i = 0; i < 3; i++ ) {
		Component *newArgument;
		switch (current->getType()) {
		case tAddition:
			newArgument = new Addition();

			break;
		case tMultiplication:
			newArgument = new Multiplication();

			break;
		case tNegation:
			newArgument = new Negation();

			break;
		case tReciprocal:
			newArgument = new Reciprocal();

			break;
		case tConstant:
		{
			newArgument = new Constant();
			void *value = 0;
			Constant::Type type = ((Constant*)newArgument)->getValue(value);
			switch (type) {
			case Constant::String:
				((Constant*)newArgument)->setValue((char*)value);

				break;
			case Constant::Integer:
				((Constant*)newArgument)->setValue(*(int*)value);

				break;
			case Constant::Double:
				((Constant*)newArgument)->setValue(*(double*)value);

				break;
			default:
				break;
			}
		}
		break;
		case tVariable:
		{
			newArgument = new Variable();
			((Variable*)newArgument)->setName(((Variable*)current)->getName());
			void *value = 0;
			Variable::Type type = ((Variable*)newArgument)->getValue(value);
			switch (type) {
			case Variable::Integer:
				((Variable*)newArgument)->setValue(*(int*)value);

				break;
			case Variable::Double:
				((Variable*)newArgument)->setValue(*(double*)value);

				break;
			default:
				break;
			}
		}
		break;
		default:
			break;
		}
		switch (parentsArgument) {
		case Single:
			((ArgumentsOne*)parent[i])->setArgument(newArgument);

			break;
		case Left:
			((ArgumentsTwo*)parent[i])->setLeft(newArgument);

			break;
		case Right:
			((ArgumentsTwo*)parent[i])->setRight(newArgument);

			break;
		default:
			break;
		}
		newItLeft.parent[i] = newArgument;
		newItRight.parent[i] = newArgument;
	}
	switch (current->getType()) {
	case tAddition:
	case tMultiplication:
		newItLeft.current = ((ArgumentsTwo*)current)->getLeft();
		newItRight.current = ((ArgumentsTwo*)current)->getRight();
		newItLeft.parentsArgument = Left;
		newItRight.parentsArgument = Right;
		todo.push(newItLeft);
		todo.push(newItRight);

		break;
	case tNegation:
	case tReciprocal:
		newItLeft.current = ((ArgumentsOne*)current)->getArgument();
		newItLeft.parentsArgument = Single;
		todo.push(newItLeft);

		break;
	default:
		break;
	}

}

std::string Equation::getQuality() {

	std::string tmp = "ups";
	return tmp;

}

}


