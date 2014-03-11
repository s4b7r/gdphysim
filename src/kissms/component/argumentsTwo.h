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

	/**
	 * @brief Returns the Component's left argument
	 * @return Component's left-side argument
	 */
	Component* getLeft();

	/**
	 * @brief Returns the Component's right argument
	 * @return Component's right-side arguments
	 */
	Component* getRight();

	virtual void replace( Component *search, Component *replace );

	virtual bool isCalculable();

	virtual bool isQuantifiable();

	virtual ComponentType getType();

	virtual bool hasChild( Component *child );

	virtual bool isVectorial();

	virtual void getVariables( std::vector<Variable*> *variables );

	virtual Component* clone();

	virtual void clone( Component *source, Component *destination );

protected:
	/**
	 * @brief The Component's left side argument
	 */
	Component *argumentLeft;

	/**
	 * @brief The Component's right side argument
	 */
	Component *argumentRight;

	/**
	 * @brief Checks whether an other Component is on the Component's left side
	 * @param component Variable to check for
	 * @return bool
	 */
	bool isOnLeft( Component *component );

	/**
	 * @brief Checks whether an other Component is on the Component's right side
	 * @param component Variable to check for
	 * @return bool
	 */
	bool isOnRight( Component *component );


};

}


#endif /* ARGUMENTSTWO_H_ */
