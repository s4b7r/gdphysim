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

	DP("Eqsys::solveFor(" << variable->getName() << ")");
	DP("Eqsys with " << equations.size() << " Eqs left");

	if( equations.size() <= 0 ) {
		DP("Equationsystem has no Equations for solving!");
		return GeneralFailure;
	}

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
	DP("Eqsys: Solve " << solveEquation->getQuality());
	rc = solveEquation->solveFor(variable);
	if( rc != Successful ) {
		DP("Eqsys: Solve returned " << rc);
		return rc;
	}

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
		DP("Eqsys: Need " << (*varIt)->getName());
		if( !(*varIt)->isCalculable() ) {
			DP(".. and it's pending");
			pendingVariables->push_back(*varIt);

			// Check for recursive dependencies
			std::vector<struct trace>::iterator traceIt;
			traceIt = traceVariables->begin();
			while( traceIt != traceVariables->end() ) {
				if( *varIt == (*traceIt).variable ) {
					// Recursive dependency detected
					DP("Recursive dependency detected with " << variable->getName() << " and " << (*varIt)->getName());

					// Create Equation with two Equations value sides representing one Variable
					Equation *circEquation = new Equation();
					circEquation->setLeft(valueComponent);
					std::vector<struct trace>::iterator traceItB;
					Component *valueComponentB = 0;
					traceItB = traceVariables->begin();
					while( traceItB != traceVariables->end() && valueComponentB == 0 ) {
						// Should: Simplify: *traceItB equals *traceIt  <-- when necessary
						if( (*traceItB).variable == *varIt ) {
							DP("Eq1 to solve rec.dep. with: " << solveEquation->getQuality());
							DP("Eq2 to solve rec.dep. with: " << (*traceItB).equation->getQuality());
							DP("Variable to be eliminated: " << variable->getName());
							rc = (*traceItB).equation->solveFor(variable); // Maybe a problem, but not yet
							if( rc != Successful ) {
								DP("Eqsys: Rec.Dep. solve 1 returns " << rc);
								return rc;
							}
							if( (*traceItB).equation->getLeft() == variable ) {
								valueComponentB = (*traceItB).equation->getRight();
							} else if( (*traceItB).equation->getRight() == variable ) {
								valueComponentB = (*traceItB).equation->getLeft();
							} else {
								return ImpossibleState;
							}
							circEquation->setRight(valueComponentB);
						}
						traceItB++;
					}
					DP("circEq containing nan values is legal");
					DP("circEq: " << circEquation->getQuality());

					rc = circEquation->standardizeLinear(*varIt);
					if( rc != Successful ) {
						DP("Eqsys: Rec.Dep. standardize returns " << rc);
						return rc;
					}
					DP("circEq standardized: " << circEquation->getQuality());

					rc = circEquation->solveFor(*varIt);
					if( rc != Successful ) {
						DP("Eqsys: Rec.Dep. solve 2 returns " << rc);
						return rc;
					}
					pendingVariables->pop_back();
					rc = circEquation->getLeft()->calculate();
					if( rc != Successful ) {
						DP("Eqsys: Rec.Dep. calc returns " << rc);
						return rc;
					}
					(*varIt)->setValue(circEquation->getLeft()->getQuantity());
					(*varIt)->setQuality(circEquation->getLeft()->getQuality());


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
		DP("Eqsys: Solve pending " << pendingVariables->size() << " Variables");
		rc = equationsLeft.solvePending();

		if( rc != Successful ) {
			DP("Eqsys: Solve pending returns " << rc);
			return rc;
		}
	}

	DP("Eqsys: " << variable->getName() << " is already quantifiable: " << variable->isQuantifiable());
	if( !variable->isQuantifiable() ) {
		// Calculate
		DP("Eqsys calculates " << valueComponent->getQuality());
		rc = valueComponent->calculate();
		if( rc != Successful ) {
			DP("Eqsys: Final calc returns " << rc);
			return rc;
		}
		// If everything is okay, set the Variable's numerical value
		variable->setValue(valueComponent->getQuantity());
		DP("Eqsys set " << variable->getName() << " 's quantity = " << valueComponent->getQuantity());
		// And it's quality
		variable->setQuality(valueComponent->getQuality());
		DP("Eqsys set " << variable->getName() << " 's quality = " << valueComponent->getQuality());
	}
	DP("Eqsys: " << variable->getName() << " is now calculable: " << variable->isCalculable());
	DP(".. and quantifiable: " << variable->isQuantifiable());

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

void Equationsystem::clearSystem() {

	equations.clear();
	pendingVariables->clear();
	traceVariables->clear();

}

void Equationsystem::setTraceVariables(std::vector<struct trace>* traceVariables) {

	free(this->traceVariables);
	this->traceVariables = traceVariables;

}

ResultCode Equationsystem::solve() {

	DP("Eqsys::solve()");

	ResultCode rc = Successful;

	std::vector<Equation*>::iterator sourceEquation;
	std::vector<Variable*> srcEqVariables;
	Variable *sourceVariable = 0;
	std::vector<Equation*>::iterator destinationEquation;
	Component *sourceComponent = 0;
	std::stack<Equation*> eqStack;
	Equation *solveEquation = 0;
	std::vector<Variable*> slvEqVariables;
	std::vector<Variable*>::iterator solveVariable;

	sourceEquation = equations.begin();
	while( sourceEquation != equations.end() ) {
		DP("Eqsys::slv: srcEq = " << (*sourceEquation)->getQuality());
		srcEqVariables.clear();
		(*sourceEquation)->getVariables(&srcEqVariables);
		DP("Eqsys::slv: " << srcEqVariables.size() << " srcEqVars");
		sourceVariable = 0;
		sourceVariable = srcEqVariables.front();
		DP("Eqsys::slv: srcVar = " << sourceVariable->getName());
		/*rc = (*sourceEquation)->standardizeLinear(sourceVariable);
		if( rc != Successful ) {
			DP("Eqsys::slv: srcEq.std1 returns " << rc);
			return rc;
		}*/
		rc = (*sourceEquation)->solveFor(sourceVariable);
		if( rc != Successful ) {
			DP("Eqsys::slv: srcEq.slv1 returns " << rc);
			return rc;
		}
		eqStack.push((Equation*)(*sourceEquation)->clone());
		if( (*sourceEquation)->getLeft() == sourceVariable ) {
			sourceComponent = (*sourceEquation)->getRight();
		} else if( (*sourceEquation)->getRight() == sourceVariable ) {
			sourceComponent = (*sourceEquation)->getLeft();
		} else {
			return ImpossibleState;
		}
		destinationEquation = sourceEquation + 1;
		DP("Eqsys::slv: Replace " << sourceVariable->getName() << " with " << sourceComponent->getQuality());
		while( destinationEquation != equations.end() ) {
			DP(".. in " << (*destinationEquation)->getQuality());
			(*destinationEquation)->replace(sourceVariable, sourceComponent);
			eqStack.push((Equation*)(*destinationEquation)->clone());
			DP(".. \\-> " << eqStack.top()->getQuality());
			destinationEquation++;
		}
		sourceEquation++;
	}

	while( !eqStack.empty() ) {
		solveEquation = eqStack.top();
		DP("Eqsys::slv: Solve " << solveEquation->getQuality());
		slvEqVariables.clear();
		solveEquation->getVariables(&slvEqVariables);
		solveVariable = slvEqVariables.begin();
		while( solveVariable != slvEqVariables.end() ) {
			DP(".. test " << (*solveVariable)->getName());
			if( !(*solveVariable)->isCalculable() ) {
				DP("Eqsys::slv: Solve for " << (*solveVariable)->getName());
				/*rc = solveEquation->standardizeLinear(*solveVariable);
				if( rc != Successful ) {
					DP("Eqsys::slv: srcEq.std2 returns " << rc);
					return rc;
				}*/
				rc = solveEquation->solveFor(*solveVariable);
				if( rc != Successful ) {
					DP("Eqsys::slv: srcEq.slv2 returns " << rc);
					return rc;
				}
				rc = solveEquation->calculateFor(*solveVariable);
				if( rc != Successful ) {
					DP("Eqsys::slv: srcEq.calc returns " << rc);
					return rc;
				}
			}
			solveVariable++;
		}
		eqStack.pop();
	}

	//DP("Okay");
	/*exit(0);*/
	return rc;

}

}


