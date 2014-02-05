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

protected:
	/**
	 * @brief The Component's left side argument
	 */
	Component *argumentLeft;

	/**
	 * @brief The Component's right side argument
	 */
	Component *argumentRight;

};

}


#endif /* ARGUMENTSTWO_H_ */
