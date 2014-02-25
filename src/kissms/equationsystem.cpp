/*
 * equationsystem.cpp
 *
 *  Created on: 25.02.2014
 *      Author: sieb
 */

#include "kissms/kissms.h"

namespace kissms {

Equationsystem::Equationsystem() {
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

	Equation *mainEquation = 0;
	std::vector<Equation*>::iterator it;
	ResultCode rc;
	bool found = false;
	unsigned int minOtherVars = 0;
	std::vector<Variable*> tmpVarVector;

	it = equations.begin();
	while( it != equations.end() ) {
		if( (*it)->hasChild(variable) ) {
			tmpVarVector.clear();
			(*it)->getVariables(&tmpVarVector);
			if( !found || minOtherVars > tmpVarVector.size() ) {
				mainEquation = *it;
				minOtherVars = tmpVarVector.size();
				found = true;
			}
		}
		it++;
	}
	if( !found ) {
		return GeneralFailure;
	}
	printf("\nDebug 3\n");
	rc = mainEquation->solveFor(variable);
	if( rc != Successful ) {
		return rc;
	}
	printf("\nDebug 4\n");
	Component *mainEqsValueside = 0;
	if( mainEquation->getLeft() == variable ) {
		mainEqsValueside = mainEquation->getRight();
	} else {
		mainEqsValueside = mainEquation->getLeft();
	}
	variable->setQuality(mainEqsValueside->getQuality());
	printf("\nDebug 5: %s\n", variable->getQuality().c_str());
	if( mainEqsValueside->isCalculable() ) {
		return Successful;
	}
	printf("\nDebug 6\n");
	std::vector<Variable*> varsToResolve;
	mainEqsValueside->getVariables(&varsToResolve);
	std::vector<Equation*> equationsLeft;
	it = equations.begin();
	while( it != equations.end() ) {
		printf("\nDebug 9\n");
		if( *it != mainEquation ) {
			printf("\nDebug 8\n");
			equationsLeft.push_back(*it);
		}
		it++;
	}
	printf("\nDebug 7: %d\n", (int)equationsLeft.size());

	std::stack<Variable*> varsToRes;
	std::vector<Variable*>::iterator itVar;
	itVar = varsToResolve.begin();
	while( itVar != varsToResolve.end() ) {
		varsToRes.push(*itVar);
		itVar++;
	}
	printf("\nDebug 10: %d\n", (int)varsToRes.size());
	while( !varsToRes.empty() ) {
		printf("\nDebug 11\n");
		solveFor(&varsToRes, &equationsLeft);
	}

	return Successful;

}

ResultCode Equationsystem::calculateFor(Variable* variable) {

	ResultCode rc;
	std::vector<Equation*>::iterator it;
	Component *calcComp;
	Variable *explicitVariable;

	rc = solveFor(variable);
	if( rc != Successful ) {
		return rc;
	}
printf("\nDebug 12\n");
	it = equations.begin();
	while( it != equations.end() ) {
		if( (*it)->hasChild(variable) && (*it)->isExplicitly(variable) ) {
			if( (*it)->getLeft() == variable ) {
				calcComp = (*it)->getRight();
				explicitVariable = (Variable*) (*it)->getLeft();
			} else if( (*it)->getRight() == variable ) {
				calcComp = (*it)->getLeft();
				explicitVariable = (Variable*) (*it)->getRight();
			} else {
				return ImpossibleState;
			}
			if( calcComp->isCalculable() ) {
				rc = calcComp->calculate();
				if( rc == Successful ) {
					// If everything is okay, set the Variable's numerical value
					explicitVariable->setValue(calcComp->getQuantity());
					// And it's quality
					explicitVariable->setQuality(calcComp->getQuality());
				}
			} else {
				printf("\nDebug AA: %s\n", explicitVariable->getName());
				explicitVariable->setQuality(calcComp->getQuality());
				rc = NotCalculable;
				std::vector<Variable*> varsInCalc;
				calcComp->getVariables(&varsInCalc);
				std::vector<Variable*>::iterator varIt;
				varIt = varsInCalc.begin();
				std::vector<Equation*>::iterator eqIt;
				while( varIt != varsInCalc.end() ) {
					eqIt = equations.begin();
					while( eqIt != equations.end() ) {
						if( (*eqIt)->isExplicitly(*varIt) ) {
							if( (*eqIt)->getLeft() == *varIt ) {
								(*varIt)->setValue((*eqIt)->getRight()->getQuantity());
							} else if( (*eqIt)->getRight() == *varIt ) {
								(*varIt)->setValue((*eqIt)->getLeft()->getQuantity());
							}
						}
						eqIt++;
					}
					varIt++;
				}
				rc = calculateFor(variable);
			}
		}
		it++;
	}
	return rc;

}

ResultCode Equationsystem::solveFor(
		std::stack<Variable*> *variablesToResolve,
		std::vector<Equation*> *equationsLeft) {

	Variable *variable = variablesToResolve->top();
	variablesToResolve->pop();
	Equation *mainEquation = 0;
	std::vector<Equation*>::iterator it;
	ResultCode rc;
	bool found = false;
	unsigned int minOtherVars = 0;
	std::vector<Variable*> tmpVarVector;

	it = equationsLeft->begin();
	while( it != equationsLeft->end() ) {
		if( (*it)->hasChild(variable) ) {
			tmpVarVector.clear();
			(*it)->getVariables(&tmpVarVector);
			if( !found || minOtherVars > tmpVarVector.size() ) {
				mainEquation = *it;
				minOtherVars = tmpVarVector.size();
				found = true;
			}
		}
		it++;
	}
	if( !found ) {
		return GeneralFailure;
	}
	rc = mainEquation->solveFor(variable);
	if( rc != Successful ) {
		return rc;
	}
	Component *mainEqsValueside = 0;
	if( mainEquation->getLeft() == variable ) {
		mainEqsValueside = mainEquation->getRight();
	} else {
		mainEqsValueside = mainEquation->getLeft();
	}
	if( mainEqsValueside->isCalculable() ) {
		return Successful;
	}
	std::vector<Variable*> varsToResolve;
	mainEqsValueside->getVariables(&varsToResolve);
	it = equationsLeft->begin();
	found = false;
	while( !found && it != equationsLeft->end() ) {
		if( *it == mainEquation ) {
			equationsLeft->erase(it);
		}
		it++;
	}

	std::vector<Variable*>::iterator itVar;
	itVar = varsToResolve.begin();
	while( itVar != varsToResolve.end() ) {
		variablesToResolve->push(*itVar);
		itVar++;
	}

	return Successful;

}

}


