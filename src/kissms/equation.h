/*
 * equation.h
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#ifndef EQUATION_H_
#define EQUATION_H_


namespace kissms {

class Equation : public ArgumentsTwo {

public:
	Equation(  );
	virtual ~Equation(  );

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
	 * @see solveFor()
	 */
	ResultCode calculateFor( Variable *variable );

	/**
	 * @brief Checks whether the Equation contains a given Variable
	 * @param variable Variable to check for
	 */
	bool contains( Variable *variable );

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
	 * @brief Checks whether the Equation is explicitly representing a Variable
	 * @param variable Variable to check for
	 */
	bool isExplicitly( Variable *variable );

	/**
	 * @brief All Variables on the Equation's left side
	 */
	std::vector<Variable*> m_variablesLeft;

	/**
	 * @brief All Variables on the Equation's right side
	 */
	std::vector<Variable*> m_variablesRight;

};

}


#endif /* EQUATION_H_ */
