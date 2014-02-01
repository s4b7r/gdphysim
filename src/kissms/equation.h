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
	 * @brief Solves this Equation
	 * @þaram variable Variable for which this Equation shall be solved
	 * @return ResultCode
	 *
	 * The Equation is reformed so that the given Variable is explicitely represented
	 * by the Equation's other side. The Variable's actual value won't be calculated.
	 *
	 * @see calculateFor()
	 */
	ResultCode solveFor( Variable *variable );

	/**
	 * @brief Solves and calculates this Equation
	 * @param variable Variable for which this Equation shall be solved
	 * @return ResultCode
	 *
	 * The Equation is solved using solveFor() and afterwards the Variable's value will
	 * be calculated, as far as the Equation's other side allows it.
	 *
	 * @see solveFor()
	 */
	ResultCode calculateFor( Variable *variable );

private:
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
