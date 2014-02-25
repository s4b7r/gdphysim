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

private:
	/**
	 *
	 */
	std::vector<Equation*> equations;


}

#endif /* EQUATIONSYSTEM_H_ */
