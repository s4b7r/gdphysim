/*
 * equation.cpp
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#include "kissms/kissms.h"

namespace kissms {

Equation::Equation() {

	scalarEquations = new Equationsystem();

}

Equation::~Equation() {

	free(scalarEquations);

}

ResultCode Equation::solveFor(Variable* variable) {

	ResultCode solveResult = Successful;
	if( !isVectorial() ) {
		Variable *twiceVariable = 0;
		if( !hasSameVariableTwice(&twiceVariable) ) {
			// Repeatedly try to solve the Equation for the given Variable,
			// until the Variable is explicitly represented.
			// Abort if solving process fails.
			while( !isExplicitly(variable) && solveResult == Successful ) {
				solveResult = solveFor(variable, isOnLeft(variable));
			}
		} else {
			if( twiceVariable == variable ) {
				standardizeLinear(twiceVariable);
				solveResult = solveFor(variable);
			} else {
				solveResult = GeneralFailure;
			}
		}
	} else {
		getScalarEquations();
		scalarEquations->solveFor(variable);
	}

	return solveResult;

}

ResultCode Equation::calculateFor(Variable* variable) {

	ResultCode rc;
	Component *calcComp;
	Variable *explicitVariable;

	if( !isVectorial() ) {
		// First the Equation has to be solved
		rc = solveFor(variable);
		if( rc != Successful ) {
			return rc;
		}
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
			// And it's quality
			explicitVariable->setQuality(calcComp->getQuality());
		}
	} else {
		getScalarEquations();
		rc = scalarEquations->calculateFor(variable);
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
			getScalarEquations(current, parent, parentsArgument, &todo);

			break;
		default:
			break;
		}
	}

	return Successful;

}

void Equation::getScalarEquations(Component* current,
		Component* parent[], WhichLastArgument parentsArgument,
		std::stack<struct iteration>* todo_stack) {


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
			void **value = (void**)malloc(sizeof(void*));
			Constant::Type type = ((Constant*)current)->getValue(value);
			switch (type) {
			case Constant::String:
				((Constant*)newArgument)->setValue(*((char**)value));

				break;
			case Constant::Integer:
				((Constant*)newArgument)->setValue(**((int**)value));

				break;
			case Constant::Double:
				((Constant*)newArgument)->setValue(**((double**)value));

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
			void **value = (void**)malloc(sizeof(void*));
			Variable::Type type = ((Variable*)newArgument)->getValue(value);
			switch (type) {
			case Variable::Integer:
				((Variable*)newArgument)->setValue(**((int**)value));

				break;
			case Variable::Double:
				((Variable*)newArgument)->setValue(**((double**)value));

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
		todo_stack->push(newItLeft);
		todo_stack->push(newItRight);

		break;
	case tNegation:
	case tReciprocal:
		newItLeft.current = ((ArgumentsOne*)current)->getArgument();
		newItLeft.parentsArgument = Single;
		todo_stack->push(newItLeft);

		break;
	default:
		break;
	}

}

std::string Equation::getQuality() {

	std::string tmp;
	std::ostringstream oss;

	//if( isQuantifiable() ) {
	//	oss << getQuantity();
	//} else {
	oss << argumentLeft->getQuality() << "=" << argumentRight->getQuality();
	//}
	tmp = oss.str();
	return tmp;

}

void Equation::getScalarEquations() {

	Equation *equations[3];
	scalarEquations = new Equationsystem();
	for( int i = 0; i < 3; i++ ) {
		equations[i] = new Equation();
		scalarEquations->addEquation(equations[i]);
	}
	getScalarEquations(equations);

}

ResultCode Equation::standardizeLinear(Variable *variable) {
	// This is the symbolic method

	// TODO Check for conditions to standardize to linear Equation

	DP("Equation::standardizeLinear(" << variable->getName() << ")");

	ResultCode rc = Successful;

	Negation *negationB1 = new Negation();
	Addition *additionB1 = new Addition();
	Constant *constantB1 = new Constant();
	Addition *b = 0;

	negationB1->setArgument(argumentRight);
	additionB1->setArguments(argumentLeft, negationB1);
	constantB1->setValue(0);
	additionB1->replace(variable, constantB1);
	b = (Addition*)(additionB1->clone());
	additionB1->replace(constantB1, variable);
	rc = b->calculate();
	DP("Eq::standardize : Calculate b returns " << rc);
	//if( rc != Successful ) {
	//	return rc;
	//}
	DP("Eq::standardize : b = " << b->getQuality());

	Negation *negationM1 = new Negation();
	Addition *additionM1 = new Addition();
	Constant *constantM1 = new Constant();
	Addition *additionM1b = 0;
	Negation *negationM2 = new Negation();
	Addition *m = new Addition();

	negationM1->setArgument(argumentRight);
	additionM1->setArguments(argumentLeft, negationM1);
	constantM1->setValue(1);
	additionM1->replace(variable, constantM1);
	additionM1b = (Addition*)(additionM1->clone());
	additionM1->replace(constantM1, variable);
	rc = additionM1b->calculate();
	DP("Eq::standardize : Calculate addM1 returns " << rc);
	//if( rc != Successful ) {
	//	return rc;
	//}
	negationM2->setArgument(b);
	m->setArguments(additionM1b, negationM2);
	DP("Eq::standardize : m = " << m->getQuality());
	m->calculate();
	DP("Eq::standardize : m = " << m->getQuantity());

	Constant *constant00 = new Constant();
	Multiplication *mult = new Multiplication();
	Addition *addition00 = new Addition();

	constant00->setValue(0);
	mult->setArguments(m, variable);
	addition00->setArguments(mult, b);
	DP("Eq::standardize : final add = " << addition00->getQuality());
	rc = addition00->calculate();
	DP("Eq::standardize : Calculate final add returns " << rc);
	//if( rc != Successful ) {
	//	return rc;
	//}

	argumentLeft = constant00;
	argumentRight = addition00;

	DP("Eq::standardize Equation: " << getQuality());

	//exit(0);
	return rc;

}

/*ResultCode Equation::standardizeLinear(Variable *variable) {
	// This is the numeric version

	ResultCode rc = Successful;
	Negation *negation = new Negation();
	Addition *addition = new Addition();
	double b = 0;
	double m = 0;

	negation->setArgument(argumentRight);
	addition->setArguments(argumentLeft, negation);

	variable->setValue(0);
	rc = addition->calculate();
	if( rc != Successful ) {
		return rc;
	}
	b = addition->getQuantity();

	variable->setValue(1);
	rc = addition->calculate();
	if( rc != Successful ) {
		return rc;
	}
	m = addition->getQuantity() - b;

	variable->resetValue();

	Constant *zero = new Constant();
	Constant *constB = new Constant();
	Constant *constM = new Constant();
	Multiplication *mu = new Multiplication();
	Addition *ad = new Addition();

	zero->setValue(0);
	constB->setValue(b);
	constM->setValue(m);
	ad->setArguments(mu, constB);
	mu->setArguments(constM, variable);

	argumentLeft = zero;
	argumentRight = ad;

	return rc;

}*/

bool Equation::hasSameVariableTwice(Variable** variable) {

	std::vector<Variable*> foundVariables;
	std::vector<Variable*>::iterator varItA;
	std::vector<Variable*>::iterator varItB;

	getVariables(&foundVariables);

	varItA = foundVariables.begin();
	while( varItA != foundVariables.end() ) {
		varItB = foundVariables.begin();
		while( varItB != foundVariables.end() ) {
			if( *varItA == *varItB && varItA != varItB ) {
				*variable = *varItA;
				return true;
			}
			varItB++;
		}
		varItA++;
	}
	variable = 0;
	return false;

}

void Equation::setScalarEquations(Equationsystem* scalarEquations) {

	this->scalarEquations = scalarEquations;

}

}


