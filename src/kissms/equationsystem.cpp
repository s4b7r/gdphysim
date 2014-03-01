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

	DP("Equationsystem::solveFor(" << variable->getName() << ")");

	Equation *mainEquation = 0;
	std::vector<Equation*>::iterator it;
	ResultCode rc;
	bool found = false;
	unsigned int minOtherVars = 0;
	std::vector<Variable*> tmpVarVector;

	DP("Search for main Equation")
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
	DP("Main Equation ID: " << mainEquation->getDebugId())
	if( !found ) {
		return GeneralFailure;
	}
	rc = mainEquation->solveFor(variable);
	if( rc != Successful ) {
		return rc;
	}
	Component *mainEqsValueside;
	if( mainEquation->getLeft() == variable ) {
		mainEqsValueside = mainEquation->getRight();
	} else {
		mainEqsValueside = mainEquation->getLeft();
	}
	variable->setQuality(mainEqsValueside->getQuality());
	DP("Set quality " << variable->getName() << " = " << variable->getQuality() <<
			" = " << mainEqsValueside->getQuality())
	if( mainEqsValueside->isCalculable() ) {
		return Successful;
	}
	DP("Equationsystem::solveFor(" << variable->getName() << ") has to resolve other Variables ...")
	std::vector<Variable*> varsToResolve;
	mainEqsValueside->getVariables(&varsToResolve);
	std::vector<Variable*>::iterator debugVarIt;
	debugVarIt = varsToResolve.begin();
	while( debugVarIt != varsToResolve.end() ) {
		Variable *tmp = *debugVarIt;
		DP("... has to resolve (vector): " << tmp->getName())
		debugVarIt++;
	}
	std::vector<Equation*> equationsLeft;
	it = equations.begin();
	while( it != equations.end() ) {
		if( *it != mainEquation ) {
			equationsLeft.push_back(*it);
		}
		it++;
	}
	DP("... with " << equationsLeft.size() << " Equations left")

	std::stack<Variable*> varsToRes;
	std::vector<Variable*>::iterator itVar;
	itVar = varsToResolve.begin();
	while( itVar != varsToResolve.end() ) {
		varsToRes.push(*itVar);
		DP("... has to resolve (stack): " << (*itVar)->getName())
		itVar++;
	}
	while( !varsToRes.empty() ) {
		solveFor(&varsToRes, &equationsLeft);
		std::stack<Variable*> tmpVarsToRes;
		while( !varsToRes.empty() ) {
			Variable *tmp = varsToRes.top();
			DP("... has to resolve (stack): " << tmp->getName())
			tmpVarsToRes.push(tmp);
			varsToRes.pop();
		}
		while( !tmpVarsToRes.empty() ) {
			varsToRes.push(tmpVarsToRes.top());
			tmpVarsToRes.pop();
		}
		DP("... with " << equationsLeft.size() << " Equations left")
	}

	return Successful;

}

ResultCode Equationsystem::calculateFor(Variable* variable) {

	DP("Equationsystem::calculateFor(" << variable->getName() << ")");

	ResultCode rc;
	std::vector<Equation*>::iterator it;
	Component *calcComp;
	Variable *explicitVariable;

	rc = solveFor(variable);
	if( rc != Successful ) {
		return rc;
	}
	DP("calculateFor() did it's solveFor()")
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


