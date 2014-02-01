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
 * @author sbekemeier
 *
 *
 */
class ArgumentsTwo : public Component {

public:
	ArgumentsTwo(  );
	virtual ~ArgumentsTwo(  );

	/**
	 * @brief
	 * @param argument Component on this component's left side
	 *
	 */
	void setLeft( Component *argument );

	/**
	 * @brief
	 * @param argument Component on this component's right side
	 */
	void setRight( Component *argument );

	/**
	 * @brief
	 * @param left Component on this component's left side
	 * @param right Component on this component's right side
	 *
	 */
	void setArguments( Component *left, Component *right );

};

}


#endif /* ARGUMENTSTWO_H_ */
