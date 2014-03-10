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
	 * @brief Processes this vectorial Equation into three scalar Equations
	 * @param equations Array with three Equations in which the scalar Equations will be stored
	 * @return ResultCode
	 */
	ResultCode getScalarEquations( Equation *equations[] );

	/**
	 * @brief Checks whether the Equation is explicitly representing a Variable
	 * @param variable Variable to check for
	 * @retval true The Equation explicitly represents the given Variable
	 * @retval false The Equation does not explicitly represent the given Variable
	 */
	bool isExplicitly( Variable *variable );

	/**
	 * @brief Processes this vectorial Equation into three scalar Equations
	 *
	 * The three resulting scalar Equations will be stored in the Equation's member scalarEquations.
	 */
	void getScalarEquations();

	/**
	 * @brief Processes this Equation into a standardized linear format
	 * @param variable Variable which shall be the variable in the standardized linear format
	 * @return ResultCode
	 * @todo Describe the process of standardizing an Equation
	 */
	ResultCode standardizeLinear( Variable *variable );

	/**
	 * @brief Checks wether this Equation contains the same Variable at least two times
	 * @param variable Variable to check for
	 * @retval true Equation contains the same Variable at least two times
	 * @retval false Equation contains the Variable only once
	 */
	bool hasSameVariableTwice( Variable **variable );

	/**
	 * @brief Sets this (vectorial) Equations three scalar representations
	 * @param scalarEquations Equationsystem to store as the three scalar representations
	 */
	void setScalarEquations( Equationsystem *scalarEquations );

	virtual ResultCode calculate();

	virtual ResultCode reformFor( Variable *variable, Component **newSide, Component **otherSide );

	virtual ComponentType getType();

	virtual std::string getQuality();

private:
	/**
	 * @brief Enumeration type used in getScalarEquations-process
	 * @see getScalarEquations()
	 * @see getScalarEquations( Equation *equations[] )
	 * @see getScalarEquations( Component *current, Component *parent[], WhichLastArgument parentsArgument, std::stack<struct iteration> *todo_stack )
	 * @todo Add doxygen comments for Equation::WhichLastArgument's values
	 */
	enum WhichLastArgument {
		Single = 0,
		Left,
		Right
	};

	/**
	 * @brief Struct type used in getScalarEquations-process
	 * @see getScalarEquations()
	 * @see getScalarEquations( Equation *equations[] )
	 * @see getScalarEquations( Component *current, Component *parent[], WhichLastArgument parentsArgument, std::stack<struct iteration> *todo_stack )
	 * @todo Add doxygen comments for Equation::struct iteration's fields
	 */
	struct iteration {
		Component *current;
		Component *parent[3];
		WhichLastArgument parentsArgument;
	};

	/**
	 * @brief Equationsystem representing this vectorial Equation's three scalar representations
	 */
	Equationsystem *scalarEquations;

	/**
	 * @brief Does one interation of the solving process
	 *
	 * @see solveFor( Variable *variable )
	 */
	ResultCode solveFor( Variable *variable, bool variableOnLeft );

	/**
	 * @brief Processes this vectorial Equation into three scalar Equations
	 * @param current Current Component which has to be scalarized
	 * @param parent Current Component's parent Components
	 * @param parentsArgument Information about which of the parent's arguments has to be set
	 * @param todo_stack The whole stack of Components which still have to be scalarized
	 */
	void getScalarEquations( Component *current,
			Component *parent[], WhichLastArgument parentsArgument,
			std::stack<struct iteration> *todo_stack );



};

}


#endif /* EQUATION_H_ */
