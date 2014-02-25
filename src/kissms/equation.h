/*
 * equation.h
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#ifndef EQUATION_H_
#define EQUATION_H_


namespace kissms {

/**
 * @brief Component representing a whole mathematical equation
 */
class Equation : public ArgumentsTwo {

public:
	Equation();
	virtual ~Equation();

	/**
	 * @brief Solves the Equation
	 * @param variable Variable for which the Equation shall be solved
	 * @return ResultCode
	 *
	 * The Equation is reformed so that the given Variable is explicitely represented
	 * by the Equation's other side. The Variable's actual value won't be calculated.
	 *
	 * @see calculateFor()
	 */
	ResultCode solveFor( Variable *variable );

	/**
	 * @brief Solves and calculates the Equation
	 * @param variable Variable for which the Equation shall be solved
	 * @return ResultCode
	 *
	 * The Equation is solved using solveFor() and afterwards the Variable's value will
	 * be calculated, as far as the Equation's other side allows it.
	 *
	 * @see solveFor( Variable *variable )
	 */
	ResultCode calculateFor( Variable *variable );

	/**
	 *
	 */
	ResultCode getScalarEquations( Equation *equations[] );

	virtual ResultCode calculate();

	virtual ResultCode reformFor( Variable *variable, Component **newSide, Component **otherSide );

	virtual ComponentType getType();

	virtual char* getQuality();

private:
	/**
	 *
	 */
	enum WhichLastArgument {
		Single = 0,
		Left,
		Right
	};

	/**
	 *
	 */
	struct iteration {
		Component *current;
		Component *parent[3];
		WhichLastArgument parentsArgument;
	};

	/**
	 *
	 */
	Equation *scalarEquations[3];

	/**
	 * @brief Checks whether the Equation is explicitly representing a Variable
	 * @param variable Variable to check for
	 */
	bool isExplicitly( Variable *variable );

	/**
	 * @brief Does one interation of the solving process
	 *
	 * @see solveFor( Variable *variable )
	 */
	ResultCode solveFor( Variable *variable, bool variableOnLeft );

	/**
	 *
	 */
	void getScalarEquations( Component *current,
			Component *parent[], WhichLastArgument parentsArgument,
			std::stack<struct iteration> todo );



};

}


#endif /* EQUATION_H_ */
