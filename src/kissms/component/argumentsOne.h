/*
 * argumentsOne.h
 *
 *  Created on: 30.01.2014
 *      Author: sieb
 */

#ifndef ARGUMENTSONE_H_
#define ARGUMENTSONE_H_


namespace kissms {

/**
 * @brief Representation of Components taking one argument
 *
 *
 */
class ArgumentsOne : public Component {

public:
	ArgumentsOne();
	virtual ~ArgumentsOne();

	/**
	 * @brief Sets the Component's argument
	 * @param argument The Component's new argument
	 */
	void setArgument( Component *argument );

	virtual bool isCalculable();

	virtual bool isQuantifiable();

	virtual ComponentType getType();

	virtual bool hasChild( Component *child );

	virtual bool isVectorial();

protected:
	/**
	 * @brief The Component's argument
	 */
	Component *argument;

};

}


#endif /* ARGUMENTSONE_H_ */
