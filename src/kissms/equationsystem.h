/*
 * equationsystem.h
 *
 *  Created on: 25.02.2014
 *      Author: sieb
 */

#ifndef EQUATIONSYSTEM_H_
#define EQUATIONSYSTEM_H_


namespace kissms {

/**
 *
 */
class Equationsystem {

public:
	Equationsystem();
	virtual ~Equationsystem();

	/**
	 *
	 */
	void addEquation( Equation *equation );

	/**
	 *
	 */
	void removeEquation( Equation *equation );

	/**
	 *
	 */
	bool containsEquation( Equation *equation );

	/**
	 *
	 */
	ResultCode solveFor( Variable *variable );

	/**
	 *
	 */
	ResultCode calculateFor( Variable *variable );

	/**
	 *
	 */
	void setPendingVariables( std::vector<Variable*> pendingVariables );

	/**
	 *
	 */
	ResultCode solvePending();

private:
	/**
	 *
	 */
	std::vector<Equation*> equations;

	/**
	 *
	 */
	std::vector<Variable*> pendingVariables;


};

}

#endif /* EQUATIONSYSTEM_H_ */
