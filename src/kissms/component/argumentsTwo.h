/*
 * argumentsTwo.h
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#ifndef ARGUMENTSTWO_H_
#define ARGUMENTSTWO_H_


namespace kissms {

/**
 * @brief Representation of Components taking two arguments
 *
 *
 */
class ArgumentsTwo : public Component {

public:
	ArgumentsTwo();
	virtual ~ArgumentsTwo();

	/**
	 * @brief Sets the Component's left side
	 * @param argument New argument on the Component's left side
	 *
	 */
	void setLeft( Component *argument );

	/**
	 * @brief Sets the Component's right side
	 * @param argument New argument on the Component's right side
	 */
	void setRight( Component *argument );

	/**
	 * @brief Sets the Component's arguments
	 * @param left New argument on the Component's left side
	 * @param right New argument on the Component's right side
	 *
	 */
	void setArguments( Component *left, Component *right );

	virtual bool isCalculable();

	virtual bool isQuantifiable();

protected:
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
	 * @brief The Component's left side argument
	 */
	Component *argumentLeft;

	/**
	 * @brief The Component's right side argument
	 */
	Component *argumentRight;

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


#endif /* ARGUMENTSTWO_H_ */
