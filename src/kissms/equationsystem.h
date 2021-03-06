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
 * @brief An Equationsystem containing multiplce Equations
 */
class Equationsystem {

public:
	/**
	 * @brief Enumeration type for Equationsystem's Variable-trace
	 */
	struct trace {
		/**
		 * @brief Variable which has been solved
		 */
		Variable *variable;
		/**
		 * @brief Equation which solved the Variable
		 */
		Equation *equation;
	};

	Equationsystem();
	virtual ~Equationsystem();

	/**
	 * @brief Add an Equation to the Equationsystem
	 * @param equation The Equation which shall be added
	 */
	void addEquation( Equation *equation );

	/**
	 * @brief Remove an Equation from the Equationsystem
	 * @param equation The Equation which shall be removed
	 */
	void removeEquation( Equation *equation );

	/**
	 * @brief Remove all Equations from the Equationsystem
	 */
	void clearSystem();

	/**
	 * @brief Checks wether the Equationsystem contains an Equation
	 * @param equation Equation to check for
	 * @retval true The Equationsystem contains the given Equation
	 * @retval false The Equationsystem does not contain the given Equation
	 */
	bool containsEquation( Equation *equation );

	/**
	 * @brief Solves and calculates the Equationsystem
	 * @param variable Variable for which the Equationsystem shall be solved
	 * @return ResultCode
	 */
	ResultCode solveFor( Variable *variable );

	/**
	 * @brief Solves and calculates the Equationsystem
	 * @param variable Variable for which the Equationsystem shall be solved
	 * @return ResultCode
	 *
	 * Just calls solveFor( Variable *variable )
	 *
	 * @see solveFor( Variable *variable )
	 */
	ResultCode calculateFor( Variable *variable );

	/**
	 * @brief Sets the Equationsystem's pending Variables
	 * @param pendingVariables C++ vector of Variables to set the System's pending Variables to
	 */
	void setPendingVariables( std::vector<Variable*> *pendingVariables );

	/**
	 * @brief Solves the Equationsystem for the next pending Variable
	 * @return ResultCode
	 */
	ResultCode solvePending();

	/**
	 * @brief Sets the Equationsystem's Variable-trace-vector
	 * @param traceVariables C++ vector of Variables to set the System's trace to
	 */
	void setTraceVariables( std::vector<struct trace> *traceVariables );

	/**
	 * @brief Solves the Equationsystem for all Variables
	 * @return ResultCode
	 */
	ResultCode solve();

private:
	/**
	 * @brief The System's single Equations
	 */
	std::vector<Equation*> equations;

	/**
	 * @brief The System's pending Variables
	 */
	std::vector<Variable*> *pendingVariables;

	/**
	 * @brief The System's Variable-trace
	 */
	std::vector<struct trace> *traceVariables;


};

}

#endif /* EQUATIONSYSTEM_H_ */
