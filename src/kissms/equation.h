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
	 * @brief Checks whether the Equation contains a given Variable
	 * @param variable Variable to check for
	 */
	bool contains( Variable *variable );

	virtual void calculate();

	virtual ResultCode reformFor( Variable *variable, Component **newSide, Component **otherSide,
			Component **placeholder );

	virtual bool isCalculable();

	virtual bool isQuantifiable();

private:
	/**
	 * @brief Checks whether a Variable is on the Equation's left side
	 * @param variable Variable to check for
	 */
	bool isOnLeft( Variable *variable );

	/**
	 * @brief Checks whether a Variable is on the Equation's right side
	 * @param variable Variable to check for
	 */
	bool isOnRight( Variable *variable );

	/**
	 * @brief Checks whether a given std::vector<Variable*> contains a given Variable
	 * @param variable Variable to check for
	 * @param vector std::vector<Variable*> in which variable shall be searched
	 */
	bool isOnVector( Variable *variable, std::vector<Variable*> vector );

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
	 * @brief All Variables on the Equation's left side
	 */
	std::vector<Variable*> variablesLeft;

	/**
	 * @brief All Variables on the Equation's right side
	 */
	std::vector<Variable*> variablesRight;

};

}


#endif /* EQUATION_H_ */
